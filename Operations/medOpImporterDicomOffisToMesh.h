/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: medOpImporterDicomOffisToMesh.h,v $
Language:  C++
Date:      $Date: 2009-06-03 10:44:51 $
Version:   $Revision: 1.1.2.1 $
Authors:   Matteo Giacomoni, Roberto Mucci (DCMTK)
==========================================================================
Copyright (c) 2002/2007
SCS s.r.l. - BioComputing Competence Centre (www.scsolutions.it - www.b3c.it)

MafMedical Library use license agreement

The software named MafMedical Library and any accompanying documentation, 
manuals or data (hereafter collectively "SOFTWARE") is property of the SCS s.r.l.
This is an open-source copyright as follows:
Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, 
this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation and/or 
other materials provided with the distribution.
* Modified source versions must be plainly marked as such, and must not be misrepresented 
as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR 
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

MafMedical is partially based on OpenMAF.
=========================================================================*/

#ifndef __medOpImporterDicomOffisToMesh_H__
#define __medOpImporterDicomOffisToMesh_H__

//----------------------------------------------------------------------------
// Include :
//----------------------------------------------------------------------------
#include "mafOp.h"
#include "vtkImageData.h"
#include <map>


//----------------------------------------------------------------------------
// forward references :
//----------------------------------------------------------------------------
class medOpImporterDicomOffisToMeshToMesh;
class mmiDICOMImporterInteractor;
class medGUIWizard;
class medGUIWizardPageNew;
class mafString;
class mafTagArray;
class mafVMEImage;
class mafVMEVolumeGray;
class mafGUICheckListBox;
class mafVMEMesh;
class vtkDirectory;
class vtkWindowLevelLookupTable;
class vtkPlaneSource;
class vtkPolyDataMapper;
class vtkTexture;
class vtkActor;



WX_DECLARE_LIST(medOpImporterDicomOffisToMeshToMesh, medListDICOMFilesToMesh);
//----------------------------------------------------------------------------
// medOpImporterDicomOffisToMesh :
//----------------------------------------------------------------------------
/** 
Perform DICOM importer.
From a DICOM dataset return a VME Volume.
*/
class medOpImporterDicomOffisToMesh : public mafOp
{
public:
	medOpImporterDicomOffisToMesh(wxString label = "Importer DICOM");

	mafTypeMacro(medOpImporterDicomOffisToMesh, mafOp);

  /** Copy. */
	mafOp* Copy();

	/** Return true for the acceptable vme type. */
	bool Accept(mafNode *node) {return true;};

	/** Builds operation's interface calling CreateGui() method. */
	virtual void OpRun();

	/** This method is called at the end of the operation and result contain the wxOK or wxCANCEL. */
	virtual void OpStop	(int result);

	/** Execute the operation. */
	virtual  void OpDo();

	/** Makes the undo for the operation. */
	void OpUndo(){};

	/** Create the dialog interface for the importer. */
	virtual void CreateGui();

  /** Set the directory name which contains DICOM slices to import. */
  void SetDirName(const char *dirName){m_DicomDirectory = dirName;};

  /** Return the directory name which contains DICOM slices to import. */
  const char *GetDirName() const {return m_DicomDirectory.GetCStr();};

  /** OnEvent. */
	virtual void OnEvent(mafEventBase *maf_event);

  /** Assign the dicom directory*/
  void SetDicomDirectory(const char *directory){m_DicomDirectory = directory;}

  /** Set if output must be in imagedata(resampled) or original rectilinear grid. */
  void SetResampleFlag(int enable){m_ResampleFlag = enable;}

  /** Retrieve resample flag. */
  int GetResampleFlag(){return m_ResampleFlag;};

  /** Read Dicom file */
  void ReadDicom();

  /** Create the slice slice_num. */
  void CreateSlice(int slice_num);

  /** Return vtkImageData of the selected slice */
  vtkImageData* GetSlice(int slice_num);

