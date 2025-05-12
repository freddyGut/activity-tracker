#include "Register.h"

#include <algorithm>
#include <wx/datetime.h>
#include <wx/log.h>


void Register::AddActivity(const wxDateTime day, const Activity &activity) {
    wxDateTime normalizedDate = day;
    normalizedDate.ResetTime(); //resets time to 00:00:00, so the key is the same for all activities in the same date

    registerMap[normalizedDate].push_back(activity);
}

bool Register::RemoveActivity(const wxDateTime &day, const Activity &activity) {
    wxDateTime normalizedDate = day;
    normalizedDate.ResetTime();

    auto it = registerMap.find(normalizedDate);
    if (it != registerMap.end()) {
        auto &activities = it->second;
        activities.erase(std::remove_if(activities.begin(), activities.end(),
                                        [&activity](const Activity &a) {
                                            return a.getDescription() == activity.getDescription()
                                                   && a.getFormattedStartTime() == activity.getFormattedStartTime()
                                                   && a.getFormattedEndTime() == activity.getFormattedEndTime();
                                        }),
                         activities.end());

        return true;
    }

    return false;
}


std::vector<Activity> Register::GetActivitiesPerDate(const wxDateTime &day) const {
    wxDateTime normalizedDate = day;
    normalizedDate.ResetTime();

    auto it = registerMap.find(normalizedDate);
    if (it != registerMap.end()) {
        // ordering the activities
        std::vector<Activity> activities = it->second;
        std::sort(activities.begin(), activities.end());
        return activities;
    }
    return {};
}


int Register::GetTotalActivities() const {
    int total = 0;
    for (const auto &pair: registerMap) {
        total += static_cast<int>(pair.second.size());
    }

    return total;
}


std::vector<Activity> Register::GetActivitiesPerDescription(const std::string &description) const {
    std::vector<Activity> result;

    for (const auto &pair: registerMap) {
        for (const auto &activity: pair.second) {
            if (activity.getDescription() == description) {
                result.push_back(activity);
            }
        }
    }

    return result;
}
