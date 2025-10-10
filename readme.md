# 🖼️ PPM Viewer – Manipulation d’images PPM en C

## 🎯 Objectif du projet

Ce projet consiste à réaliser un **programme interactif en C** permettant de **manipuler des images au format PPM** (*Portable Pixmap*).  
L’application offre plusieurs fonctionnalités de traitement d’image telles que l’éclaircissement, la conversion en niveaux de gris, le négatif, le découpage ou encore l’application d’un filtre médian.

Le tout se fait via une **interface en ligne de commande** du type : **ppmviewer>**


---

## 🧩 Fonctionnalités à implémenter

### 1️⃣ Foncer ou éclaircir les pixels selon leur dominante
- La **dominante** d’un pixel est la couleur primaire (R, G ou B) dont la valeur est la plus grande.
- Pour **foncer** un pixel, on **soustrait** un entier à chaque composante (R, G, B).
- Pour **éclaircir** un pixel, on **ajoute** cet entier.
- L’opération ne s’applique qu’aux pixels ayant une dominante choisie (`rouge`, `vert` ou `bleu`).

---

### 2️⃣ Conversion en niveaux de gris
- Chaque pixel `(r, g, b)` est remplacé par un pixel `(m, m, m)` où :
- L’image résultante est en noir et blanc.

---

### 3️⃣ Création du négatif
- Chaque couleur est remplacée par son complémentaire :

---

### 4️⃣ Affichage de la taille de l’image
- Le programme doit afficher :
- Exemple : `640 × 480` pour une image de 640 pixels de large et 480 de haut.

---

### 5️⃣ Découpage d’une image
- L’utilisateur choisit :
- deux lignes `l1`, `l2`
- deux colonnes `c1`, `c2`
- Le programme garde **uniquement** cette portion de l’image et l’enregistre dans un nouveau fichier.

---

### 6️⃣ Application du filtre médian
- Pour chaque pixel, on calcule la **médiane** des valeurs de son voisinage (8 voisins + lui-même).
- Chaque canal (R, G, B) est traité indépendamment.
- Ce filtre permet de **réduire le bruit** dans l’image.

---

## 💻 Interface utilisateur (CLI)

Le programme est interactif et tourne dans une boucle d’invite :


L’utilisateur peut saisir des **commandes** pour manipuler l’image.  
Exemples :


---

## 🧠 Architecture logique

Le projet peut être découpé en plusieurs modules :

| Fichier | Rôle |
|----------|------|
| `main.c` | Gère la boucle principale et l’interface utilisateur |
| `ppm_io.c / ppm_io.h` | Fonctions de lecture et écriture des fichiers PPM |
| `image_ops.c / image_ops.h` | Implémentation des opérations de traitement (gris, négatif, etc.) |
| `utils.c / utils.h` | Fonctions d’aide (parsing, validation, etc.) |

---

## 🧱 Structure de données proposée

Une image PPM peut être représentée par la structure suivante :

```c
typedef struct {
    int width;
    int height;
    int max_value;
    unsigned char *data; // Contient les valeurs RGB des pixels
} Image;
```

## Compiler le System
- Cloner le depot 
- Se deplacer dans le dossier **src**.
- Ouvrir le terminal dans ce dossier .
- Executer la commande gcc *.c  -o **nom_executable** ceci compile le programme .
- Maintenant executer le system avec  **./nom_executable**.

## Distribution des taches.

### 24F2920_kamgaTafoneEdgarColin :

- creation du depot.
- Definition de la structure du travail.
- implementation du fichier **main.c**.
- Implementation du modules  **imgage_ops**.
- Ecriture du readme.

### MOAKO EKANGO BILL ARMEL :

- implementation du **module ppm_io.c** contenant les fonctions de lecture et d'ecriture d'un fichier ppm.

### NDEMBA KAMGNE YVES WILSON : 

- implemention du module **utils** contenants les fonctions utilitaires.

### TEUKEU FOMEKONG ISMAËL : 

- implementation de la deuxieme version du projets en un fichier non modulaire **ppmviewer.c**.

### mban yigi henri edmond :

- Tester les systems dans l'espoir de reperer des bugs.
- proposer des ameliorations.

### ABENGA OGNA BERNADETTE : 

- Ecriture du **readme**
- participation a l'implementation du module **ppm_io.c**.
