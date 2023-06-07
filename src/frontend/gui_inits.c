/**
 * @file gui_inits.c
 * @authors mebblera@student.21-school.ru
 * @authors weaveryu@student.21-school.ru
 * @brief Init functions for 3DViewer GUI elements:\n
 * 1) Init builder from from Glade xml file\n
 * 2) Init widgets as objects from builder UI\n
 * 3) Connect widget signals to its callback functions\n
 * 4) Set style for GUI elements from css file\n
 * @copyright Copyright (c) 2023
 * TODO: adjust on release
 */

#include "gui_main.h"

void builder_init(widgets_core* w_core, const char* path_xml) {
  // establish contact with xml code (glade) used to adjust widget settings
  if (!gtk_builder_add_from_file(w_core->ui_builder, path_xml,
                                 &w_core->err)) {
    g_critical("Cant find builder UI : %s", w_core->err->message);
    g_error_free(w_core->err);
  }
  // initialising main window of application
  w_core->window_main = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "window_main"));
  w_core->window_help = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "window_help"));
}

void widget_init(widgets_core* w_core, widgets_controls* ctrls) {
  ctrls->box_ctrls = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "box_controls"));

  ctrls->trans_grid_menu = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "grid_menu_translation"));
  ctrls->b_trans_x_l = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_x_l"));
  ctrls->b_trans_x_r = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_x_r"));
  ctrls->b_trans_x_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_x_reset"));
  ctrls->e_trans_x = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_translation_x"));
  ctrls->s_trans_x = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_translation_x"));
  ctrls->adj_trans_x = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_translation_x"));
  ctrls->b_trans_y_l = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_y_l"));
  ctrls->b_trans_y_r = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_y_r"));
  ctrls->b_trans_y_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_y_reset"));
  ctrls->e_trans_y = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_translation_y"));
  ctrls->s_trans_y = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_translation_y"));
  ctrls->adj_trans_y = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_translation_y"));
  ctrls->b_trans_z_l = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_z_l"));
  ctrls->b_trans_z_r = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_z_r"));
  ctrls->b_trans_z_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_z_reset"));
  ctrls->e_trans_z = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_translation_z"));
  ctrls->s_trans_z = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_translation_z"));
  ctrls->adj_trans_z = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_translation_z"));

  ctrls->rotat_grid_menu = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "grid_menu_rotation"));
  ctrls->b_rotat_x_l = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_x_l"));
  ctrls->b_rotat_x_r = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_x_r"));
  ctrls->b_rotat_x_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_x_reset"));
  ctrls->e_rotat_x = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_rotation_x"));
  ctrls->s_rotat_x = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_rotating_x"));
  ctrls->adj_rotat_x = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_rotation_x"));
  ctrls->b_rotat_y_l = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_y_l"));
  ctrls->b_rotat_y_r = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_y_r"));
  ctrls->b_rotat_y_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_y_reset"));
  ctrls->e_rotat_y = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_rotation_y"));
  ctrls->s_rotat_y = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_rotating_y"));
  ctrls->adj_rotat_y = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_rotation_y"));
  ctrls->b_rotat_z_l = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_z_l"));
  ctrls->b_rotat_z_r = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_z_r"));
  ctrls->b_rotat_z_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_z_reset"));
  ctrls->e_rotat_z = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_rotation_z"));
  ctrls->s_rotat_z = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_rotating_z"));
  ctrls->adj_rotat_z = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_rotation_z"));

  ctrls->scale_grid_menu = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "grid_menu_scale"));
  ctrls->b_scale_l = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_scaling_l"));
  ctrls->b_scale_r = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_scaling_r"));
  ctrls->b_scale_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_scaling_reset"));
  ctrls->e_scale = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_scaling"));
  ctrls->s_scale = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_scaling"));
  ctrls->adj_scale = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_scaling"));

  ctrls->b_hide_ctrl =  GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_hide_controls"));
  ctrls->b_help =  GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_help"));
}

