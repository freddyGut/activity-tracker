//
// Created by Jonathan on 12/05/2025.
//


#include <vector>

#include "SearchActivityDialog.h"
#include "Activity.h"


SearchActivityDialog::SearchActivityDialog(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, "Search activity list", wxPoint(400, 300), wxSize(400, 300)) {
    SetBackgroundColour(wxColour(0, 116, 166));
    activityList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(350, 400), wxLC_REPORT | wxBORDER_SUNKEN);
    wxFont listFont(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Rockwell");
    activityList->SetFont(listFont);

    activityList->InsertColumn(0, "Day", wxLIST_FORMAT_LEFT, 150);
    activityList->InsertColumn(1, "Time", wxLIST_FORMAT_LEFT, 250);
}


void SearchActivityDialog::ClearActivities() {
    activityList->DeleteAllItems();
}


void SearchActivityDialog::AddActivityRow(const wxString &day, const wxString &time) {
    long index = activityList->InsertItem(activityList->GetItemCount(), day);
    activityList->SetItem(index, 1, time);

    //alternating colors
    wxColour rowColor = (index % 2 == 0) ? wxColour(245, 245, 245) : wxColour(230, 230, 255);
    activityList->SetItemBackgroundColour(index, rowColor);
}
