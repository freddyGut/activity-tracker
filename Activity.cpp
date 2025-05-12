#include <wx/datetime.h>
#include <stdexcept>

#include "Activity.h"

Activity::Activity(const std::string &description, wxDateTime &startTime, wxDateTime &endTime)
    : description(description), startTime(startTime), endTime(endTime) {
    if (!startTime.IsEarlierThan(endTime)) {
        throw std::invalid_argument("Start time must be earlier than end time");
    }
}

Activity::Activity() : description(" "), startTime(wxDateTime::Now()),
                       endTime(wxDateTime::Now() + wxTimeSpan::Hours(1)) {
}


// === GETTERS ===
std::string Activity::getDescription() const {
    return description;
}

wxDateTime Activity::getStartTime() const {
    return startTime;
}

wxDateTime Activity::getEndTime() const {
    return endTime;
}


// === SETTERS ===
void Activity::setDescription(const std::string &description) {
    this->description = description;
}

void Activity::setStartTime(const wxDateTime &startTime) {
    this->startTime = startTime;
}

void Activity::setEndTime(const wxDateTime &endTime) {
    this->endTime = endTime;
}


std::string Activity::getFormattedStartTime() const {
    return startTime.Format("%H:%M").ToStdString();
}

std::string Activity::getFormattedEndTime() const {
    return endTime.Format("%H:%M").ToStdString();
}

bool Activity::operator<(const Activity &other) const {
    return startTime.IsEarlierThan(other.startTime);
}
