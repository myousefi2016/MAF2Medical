/*==============================================================================

Program:   Multimod Application Framework
Module:    $RCSfile: vtkMAFMeshCutter_BES.h,v $
Language:  C++
Date:      $Date: 2009-05-13 15:51:38 $
Version:   $Revision: 1.1.2.1 $
Authors:   Nigel McFarlane

================================================================================
Copyright (c) 2007 University of Bedfordshire, UK (www.beds.ac.uk)
All rights reserved.
===============================================================================*/


#ifndef __vtkMAFMeshCutter_h
#define __vtkMAFMeshCutter_h

//---------------------------------------------
// includes:
//---------------------------------------------
#include "vtkUnstructuredGridToPolyDataFilter.h"
#include "vtkMAFConfigure.h"
#include "assert.h"
#include <vector>
#include <map>

#include "vtkPlane.h"

//---------------------------------------------
// class forward:
//---------------------------------------------
class vtkIdList;
class vtkCell;

/** vtkMAFMeshCutter_BES - vtk filter which cuts a finite element mesh (unstructured grid) with a plane.
This is very similar to vtkCutter().

Differences from vtkCutter():
1) vtkMAFMeshCutter_BES() returns polygons which correspond to the mesh cells, eg a slice
through the center of a cube might return a square.  In vtkCutter() this would
be subdivided into triangles.
2) Public methods have been provided to map the output points and cells back to the input mesh.
3) Integer scalars are rounded, not truncated to next-lowest integer.
4) There is no contouring, ie multiple slices.

Special cases:
1) It is possible for a slice through a non-convex cell to create a hole.
The class cannot currently deal with this, and will return an error.
2) Edges which are exactly in the plane are not included in the list of
edges cut by the plane, although their endpoints are.
3) No cells of lower order than triangles are created.
Therefore if the plane cuts exactly through an isolated edge or vertex, the output
polydata will contain the points, but no cell will be created.*/
class VTK_vtkMAF_EXPORT vtkMAFMeshCutter_BES : public vtkUnstructuredGridToPolyDataFilter
{
public:
  vtkTypeRevisionMacro(vtkMAFMeshCutter_BES,vtkUnstructuredGridToPolyDataFilter);
  static vtkMAFMeshCutter_BES *New() ;
  void PrintSelf(ostream& os, vtkIndent indent);                                ///< print self

   /** Overload standard modified time function. If cut function is modified,
  then this object is modified as well. */
  unsigned long GetMTime();

  void SetCutFunction(vtkPlane *P) ;                                            ///< Set the cutting plane (but does not register the object)
  vtkPlane* GetCutFunction() ;                                                  ///< Get the cutting plane

  /** Get the output point idout corresponding to the input edge (id0,id1). 
  Lambda returns the fractional distance between id0 and id1. 
  Returns true if the edge exists and was cut by the plane. 
  NB this will not find edges which lie exactly in the plane. */
  bool GetOutputPointWhichCutsEdge(vtkIdType id0, vtkIdType id1, vtkIdType *idout, double *lambda) const ;

  /** Get the output point idout corresponding to the single input point id0. 
  Returns true if the input point exists and was intersected exactly by the plane. */
  bool GetOutputPointWhichCutsPoint(vtkIdType id0, vtkIdType *idout) const ;

  /** Get the input edge (id0,id1) corresponding to the point idout. 
  Lambda returns the fractional distance between id0 and id1. */
  inline bool GetInputEdgeCutByPoint(vtkIdType idout, vtkIdType *id0, vtkIdType *id1, double *lambda) const ;

  /** Get the single input point id0 corresponding to the point idout. */
  inline bool GetInputPointCutByPoint(vtkIdType idout, vtkIdType *id0) const ;

  /** Get the input cell corresponding to the output cell. */
  inline vtkIdType GetInputCellCutByOutputCell(vtkIdType idout) ;

  /** Get the output cell corresponding to the input cell.
  Returns true if the input id was found. */
  bool GetOutputCellWhichCutsInputCell(vtkIdType idin, vtkIdType *idout) ;


  /** initialize the cutter */
  void Initialize() ;

protected:
  vtkMAFMeshCutter_BES() ;                                                              ///< constructor
  ~vtkMAFMeshCutter_BES() ;                                                             ///< destructor

