# -------------------------------------------------
# Project created by QtCreator 2010-07-04T23:35:33
# -------------------------------------------------
QT += opengl
TARGET = geoix
TEMPLATE = app
CONFIG += precompile_header

# PRECOMPILED_HEADER = geoix_pch.h
# DEFINES += USING_PCH
SOURCES += main.cpp \
    mainwindow.cpp \
    engine.cpp \
    project.cpp \
    tree_menu_fabric.cpp \
    tree_object.cpp \
    render_panel.cpp \
    data_loader.cpp \
    render_panel_3D.cpp \
    points.cpp \
    surface.cpp \
    gl_panel_3d.cpp \
    render_panel_2D.cpp \
    gl_panel_2d.cpp \
    lines.cpp \
    spliner_dialog.cpp \
    surf_prop_dialog.cpp \
    color_palette.cpp \
    contourer_fast.cpp \
    coord_system_2d.cpp \
    coord_system_3d.cpp \
    logger.cpp \
    project_tree_model.cpp \
    tree_folder_object.cpp \
    tree_abstract_object.cpp \
    rbf_mapper.cpp \
    rbf_core.cpp \
    rbf_domain.cpp \
    visual_object.cpp \
    subtree_model.cpp \
    custom_tree_model.cpp \
    cube.cpp \
    cubedialog.cpp \
    kriging_core.cpp \
    kriging_mapper.cpp \
    well.cpp \
    surface_data.cpp \
    abstract_mapper.cpp \
    point3D.cpp \
    local_b_spline_mapper.cpp \
    lattice.cpp \
    bspline.cpp \
    fourier.cpp \
    fourier/kiss_fft.cpp \
    data_exporter.cpp \
    curve.cpp \
    curve_load_table_model.cpp \
    curve_load_table_delegate.cpp \
    curveloaddialog.cpp \
    cg/cg.cpp
HEADERS += mainwindow.h \
    mainwindow_actions.h \
    project.h \
    tree_object.h \
    tree_menu_fabric.h \
    engine.h \
    render_panel.h \
    render_panel_2D.h \
    visual_object.h \
    render_panel_3D.h \
    size.h \
    coord_system_3d.h \
    points.h \
    data_loader.h \
    point3D.h \
    constants.h \
    surface_data.h \
    contour.h \
    contourer_fast.h \
    surface.h \
    color_palette.h \
    gl_panel_3d.h \
    gl_panel_2d.h \
    scene_2d.h \
    scene_3d.h \
    coord_system_2d.h \
    flat_contour.h \
    lines.h \
    spliner_dialog.h \
    surf_prop_dialog.h \
    surface_data_iterator.h \
    logger.h \
    color_slider.h \
    drop_widget.h \
    project_tree_model.h \
    tree_abstract_object.h \
    tree_folder_object.h \
    abstract_mapper.h \
    rbf_mapper.h \
    matrix.h \
    point2D.h \
    rbf_core.h \
    rbf_domain.h \
    subtree_model.h \
    custom_tree_model.h \
    cube.h \
    cubedialog.h \
    edge.h \
    kriging_mapper.h \
    kriging_core.h \
    well.h \
    local_b_spline_mapper.h \
    lattice.h \
    bspline.h \
    fourier.h \
    fourier/kiss_fft.h \
    fourier/_kiss_fft_guts.h \
    data_exporter.h \
    curve.h \
    curve_load_table_model.h \
    curve_load_table_delegate.h \
    curveloaddialog.h \
    cg/tnt_array2d.h \
    cg/tnt_array1d.h \
    cg/tnt_i_refvec.h \
    cg/tnt_array2d_utils.h \
    cg/tnt_array1d_utils.h \
    cg/cg.h
FORMS += mainwindow.ui \
    spliner_dialog.ui \
    surf_prop_dialog.ui \
    rbf_settings_widget.ui \
    cubedialog.ui \
    kriging_settings_widget.ui \
    localb_settings_widget.ui \
    curveloader.ui
RESOURCES += images.qrc
