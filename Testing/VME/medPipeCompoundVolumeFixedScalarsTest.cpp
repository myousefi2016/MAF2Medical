/*=========================================================================

 Program: MAF2Medical
 Module: medPipeCompoundVolumeFixedScalarsTest
 Authors: Eleonora Mambrini
 
 Copyright (c) B3C
 All rights reserved. See Copyright.txt or
 http://www.scsitaly.com/Copyright.htm for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "medDefines.h" 
//----------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//----------------------------------------------------------------------------

#include <cppunit/config/SourcePrefix.h>
#include "medPipeCompoundVolumeFixedScalars.h"
#include "medPipeCompoundVolumeFixedScalarsTest.h"
#include "mafSceneNode.h"
#include "medGUIDynamicVP.h"

#include "mafVMEVolumeGray.h"


#include <iostream>

class DummyPipeCompoundVolumeFixedScalars : public medPipeCompoundVolumeFixedScalars
{
public:
  mafTypeMacro(DummyPipeCompoundVolumeFixedScalars,medPipeCompoundVolumeFixedScalars);
  DummyPipeCompoundVolumeFixedScalars(){}
  void Create(mafSceneNode *n);
protected:
  // redefinition for avoiding gui components
  mafGUI *CreateGui() {return NULL;}
  void    UpdateGUILayout(bool bForce){}
  void    CreatePageGroups(){}
};

//----------------------------------------------------------------------------
void DummyPipeCompoundVolumeFixedScalars::Create(mafSceneNode *n)
//----------------------------------------------------------------------------
{
  //remove wxCursor busy;

  mafPipe::Create(n);
  m_SceneNode = n; 

  //creates description of groups
  CreatePageGroups();

  //creates initial pages for each group
  CreatePages();

  //AddActor();
}

//----------------------------------------------------------------------------
mafCxxTypeMacro(DummyPipeCompoundVolumeFixedScalars);
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void medPipeCompoundVolumeFixedScalarsTest::TestFixture()
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
void medPipeCompoundVolumeFixedScalarsTest::setUp()
//----------------------------------------------------------------------------
{

}
//----------------------------------------------------------------------------
void medPipeCompoundVolumeFixedScalarsTest::tearDown()
//----------------------------------------------------------------------------
{

}

//----------------------------------------------------------------------------
void medPipeCompoundVolumeFixedScalarsTest::TestAllocation()
//----------------------------------------------------------------------------
{
  DummyPipeCompoundVolumeFixedScalars *pipe = new DummyPipeCompoundVolumeFixedScalars;
  mafDEL(pipe);
}
//----------------------------------------------------------------------------
void medPipeCompoundVolumeFixedScalarsTest::TestCreateSceneNode()
//----------------------------------------------------------------------------
{
  mafVMEVolumeGray *volume;
  mafNEW(volume);

  //Assembly will be create when instancing mafSceneNode
  mafSceneNode *sceneNode;
  sceneNode = new mafSceneNode(NULL,NULL,volume, NULL);

  /////////// Pipe Instance and Creation ///////////
  DummyPipeCompoundVolumeFixedScalars *pipe = new DummyPipeCompoundVolumeFixedScalars;
  pipe->Create(sceneNode);

  delete pipe;
  delete sceneNode;
  mafDEL(volume);

  delete wxLog::SetActiveTarget(NULL);
}

//----------------------------------------------------------------------------
void medPipeCompoundVolumeFixedScalarsTest::TestGetCurrentScalarVisualPipe()
//----------------------------------------------------------------------------
{

  mafVMEVolumeGray *volume;
  mafNEW(volume);

  //Assembly will be create when instancing mafSceneNode
  mafSceneNode *sceneNode;
  sceneNode = new mafSceneNode(NULL,NULL,volume, NULL);

  /////////// Pipe Instance and Creation ///////////
  DummyPipeCompoundVolumeFixedScalars *pipe = new DummyPipeCompoundVolumeFixedScalars;
  pipe->Create(sceneNode);

  pipe->GetCurrentScalarVisualPipe();

  delete pipe;
  delete sceneNode;
  mafDEL(volume);

}