  void Execute();                                                               ///< execute method


  // edge described by id's of endpoints
  typedef struct{
    vtkIdType id0 ;   // id's of endpoints
    vtkIdType id1 ;    
  } Edge ;

  /** type of intersection made by cutting line with plane */
  enum intersection_type {
    NO_INTERSECTION = 0,    // no intersection
    INTERSECTS_LINE,        // single intersection with line
    INTERSECTS_POINT0,      // intersects line at endpoint 0 (ie lambda = 0)
    INTERSECTS_POINT1,      // intersects line at endpoint 1 (ie lambda = 1)
    LINE_IN_PLANE          // line lies in plane
  } ;

  /** type of mapping between output point and input mesh */
  enum mapping_type {
    NO_MAPPING = 0,
    POINT_TO_EDGE,
    POINT_TO_POINT
  } ;

  // constant for undefined id's
  static const vtkIdType undefinedId = -1 ;

  /** Computes a unique key for the given edge */
  inline unsigned long long GetEdgeKey(const Edge& edge) const {
    return GetEdgeKey(edge.id0, edge.id1);
  }

  /** computes a unique key for the given edge */
  inline unsigned long long GetEdgeKey(vtkIdType id0, vtkIdType id1) const;

  /** Add set of id's to the edge mapping table.
  This is a POINT_TO_EDGE mapping
  This maps output point idout to input edge */
  inline void AddMapping(vtkIdType idout, const Edge& edge, double lambda) ;

  /** Add set of id's to the edge mapping table.
  This is a POINT_TO_POINT mapping
  This maps output point idout to single input point id0 */
  inline void AddMapping(vtkIdType idout, vtkIdType id0, double lambda) ;

  /** Get intersection of line with plane
  Line is defined by coords of endpoints (p0, p1).
  Plane is defined by origin and normal.
  Returns intersection type (see enum)
  lambda returns fractional distance of interpolated point along edge (0 <= lambda <= 1). */
  int GetIntersectionOfLineWithPlane(const double *p0, const double *p1, const double *origin, const double *norm, 
    double *coords, double *lambda) const ;

  /** Get intersection of edge with plane
  Returns intersection type (see enum)
  lambda returns fractional distance of interpolated point along edge (0 <= lambda <= 1). */
  inline int GetIntersectionOfEdgeWithPlane(const Edge& edge, double *coords, double *lambda) const ;

  /** Get list of cells which are adjoined to point */
  void GetCellNeighboursOfPoint(vtkIdType idpt, vtkIdList *list) const ;

  /** Get list of cells which are adjoined to edge */
  void GetCellNeighboursOfEdge(const Edge& edge, vtkIdList *list) const ;

  /** Find where the edges cross the plane and create points */
  void FindPointsInPlane() ;

  /** Get the list of input cells which are attached to the output point */
  void GetInputCellsOnOutputPoint(vtkIdType idout, vtkIdList *cellids) const ;

  /** Create and fill table of cells.
  // There is an entry for every input cell.
  // Entry i is the list of output points in input cell i */
  void AssignPointsToCells() ;

  /** Are all the point ids in the list members of this face
  Undefined id's are ignored, eg if the list is {1, 3, -1} and the face is {1, 3, 10, 11}, the result is true */
  bool AllIdsInFace(vtkCell *face, vtkIdList *idlist) ;

  /** Find a face containing all id's in the list
  Undefined id's are ignored, ie the result can still be true if some of the id's are undefined */
  bool FindFaceContainingAllIds(vtkCell *cell, vtkIdList *idlist, vtkIdType *faceid) ;

  /** Construct the polygonal slice through the cell */
  bool ConstructCellSlicePolygon(vtkIdType cellid, vtkIdList *idlist) ;

  /** calculate the normal of the output polygon, given the list of point id's */
  void CalculatePolygonNormal(vtkIdList *idlist, double *norm) ;

  /** Interpolate two scalar tuples
  tupout = (1-lambda)*tup0 + lambda*tup1 */
  inline void InterpolateScalars(double *tup0, double *tup1, double *tupout, double lambda, int ncomponents, int dattype) ;

