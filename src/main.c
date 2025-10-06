#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ppm_io.h"
#include "../include/image_ops.h"
#include "../include/utils.h"

int main() {
    Image *img = NULL;
    char commande[128];

    printf("Bienvenue dans PPM Viewer !\n");
    printf("Tapez 'help' pour voir la liste des commandes.\n");

    while (1) {
        printf("ppmviewer> ");
        if (!fgets(commande, sizeof(commande), stdin))
            break;

        nettoyer_chaine(commande);

        // ---- Commande: exit ----
        if (strcmp(commande, "exit") == 0) {
            break;
        }

        // ---- Commande: help ----
        else if (strcmp(commande, "help") == 0) {
            afficher_help();
        }

        // ---- Commande: load ----
        else if (strncmp(commande, "load ", 5) == 0) {
            char *filename = commande + 5;
            if (img) free_image(img);
            img = read_ppm(filename);
            if (img)
                printf("Image '%s' chargée (%d x %d)\n", filename, img->width, img->height);
            else
                printf("Erreur : impossible de charger '%s'\n", filename);
        }

        // ---- Commande: save ----
        else if (strncmp(commande, "save ", 5) == 0) {
            if (!img) { printf("Aucune image chargée.\n"); continue; }
            char *filename = commande + 5;
            write_ppm(filename, img);
            printf("Image enregistrée sous '%s'\n", filename);
        }

        // ---- Commande: gris ----
        else if (strcmp(commande, "gris") == 0) {
            if (!img) { printf("Aucune image chargée.\n"); continue; }
            to_gray(img);
            printf("Image convertie en niveaux de gris.\n");
        }

        // ---- Commande: negatif ----
        else if (strcmp(commande, "negatif") == 0) {
            if (!img) { printf("Aucune image chargée.\n"); continue; }
            negatif(img);
            printf("Négatif appliqué.\n");
        }

        // ---- Commande: taille ----
        else if (strcmp(commande, "taille") == 0) {
            if (!img) { printf("Aucune image chargée.\n"); continue; }
            print_size(img);
        }

        else {
            printf("Commande inconnue. Tapez 'help' pour la liste des commandes.\n");
        }
    }

    if (img) free_image(img);
    printf("Programme terminé.\n");
    return 0;
}
