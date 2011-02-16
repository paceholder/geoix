#############################################################################
# Makefile for building: geoix
# Generated by qmake (2.01a) (Qt 4.6.2) on: ?? ????. 16 23:11:45 2011
# Project:  geoix.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile geoix.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4 -I/usr/X11R6/include -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -L/usr/X11R6/lib -lQtOpenGL -lQtGui -lQtCore -lGLU -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
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
		tree_abstract_object.cpp moc_mainwindow.cpp \
		moc_project.cpp \
		moc_tree_object.cpp \
		moc_tree_menu_fabric.cpp \
		moc_render_panel.cpp \
		moc_render_panel_2D.cpp \
		moc_visual_object.cpp \
		moc_render_panel_3D.cpp \
		moc_size.cpp \
		moc_coord_system_3d.cpp \
		moc_points.cpp \
		moc_data_loader.cpp \
		moc_contour.cpp \
		moc_contourer_fast.cpp \
		moc_surface.cpp \
		moc_color_palette.cpp \
		moc_gl_panel_3d.cpp \
		moc_gl_panel_2d.cpp \
		moc_scene_2d.cpp \
		moc_scene_3d.cpp \
		moc_coord_system_2d.cpp \
		moc_spliner.cpp \
		moc_flat_contour.cpp \
		moc_lines.cpp \
		moc_spliner_dialog.cpp \
		moc_surf_prop_dialog.cpp \
		moc_surface_data_iterator.cpp \
		moc_logger.cpp \
		moc_color_slider.cpp \
		moc_project_tree.cpp \
		moc_subtree.cpp \
		moc_drop_widget.cpp \
		moc_project_tree_model.cpp \
		moc_tree_abstract_object.cpp \
		moc_tree_folder_object.cpp \
		qrc_images.cpp
OBJECTS       = main.o \
		mainwindow.o \
		engine.o \
		project.o \
		tree_menu_fabric.o \
		tree_object.o \
		render_panel.o \
		data_loader.o \
		render_panel_3D.o \
		points.o \
		surface.o \
		gl_panel_3d.o \
		render_panel_2D.o \
		gl_panel_2d.o \
		lines.o \
		spliner_dialog.o \
		surf_prop_dialog.o \
		color_palette.o \
		contourer_fast.o \
		coord_system_2d.o \
		coord_system_3d.o \
		logger.o \
		project_tree.o \
		subtree.o \
		project_tree_model.o \
		tree_folder_object.o \
		tree_abstract_object.o \
		moc_mainwindow.o \
		moc_project.o \
		moc_tree_object.o \
		moc_tree_menu_fabric.o \
		moc_render_panel.o \
		moc_render_panel_2D.o \
		moc_visual_object.o \
		moc_render_panel_3D.o \
		moc_size.o \
		moc_coord_system_3d.o \
		moc_points.o \
		moc_data_loader.o \
		moc_contour.o \
		moc_contourer_fast.o \
		moc_surface.o \
		moc_color_palette.o \
		moc_gl_panel_3d.o \
		moc_gl_panel_2d.o \
		moc_scene_2d.o \
		moc_scene_3d.o \
		moc_coord_system_2d.o \
		moc_spliner.o \
		moc_flat_contour.o \
		moc_lines.o \
		moc_spliner_dialog.o \
		moc_surf_prop_dialog.o \
		moc_surface_data_iterator.o \
		moc_logger.o \
		moc_color_slider.o \
		moc_project_tree.o \
		moc_subtree.o \
		moc_drop_widget.o \
		moc_project_tree_model.o \
		moc_tree_abstract_object.o \
		moc_tree_folder_object.o \
		qrc_images.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		geoix.pro
