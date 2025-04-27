
#include "Register.h"

#include <algorithm>

Register::Register() {
    registerMap = new std::map<wxDateTime, std::vector<Activity>>;
}

void Register::AddActivity(const wxDateTime &day, const Activity &activity) {
    registerMap[day].push_back(activity);
}

void Register::RemoveActivity(const wxDateTime &day, const Activity &activity) {

    // returns an iterator to the pair in the map corresponding to the day key, else end() if not found
    auto it = registerMap->find(day);
    // checking that the element actually exists
    if (it != registerMap->end()) {
        // now it points to the pair. we just care about the vector, not the day anymore
        auto activities = it->second;

        // returns the iterator to the element to delete (always the last one). It moves the element to delete in the last position
        auto toDelete_ = std::remove_if(activities.begin(), activities.end(), [&activity](const Activity& a) {
                return a.getDescription() == activity.getDescription()
                && a.getStartTime().IsSameDate(activity.getStartTime())
                && a.getEndTime().IsSameDate(activity.getEndTime());
            });
        // deleting the activity
        activities.erase(toDelete_, activities.end());

        // if the vector for a day is empty, delete that entry to the map to keep it clean
        if (activities.empty())
            registerMap->erase(it);
    }



}

std::vector<Activity> Register::GetActivitiesPerDate(const wxDateTime &day) const {

    auto it = registerMap->find(day);
    if (it != registerMap->end())
        return it->second;
    return {};
}

