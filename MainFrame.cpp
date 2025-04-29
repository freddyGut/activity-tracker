#include <wx/wx.h>
#include <wx/event.h>
#include <wx/msw/button.h>
#include <wx/listctrl.h>
#include <wx/calctrl.h> // events and costructors for calendars


#include "MainFrame.h"
#include "Register.h"

#include <wx/generic/textdlgg.h>

#include "AddActivityDialog.h"


// === Constructor ===
MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title, wxPoint(200,200), wxSize(8000, 600))
{
    SetBackgroundColour(wxColour(0, 116, 166));

    // Main sizer: HORIZONTAL
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Bigger calendar
    calendar = new wxGenericCalendarCtrl(this, ID_Calendar, wxDefaultDateTime, wxDefaultPosition, wxSize(300, 400));
    wxFont calendarFont(14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Rockwell");
    calendar->SetFont(calendarFont);
    calendar->SetHeaderColours(*wxWHITE, wxColour(0, 65, 112));        // Header text
    calendar->SetHighlightColours(*wxWHITE, *wxRED);      // Selected day
    calendar->SetHolidayColours(*wxBLUE, *wxWHITE);      // Festivity

    // Right sizer: VERTICAL (activities + buttons)
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    activityList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(350, 400), wxLC_REPORT | wxBORDER_SUNKEN);
    wxFont listFont(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Rockwell");
    activityList->SetFont(listFont);

    activityList->InsertColumn(0, "Time", wxLIST_FORMAT_LEFT, 120);
    activityList->InsertColumn(1, "Description",wxLIST_FORMAT_LEFT, 230);

    // Buttons
    addActivityButton = new wxButton(this, ID_AddActivity, "Add Activity");
    addActivityButton->SetBackgroundColour(wxColour(0, 65, 112));
    addActivityButton->SetForegroundColour(*wxWHITE);
    addActivityButton->SetFont(listFont);

    removeActivityButton = new wxButton(this, ID_RemoveActivity, "Remove Activity");
    removeActivityButton->SetBackgroundColour(wxColour(208, 8, 37));
    removeActivityButton->SetForegroundColour(*wxWHITE);
    removeActivityButton->SetFont(listFont);


    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(addActivityButton, 0, wxALL, 5);
    buttonSizer->Add(removeActivityButton, 0, wxALL, 5);

    // Building the right size
    rightSizer->Add(activityList, 0, wxEXPAND | wxALL, 5);
    rightSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    // Putting the calendar on the left and rightSizer on the right
    mainSizer->Add(calendar, 1, wxALL, 10);
    mainSizer->Add(rightSizer, 1, wxEXPAND | wxALL, 10);

    SetSizerAndFit(mainSizer);

    // Binding
    calendar->Bind(wxEVT_CALENDAR_SEL_CHANGED, &MainFrame::OnDateChanged, this);
    addActivityButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddActivity, this);
    removeActivityButton->Bind(wxEVT_BUTTON, &MainFrame::OnRemoveActivity, this);

    _register = Register();
    UpdateActivityList(calendar->GetDate());

}









// === EVENT HANDLERS === OK
void MainFrame::OnDateChanged(wxCalendarEvent& event)
{
    wxDateTime selectedDate = event.GetDate();
    UpdateActivityList(selectedDate);
}

void MainFrame::OnAddActivity(wxCommandEvent& event)
{
    AddActivityDialog* dialog = new AddActivityDialog(this);


    // the users presses OK
    if (dialog->ShowModal() == wxID_OK) {
        wxString description = dialog->GetDescription();
        if (description.IsEmpty()) {
            wxLogError("Description cannot be empty");
            return;
        }
        int startHour = dialog->GetStartHour();
        int startMinute = dialog->GetStartMinute();
        int endHour = dialog->GetEndHour();
        int endMinute = dialog->GetEndMinute();

        if (startHour > endHour || (startHour == endHour && startMinute >= endMinute)) {
            wxLogError("Start time must be before end time");
            return;
        }

        // building DateTime object
        wxDateTime date = calendar->GetDate();
        if (!date.IsValid()) {
            wxLogError("Invalid date selected.");
            return;
        }

        wxDateTime startTime(date.GetDay(), date.GetMonth(), date.GetYear(), startHour, startMinute);
        wxDateTime endTime(date.GetDay(), date.GetMonth(), date.GetYear(), endHour, endMinute);

        // Creating the new activity
        Activity activity(description.ToStdString(), startTime, endTime);

        // Saving the activity in the register
        _register.AddActivity(date, activity);


        // Updating visible list
        UpdateActivityList(date);


    }

    dialog->Destroy();

}

void MainFrame::OnRemoveActivity(wxCommandEvent& event)
{
    int activityIndex = activityList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (activityIndex == -1)
    {
        wxMessageBox("No activity selected!", "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxDateTime date = calendar->GetDate();
    std::vector<Activity> activities = _register.GetActivitiesPerDate(date);

    if (activityIndex < 0 || activityIndex >= static_cast<int>(activities.size()))
    {
        wxMessageBox("Invalid activity selected!", "Error", wxOK | wxICON_ERROR);
        return;
    }

    Activity selectedActivity = activities[activityIndex];
    _register.RemoveActivity(date, selectedActivity);

    UpdateActivityList(date);
}







// === HELPER === OK
void MainFrame::UpdateActivityList(const wxDateTime& selectedDate)
{
    activityList->DeleteAllItems();

    std::vector<Activity> activities = _register.GetActivitiesPerDate(selectedDate);

    int index = 0;
    for (const auto& activity : activities)
    {
        wxString time = activity.getFormattedStartTime() + " - " + activity.getFormattedEndTime();
        wxString description = activity.getDescription();

        index = activityList->InsertItem(index, time);
        activityList->SetItem(index, 1, description);

        //alternating colors
        wxColour rowColor = (index % 2 == 0) ? wxColour(245, 245, 245) : wxColour(230, 230, 255);
        activityList->SetItemBackgroundColour(index, rowColor);

        ++index;
    }
}


