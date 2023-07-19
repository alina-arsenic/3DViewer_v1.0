/**
 * @file gui_event_handlers.c
 * @authors mebblera@student.21-school.ru
 * @authors weaveryu@student.21-school.ru
 * @brief
 * Functions to handle events, generated by widgets from 3DViewer UI. Widgets
 * initialised in gui_main.c sourcefile.
 * @copyright Copyright (c) 2023
 * TODO: adjust on release
 */

#include <gdk/gdkkeysyms.h>

#include "gui_main.h"

void on_btn_pressed_hide_ctrl(GtkButton *button, gpointer user_data) {
  widgets_controls *p_ctrl = user_data;
  if (gtk_widget_get_visible(p_ctrl->box_ctrls)) {
    gtk_widget_set_visible(p_ctrl->box_ctrls, FALSE);
    gtk_button_set_label(button, "Show controls");
  } else {
    gtk_widget_set_visible(p_ctrl->box_ctrls, TRUE);
    gtk_button_set_label(button, "Hide controls");
  }
}

void on_btn_pressed_help(GtkButton *button, gpointer user_data) {
  widgets_core *p_core = user_data;
  gtk_widget_show_all(p_core->window_help);
  gtk_window_present(GTK_WINDOW(p_core->window_help));
}

void on_btn_pressed_model_select(GtkButton *button, gpointer user_data) {
  render_data *render = user_data;
  char path[FILENAME_LENGTH];
  read_path_from_entry(render->ctrls->path_entry, path);
  if (strcmp(path, "Incorrect path") != 0) {
    render->model->path = path;
    on_glarea_realize(GTK_GL_AREA(render->glarea), user_data);
    set_model_info(*render->model, render->ctrls);
  } else {
    gtk_entry_set_text(render->ctrls->path_entry, path);
  }
}

gboolean on_key_press(GtkWidget *window, GdkEventKey *event,
                      gpointer user_data) {
  render_data *render = user_data;
  widgets_controls *p_ctrl = render->ctrls;
  unsigned int key = event->keyval;
  gboolean ctrl_pressed = (gboolean)(event->state & GDK_CONTROL_MASK);
  // printf("Pressed key: %d\n", event->keyval);
  GtkWidget *target = gtk_window_get_focus(GTK_WINDOW(window));
  if (target != GTK_WIDGET(p_ctrl->path_entry)) {
    if (key == GDK_KEY_Return) {
      if (GTK_IS_ENTRY(target)) {
        read_entry_on_change(GTK_ENTRY(target), p_ctrl);
      }
    } else if (is_key(key, 'A')) {
      on_btn_pressed_left(NULL,
                          ctrl_pressed ? &p_ctrl->rotat_x : &p_ctrl->trans_x);
    } else if (is_key(key, 'D')) {
      on_btn_pressed_right(NULL,
                           ctrl_pressed ? &p_ctrl->rotat_x : &p_ctrl->trans_x);
    } else if (is_key(key, 'S')) {
      on_btn_pressed_left(NULL,
                          ctrl_pressed ? &p_ctrl->rotat_y : &p_ctrl->trans_y);
    } else if (is_key(key, 'W')) {
      on_btn_pressed_right(NULL,
                           ctrl_pressed ? &p_ctrl->rotat_y : &p_ctrl->trans_y);
    } else if (is_key(key, 'Q')) {
      on_btn_pressed_left(NULL,
                          ctrl_pressed ? &p_ctrl->rotat_z : &p_ctrl->trans_z);
    } else if (is_key(key, 'E')) {
      on_btn_pressed_right(NULL,
                           ctrl_pressed ? &p_ctrl->rotat_z : &p_ctrl->trans_z);
    } else if (is_key(key, '-')) {
      on_btn_pressed_left(NULL, &p_ctrl->scale);
    } else if (is_key(key, '+')) {
      on_btn_pressed_right(NULL, &p_ctrl->scale);
    } else if (is_key(key, 'R')) {
      reset_scale(p_ctrl);
    }
  } else if (key == GDK_KEY_Return) {
    on_btn_pressed_model_select(GTK_BUTTON(render->ctrls->b_model_select),
                                render);
  }
  return FALSE;
}

void on_adj_changed(GtkAdjustment *adj, gpointer user_data) {
  controls_group *p_ctrl = user_data;
  set_entry_from_adjust(p_ctrl->entry, p_ctrl->adj);
}

void on_btn_pressed_left(GtkButton *button, gpointer user_data) {
  controls_group *p_ctrl = user_data;
  shift_adjustment(p_ctrl->adj, DEC_MUL, CTRL_MUL);
}

void on_btn_pressed_right(GtkButton *button, gpointer user_data) {
  controls_group *p_ctrl = user_data;
  shift_adjustment(p_ctrl->adj, INC_MUL, CTRL_MUL);
}

void on_btn_pressed_reset(GtkButton *button, gpointer user_data) {
  controls_group *p_ctrl = user_data;
  shift_adjustment(p_ctrl->adj, SET_TO_VAL, 0);
}

void on_entry_focus_out_event(GtkWidget *entry, GdkEventFocus *event,
                              gpointer user_data) {
  controls_group *p_ctrl = user_data;
  set_adjustment_from_entry(p_ctrl->entry, p_ctrl->adj);
}

//********************** GLArea events ***************************************//

void on_main_window_resize(GtkWindow *window, gpointer user_data) {
  render_data *p_render = user_data;

  gtk_window_get_size(window, &p_render->width, &p_render->height);
  // FIXME: Broken, cant scale down
  gtk_widget_set_size_request(p_render->glarea, p_render->width,
                              p_render->height);
}

