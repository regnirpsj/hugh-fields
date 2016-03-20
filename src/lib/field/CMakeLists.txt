# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED COMPONENTS thread)
find_package(HUGH                           REQUIRED COMPONENTS support)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${HUGH_INCLUDE_DIRS})

set(SRC)
list(APPEND SRC "adapter/multi.cpp")
list(APPEND SRC "adapter/single.cpp")
list(APPEND SRC "base.cpp")
list(APPEND SRC "connection/manager.cpp")
list(APPEND SRC "connection/update.cpp")
list(APPEND SRC "container.cpp")
list(APPEND SRC "defaults.cpp")
list(APPEND SRC "multi/base.cpp")
list(APPEND SRC "single/base.cpp")
list(APPEND SRC "value/multi.cpp")
list(APPEND SRC "value/single.cpp")

set(LIBS)
list(APPEND LIBS ${HUGH_LIBRARIES})
list(APPEND LIBS ${Boost_LIBRARIES})

if(CMAKE_HOST_UNIX)
  # 'pthread_mutexattr_settype' used in connection/manager.cpp
  list(APPEND LIBS pthread)
endif()

set(LIB "hugh_field")

cma_setup_library(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS} INCDIR "hugh/field")
cma_setup_export(${LIB})

add_subdirectory(test EXCLUDE_FROM_ALL)
