cmake_minimum_required(VERSION 3.2)
# version 3.4 is required as other do not work with C++14 and clang

project(Geoix CXX)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

get_directory_property(_has_parent PARENT_DIRECTORY)
if(_has_parent)
  set(is_root_project OFF)
else()
  set(is_root_project ON)
endif()

set(NE_DEVELOPER_DEFAULTS "${is_root_project}" CACHE BOOL "Turns on default settings for development of Geoix")

#option(BUILD_TESTING "Build tests" "${NE_DEVELOPER_DEFAULTS}")
#option(BUILD_EXAMPLES "Build Examples" "${NE_DEVELOPER_DEFAULTS}")
#option(BUILD_SHARED_LIBS "Build as shared library" ON)
option(NE_FORCE_TEST_COLOR "Force colorized unit test output" OFF)

enable_testing()

if(NE_DEVELOPER_DEFAULTS)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_EXTENSIONS OFF)

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()

#add_subdirectory(external)

# Find the QtWidgets library
find_package(Qt5 5.3 COMPONENTS
             Core
             Widgets
             Gui
             OpenGL)


find_package(OpenGL REQUIRED COMPONENTS OpenGL)

#include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )



qt5_add_resources(RESOURCES ./images.qrc)

# Unfortunately, as we have a split include/src, AUTOMOC doesn't work.
# We'll have to manually specify some files
set(CMAKE_AUTOMOC ON)



set(HEADERS 
    mainwindow.h
    mainwindow_actions.h
    project.h
    tree_object.h
    tree_menu_fabric.h
    engine.h
    render_panel.h
    render_panel_2D.h
    visual_object.h
    render_panel_3D.h
    size.h
    coord_system_3d.h
    points.h
    data_loader.h
    constants.h
    surface_data.h
    contour.h
    contourer_fast.h
    surface.h
    color_palette.h
    gl_panel_3d.h
    gl_panel_2d.h
    scene_2d.h
    scene_3d.h
    coord_system_2d.h
    flat_contour.h
    lines.h
    spliner_dialog.h
    surf_prop_dialog.h
    surface_data_iterator.h
    logger.h
    color_slider.h
    drop_widget.h
    project_tree_model.h
    tree_abstract_object.h
    tree_folder_object.h
    abstract_mapper.h
    rbf_mapper.h
    matrix.h
    rbf_core.h
    rbf_domain.h
    subtree_model.h
    custom_tree_model.h
    cube.h
    cubedialog.h
    edge.h
    kriging_mapper.h
    kriging_core.h
    well.h
    local_b_spline_mapper.h
    lattice.h
    bspline.h
    fourier.h
    fourier/kiss_fft.h
    fourier/_kiss_fft_guts.h
    data_exporter.h
    curve.h
    curve_load_table_model.h
    curve_load_table_delegate.h
    curveloaddialog.h
    cg/tnt_array2d.h
    cg/tnt_array1d.h
    cg/tnt_i_refvec.h
    cg/tnt_array2d_utils.h
    cg/tnt_array1d_utils.h
    cg/cg.h
    kriging_var_core.h
    kriging_core_functions.h
    sgs_2d_mapper.h
    gaussian_distr.h
    cumulative_distribution.h
    variance_model.h
    point_nd.h
    kriging_params.h
    #kdtree.h
    #kd_tree.h
)

