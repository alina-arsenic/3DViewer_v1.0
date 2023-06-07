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

#define CTRL_MUL           0.005L    /*!< Multiplayer to buttons controls */
#define ENTRY_BUFFER_SIZE  255      /*!< Size of buffer for entry boxes */
#define FILENAME_LENGTH    4096     /*!< Max length of filename in Linux OS */

#include <GL/gl.h>
#include <gtk-3.0/gtk/gtk.h>

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
  GtkWidget *window_help; /*!< Widget for help window */
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
  GtkWidget *s_trans_x;             /*!< Scale  translation x */
  GtkAdjustment *adj_trans_x;       /*!< Adjustment value  translation x */
  GtkWidget *b_trans_y_l;           /*!< Button translation y left */
  GtkWidget *b_trans_y_r;           /*!< Button translation y right */
  GtkWidget *b_trans_y_reset;       /*!< Button translation y reset */
  GtkEntry  *e_trans_y;             /*!< Entry  translation y */
  GtkWidget *s_trans_y;             /*!< Scale  translation y */
  GtkAdjustment *adj_trans_y;       /*!< Adjustment value  translation y */
  GtkWidget *b_trans_z_l;           /*!< Button translation z left */
  GtkWidget *b_trans_z_r;           /*!< Button translation z right */
  GtkWidget *b_trans_z_reset;       /*!< Button translation z reset */
  GtkEntry  *e_trans_z;             /*!< Entry  translation z */
  GtkWidget *s_trans_z;             /*!< Scale  translation z */
  GtkAdjustment *adj_trans_z;       /*!< Adjustment value  translation z */

  GtkWidget *rotat_grid_menu;       /*!< Grid with rotation controls */
  GtkWidget *b_rotat_x_l;           /*!< Button rotation x left */
  GtkWidget *b_rotat_x_r;           /*!< Button rotation x right */
  GtkWidget *b_rotat_x_reset;       /*!< Button rotation x reset */
  GtkEntry  *e_rotat_x;             /*!< Entry  rotation x */
  GtkWidget *s_rotat_x;             /*!< Scale  rotation x */
  GtkAdjustment *adj_rotat_x;       /*!< Adjustment value  rotation x */
  GtkWidget *b_rotat_y_l;           /*!< Button rotation y left */
  GtkWidget *b_rotat_y_r;           /*!< Button rotation y right */
  GtkWidget *b_rotat_y_reset;       /*!< Button rotation y reset */
  GtkEntry  *e_rotat_y;             /*!< Entry  rotation y */
  GtkWidget *s_rotat_y;             /*!< Scale  rotation y */
  GtkAdjustment *adj_rotat_y;       /*!< Adjustment value  rotation x */
  GtkWidget *b_rotat_z_l;           /*!< Button rotation z left */
  GtkWidget *b_rotat_z_r;           /*!< Button rotation z right */
  GtkWidget *b_rotat_z_reset;       /*!< Button rotation z reset */
  GtkEntry  *e_rotat_z;             /*!< Entry  rotation z */
  GtkWidget *s_rotat_z;             /*!< Scale  rotation z */
  GtkAdjustment *adj_rotat_z;       /*!< Adjustment value  rotation x */

  GtkWidget *scale_grid_menu;       /*!< Grid with scale controls */
  GtkWidget *b_scale_l;             /*!< Button scale left */
  GtkWidget *b_scale_r;             /*!< Button scale right */
  GtkWidget *b_scale_reset;         /*!< Button scale reset */
  GtkEntry  *e_scale;               /*!< Entry  scale */
  GtkWidget *s_scale;               /*!< Scale  scale */
  GtkAdjustment *adj_scale;         /*!< Adjustment value scaling */

  GtkWidget *b_hide_ctrl;           /*!< Button to hide GUI controls */
  GtkWidget *b_help;                /*!< Button to open help/about window */
}widgets_controls;

typedef struct Render_data {
  GtkWidget *glarea;                 /*!< Area to render 3D object */

  int width;
  int height;
}render_data;

typedef enum Shift_type {
  INC_FLAT,        /*!< Increase to flat value */
  DEC_FLAT,        /*!< Decrease to flat value */
  INC_MUL,         /*!< Increase by multiplier */
  DEC_MUL,         /*!< Decrease by multiplier */
  SET_TO_VAL,      /*!< Set to fixed value */
  SET_TO_MIN,      /*!< Set to min value */
  SET_TO_MAX       /*!< Set to max value */
}shift_type;

