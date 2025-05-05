set(INSTALL_GTEST OFF)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR ./lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
message("wxWidgets_LIBRARIES" ${wxWidgets_LIBRARIES})

set(TEST_SOURCE_FILES ActivityTest.cpp RegisterTest.cpp RunAllTests.cpp)
add_executable(runActivityTrackerTest ${TEST_SOURCE_FILES}) # puts together all test source files
target_link_libraries(runActivityTrackerTest gtest gtest_main core ${wxWidgets_LIBRARIES})
# links together the test source files, the Google Test library and the source file respectively