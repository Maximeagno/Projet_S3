#ifndef __NEEDED_H_
#define __NEEDED_H_

#include <stdio.h>
#include <stdlib.h>

#include "../Preprocess/mainFunctions.h"
#include "../ReseauNew/alphabet.h"
#include "../ReseauNew/add.h"
#include "../ReseauNew/class.h"
#include "../ReseauNew/link.h"

void Quit();
void on_ContinueButton_clicked();
void UnlockBinarizationButton();
void UnlockSegmentationButton();
void UnlockRButton();
void UnlockSButton();
GdkPixbuf *ResizeImage(GdkPixbuf *pixbuf);
void DisplayImage(GtkFileChooser *chooser, GtkImage *image);
void Binarization(GtkButton *button, GtkFileChooser *selectImage);
SDL_Surface* detection_gtk(struct matrix* matrix, SDL_Surface* image);
void Segmentation(GtkButton *button, GtkImage *img);
void SaveLabel(GtkButton *button, GtkLabel *label);
void Run(GtkButton *button, GtkLabel *label);
#endif