QMAKE_TARGET  = geoix
DESTDIR       = 
TARGET        = geoix

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_spliner_dialog.h ui_surf_prop_dialog.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: geoix.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtOpenGL.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile geoix.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/opengl.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtOpenGL.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile geoix.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/geoix1.0.0 || $(MKDIR) .tmp/geoix1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/geoix1.0.0/ && $(COPY_FILE) --parents mainwindow.h mainwindow_actions.h project.h tree_object.h tree_menu_fabric.h engine.h render_panel.h render_panel_2D.h visual_object.h render_panel_3D.h size.h coord_system_3d.h points.h data_loader.h point3D.h constants.h surface_data.h contour.h contourer_fast.h surface.h color_palette.h gl_panel_3d.h gl_panel_2d.h scene_2d.h scene_3d.h coord_system_2d.h spliner.h flat_contour.h lines.h spliner_dialog.h surf_prop_dialog.h surface_data_iterator.h logger.h color_slider.h project_tree.h subtree.h drop_widget.h project_tree_model.h tree_abstract_object.h tree_folder_object.h .tmp/geoix1.0.0/ && $(COPY_FILE) --parents images.qrc .tmp/geoix1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp engine.cpp project.cpp tree_menu_fabric.cpp tree_object.cpp render_panel.cpp data_loader.cpp render_panel_3D.cpp points.cpp surface.cpp gl_panel_3d.cpp render_panel_2D.cpp gl_panel_2d.cpp lines.cpp spliner_dialog.cpp surf_prop_dialog.cpp color_palette.cpp contourer_fast.cpp coord_system_2d.cpp coord_system_3d.cpp logger.cpp project_tree.cpp subtree.cpp project_tree_model.cpp tree_folder_object.cpp tree_abstract_object.cpp .tmp/geoix1.0.0/ && $(COPY_FILE) --parents mainwindow.ui spliner_dialog.ui surf_prop_dialog.ui .tmp/geoix1.0.0/ && (cd `dirname .tmp/geoix1.0.0` && $(TAR) geoix1.0.0.tar geoix1.0.0 && $(COMPRESS) geoix1.0.0.tar) && $(MOVE) `dirname .tmp/geoix1.0.0`/geoix1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/geoix1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_project.cpp moc_tree_object.cpp moc_tree_menu_fabric.cpp moc_render_panel.cpp moc_render_panel_2D.cpp moc_visual_object.cpp moc_render_panel_3D.cpp moc_size.cpp moc_coord_system_3d.cpp moc_points.cpp moc_data_loader.cpp moc_contour.cpp moc_contourer_fast.cpp moc_surface.cpp moc_color_palette.cpp moc_gl_panel_3d.cpp moc_gl_panel_2d.cpp moc_scene_2d.cpp moc_scene_3d.cpp moc_coord_system_2d.cpp moc_spliner.cpp moc_flat_contour.cpp moc_lines.cpp moc_spliner_dialog.cpp moc_surf_prop_dialog.cpp moc_surface_data_iterator.cpp moc_logger.cpp moc_color_slider.cpp moc_project_tree.cpp moc_subtree.cpp moc_drop_widget.cpp moc_project_tree_model.cpp moc_tree_abstract_object.cpp moc_tree_folder_object.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_project.cpp moc_tree_object.cpp moc_tree_menu_fabric.cpp moc_render_panel.cpp moc_render_panel_2D.cpp moc_visual_object.cpp moc_render_panel_3D.cpp moc_size.cpp moc_coord_system_3d.cpp moc_points.cpp moc_data_loader.cpp moc_contour.cpp moc_contourer_fast.cpp moc_surface.cpp moc_color_palette.cpp moc_gl_panel_3d.cpp moc_gl_panel_2d.cpp moc_scene_2d.cpp moc_scene_3d.cpp moc_coord_system_2d.cpp moc_spliner.cpp moc_flat_contour.cpp moc_lines.cpp moc_spliner_dialog.cpp moc_surf_prop_dialog.cpp moc_surface_data_iterator.cpp moc_logger.cpp moc_color_slider.cpp moc_project_tree.cpp moc_subtree.cpp moc_drop_widget.cpp moc_project_tree_model.cpp moc_tree_abstract_object.cpp moc_tree_folder_object.cpp
moc_mainwindow.cpp: mainwindow_actions.h \
		mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_project.cpp: tree_folder_object.h \
		tree_abstract_object.h \
		logger.h \
		project.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) project.h -o moc_project.cpp

moc_tree_object.cpp: tree_abstract_object.h \
		tree_object.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) tree_object.h -o moc_tree_object.cpp

