/**
 * @file gui_main.c
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

#include "gui_main.h"

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);
  config_paths path = {.xml = {"materials/viewer_glade.xml"},
                       .css = {"materials/viewer_glade.css"},
                       .model = {"samples/2_man.obj"}};
  widgets_core w_core;
  widgets_controls ctrl;
  model model;
  render_data render;
  render.ctrls = &ctrl;
  render.model = &model;
  model.path = *path.model;

  w_core.ui_builder = gtk_builder_new();
  builder_init(&w_core, *path.xml);
  widget_init(&w_core, &ctrl);
  entry_init(&ctrl);
  glarea_init(&w_core, &render);
  signals_connect(&w_core, &ctrl, &render, &model);
  glarea_signals_connect(&render, &ctrl);
  set_css_style(&w_core, *path.css);
  gtk_widget_show(w_core.window_main);
  set_model_info(model, &ctrl);
  gtk_main();
  return 0;
}
