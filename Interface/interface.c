#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "interface.h"

GtkWidget       *window, *window2;
GtkBuilder      *builder;

int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "window_main.glade", NULL);

  window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
  window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window_2"));

  gtk_builder_connect_signals(builder, NULL);

  //g_object_unref(builder);

  gtk_widget_show(window);                
  gtk_main();

  return 0;
}

void Quit() {
  //gtk_widget_destroy(Image);
  //gtk_widget_destroy(selectImage);
  //gtk_widget_destroy(window);
  //g_free(window2);
  //g_free(builder);
  gtk_main_quit();
}

void on_ContinueButton_clicked() {
  gtk_widget_hide(window);
  gtk_widget_show(window2);
}

void UnlockGreyScaleButton() {
  GtkWidget *GreyScale_button = GTK_WIDGET(gtk_builder_get_object(builder, "grey_scale_button"));
  gtk_widget_set_sensitive(GreyScale_button, TRUE);
}

void UnlockBinarizationButton() {
  GtkWidget *Binarization_button = GTK_WIDGET(gtk_builder_get_object(builder, "binarization_button"));
  gtk_widget_set_sensitive(Binarization_button, TRUE);
}


GdkPixbuf *ResizeImage(GdkPixbuf *pixbuf)
{
  int orig_width = gdk_pixbuf_get_width(pixbuf);
  int orig_height = gdk_pixbuf_get_height(pixbuf);

  if (orig_width > 600 || orig_height > 400) {
     orig_width = 600;
     orig_height = 400;
  }
  GdkPixbuf *new_pixbuf = gdk_pixbuf_scale_simple(pixbuf, orig_width, orig_height, GDK_INTERP_BILINEAR);
  return new_pixbuf;
}

void DisplayImage(GtkFileChooser *chooser, GtkImage *image) {
  GtkFileChooser *selectImage = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "selectImage"));
  char *path = gtk_file_chooser_get_filename(selectImage);
  
  gtk_image_set_from_file(image, path);

  //Resize image
  GdkPixbuf *pixbuf = gtk_image_get_pixbuf(image);
  GdkPixbuf *new_pixbuf = ResizeImage(pixbuf);
  gtk_image_set_from_pixbuf(image, new_pixbuf);
  gtk_file_chooser_set_filename(chooser, path);

  g_free(path);
}

void GreyScale(GtkButton *button, GtkFileChooser *selectImage) {
  gtk_button_set_label(button, "Grey Scale");
  char *path = gtk_file_chooser_get_filename(selectImage);
  SDL_Surface* image = load_image(path);
  image = black_white(grey_level(image));
  SDL_SaveBMP(image, "image_1.bmp");
  GtkImage *image1 = GTK_IMAGE(gtk_builder_get_object(builder, "Image"));
  gtk_image_set_from_file(image1, "image_1.bmp");

  //Resize
  GdkPixbuf *pixbuf = gtk_image_get_pixbuf(image1);
  GdkPixbuf *new_pixbuf = ResizeImage(pixbuf);
  gtk_image_set_from_pixbuf(image1, new_pixbuf);

  //g_object_unref(pixbuf);
  g_object_unref(new_pixbuf);
  SDL_FreeSurface(image);
}

SDL_Surface* detection_gtk(struct matrix* matrix, SDL_Surface* image) {
  image = lines(image, 0);
  image = columns(matrix, image);
  return image;
}
void Binarization(GtkButton *button, GtkImage *img) {
  gtk_button_set_label(button, "Binarize");
  SDL_Surface* image = load_image("image_1.bmp");
  struct matrix* res = binarization(image);
  image = detection_gtk(res, image);

  SDL_SaveBMP(image, "image_1.bmp");
  gtk_image_set_from_file(img, "image_1.bmp");


  //Resize
  GdkPixbuf *pixbuf = gtk_image_get_pixbuf(img);
  GdkPixbuf *new_pixbuf = ResizeImage(pixbuf);
  gtk_image_set_from_pixbuf(img, new_pixbuf);

  //struct vector *vect = blocks_detection(matrix, image);

  //free_vector(res);
  //g_object_unref(pixbuf);
  g_object_unref(new_pixbuf);
  free_matrix(res);
  SDL_FreeSurface(image);
}

void Save(GtkButton *button, GtkLabel *label)
{
  gtk_button_set_label(button, "Save");
  GtkWindow *window_parent = GTK_WINDOW(gtk_builder_get_object(builder, "window_2"));
  GtkWidget *dialog;
  GtkFileChooser *chooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Save File",
                                      window_parent,
                                      action,
                                      ("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                      ("_Save"),
                                      GTK_RESPONSE_ACCEPT,
                                      NULL);
  chooser = GTK_FILE_CHOOSER (dialog);
  gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);
  res = gtk_dialog_run (GTK_DIALOG (dialog));

  if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;

    filename = gtk_file_chooser_get_filename (chooser);

    FILE *file = NULL;
    file = fopen(filename, "w");

    if (file == NULL)
      printf("impossible\n");
    else {
      const char *s;
      s = gtk_label_get_text(label);
      fprintf(file, "%s\n", s);
      fclose(file);
    }
    g_free (filename);
  }

  gtk_widget_destroy (dialog);
}