moc_tree_menu_fabric.cpp: tree_object.h \
		tree_abstract_object.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h \
		tree_menu_fabric.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) tree_menu_fabric.h -o moc_tree_menu_fabric.cpp

moc_render_panel.cpp: visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		render_panel.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) render_panel.h -o moc_render_panel.cpp

moc_render_panel_2D.cpp: render_panel.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		coord_system_2d.h \
		gl_panel_2d.h \
		scene_2d.h \
		render_panel_2D.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) render_panel_2D.h -o moc_render_panel_2D.cpp

moc_visual_object.cpp: tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		visual_object.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) visual_object.h -o moc_visual_object.cpp

moc_render_panel_3D.cpp: render_panel.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		coord_system_3d.h \
		render_panel_3D.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) render_panel_3D.h -o moc_render_panel_3D.cpp

moc_size.cpp: size.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) size.h -o moc_size.cpp

moc_coord_system_3d.cpp: size.h \
		coord_system_3d.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) coord_system_3d.h -o moc_coord_system_3d.cpp

moc_points.cpp: visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		tree_folder_object.h \
		tree_menu_fabric.h \
		engine.h \
		project.h \
		logger.h \
		point3D.h \
		constants.h \
		points.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) points.h -o moc_points.cpp

moc_data_loader.cpp: point3D.h \
		constants.h \
		contour.h \
		data_loader.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) data_loader.h -o moc_data_loader.cpp

moc_contour.cpp: point3D.h \
		constants.h \
		contour.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) contour.h -o moc_contour.cpp

moc_contourer_fast.cpp: flat_contour.h \
		contour.h \
		point3D.h \
		constants.h \
		contourer_fast.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) contourer_fast.h -o moc_contourer_fast.cpp

moc_surface.cpp: visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		tree_menu_fabric.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h \
		surface_data.h \
		constants.h \
		flat_contour.h \
		contour.h \
		point3D.h \
		surface.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) surface.h -o moc_surface.cpp

moc_color_palette.cpp: color_palette.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) color_palette.h -o moc_color_palette.cpp

moc_gl_panel_3d.cpp: scene_3d.h \
		size.h \
		gl_panel_3d.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) gl_panel_3d.h -o moc_gl_panel_3d.cpp

moc_gl_panel_2d.cpp: scene_2d.h \
		size.h \
		gl_panel_2d.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) gl_panel_2d.h -o moc_gl_panel_2d.cpp

moc_scene_2d.cpp: size.h \
		scene_2d.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) scene_2d.h -o moc_scene_2d.cpp

moc_scene_3d.cpp: size.h \
		scene_3d.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) scene_3d.h -o moc_scene_3d.cpp

moc_coord_system_2d.cpp: gl_panel_2d.h \
		scene_2d.h \
		size.h \
		coord_system_2d.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) coord_system_2d.h -o moc_coord_system_2d.cpp

moc_spliner.cpp: surface_data.h \
		size.h \
		constants.h \
		point3D.h \
		spliner.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) spliner.h -o moc_spliner.cpp

moc_flat_contour.cpp: contour.h \
		point3D.h \
		constants.h \
		flat_contour.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) flat_contour.h -o moc_flat_contour.cpp

moc_lines.cpp: visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		contour.h \
		point3D.h \
		constants.h \
		tree_folder_object.h \
		lines.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) lines.h -o moc_lines.cpp

moc_spliner_dialog.cpp: spliner_dialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) spliner_dialog.h -o moc_spliner_dialog.cpp

moc_surf_prop_dialog.cpp: surf_prop_dialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) surf_prop_dialog.h -o moc_surf_prop_dialog.cpp

moc_surface_data_iterator.cpp: constants.h \
		surface_data.h \
		size.h \
		surface_data_iterator.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) surface_data_iterator.h -o moc_surface_data_iterator.cpp

moc_logger.cpp: logger.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) logger.h -o moc_logger.cpp

moc_color_slider.cpp: color_palette.h \
		color_slider.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) color_slider.h -o moc_color_slider.cpp

moc_project_tree.cpp: project_tree.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) project_tree.h -o moc_project_tree.cpp

moc_subtree.cpp: subtree.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) subtree.h -o moc_subtree.cpp

