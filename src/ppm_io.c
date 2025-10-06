#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ppm_io.h"

Image *read_ppm(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return NULL;

    Image *img = malloc(sizeof(Image));
    if (!img) return NULL;

    fscanf(fp, "%2s", img->magic);
    fscanf(fp, "%d %d", &img->width, &img->height);
    fscanf(fp, "%d", &img->max_value);

    img->data = malloc(3 * img->width * img->height);
    if (!img->data) { free(img); fclose(fp); return NULL; }

    fread(img->data, 3, img->width * img->height, fp);
    fclose(fp);
    return img;
}

int write_ppm(const char *filename, const Image *img) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return 0;

    fprintf(fp, "%s\n%d %d\n%d\n", img->magic, img->width, img->height, img->max_value);
    fwrite(img->data, 3, img->width * img->height, fp);
    fclose(fp);
    return 1;
}

void free_image(Image *img) {
    if (!img) return;
    free(img->data);
    free(img);
}
