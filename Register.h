#ifndef REGISTER_H
#define REGISTER_H
#include <vector>
#include <wx/datetime.h>
#include <map>

#include "Activity.h"


class Register {
public:
    Register();

    void AddActivity(const wxDateTime day, const Activity &activity);

    bool RemoveActivity(const wxDateTime &day, const Activity &activity);

    std::vector<Activity> GetActivitiesPerDate(const wxDateTime &day) const;

    int GetTotalNumberOfActivities() const;

    std::vector<Activity> GetActivitiesPerDescription(const std::string &description) const;

private:
    std::map<wxDateTime, std::vector<Activity> > registerMap;
    int totalNumberOfActivities;
};


#endif //REGISTER_H
