# Projet Voyageur de Commerce

## Présentation

Ce projet a pour objectif de résoudre le problème du voyageur de commerce à partir de fichiers `.tsp`.

Le programme lit une instance TSP, construit une première solution avec une méthode gloutonne, puis améliore cette solution avec une méthode OR-opt rework.

Le but est de trouver un chemin passant par toutes les villes une seule fois, puis revenant à la ville de départ, avec une longueur totale la plus petite possible.

## Organisation du projet

Le projet est séparé en plusieurs fichiers pour rendre le code plus clair.

### `tsp.h` et `tsp.cpp`

Ces fichiers servent à gérer les instances TSP.

Ils permettent de :

- initialiser une instance ;
- lire un fichier `.tsp` ;
- stocker les villes ;
- stocker les distances ;
- calculer les distances à partir des coordonnées ;
- afficher les informations de l’instance.

### `algorithmes.h` et `algorithmes.cpp`

Ces fichiers contiennent les algorithmes utilisés pour construire et améliorer une solution.

Ils contiennent :

- la méthode gloutonne ;
- l’affichage de la solution ;
- l’amélioration OR-opt rework ;
- la gestion mémoire des solutions.

La méthode gloutonne construit une première solution en partant d’une ville et en choisissant à chaque étape la ville non visitée la plus proche.

La méthode OR-opt rework améliore ensuite cette solution en déplaçant certaines villes dans le trajet si cela permet de réduire la distance totale.

### `affichage.h` et `affichage.cpp`

Ces fichiers servent à gérer l’affichage graphique avec SFML.

La fonction `afficher_solution_sfml` permet d’ouvrir une fenêtre graphique et d’afficher la meilleure solution trouvée.

L’affichage montre :

- les villes sous forme de points rouges ;
- le trajet entre les villes avec des lignes noires ;
- le retour de la dernière ville vers la première.

L’affichage SFML est séparé dans un fichier à part pour garder le `main.cpp` plus lisible.

### `main.cpp`

Le fichier `main.cpp` sert à lancer le programme.

Il permet de :

- récupérer les fichiers `.tsp` donnés en argument ;
- lire chaque fichier ;
- tester chaque ville comme ville de départ ;
- appliquer la méthode gloutonne ;
- appliquer OR-opt rework ;
- garder la meilleure solution ;
- sauvegarder la solution dans `solution.txt` ;
- afficher graphiquement la solution avec SFML.

## Compilation

Le projet utilise CMake.

Le fichier `CMakeLists.txt` doit contenir les fichiers suivants :

```cmake
add_executable(voyageur_de_commerce
    main.cpp
    tsp.cpp
    algorithmes.cpp
    affichage.cpp
)