add_subdirectory(build)
#============================================================================
# Building the API documentation using doxygen
#============================================================================
configure_file(Doxyfile.in Doxyfile @ONLY)
configure_file(groups.dox groups.dox COPYONLY)
configure_file(mainpage.dox mainpage.dox COPYONLY)
configure_file(namespaces.dox namespaces.dox COPYONLY)
set_source_files_properties(Doxyfile groups.dox mainpage.dox namespaces.dox
	PROPERTIES GENERATED TRUE)

add_custom_command(OUTPUT doxygen.stamp
                   COMMAND doxygen
                   COMMAND echo "timestamp" > doxygen.stamp
                   DEPENDS Doxyfile groups.dox mainpage.dox namespaces.dox
                           ${CMAKE_DOXYGEN_BUILD_DEPENDENCIES}
                   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc)

add_custom_target(api_doc DEPENDS doxygen.stamp)
add_dependencies(html api_doc)

#=============================================================================
# Build the users guide using sphinx
#=============================================================================
add_subdirectory(source)
add_custom_command(OUTPUT sphinx.stamp
    COMMAND sphinx-build -bhtml source build 
    COMMAND echo "timestamp" > sphinx.stamp
    DEPENDS ${CMAKE_SPHINX_SOURCES}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc
    )

add_custom_target(users_guide DEPENDS sphinx.stamp)
add_dependencies(html users_guide)


#==============================================================================
# need to remove some additional files after building the documentation
#==============================================================================
set(CLEANFILES doxygen.stamp sphinx.stamp html latex build)
set_directory_properties(PROPERTIES
    ADDITIONAL_MAKE_CLEAN_FILES ${CLEANFILES})
