#
# Copyright and description to be placed here
#

PROJECT(medDoxygen)

INCLUDE (${CMAKE_ROOT}/Modules/Documentation.cmake OPTIONAL)

IF (BUILD_DOCUMENTATION)

  SET (DOXYFILE ${PROJECT_BINARY_DIR}/med_doxyfile)
  CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/med_doxyfile.in
             ${PROJECT_BINARY_DIR}/med_doxyfile
             @ONLY)
             
  IF (WIN32)
    CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/makedoc.bat.in
             ${PROJECT_BINARY_DIR}/makedoc.bat
             IMMEDIATE)
  ENDIF (WIN32)

ENDIF (BUILD_DOCUMENTATION)
