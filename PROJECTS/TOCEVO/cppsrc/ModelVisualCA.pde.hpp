///   World full of cells need method of visualisation on screen/window
//*//////////////////////////////////////////////////////////////////////////

void visualizeCells(smatrix<int> cells)  ///< Need to be global!
{
  double maximum=std::log10(MAX_INT);
  for(int a=0;a<cells->length;a++)
   for(int b=0;b<cells[a]->length;b++)
   {
      // Colorisation
      double val=std::log10(cells[a][b]);
      
      fill(0,(int)(val/maximum*255),0);
    
      rect(b*cwidth,a*cwidth,cwidth,cwidth); //'a' is vertical!
   }
}

//*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - CA: BASIC VISUALISATION of CELLS FOR TragedyOfCommons
//*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//NOTE! ../../scripts did it 2023-10-11 14:12:43

