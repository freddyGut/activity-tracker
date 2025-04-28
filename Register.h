
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
    void RemoveActivity(const wxDateTime& day, const Activity& activity);
    std::vector<Activity> GetActivitiesPerDate(const wxDateTime& day);

private:
    std::map<wxDateTime, std::vector<Activity>> registerMap;

};



#endif //REGISTER_H
