set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  ${dir}/dataspace.cpp
  ${dir}/scalar.cpp
  ${dir}/selection.cpp
  ${dir}/selection_manager.cpp
  ${dir}/simple.cpp
  ${dir}/type.cpp
  ${dir}/view.cpp
  )

set(HEADERS
  ${dir}/dataspace.hpp
  ${dir}/scalar.hpp
  ${dir}/selection_manager.hpp
  ${dir}/selection.hpp
  ${dir}/simple.hpp
  ${dir}/type.hpp
  ${dir}/type_trait.hpp
  ${dir}/view.hpp
  )

install(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/dataspace)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
