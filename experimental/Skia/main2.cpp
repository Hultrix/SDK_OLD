#define SK_GL

// Compile command:
// This project uses the Skia graphics library along with SFML, EGL, and other libraries. 
// Compilation requires linking against these libraries as specified below.
// g++ -o test test.cpp -I/usr/include/skia -lskia -lsfml-graphics -lsfml-window -lsfml-system  -lyogacore -lEGL -lGLESv2 

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>

#include <SFML/Graphics.hpp>
#include <memory>
#include <yoga/Yoga.h>
#include <cmath>  // Include for mathematical functions like sin and cos
#include <iostream>

#include <skia/include/gpu/GrDirectContext.h>
#include <skia/include/gpu/gl/GrGLInterface.h>
#include <skia/include/core/SkSurface.h>
#include <skia/include/core/SkCanvas.h>
#include <skia/include/core/SkPath.h>
#include <skia/include/core/SkPaint.h>
#include <skia/include/core/SkRect.h>
#include <skia/include/core/SkRRect.h>

// Function to create and return an SkRRect representing a rounded rectangle
SkRRect createRoundedRectangle(float x, float y, float width, float height,
                               float radiusTopLeft, float radiusTopRight,
                               float radiusBottomRight, float radiusBottomLeft) {
    // Define the rectangle from specified position and size
    SkRect rect = SkRect::MakeXYWH(x, y, width, height);

    // Define radii for each corner of the rectangle
    SkVector radii[4];
    radii[SkRRect::kUpperLeft_Corner] = SkVector::Make(radiusTopLeft, radiusTopLeft);
    radii[SkRRect::kUpperRight_Corner] = SkVector::Make(radiusTopRight, radiusTopRight);
    radii[SkRRect::kLowerRight_Corner] = SkVector::Make(radiusBottomRight, radiusBottomRight);
    radii[SkRRect::kLowerLeft_Corner] = SkVector::Make(radiusBottomLeft, radiusBottomLeft);

    // Create and return the rounded rectangle with individual corner radii
    SkRRect roundedRect;
    roundedRect.setRectRadii(rect, radii);

    return roundedRect;
}

int main() {
    // Initialize an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hydra v0.0.1");

    // Setup Skia OpenGL context
    sk_sp<const GrGLInterface> interface = GrGLMakeNativeInterface();
    sk_sp<GrDirectContext> context = GrDirectContext::MakeGL(interface);

    // Define the image properties and create a Skia GPU surface
    SkImageInfo imageinfo = SkImageInfo::MakeN32Premul(800, 600);
    sk_sp<SkSurface> surface = SkSurface::MakeRenderTarget(context.get(), SkBudgeted::kNo, imageinfo);

    // Ensure the GPU surface was created successfully
    if (!surface) {
        std::cerr << "Failed to create Skia GPU surface\n";
        return -1;
    }

    // Prepare the Skia drawing context
    context->flush();

    // Retrieve the canvas from the Skia surface
    SkCanvas* canvas = surface->getCanvas();

    // Activate SFML window context
    window.setActive(true);

    // Set up Yoga layout for UI elements
    YGNodeRef container = YGNodeNew();
    YGNodeStyleSetWidth(container, 800);
    YGNodeStyleSetHeight(container, 100);
    YGNodeStyleSetFlexDirection(container, YGFlexDirectionRow);
    YGNodeStyleSetPadding(container, YGEdgeAll, 20);

    // Create and configure child nodes for layout
    YGNodeRef child = YGNodeNew();
    YGNodeStyleSetFlexGrow(child, 1);  // Allow the child to grow and fill the container
    YGNodeStyleSetMargin(child, YGEdgeAll, 5);
    YGNodeInsertChild(container, child, 0);

    YGNodeRef child1 = YGNodeNew();
    YGNodeStyleSetFlexGrow(child1, 1);
    YGNodeStyleSetMargin(child1, YGEdgeAll, 5);
    YGNodeInsertChild(container, child1, 1);

    // Compute the layout for all children
    YGNodeCalculateLayout(container, YGUndefined, YGUndefined, YGDirectionLTR);

    // Main application loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle window resizing
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        // Clear window with a specific color
        window.clear(sf::Color(23, 23, 23));

        // Start drawing operations
        canvas->clear(SkColorSetARGB(255, 255, 255, 0));  // Clear with yellow color, full opacity

        // Draw rounded and regular rectangles based on Yoga layout
        SkRRect rect = createRoundedRectangle(YGNodeLayoutGetLeft(child), YGNodeLayoutGetTop(child), YGNodeLayoutGetWidth(child), YGNodeLayoutGetHeight(child), 0, 20, 0, 20);
        SkPaint paint;
        paint.setAntiAlias(true);  // Enable anti-aliasing for smoother edges
        paint.setColor(SK_ColorBLUE);
        canvas->drawRRect(rect, paint);

        SkRect rect1 = SkRect::MakeXYWH(YGNodeLayoutGetLeft(child1), YGNodeLayoutGetTop(child1), YGNodeLayoutGetWidth(child1), YGNodeLayoutGetHeight(child1));
        SkPaint paint1;
        paint1.setAntiAlias(true);
        paint1.setColor(SK_ColorRED);
        canvas->drawRect(rect1, paint1);
        
        // Finish drawing and update the canvas
        canvas->flush();

        // Display the updated window
        window.display();
    }

    // Cleanup
    delete canvas;

    return 0;
}
