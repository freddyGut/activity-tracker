
#include "MainController.h"

#include "AddActivityDialog.h"

MainController::MainController(MainView* view, Register* model)
    : view(view), model(model) {}


void MainController::Init() {
    BindEvents();
    wxDateTime selectedDate = view->GetCalendar()->GetDate();
    UpdateActivityList(selectedDate);
}


void MainController::BindEvents() {
    view->GetCalendar()->Bind(wxEVT_CALENDAR_SEL_CHANGED, &MainController::OnDateChanged, this);
    view->GetAddActivityButton()->Bind(wxEVT_BUTTON, &MainController::OnAddActivity, this);
    view->GetRemoveActivityButton()->Bind(wxEVT_BUTTON, &MainController::OnRemoveActivity, this);
}


void MainController::OnDateChanged(wxCalendarEvent& event)
{
    wxDateTime selectedDate = event.GetDate();
    UpdateActivityList(selectedDate);
}


void MainController::OnAddActivity(wxCommandEvent& event)
{
    AddActivityDialog* dialog = new AddActivityDialog(view);


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
        wxDateTime date = view->GetCalendar()->GetDate();
        if (!date.IsValid()) {
            wxLogError("Invalid date selected.");
            return;
        }

        wxDateTime startTime(date.GetDay(), date.GetMonth(), date.GetYear(), startHour, startMinute);
        wxDateTime endTime(date.GetDay(), date.GetMonth(), date.GetYear(), endHour, endMinute);

        // Creating the new activity
        Activity activity(description.ToStdString(), startTime, endTime);

        // Saving the activity in the register
        model->AddActivity(date, activity);


        // Updating visible list
        UpdateActivityList(date);


    }

    dialog->Destroy();

}



void MainController::OnRemoveActivity(wxCommandEvent& event)
{
    int activityIndex = view->GetActivityList()->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (activityIndex == -1)
    {
        wxMessageBox("No activity selected!", "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxDateTime date = view->GetCalendar()->GetDate();
    std::vector<Activity> activities = model->GetActivitiesPerDate(date);

    if (activityIndex < 0 || activityIndex >= static_cast<int>(activities.size()))
    {
        wxMessageBox("Invalid activity selected!", "Error", wxOK | wxICON_ERROR);
        return;
    }

    Activity selectedActivity = activities[activityIndex];
    model->RemoveActivity(date, selectedActivity);

    UpdateActivityList(date);
}


// === HELPER === OK
void MainController::UpdateActivityList(const wxDateTime& selectedDate)
{
    view->GetActivityList()->DeleteAllItems();

    std::vector<Activity> activities = model->GetActivitiesPerDate(selectedDate);

    int index = 0;
    for (const auto& activity : activities)
    {
        wxString time = activity.getFormattedStartTime() + " - " + activity.getFormattedEndTime();
        wxString description = activity.getDescription();

        index = view->GetActivityList()->InsertItem(index, time);
        view->GetActivityList()->SetItem(index, 1, description);

        //alternating colors
        wxColour rowColor = (index % 2 == 0) ? wxColour(245, 245, 245) : wxColour(230, 230, 255);
        view->GetActivityList()->SetItemBackgroundColour(index, rowColor);

        ++index;
    }
}
