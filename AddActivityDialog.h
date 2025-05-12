#ifndef ADDACTIVITYDIALOG_H
#define ADDACTIVITYDIALOG_H


#include <wx/wx.h>
#include <wx/spinctrl.h>

class AddActivityDialog : public wxDialog {
public:
    AddActivityDialog(wxWindow *parent);

    wxString GetDescription() const;

    int GetStartHour() const;

    int GetStartMinute() const;

    int GetEndHour() const;

    int GetEndMinute() const;

private:
    wxTextCtrl *descriptionCtrl;

    wxSpinCtrl *startHourCtrl;
    wxSpinCtrl *startMinuteCtrl;
    wxSpinCtrl *endHourCtrl;
    wxSpinCtrl *endMinuteCtrl;
    wxButton *okButton;

    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
    std::string description;

    void OnOK(wxCommandEvent &event);
};


#endif //ADDACTIVITYDIALOG_H
