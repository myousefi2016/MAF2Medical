PROJECT (exMedical)

SET(PROJECT_SRCS 
	exMedicalApp.cpp
	exMedicalApp.h
	medOpInteractionOp.cpp
	medOpInteractionOp.h
	exWizardSample.cpp
	exWizardSample.h
)

IF (NOT EXECUTABLE_OUTPUT_PATH)
  SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/ CACHE INTERNAL 
     "Single output directory for building all executables.")
ENDIF (NOT EXECUTABLE_OUTPUT_PATH)

IF (WIN32)	
	#Newer versions of CMakes supports CXX_COMPILER info, so it is not necessary to test CMAKE_GENERATOR
	IF (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC" AND NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 18.0)		
		SET(NO_MANIFEST 1)
	ELSE (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC" AND NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 18.0)
		#Prehaps an older version, i.e., it does not support VS 10, 12, 13
		IF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 9 2008" OR ${CMAKE_GENERATOR} STREQUAL "Visual Studio 8 2005" OR ${CMAKE_GENERATOR} STREQUAL "Visual Studio 10" OR ${CMAKE_GENERATOR} STREQUAL "Visual Studio 11")
		  SET(NO_MANIFEST 1)
		ELSE(${CMAKE_GENERATOR} STREQUAL "Visual Studio 9 2008" OR ${CMAKE_GENERATOR} STREQUAL "Visual Studio 8 2005" OR ${CMAKE_GENERATOR} STREQUAL "Visual Studio 10" OR ${CMAKE_GENERATOR} STREQUAL "Visual Studio 11")
		  SET(NO_MANIFEST 0)
		ENDIF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 9 2008" OR ${CMAKE_GENERATOR} STREQUAL "Visual Studio 8 2005" OR ${CMAKE_GENERATOR} STREQUAL "Visual Studio 10" OR ${CMAKE_GENERATOR} STREQUAL "Visual Studio 11")	
	ENDIF (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC" AND NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 18.0)
		
	CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/app.rc.in ${PROJECT_BINARY_DIR}/app.rc @ONLY)
	CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/app.ico ${PROJECT_BINARY_DIR}/app.ico COPYONLY)
  ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${PROJECT_SRCS} ${PROJECT_BINARY_DIR}/app.rc)
ELSE (WIN32)
  ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_SRCS} )
ENDIF (WIN32)


IF(MED_BUILD_MEDDLL)
  SET(PROJECT_LIBS
  medOperations medGui medViews medVME medInteraction
)
ELSE(MED_BUILD_MEDDLL)
  SET(PROJECT_LIBS
  medOperations medGui medViews medVME medInteraction mafVME mafOperations vtkMAF GPUAPI
)
ENDIF (MED_BUILD_MEDDLL)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${PROJECT_LIBS})
IF (WIN32)
  SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/MANIFEST")
ENDIF (WIN32)

IF (MED_USE_GDCM)
  ADD_DEPENDENCIES(${PROJECT_NAME} BUILD_GDCM_LIBRARY)
ENDIF (MED_USE_GDCM)
