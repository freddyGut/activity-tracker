
#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <wx/wx.h>
#include <wx/event.h>
#include <wx/msw/button.h>
#include <wx/listctrl.h>
#include <wx/calctrl.h> // events and costructors for calendars


#include "MainView.h"
#include "Register.h"

class MainController {
public:
    MainController(MainView* view, Register* model);

    void Init();

private:
    MainView* view;
    Register* model;

    void OnDateChanged(wxCalendarEvent& event);
    void OnAddActivity(wxCommandEvent& event);
    void OnRemoveActivity(wxCommandEvent& event);
    void OnSearchActivity(wxCommandEvent& event);

    void BindEvents();
    void UpdateActivityList(const wxDateTime& date);
    void UpdateTotalActivitiesText(int total);
};



#endif //MAINCONTROLLER_H
