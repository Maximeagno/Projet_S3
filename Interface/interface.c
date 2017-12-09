#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
//#include "interface.h"

GtkWidget       *window, *window2, *Image, *ContinueButton2;
GtkBuilder      *builder;
GtkFileChooser  *selectImage;

int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "window_main.glade", NULL);
 
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
  window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window_2"));
  ContinueButton2 = GTK_WIDGET(gtk_builder_get_object(builder, "ContinueButton2"));
  selectImage = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "selectImage"));
  Image = GTK_WIDGET(gtk_builder_get_object(builder, "Image"));
  
  gtk_builder_connect_signals(builder, NULL);
 
  g_object_unref(builder);
 
  gtk_widget_show(window);                
  gtk_main();
 
  return 0;
}

void Quit() {
  gtk_main_quit();
}

void on_ContinueButton_clicked() {
  gtk_widget_hide(window);
  gtk_widget_show(window2);
}

void UnlockButton() {
  gtk_widget_set_sensitive(ContinueButton2, TRUE);
}

GdkPixbuf *ResizeImage(GdkPixbuf *pixbuf)
{
  int orig_width = gdk_pixbuf_get_width(pixbuf);
  int orig_height = gdk_pixbuf_get_height(pixbuf);

  if (orig_width > 640 || orig_height > 480) {
     orig_width = 640;
     orig_height = 480;
  }
  GdkPixbuf *new_pixbuf = gdk_pixbuf_scale_simple(pixbuf, orig_width, orig_height, GDK_INTERP_BILINEAR);
  return new_pixbuf;
}

void DisplayImage(GtkFileChooser *chooser, GtkImage *image) {
  char *path = gtk_file_chooser_get_filename(selectImage);
  
  gtk_image_set_from_file(image, path);

  //Resize image
  GdkPixbuf *pixbuf = gtk_image_get_pixbuf(image);
  GdkPixbuf *new_pixbuf = ResizeImage(pixbuf);
  gtk_image_set_from_pixbuf(image, new_pixbuf);

  gtk_file_chooser_set_filename(chooser, path);
}

/*void Start_Preprocess(GtkButton *button, GtkFileChooser *selectImage) {
  char *path = gtk_file_chooser_get_filename(selectImage);
  struct matrix* res = GetMatrix(path);

  print_matrix(res);

  free_matrix(res);
  }*/