set(CPP_SOURCE_FILES
  main.cpp
  mainwindow.cpp
  engine.cpp
  project.cpp
  tree_menu_fabric.cpp
  tree_object.cpp
  render_panel.cpp
  data_loader.cpp
  render_panel_3D.cpp
  surface.cpp
  contour.cpp
  gl_panel_3d.cpp
  render_panel_2D.cpp
  gl_panel_2d.cpp
  lines.cpp
  spliner_dialog.cpp
  surf_prop_dialog.cpp
  color_palette.cpp
  contourer_fast.cpp
  coord_system_2d.cpp
  coord_system_3d.cpp
  logger.cpp
  project_tree_model.cpp
  tree_folder_object.cpp
  tree_abstract_object.cpp
  rbf_mapper.cpp
  rbf_core.cpp
  rbf_domain.cpp
  visual_object.cpp
  subtree_model.cpp
  custom_tree_model.cpp
  cube.cpp
  cubedialog.cpp
  kriging_core.cpp
  kriging_mapper.cpp
  well.cpp
  surface_data.cpp
  abstract_mapper.cpp
  local_b_spline_mapper.cpp
  lattice.cpp
  bspline.cpp
  fourier.cpp
  fourier/kiss_fft.cpp
  data_exporter.cpp
  curve.cpp
  curve_load_table_model.cpp
  curve_load_table_delegate.cpp
  curveloaddialog.cpp
  cg/cg.cpp
  kriging_var_core.cpp
  sgs_2d_mapper.cpp
  points.cpp
  #kdtree.c
)

qt5_wrap_ui(UI_HEADERS
  cubedialog.ui
  curveloader.ui
  kriging_settings_widget.ui
  localb_settings_widget.ui
  mainwindow.ui
  rbf_settings_widget.ui
  spliner_dialog.ui
  surf_prop_dialog.ui
  TARGET geoix
)

qt5_add_resources(RESOURCES images.qrc)

# If we want to give the option to build a static library,
# set BUILD_SHARED_LIBS option to OFF
add_executable(geoix
  ${CPP_SOURCE_FILES}
  ${HEADERS}
  ${UI_HEADERS}
  ${RESOURCES}
)

#add_library(NodeEditor::geoix ALIAS geoix)

target_include_directories(geoix
  PUBLIC
    $<INSTALL_INTERFACE:include>
    #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(geoix
  PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::OpenGL
    OpenGL::OpenGL
    ${OPENGL_glu_LIBRARY}
)

target_compile_definitions(geoix
  PUBLIC
    ${Qt5Widgets_DEFINITIONS}
    #NODE_EDITOR_SHARED
  PRIVATE
    #NODE_EDITOR_EXPORTS
    #NODE_DEBUG_DRAWING
    #QT_NO_KEYWORDS
    _NO_EXCEPTION
)

target_compile_options(geoix
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4gcwd4127 /EHsc>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
)

target_compile_features(geoix
  PUBLIC
    cxx_generic_lambdas # Require C++14
)

set_target_properties(geoix
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

######
# Moc
##

#file(GLOB_RECURSE HEADERS_TO_MOC include/geoix/internal/*.hpp)

#qt5_wrap_cpp(geoix_moc
    #${HEADERS_TO_MOC}
  #TARGET geoix
  #OPTIONS --no-notes # Don't display a note for the headers which don't produce a moc_*.cpp
#)

#target_sources(geoix PRIVATE ${geoix_moc})

###########
# Examples
##

#if(BUILD_EXAMPLES)
  #add_subdirectory(examples)
#endif()

##################
# Automated Tests
##

#if(BUILD_TESTING)
  #add_subdirectory(test)
#endif()

###############
# Installation
##

#include(GNUInstallDirs)

#set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/geoix)

#install(TARGETS geoix
  #EXPORT NodeEditorTargets
  #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  #ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)

#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#install(EXPORT NodeEditorTargets
  #FILE NodeEditorTargets.cmake
  #NAMESPACE NodeEditor::
  #DESTINATION ${INSTALL_CONFIGDIR}
#)

#include(CMakePackageConfigHelpers)

#configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/NodeEditorConfig.cmake.in
  #${CMAKE_CURRENT_BINARY_DIR}/NodeEditorConfig.cmake
  #INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
#)

#install(FILES
  #${CMAKE_CURRENT_BINARY_DIR}/NodeEditorConfig.cmake
  #DESTINATION ${INSTALL_CONFIGDIR}
#)

