/// @file
/// @note Automatically made from _klasaWorld.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:04 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// Agent Base Model adopted for Processing2C
/// @author: Zofia Cieślińska
/// @date 2024-09-30 (last change)
/// ORIGINAL FILE: klasaWorld->pde
/////////////////////////////////////////////

//++++++++++++ ZMIENNE ++++++++++++
int worozmiar = sizew/ws;  ///<ile pól jest na świecie

float density = 0.005;  ///<ewentualna gęstośc jedzenia rozłożena

int xNest = int(worozmiar/7);  ///<współrzędne gniazda i jego rozmiar
int yNest = int(worozmiar/7);  ///<???
int siNest = 3;                ///<???

int foodSupply;  ///< początkowa ilość jedzenia w gnieździe
int ileWsumieMrowek = sizew/10;  ///< maksymalna dopuszczalna liczba mrówek


#include "World_class.pde.hpp"
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:04 !

