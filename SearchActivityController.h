#ifndef SEARCHACTIVITYCONTROLLER_H
#define SEARCHACTIVITYCONTROLLER_H

#include <vector>
#include "SearchActivityDialog.h"


class SearchActivityController {
public:
    explicit SearchActivityController(SearchActivityDialog *dialog);

    void ShowActivities(const std::vector<Activity> &activities);

private:
    SearchActivityDialog *view;
};


#endif //SEARCHACTIVITYCONTROLLER_H
