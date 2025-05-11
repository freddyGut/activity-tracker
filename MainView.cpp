#include <wx/wx.h>
#include <wx/event.h>
#include <wx/msw/button.h>
#include <wx/listctrl.h>
#include <wx/calctrl.h> // events and costructors for calendars


#include "MainView.h"
#include "Register.h"

#include <wx/generic/textdlgg.h>

#include "AddActivityDialog.h"


// === Constructor ===
MainView::MainView(const wxString& title): wxFrame(nullptr, wxID_ANY, title, wxPoint(200,200), wxSize(8000, 600))
{
    SetBackgroundColour(wxColour(0, 116, 166));

    // Main sizer: HORIZONTAL
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);


    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
    // Bigger calendar
    calendar = new wxGenericCalendarCtrl(this, ID_Calendar, wxDefaultDateTime, wxDefaultPosition, wxSize(300, 400));
    wxFont calendarFont(14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Rockwell");
    calendar->SetFont(calendarFont);
    calendar->SetHeaderColours(*wxWHITE, wxColour(0, 65, 112));        // Header text
    calendar->SetHighlightColours(*wxWHITE, *wxRED);      // Selected day
    calendar->SetHolidayColours(*wxBLUE, *wxWHITE);      // Festivity


    wxBoxSizer* infoSizer = new wxBoxSizer(wxHORIZONTAL);

    totalActivitiesText = new wxStaticText(this, wxID_ANY, "Total activities: 0  ");
    wxFont totalActivitiesFont(9, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Rockwell");
    totalActivitiesText->SetFont(totalActivitiesFont);
    totalActivitiesText->SetForegroundColour(*wxWHITE);
    searchBox = new wxTextCtrl(this, wxID_ANY);
    wxFont searchFont(7, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Rockwell");
    searchBox->SetFont(searchFont);
    searchBox->SetHint("Search by description"); //placeholder
    searchButton = new wxButton(this, ID_SearchActivity, "Search");
    searchButton->SetBackgroundColour(wxColour(0, 65, 112));
    searchButton->SetForegroundColour(*wxWHITE);
    searchButton->SetFont(totalActivitiesFont);

    infoSizer->Add(totalActivitiesText, 0);
    infoSizer->Add(searchBox, 0);
    infoSizer->Add(searchButton, 0);

    leftSizer->Add(calendar, 0, wxALL);
    leftSizer->Add(infoSizer, 0, wxALL);


    // Right sizer: VERTICAL (activities + buttons)
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    activityList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(350, 400), wxLC_REPORT | wxBORDER_SUNKEN);
    wxFont listFont(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Rockwell");
    activityList->SetFont(listFont);

    activityList->InsertColumn(0, "Time", wxLIST_FORMAT_LEFT, 120);
    activityList->InsertColumn(1, "Description",wxLIST_FORMAT_LEFT, 230);

    // Buttons
    addActivityButton = new wxButton(this, ID_AddActivity, "Add Activity");
    addActivityButton->SetBackgroundColour(wxColour(0, 65, 112));
    addActivityButton->SetForegroundColour(*wxWHITE);
    addActivityButton->SetFont(listFont);

    removeActivityButton = new wxButton(this, ID_RemoveActivity, "Remove Activity");
    removeActivityButton->SetBackgroundColour(wxColour(208, 8, 37));
    removeActivityButton->SetForegroundColour(*wxWHITE);
    removeActivityButton->SetFont(listFont);


    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(addActivityButton, 0, wxALL, 5);
    buttonSizer->Add(removeActivityButton, 0, wxALL, 5);

    // Building the right size
    rightSizer->Add(activityList, 0, wxEXPAND | wxALL, 5);
    rightSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    mainSizer->Add(leftSizer, 1, wxEXPAND | wxALL);
    mainSizer->Add(rightSizer, 1, wxEXPAND | wxALL);

    SetSizerAndFit(mainSizer);
}



wxGenericCalendarCtrl* MainView::GetCalendar() const {
    return calendar;
}

wxListCtrl* MainView::GetActivityList() const {
    return activityList;
}

wxButton* MainView::GetAddActivityButton() const {
    return addActivityButton;
}

wxButton* MainView::GetRemoveActivityButton() const {
    return removeActivityButton;
}

wxStaticText* MainView::GetTotalActivitiesText() const {
    return totalActivitiesText;
}

wxTextCtrl* MainView::GetSearchBox() const {
    return searchBox;
}

wxButton* MainView::GetSearchButton() const {
    return searchButton;
}






















