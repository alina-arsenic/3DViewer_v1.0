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

char *file_from_path(char *pathname)
{
  char *fname = NULL;
  if (pathname)
  {
    fname = strrchr (pathname, '/') + 1;
  }
  return fname;
}
// to read filename:
//int main (void)
//{
//  char pathname[] = "/Users/abc/Desktop/xyz/test.s";
//  char *fname = file_from_path (pathname);
//
//  printf ("path \"%s\", filename \"%s\"\n", pathname,
//         fname != NULL ? fname : "(null)");
//
//  return 0;
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

void get_entry_adjustment(GtkEntry *target, GtkAdjustment *adj);

// TODO: refactor to separated method for duplicates?
void read_entry_on_change(GtkEntry *target, widgets_controls* ctrls) {
  controls_group c_group;
  if (target == ctrls->trans_x.entry) {
    c_group = ctrls->trans_x;
  } else if (target == ctrls->trans_y.entry) {
    c_group = ctrls->trans_y;
  } else if (target == ctrls->trans_z.entry) {
    c_group = ctrls->trans_z;
  } else if (target == ctrls->rotat_x.entry) {
    c_group = ctrls->rotat_x;
  } else if (target == ctrls->rotat_y.entry) {
    c_group = ctrls->rotat_y;
  } else if (target == ctrls->rotat_z.entry) {
    c_group = ctrls->rotat_z;
  } else if (target == ctrls->scale.entry) {
    c_group = ctrls->scale;
  }

  set_adjustment_from_entry(c_group.entry, c_group.adj);
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

double get_adjustment_range(GtkAdjustment *adj) {
  return (gtk_adjustment_get_upper(adj) -
          gtk_adjustment_get_lower(adj));
}

void shift_adjustment(GtkAdjustment *adj, shift_type type, double shift_value) {
  if (type == INC_FLAT) {
    gtk_adjustment_set_value(
        adj, (gtk_adjustment_get_value(adj) + shift_value));
  } else if (type == DEC_FLAT) {
    gtk_adjustment_set_value(
        adj, (gtk_adjustment_get_value(adj) - shift_value));
  } else if (type == INC_MUL) {
    double range = get_adjustment_range(adj);
    gtk_adjustment_set_value(adj,
                             (gtk_adjustment_get_value(adj) +
                              (shift_value * range)));
  } else if (type == DEC_MUL) {
    double range = get_adjustment_range(adj);
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

gboolean is_key(unsigned int keyval, char key) {
  gboolean res = FALSE;
  if (key == 'A') {
    res = keyval_compare(keyval, GDK_KEY_A, GDK_KEY_a, GDK_KEY_Cyrillic_ef,
                         GDK_KEY_Cyrillic_EF, 0);
  } else if (key == 'D') {
    res = keyval_compare(keyval, GDK_KEY_D, GDK_KEY_d, GDK_KEY_Cyrillic_ve,
                         GDK_KEY_Cyrillic_VE, 0);
  } else if (key == 'S') {
    res = keyval_compare(keyval, GDK_KEY_S, GDK_KEY_s,
                         GDK_KEY_Cyrillic_yeru, GDK_KEY_Cyrillic_YERU, 0);
  } else if (key == 'W') {
    res = keyval_compare(keyval, GDK_KEY_W, GDK_KEY_w, GDK_KEY_Cyrillic_tse,
                         GDK_KEY_Cyrillic_TSE, 0);
  } else if (key == 'Q') {
    res = keyval_compare(keyval, GDK_KEY_Q, GDK_KEY_q,
                         GDK_KEY_Cyrillic_shorti, GDK_KEY_Cyrillic_SHORTI, 0);
  } else if (key == 'E') {
    res = keyval_compare(keyval, GDK_KEY_E, GDK_KEY_e, GDK_KEY_Cyrillic_u,
                         GDK_KEY_Cyrillic_U, 0);
  } else if (key == '-') {
    res = keyval_compare(keyval, GDK_KEY_minus, GDK_KEY_KP_Subtract, 0);
  } else if (key == '+') {
    res = keyval_compare(keyval, GDK_KEY_plus, GDK_KEY_KP_Add,
                         GDK_KEY_equal, 0);
  } else if (key == 'R') {
    res = keyval_compare(keyval, GDK_KEY_R, GDK_KEY_r, GDK_KEY_Cyrillic_ka,
                         GDK_KEY_Cyrillic_KA, 0);
  }
  return (res);
}

gboolean keyval_compare(unsigned int ref, ...) {
  va_list marker;
  unsigned int buffer = ref;
  gboolean equal = FALSE;
  va_start(marker, ref);

  while (buffer != 0 && !equal) {
    buffer = va_arg(marker, unsigned int);
    equal = (ref == buffer) ? TRUE : FALSE;
  }
  va_end(marker);
  return (equal);
}

void reset_scale(widgets_controls *ctrl) {
  shift_adjustment(ctrl->trans_x.adj, SET_TO_VAL, 0);
  shift_adjustment(ctrl->trans_y.adj, SET_TO_VAL, 0);
  shift_adjustment(ctrl->trans_z.adj, SET_TO_VAL, 0);
  shift_adjustment(ctrl->rotat_x.adj, SET_TO_VAL, 0);
  shift_adjustment(ctrl->rotat_y.adj, SET_TO_VAL, 0);
  shift_adjustment(ctrl->rotat_z.adj, SET_TO_VAL, 0);
  shift_adjustment(ctrl->scale.adj, SET_TO_VAL, 10);
}

void read_path_from_entry(GtkEntry *entry, char *path) {
  const char *entry_buffer;
  entry_buffer = gtk_entry_get_text(entry);

  if (access(entry_buffer, F_OK) == 0) {
    sprintf(path, "%s", entry_buffer);
  } else {
    sprintf(path, "%s", "Incorrect path");
  }
}
