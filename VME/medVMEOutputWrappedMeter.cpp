/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: medVMEOutputWrappedMeter.cpp,v $
  Language:  C++
  Date:      $Date: 2007-08-20 13:47:36 $
  Version:   $Revision: 1.1 $
  Authors:   Daniele Giunchi
==========================================================================
  Copyright (c) 2001/2005 
  CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/


#include "mafDefines.h" 
//----------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//----------------------------------------------------------------------------

#include "medVMEOutputWrappedMeter.h"
#include "medVMEWrappedMeter.h"
#include "mmgGui.h"

#include <assert.h>

//-------------------------------------------------------------------------
mafCxxTypeMacro(medVMEOutputWrappedMeter)
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
medVMEOutputWrappedMeter::medVMEOutputWrappedMeter()
//-------------------------------------------------------------------------
{
	m_MiddlePoints.push_back(mafString()); //first middlepoint
	m_MiddlePoints.push_back(mafString()); //last middlepoint
}

//-------------------------------------------------------------------------
medVMEOutputWrappedMeter::~medVMEOutputWrappedMeter()
//-------------------------------------------------------------------------
{
}
//-------------------------------------------------------------------------
mmgGui *medVMEOutputWrappedMeter::CreateGui()
//-------------------------------------------------------------------------
{
  assert(m_Gui == NULL);
  m_Gui = mafVMEOutput::CreateGui();

  m_Distance = ((medVMEWrappedMeter *)m_VME)->GetDistance();
  m_Gui->Label(_("distance: "), &m_Distance, true);

	double *coordinateFIRST = ((medVMEWrappedMeter *)m_VME)->GetMiddlePointCoordinate(0);
	double *coordinateLAST = ((medVMEWrappedMeter *)m_VME)->GetMiddlePointCoordinate(((medVMEWrappedMeter *)m_VME)->GetNumberMiddlePoints()-1);
	if(coordinateFIRST != NULL)
	  m_MiddlePoints[0] = wxString::Format("%.2f %.2f %.2f", coordinateFIRST[0], coordinateFIRST[1], coordinateFIRST[2]);
	if(coordinateLAST != NULL)
	  m_MiddlePoints[m_MiddlePoints.size()-1] = wxString::Format("%.2f %.2f %.2f", coordinateLAST[0], coordinateLAST[1], coordinateLAST[2]);

	m_Gui->Label(_("first mp:"), &m_MiddlePoints[0], true);
	m_Gui->Label(_("last mp:"), &m_MiddlePoints[m_MiddlePoints.size()-1], true);

  m_Angle = ((medVMEWrappedMeter *)m_VME)->GetAngle();
  m_Gui->Label(_("angle: "), &m_Angle, true);
	m_Gui->Divider();

  return m_Gui;
}
//-------------------------------------------------------------------------
void medVMEOutputWrappedMeter::Update()
//-------------------------------------------------------------------------
{
  assert(m_VME);
  m_VME->Update();

  if(((medVMEWrappedMeter *)m_VME)->GetMeterMode() == medVMEWrappedMeter::POINT_DISTANCE)
  {
		m_Distance = ((medVMEWrappedMeter *)m_VME)->GetDistance();

		double *coordinateFIRST = ((medVMEWrappedMeter *)m_VME)->GetMiddlePointCoordinate(0);
		double *coordinateLAST = ((medVMEWrappedMeter *)m_VME)->GetMiddlePointCoordinate(((medVMEWrappedMeter *)m_VME)->GetNumberMiddlePoints()-1);
		if(coordinateFIRST != NULL)
			m_MiddlePoints[0] = wxString::Format("%.2f %.2f %.2f", coordinateFIRST[0], coordinateFIRST[1], coordinateFIRST[2]);
		if(coordinateLAST != NULL)
			m_MiddlePoints[m_MiddlePoints.size()-1] = wxString::Format("%.2f %.2f %.2f", coordinateLAST[0], coordinateLAST[1], coordinateLAST[2]);

		m_Angle ="";
  }
	else if(((medVMEWrappedMeter *)m_VME)->GetMeterMode() == medVMEWrappedMeter::LINE_DISTANCE)
	{
		m_Distance = ((medVMEWrappedMeter *)m_VME)->GetDistance();
		m_Angle ="";
	}
  else if(((medVMEWrappedMeter *)m_VME)->GetMeterMode() == medVMEWrappedMeter::LINE_ANGLE)
  {
    m_Distance ="";
    m_Angle= ((medVMEWrappedMeter *)m_VME)->GetAngle();
  }
  if (m_Gui)
  {
    m_Gui->Update();
  }
}