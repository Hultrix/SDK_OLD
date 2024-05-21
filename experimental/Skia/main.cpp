/*
MIT License

Copyright (c) 2024 Steven Starr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define SK_GL

// g++ -o test main.cpp -I/usr/include/skia -lskia -lsfml-graphics -lsfml-window -lsfml-system  -lyogacore

#include <memory>
#include <cmath>
#include <iostream>
#include <map>
#include <functional>
#include <any>
#include <thread>
#include <mutex>
#include <vector>

#include <SFML/Graphics.hpp>

#include <skia/include/gpu/GrDirectContext.h>
#include <skia/include/gpu/gl/GrGLInterface.h>
#include <skia/include/core/SkSurface.h>
#include <skia/include/core/SkCanvas.h>
#include <skia/include/core/SkPath.h>
#include <skia/include/core/SkPaint.h>
#include <skia/include/core/SkRect.h>
#include <skia/include/core/SkRRect.h>
#include <skia/include/core/SkTextBlob.h>

#include <yoga/Yoga.h>



// Window
#define WINDOW_BG_COLOR_DARK SkColorSetARGB(255, 36, 36, 36)
#define WINDOW_BG_COLOR_LIGHT SkColorSetARGB(255, 250, 250, 250)

#define WINDOW_FG_COLOR_DARK SkColorSetARGB(255, 255, 255, 255)
#define WINDOW_FG_COLOR_LIGHT SkColorSetARGB(204, 0, 0, 0)

// Light Mode
#define BUTTON_NORMAL_COLOR_LIGHT SkColorSetARGB(255, 235, 235, 235)
#define BUTTON_HOVER_COLOR_LIGHT SkColorSetARGB(255, 222, 222, 222)
#define BUTTON_CLICKED_COLOR_LIGHT SkColorSetARGB(255, 223, 223, 223)

// Dark Mode
#define BUTTON_NORMAL_COLOR_DARK SkColorSetARGB(255, 57, 57, 57)
#define BUTTON_HOVER_COLOR_DARK SkColorSetARGB(255, 69, 69, 69)
#define BUTTON_CLICKED_COLOR_DARK SkColorSetARGB(255, 102, 102, 102)

#define BUTTON_CORNER_RADIUS 5.0f








 



namespace Ht {







// Global or namespace scope for general accessibility
enum class Style { Dark, Light };




class Object {
public:
  using Slot = std::function<void(std::any)>;
  std::map<std::string, std::vector<Slot>> slots;
  std::map<std::string, std::any> properties;
  std::mutex mutex;

  virtual ~Object() {}

    void emitSignal(const std::string& signalName, std::any data) {
        std::lock_guard<std::mutex> lock(mutex);
        if (slots.find(signalName) != slots.end()) {
            for (auto& slot : slots[signalName]) {
                slot(data);
            }
        }
    }

    void connect(const std::string& signalName, Slot slot) {
        std::lock_guard<std::mutex> lock(mutex);
        slots[signalName].push_back(slot);
    }

    void setProperty(const std::string& propertyName, std::any value) {
        std::lock_guard<std::mutex> lock(mutex);
        properties[propertyName] = value;
    }

    std::any getProperty(const std::string& propertyName) {
        std::lock_guard<std::mutex> lock(mutex);
        return properties[propertyName];
    }
};





















class Widget : public Object {
public:
    Widget(int x, int y, int width, int height)
        : _bounds(SkRect::MakeLTRB(x, y, x + width, y + height)), _visible(true) {}

    virtual ~Widget() {}

    virtual void draw(SkCanvas* canvas) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void updateStyle(Style style) = 0;
    
    void setVisible(bool visible) {
        setProperty("visible", visible);
        _visible = std::any_cast<bool>(getProperty("visible"));
    }

    bool isVisible() const {
        return _visible;
    }

    void setBounds(int x, int y, int width, int height) {
        _bounds = SkRect::MakeXYWH(x, y, width, height);
    }

    const SkRect& getBounds() const {
        return _bounds;
    }
    


protected:
    SkRect _bounds;
    bool _visible;
};











class Window : public sf::RenderWindow, public Object {
public:
    Window(const std::string& title, int width, int height)
        : sf::RenderWindow(sf::VideoMode(width, height), title), 
        width(width), height(height) 
        {
            if (!this->initializeSkia()) {
                throw std::runtime_error("Failed to initialize Skia");
            }
            this->setStyle(Style::Dark); 
    }


    
    void setStyle(Style newStyle) {
            this->style = newStyle; 
            this->updateStyle(this->style); 
    }
    
    void updateStyle(Style style) {
        // Apply the background color based on the new style
        if (this->style == Style::Dark) {
            this->backgroundColor = WINDOW_BG_COLOR_DARK;
        } else {
            this->backgroundColor = WINDOW_BG_COLOR_LIGHT;
        }
        
        // Update all widgets' styles
        for (Widget* widget : widgets) {
            widget->updateStyle(style);
        }
    }
    
    
    Style getStyle() const {
        return this->style;
    }
    
    void setBackgroundColor(int r, int g, int b, int a) {
        this->backgroundColor = SkColorSetARGB(a, r, g, b);
    }

    void addWidget(Widget& widget) {
        widgets.push_back(&widget);
        widget.updateStyle(this->style);
    }

   SkCanvas* getSurface() {
        return surface->getCanvas();
    }
    
    void display()  {
        this->setActive(true);
        
        SkCanvas* canvas = this->getSurface();
        canvas->clear(backgroundColor);
        
        for (auto& widget : widgets) {
            widget->draw(canvas);
        }
        
        canvas->flush();
        sf::RenderWindow::display();
    }
    
        int getWidth() const {
        return width;
    }
    
    int getHeight() const {
        return height;
    }

private:
    sk_sp<GrDirectContext> context;
    sk_sp<SkSurface> surface;
    int width;
    int height;
    SkColor backgroundColor;
    std::vector<Widget*> widgets; // Store pointers to widgets
    Style style;
    
    bool initializeSkia() {
        sk_sp<const GrGLInterface> interface = GrGLMakeNativeInterface();
        context = GrDirectContext::MakeGL(interface);
        SkImageInfo imageInfo = SkImageInfo::MakeN32Premul(width, height);
        surface = SkSurface::MakeRenderTarget(context.get(), SkBudgeted::kNo, imageInfo);

        if (!surface) {
            std::cerr << "Failed to create Skia GPU surface\n";
            return false;
        }

        context->flush();
        return true;
    }
};









enum FlexDirection {
    Column, Row, RowReverse, ColumnReverse
};

enum Edge {
    Left, Top, Right, Bottom, Start, End, Horizontal, Vertical, All
};

enum JustifyContent {
    FlexStart, FlexEnd, Center, SpaceBetween, SpaceAround, SpaceEvenly
};

enum AlignItems {
    AlignFlexStart, AlignFlexEnd, AlignCenter, Baseline, Stretch
};


class Layout  : public Object {
public:
    explicit Layout(Window& parent);
       Layout();
    ~Layout();
    void AddChild(Layout& childLayout);
    void SetFlexDirection(FlexDirection direction);
    void SetGap(); // Placeholder for implementation
    void SetWidth(float width);
    void SetHeight(float height);
    void SetPosition(Edge edge, float position);
    void CalculateLayout();
    float GetWidth();
    float GetHeight();
    void SetMargin(Edge edge, float margin);
    void SetPadding(Edge edge, float padding);
    void SetBorder(Edge edge, float border);
    void SetAspectRatio(float aspectRatio);
    void SetFlex(float flex);
    void SetMinWidth(float minWidth);
    void SetMinHeight(float minHeight);
    void SetMaxWidth(float maxWidth);
    void SetMaxHeight(float maxHeight);
    void SetJustifyContent(JustifyContent justifyContent);
    void SetAlignItems(AlignItems alignItems);
    void SetTop(float top);
    void SetLeft(float left);
    void SetRight(float right);
    void SetBottom(float bottom);
    void SetStart(float start);
    void SetEnd(float end);
    void SetHorizontalMargin(float margin);
    void SetVerticalMargin(float margin);
    void SetHorizontalPadding(float padding);
    void SetVerticalPadding(float padding);
    float GetTop();
    float GetLeft();
    void Reset();
    float GetChildWidth(int index);
    float GetChildHeight(int index);
    float GetChildTop(int index);
    float GetChildLeft(int index);

private:
    YGNodeRef node;
};


Layout::Layout(Window& window) {
    node = YGNodeNew();
    YGNodeStyleSetWidth(node, window.getWidth());
    YGNodeStyleSetHeight(node, window.getHeight());
}

Layout::Layout() {
    node = YGNodeNew();
}


Layout::~Layout() {
  YGNodeFreeRecursive(node);
}

void Layout::AddChild(Layout& childLayout) {
    YGNodeInsertChild(node, childLayout.node, YGNodeGetChildCount(node));
    YGNodeCalculateLayout(node, YGUndefined, YGUndefined, YGDirectionLTR);
}

void Layout::SetFlexDirection(FlexDirection direction) {
  switch (direction) {
    case Column:
      YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumn);
      break;
    case Row:
      YGNodeStyleSetFlexDirection(node, YGFlexDirectionRow);
      break;
    case RowReverse:
      YGNodeStyleSetFlexDirection(node, YGFlexDirectionRowReverse);
      break;
    case ColumnReverse:
      YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumnReverse);
      break;
  }
}

void Layout::SetGap() {
  // Function definition
  // You can use 'direction' here to set the flex direction
}

void Layout::SetWidth(float width) {
    YGNodeStyleSetWidth(node, width);
}

void Layout::SetHeight(float height) {
    YGNodeStyleSetHeight(node, height);
}


void Layout::SetPosition(Edge edge, float position) {
    YGEdge ygEdge;
    switch (edge) {
        case Left:
            ygEdge = YGEdgeLeft;
            break;
        case Top:
            ygEdge = YGEdgeTop;
            break;
        case Right:
            ygEdge = YGEdgeRight;
            break;
        case Bottom:
            ygEdge = YGEdgeBottom;
            break;
        case Start:
            ygEdge = YGEdgeStart;
            break;
        case End:
            ygEdge = YGEdgeEnd;
            break;
        case Horizontal:
            ygEdge = YGEdgeHorizontal;
            break;
        case Vertical:
            ygEdge = YGEdgeVertical;
            break;
        case All:
            ygEdge = YGEdgeAll;
            break;
    }
    YGNodeStyleSetPosition(node, ygEdge, position);
}

void Layout::CalculateLayout() {
    YGNodeCalculateLayout(node, YGUndefined, YGUndefined, YGDirectionLTR);
}

float Layout::GetWidth() {
    return YGNodeLayoutGetWidth(node);
}

float Layout::GetHeight() {
    return YGNodeLayoutGetHeight(node);
}

void Layout::SetMargin(Edge edge, float margin) {
    YGEdge ygEdge;
    switch (edge) {
        case Left:
            ygEdge = YGEdgeLeft;
            break;
        case Top:
            ygEdge = YGEdgeTop;
            break;
        case Right:
            ygEdge = YGEdgeRight;
            break;
        case Bottom:
            ygEdge = YGEdgeBottom;
            break;
        case Start:
            ygEdge = YGEdgeStart;
            break;
        case End:
            ygEdge = YGEdgeEnd;
            break;
        case Horizontal:
            ygEdge = YGEdgeHorizontal;
            break;
        case Vertical:
            ygEdge = YGEdgeVertical;
            break;
        case All:
            ygEdge = YGEdgeAll;
            break;
    }
    YGNodeStyleSetMargin(node, ygEdge, margin);
}

void Layout::SetPadding(Edge edge, float padding) {
    YGEdge ygEdge;
    switch (edge) {
        case Left:
            ygEdge = YGEdgeLeft;
            break;
        case Top:
            ygEdge = YGEdgeTop;
            break;
        case Right:
            ygEdge = YGEdgeRight;
            break;
        case Bottom:
            ygEdge = YGEdgeBottom;
            break;
        case Start:
            ygEdge = YGEdgeStart;
            break;
        case End:
            ygEdge = YGEdgeEnd;
            break;
        case Horizontal:
            ygEdge = YGEdgeHorizontal;
            break;
        case Vertical:
            ygEdge = YGEdgeVertical;
            break;
        case All:
            ygEdge = YGEdgeAll;
            break;
    }
    YGNodeStyleSetPadding(node, ygEdge, padding);
}

void Layout::SetBorder(Edge edge, float border) {
    YGEdge ygEdge;
    switch (edge) {
        case Left:
            ygEdge = YGEdgeLeft;
            break;
        case Top:
            ygEdge = YGEdgeTop;
            break;
        case Right:
            ygEdge = YGEdgeRight;
            break;
        case Bottom:
            ygEdge = YGEdgeBottom;
            break;
        case Start:
            ygEdge = YGEdgeStart;
            break;
        case End:
            ygEdge = YGEdgeEnd;
            break;
        case Horizontal:
            ygEdge = YGEdgeHorizontal;
            break;
        case Vertical:
            ygEdge = YGEdgeVertical;
            break;
        case All:
            ygEdge = YGEdgeAll;
            break;
    }
    YGNodeStyleSetBorder(node, ygEdge, border);
}

void Layout::SetAspectRatio(float aspectRatio) {
    YGNodeStyleSetAspectRatio(node, aspectRatio);
}

void Layout::SetFlex(float flex) {
    YGNodeStyleSetFlex(node, flex);
}

void Layout::SetMinWidth(float minWidth) {
    YGNodeStyleSetMinWidth(node, minWidth);
}

void Layout::SetMinHeight(float minHeight) {
    YGNodeStyleSetMinHeight(node, minHeight);
}

void Layout::SetMaxWidth(float maxWidth) {
    YGNodeStyleSetMaxWidth(node, maxWidth);
}

void Layout::SetMaxHeight(float maxHeight) {
    YGNodeStyleSetMaxHeight(node, maxHeight);
}

void Layout::SetJustifyContent(JustifyContent justifyContent) {
    YGNodeStyleSetJustifyContent(node, static_cast<YGJustify>(justifyContent));
}

void Layout::SetAlignItems(AlignItems alignItems) {
    YGNodeStyleSetAlignItems(node, static_cast<YGAlign>(alignItems));
}

void Layout::SetTop(float top) {
    YGNodeStyleSetPosition(node, YGEdgeTop, top);
}

void Layout::SetLeft(float left) {
    YGNodeStyleSetPosition(node, YGEdgeLeft, left);
}

void Layout::SetRight(float right) {
    YGNodeStyleSetPosition(node, YGEdgeRight, right);
}

void Layout::SetBottom(float bottom) {
    YGNodeStyleSetPosition(node, YGEdgeBottom, bottom);
}

void Layout::SetStart(float start) {
    YGNodeStyleSetPosition(node, YGEdgeStart, start);
}

void Layout::SetEnd(float end) {
    YGNodeStyleSetPosition(node, YGEdgeEnd, end);
}

void Layout::SetHorizontalMargin(float margin) {
    YGNodeStyleSetMargin(node, YGEdgeHorizontal, margin);
}

void Layout::SetVerticalMargin(float margin) {
    YGNodeStyleSetMargin(node, YGEdgeVertical, margin);
}

void Layout::SetHorizontalPadding(float padding) {
    YGNodeStyleSetPadding(node, YGEdgeHorizontal, padding);
}

void Layout::SetVerticalPadding(float padding) {
    YGNodeStyleSetPadding(node, YGEdgeVertical, padding);
}

float Layout::GetTop() {
    return YGNodeLayoutGetTop(node);
}

float Layout::GetLeft() {
    return YGNodeLayoutGetLeft(node);
}

void Layout::Reset() {
  YGNodeReset(node);
}

float Layout::GetChildWidth(int index) {
    return YGNodeLayoutGetWidth(YGNodeGetChild(node, index));
}

float Layout::GetChildHeight(int index) {
    return YGNodeLayoutGetHeight(YGNodeGetChild(node, index));
}

float Layout::GetChildTop(int index) {
    return YGNodeLayoutGetTop(YGNodeGetChild(node, index));
}

float Layout::GetChildLeft(int index) {
    return YGNodeLayoutGetLeft(YGNodeGetChild(node, index));
}











class PushButton : public Widget {
public:
    PushButton(int x, int y, int width, int height, const std::string& label)
        : Widget(x, y, width, height), 
        _label(label), 
        _hover(false), 
        _clicked(false) {}


    void updateStyle(Style style) override {
        if (style == Style::Dark) {
            normalColor = BUTTON_NORMAL_COLOR_DARK;
            hoverColor = BUTTON_HOVER_COLOR_DARK;
            clickedColor = BUTTON_CLICKED_COLOR_DARK;
            textColor = WINDOW_FG_COLOR_DARK;
        } else {
            normalColor = BUTTON_NORMAL_COLOR_LIGHT;
            hoverColor = BUTTON_HOVER_COLOR_LIGHT;
            clickedColor = BUTTON_CLICKED_COLOR_LIGHT;
            textColor = WINDOW_FG_COLOR_LIGHT;
        }
    }

    void draw(SkCanvas* canvas) override {
        SkPaint paint;
        paint.setAntiAlias(true);

        if (_clicked) {
            paint.setColor(clickedColor);
        } else if (_hover) {
            paint.setColor(hoverColor);
        } else {
            paint.setColor(normalColor);
        }

        SkRRect roundedRect;
        roundedRect.setRectXY(_bounds, BUTTON_CORNER_RADIUS, BUTTON_CORNER_RADIUS);
        canvas->drawRRect(roundedRect, paint);

        SkPaint textPaint;
        textPaint.setColor(textColor);
        auto text = SkTextBlob::MakeFromString(_label.c_str(), SkFont(nullptr, 18));
        canvas->drawTextBlob(text.get(), _bounds.centerX(), _bounds.centerY(), textPaint);
    }

    void handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::MouseMoved) {
            int mouseX = event.mouseMove.x;
            int mouseY = event.mouseMove.y;
            _hover = _bounds.contains(mouseX, mouseY);
        } else if (event.type == sf::Event::MouseButtonPressed && _hover) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                _clicked = true;
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (_clicked && _hover && event.mouseButton.button == sf::Mouse::Left) {
                _clicked = false;
                emitSignal("clicked", std::any());  // Emitting the clicked signal
            }
        }
    }

private:
    std::string _label;
    bool _hover;
    bool _clicked;
    SkColor normalColor, hoverColor, clickedColor, textColor;
};

}




int main() {


    Ht::Window* window = new Ht::Window("Title", 1024, 600);

    // Create the main layout
    
    Ht::Layout mainLayout(*window); 
    mainLayout.SetFlexDirection(Ht::Column);
    mainLayout.SetPadding(Ht::Edge::All, 50);


    // Create first child layout
    Ht::Layout childLayout1;
    //childLayout1.SetWidth(200);
    childLayout1.SetHeight(50);
    //childLayout1.SetFlex(0);
    childLayout1.SetMargin(Ht::Edge::All, 5);
    
    // Create second child layout
    Ht::Layout childLayout2;
    //childLayout2.SetWidth(300);
    childLayout2.SetHeight(50);
    childLayout2.SetFlex(1);
    childLayout2.SetMargin(Ht::Edge::All, 5);

    // Add children to main layout
    mainLayout.AddChild(childLayout1);
    mainLayout.AddChild(childLayout2);
    

         
     Ht::PushButton myButton(mainLayout.GetChildLeft(0), mainLayout.GetChildTop(0), 
     mainLayout.GetChildWidth(0), mainLayout.GetChildHeight(0), "Click Me!");
    window->addWidget(myButton);
        
     Ht::PushButton myButton2(mainLayout.GetChildLeft(1), mainLayout.GetChildTop(1), 
     mainLayout.GetChildWidth(1), mainLayout.GetChildHeight(1), "Click Me!");
    window->addWidget(myButton2);
    
    
    
    myButton.connect("clicked", [&window](std::any data) {
        window->setStyle(Ht::Style::Dark);
        std::cout << "Button1 was clicked!" << std::endl;
    });

    myButton2.connect("clicked", [&window](std::any data) {
        window->setStyle(Ht::Style::Light);
        std::cout << "Button2 was clicked!" << std::endl;
    });
 



    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));
                //mainLayout->handleResize(event.size.width, event.size.height);
            }

            myButton.handleEvent(event);
            myButton2.handleEvent(event);
        }

        window->display();

    }

    return 0;
}
