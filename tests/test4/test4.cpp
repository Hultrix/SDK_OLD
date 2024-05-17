#include <iostream>
#include <string>
#include "HWindow.h"
#include "HCursor.h"
#include "HString.h"
#include "HSize.h"
#include "HRect.h"

int main()
{
    // Create an HWindow object with default size
    Ht::HWindow myWindow;

    // Retrieve and display the base size of the window
    Ht::HSize size = myWindow.baseSize();
    std::cout << "Window base size is " << size.width() << "x" << size.height() << std::endl;

    Ht::ScreenOrientation orientation = myWindow.contentOrientation();

    if (orientation == Ht::ScreenOrientation::PortraitOrientation)
    {
        std::cout << "The orientation is Portrait." << std::endl;
    }

    // Retrieve the cursor from the window
    Ht::HCursor cursor = myWindow.cursor();

    if (cursor.shape() == Ht::HCursorShape::Arrow)
    {
        std::cout << "The cursor shape is Arrow." << std::endl;
    }

    Ht::HString path = myWindow.filePath();
    std::cout << "Window file path: " << path << std::endl;

    Ht::WindowFlags flags = myWindow.flags();
    if (flags == Ht::WindowFlags::Window)
    {
        std::cout << "The flag is Window." << std::endl;
    }

    // Get the frame geometry of the window
    Ht::HRect frame = myWindow.frameGeometry();

    // Print the frame geometry
    std::cout << "Frame Geometry: x=" << frame.x() << ", y=" << frame.y()
              << ", width=" << frame.width() << ", height=" << frame.height() << std::endl;

    // Get the frame geometry of the window
    Ht::HMargins margins = myWindow.frameMargins();

    // Print the frame geometry
    std::cout << "Frame Margins: top=" << margins.top() << ", right=" << margins.right()
              << ", bottom=" << margins.bottom() << ", left=" << margins.left() << std::endl;

    if (myWindow.isTopLevel())
    {
        std::cout << "Window is toplevel = true " << std::endl;
    }

    myWindow.setMaximumSize(Ht::HSize(800, 600));
    Ht::HSize maxsize = myWindow.maximumSize();
    std::cout << "Window maximumSize width is " << maxsize.width() << " height " << maxsize.height() << std::endl;

    Ht::HSize minsize = myWindow.minimumSize();
    std::cout << "Window minimumSize width is " << minsize.width() << " height " << minsize.height() << std::endl;

    int mh = myWindow.maximumHeight();
    std::cout << "Window maximumHeight is " << mh << std::endl;

    std::cout << "Window opacity is " << myWindow.opacity() << std::endl;

    myWindow.setOpacity(0.5);
    std::cout << "Window opacity is " << myWindow.opacity() << std::endl;

    std::cout << "Window title is " << myWindow.title() << std::endl;

    Ht::HString title = "My Window";
    myWindow.setTitle(title);

    std::cout << "Window title is " << myWindow.title() << std::endl;

    return 0;
}
