cmake_minimum_required(VERSION 3.0)
project("c-homework" C)

set(TARGET_GROUP production CACHE STRING "Group to build")

add_subdirectory(src)

if(TARGET_GROUP STREQUAL production)
  add_subdirectory(main)
elseif(TARGET_GROUP STREQUAL test)
  include(CTest)

  add_subdirectory(external)
  add_subdirectory(test)

else()
  message(FATAL_ERROR "Given TARGET_GROUP unknown")
endif()
#set(LIB_SOURCE
#  db.h db.c)

#set(LIB_TEST_SOURCE
#  db_test.c)

