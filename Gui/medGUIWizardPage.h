/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: medGUIWizardPage.h,v $
Language:  C++
Date:      $Date: 2007-09-25 14:20:27 $
Version:   $Revision: 1.1 $
Authors:   Matteo Giacomoni
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
#ifndef __medGUIWizardPage_H__
#define __medGUIWizardPage_H__
//----------------------------------------------------------------------------
// Include:
//----------------------------------------------------------------------------
#include "wx/wizard.h"
#include "mafEvent.h"
#include "mafObserver.h"
#include "mafRWI.h"

//----------------------------------------------------------------------------
// forward references :
//----------------------------------------------------------------------------
class medGUIWizard;
class mmgGui;

//----------------------------------------------------------------------------
// Const:
//----------------------------------------------------------------------------
enum DIALOG_EXSTYLES
{
	medUSEGUI = 1,
	medUSERWI = 2,
};

//----------------------------------------------------------------------------
// medGUIWizardPage :
//----------------------------------------------------------------------------
/**
*/
class medGUIWizardPage : public wxWizardPageSimple, public mafObserver  
{
public:
	medGUIWizardPage (medGUIWizard *wizardParent,long style = medUSEGUI | medUSERWI,wxString label="");
	virtual ~medGUIWizardPage (); 
	void SetListener(mafObserver *Listener) {m_Listener = Listener;};
	void OnEvent(mafEventBase *maf_event);

	mafObserver *m_Listener;

	void AddGui(mmgGui *gui);

	void AddSizerToRWI(wxSizer *sizer){m_RwiSizer->Add(sizer, 0, wxEXPAND);SetSizer(m_PreviewSizer,true);m_PreviewSizer->Fit(this);};

	/** Create a chain between this page ad nextPage */
	void SetNextPage(medGUIWizardPage *nextPage);

	mafRWI* GetRWI(){return m_Rwi;};

	mmgGui     *m_Gui; ///< Gui variable used to plug custom widgets
	wxBoxSizer *m_RwiSizer; ///< Sizer used for the vtk render window and if you want to plug any gui on bottom of the RWI

private:

	wxWizardPageSimple *m_FirstPage;

	wxBoxSizer *m_PreviewSizer; ///< Sizer used for the preview render window
	mafRWI     *m_Rwi; ///< Render window

	//DECLARE_EVENT_TABLE()
};
#endif