#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "interface.h"

GtkWidget       *window, *window2, *ContinueButton2;
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
  
  gtk_builder_connect_signals(builder, NULL);
 
  //g_object_unref(builder);
 
  gtk_widget_show(window);                
  gtk_main();
 
  return 0;
}

void Quit() {
  //g_free(Image);
  //g_free(ContinueButton2);
  //g_free(selectImage);
  //g_free(window);
  //g_free(window2);
  //g_free(window3);
  //g_free(builder);
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

void Start_Preprocess(GtkButton *button, GtkFileChooser *selectImage) {
  gtk_button_set_label(button, "Continuer");
  //gtk_widget_hide(window2);
  //gtk_widget_show(window3);
  char *path = gtk_file_chooser_get_filename(selectImage);
  SDL_Surface* image = load_image(path);
  image = black_white(grey_level(image));
  SDL_SaveBMP(image, "image_1.bmp");
  GtkImage *image1 = GTK_IMAGE(gtk_builder_get_object(builder, "Image"));
  //builder = gtk_builder_new();
  gtk_image_set_from_file(image1, "image_1.bmp");
  //struct vector* res = GetVector(path);
  //free_vector(res);
}
