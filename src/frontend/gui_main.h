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
#define LOG_LEN 512                 /*!< InfoLog length */

#define max(a,b) {if (a < b) a = b;}
#define min(a,b) {if (a > b) a = b;}

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <gtk-3.0/gtk/gtk.h>

#include <cglm/cglm.h>
#include <cglm/affine.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/**
 * @brief Struct with paths to files with configurations of UI
 */
typedef struct Config_paths {
  const char* xml[FILENAME_LENGTH];     /*!< Path to glade-generated xml file */
  const char* css[FILENAME_LENGTH];     /*!< Path to file with css styles for GUI */
  const char* model[FILENAME_LENGTH];   /*!< Path to file with initial model */
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

typedef struct Controls_group {
  GtkWidget *b_left;      /*!< Button left  (decrease)*/
  GtkWidget *b_right;     /*!< Button right (increase)*/
  GtkWidget *b_reset;     /*!< Button reset */
  GtkEntry  *entry;       /*!< Entry for value */
  GtkWidget *scale;       /*!< Scale for value */
  GtkAdjustment *adj;     /*!< Adjustment value */
}controls_group;

/**
 * @brief Struct with widgets for control buttons
 */
typedef struct Widgets_controls {
  GtkWidget *box_ctrls;             /*!< Box with all widgets for control */

  GtkWidget *model_grid_file;       /*!< Grid with model information */
  GtkWidget *path_combobox;         /*!< Combobox to select model */
  GtkEntry  *path_entry;            /*!< Entry for model name */
  GtkWidget *b_model_select;        /*!< Button to select model */

  GtkWidget *model_grid_menu;       /*!< Grid with model information */
  GtkLabel  *model_name;            /*!< Entry for model name */
  GtkLabel  *model_vertices;        /*!< Entry for model vertices counter */
  GtkLabel  *model_edges;           /*!< Entry for model edges counter */

  GtkWidget *trans_grid_menu;       /*!< Grid with translation controls */
  controls_group trans_x;
  controls_group trans_y;
  controls_group trans_z;

  GtkWidget *rotat_grid_menu;       /*!< Grid with rotation controls */
  controls_group rotat_x;
  controls_group rotat_y;
  controls_group rotat_z;

  GtkWidget *scale_grid_menu;       /*!< Grid with scale controls */
  controls_group scale;

  GtkWidget *b_hide_ctrl;           /*!< Button to hide GUI controls */
  GtkWidget *b_help;                /*!< Button to open help/about window */
}widgets_controls;

typedef struct Model {
  GLuint VAO, VBO, EBO;             /*!< Buffer objects */
  const GLchar *path;               /*!< File path */
  GLchar infoLog[LOG_LEN];

  const C_STRUCT aiScene* scene;    /*!< Data from file */
  C_STRUCT aiVector3D max, min;     /*!< Max and min vertices coordinates */
  unsigned int vertices_count, faces_count;

  struct { double x, y, z; } trans;  /*!< Initial transformation vector */
  struct { double x, y, z; } center; /*!< Model center */
  double scale, scale_z;             /*!< Scaling for transitioning */
}model;

typedef struct Render_data {
  GtkWidget *glarea;                 /*!< Area to render 3D object */
  GdkFrameClock *frame_clock;        /*!< Needed for frame changing */
  GLuint shaderProgram;              /*!< Compiled OpenGL shader program index */
  GLchar infoLog[LOG_LEN];

  model *model;
  widgets_controls *ctrls;

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
void signals_connect(widgets_core* w_core, widgets_controls* ctrls,
                     render_data *render, model *model);
/**
 * @brief Connecting signals to glarea events to its handlers
 */
void glarea_signals_connect(render_data *render, widgets_controls *ctrls);
/**
 * @brief Setting css style for interface elements from file
 */
void set_css_style(widgets_core* w_core, const char* path_css);

void set_model_info(model model, widgets_controls *ctrls);

    //*************************** EVENT HANDLERS *********************************//

void on_btn_pressed_help(GtkButton *button, gpointer user_data);
void on_btn_pressed_hide_ctrl(GtkButton *button, gpointer user_data);
void on_btn_pressed_model_select(GtkButton *button, gpointer user_data);

/**
 * @brief Reading pressed buttons TODO: fill it
 * @return gboolean Always returns false. #TRUE used to stop other handlers from
 * being invoked for the event. #FALSE to propagate the event further.
 */
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);

void on_adj_changed(GtkAdjustment *adj, gpointer user_data);

void on_btn_pressed_left(GtkButton *button, gpointer user_data);
void on_btn_pressed_right(GtkButton *button, gpointer user_data);
void on_btn_pressed_reset(GtkButton *button, gpointer user_data);

void on_entry_focus_out_event(
    GtkWidget *entry, GdkEventFocus *event, gpointer user_data);

void on_glarea_realize(GtkGLArea *glarea, gpointer user_data);
gboolean on_glarea_render(GtkGLArea *glarea, GdkGLContext *context, gpointer user_data);
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

char *file_from_path(char *pathname);
void on_main_window_resize(GtkWindow* window, gpointer user_data);
gboolean on_widget_deleted(GtkWidget *widget, GdkEvent *event, gpointer data);
void set_entry_from_adjust(GtkEntry *entry, GtkAdjustment *adj);
void read_entry_on_change(GtkEntry *target, widgets_controls *ctrls);
void set_adjustment_from_entry(GtkEntry *entry, GtkAdjustment *adj);
double get_adjustment_range(GtkAdjustment *adj);
void shift_adjustment(GtkAdjustment *adj, shift_type type, double shift_value);
gboolean keyval_compare(unsigned int ref, ...);
gboolean is_key(unsigned int keyval, char key);
void reset_scale(widgets_controls *ctrl);
void read_path_from_entry(GtkEntry *entry, char *path);

    //******************************* MODEL ************************************//

GLchar *getFileBuffer(char *path);
int shadersInit(render_data *render, GLchar *infoLog);
int modelLoad(model *model);
int buffersInit(model *model);
void countVerticesAndFaces(model *model);
void init_minmax(model *model, C_STRUCT aiVector3D v);
void minmax(model *model, C_STRUCT aiVector3D v);
void verticesInit(model *model, GLfloat *vertices);
void indicesInit(model *model, GLuint *indices);
void utilityInit(model *model);
void modelDraw(render_data *render);


#endif //C8_3DVIEWER_V1_0_1_GUI_MAIN_H
