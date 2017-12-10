#ifndef __NEEDED_H_
#define __NEEDED_H_

#include <stdio.h>
#include <stdlib.h>

#include "../Preprocess/mainFunctions.h"

void Quit();
void on_ContinueButton_clicked();
void UnlockGreyScaleButton();
void UnlockBinarizationButton();
GdkPixbuf *ResizeImage(GdkPixbuf *pixbuf);
void DisplayImage(GtkFileChooser *chooser, GtkImage *image);
void GreyScale(GtkButton *button, GtkFileChooser *selectImage);
SDL_Surface* detection_gtk(struct matrix* matrix, SDL_Surface* image);
void Binarization(GtkButton *button, GtkImage *img);

#endif
