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
typedef struct Widgets_controls {
  GtkWidget *box_ctrls;             /*!< Box with all widgets for control */

  GtkWidget *trans_grid_menu;       /*!< Grid with translation controls */
  GtkWidget *b_trans_x_l;           /*!< Button translation x left */
  GtkWidget *b_trans_x_r;           /*!< Button translation x right */
  GtkWidget *b_trans_x_reset;       /*!< Button translation x reset */
  GtkEntry  *e_trans_x;             /*!< Entry  translation x */
  GtkWidget *b_trans_y_l;           /*!< Button translation y left */
  GtkWidget *b_trans_y_r;           /*!< Button translation y right */
  GtkWidget *b_trans_y_reset;       /*!< Button translation y reset */
  GtkEntry  *e_trans_y;             /*!< Entry  translation y */
  GtkWidget *b_trans_z_l;           /*!< Button translation z left */
  GtkWidget *b_trans_z_r;           /*!< Button translation z right */
  GtkWidget *b_trans_z_reset;       /*!< Button translation z reset */
  GtkEntry  *e_trans_z;             /*!< Entry  translation z */

  GtkWidget *rotat_grid_menu;       /*!< Grid with rotation controls */
  GtkWidget *b_rotat_x_l;           /*!< Button rotation x left */
  GtkWidget *b_rotat_x_r;           /*!< Button rotation x right */
  GtkWidget *b_rotat_x_reset;       /*!< Button rotation x reset */
  GtkEntry  *e_rotat_x;             /*!< Entry  rotation x */
  GtkWidget *b_rotat_y_l;           /*!< Button rotation y left */
  GtkWidget *b_rotat_y_r;           /*!< Button rotation y right */
  GtkWidget *b_rotat_y_reset;       /*!< Button rotation y reset */
  GtkEntry  *e_rotat_y;             /*!< Entry  rotation y */
  GtkWidget *b_rotat_z_l;           /*!< Button rotation z left */
  GtkWidget *b_rotat_z_r;           /*!< Button rotation z right */
  GtkWidget *b_rotat_z_reset;       /*!< Button rotation z reset */
  GtkEntry  *e_rotat_z;             /*!< Entry  rotation z */

  GtkWidget *scale_grid_menu;       /*!< Grid with scale controls */
  GtkWidget *b_scale_l;             /*!< Button scale left */
  GtkWidget *b_scale_r;             /*!< Button scale right */
  GtkWidget *b_scale_reset;         /*!< Button scale reset */
  GtkEntry  *e_scale;               /*!< Entry  scale */

  GtkWidget *b_hide_ctrl;             /*!< Button to hide GUI controls */
}widgets_controls;


//************************ MAIN INIT FUNCTIONS *******************************//

/**
 * @brief Parses a XML file designed in Glade, which contains a UI definition.
 * Initialising builder, based on read widget info.
 */
void builder_init(widgets_core* w_core, const char* path_xml);
/**
 * @brief Manual initialisation of widgets by its ID in Glade to further use
 */
void widget_init(widgets_core* w_core, widgets_controls* btns);
/**
 * @brief Connecting signals to its handlers as callback functions
 */
void signals_connect(widgets_core* w_core, widgets_controls* btns);
/**
 * @brief Setting css style for interface elements from file
 */
void set_css_style(widgets_core* w_core, const char* path_css);


//*************************** EVENT HANDLERS *********************************//

void on_btn_pressed_hide_ctrl(GtkButton *button, gpointer user_data);

#endif //C8_3DVIEWER_V1_0_1_GUI_MAIN_H
