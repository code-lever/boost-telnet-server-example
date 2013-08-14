cmake_minimum_required(VERSION 2.6)

project(boost-telnet)

set(BOOST_USE_STATIC_LIBS ON)
set(BOOST_USE_MULTITHREADED ON)
set(BOOST_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.49 COMPONENTS filesystem program_options system)

file(GLOB_RECURSE headers "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c*")

source_group("Header Files" FILES ${headers})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${Boost_INCLUDE_DIR})

add_executable(boost-telnet ${sources} ${headers})
target_link_libraries(boost-telnet pthread boost_system-mt boost_program_options-mt)

if(DOXYGEN_FOUND)
  configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  add_custom_target(docs ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES api-doc)
endif()
