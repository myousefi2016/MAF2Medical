/*=========================================================================
Program:   VPH2
Module:    $RCSfile: mafDeviceButtonsPadMouseDialog.h,v $
Language:  C++
Date:      $Date: 2009-07-01 08:34:07 $
Version:   $Revision: 1.1.2.1 $
Authors:   Alberto Losi
==========================================================================
Copyright (c) 2008
SCS s.r.l. - BioComputing Competence Centre (www.scsolutions.it - www.b3c.it)
=========================================================================*/
#ifndef __mafDeviceButtonsPadMouseDialog_h
#define __mafDeviceButtonsPadMouseDialog_h

#include "mafDeviceButtonsPadMouse.h"

//----------------------------------------------------------------------------
// forward declarations
//----------------------------------------------------------------------------
class mafDeviceButtonsPadMouse;
class mafView;

/**
Add SetView method to mafDeviceButtonsPadMouse class to directly set a view to a mouse object.
This class avoid the following problem that occurs trying to use a mafDeviceButtonsPadMouse to
interact with a view plugged inside a modal dialog:
In a standard MAF application to set a view to a mouse object you must use the method
mafEventMacro(mafEvent(this, VIEW_SELECT, View); that rise a VIEW_SELECT event.
Logic's OnEvent method trap this event but ignore the view parameter and use ViewManager
to find the selected view;
Views plugged into modal dialogs are not listed inside the view manager so this method don't
set the desired view.

(An operation using this class is vph2OpAnnulusIdentification)
*/
//----------------------------------------------------------------------------
class mafDeviceButtonsPadMouseDialog : public  mafDeviceButtonsPadMouse
//----------------------------------------------------------------------------
{
  mafTypeMacro(mafDeviceButtonsPadMouseDialog,mafDeviceButtonsPadMouse); 
public:
  /** Set the selected view. */
  void SetView(mafView *view);

protected:
  mafDeviceButtonsPadMouseDialog();
  virtual ~mafDeviceButtonsPadMouseDialog();
};
#endif