set(IMAGES attribute_manager_uml.png
           base_classes_uml.png
           hyperslab_uml.png
           property_lists_uml.png
           selection_classes.png
           hdf5_attributes.svg
           hdf5_basic_tree.svg
           hdf5_links.svg
           hdf5_package_overview.svg
           hdf5_node_types.svg
           hdf5_dataspaces.svg
           hdf5_selections.svg
           static_dataspace.svg
           dynamic_dataspace_bounded.svg
           dynamic_dataspace_unbounded.svg
           hdf5_selection_manager.svg
           memory_buffer_40byte.svg
           32bit_integer.svg
           dataspace_high_level.svg
           storage_models.svg
           memory_storage_example.svg
           hyperslab_1.svg
           hyperslab_2.svg
           hyperslab_3.svg
           )

add_sphinx_source(${IMAGES})
copy_to_current_build(${IMAGES})
