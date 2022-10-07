# Sources
file(GLOB CORE_SRCS "core/*.c")
file(GLOB GUI_SRCS "gui/*.c")
file(GLOB TESTS_SRCS "tests/*.c")
set(TEST_SCRIPT "build_tests.sh")
set(MAIN_SRC main.c)
file(GLOB TEST_SRCS "tests/*.c")
set(GRESOURCE_XML 3dviewer.gresource.xml)
set(GRESOURCE_C resources.c)


# Dependencies
find_package(PkgConfig REQUIRED)
find_package(Check REQUIRED)
find_package(OpenGL REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(GLIB REQUIRED glib-2.0)
find_program(
  GLIB_COMPILE_RESOURCES
  NAMES glib-compile-resources
  REQUIRED
  )
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR},
  ${CHECK_INCLUDE_DIRS},
  ${GTK4_INCLUDE_DIRS}
  )
add_definitions(${GTK4_CFLAGS_OTHER})
link_directories(${CHECK_LIBRARY_DIRS} ${GTK4_LIBRARY_DIRS})



add_executable(test_run ${CORE_SRCS} ${TESTS_SRCS})
target_link_libraries(
  test_run
  gcov
  glib-2.0
  ${CHECK_LIBRARIES}
  )
target_include_directories(test_run PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_target(
  test
  DEPENDS test_run
  COMMAND
  ./test_run
  )
set(COV_DIR "coverage")
set(COV_INFO "${COV_DIR}/coverage.info")
set(COV_REPORT "${COV_DIR}/index.html")
set(COV_SRCS_DIR "CMakeFiles/test_core.dir/")
add_custom_target(gcov_report
  COMMAND mkdir -p ${COV_DIR}
  COMMAND lcov -q -c -d ${COV_SRCS_DIR} -o ${COV_INFO} 
  COMMAND genhtml -q ${COV_INFO} -o ${COV_DIR}
  COMMAND find . -name "*.gcda" -exec rm {} +
  COMMAND find . -name "*.gcno" -exec rm {} +
  COMMAND open ${COV_REPORT}
  DEPENDS test
  )


# Documentation generation
set(DOCS_DIR "docs")
set(DOXYFILE "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")
add_custom_target(dvi
  COMMAND mkdir -p ${DOCS_DIR}
  COMMAND doxygen ${DOXYFILE}
  COMMAND make -C ${DOCS_DIR}/latex
  )


# Gresource source generation
add_custom_command(
  OUTPUT ${GRESOURCE_C}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND ${GLIB_COMPILE_RESOURCES}
  ARGS
      --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
      ${GRESOURCE_XML}
      --generate-source
  VERBATIM
  MAIN_DEPENDENCY ${GRESOURCE_XML}
  )
add_custom_target(
  resources
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
  )


# Main execuatable file
add_executable(
  ${PROJECT_NAME}
  ${MAIN_SRC}
  ${CORE_SRCS}
  ${GUI_SRCS}
  ${GRESOURCE_C}
  ) 
target_include_directories(${PROJECT_NAME} PUBLIC . gui)
target_link_libraries(
  ${PROJECT_NAME}
  ${GTK4_LIBRARIES}
  gcov
  ${OPENGL_gl_LIBRARY}
  )
add_dependencies(${PROJECT_NAME} resources)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
