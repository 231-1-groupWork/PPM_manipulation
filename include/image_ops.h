#ifndef IMAGE_OPS_H
#define IMAGE_OPS_H

#include "ppm_io.h"

// Fonctions de traitement d’image
void foncer(Image *img, const char *couleur, int valeur);
void eclaircir(Image *img, const char *couleur, int valeur);
void to_gray(Image *img);
void negatif(Image *img);
void print_size(const Image *img);
Image *decoupe(Image *img, int l1, int l2, int c1, int c2);
void median_filter(Image *img);
void foncer_ou_eclaircir(Image *img, char couleur, int val);
Image *decoupe(Image *img, int l1, int l2, int c1, int c2);
void median_filter(Image *img);

#endif
