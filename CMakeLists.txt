project (ROBJECT)

add_subdirectory (robject)
include_directories(${ROBJECT_SOURCE_DIR}/robject)

add_subdirectory (rtest)
include_directories(${ROBJECT_SOURCE_DIR}/rtest)

add_subdirectory (test)