moc_drop_widget.cpp: drop_widget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) drop_widget.h -o moc_drop_widget.cpp

moc_project_tree_model.cpp: project.h \
		tree_folder_object.h \
		tree_abstract_object.h \
		logger.h \
		project_tree_model.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) project_tree_model.h -o moc_project_tree_model.cpp

moc_tree_abstract_object.cpp: tree_abstract_object.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) tree_abstract_object.h -o moc_tree_abstract_object.cpp

moc_tree_folder_object.cpp: tree_abstract_object.h \
		tree_folder_object.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) tree_folder_object.h -o moc_tree_folder_object.cpp

compiler_rcc_make_all: qrc_images.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_images.cpp
qrc_images.cpp: images.qrc \
		images/add_folder.png \
		images/Delete.png \
		images/add_surface.png \
		images/Closed_folder.png \
		images/3D.png \
		images/Screenshot.png \
		images/Create.png \
		images/2D.png \
		images/points.png \
		images/Delete_panel.png \
		images/add_points.png \
		images/surface.png \
		images/Hierarchy.png
	/usr/bin/rcc -name images images.qrc -o qrc_images.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_spliner_dialog.h ui_surf_prop_dialog.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_spliner_dialog.h ui_surf_prop_dialog.h
ui_mainwindow.h: mainwindow.ui
	/usr/bin/uic-qt4 mainwindow.ui -o ui_mainwindow.h

ui_spliner_dialog.h: spliner_dialog.ui
	/usr/bin/uic-qt4 spliner_dialog.ui -o ui_spliner_dialog.h

ui_surf_prop_dialog.h: surf_prop_dialog.ui
	/usr/bin/uic-qt4 surf_prop_dialog.ui -o ui_surf_prop_dialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		mainwindow_actions.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		tree_abstract_object.h \
		logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		mainwindow_actions.h \
		ui_mainwindow.h \
		tree_object.h \
		tree_abstract_object.h \
		tree_menu_fabric.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h \
		render_panel.h \
		visual_object.h \
		size.h \
		scene_3d.h \
		project_tree.h \
		project_tree_model.h \
		subtree.h \
		spliner_dialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

engine.o: engine.cpp engine.h \
		project.h \
		tree_folder_object.h \
		tree_abstract_object.h \
		logger.h \
		mainwindow.h \
		mainwindow_actions.h \
		render_panel_2D.h \
		render_panel.h \
		visual_object.h \
		tree_object.h \
		size.h \
		scene_3d.h \
		coord_system_2d.h \
		gl_panel_2d.h \
		scene_2d.h \
		render_panel_3D.h \
		coord_system_3d.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o engine.o engine.cpp

project.o: project.cpp project.h \
		tree_folder_object.h \
		tree_abstract_object.h \
		logger.h \
		tree_menu_fabric.h \
		tree_object.h \
		engine.h \
		project_tree_model.h \
		mainwindow.h \
		mainwindow_actions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o project.o project.cpp

tree_menu_fabric.o: tree_menu_fabric.cpp tree_menu_fabric.h \
		tree_object.h \
		tree_abstract_object.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h \
		points.h \
		visual_object.h \
		size.h \
		scene_3d.h \
		point3D.h \
		constants.h \
		lines.h \
		contour.h \
		surface.h \
		surface_data.h \
		flat_contour.h \
		mainwindow.h \
		mainwindow_actions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tree_menu_fabric.o tree_menu_fabric.cpp

tree_object.o: tree_object.cpp tree_object.h \
		tree_abstract_object.h \
		tree_folder_object.h \
		engine.h \
		project.h \
		logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tree_object.o tree_object.cpp

render_panel.o: render_panel.cpp render_panel.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o render_panel.o render_panel.cpp

data_loader.o: data_loader.cpp data_loader.h \
		point3D.h \
		constants.h \
		contour.h \
		points.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		tree_folder_object.h \
		tree_menu_fabric.h \
		engine.h \
		project.h \
		logger.h \
		surface_data.h \
		mainwindow.h \
		mainwindow_actions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o data_loader.o data_loader.cpp

render_panel_3D.o: render_panel_3D.cpp render_panel_3D.h \
		render_panel.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		coord_system_3d.h \
		gl_panel_3d.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o render_panel_3D.o render_panel_3D.cpp

