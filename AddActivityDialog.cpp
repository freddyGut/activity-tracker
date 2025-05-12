#include "AddActivityDialog.h"


AddActivityDialog::AddActivityDialog(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, "Add activity", wxPoint(400, 300), wxSize(400, 300)) {
    SetBackgroundColour(wxColour(0, 116, 166));

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    wxFont textFont(14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Rockwell");

    // Activity description
    auto descLabel = new wxStaticText(this, wxID_ANY, "Description:");
    descLabel->SetFont(textFont);
    descLabel->SetForegroundColour(*wxWHITE);
    mainSizer->Add(descLabel, 0, wxALL | wxALIGN_CENTER, 5);

    descriptionCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_CENTER);
    descriptionCtrl->SetBackgroundColour(wxColour(196, 208, 255));
    descriptionCtrl->SetFont(textFont);
    mainSizer->Add(descriptionCtrl, 0, wxALL | wxEXPAND | wxALIGN_CENTER, 5);


    // Start time
    auto startTimeLabel = new wxStaticText(this, wxID_ANY, "Start time: ");
    startTimeLabel->SetFont(textFont);
    startTimeLabel->SetForegroundColour(*wxWHITE);
    mainSizer->Add(startTimeLabel, 0, wxALL | wxALIGN_CENTER, 5);
    wxBoxSizer *startTimeSizer = new wxBoxSizer(wxHORIZONTAL);

    startHourCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 23, 0);
    startHourCtrl->SetFont(textFont);
    startHourCtrl->SetBackgroundColour(wxColour(196, 208, 255));

    startMinuteCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 59, 0);
    startMinuteCtrl->SetFont(textFont);
    startMinuteCtrl->SetBackgroundColour(wxColour(196, 208, 255));

    startTimeSizer->Add(startHourCtrl, 0, wxALL, 5);
    startTimeSizer->Add(new wxStaticText(this, wxID_ANY, ":"), 0, wxALIGN_CENTER_VERTICAL);
    startTimeSizer->Add(startMinuteCtrl, 0, wxALL, 5);
    mainSizer->Add(startTimeSizer, 0, wxALIGN_CENTER);


    // End time
    auto endTimeLabel = new wxStaticText(this, wxID_ANY, "End time: ");
    endTimeLabel->SetFont(textFont);
    endTimeLabel->SetForegroundColour(*wxWHITE);
    mainSizer->Add(endTimeLabel, 0, wxALL | wxALIGN_CENTER, 5);
    wxBoxSizer *endTimeSizer = new wxBoxSizer(wxHORIZONTAL);

    endHourCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 23, 0);
    endHourCtrl->SetFont(textFont);
    endHourCtrl->SetBackgroundColour(wxColour(196, 208, 255));

    endMinuteCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 59, 0);
    endMinuteCtrl->SetFont(textFont);
    endMinuteCtrl->SetBackgroundColour(wxColour(196, 208, 255));

    endTimeSizer->Add(endHourCtrl, 0, wxALL | wxALIGN_CENTER, 5);
    endTimeSizer->Add(new wxStaticText(this, wxID_ANY, ":"), 0, wxALIGN_CENTER_VERTICAL);
    endTimeSizer->Add(endMinuteCtrl, 0, wxALL | wxALIGN_CENTER, 5);
    mainSizer->Add(endTimeSizer, 0, wxALIGN_CENTER);

    // OK button
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    okButton = new wxButton(this, wxID_OK, "OK");
    okButton->SetBackgroundColour(wxColour(0, 65, 112));
    okButton->SetForegroundColour(*wxWHITE);
    okButton->SetFont(textFont);
    buttonSizer->Add(okButton, 0, wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    okButton->Bind(wxEVT_BUTTON, &AddActivityDialog::OnOK, this);

    SetSizer(mainSizer);
}

wxString AddActivityDialog::GetDescription() const {
    return descriptionCtrl->GetValue();
}

int AddActivityDialog::GetStartHour() const {
    return startHourCtrl->GetValue();
}

int AddActivityDialog::GetStartMinute() const {
    return startMinuteCtrl->GetValue();
}

int AddActivityDialog::GetEndHour() const {
    return endHourCtrl->GetValue();
}

int AddActivityDialog::GetEndMinute() const {
    return endMinuteCtrl->GetValue();
}

void AddActivityDialog::OnOK(wxCommandEvent &event) {
    EndModal(wxID_OK);
}
