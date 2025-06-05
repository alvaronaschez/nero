#include(FetchContent)
#
#FetchContent_Declare(
#  Catch2
#  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#  GIT_TAG v3.8.1  # or the latest release
#)
#FetchContent_MakeAvailable(Catch2)

find_package(Catch2 3 REQUIRED)

add_executable(tests
    test_example.cc
)

target_link_libraries(tests
    PRIVATE
        nero_lib
        Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(tests)

