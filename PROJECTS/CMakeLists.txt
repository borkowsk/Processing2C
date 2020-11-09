# Examples for Processing2C
# Remove EXCLUDE_FROM_ALL if you want compile all in one build\n"
cmake_minimum_required(VERSION 3.0)

#LIBRARIES
add_subdirectory( "/data/wb/SCC/__working_copies/symShell2/WBRTM_Linux/" 
                  "/data/wb/SCC/__working_copies/symShell2/WBRTM_Linux/" ) 
add_subdirectory( "../lib/" 
                  "../lib/" )

#EXAMPLES
add_subdirectory( ALIGNMENT                      )
add_subdirectory( ARRAYLIST 	 EXCLUDE_FROM_ALL)
add_subdirectory( ARRAYTEST 	 EXCLUDE_FROM_ALL)
add_subdirectory( CLASSTEST 	 EXCLUDE_FROM_ALL)
add_subdirectory( ELIPSY 	 EXCLUDE_FROM_ALL)
add_subdirectory( EPIDEMIA 	 EXCLUDE_FROM_ALL)
add_subdirectory( FORMATS 	                 )
add_subdirectory( FORESTFIRE 	 EXCLUDE_FROM_ALL)
add_subdirectory( MROWKI 	 EXCLUDE_FROM_ALL)
add_subdirectory( PERLIN 	 EXCLUDE_FROM_ALL)
add_subdirectory( SAKODA 	 EXCLUDE_FROM_ALL)
add_subdirectory( SYNCHRONIC1 	                 )
add_subdirectory( WZROST 	 EXCLUDE_FROM_ALL)
