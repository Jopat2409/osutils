include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

include(GoogleTest)

add_executable(osutils_test "")
target_sources(osutils_test
    PUBLIC
        db_test.cpp
)
target_link_libraries(osutils_test
  PRIVATE
    GTest::GTest
)

gtest_discover_tests(osutils_test)

add_custom_command(TARGET osutils_test POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/build/src/Debug/osutils.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:osutils_test>)                 # <--this is out-file path
