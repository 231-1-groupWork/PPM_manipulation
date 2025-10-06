#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

void afficher_help() {
    printf("Commandes disponibles :\n");
    printf("  load <fichier>       - Charger une image PPM\n");
    printf("  save <fichier>       - Sauvegarder l'image actuelle\n");
    printf("  gris                 - Convertir en niveaux de gris\n");
    printf("  negatif              - Créer le négatif\n");
    printf("  taille               - Afficher la taille de l'image\n");
    printf("  help                 - Afficher cette aide\n");
    printf("  exit                 - Quitter le programme\n");
}

void nettoyer_chaine(char *s) {
    s[strcspn(s, "\n")] = '\0'; // retire le '\n'
}

int clamp(int val, int min, int max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}
