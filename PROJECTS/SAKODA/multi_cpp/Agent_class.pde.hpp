/// @file
#pragma once
/// @date 2024-10-15 (last change)
#ifndef HEADER_Agent_INCLUDED
#define HEADER_Agent_INCLUDED

/// @brief Agent with identity and stress.

/// @note Automatically extracted definition of `class`: Agent
class Agent: public virtual Object{
  public:
 

  float identity; //!< pAgent Identity: [1..Number_of_identities]
  float stress;   //!< Stress felt in current position [0..1]
  
  Agent() //!< Constructor of the Agent
  {
    identity=round(random(1,Number_of_identities));
    stress=0;
  }
};

/// Generated by Processing2C++ extraction Tools
#endif //HEADER_Agent_INCLUDED

//MADE NOTE: ../../scripts did it 2024-10-15 16:11:04 !
