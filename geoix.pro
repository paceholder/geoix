# -------------------------------------------------
# Project created by QtCreator 2010-07-04T23:35:33
# -------------------------------------------------
QT += opengl
TARGET = geoix
TEMPLATE = app
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
    project_tree.cpp \
    subtree.cpp \
    project_tree_model.cpp \
    tree_folder_object.cpp \
    tree_abstract_object.cpp \
    rbf_mapper.cpp
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
    spliner.h \
    flat_contour.h \
    lines.h \
    spliner_dialog.h \
    surf_prop_dialog.h \
    surface_data_iterator.h \
    logger.h \
    color_slider.h \
    project_tree.h \
    subtree.h \
    drop_widget.h \
    project_tree_model.h \
    tree_abstract_object.h \
    tree_folder_object.h \
    abstract_mapper.h \
    rbf_mapper.h \
    matrix.h
FORMS += mainwindow.ui \
    spliner_dialog.ui \
    surf_prop_dialog.ui \
    rbf_settings_widget.ui
RESOURCES += images.qrc
