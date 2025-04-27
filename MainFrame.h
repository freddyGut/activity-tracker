
#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/event.h>
#include <wx/string.h>
#include <wx/msw/button.h>
#include <wx/msw/frame.h>
#include <wx/msw/listbox.h>
#include <wx/calctrl.h>


class MainFrame : public wxFrame {

public:
    // c-tor
    explicit MainFrame(const wxString& title);


private:
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
    void UpdateActivityListForSelectedDate();


    // === ID ===
    enum
    {
        ID_Calendar = wxID_HIGHEST + 1,
        ID_AddActivity,
        ID_RemoveActivity
    };

    // tells the compiler: "Look, this class is going to use an event table to map IDs to C++ functions"
    wxDECLARE_EVENT_TABLE();

};



#endif //MAINFRAME_H