  /** Build the volume starting from the list of dicom files. */
  int BuildVolume();

  /** Build the volume starting from the list of CineMRI files. */
  int BuildVolumeCineMRI();
  
  /** Create the pipeline to read the images. */
	virtual void CreatePipeline();

  /** Open dir containing Dicom images. */
  bool OpenDir();

protected:

	/** Create load page and his GUI for the wizard. */
	void CreateLoadPage();
	
	/** Create crop page and his GUI for the wizard. */
	void CreateCropPage();

	/** Create build page and his GUI for the wizard. */
	void CreateBuildPage();

	/** Reset the list of files and all the structures that own images information. */
	void ResetStructure();

	/** Reset the slider that allow to scan the slices. */
	void ResetSliders();

	/** Build the list of dicom filer recognized. */
	bool BuildDicomFileList(const char *dir);

	/** Return the slice number from the heightId and sliceId*/
	int GetImageId(int heightId, int timeId);

	/** Show the slice slice_num. */
	void ShowSlice();

  /** Fill listbox. */
  void FillListBox(mafString StudyUID);

	/** Import dicom tags into vme tags. */
	void ImportDicomTags();

	/** Perform update of guis of 3 pages of the wizard */
	void GuiUpdate();

	
  /** Enable slice slider. */
  void EnableSliceSlider(bool enable);

  /** Enable time slider. */
	void EnableTimeSlider(bool enable);

  /** Update camera. */
	void CameraUpdate();

  /** reset camera. */
	void CameraReset();

  /** On page changing. */
	void OnWizardPageChanging(){};

	/** Auto position of the crop plane in way of Volume side. */
	void AutoPositionCropPlane();

	/** Performe crop of dicom data. */
	void Crop();
  
  /** Performe Undo crop of dicom data. */
  void UndoCrop();

  /** Delete all istances of used objects. */
  void Destroy();

  /** function that resample volume with rectilinear grid output. */
  void ResampleVolume();

	vtkDirectory			*m_DirectoryReader; ///<Filter to get DICOM file from DICOM directory
	vtkWindowLevelLookupTable	*m_SliceLookupTable;
	vtkPlaneSource		*m_SlicePlane;
	vtkPolyDataMapper	*m_SliceMapper;
	vtkTexture				*m_SliceTexture;
	vtkActor					*m_SliceActor;
	vtkPlaneSource		*m_CropPlane;
	vtkActor					*m_CropActor;
	vtkActor					*m_SliceActorInCropPage;

	mmiDICOMImporterInteractor *m_DicomInteractor;

	medGUIWizard			*m_Wizard;
	medGUIWizardPageNew	*m_LoadPage;
	medGUIWizardPageNew	*m_CropPage;
	medGUIWizardPageNew	*m_BuildPage;
  mafVMEMesh        *m_Mesh;

	mafGUI	*m_LoadGuiLeft;
  mafGUI	*m_LoadGuiUnderLeft;
	mafGUI	*m_CropGuiLeft;
  mafGUI	*m_CropGuiCenter;
	mafGUI	*m_BuildGuiLeft;
  mafGUI	*m_BuildGuiCenter;

	int				m_DicomModality; ///<Modality to set witch type of DICOM to read
	mafString	m_DicomDirectory;
	mafString m_PatientName;
	mafString m_SurgeonName;
	mafString	m_Identifier;

  mafString m_PatientPosition;
  double m_ImagePositionPatient[3];
  double m_ImageOrientationPatient[9];

	int				m_BuildStepValue;
	int				m_DicomTypeRead; ///<Type DICOM Read from file
	int				m_SortAxes;
	int				m_NumberOfTimeFrames;

	medListDICOMFilesToMesh	*m_FilesList;
	medListDICOMFilesToMesh	*m_ListSelected;
  std::map<mafString,medListDICOMFilesToMesh*> m_DicomMap;

	mafString	m_CurrentSliceName;
	mafString	m_VolumeName;
  wxString  m_FileName;
	int				m_VolumeSide;

