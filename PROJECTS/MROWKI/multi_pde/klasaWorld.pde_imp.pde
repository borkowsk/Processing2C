/// Agent Base Model adopted for Processing2C
/// @author: Zofia Cieślińska
/// @date 2024-09-30 (last change)
/// ORIGINAL FILE: klasaWorld.pde
/////////////////////////////////////////////

//++++++++++++ ZMIENNE ++++++++++++
int worozmiar = sizew/ws;  ///<ile pól jest na świecie

float density = 0.005;  ///<ewentualna gęstośc jedzenia rozłożena

int xNest = int(worozmiar/7);  ///<współrzędne gniazda i jego rozmiar
int yNest = int(worozmiar/7);  ///<???
int siNest = 3;                ///<???

int foodSupply;  ///< początkowa ilość jedzenia w gnieździe
int ileWsumieMrowek = sizew/10;  ///< maksymalna dopuszczalna liczba mrówek


/*_import_class:World */