void on_glarea_realize(GtkGLArea *glarea, gpointer user_data) {
  render_data *render = user_data;
  gtk_gl_area_make_current(GTK_GL_AREA(render->glarea));
  gtk_gl_area_set_has_depth_buffer(GTK_GL_AREA(render->glarea), TRUE);
  glewExperimental = GL_TRUE;
  glewInit();
  glEnable(GL_DEPTH_TEST);

  memset(render->infoLog, 0, LOG_LEN);
  memset(render->model->infoLog, 0, LOG_LEN);

  if (shadersInit(render, render->infoLog)) {
    printf("ERROR: %s\n", render->infoLog);
  }

  if (modelLoad(render->model) ||
      buffersInit(render->model)) {  // CHANGE: MUST BE CALLED WITH MODEL
                                     // OPENING FROM FILE
    printf("ERROR: %s\n", render->model->infoLog);
  }

  // Get frame clock:
  GdkGLContext *glcontext =
      gtk_gl_area_get_context(GTK_GL_AREA(render->glarea));
  GdkWindow *glwindow = gdk_gl_context_get_window(glcontext);
  GdkFrameClock *frame_clock = gdk_window_get_frame_clock(glwindow);

  // Connect update signal:
  g_signal_connect_swapped(frame_clock, "update",
                           G_CALLBACK(gtk_gl_area_queue_render),
                           GTK_GL_AREA(render->glarea));

  // Start updating:
  gdk_frame_clock_begin_updating(frame_clock);
}

gboolean on_glarea_render(GtkGLArea *glarea, GdkGLContext *context,
                          gpointer user_data) {
  render_data *render = user_data;

  glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  modelDraw(render);
  glFlush();

  // Don't propagate signal:
  return TRUE;
}

void on_glarea_resize(GtkGLArea *area, gint width, gint height) {}

// Mouse movement:
static struct {
  gboolean pressed_button; /*!< Mouse button is pressed */
  mouse_button button;
  double x;
  double y;
  double dx;
  double dy;

  double z;

  double buf_x_t;
  double buf_y_t;
  double buf_x_r;
  double buf_y_r;
} panning = {.z = 0.f};

void model_panning_start(double x, double y) {
  panning.x = x;
  panning.y = y;
}

void model_panning_move(double x, double y) {
  panning.dx = panning.x - x;
  panning.dy = panning.y - y;
}

void view_z_decrease(void) { panning.z -= 5.f; }

void view_z_increase(void) { panning.z += 5.f; }

gboolean on_glarea_scroll(GtkWidget *widget, GdkEventScroll *event,
                          gpointer user_data) {
  widgets_controls *p_ctrl = user_data;
  if (event->direction == GDK_SCROLL_UP) {
    view_z_increase();
  } else if (event->direction == GDK_SCROLL_DOWN) {
    view_z_decrease();
  }

  //////////// FIXME: Just to test, insert implementation here
  shift_adjustment(p_ctrl->scale.adj, INC_FLAT, panning.z);
  panning.z = 0;
  // printf("Mouse scroll state = z = %lf\n", panning.z);
  ////////////
  return FALSE;
}

gboolean on_glarea_button_press(GtkWidget *widget, GdkEventButton *event,
                                gpointer user_data) {
  widgets_controls *p_ctrl = user_data;
  GtkAllocation allocation;

  gtk_widget_grab_focus(widget);
  gtk_widget_get_allocation(widget, &allocation);
  if (event->button == LMB || event->button == MMB || event->button == RMB) {
    panning.button = event->button;
    if (panning.pressed_button == FALSE) {
      panning.pressed_button = TRUE;
      model_panning_start(event->x, allocation.height - event->y);
    }
  }

  //////////// FIXME: Just to test, insert implementation here
  panning.buf_x_t = gtk_adjustment_get_value(p_ctrl->trans_x.adj);
  panning.buf_y_t = gtk_adjustment_get_value(p_ctrl->trans_y.adj);
  panning.buf_x_r = gtk_adjustment_get_value(p_ctrl->rotat_x.adj);
  panning.buf_y_r = gtk_adjustment_get_value(p_ctrl->rotat_y.adj);

  // printf("Mouse init place = x = %lf y = %lf\n", panning.x, panning.y);
  /////////
  return FALSE;
}

gboolean on_glarea_button_release(GtkWidget *widget, GdkEventButton *event,
                                  gpointer user_data) {
  //  widgets_controls *p_ctrl = user_data;
  if (event->button == LMB || event->button == MMB || event->button == RMB) {
    panning.button = event->button;
    panning.pressed_button = FALSE;
  }

  return FALSE;
}

gboolean on_glarea_motion_notify(GtkWidget *widget, GdkEventMotion *event,
                                 gpointer user_data) {
  widgets_controls *p_ctrl = user_data;
  GtkAllocation allocation;
  gtk_widget_get_allocation(widget, &allocation);

  if (panning.pressed_button == TRUE) {
    model_panning_move(event->x, allocation.height - event->y);
  }

  //////////// FIXME: Just to test, insert implementation here
  if (panning.button == RMB) {
    shift_adjustment(p_ctrl->trans_x.adj, SET_TO_VAL,
                     panning.buf_x_t + panning.dx);
    shift_adjustment(p_ctrl->trans_y.adj, SET_TO_VAL,
                     panning.buf_y_t + panning.dy);
  } else if (panning.button == LMB) {
    shift_adjustment(p_ctrl->rotat_x.adj, SET_TO_VAL,
                     panning.buf_x_r + panning.dx);
    shift_adjustment(p_ctrl->rotat_y.adj, SET_TO_VAL,
                     panning.buf_y_r + panning.dy);
  }
  // printf("Mouse new place = x = %lf y = %lf\n", panning.x, panning.y);
  // printf("Mouse movement = dx = %lf dy = %lf\n", panning.dx, panning.dy);
  /////////
  return FALSE;
}
