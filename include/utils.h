#ifndef UTILS_H
#define UTILS_H

#include "ppm_io.h"

// Fonctions utilitaires
void afficher_help();
void nettoyer_chaine(char *s);
int couleur_valide(const char *c);
int clamp(int val, int min, int max);

#endif