typedef enum Mouse_button {
  LMB = 1,         /*!< Value on click event on left mouse button */
  MMB = 2,         /*!< Value on click event on mouse scroll? */
  RMB = 3          /*!< Value on click event on right mouse button */
}mouse_button;
//************************ MAIN INIT FUNCTIONS *******************************//

/**
 * @brief Parses a XML file designed in Glade, which contains a UI definition.
 * Initialising builder, based on read widget info.
 */
void builder_init(widgets_core* w_core, const char* path_xml);
/**
 * @brief Manual initialisation of widgets by its ID in Glade to further use
 */
void widget_init(widgets_core* w_core, widgets_controls* ctrls);
/**
 * @brief Writing initial values to entry fields
 */
void entry_init(widgets_controls* ctrls);
/**
 * @brief OpenGL area initialisation
 */
void glarea_init(widgets_core* w_core, render_data *render);
/**
 * @brief Connecting signals to its handlers as callback functions
 */
void signals_connect(
    widgets_core* w_core, widgets_controls* ctrls, render_data *render);
/**
 * @brief Connecting signals to glarea events to its handlers
 */
void glarea_signals_connect(render_data *render, widgets_controls *ctrls);
/**
 * @brief Setting css style for interface elements from file
 */
void set_css_style(widgets_core* w_core, const char* path_css);


//*************************** EVENT HANDLERS *********************************//

void on_btn_pressed_help(GtkButton *button, gpointer user_data);
void on_btn_pressed_hide_ctrl(GtkButton *button, gpointer user_data);
/**
 * @brief Reading pressed buttons TODO: fill it
 * @return gboolean Always returns false. #TRUE used to stop other handlers from
 * being invoked for the event. #FALSE to propagate the event further.
 */
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);

void on_adj_trans_changed(GtkAdjustment *adj, gpointer user_data);
void on_adj_rotat_changed(GtkAdjustment *adj, gpointer user_data);
void on_adj_scale_changed(GtkAdjustment *adj, gpointer user_data);

void on_btn_pressed_b_trans_x_l(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_trans_x_r(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_trans_x_reset(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_trans_y_l(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_trans_y_r(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_trans_y_reset(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_trans_z_l(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_trans_z_r(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_trans_z_reset(GtkButton *button, gpointer user_data);

void on_btn_pressed_b_rotat_x_l(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_rotat_x_r(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_rotat_x_reset(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_rotat_y_l(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_rotat_y_r(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_rotat_y_reset(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_rotat_z_l(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_rotat_z_r(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_rotat_z_reset(GtkButton *button, gpointer user_data);

void on_btn_pressed_b_scale_l(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_scale_r(GtkButton *button, gpointer user_data);
void on_btn_pressed_b_scale_reset(GtkButton *button, gpointer user_data);

void on_glarea_realize(GtkGLArea *glarea);
gboolean on_glarea_render(GtkGLArea *glarea, GdkGLContext *context);
void on_glarea_resize(GtkGLArea *area, gint width, gint height);
gboolean on_glarea_scroll(
    GtkWidget* widget, GdkEventScroll *event, gpointer user_data);
gboolean on_glarea_button_press(
    GtkWidget *widget, GdkEventButton *event, gpointer user_data);
gboolean on_glarea_button_release(
    GtkWidget *widget, GdkEventButton *event, gpointer user_data);
gboolean on_glarea_motion_notify(
    GtkWidget *widget, GdkEventMotion *event, gpointer user_data);


//******************************* UTILITY ************************************//

void on_main_window_resize(GtkWindow* window, gpointer user_data);
gboolean on_widget_deleted(GtkWidget *widget, GdkEvent *event, gpointer data);
void set_entry_from_adjust(GtkEntry *entry, GtkAdjustment *adj);
void read_entry_on_return_key(GtkWidget *window, widgets_controls* ctrls);
void set_adjustment_from_entry(GtkEntry *entry, GtkAdjustment *adj);
void shift_adjustment(GtkAdjustment *adj, shift_type type, double shift_value);
gboolean keyval_compare(uint ref, ...);
gboolean is_key(uint keyval, char key);
void reset_scale(widgets_controls *ctrl);

#endif //C8_3DVIEWER_V1_0_1_GUI_MAIN_H
