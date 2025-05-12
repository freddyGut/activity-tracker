//
// Created by Jonathan on 12/05/2025.
//

#ifndef SEARCHACTIVITYDIALOG_H
#define SEARCHACTIVITYDIALOG_H

#include <wx/wx.h>
#include <wx/listctrl.h>

#include "Activity.h"


class SearchActivityDialog : public wxDialog {
public:
    SearchActivityDialog(wxWindow *parent);

    void ClearActivities();

    void AddActivityRow(const wxString &day, const wxString &time);

private:
    wxListCtrl *activityList;
};


#endif //SEARCHACTIVITYDIALOG_H
