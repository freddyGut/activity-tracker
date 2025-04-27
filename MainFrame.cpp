#include <wx/wx.h>
#include <wx/event.h>
#include <wx/msw/button.h>
#include <wx/msw/panel.h>

#include "MainFrame.h"

#include <wx/generic/textdlgg.h>


// === EVENT TABLE ===
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CALENDAR_SEL_CHANGED(ID_Calendar, OnDateChanged)
    EVT_BUTTON(ID_AddActivity, OnAddActivity)
    EVT_BUTTON(ID_RemoveActivity, OnRemoveActivity)
wxEND_EVENT_TABLE()

// === Constructor ===
MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400))
{
    wxPanel* panel = new wxPanel(this);

    // Initializing calendar
    calendar = new wxCalendarCtrl(panel, ID_Calendar, wxDefaultDateTime,
                                    wxPoint(20, 20), wxDefaultSize);

    // Initializing list of activities
    activityList = new wxListBox(panel, wxID_ANY, wxPoint(300, 20), wxSize(250, 250));

    // Initializing buttons
    addActivityButton = new wxButton(panel, ID_AddActivity, "Add Activity", wxPoint(300, 300));
    removeActivityButton = new wxButton(panel, ID_RemoveActivity, "Remove Activity", wxPoint(450, 300));
}


// === EVENT HANDLERS ===
void MainFrame::OnDateChanged(wxCalendarEvent& event)
{
    UpdateActivityListForSelectedDate();
}

void MainFrame::OnAddActivity(wxCommandEvent& event)
{
    wxString newActivity = wxGetTextFromUser("Describe activity:", "New activity");
    if (!newActivity.IsEmpty())
    {
        activityList->Append(newActivity);
        // We will save data to database
    }
}

void MainFrame::OnRemoveActivity(wxCommandEvent& event)
{
    int selection = activityList->GetSelection();
    if (selection != wxNOT_FOUND)
    {
        activityList->Delete(selection);
    }
}

// === HELPER ===
void MainFrame::UpdateActivityListForSelectedDate()
{
    //for now, we are just clearing the list: in the future, we will fetch data from database
    activityList->Clear();
}