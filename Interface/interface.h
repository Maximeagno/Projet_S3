#ifndef __NEEDED_H_
#define __NEEDED_H_

#include "../Preprocess/pixel-from-image.h"
#include "../Preprocess/pretraitement.h"
#include "../Preprocess/binarization.h"
#include "../Preprocess/text_blocks_detection.h"
#include "../Preprocess/mainFunctions.h"

#include "../Preprocess/pixel-from-image.c"
#include "../Preprocess/pretraitement.c"
#include "../Preprocess/binarization.c"
#include "../Preprocess/text_blocks_detection.c"
#include "../Preprocess/mainFunctions.c"

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
