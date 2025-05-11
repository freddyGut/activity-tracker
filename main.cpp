#include <wx/wx.h>

#include "MainView.h"
#include "Register.h"
#include "MainController.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};


bool MyApp::OnInit() {

    auto* model = new Register();
    auto* view = new MainView("ACTIVITY TRACKER");
    auto* controller = new MainController(view, model);
    controller->Init();
    view->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);