	int				 m_NumberOfStudy; ///<Number of study present in the DICOM directory
	int				 m_NumberOfSlices;
	wxListBox	*m_StudyListbox;

	int						m_CurrentSlice;
	wxSlider		 *m_SliceScannerLoadPage;
	wxSlider		 *m_SliceScannerCropPage;
	wxSlider		 *m_SliceScannerBuildPage;

	int						m_CurrentTime;
	wxSlider		 *m_TimeScannerLoadPage;
	wxSlider		 *m_TimeScannerCropPage;
	wxSlider		 *m_TimeScannerBuildPage;

	mafTagArray	*m_TagArray;

	double	m_DicomBounds[6];

	int	m_GizmoStatus;
	int	m_SideToBeDragged;

	bool	m_BoxCorrect;
	bool	m_CropFlag;
	bool	m_CroppedExetuted; //<<<To check if a crop as been executed

  int m_ResampleFlag;

	mafVMEImage				*m_Image;
	mafVMEVolumeGray	*m_Volume;

	mafGUICheckListBox *m_DicomModalityListBox;

	~medOpImporterDicomOffisToMesh();
};

//----------------------------------------------------------------------------
// medOpImporterDicomOffisToMeshToMesh :
//----------------------------------------------------------------------------
class medOpImporterDicomOffisToMeshToMesh
{
public:
	medOpImporterDicomOffisToMeshToMesh() 
	{
		m_SliceFilename = "";
		m_Pos[0] = -9999;
		m_Pos[1] = -9999;
		m_Pos[2] = -9999;
		m_ImageNumber = -1;
		m_TriggerTime = -1.0;
		m_NumberOfImages = -1;
	};

	medOpImporterDicomOffisToMeshToMesh(mafString filename,double coord[3], vtkImageData *data ,int imageNumber=-1, int numberOfImages=-1, double trigTime=-1.0)  
	{
		m_SliceFilename = filename;
		m_Pos[0] = coord[0];
		m_Pos[1] = coord[1];
		m_Pos[2] = coord[2];
		m_ImageNumber = imageNumber;
		m_NumberOfImages = numberOfImages;
		m_TriggerTime = trigTime;
		vtkNEW(m_Data);
		m_Data->DeepCopy(data);
	};

	~medOpImporterDicomOffisToMeshToMesh() {vtkDEL(m_Data);};

	/** Add the filename and the image coordinates to the list. */
	void SetListElement(mafString filename,double coord[3], int imageNumber=-1, int numberOfImages=-1, double trigTime=-1.0) 
	{
		m_SliceFilename = filename; 
		m_Pos[0] = coord[0];
		m_Pos[1] = coord[1];
		m_Pos[2] = coord[2];
		m_ImageNumber = imageNumber;
		m_NumberOfImages = numberOfImages;
		m_TriggerTime = trigTime;
	};

	/** Return the filename of the corresponding dicom slice. */
	const char *GetFileName() const {return m_SliceFilename.GetCStr();};

	/**	Return the Coordinate along a specified axes of the dicom slice	*/
	double	GetCoordinate(int i) const {return m_Pos[i];};

	/** Return the image number of the dicom slice*/
	int GetImageNumber() const {return m_ImageNumber;};

	/** Return the image number of the dicom slice*/
	int GetNumberOfImages() const {return m_NumberOfImages;};

	/** Return the trigger time of the dicom slice*/
	int GetTriggerTime() const {return m_TriggerTime;};

	vtkImageData* GetOutput(){return m_Data;};

	void GetSliceLocation(double pos[3]){pos[0]=m_Pos[0];pos[1]=m_Pos[1];pos[2]=m_Pos[2];};

protected:
	double m_Pos[3];
	mafString m_SliceFilename;

	double m_TriggerTime;
	int m_ImageNumber;
	int m_NumberOfImages;

	vtkImageData *m_Data;

};
#endif