  /** transfer the scalars by interpolation from input to output */
  void TransferScalars() ;  

  /** do the whole thing */
  void CreateSlice() ;

  /** computes the intersection of the given plane with the mesh bounding box
  returns coordinates of the first intersection in pts, returns false, if the bounding box is not intersected*/
  bool GetIntersectionOfBoundsWithPlane(const double *origin, const double *norm, double* pts);

  /** gets the first cell intersected by the current plane
  the search starts with cells sharing the given point*/
  vtkIdType GetFirstIntersectedCell(vtkIdType ptId);

  // This table maps each output point to the input points or point which created it.
  // if mtype = POINT_TO_POINT this maps the point idout to the intersected point id0
  // if   "   = POINT_TO_EDGE   "   "     "    "   idout  "  "  intersected edge (id0,id1)
  typedef struct{
    vtkIdType idout ;    // id of point in output polydata
    vtkIdType id0 ;      // id's of corresponding input points
    vtkIdType id1 ;     
    double lambda ;      // fractional distance of interpolated point along edge
    mapping_type mtype ; // mapping is point-to-edge or point-to-point
  } EdgeMapping ;
  std::vector<EdgeMapping> m_edgeMapping ;
  
  typedef std::map<unsigned long long, int> InvEdgeMapping;
  InvEdgeMapping m_invEdgeMapping;    //<maps edges keys to index of edge in m_edgeMapping
  

  // This is a list of the input cells which have been touched by the plane.
  // NB this includes some grazing incidence cells which do not create any output polygons,
  // so don't use it to map input and output cells.
  std::vector<vtkIdType> m_intersectedCells ;

  // This is a list of the output point id's in EVERY input cell, including all the empty ones.
  // It is a list of lists.
  //typedef std::vector<vtkIdType> IdList;
  std::vector<vtkIdType>* m_pointsInCells ;

  // This is a mapping from the output cells to the input cells: 
  // cellid_in = m_cellMapping[cellid_out]
  // It is set in CreateSlice()
  std::vector<vtkIdType>m_cellMapping ;

  // cutting function
  vtkPlane *m_cutFunction ;

  // input and output
  vtkUnstructuredGrid *m_unstructGrid ;
  vtkPolyData *m_polydata ;

  //points coordinates (to speed up the processing)
  double* m_PointsCoords;       //<data of points (in doubles)  
  bool m_bReleasePointsCoords;  //<false if the array m_PointsData may not be released

  vtkUnstructuredGrid* m_LastInput;     //<stored last processed input
  unsigned long m_LastInputTimeStamp;   //<timestamp for last input

  vtkIdList* m_idlist0;   //<GetCellNeighboursOfEdge list
  vtkIdList* m_idlist1;   //<GetCellNeighboursOfEdge list
  vtkIdList* m_ptlist;    //<ConstructCellSlicePolygon list
} ;

//------------------------------------------------------------------------------
// Add set of id's to the edge mapping table
// This is a POINT_TO_EDGE mapping
// This maps output point idout to input edge (id0,id1) 
inline void vtkMAFMeshCutter_BES::AddMapping(vtkIdType idout, const Edge& edge, double lambda)
//------------------------------------------------------------------------------
{
  EdgeMapping em = {idout, edge.id0, edge.id1, lambda, POINT_TO_EDGE} ;
  m_edgeMapping.push_back(em);

  m_invEdgeMapping.insert(InvEdgeMapping::value_type(GetEdgeKey(edge), m_edgeMapping.size() - 1));
}

//------------------------------------------------------------------------------
// Add set of id's to the edge mapping table
// this is a POINT_TO_POINT mapping
// This maps output point idout to single input point id0
inline void vtkMAFMeshCutter_BES::AddMapping(vtkIdType idout, vtkIdType id0, double lambda)
//------------------------------------------------------------------------------
{  
  EdgeMapping em = {idout, id0, undefinedId, lambda, POINT_TO_POINT} ;
  m_edgeMapping.push_back(em) ;
  
  m_invEdgeMapping.insert(InvEdgeMapping::value_type(id0, m_edgeMapping.size() - 1));
}

