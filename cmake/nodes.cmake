# -----------------------------------------------------------------
# JF_LIBRARY
#
# create and install a library, together with its header files
# 
# JF_LIBRARY(
#   NAME <library-name>
#   DEPENDENCIES <libraries that we depend on (optional)>
#   HEADERS <header files defining interfaces into the library (optional)>
#   SOURCES <C and C++ implementation files>
# )
# -----------------------------------------------------------------
FUNCTION(JF_LIBRARY)
  SET(options)
  SET(oneValueArgs NAME)
  SET(multiValueArgs DEPENDENCIES HEADERS SOURCES)
  CMAKE_PARSE_ARGUMENTS(JF_LIBRARY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if (NOT  "${JF_LIBRARY_UNPARSED_ARGUMENTS}" STREQUAL "")
    MESSAGE(FATAL_ERROR "JF_LIBRARY: unparsed arguments (${JF_LIBRARY_UNPARSED_ARGUMENTS}) remain: ${ARGN}")
  endif()

  ADD_LIBRARY(${JF_LIBRARY_NAME} ${JF_LIBRARY_HEADERS} ${JF_LIBRARY_SOURCES})
  TARGET_LINK_LIBRARIES(${JF_LIBRARY_NAME} ${JF_LIBRARY_DEPENDENCIES} ${CMAKE_THREAD_LIBS_INIT})

  # PIC - Position Independent Code. Needed to aggregate objects (from
  # an archive, likely) into a shared object.
  TARGET_COMPILE_OPTIONS(${JF_LIBRARY_NAME} PRIVATE -fPIC)

  INSTALL(TARGETS ${JF_LIBRARY_NAME} DESTINATION lib)
  INSTALL(FILES ${JF_LIBRARY_HEADERS} DESTINATION include)
ENDFUNCTION(JF_LIBRARY)

# -----------------------------------------------------------------
# JF_EXECUTABLE
#
# create and install an executable
# 
# JF_EXECUTABLE(
#   NAME <exe-name>
#   DEPENDENCIES <libraries that we depend on (optional)>
#   HEADERS <header files (optional; if given *not* installed)>
#   SOURCES <C and C++ implementation files>
# )
 # -----------------------------------------------------------------
FUNCTION(JF_EXECUTABLE)
  CMAKE_PARSE_ARGUMENTS(JF_EXECUTABLE "" "NAME" "HEADERS;SOURCES;DEPENDENCIES" ${ARGN})
  IF (NOT  "${JF_EXECUTABLE_UNPARSED_ARGUMENTS}" STREQUAL "")
    MESSAGE(FATAL_ERROR "JF_EXECUTABLE: unparsed arguments (${JF_EXECUTABLE_UNPARSED_ARGUMENTS}) remain: ${ARGN}")
  ENDIF()

  ADD_EXECUTABLE(${JF_EXECUTABLE_NAME} ${JF_EXECUTABLE_HEADERS} ${JF_EXECUTABLE_SOURCES})
  TARGET_LINK_LIBRARIES(${JF_EXECUTABLE_NAME} ${JF_EXECUTABLE_DEPENDENCIES} ${CMAKE_THREAD_LIBS_INIT})
  INSTALL(TARGETS ${JF_EXECUTABLE_NAME} DESTINATION bin)

ENDFUNCTION(JF_EXECUTABLE)
