#pragma once

#include "HSize.h"
#include "HCursor.h"
#include "HString.h"
#include "HRect.h"
#include "HMargins.h"

namespace Ht {

enum class ScreenOrientation {
    PortraitOrientation,
    LandscapeOrientation
};

enum class WindowFlags {
    Window,
    Dialog
};

class HWindow {
public:
    HWindow();

    HSize baseSize() const;
    ScreenOrientation contentOrientation() const;
    HCursor cursor() const;
    HString filePath() const;
    WindowFlags flags() const;
    HRect frameGeometry() const;
    HMargins frameMargins() const;
    bool isTopLevel() const;
    HSize maximumSize() const;
    HSize minimumSize() const;
    int maximumHeight() const;
    double opacity() const;
    void setOpacity(double opacity);
    HString title() const;
    void setTitle(const HString& title);

private:
    double opacity_;
    HString title_;
};

} // namespace Ht

