# Projet voyageur de commerce

## Présentation

Ce projet résout le problème du voyageur de commerce à partir de fichiers au format `.tsp`.

Le but est de trouver une tournée qui passe une seule fois par chaque ville, puis qui revient à la ville de départ.

La méthode utilisée est composée de deux étapes :

1. Construction d'une première solution avec une méthode gloutonne.
2. Amélioration de cette solution avec la méthode OR-opt.

Le programme teste chaque ville comme ville de départ, puis conserve la meilleure solution trouvée.

## Fichiers du projet

Le projet contient les fichiers suivants :

- `main.cpp` : contient le programme principal et le traitement des fichiers donnés en argument.
- `tsp.h` : contient les structures et les prototypes liés aux instances TSP.
- `tsp.cpp` : contient les fonctions de lecture des fichiers .tsp, d'allocation mémoire, de calcul des distances et d'affichage de l'instance.
- `algorithmes.h` : contient la structure Solution et les prototypes des algorithmes.
- `algorithmes.cpp` : contient la méthode gloutonne, l'affichage d'une solution et l'amélioration OR-opt.
- `CMakeLists.txt` : contient les indications permettant de compiler le projet avec CMake.
- `README.md` : explique comment compiler et exécuter le programme.

Les fichiers .tsp utilisés pour les tests peuvent aussi être placés dans le même dossier que les fichiers source.

## Compilation

Le projet se compile avec CMake.

Depuis le dossier principal du projet, utiliser les commandes suivantes :

```bash
cmake -S . -B build
cmake --build build
.\voyageur_de_commerce.exe att48.tsp
