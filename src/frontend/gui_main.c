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
#include "common/common_widgets.h"

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);
  config_paths path = {
      .xml = {"materials/viewer_glade.xml"},
      .css = {"materials/viewer_glade.css"}
  };
  widgets_core w_core;
  widgets_buttons btns;
  w_core.ui_builder = gtk_builder_new();
  builder_init(&w_core, *path.xml);
  widget_init(&w_core, &btns);
  signals_connect(&w_core, &btns);
  set_css_style(&w_core, *path.css);
  gtk_widget_show(w_core.window_main);
  gtk_main();
  return 0;
}

void builder_init(widgets_core* w_core, const char* path_xml) {
  // establish contact with xml code (glade) used to adjust widget settings
  if (!gtk_builder_add_from_file(w_core->ui_builder, path_xml,
                                 &w_core->err)) {
    g_critical("Cant find builder UI : %s", w_core->err->message);
    g_error_free(w_core->err);
  }
  // initialising main window of application
  w_core->window_main = GTK_WIDGET(gtk_builder_get_object(w_core->ui_builder, "window_main"));
}

void widget_init(widgets_core* w_core, widgets_buttons* btns) {
  btns->trans_x_l = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_x_l"));
  btns->trans_x_r = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_x_r"));
  btns->trans_x_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_x_reset"));
  btns->trans_y_l = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_y_l"));
  btns->trans_y_r = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_y_r"));
  btns->trans_y_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_y_reset"));
  btns->trans_z_l = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_z_l"));
  btns->trans_z_r = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_z_r"));
  btns->trans_z_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_z_reset"));
}

void signals_connect(widgets_core* w_core, widgets_buttons* btns) {
  // callback function to exit from gtk_main() cycle when app is closed
  g_signal_connect(
      w_core->window_main, "destroy", G_CALLBACK(gtk_main_quit), NULL);
//  g_signal_connect(
//      btns->trans_x_l, "pressed", G_CALLBACK(on_btn_pressed_trans_x_l), NULL);
}

void set_css_style(widgets_core* w_core, const char* path_css) {
  GtkCssProvider* provider_file = gtk_css_provider_new();
  GFile* css_path = g_file_new_for_path(path_css);
  if (!gtk_css_provider_load_from_file(provider_file, css_path, &w_core->err)) {
    g_critical("Cant find css file : %s", w_core->err->message);
    g_error_free(w_core->err);
  }
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider_file), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}
