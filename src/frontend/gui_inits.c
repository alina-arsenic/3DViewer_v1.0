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
  // add event to main window to handle focus changing(for entry ports)
  gtk_widget_add_events(
      w_core->window_main, GDK_FOCUS_CHANGE_MASK);
}

void widget_init(widgets_core* w_core, widgets_controls* ctrls) {
  ctrls->box_ctrls = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "box_controls"));

  ctrls->model_grid_file = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "grid_file_select"));

  ctrls->path_combobox = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "combobox_file_path"));
  ctrls->path_entry = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_file_path"));
  ctrls->b_model_select = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_file_select"));

  ctrls->model_grid_menu = GTK_WIDGET(
          gtk_builder_get_object(w_core->ui_builder, "grid_model_info"));

  ctrls->model_name = GTK_LABEL(
      gtk_builder_get_object(w_core->ui_builder, "label_file_name_value"));
  ctrls->model_vertices = GTK_LABEL(
      gtk_builder_get_object(w_core->ui_builder, "label_vertices_value"));
  ctrls->model_edges = GTK_LABEL(
      gtk_builder_get_object(w_core->ui_builder, "label_edges_value"));

  ctrls->trans_grid_menu = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "grid_menu_translation"));

  ctrls->trans_x.b_left = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_x_l"));
  ctrls->trans_x.b_right = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_x_r"));
  ctrls->trans_x.b_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_x_reset"));
  ctrls->trans_x.entry = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_translation_x"));
  ctrls->trans_x.scale = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_translation_x"));
  ctrls->trans_x.adj = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_translation_x"));

  ctrls->trans_y.b_left = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_y_l"));
  ctrls->trans_y.b_right = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_y_r"));
  ctrls->trans_y.b_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_y_reset"));
  ctrls->trans_y.entry = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_translation_y"));
  ctrls->trans_y.scale = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_translation_y"));
  ctrls->trans_y.adj = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_translation_y"));

  ctrls->trans_z.b_left = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_z_l"));
  ctrls->trans_z.b_right = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_z_r"));
  ctrls->trans_z.b_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_translation_z_reset"));
  ctrls->trans_z.entry = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_translation_z"));
  ctrls->trans_z.scale = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_translation_z"));
  ctrls->trans_z.adj = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_translation_z"));

  ctrls->rotat_grid_menu = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "grid_menu_rotation"));

  ctrls->rotat_x.b_left = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_x_l"));
  ctrls->rotat_x.b_right = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_x_r"));
  ctrls->rotat_x.b_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_x_reset"));
  ctrls->rotat_x.entry = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_rotation_x"));
  ctrls->rotat_x.scale = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_rotation_x"));
  ctrls->rotat_x.adj = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_rotation_x"));

  ctrls->rotat_y.b_left = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_y_l"));
  ctrls->rotat_y.b_right = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_y_r"));
  ctrls->rotat_y.b_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_y_reset"));
  ctrls->rotat_y.entry = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_rotation_y"));
  ctrls->rotat_y.scale = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_rotation_y"));
  ctrls->rotat_y.adj = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_rotation_y"));

  ctrls->rotat_z.b_left = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_z_l"));
  ctrls->rotat_z.b_right = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_z_r"));
  ctrls->rotat_z.b_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_rotation_z_reset"));
  ctrls->rotat_z.entry = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_rotation_z"));
  ctrls->rotat_z.scale = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_rotation_z"));
  ctrls->rotat_z.adj = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_rotation_z"));

  ctrls->scale_grid_menu = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "grid_menu_scale"));

  ctrls->scale.b_left = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_scaling_l"));
  ctrls->scale.b_right = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_scaling_r"));
  ctrls->scale.b_reset = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_scaling_reset"));
  ctrls->scale.entry = GTK_ENTRY(
      gtk_builder_get_object(w_core->ui_builder, "entry_scaling"));
  ctrls->scale.scale = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "scale_scaling"));
  ctrls->scale.adj = GTK_ADJUSTMENT(
      gtk_builder_get_object(w_core->ui_builder, "adj_scaling"));

  ctrls->b_hide_ctrl =  GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_hide_controls"));
  ctrls->b_help =  GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "button_help"));
}

