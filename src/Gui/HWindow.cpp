#include "HWindow.h"

namespace Ht {

HWindow::HWindow()
    : HObject(nullptr), 
      baseSize_(800, 600),
      contentOrientation_(ScreenOrientation::PortraitOrientation),
      cursor_(HCursorShape::Arrow),
      filePath_(""),
      flags_(WindowFlags::Window),
      frameGeometry_(100, 100, 800, 600),
      frameMargins_(10, 10, 10, 10),
      isTopLevel_(true),
      maximumSize_(/* default max size */),
      minimumSize_(/* default min size */),
      opacity_(1.0),
      title_("") {}

HSize HWindow::baseSize() const {
    return baseSize_;
}

ScreenOrientation HWindow::contentOrientation() const {
    return contentOrientation_;
}

HCursor HWindow::cursor() const {
    return cursor_;
}

HString HWindow::filePath() const {
    return filePath_;
}

WindowFlags HWindow::flags() const {
    return flags_;
}

HRect HWindow::frameGeometry() const {
    return frameGeometry_;
}

HMargins HWindow::frameMargins() const {
    return frameMargins_;
}

bool HWindow::isTopLevel() const {
    return isTopLevel_;
}

HSize HWindow::maximumSize() const {
    return maximumSize_;
}

HSize HWindow::minimumSize() const {
    return minimumSize_;
}

int HWindow::maximumHeight() const {
    return maximumSize_.height(); 
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

void HWindow::setMaximumSize(const HSize& size) {
  maximumSize_ = size;
}

} // namespace Ht

