#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

void afficher_help() {
    printf("Commandes disponibles :\n");
    printf("  load <fichier>       - Charger une image PPM\n");
    printf("  save <fichier>       - Sauvegarder l'image actuelle\n");
    printf("  gris  <fichier>               - Convertir en niveaux de gris\n");
    printf("  negatif <fichier>             - Créer le négatif\n");
    printf("  taille <fichier>               - Afficher la taille de l'image\n");
    printf("  dom <C> <val> <filname>       - Foncer (val>0) ou éclaircir (val<0) la couleur dominante C (R, G, B) de |val|\n");
    printf("cut <l1> <l2> <c1> <c2> - Découper l'image entre les lignes l1-l2 et colonnes c1-c2\n");
    printf("fil <fichier> <fichier_resultat> - Appliquer un filtre médian \n");
    printf("  help                 - Afficher cette aide\n");
    printf("  exit                 - Quitter le programme\n");
}

void nettoyer_chaine(char *s) {
    s[strcspn(s, "\n")] = '\0'; // retire le '\n'
}

int clamp(int val) {
    if (val < 0 )return 0;
    if (val > 255) return 255;
    return val;
}
