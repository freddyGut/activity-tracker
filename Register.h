
#ifndef REGISTER_H
#define REGISTER_H
#include <vector>
#include <wx/datetime.h>
#include <map>

#include "Activity.h"


class Register {

public:
    Register() = default;

    void AddActivity(const wxDateTime day, const Activity& activity);
    bool RemoveActivity(const wxDateTime& day, const Activity& activity); //bool se parametri sbagliati
    std::vector<Activity> GetActivitiesPerDate(const wxDateTime& day) const;
    int GetTotalActivities() const;
    std::vector<Activity> GetActivitiesPerDescription(const std::string& description) const;

private:
    std::map<wxDateTime, std::vector<Activity>> registerMap;

};



#endif //REGISTER_H
