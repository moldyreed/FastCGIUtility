project(fastcginetworkconfig_tests CXX)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${PROJECT_NAME}

	"${PROJECT_SOURCE_DIR}/networkconfig-test.cpp"
	"${PROJECT_SOURCE_DIR}/dispatcher-test.cpp"
	"${PROJECT_SOURCE_DIR}/tests.cpp"
)
target_link_libraries(${PROJECT_NAME} gtest gtest_main fastcginetworkconfig_lib )
add_test(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/tests.cpp")
