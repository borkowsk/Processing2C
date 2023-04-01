# Examples for Processing2C
# Add or remove EXCLUDE_FROM_ALL, if you want (not) compile a particular example\n
cmake_minimum_required(VERSION 3.0)
project(PROCESSING2C_EXAMPLES)
#LIBRARIES
add_subdirectory( "/home/data/SCC/public/symShellLight" 
                  "/home/data/SCC/public/symShellLight" )
add_subdirectory( "../lib/" 
                  "../lib/" )
add_subdirectory( "../tools/" 
                  "../tools/" )
#EXAMPLES
add_subdirectory( ALIGNMENT 	)
add_subdirectory( ARCS 	)
add_subdirectory( ARRAYLIST 	)
add_subdirectory( ARRAYTEST 	)
add_subdirectory( CLASSTEST 	)
add_subdirectory( DICTSTEST 	)
add_subdirectory( ELIPSY 	)
add_subdirectory( EPIDEMIA 	)
add_subdirectory( EVENTS 	)
add_subdirectory( FILES 	)
add_subdirectory( FORESTFIRE 	)
add_subdirectory( FORMATS 	)
add_subdirectory( MAPTEST 	)
add_subdirectory( MROWKI 	)
add_subdirectory( PERLIN 	)
add_subdirectory( SAKODA 	)
add_subdirectory( SHAPES 	)
add_subdirectory( STRINGDICT 	)
add_subdirectory( STRINGTEST 	)
add_subdirectory( SYNCHRONIC1 	)
add_subdirectory( THISTEST 	)
add_subdirectory( TOCEVO 	)
add_subdirectory( WZROST 	)
