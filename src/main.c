#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
        else if (strncmp(commande, "gris", 4) == 0) {
            char filename[50];
            sscanf(commande, "gris %s", filename);
            if (img) free_image(img);
            img = read_ppm(filename);
            if (!img) { printf("Aucune image chargée.\n"); continue; }
            to_gray(img);
            printf("Image convertie en niveaux de gris.\n");
        }

        // ---- Commande: negatif ----
        else if (strncmp(commande, "negatif", 8) == 0) {
            char filename[50];
            sscanf(commande, "negatif %s", filename);
            if (img) free_image(img);
            img = read_ppm(filename);
            if (!img) { printf("Aucune image chargée.\n"); continue; }
            negatif(img);
            printf("Négatif appliqué.\n");
        }

        // ---- Commande: taille ----
        else if (strncmp(commande, "taille", 6) == 0) {
            char filename[50];
            sscanf(commande, "taille %s", filename);
            if (img) free_image(img);
            img = read_ppm(filename);
            if (!img) { printf("Aucune image chargée.\n"); continue; }
            print_size(img);
        }

        else if (strncmp(commande,"dom",3)==0){
            //if (!img) { printf("Aucune image chargée.\n"); continue; }
            char couleur;
            int val;
            char filname[50];
            if (sscanf(commande, "dom %c %d %s", &couleur, &val, filname) == 3) {
                img = read_ppm(filname);
                if (!img) { printf("Aucune image chargée.\n"); continue; }
                //val doit etre entre -
                if (val < -255 || val > 255) {
                    printf("Erreur : la valeur doit être entre -255 et 255.\n");
                    continue;
                }
                couleur = toupper(couleur);
                if (couleur != 'R' && couleur != 'G' && couleur != 'B') {
                    printf("Erreur : la couleur doit être R, G ou B.\n");
                    continue;
                }
                foncer_ou_eclaircir(img, couleur, val);
                if (val > 0)
                    printf("Image foncée sur la dominante %c de %d.\n", couleur, val);
                else
                    printf("Image éclaircie sur la dominante %c de %d.\n", couleur, -val);
            } else {
                printf("Usage: dom <R|G|B> <valeur entre -255 et 255>\n");
            }
        }  
        
        else if (strncmp(commande,"cut",3)==0){
            //if (!img) { printf("Aucune image chargée.\n"); continue; }
            int l1, l2, c1, c2;
            char filname[50];
            char store[50];
            if (sscanf(commande, "cut %s %d %d %d %d %s", filname,&l1, &l2, &c1, &c2,store) == 6) {
                img = read_ppm(filname);
                if (!img) { printf("Aucune image chargée.\n"); continue; }
                Image *new_img = decoupe(img, l1, l2, c1, c2);
                if (new_img) {
                    write_ppm(store, new_img);
                    printf("Image découpée : nouvelle taille %d x %d.\n", new_img->width, new_img->height);
                } else {
                    printf("Erreur lors de la découpe de l'image.\n");
                }
            } else {
                printf("Usage: cut <l1> <l2> <c1> <c2>\n");
            }
        }
        // filtre median 

        else if (strncmp(commande, "fil",3)==0) {
            char filename[50];
            char store[50];
            if (sscanf(commande, "fil %s %s", filename, store) == 2) {
                img = read_ppm(filename);
                if (!img) { printf("Aucune image chargée.\n"); continue; }
                median_filter(img);
                write_ppm(store, img);
                printf("Filtre médian appliqué et image sauvegardée sous '%s'.\n", store);
            } else {
                printf("Usage: fil <input_filename> <output_filename>\n");
            }
            median_filter(img);
            printf("Filtre médian appliqué.\n");
        }

        else {
            printf("Commande inconnue. Tapez 'help' pour la liste des commandes.\n");
        }
    }

    if (img) free_image(img);
    printf("Programme terminé.\n");
    return 0;
}
