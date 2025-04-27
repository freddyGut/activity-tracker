
#ifndef ACTIVITY_H
#define ACTIVITY_H
#include <wx/datetime.h>


class Activity {

public:
  Activity (const std::string& description, wxDateTime& startTime, wxDateTime& endTime);

  // Getters
  std::string getDescription() const;
  wxDateTime getStartTime() const;
  wxDateTime getEndTime() const;

  // Setters
  void setDescription(const std::string& description);
  void setStartTime(const wxDateTime& startTime);
  void setEndTime(const wxDateTime& endTime);


private:
  std::string description;
  wxDateTime startTime;
  wxDateTime endTime;
};



#endif //ACTIVITY_H
