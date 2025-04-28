
#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/event.h>
#include <wx/string.h>
#include <wx/msw/button.h>
#include <wx/msw/frame.h>
#include <wx/msw/listbox.h>
#include <wx/calctrl.h>

#include "Activity.h"
#include "Register.h"

class MainFrame : public wxFrame {

public:
    // c-tor
    explicit MainFrame(const wxString& title);


private:

    Register _register;

    // === GRAPHICAL COMPONENTS ===
    wxCalendarCtrl* calendar;      // Calendar to select the days
    wxListBox* activityList;        // List of activities in the selected date
    wxButton* addActivityButton;    // Button to add a new activity
    wxButton* removeActivityButton; // Button to remove an activity

    // === EVENT HANDLERS ===
    void OnDateChanged(wxCalendarEvent& event);
    void OnAddActivity(wxCommandEvent& event);
    void OnRemoveActivity(wxCommandEvent& event);


    // === HELPER ===
    void UpdateActivityList(const wxDateTime& selectedDate);


    // === ID ===
    enum
    {
        ID_Calendar = wxID_HIGHEST + 1,
        ID_AddActivity,
        ID_RemoveActivity
    };

};



#endif //MAINFRAME_H