void entry_init(widgets_controls* ctrls) {
  on_adj_trans_changed(NULL, ctrls);
  on_adj_rotat_changed(NULL, ctrls);
  on_adj_scale_changed(NULL, ctrls);
}

void glarea_init(widgets_core* w_core, render_data *render) {
  render->glarea = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "gl_drawing_area"));
}

void signals_connect(
    widgets_core* w_core, widgets_controls* ctrls, render_data *render) {
  // callback function to exit from gtk_main() cycle when app is closed
  g_signal_connect(w_core->window_main, "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(w_core->window_main, "check-resize",
                   G_CALLBACK(on_main_window_resize), render);
  g_signal_connect(w_core->window_help, "delete-event",
                   G_CALLBACK(on_widget_deleted), NULL);

  g_signal_connect(ctrls->b_hide_ctrl, "pressed",
                   G_CALLBACK(on_btn_pressed_hide_ctrl), ctrls);
  g_signal_connect(ctrls->b_help, "pressed",
                   G_CALLBACK(on_btn_pressed_help), w_core);
  g_signal_connect(w_core->window_main, "key_press_event",
                   G_CALLBACK(on_key_press), ctrls);
  g_signal_connect(ctrls->adj_trans_x, "value-changed",
                   G_CALLBACK(on_adj_trans_changed), ctrls);
  g_signal_connect(ctrls->adj_trans_y, "value-changed",
                   G_CALLBACK(on_adj_trans_changed), ctrls);
  g_signal_connect(ctrls->adj_trans_z, "value-changed",
                   G_CALLBACK(on_adj_trans_changed), ctrls);
  g_signal_connect(ctrls->adj_rotat_x, "value-changed",
                   G_CALLBACK(on_adj_rotat_changed), ctrls);
  g_signal_connect(ctrls->adj_rotat_y, "value-changed",
                   G_CALLBACK(on_adj_rotat_changed), ctrls);
  g_signal_connect(ctrls->adj_rotat_z, "value-changed",
                   G_CALLBACK(on_adj_rotat_changed), ctrls);
  g_signal_connect(ctrls->adj_scale, "value-changed",
                   G_CALLBACK(on_adj_scale_changed), ctrls);

  g_signal_connect(ctrls->b_trans_x_l, "pressed",
                   G_CALLBACK(on_btn_pressed_b_trans_x_l), ctrls);
  g_signal_connect(ctrls->b_trans_x_r, "pressed",
                   G_CALLBACK(on_btn_pressed_b_trans_x_r), ctrls);
  g_signal_connect(ctrls->b_trans_x_reset, "pressed",
                   G_CALLBACK(on_btn_pressed_b_trans_x_reset), ctrls);
  g_signal_connect(ctrls->b_trans_y_l, "pressed",
                   G_CALLBACK(on_btn_pressed_b_trans_y_l), ctrls);
  g_signal_connect(ctrls->b_trans_y_r, "pressed",
                   G_CALLBACK(on_btn_pressed_b_trans_y_r), ctrls);
  g_signal_connect(ctrls->b_trans_y_reset, "pressed",
                   G_CALLBACK(on_btn_pressed_b_trans_y_reset), ctrls);
  g_signal_connect(ctrls->b_trans_z_l, "pressed",
                   G_CALLBACK(on_btn_pressed_b_trans_z_l), ctrls);
  g_signal_connect(ctrls->b_trans_z_r, "pressed",
                   G_CALLBACK(on_btn_pressed_b_trans_z_r), ctrls);
  g_signal_connect(ctrls->b_trans_z_reset, "pressed",
                   G_CALLBACK(on_btn_pressed_b_trans_z_reset), ctrls);

  g_signal_connect(ctrls->b_rotat_x_l, "pressed",
                   G_CALLBACK(on_btn_pressed_b_rotat_x_l), ctrls);
  g_signal_connect(ctrls->b_rotat_x_r, "pressed",
                   G_CALLBACK(on_btn_pressed_b_rotat_x_r), ctrls);
  g_signal_connect(ctrls->b_rotat_x_reset, "pressed",
                   G_CALLBACK(on_btn_pressed_b_rotat_x_reset), ctrls);
  g_signal_connect(ctrls->b_rotat_y_l, "pressed",
                   G_CALLBACK(on_btn_pressed_b_rotat_y_l), ctrls);
  g_signal_connect(ctrls->b_rotat_y_r, "pressed",
                   G_CALLBACK(on_btn_pressed_b_rotat_y_r), ctrls);
  g_signal_connect(ctrls->b_rotat_y_reset, "pressed",
                   G_CALLBACK(on_btn_pressed_b_rotat_y_reset), ctrls);
  g_signal_connect(ctrls->b_rotat_z_l, "pressed",
                   G_CALLBACK(on_btn_pressed_b_rotat_z_l), ctrls);
  g_signal_connect(ctrls->b_rotat_z_r, "pressed",
                   G_CALLBACK(on_btn_pressed_b_rotat_z_r), ctrls);
  g_signal_connect(ctrls->b_rotat_z_reset, "pressed",
                   G_CALLBACK(on_btn_pressed_b_rotat_z_reset), ctrls);

  g_signal_connect(ctrls->b_scale_l, "pressed",
                   G_CALLBACK(on_btn_pressed_b_scale_l), ctrls);
  g_signal_connect(ctrls->b_scale_r, "pressed",
                   G_CALLBACK(on_btn_pressed_b_scale_r), ctrls);
  g_signal_connect(ctrls->b_scale_reset, "pressed",
                   G_CALLBACK(on_btn_pressed_b_scale_reset), ctrls);

//  g_signal_connect(
//      ctrls->e_trans_x, "changed", G_CALLBACK(on_entry_trans_x_changed), ctrls);
//  g_signal_connect(
//      ctrls->e_trans_y, "changed", G_CALLBACK(on_entry_trans_y_changed), ctrls);
//  g_signal_connect(
//      ctrls->e_trans_z, "changed", G_CALLBACK(on_entry_trans_z_changed), ctrls);
//  g_signal_connect(
//      ctrls->e_rotat_x, "changed", G_CALLBACK(on_entry_rotat_x_changed), ctrls);
//  g_signal_connect(
//      ctrls->e_rotat_y, "changed", G_CALLBACK(on_entry_rotat_y_changed), ctrls);
//  g_signal_connect(
//      ctrls->e_rotat_z, "changed", G_CALLBACK(on_entry_rotat_z_changed), ctrls);
//  g_signal_connect(
//      ctrls->e_scale, "changed", G_CALLBACK(on_entry_scale_changed), ctrls);
}

