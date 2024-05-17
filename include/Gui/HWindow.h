#pragma once

#include "HObject.h"
#include "HSize.h"
#include "HCursor.h"
#include "HString.h"
#include "HRect.h"
#include "HMargins.h"

namespace Ht {


class HWindow : public HObject {
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
    void setMaximumSize(const HSize& size);
    int maximumHeight() const;
    double opacity() const;
    void setOpacity(double opacity);
    HString title() const;
    void setTitle(const HString& title);

private:
    HSize baseSize_;
    ScreenOrientation contentOrientation_;
    HCursor cursor_;
    HString filePath_;
    WindowFlags flags_;
    HRect frameGeometry_;
    HMargins frameMargins_;
    bool isTopLevel_;
    HSize maximumSize_;
    HSize minimumSize_;
    double opacity_;
    HString title_;
};

}

