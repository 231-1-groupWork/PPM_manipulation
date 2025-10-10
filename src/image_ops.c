#include "../include/image_ops.h"
#include "../include/utils.h"
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

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


// implementons foncer


void foncer_ou_eclaircir(Image *img, char couleur, int val) {
    if (!img || !img->data) {
        printf("Erreur : aucune image chargée.\n");
        return;
    }

    couleur = toupper(couleur); // rendre la commande insensible à la casse

    int size = img->width * img->height * 3;

    for (int i = 0; i < size; i += 3) {
        int R = img->data[i];
        int G = img->data[i + 1];
        int B = img->data[i + 2];

        // déterminer la dominante du pixel
        char dominante;
        if (R > G && R > B)
            dominante = 'R';
        else if (G > R && G > B)
            dominante = 'G';
        else if (B > R && B > G)
            dominante = 'B';
        else
            continue; // pas de dominante claire, on ignore

        // si la dominante correspond à celle demandée
        if (dominante == couleur) {
            if (val > 0) {
                // foncer → retrancher val
                R = clamp(R - val);
                G = clamp(G - val);
                B = clamp(B - val);
            } else if (val < 0) {
                // éclaircir → ajouter |val|
                int add = abs(val);
                R = clamp(R + add);
                G = clamp(G + add);
                B = clamp(B + add);
            }
        }

        // enregistrer les nouvelles valeurs
        img->data[i]     = (unsigned char)R;
        img->data[i + 1] = (unsigned char)G;
        img->data[i + 2] = (unsigned char)B;
    }

    printf("Opération terminée : %s selon la dominante %c.\n",
           (val > 0) ? "foncé" : "éclairci", couleur);
}
// autres fonctions à venir : foncer, eclaircir, decoupe, median_filter


// découper une portion de l'image en toute sécurité
Image *decoupe(Image *img, int l1, int l2, int c1, int c2) {
    if (!img || !img->data) {
        printf("Erreur : aucune image chargée.\n");
        return NULL;
    }

    // vérifier la validité des coordonnées
    if (l1 < 0 || l2 > img->height || l1 >= l2 ||
        c1 < 0 || c2 > img->width || c1 >= c2) {
        printf("Erreur : coordonnées invalides.\n");
        return NULL;
    }

    int new_width  = c2 - c1;
    int new_height = l2 - l1;

    // créer la nouvelle image
    Image *new_img = malloc(sizeof(Image));
    if (!new_img) return NULL;

    new_img->width = new_width;
    new_img->height = new_height;
    new_img->max_value = img->max_value;
    snprintf(new_img->magic, sizeof(new_img->magic), "%s", img->magic);

    // allouer correctement la mémoire selon le type de data
    new_img->data = malloc(3 * new_width * new_height * sizeof(*img->data));
    if (!new_img->data) {
        free(new_img);
        return NULL;
    }

    // copier les pixels sélectionnés
    for (int row = 0; row < new_height; row++) {
        for (int col = 0; col < new_width; col++) {
            int old_idx = ((l1 + row) * img->width + (c1 + col)) * 3;
            int new_idx = (row * new_width + col) * 3;

            new_img->data[new_idx]     = img->data[old_idx];     
            new_img->data[new_idx + 1] = img->data[old_idx + 1]; 
            new_img->data[new_idx + 2] = img->data[old_idx + 2]; 
        }
    }

    printf("Découpe effectuée : lignes %d-%d, colonnes %d-%d\n", l1, l2, c1, c2);
    return new_img;
}




// fonction utilitaire pour trier 9 valeurs et renvoyer la médiane
static unsigned char median9(unsigned char *vals, int n) {
    // tri à bulle simple car n=9 → très petit
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (vals[i] > vals[j]) {
                unsigned char tmp = vals[i];
                vals[i] = vals[j];
                vals[j] = tmp;
            }
        }
    }
    return vals[n/2]; // médiane
}

void median_filter(Image *img) {
    if (!img || !img->data) {
        printf("Erreur : aucune image chargée.\n");
        return;
    }

    int w = img->width;
    int h = img->height;

    // copie temporaire pour ne pas modifier l'image pendant le calcul
    unsigned char *tmp = malloc(3 * w * h);
    if (!tmp) return;
    for (int i = 0; i < 3*w*h; i++)
        tmp[i] = img->data[i];

    // parcours de tous les pixels
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            unsigned char voisinsR[9], voisinsG[9], voisinsB[9];
            int count = 0;

            // boucle sur le voisinage 3x3
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int ny = y + dy;
                    int nx = x + dx;
                    if (nx >=0 && nx < w && ny >=0 && ny < h) {
                        int idx = (ny*w + nx)*3;
                        voisinsR[count] = tmp[idx];
                        voisinsG[count] = tmp[idx + 1];
                        voisinsB[count] = tmp[idx + 2];
                        count++;
                    }
                }
            }

            int idx = (y*w + x)*3;
            img->data[idx]     = median9(voisinsR, count);
            img->data[idx + 1] = median9(voisinsG, count);
            img->data[idx + 2] = median9(voisinsB, count);
        }
    }

    free(tmp);
    printf("Filtre médian appliqué.\n");
}


