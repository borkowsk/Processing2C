# Examples for Processing2C
# Remove EXCLUDE_FROM_ALL if you want compile all in one build\n"
cmake_minimum_required(VERSION 3.0)
project(PROCESSING2C_EXAMPLES)
#LIBRARIES
add_subdirectory( "/data/wb/SCC/__public_git/SymShellLight" 
                  "/data/wb/SCC/__public_git/SymShellLight" ) 
add_subdirectory( "../lib/" 
                  "../lib/" )

#EXAMPLES
add_subdirectory( ALIGNMENT 	  )
add_subdirectory( ARCS            )
add_subdirectory( ARRAYLIST 	  )
add_subdirectory( ARRAYTEST 	  )
add_subdirectory( CLASSTEST 	  )
add_subdirectory( ELIPSY 	  )
add_subdirectory( EPIDEMIA 	  )
add_subdirectory( FILES 	  )
add_subdirectory( FORESTFIRE 	  )
add_subdirectory( FORMATS 	  )
add_subdirectory( MROWKI 	  )
add_subdirectory( PERLIN 	 EXCLUDE_FROM_ALL )
add_subdirectory( SAKODA 	  )
add_subdirectory( SYNCHRONIC1 	  )
add_subdirectory( WZROST 	  )
