#include <gtest/gtest.h>
#include <wx/datetime.h>
#include "../Register.h"

class RegisterTestFixture : public ::testing::Test {
protected:
  Register reg;
  Activity* yoga;
  Activity* run;
  wxDateTime date;

  void SetUp() override {

    date.Set(15, wxDateTime::Apr, 2025);

    wxDateTime startTime, endTime;
    startTime.Set(15, wxDateTime::Apr, 2025, 7, 0);
    endTime.Set(15, wxDateTime::Apr, 2025, 8, 30);
    yoga = new Activity("Yoga", startTime, endTime);

    startTime.Set(15, wxDateTime::Apr, 2025, 8, 30);
    endTime.Set(15, wxDateTime::Apr, 2025, 10, 0);
    run = new Activity("Run", startTime, endTime);

    reg.AddActivity(date, *yoga);
    reg.AddActivity(date, *run);
  }

  void TearDown() override {
    delete yoga;
    delete run;
  }

};


TEST_F(RegisterTestFixture, CorrectRegisterSize) {
  ASSERT_EQ(reg.GetActivitiesPerDate(date).size(), 2);
}

TEST_F(RegisterTestFixture, ActivitiesStoredCorrectly) {
  auto activites = reg.GetActivitiesPerDate(date);
  ASSERT_EQ(activites[0].getDescription(), "Yoga");
  ASSERT_EQ(activites[1].getDescription(), "Run");
}

TEST_F(RegisterTestFixture, RemoveActivityWorksCorrectly) {
  reg.RemoveActivity(date, *yoga);
  auto activities = reg.GetActivitiesPerDate(date);
  ASSERT_EQ(activities.size(), 1);
  ASSERT_EQ(activities[0].getDescription(), "Run");
}

TEST_F(RegisterTestFixture, RemoveActivityNotAdded) {
  auto t1 = wxDateTime::Today() + wxTimeSpan::Hours(5);
  auto t2 = wxDateTime::Today() + wxTimeSpan::Hours(6);

  bool result = reg.RemoveActivity(wxDateTime::Today(), Activity("Basket", t1, t2));
  EXPECT_FALSE(result);
}





// === BASIC TYPE OF TEST === //


TEST(RegisterTest, AddActivityInsertsCorrectly) {
  Register reg;
  wxDateTime day(1, wxDateTime::Mar, 2024);
  wxDateTime start(1, wxDateTime::Mar, 2024, 8);
  wxDateTime end(1, wxDateTime::Mar, 2024, 12);
  Activity a("Study", start, end);

  reg.AddActivity(day, a);
  auto activities = reg.GetActivitiesPerDate(day);

  ASSERT_EQ(activities.size(), 1);
  EXPECT_EQ(activities[0].getDescription(), "Study");
}


TEST(RegisterTest, RemoveActivityWorks) {
  Register reg;
  wxDateTime day(5, wxDateTime::Apr, 2024);
  wxDateTime start1(5, wxDateTime::Apr, 2024, 6);
  wxDateTime end1(5, wxDateTime::Apr, 2024, 7);
  wxDateTime start2(5, wxDateTime::Apr, 2024, 8);
  wxDateTime end2(5, wxDateTime::Apr, 2024, 9);

  Activity a1("Gym", start1, end1);
  Activity a2("Read", start2, end2);

  reg.AddActivity(day, a1);
  reg.AddActivity(day, a2);
  reg.RemoveActivity(day, a1);

  auto remaining = reg.GetActivitiesPerDate(day);
  ASSERT_EQ(remaining.size(), 1);
  EXPECT_EQ(remaining[0].getDescription(), "Read");
}


TEST(RegisterTest, NoCrashOnRemoveFromEmptyDay) {
  Register reg;
  wxDateTime emptyDay(10, wxDateTime::Dec, 2023);
  wxDateTime start(1, wxDateTime::Mar, 2024, 8);
  wxDateTime end(1, wxDateTime::Mar, 2024, 12);
  Activity dummy("X", start, end);

  EXPECT_NO_THROW(reg.RemoveActivity(emptyDay, dummy));
}


TEST(registerTest, GetActivitiesByDescriptionReturnsCorrectMatches) {
  Register reg;
  wxDateTime day = wxDateTime::Today();
  wxDateTime t1 = wxDateTime::Now();
  wxDateTime t2 = t1 + wxTimeSpan::Hours(1);

  reg.AddActivity(day, Activity("Study", t1, t2));
  reg.AddActivity(day, Activity("Sport", t1, t2));
  reg.AddActivity(day + wxTimeSpan::Days(1), Activity("Study", t1, t2));

  auto result = reg.GetActivitiesPerDescription("Study");
  EXPECT_EQ(result.size(), 2);

}


TEST(registerTest, GetActivitiesByDescriptionReturnsZeroLengthVector) {
  Register reg;
  wxDateTime day = wxDateTime::Today();
  wxDateTime t1 = wxDateTime::Now();
  wxDateTime t2 = t1 + wxTimeSpan::Hours(1);

  reg.AddActivity(day, Activity("Study", t1, t2));
  reg.AddActivity(day, Activity("Sport", t1, t2));
  reg.AddActivity(day + wxTimeSpan::Days(1), Activity("Study", t1, t2));

  auto result = reg.GetActivitiesPerDescription("Dinner");
  EXPECT_EQ(result.size(), 0);

}