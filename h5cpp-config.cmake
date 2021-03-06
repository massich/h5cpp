#
# add some additional information via cached variables
#

set(H5CPP_MPI_ENABLED @WITH_MPI@ CACHE BOOL "h5cpp was built with MPI support")
set(H5CPP_SWMR_ENABLED @WITH_SWMR@ CACHE BOOL "h5cpp was built with SMWR support")
set(H5CPP_VDS_ENABLED @WITH_VDS@ CACHE BOOL "h5cpp was built with VDS support")

#
# checking for the Boost library
#
set(BOOST_COMPONENTS)

if(NOT TARGET Boost::filesystem)
	list(APPEND BOOST_COMPONENTS filesystem)
endif()

find_package(Boost @Boost_MAJOR_VERSION@.@Boost_MINOR_VERSION@.@Boost_SUBMINOR_VERSION@ EXACT REQUIRED COMPONENTS ${BOOST_COMPONENTS})
if(NOT Boost_FOUND)
	message(FATAL_ERROR "Could not find Boost filesystem library - cannot load h5cpp targets")
endif()

link_directories(${Boost_LIBRARY_DIRS})


#
# checking for hdf5
#
set(HDF5_PREFER_PARALLEL @WITH_MPI@)
find_package(HDF5 @HDF5_VERSION@ EXACT REQUIRED COMPONENTS C)

if(H5CPP_MPI_ENABLED AND (NOT HDF5_IS_PARALLEL))
    message(FATAL_ERROR "HDF5 library with MPI support required!")
endif()
    

#
# load targets 
#
include(${CMAKE_CURRENT_LIST_DIR}/h5cpp_shared_targets.cmake)