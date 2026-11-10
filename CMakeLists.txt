cmake_minimum_required(VERSION 3.11)

project(int2048)

enable_testing()

include_directories(src/include)

set(DATA_PATH "${CMAKE_CURRENT_SOURCE_DIR}/data")
set(TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/test")
file(GLOB_RECURSE SOURCES "${DATA_PATH}/**.cpp")

foreach (SOURCE ${SOURCES})
  file(RELATIVE_PATH TESTCASE_NAME "${DATA_PATH}" "${SOURCE}")
  string(REPLACE "/" "_" TESTCASE_NAME "${TESTCASE_NAME}")
  string(REPLACE ".cpp" "" TESTCASE_NAME "${TESTCASE_NAME}")
  string(REPLACE ".cpp" ".in" INPUT ${SOURCE})
  string(REPLACE ".cpp" ".out" OUTPUT ${SOURCE})
  add_executable("${TESTCASE_NAME}" ${SOURCE} src/int2048.cpp)
  if (EXISTS ${INPUT})
    add_test(NAME ${TESTCASE_NAME} COMMAND bash -c "$<TARGET_FILE:${TESTCASE_NAME}> <${INPUT} | diff ${OUTPUT} -")
  else ()
    add_test(NAME ${TESTCASE_NAME} COMMAND bash -c "$<TARGET_FILE:${TESTCASE_NAME}> | diff ${OUTPUT} -")
  endif()
  set_property(TEST ${TESTCASE_NAME} PROPERTY TIMEOUT 10)
endforeach()

# Hand-written tests in test/: one executable per file (no .out to diff against).
file(GLOB TEST_SOURCES "${TEST_PATH}/*.cpp")
foreach (SOURCE ${TEST_SOURCES})
  get_filename_component(TEST_NAME "${SOURCE}" NAME_WE)
  add_executable("${TEST_NAME}" ${SOURCE} src/int2048.cpp)
endforeach()