#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ppm_io.h"
#include <ctype.h>
/*Image *read_ppm(const char *filename) {
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
}*/



// Helper to skip comments and whitespace
void skip_comments(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (isspace(c)) {
            continue; // skip whitespace
        } else if (c == '#') {
            // skip the rest of the line                                     //remember to add the prototype in the header file
            while ((c = fgetc(fp)) != EOF && c != '\n');
        } else {
            // put back the non-comment character for fscanf
            ungetc(c, fp);
            break;
        }
    }
}

// Read PPM P3 (ASCII) image with comment support
Image *read_ppm(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("Error opening file"); return NULL; }

    Image *img = malloc(sizeof(Image));
    if (!img) { fclose(fp); printf("Error allocating memory for image\n"); return NULL; }

    skip_comments(fp);
    fscanf(fp, "%2s", img->magic);

    skip_comments(fp);
    fscanf(fp, "%d", &img->width);

    skip_comments(fp);
    fscanf(fp, "%d", &img->height);

    skip_comments(fp);
    fscanf(fp, "%d", &img->max_value);

    img->data = malloc(3 * img->width * img->height * sizeof(int));
    if (!img->data) { free(img); fclose(fp); printf("Error allocating memory for image data\n"); return NULL; }

    for (int i = 0; i < 3 * img->width * img->height; i++) {
        skip_comments(fp);
        fscanf(fp, "%d", &img->data[i]);
    }

    fclose(fp);
    return img;
}

// Write PPM P3 (ASCII) image
int write_ppm(const char *filename, const Image *img) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return 0;

    fprintf(fp, "%s\n%d %d\n%d\n", img->magic, img->width, img->height, img->max_value);

    for (int i = 0; i < 3 * img->width * img->height; i++) {
        fprintf(fp, "%d ", img->data[i]);
        if ((i + 1) % 3 == 0) fprintf(fp, "\n");  // newline after each pixel
    }

    fclose(fp);
    return 1;
}

// Free image memory
void free_image(Image *img) {
    if (!img) return;
    free(img->data);
    free(img);
}

