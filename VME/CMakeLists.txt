#
# Copyright and description to be placed here
#

PROJECT(medVME)

# Set your list of sources here.
SET(PROJECT_SRCS
  medVMEFactory.cpp 
  medVMEFactory.h
  medVMELabeledVolume.cpp
  medVMELabeledVolume.h
  medPipeFactoryVME.cpp
  medPipeFactoryVME.h

  medPipeVolumeMIP.cpp
  medPipeVolumeMIP.h
  medPipeDensityDistance.cpp
  medPipeDensityDistance.h
  medPipeTrajectories.cpp
  medPipeTrajectories.h
  medPipeVolumeDRR.cpp
  medPipeVolumeDRR.h
  medPipeVolumeVR.cpp
  medPipeVolumeVR.h

  # mafPolylineGraph.cpp
  # mafPolylineGraph.h
  medVMEPolylineGraph.cpp
  medVMEPolylineGraph.h
  medVMEPolylineEditor.cpp
  medVMEPolylineEditor.h
  medPipePolylineGraphEditor.cpp
  medPipePolylineGraphEditor.h
  medVMEOutputPolylineEditor.cpp
  medVMEOutputPolylineEditor.h
  medVMEMaps.cpp
  medVMEMaps.h
  
  medVMEWrappedMeter.cpp
  medVMEWrappedMeter.h
  medVMEOutputWrappedMeter.cpp
  medVMEOutputWrappedMeter.h
  medPipeWrappedMeter.cpp
  medPipeWrappedMeter.h

  medVMESurfaceEditor.cpp
  medVMESurfaceEditor.h
  medPipeSurfaceEditor.cpp
  medPipeSurfaceEditor.h
  medVMEOutputSurfaceEditor.cpp
  medVMEOutputSurfaceEditor.h
  
  medVisualPipeSlicerSlice.cpp
  medVisualPipeSlicerSlice.h
  
  medVisualPipePolylineGraph.cpp
  medVisualPipePolylineGraph.h

  medVMEComputeWrapping.h
  medVMEComputeWrapping.cpp
  medPipeComputeWrapping.h
  medPipeComputeWrapping.cpp
  medVMEOutputComputeWrapping.cpp
  medVMEOutputComputeWrapping.h 
  
  medPipeVectorField.cpp
  medPipeVectorField.h
  medPipeVectorFieldMapWithArrows.cpp
  medPipeVectorFieldMapWithArrows.h
  medPipeVectorFieldGlyphs.cpp
  medPipeVectorFieldGlyphs.h
  medPipeVectorFieldSurface.cpp
  medPipeVectorFieldSurface.h
  medPipeVectorFieldSlice.cpp
  medPipeVectorFieldSlice.h
  medPipeTensorField.cpp
  medPipeTensorField.h
  medPipeTensorFieldGlyphs.cpp
  medPipeTensorFieldGlyphs.h
  medPipeTensorFieldSurface.cpp
  medPipeTensorFieldSurface.h
  medPipeTensorFieldSlice.cpp
  medPipeTensorFieldSlice.h
  medPipeCompound.cpp
  medPipeCompound.h
  medPipeCompoundVolume.cpp
  medPipeCompoundVolume.h
  medPipeCompoundVolumeFixedScalars.cpp
  medPipeCompoundVolumeFixedScalars.h
  medVMESegmentationVolume.cpp
  medVMESegmentationVolume.h
  medDataPipeCustomSegmentationVolume.cpp
  medDataPipeCustomSegmentationVolume.h
  medAttributeSegmentationVolume.cpp
  medAttributeSegmentationVolume.h
  
  
  ### TO BE COMMITTED DOWN ###
  mafPipeSlice.cpp
  mafPipeSlice.h
  ############################
  
  mafGizmoROI_BES.cpp
  mafGizmoROI_BES.h
  mafPipeMeshSlice_BES.cpp
  mafPipeMeshSlice_BES.h
  mafPipePolylineSlice_BES.cpp
  mafPipePolylineSlice_BES.h
  mafPipeSurfaceSlice_BES.cpp
  mafPipeSurfaceSlice_BES.h
  mafPipeVolumeSlice_BES.cpp
  mafPipeVolumeSlice_BES.h
  
  ############# VolumeLarge Files - TO BE COMMITTED DOWN ########
  ../BES_Beta/IO/mafBrickedFile.cpp
  ../BES_Beta/IO/mafBrickedFile.h
  ../BES_Beta/IO/mafBrickedFileReader.cpp
  ../BES_Beta/IO/mafBrickedFileReader.h
  ../BES_Beta/IO/mafBrickedFileWriter.cpp
  ../BES_Beta/IO/mafBrickedFileWriter.h
  ../BES_Beta/IO/mafVolumeLargeReader.cpp
  ../BES_Beta/IO/mafVolumeLargeReader.h
  ../BES_Beta/IO/mafVolumeLargeWriter.cpp
  ../BES_Beta/IO/mafVolumeLargeWriter.h
  mafVMEVolumeLarge.cpp
  mafVMEVolumeLarge.h
  mafVMEVolumeLargeUtils.cpp
  mafVMEVolumeLargeUtils.h  
  ###############################################################

  medPipeVolumeSliceBlend.cpp
  medPipeVolumeSliceBlend.h

  medVisualPipeCollisionDetection.cpp
  medVisualPipeCollisionDetection.h

  medPipeVolumeSliceNotInterpolated.cpp
  medPipeVolumeSliceNotInterpolated.h
  
  medPipeRayCast.cpp
  medPipeRayCast.h
  

)

IF (MAF_USE_ITK)
SET(PROJECT_SRCS  ${PROJECT_SRCS}
  mafVMERawMotionData.cpp
  mafVMERawMotionData.h
  medPipeGraph.cpp
  medPipeGraph.h
  medVMEAnalog.cpp
  medVMEAnalog.h
  
 #add for stent
  medVMEStent.cpp
  medVMEStent.h

  #stent used tool, to find nearest point
  kdtree.c
  kdtree.h

  
)
ENDIF (MAF_USE_ITK)

MESSAGE("${CMAKE_SHARED_LINKER_FLAGS}")

# List libraries that are needed by this project.
SET(PROJECT_LIBS "mafVME" "mafInteraction" "vtkMAF")

SET(PROJECT_LIBS ${PROJECT_LIBS} vtkMED)

IF(MED_BUILD_MEDDLL)
  SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /FORCE:MULTIPLE")
  SET(BUILD_SHARED_LIBS 1)
  ADD_DEFINITIONS(-DMED_VME_EXPORTS)
  # Create the library.
  ADD_LIBRARY(${PROJECT_NAME} ${PROJECT_SRCS})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} mafDLL vtkMED medGui medCommon)
ELSE(MED_BUILD_MEDDLL)
  # Create the library.
  ADD_LIBRARY(${PROJECT_NAME} ${PROJECT_SRCS})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${PROJECT_LIBS})
ENDIF (MED_BUILD_MEDDLL)
