/**
 * @file gui_main.h
 * @authors mebblera@student.21-school.ru
 * @authors weaveryu@student.21-school.ru
 * @brief
 * 3DViewer GUI based on GTK+ and OpenGL libraries. GUI provides the ability
 * to:\n
 * 1) Load and view models from obj files.\n
 * 2) Translate, rotate and scale models.\n
 * 3) Show brief information about model (file name, number of vertices and
 *    edges).\n
 * Interface controls:\n
 * 1) Virtual interface buttons.\n
 * 2) Physical keyboard keys.\n
 * 3) Mouse movement/buttons.\n
 * @copyright Copyright (c) 2023
 * TODO: adjust on release
 */

#ifndef C8_3DVIEWER_V1_0_1_GUI_MAIN_H
#define C8_3DVIEWER_V1_0_1_GUI_MAIN_H

#define FILENAME_LENGTH 4096 /*!< Max length of filename in Linux OS */

#include <gtk-3.0/gtk/gtk.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>

#include "common/common_externs.h"

/**
 * @brief Struct with paths to files with configurations of UI
 */
typedef struct Config_paths {
  const char* xml[FILENAME_LENGTH]; /*!< Path to glade-generated xml file */
  const char* css[FILENAME_LENGTH]; /*!< Path to file with css styles for GUI */
}config_paths;
/**
 * @brief Struct with core widgets of program - builder, main window and error
 * handler
 */
typedef struct Widgets_core {
  GtkBuilder *ui_builder; /*!< Widget for UI builder */
  GtkWidget *window_main; /*!< Widget for main GUI window */
  GError *err;            /*!< Widget for main error handler */
}widgets_core;
/**
 * @brief Struct with widgets for control buttons
 */
typedef struct Widgets_buttons {
  GtkWidget *trans_x_l;
  GtkWidget *trans_x_r;
  GtkWidget *trans_x_reset;
  GtkWidget *trans_y_l;
  GtkWidget *trans_y_r;
  GtkWidget *trans_y_reset;
  GtkWidget *trans_z_l;
  GtkWidget *trans_z_r;
  GtkWidget *trans_z_reset;

  GtkWidget *hide_ctrl;
}widgets_buttons;




/**
 * @brief Parses a XML file designed in Glade, which contains a UI definition.
 * Initialising builder, based on read widget info.
 */
void builder_init(widgets_core* w_core, const char* path_xml);
/**
 * @brief Manual initialisation of widgets by its ID in Glade to further use
 */
void widget_init(widgets_core* w_core, widgets_buttons* btns);
/**
 * @brief Connecting signals to its handlers as callback functions
 */
void signals_connect(widgets_core* w_core, widgets_buttons* btns);
/**
 * @brief Setting css style for interface elements from file
 */
void set_css_style(widgets_core* w_core, const char* path_css);

#endif //C8_3DVIEWER_V1_0_1_GUI_MAIN_H
