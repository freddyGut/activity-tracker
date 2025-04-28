#include <wx/wx.h>
#include <wx/event.h>
#include <wx/msw/button.h>

#include "MainFrame.h"
#include "Register.h"

#include <wx/generic/textdlgg.h>

#include "AddActivityDialog.h"


// === Constructor ===
MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400))
{
    // Creating the widgets
    calendar = new wxCalendarCtrl(this, ID_Calendar, wxDefaultDateTime, wxPoint(20, 20), wxDefaultSize);
    activityList = new wxListBox(this, wxID_ANY, wxPoint(300, 20), wxSize(250, 250));
    addActivityButton = new wxButton(this, ID_AddActivity, "Add Activity", wxPoint(300, 300));
    removeActivityButton = new wxButton(this, ID_RemoveActivity, "Remove Activity", wxPoint(450, 300));

    // Binding widgets to their handlers
    calendar->Bind(wxEVT_CALENDAR_SEL_CHANGED, &MainFrame::OnDateChanged, this);
    addActivityButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddActivity, this);
    removeActivityButton->Bind(wxEVT_BUTTON, &MainFrame::OnRemoveActivity, this);

    // Creating sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(addActivityButton, 0, wxALL, 5);
    buttonSizer->Add(removeActivityButton, 0, wxALL, 5);

    // Populating sizer
    mainSizer->Add(calendar, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(activityList, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    SetSizerAndFit(mainSizer);
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
        wxLogError("Start time: %d:%d", startHour, startMinute);

        // Creating the new activity
        Activity activity(description.ToStdString(), startTime, endTime);

        // Saving the activity in the register
        wxLogError("Saving activity to register...");
        _register.AddActivity(date, activity);


        // Updating visible list
        UpdateActivityList(date);


    }

    dialog->Destroy();

}

void MainFrame::OnRemoveActivity(wxCommandEvent& event)
{
    int activityIndex = activityList->GetSelection();
    if (activityIndex == wxNOT_FOUND)
    {
        wxMessageBox("Please select an activity to remove!", "Error", wxOK | wxICON_ERROR);
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
    activityList->Clear();

    std::vector<Activity> activities = _register.GetActivitiesPerDate(selectedDate);

    for (const auto& activity : activities)
    {
        std::string line = activity.getFormattedStartTime() + " - " + activity.getFormattedEndTime() + " " + activity.getDescription();
        activityList->Append(line);
    }
}


