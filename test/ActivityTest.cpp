#include <gtest/gtest.h>
#include "../Activity.h"
#include <wx/datetime.h>


// === TEST FIXTURE === //

class ActivityTestFixture : public ::testing::Test {
protected:
    wxDateTime startTime;
    wxDateTime endTime;
    Activity* activity;

    void SetUp() override {
        startTime.Set(1, wxDateTime::Apr, 2025, 10, 0);
        endTime.Set(1, wxDateTime::Apr, 2025, 13, 0);
        activity = new Activity("Ballroom", startTime, endTime);
    }

    void TearDown() override {
        delete activity;
    }
};


TEST_F(ActivityTestFixture, GetNameReturnsCorrectName) {
    EXPECT_EQ(activity->getDescription(), "Ballroom");
}

TEST_F(ActivityTestFixture, GetStartTimeReturnsCorrectValue) {
    EXPECT_EQ(activity->getStartTime(), startTime);
}

TEST_F(ActivityTestFixture, GetEndTimeReturnsCorrectValue) {
    EXPECT_EQ(activity->getEndTime(), endTime);
}

TEST_F(ActivityTestFixture, GetFormattedStartTimeReturnsCorrectValue) {
    EXPECT_EQ(activity->getFormattedStartTime(), "10:00");
}

TEST_F(ActivityTestFixture, GetFormattedEndTimeReturnsCorrectValue) {
    EXPECT_EQ(activity->getFormattedEndTime(), "13:00");
}



// === BASIC TYPE OF TEST === //


TEST(ActivityTest, ConstructorStoresValuesCorrectly) {
    wxDateTime start(9, wxDateTime::Jan, 2024, 10, 0);
    wxDateTime end(9, wxDateTime::Jan, 2024, 12, 0);
    Activity a("Meeting", start, end);

    EXPECT_EQ(a.getDescription(), "Meeting");
    EXPECT_EQ(a.getFormattedStartTime(), "10:00");
    EXPECT_EQ(a.getFormattedEndTime(), "12:00");
}

TEST(ActivityTest, ConstructorThrowsIfStartAfterEnd) {
    wxDateTime start(9, wxDateTime::Jan, 2024, 15, 0);
    wxDateTime end(9, wxDateTime::Jan, 2024, 12, 0);

    EXPECT_THROW({Activity a("Meeting", start, end);}, std::invalid_argument);
}

TEST(ActivityTest, ConstructorThrowsIfStartEqualsEnd) {
    wxDateTime now = wxDateTime::Now();

    EXPECT_THROW({Activity a("Test", now, now);}, std::invalid_argument);
}