void entry_init(widgets_controls* ctrls) {
  on_adj_changed(NULL, &ctrls->trans_x);
  on_adj_changed(NULL, &ctrls->trans_y);
  on_adj_changed(NULL, &ctrls->trans_z);
  on_adj_changed(NULL, &ctrls->rotat_x);
  on_adj_changed(NULL, &ctrls->rotat_y);
  on_adj_changed(NULL, &ctrls->rotat_z);
  on_adj_changed(NULL, &ctrls->scale);
}

void glarea_init(widgets_core* w_core, render_data *render) {
  render->glarea = GTK_WIDGET(
      gtk_builder_get_object(w_core->ui_builder, "gl_drawing_area"));
}

void connect_control_group(controls_group *ctrl_group) {
  g_signal_connect(ctrl_group->adj, "value-changed",
                   G_CALLBACK(on_adj_changed), ctrl_group);
  g_signal_connect(ctrl_group->b_left, "pressed",
                   G_CALLBACK(on_btn_pressed_left), ctrl_group);
  g_signal_connect(ctrl_group->b_right, "pressed",
                   G_CALLBACK(on_btn_pressed_right), ctrl_group);
  g_signal_connect(ctrl_group->b_reset, "pressed",
                   G_CALLBACK(on_btn_pressed_reset), ctrl_group);
  g_signal_connect(ctrl_group->entry, "focus-out-event",
                   G_CALLBACK(on_entry_focus_out_event), ctrl_group);
}

void signals_connect(widgets_core* w_core, widgets_controls* ctrls,
                     render_data *render, model *model) {
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

  g_signal_connect(ctrls->b_model_select, "pressed",
                   G_CALLBACK(on_btn_pressed_model_select), render);

  connect_control_group(&ctrls->trans_x);
  connect_control_group(&ctrls->trans_y);
  connect_control_group(&ctrls->trans_z);

  connect_control_group(&ctrls->rotat_x);
  connect_control_group(&ctrls->rotat_y);
  connect_control_group(&ctrls->rotat_z);

  connect_control_group(&ctrls->scale);
}

void glarea_signals_connect(render_data *render, widgets_controls *ctrls) {
  // event to mouse controls: buttons and scroll
  gtk_widget_add_events(render->glarea, GDK_SCROLL_MASK);
  gtk_widget_add_events(render->glarea, GDK_BUTTON_PRESS_MASK);
  gtk_widget_add_events(render->glarea, GDK_BUTTON_RELEASE_MASK);
  gtk_widget_add_events(render->glarea, GDK_BUTTON1_MOTION_MASK);
  gtk_widget_add_events(render->glarea, GDK_BUTTON2_MOTION_MASK);
  gtk_widget_add_events(render->glarea, GDK_BUTTON3_MOTION_MASK);

  g_signal_connect(render->glarea, "realize", G_CALLBACK(on_glarea_realize), render);
  g_signal_connect(render->glarea, "render", G_CALLBACK(on_glarea_render), render);
  g_signal_connect(render->glarea, "resize", G_CALLBACK(on_glarea_resize), render);

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
  gtk_style_context_add_provider_for_screen(
      gdk_screen_get_default(),
      GTK_STYLE_PROVIDER(provider_file),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void set_model_info(model model, widgets_controls *ctrls) {
  char vertices_buf[FILENAME_LENGTH],
       edges_buf[FILENAME_LENGTH];
  gtk_label_set_label(ctrls->model_name,
                      file_from_path((char *)model.path));

  sprintf(vertices_buf, "%d", model.vertices_count);
  sprintf(edges_buf, "%d",
          model.faces_count + model.vertices_count - 2); // euler's formula

  gtk_label_set_label(ctrls->model_vertices, vertices_buf);
  gtk_label_set_label(ctrls->model_edges, edges_buf);
}
