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

//void rm_trailing_zeros(char *str) {
//  size_t length = strlen(str), length_cnt = 0;
//  str = str + length - 1;
//  if (length > 1) {
//    while (*str == '0' && (length_cnt <= length)) {
//      *str = '\0';
//      str--;
//      length_cnt++;
//    }
//    if (*str == '.') {
//      *str = '\0';
//    }
//  }
//}

gboolean on_widget_deleted(GtkWidget *widget, GdkEvent *event, gpointer data) {
  gtk_widget_hide(widget);
  return TRUE;
}

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
    // in case value in entry is out of bounds
    double actual_val = gtk_adjustment_get_value(adj);
    if (actual_val != entry_value) {
      set_entry_from_adjust(entry, adj);
    }
  } else {
    set_entry_from_adjust(entry, adj);
  }
}

void shift_adjustment(GtkAdjustment *adj, shift_type type, double shift_value) {
  if (type == INC_FLAT) {
    gtk_adjustment_set_value(
        adj, (gtk_adjustment_get_value(adj) + shift_value));
  } else if (type == DEC_FLAT) {
    gtk_adjustment_set_value(
        adj, (gtk_adjustment_get_value(adj) - shift_value));
  } else if (type == INC_MUL) {
    double range = gtk_adjustment_get_upper(adj) -
                   gtk_adjustment_get_lower(adj);
    gtk_adjustment_set_value(adj,
                             (gtk_adjustment_get_value(adj) +
                              (shift_value * range)));
  } else if (type == DEC_MUL) {
    double range = gtk_adjustment_get_upper(adj) -
                   gtk_adjustment_get_lower(adj);
    gtk_adjustment_set_value(adj,
                             (gtk_adjustment_get_value(adj) -
                              (shift_value * range)));
  } else if (type == SET_TO_VAL) {
    gtk_adjustment_set_value(adj, shift_value);
  } else if (type == SET_TO_MIN) {
    gtk_adjustment_set_value(adj, -DBL_MAX);
  } else if (type == SET_TO_MAX) {
    gtk_adjustment_set_value(adj, DBL_MAX);
  }
}
