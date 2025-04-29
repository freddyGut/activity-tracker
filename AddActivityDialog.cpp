
#include "AddActivityDialog.h"


AddActivityDialog::AddActivityDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Add activity", wxDefaultPosition, wxSize(500, 500))
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Activity description
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Description:"), 0, wxALL, 5);
    descriptionCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(descriptionCtrl, 0, wxALL | wxEXPAND, 5);

    // Start time
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Start time:"), 0, wxALL, 5);
    wxBoxSizer* startTimeSizer = new wxBoxSizer(wxHORIZONTAL);
    startHourCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 23, 0);
    startMinuteCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 59, 0);
    startTimeSizer->Add(startHourCtrl, 0, wxALL, 5);
    startTimeSizer->Add(new wxStaticText(this, wxID_ANY, ":"), 0, wxALIGN_CENTER_VERTICAL);
    startTimeSizer->Add(startMinuteCtrl, 0, wxALL, 5);
    mainSizer->Add(startTimeSizer, 0, wxALIGN_LEFT);

    // End time
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "End time:"), 0, wxALL, 5);
    wxBoxSizer* endTimeSizer = new wxBoxSizer(wxHORIZONTAL);
    endHourCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 23, 0);
    endMinuteCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1), wxSP_ARROW_KEYS, 0, 59, 0);
    endTimeSizer->Add(endHourCtrl, 0, wxALL, 5);
    endTimeSizer->Add(new wxStaticText(this, wxID_ANY, ":"), 0, wxALIGN_CENTER_VERTICAL);
    endTimeSizer->Add(endMinuteCtrl, 0, wxALL, 5);
    mainSizer->Add(endTimeSizer, 0, wxALIGN_LEFT);

    // Buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    okButton = new wxButton(this, wxID_OK, "OK");
    buttonSizer->Add(okButton, 0, wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    okButton->Bind(wxEVT_BUTTON, &AddActivityDialog::OnOK, this);

    SetSizerAndFit(mainSizer);
}

wxString AddActivityDialog::GetDescription() const
{
    return descriptionCtrl->GetValue();
}

int AddActivityDialog::GetStartHour() const
{
    return startHourCtrl->GetValue();
}

int AddActivityDialog::GetStartMinute() const
{
    return startMinuteCtrl->GetValue();
}

int AddActivityDialog::GetEndHour() const
{
    return endHourCtrl->GetValue();
}

int AddActivityDialog::GetEndMinute() const
{
    return endMinuteCtrl->GetValue();
}

void AddActivityDialog::OnOK(wxCommandEvent& event)
{
    // Fetching values from spin controls
    //startHour = GetStartHour();
    //startMinute = GetStartMinute();
    //endHour = GetEndHour();
    //endMinute = GetEndMinute();

    // Fetching the description
    //description = GetDescription();
    wxLogError("Clicked OK, closing dialog...");

    // Closing the window, everything ran well
    EndModal(wxID_OK);
}