points.o: points.cpp points.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		tree_folder_object.h \
		tree_menu_fabric.h \
		engine.h \
		project.h \
		logger.h \
		point3D.h \
		constants.h \
		data_loader.h \
		contour.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o points.o points.cpp

surface.o: surface.cpp surface.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		tree_menu_fabric.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h \
		surface_data.h \
		constants.h \
		flat_contour.h \
		contour.h \
		point3D.h \
		data_loader.h \
		contourer_fast.h \
		color_palette.h \
		surf_prop_dialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o surface.o surface.cpp

gl_panel_3d.o: gl_panel_3d.cpp gl_panel_3d.h \
		scene_3d.h \
		size.h \
		render_panel_3D.h \
		render_panel.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		coord_system_3d.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gl_panel_3d.o gl_panel_3d.cpp

render_panel_2D.o: render_panel_2D.cpp render_panel_2D.h \
		render_panel.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		coord_system_2d.h \
		gl_panel_2d.h \
		scene_2d.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o render_panel_2D.o render_panel_2D.cpp

gl_panel_2d.o: gl_panel_2d.cpp gl_panel_2d.h \
		scene_2d.h \
		size.h \
		render_panel_2D.h \
		render_panel.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		scene_3d.h \
		coord_system_2d.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gl_panel_2d.o gl_panel_2d.cpp

lines.o: lines.cpp lines.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		contour.h \
		point3D.h \
		constants.h \
		tree_folder_object.h \
		data_loader.h \
		tree_menu_fabric.h \
		engine.h \
		project.h \
		logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lines.o lines.cpp

spliner_dialog.o: spliner_dialog.cpp spliner_dialog.h \
		ui_spliner_dialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o spliner_dialog.o spliner_dialog.cpp

surf_prop_dialog.o: surf_prop_dialog.cpp surf_prop_dialog.h \
		ui_surf_prop_dialog.h \
		surface.h \
		visual_object.h \
		tree_object.h \
		tree_abstract_object.h \
		size.h \
		scene_3d.h \
		tree_menu_fabric.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h \
		surface_data.h \
		constants.h \
		flat_contour.h \
		contour.h \
		point3D.h \
		color_slider.h \
		color_palette.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o surf_prop_dialog.o surf_prop_dialog.cpp

color_palette.o: color_palette.cpp color_palette.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o color_palette.o color_palette.cpp

contourer_fast.o: contourer_fast.cpp contourer_fast.h \
		flat_contour.h \
		contour.h \
		point3D.h \
		constants.h \
		surface_data.h \
		size.h \
		surface_data_iterator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o contourer_fast.o contourer_fast.cpp

coord_system_2d.o: coord_system_2d.cpp coord_system_2d.h \
		gl_panel_2d.h \
		scene_2d.h \
		size.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o coord_system_2d.o coord_system_2d.cpp

coord_system_3d.o: coord_system_3d.cpp coord_system_3d.h \
		size.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o coord_system_3d.o coord_system_3d.cpp

logger.o: logger.cpp logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o logger.o logger.cpp

project_tree.o: project_tree.cpp project_tree.h \
		tree_object.h \
		tree_abstract_object.h \
		visual_object.h \
		size.h \
		scene_3d.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h \
		render_panel.h \
		tree_menu_fabric.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o project_tree.o project_tree.cpp

subtree.o: subtree.cpp subtree.h \
		tree_object.h \
		tree_abstract_object.h \
		logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o subtree.o subtree.cpp

project_tree_model.o: project_tree_model.cpp project_tree_model.h \
		project.h \
		tree_folder_object.h \
		tree_abstract_object.h \
		logger.h \
		tree_object.h \
		render_panel.h \
		visual_object.h \
		size.h \
		scene_3d.h \
		engine.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o project_tree_model.o project_tree_model.cpp

