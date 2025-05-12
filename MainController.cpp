#include "MainController.h"

#include <algorithm>

#include "AddActivityDialog.h"
#include "SearchActivityController.h"
#include "SearchActivityDialog.h"

MainController::MainController(MainView *view, Register *model)
    : view(view), model(model) {
}


void MainController::Init() {
    BindEvents();
    wxDateTime selectedDate = view->GetCalendar()->GetDate();
    UpdateActivityList(selectedDate);
}


void MainController::BindEvents() {
    view->GetCalendar()->Bind(wxEVT_CALENDAR_SEL_CHANGED, &MainController::OnDateChanged, this);
    view->GetAddActivityButton()->Bind(wxEVT_BUTTON, &MainController::OnAddActivity, this);
    view->GetRemoveActivityButton()->Bind(wxEVT_BUTTON, &MainController::OnRemoveActivity, this);
    view->GetSearchButton()->Bind(wxEVT_BUTTON, &MainController::OnSearchActivity, this);
}


void MainController::OnDateChanged(wxCalendarEvent &event) {
    wxDateTime selectedDate = event.GetDate();
    UpdateActivityList(selectedDate);
}


void MainController::OnAddActivity(wxCommandEvent &event) {
    AddActivityDialog *dialog = new AddActivityDialog(view);


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

        // building DateTime object
        wxDateTime date = view->GetCalendar()->GetDate();
        if (!date.IsValid()) {
            wxLogError("Invalid date selected.");
            return;
        }

        wxDateTime startTime(date.GetDay(), date.GetMonth(), date.GetYear(), startHour, startMinute);
        wxDateTime endTime(date.GetDay(), date.GetMonth(), date.GetYear(), endHour, endMinute);

        try {
            Activity activity(description.ToStdString(), startTime, endTime);
            model->AddActivity(date, activity);
            UpdateTotalActivitiesText(model->GetTotalNumberOfActivities());
            UpdateActivityList(date);
        } catch (const std::invalid_argument &e) {
            wxLogError(e.what());
        }
    }

    dialog->Destroy();
}


void MainController::OnRemoveActivity(wxCommandEvent &event) {
    int activityIndex = view->GetActivityList()->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (activityIndex == -1) {
        wxMessageBox("No activity selected!", "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxDateTime date = view->GetCalendar()->GetDate();
    std::vector<Activity> activities = model->GetActivitiesPerDate(date);

    if (activityIndex < 0 || activityIndex >= static_cast<int>(activities.size())) {
        wxMessageBox("Invalid activity selected!", "Error", wxOK | wxICON_ERROR);
        return;
    }

    Activity selectedActivity = activities[activityIndex];
    bool removed = model->RemoveActivity(date, selectedActivity);
    if (!removed) {
        wxMessageBox("Activity not found!", "Error", wxOK | wxICON_ERROR);
        return;
    }

    UpdateActivityList(date);
    UpdateTotalActivitiesText(model->GetTotalNumberOfActivities());
}


void MainController::OnSearchActivity(wxCommandEvent &event) {
    std::string description = view->GetSearchBox()->GetValue().ToStdString();
    std::vector<Activity> searchActivities = model->GetActivitiesPerDescription(description);
    if (searchActivities.size() == 0) {
        wxMessageBox("Activity not found!", "Error", wxOK | wxICON_ERROR);
        return;
    }

    auto *dialog = new SearchActivityDialog(view);
    SearchActivityController controller(dialog);
    controller.ShowActivities(searchActivities);
    dialog->ShowModal();
    dialog->Destroy();
}


// === HELPER === OK
void MainController::UpdateActivityList(const wxDateTime &selectedDate) {
    view->GetActivityList()->DeleteAllItems();

    std::vector<Activity> activities = model->GetActivitiesPerDate(selectedDate);

    int index = 0;
    for (const auto &activity: activities) {
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


void MainController::UpdateTotalActivitiesText(int total) {
    view->GetTotalActivitiesText()->SetLabel(wxString::Format("Total activities: %d  ", total));
}
