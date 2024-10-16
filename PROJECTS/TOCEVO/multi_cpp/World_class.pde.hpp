/// @file
#pragma once
/// @date 2024-10-15 (last modification)
#ifndef HEADER_World_INCLUDED
#define HEADER_World_INCLUDED

#include "Agent_class.pde.hpp"

/// World is a one of two central class of each ABM model.
/// @details 
///         We have two layer - environment resources cells and agents. 
///         

/// @note Automatically extracted definition of `class`: World
class World: public virtual Object{
  public:

  smatrix<int>     cells;  //!< Two dimensional array of resources
  smatrix<pAgent>   agents; //!< Two dimensional array of agents
  
  World(int side)     //!< Constructor of the World
  {
    cells=new matrix<int>(side,side);
    agents=new matrix<pAgent>(side,side);
  }
};

/// Generated by Processing2C++ extraction Tools
#endif //HEADER_World_INCLUDED

//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

