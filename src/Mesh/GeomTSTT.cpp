/* ***************************************************************** 
    MESQUITE -- The Mesh Quality Improvement Toolkit

    Copyright 2004 Lawrence Livermore National Laboratory.  Under 
    the terms of Contract B545069 with the University of Wisconsin -- 
    Madison, Lawrence Livermore National Laboratory retains certain
    rights in this software.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License 
    (lgpl.txt) along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
    kraftche@cae.wisc.edu    
   
  ***************************************************************** */

/*!
  \file   GeomTSTT.cpp
  \brief  


  \author Jason Kraftcheck
  \date   2005-01-13
*/

#include <sidl_cxx.hh>
#include "TSTT.hh"
#include "TSTTM.hh"
#include "TSTTR.hh"
#include "TSTTG.hh"
#include "GeomTSTT.hpp"
#include "MsqDebug.hpp"
#include "MsqVertex.hpp"
#include "MsqError.hpp"
#include "TSTTUtil.hpp"

namespace Mesquite
{

class GeomTSTTImpl : public GeomTSTT
{
public:

  GeomTSTTImpl( TSTTG::Geometry& geom,
                TSTTM::Mesh& mesh, 
                TSTTR::Relate& relate ) throw( TSTT::Error );

  virtual ~GeomTSTTImpl();

  void snap_to( Mesh::EntityHandle entity_handle,
                Vector3D& coordinat ) const;

  void normal_at( Mesh::EntityHandle entity_handle,
                  Vector3D& coordinate ) const;

protected:

  void* geom_from_mesh( void* handle ) const throw( TSTT::Error );
  
  void move_to( void* geom_handle, Vector3D& coord ) const throw( TSTT::Error );
  void normal ( void* geom_handle, Vector3D& coord ) const throw( TSTT::Error );

private:

  mutable TSTTG::Shape  geomIface;
  mutable TSTTM::Mesh   meshIface;
  mutable TSTTR::Relate relateIface;
  
  mutable sidl::array<void*> oneGeomHandle, oneMeshHandle;
  mutable sidl::array<double> oneVectorIn, oneVectorOut;
};


GeomTSTT* GeomTSTT::create( TSTTG::Geometry& geom,
                            TSTTM::Mesh& mesh,
                            TSTTR::Relate& relate,
                            MsqError& err )
{
  try {
    return new GeomTSTTImpl( geom, mesh, relate );
  }
  catch (TSTT::Error& tstt_err ) {
    MSQ_SETERR(err)(process_tstt_error(tstt_err),MsqError::INTERNAL_ERROR);
  }
  return 0;
}
  

GeomTSTT::~GeomTSTT() {}


GeomTSTTImpl::GeomTSTTImpl( TSTTG::Geometry& geom,
                            TSTTM::Mesh& mesh,
                            TSTTR::Relate& relate ) 
                            throw ( TSTT::Error )
  : geomIface( geom ), 
    meshIface(mesh), 
    relateIface( relate ),
    oneGeomHandle( alloc_sidl_vector<void*>(1) ),
    oneMeshHandle( alloc_sidl_vector<void*>(1) ),
    oneVectorIn ( alloc_sidl_vector<double>(3) ),
    oneVectorOut( alloc_sidl_vector<double>(3) )
{
}

GeomTSTTImpl::~GeomTSTTImpl() {}


void GeomTSTTImpl::snap_to( Mesh::EntityHandle handle,
                            Vector3D& coordinate ) const
{
  try {
    void* geom = geom_from_mesh( (void*)handle ); 
    if (geom)
      move_to( geom, coordinate );
  }
  catch (TSTT::Error& tstt_err ) {
    process_tstt_error(tstt_err);
  }
}

void GeomTSTTImpl::normal_at( Mesh::EntityHandle handle,
                              Vector3D& coordinate ) const
{
  try {
    void* geom = geom_from_mesh( (void*)handle );
    if (geom)
      normal( geom, coordinate );
  }
  catch (TSTT::Error& tstt_err ) {
    process_tstt_error(tstt_err);
  }
}

void* GeomTSTTImpl::geom_from_mesh( void* mesh_ent_handle ) const
                                    throw ( TSTT::Error )
{
  int junk;
  oneMeshHandle.set( 0, mesh_ent_handle );
  relateIface.getMeshRelatedEntities( &geomIface,
                                      &meshIface,
                                      oneMeshHandle, 1,
                                      oneGeomHandle, junk );
  return oneGeomHandle.get(0);
}

void GeomTSTTImpl::move_to( void* geom, Vector3D& coord ) const
                            throw ( TSTT::Error )
{
  oneVectorIn.set( 0, coord[0] );
  oneVectorIn.set( 1, coord[1] );
  oneVectorIn.set( 2, coord[2] );
  oneGeomHandle.set( 0, geom );

  int junk;
  geomIface.gentityClosestPoint( oneGeomHandle, 1,
                                 oneVectorIn,   3,
                                 oneVectorOut, junk );
  
  coord[0] = oneVectorOut.get(0);
  coord[1] = oneVectorOut.get(1);
  coord[2] = oneVectorOut.get(2);
}

 
 
void GeomTSTTImpl::normal( void* geom, Vector3D& coord ) const
                            throw ( TSTT::Error )
{
  oneVectorIn.set( 0, coord[0] );
  oneVectorIn.set( 1, coord[1] );
  oneVectorIn.set( 2, coord[2] );
  oneGeomHandle.set( 0, geom );

  int junk;
  geomIface.gentityNormal( oneGeomHandle, 1,
                           oneVectorIn,   3,
                           oneVectorOut, junk );
  
  coord[0] = oneVectorOut.get(0);
  coord[1] = oneVectorOut.get(1);
  coord[2] = oneVectorOut.get(2);
}

} // namespace Mesquite
