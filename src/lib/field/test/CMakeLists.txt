# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED COMPONENTS unit_test_framework)
find_package(GLM   ${GLM_MINIMUM_VERSION}   REQUIRED)

include_directories(SYSTEM ${Boost_INLCUDE_DIR})
include_directories(SYSTEM ${GLM_INCLUDE_DIR})
include_directories(       ${CMAKE_CURRENT_SOURCE_DIR})

set(SRC)
list(APPEND SRC adapter_multi.cpp)
list(APPEND SRC adapter_single.cpp)
list(APPEND SRC connection_manager.cpp)
list(APPEND SRC connection_update.cpp)
list(APPEND SRC container.cpp)
list(APPEND SRC value_multi.cpp)
list(APPEND SRC value_single.cpp)

#add_definitions(-DHUGH_ALL_TRACE)
add_definitions(-DHUGH_FIELDS_ALL_TYPES_ENABLED)

set(LIBS)
list(APPEND LIBS ${LIB})
list(APPEND LIBS ${Boost_LIBRARIES})

cma_setup_test(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS})