void glarea_signals_connect(render_data *render, widgets_controls *ctrls) {
  // event to mouse controls: buttons and scroll
  gtk_widget_add_events(render->glarea, GDK_SCROLL_MASK);
  gtk_widget_add_events(render->glarea, GDK_BUTTON_PRESS_MASK);
  gtk_widget_add_events(render->glarea, GDK_BUTTON_RELEASE_MASK);
  gtk_widget_add_events(render->glarea, GDK_BUTTON1_MOTION_MASK);
  gtk_widget_add_events(render->glarea, GDK_BUTTON2_MOTION_MASK);
  gtk_widget_add_events(render->glarea, GDK_BUTTON3_MOTION_MASK);

  g_signal_connect(render->glarea, "realize", G_CALLBACK(on_glarea_realize), 0);
  g_signal_connect(render->glarea, "render", G_CALLBACK(on_glarea_render), 0);
  g_signal_connect(render->glarea, "resize", G_CALLBACK(on_glarea_resize), 0);

  g_signal_connect(render->glarea, "scroll-event",
                   G_CALLBACK(on_glarea_scroll), ctrls);
  g_signal_connect(render->glarea, "button-press-event",
                   G_CALLBACK(on_glarea_button_press), ctrls);
  g_signal_connect(render->glarea, "button-release-event",
                   G_CALLBACK(on_glarea_button_release), ctrls);
  g_signal_connect(render->glarea, "motion-notify-event",
                   G_CALLBACK(on_glarea_motion_notify), ctrls);
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
