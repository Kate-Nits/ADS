create_executable_project(Application)

add_executable(Experiment 
	experiment_main.cpp 
	../lib_polynom/polynom.cpp 
	../lib_monom/monom.cpp 
)

configure_file(
	${CMAKE_SOURCE_DIR}/polynoms.txt 
	${CMAKE_CURRENT_BINARY_DIR}/polynoms.txt 
	COPYONLY 
)