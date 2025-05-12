#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/event.h>
#include <wx/listctrl.h>
#include <wx/msw/button.h>
#include <wx/msw/frame.h>
#include <wx/msw/listbox.h>
#include <wx/calctrl.h> // Base class wxCalendarCtrlBase
#include <wx/generic/calctrlg.h> // wxGenericCalendarCtrl


#include "Activity.h"

class MainView : public wxFrame {
public:
    // c-tor
    explicit MainView(const wxString &title);

    wxGenericCalendarCtrl *GetCalendar() const;

    wxListCtrl *GetActivityList() const;

    wxButton *GetAddActivityButton() const;

    wxButton *GetRemoveActivityButton() const;

    wxStaticText *GetTotalActivitiesText() const;

    wxTextCtrl *GetSearchBox() const;

    wxButton *GetSearchButton() const;

private:
    wxGenericCalendarCtrl *calendar; // Calendar to select the days
    wxListCtrl *activityList; // List of activities in the selected date
    wxButton *addActivityButton; // Button to add a new activity
    wxButton *removeActivityButton; // Button to remove an activity
    wxStaticText *totalActivitiesText; // Stores the total number of activities
    wxTextCtrl *searchBox; // Search by description
    wxButton *searchButton;


    // === ID ===
    enum {
        ID_Calendar = wxID_HIGHEST + 1,
        ID_AddActivity,
        ID_RemoveActivity,
        ID_SearchActivity
    };
};


#endif //MAINFRAME_H
