/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafPipeSurfaceSlice_BESTest.h,v $
Language:  C++
Date:      $Date: 2009-10-06 08:13:49 $
Version:   $Revision: 1.1.2.1 $
Authors:   Eleonora Mambrini
==========================================================================
Copyright (c) 2002/2008
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafPipeSurfaceSlice_BESTest_H__
#define __CPP_UNIT_mafPipeSurfaceSlice_BESTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

class vtkPolyData;
class vtkRenderer;
class vtkRenderWindow;
class vtkRenderWindowInteractor;
class vtkProp;
class vtkPropCollection;

class mafPipeSurfaceSlice_BESTest : public CPPUNIT_NS::TestFixture
{
public: 
  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  CPPUNIT_TEST_SUITE( mafPipeSurfaceSlice_BESTest );
  CPPUNIT_TEST(TestFixture); // just to test that the fixture has no leaks
  CPPUNIT_TEST( TestSurfacePipeCreation );
  CPPUNIT_TEST( TestSetGetThickness );
  CPPUNIT_TEST( TestSurfacePipeExecution );
  CPPUNIT_TEST( TestCloudClosePipeExecution );
  CPPUNIT_TEST( TestCloudOpenPipeExecution );

  CPPUNIT_TEST_SUITE_END();

protected:
  void TestFixture();
  /** Test the pipe with a mafVMESurface as input */
  void TestSurfacePipeExecution();
  /** Test the pipe with a close mafVMELandamarkCloud as input */
  void TestCloudClosePipeExecution();
  /** Test the pipe with a open mafVMELandamarkCloud as input */
  void TestCloudOpenPipeExecution();
  /** Test pipe creation. */
  void TestSurfacePipeCreation();
  /** Test Set and Get methods for thickness attribute. */
  void TestSetGetThickness();

  vtkRenderer *m_Renderer;
  vtkRenderWindow *m_RenderWindow;
  vtkRenderWindowInteractor *m_RenderWindowInteractor;

  /**Compare a list of already saved images (control images) with renderized image from render window
  @scalarIndex: index X of the image. Original Image is imageX.jpg, created imaged is compX.jpg
  */
  void CompareImages(int scalarIndex = 0);

  /** Select The Actor that will be controlled*/
  vtkProp *SelectActorToControl(vtkPropCollection* propList, int index);
};


int main( int argc, char* argv[] )
{
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that collects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( mafPipeSurfaceSlice_BESTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

#endif