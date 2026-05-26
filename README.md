# Projet voyageur de commerce

## Présentation

Ce projet résout le problème du voyageur de commerce à partir de fichiers au format `.tsp`.

Le but est de trouver une tournée qui passe une seule fois par chaque ville, puis qui revient à la ville de départ.

La méthode utilisée est composée de deux étapes :

1. Construction d'une première solution avec une méthode gloutonne.
2. Amélioration de cette solution avec la méthode OR-opt rework.

Le programme teste chaque ville comme ville de départ, améliore chaque solution gloutonne avec OR-opt rework, puis conserve la meilleure solution trouvée.

Un affichage graphique avec SFML a aussi été ajouté pour visualiser la tournée trouvée lorsque le fichier `.tsp` contient des coordonnées.
La solution est sauvegardée dans un fichier texte `solution.txt` .

## Fichiers du projet

Le projet contient les fichiers suivants :

- `main.cpp` : contient le programme principal et le traitement des fichiers donnés en argument. Il affiche uniquement la meilleure solution obtenue avec OR-opt rework.
- `tsp.h` : contient les structures et les prototypes liés aux instances TSP.
- `tsp.cpp` : contient les fonctions de lecture des fichiers `.tsp`, d'allocation mémoire, de calcul des distances et d'affichage de l'instance.
- `algorithmes.h` : contient la structure `Solution` et les prototypes des algorithmes.
- `algorithmes.cpp` : contient la méthode gloutonne, l'affichage d'une solution et l'amélioration OR-opt rework.
- `affichage.h` : contient le prototype de la fonction d'affichage graphique avec SFML.
- `affichage.cpp` : contient l'affichage graphique de la solution. Les villes sont affichées en rouge, le trajet en noir, et la première ville du trajet en vert.
- `CMakeLists.txt` : contient les indications permettant de compiler le projet avec CMake.
- `README.md` : explique comment compiler et exécuter le programme.

Les fichiers `.tsp` utilisés pour les tests peuvent aussi être placés dans le même dossier que les fichiers source.

## Compilation

Le projet se compile avec CMake.

Comme le projet utilise SFML pour l'affichage graphique, SFML doit être installé et relié dans le fichier `CMakeLists.txt`.

Le fichier `CMakeLists.txt` doit aussi contenir `affichage.cpp` dans la liste des fichiers du projet :

```cmake
add_executable(voyageur_de_commerce
    main.cpp
    tsp.cpp
    algorithmes.cpp
    affichage.cpp
)
cmake -S . -B build
cmake --build build
.\build\voyageur_de_commerce.exe att48.tsp
