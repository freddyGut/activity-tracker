#include "SearchActivityController.h"

SearchActivityController::SearchActivityController(SearchActivityDialog *dialog)
    : view(dialog) {
}

void SearchActivityController::ShowActivities(const std::vector<Activity> &activities) {
    view->ClearActivities();
    for (const auto &activity: activities) {
        wxString day = activity.getStartTime().FormatDate();
        wxString time = activity.getFormattedStartTime() + " - " + activity.getFormattedEndTime();
        view->AddActivityRow(day, time);
    }
}
