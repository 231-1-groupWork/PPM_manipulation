#ifndef PPM_IO_H
#define PPM_IO_H

#include <stdio.h>

typedef struct {
    char magic[3];       // "P3" ou "P6"
    int width;
    int height;
    int max_value;
    unsigned char *data; // Tableau des pixels (R,G,B,R,G,B,...)
} Image;

// Fonctions principales
Image *read_ppm(const char *filename);
int write_ppm(const char *filename, const Image *img);
void free_image(Image *img);

#endif
