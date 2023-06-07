/**
* @file gui_utils.c
* @authors mebblera@student.21-school.ru
* @authors weaveryu@student.21-school.ru
* @brief
* Utility functions to work with 3D_Viewer data.
* @copyright Copyright (c) 2023
* TODO: adjust on release
*/

#include "gui_main.h"

void set_entry_from_adjust(GtkEntry *entry, GtkAdjustment *adj) {
  char entry_buffer[ENTRY_BUFFER_SIZE];
  sprintf(entry_buffer, "%lf", gtk_adjustment_get_value(adj));
  gtk_entry_set_text(entry, entry_buffer);
}

void set_adjustment_from_entry(GtkEntry *entry, GtkAdjustment *adj) {
  const char *entry_buffer;
  char *p_entry_buffer;
  double entry_value;
  entry_buffer = gtk_entry_get_text(entry);
  entry_value = strtod(entry_buffer, &p_entry_buffer);
  if (*p_entry_buffer == '\0') {
    gtk_adjustment_set_value(adj, entry_value);
  }
}
