#include <wx/wx.h>

#include "MainFrame.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};


bool MyApp::OnInit() {

    auto* mainFrame = new MainFrame("Activity Tracker");
    mainFrame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);

