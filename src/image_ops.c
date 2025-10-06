#include "../include/image_ops.h"
#include "../include/utils.h"
#include <stdio.h>

void to_gray(Image *img) {
    for (int i = 0; i < img->width * img->height * 3; i += 3) {
        unsigned char r = img->data[i];
        unsigned char g = img->data[i + 1];
        unsigned char b = img->data[i + 2];
        unsigned char m = (r + g + b) / 3;
        img->data[i] = img->data[i + 1] = img->data[i + 2] = m;
    }
}

void negatif(Image *img) {
    for (int i = 0; i < img->width * img->height * 3; i++)
        img->data[i] = 255 - img->data[i];
}

void print_size(const Image *img) {
    printf("%d × %d\n", img->width, img->height);
}

// autres fonctions à venir : foncer, eclaircir, decoupe, median_filter
