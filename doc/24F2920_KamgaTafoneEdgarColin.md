# 🖼️ PPM Viewer – Manipulation d’images PPM en C  

## 🎯 Objectif du projet  
Le projet **PPM Viewer** consiste à développer un **programme interactif en C** permettant de manipuler des images au format **PPM (Portable Pixmap)**.  
L’application permet plusieurs traitements d’image tels que :  
- L’éclaircissement ou l’assombrissement sélectif,  
- La conversion en niveaux de gris,  
- Le négatif,  
- Le découpage d’une portion d’image,  
- Et l’application d’un **filtre médian** pour réduire le bruit.  

Le tout s’exécute via une **interface en ligne de commande** :  
```bash
ppmviewer>
```

---

## 🧩 Fonctionnalités principales
1. **Éclaircir / foncer une image** selon la dominante (rouge, vert ou bleu).  
2. **Conversion en niveaux de gris** : chaque pixel devient `(m, m, m)`.  
3. **Création du négatif** : remplacement de chaque couleur par son complémentaire.  
4. **Affichage de la taille** de l’image (exemple : `640 × 480`).  
5. **Découpage** d’une zone spécifique de l’image.  
6. **Application du filtre médian** pour réduire le bruit.  

---

## 🧱 Structure du projet  

| Fichier | Rôle |
|----------|------|
| `main.c` | Gère la boucle principale et l’interface utilisateur |
| `ppm_io.c / ppm_io.h` | Lecture et écriture des fichiers PPM |
| `image_ops.c / image_ops.h` | Fonctions de traitement d’image |
| `utils.c / utils.h` | Fonctions utilitaires diverses |

---

## 💿 Structure de données  

```c
typedef struct {
    int width;
    int height;
    int max_value;
    unsigned char *data; // Contient les valeurs RGB des pixels
} Image;
```

---

## ⚙️ Compilation et exécution  

```bash
cd src
gcc *.c -o ppmviewer
./ppmviewer
```

---

## 👨‍💻 Contribution personnelle – *kamga tafone edgar colin*  

- 🗂️ Création du dépôt GitHub et définition de la structure du projet.  
- 🧠 Implémentation du fichier `main.c` (interface CLI et boucle principale).  
- 🧩 Développement du module `image_ops.c` (fonctions de traitement : gris, négatif, éclaircissement, etc.).  
- 🖍️ Rédaction du README principal et coordination de l’équipe.  

---

## 🚀 Objectif personnel  
Concevoir un système modulaire, clair et facilement extensible, tout en assurant une exécution fluide et une expérience utilisateur simple pour la manipulation des images PPM.

