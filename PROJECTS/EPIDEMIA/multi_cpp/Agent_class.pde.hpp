/// @file
#pragma once
/// @date 2024-10-15 (last change)
#ifndef HEADER_Agent_INCLUDED
#define HEADER_Agent_INCLUDED

/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// ORIGINAL FILE: AgentDefinition->pde
/// Agent is a one of two central class of each ABM model

/// @note Automatically extracted definition of `class`: Agent
class Agent: public virtual Object{
  public:

  int   state;
  float immunity; //Zamiast PTransfer!
  
  Agent() //Konstruktor agenta->Inicjuje atrybuty
  {
    state=Susceptible;
    immunity=( random(1.0)+random(1.0)+random(1.0)
              +random(1.0)+random(1.0)+random(1.0) ) / 6.0; //Średnia 0.5
             //random(1.0); //Srednia taka sama, ale rozkład płaski
  }
};

/// Generated by Processing2C++ extraction Tools
#endif //HEADER_Agent_INCLUDED

//MADE NOTE: ../../scripts did it 2024-10-15 16:11:03 !