tree_folder_object.o: tree_folder_object.cpp mainwindow.h \
		mainwindow_actions.h \
		tree_folder_object.h \
		tree_abstract_object.h \
		tree_menu_fabric.h \
		tree_object.h \
		engine.h \
		project.h \
		logger.h \
		points.h \
		visual_object.h \
		size.h \
		scene_3d.h \
		point3D.h \
		constants.h \
		lines.h \
		contour.h \
		surface.h \
		surface_data.h \
		flat_contour.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tree_folder_object.o tree_folder_object.cpp

tree_abstract_object.o: tree_abstract_object.cpp tree_abstract_object.h \
		mainwindow.h \
		mainwindow_actions.h \
		engine.h \
		project.h \
		tree_folder_object.h \
		logger.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tree_abstract_object.o tree_abstract_object.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_project.o: moc_project.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_project.o moc_project.cpp

moc_tree_object.o: moc_tree_object.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_tree_object.o moc_tree_object.cpp

moc_tree_menu_fabric.o: moc_tree_menu_fabric.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_tree_menu_fabric.o moc_tree_menu_fabric.cpp

moc_render_panel.o: moc_render_panel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_render_panel.o moc_render_panel.cpp

moc_render_panel_2D.o: moc_render_panel_2D.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_render_panel_2D.o moc_render_panel_2D.cpp

moc_visual_object.o: moc_visual_object.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_visual_object.o moc_visual_object.cpp

moc_render_panel_3D.o: moc_render_panel_3D.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_render_panel_3D.o moc_render_panel_3D.cpp

moc_size.o: moc_size.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_size.o moc_size.cpp

moc_coord_system_3d.o: moc_coord_system_3d.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_coord_system_3d.o moc_coord_system_3d.cpp

moc_points.o: moc_points.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_points.o moc_points.cpp

moc_data_loader.o: moc_data_loader.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_data_loader.o moc_data_loader.cpp

moc_contour.o: moc_contour.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_contour.o moc_contour.cpp

moc_contourer_fast.o: moc_contourer_fast.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_contourer_fast.o moc_contourer_fast.cpp

moc_surface.o: moc_surface.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_surface.o moc_surface.cpp

moc_color_palette.o: moc_color_palette.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_color_palette.o moc_color_palette.cpp

moc_gl_panel_3d.o: moc_gl_panel_3d.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gl_panel_3d.o moc_gl_panel_3d.cpp

moc_gl_panel_2d.o: moc_gl_panel_2d.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gl_panel_2d.o moc_gl_panel_2d.cpp

moc_scene_2d.o: moc_scene_2d.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_scene_2d.o moc_scene_2d.cpp

moc_scene_3d.o: moc_scene_3d.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_scene_3d.o moc_scene_3d.cpp

moc_coord_system_2d.o: moc_coord_system_2d.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_coord_system_2d.o moc_coord_system_2d.cpp

moc_spliner.o: moc_spliner.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_spliner.o moc_spliner.cpp

moc_flat_contour.o: moc_flat_contour.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_flat_contour.o moc_flat_contour.cpp

moc_lines.o: moc_lines.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_lines.o moc_lines.cpp

moc_spliner_dialog.o: moc_spliner_dialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_spliner_dialog.o moc_spliner_dialog.cpp

moc_surf_prop_dialog.o: moc_surf_prop_dialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_surf_prop_dialog.o moc_surf_prop_dialog.cpp

moc_surface_data_iterator.o: moc_surface_data_iterator.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_surface_data_iterator.o moc_surface_data_iterator.cpp

moc_logger.o: moc_logger.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_logger.o moc_logger.cpp

moc_color_slider.o: moc_color_slider.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_color_slider.o moc_color_slider.cpp

moc_project_tree.o: moc_project_tree.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_project_tree.o moc_project_tree.cpp

moc_subtree.o: moc_subtree.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_subtree.o moc_subtree.cpp

moc_drop_widget.o: moc_drop_widget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_drop_widget.o moc_drop_widget.cpp

moc_project_tree_model.o: moc_project_tree_model.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_project_tree_model.o moc_project_tree_model.cpp

moc_tree_abstract_object.o: moc_tree_abstract_object.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_tree_abstract_object.o moc_tree_abstract_object.cpp

moc_tree_folder_object.o: moc_tree_folder_object.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_tree_folder_object.o moc_tree_folder_object.cpp

qrc_images.o: qrc_images.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_images.o qrc_images.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
