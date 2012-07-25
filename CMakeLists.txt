project (ROBJECT)

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/contrib")

add_subdirectory (contrib)
add_subdirectory (robject)
include_directories(${ROBJECT_SOURCE_DIR}/robject)

add_subdirectory (test)
