set(CMAKE_C_FLAGS "-Wall -Werror ${CMAKE_CXX_FLAGS}")

add_library(robject car.c robject.c rint.c rstring.c volvo.c)
