/*!
  \file   SmartLaplacianSmoother.cpp
  \brief  

  The SmartLaplacianSmoother Class is the concrete class
  that performs Laplacian Smoothing

  \author Thomas Leurent
  \date   2002-01-17
*/

#include "SmartLaplacianSmoother.hpp"

#include "TSTT_C.h"

using namespace Mesquite;


#undef __FUNC__
#define __FUNC__ "SmartLaplacianSmoother::SmartLaplacianSmoother" 
SmartLaplacianSmoother::SmartLaplacianSmoother(const char* quality_measure)
{
  this->set_name("SmartLaplacianSmoother");
  strcpy(qualityMeasure, quality_measure);
}  
  
  
#undef __FUNC__
#define __FUNC__ "SmartLaplacianSmoother::initialize" 
void SmartLaplacianSmoother::initialize(PatchData &pd, MsqError &err)
{
  cout << "- Executing SmartLaplacianSmoother::initialize()\n";
}

#undef __FUNC__
#define __FUNC__ "SmartLaplacianSmoother::initialize_mesh_iteration" 
void SmartLaplacianSmoother::initialize_mesh_iteration(PatchData &pd, MsqError &err)
{
  cout << "- Executing SmartLaplacianSmoother::initialize_mesh_iteration()\n";
}
  
#undef __FUNC__
#define __FUNC__ "SmartLaplacianSmoother::optimize_nodes_positio" 
void SmartLaplacianSmoother::optimize_nodes_position(PatchData &patch_data,
                                                     MsqError &err)
{
  cout << "- Executing SmartLaplacianSmoother::optimize_nodes_position()\n";
  cout << "  quality measure: " << qualityMeasure << endl;
}
  
#undef __FUNC__
#define __FUNC__ "SmartLaplacianSmoother::terminate_mesh_iteration" 
void SmartLaplacianSmoother::terminate_mesh_iteration(PatchData &pd, MsqError &err)
{
  cout << "- Executing SmartLaplacianSmoother::terminate_mesh_iteration()\n";
}
  
#undef __FUNC__
#define __FUNC__ "SmartLaplacianSmoother::cleanup" 
void SmartLaplacianSmoother::cleanup()
{
  cout << "- Executing SmartLaplacianSmoother::cleanup()\n";
}
