#include "HWindow.h"

namespace Ht {

HWindow::HWindow() : opacity_(1.0), title_("Untitled") {}

HSize HWindow::baseSize() const {
    return HSize(800, 600);
}

ScreenOrientation HWindow::contentOrientation() const {
    return ScreenOrientation::PortraitOrientation;
}

HCursor HWindow::cursor() const {
    return HCursor(HCursorShape::Arrow);
}

HString HWindow::filePath() const {
    return HString("C:/path/to/window");
}

WindowFlags HWindow::flags() const {
    return WindowFlags::Window;
}

HRect HWindow::frameGeometry() const {
    return HRect(100, 100, 800, 600);
}

HMargins HWindow::frameMargins() const {
    return HMargins(10, 10, 10, 10);
}

bool HWindow::isTopLevel() const {
    return true;
}

HSize HWindow::maximumSize() const {
    return HSize(1920, 1080);
}

HSize HWindow::minimumSize() const {
    return HSize(200, 150);
}

int HWindow::maximumHeight() const {
    return 1080;
}

double HWindow::opacity() const {
    return opacity_;
}

void HWindow::setOpacity(double opacity) {
    opacity_ = opacity;
}

HString HWindow::title() const {
    return title_;
}

void HWindow::setTitle(const HString& title) {
    title_ = title;
}

} // namespace Ht

