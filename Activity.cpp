//
// Created by Jonathan on 27/04/2025.
//

#include "Activity.h"

std::string Activity::getDescription() const {
      return description;
  }
wxDateTime Activity::getStartTime() const {
      return startTime;
  }
wxDateTime Activity::getEndTime() const {
      return endTime;
  }


void Activity::setDescription(const std::string& description) {
      this->description = description;
  }
void Activity::setStartTime(const wxDateTime& startTime) {
      this->startTime = startTime;
  }
void Activity::setEndTime(const wxDateTime& endTime) {
      this->endTime = endTime;
  }