//------------------------------------------------------------------------
//computes a unique key for the given edge
inline unsigned long long vtkMAFMeshCutter_BES::GetEdgeKey(vtkIdType id0, vtkIdType id1) const
//------------------------------------------------------------------------
{
  unsigned long long key;
  unsigned long* pkey = (unsigned long*)&key;
  if (id0 < id1) {
    pkey[0] = id0; pkey[1] = id1;
  }
  else {
    pkey[0] = id1; pkey[1] = id0;
  }

  return key;
}

//------------------------------------------------------------------------------
// Find the input edge (id0,id1) corresponding to the output point idout
// This returns true if the output point is in the table
inline bool vtkMAFMeshCutter_BES::GetInputEdgeCutByPoint(vtkIdType idout, vtkIdType *id0, vtkIdType *id1, double *lambda) const
//------------------------------------------------------------------------------
{
  //RELEASE NOTE: as AddMapping is called in a pair with InsertNextPoint in the current version,
  //idout is the index into m_edgeMapping, thus we do not need search for it
  assert(idout >= 0 && idout < (int)m_edgeMapping.size());
  const EdgeMapping& edge = m_edgeMapping[idout];
  if (edge.mtype != POINT_TO_EDGE)
    return false;

  assert(edge.idout == idout);

  *id0 = edge.id0 ;
  *id1 = edge.id1 ;
  *lambda = edge.lambda ;
  return true;
}

//------------------------------------------------------------------------------
// Find the single input point id0 corresponding to the output point idout
// This returns true if the the input point is in the table
inline bool vtkMAFMeshCutter_BES::GetInputPointCutByPoint(vtkIdType idout, vtkIdType *id0) const
//------------------------------------------------------------------------------
{
  //RELEASE NOTE: as AddMapping is called in a pair with InsertNextPoint in the current version,
  //idout is the index into m_edgeMapping, thus we do not need search for it
  assert(idout >= 0 && idout < (int)m_edgeMapping.size());
  const EdgeMapping& edge = m_edgeMapping[idout];
  if (edge.mtype != POINT_TO_POINT)
    return false;

  assert(edge.idout == idout);

  *id0 = edge.id0 ;  
  return true;  
}


//------------------------------------------------------------------------------
// Get the input cell corresponding to the output cell
inline vtkIdType vtkMAFMeshCutter_BES::GetInputCellCutByOutputCell(vtkIdType idout)
//------------------------------------------------------------------------------
{  
  assert(idout >= 0 && idout < (int)m_cellMapping.size());
  return m_cellMapping[idout] ;
}

//------------------------------------------------------------------------------
// Get intersection of edge with plane
// Edge is defined by id's of endpoints (id0, id1).
// Plane is defined by origin and normal.
// Returns type of intersection.
// lambda returns fractional distance of interpolated point along edge (0 <= lambda <= 1).
inline int vtkMAFMeshCutter_BES::GetIntersectionOfEdgeWithPlane(const Edge& edge, double *coords, double *lambda) const
//------------------------------------------------------------------------------
{
  return GetIntersectionOfLineWithPlane(&m_PointsCoords[3*edge.id0], 
    &m_PointsCoords[3*edge.id1], m_cutFunction->GetOrigin(), 
    m_cutFunction->GetNormal(), coords, lambda) ;
}

//------------------------------------------------------------------------------
// Interpolate two scalar tuples
// tupout = (1-lambda)*tup0 + lambda*tup1
// If the data type is not float or double, we add 0.5 to ensure correct rounding when it is converted back to int.
inline void vtkMAFMeshCutter_BES::InterpolateScalars(double *tup0, double *tup1, double *tupout, double lambda, int ncomponents, int dattype)
//------------------------------------------------------------------------------
{ 
  for (int j = 0 ;  j < ncomponents ;  j++)
    tupout[j] = (1.0 - lambda)*tup0[j] + lambda*tup1[j] ;

  if (dattype != VTK_FLOAT && dattype != VTK_DOUBLE){
    // the real data type of the scalars is integer, so add 0.5 to ensure correct rounding when they are put back into the polydata
    for (int j = 0 ;  j < ncomponents ;  j++)
      tupout[j] += 0.5 ;
  }
}
#endif