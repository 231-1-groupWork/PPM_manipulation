#ifndef UTILS_H
#define UTILS_H

#include "ppm_io.h"

// Fonctions utilitaires
void afficher_help();
void nettoyer_chaine(char *s);
int couleur_valide(const char *c);
int clamp(int value);//fonction pour verifier que la valeur reste entre 0 et 255.
#endif
