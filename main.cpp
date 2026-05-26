#include <iostream>
#include <fstream>

#include "tsp.h"
#include "algorithmes.h"
#include "affichage.h"

/*
But : sauvegarder la meilleure solution trouvée dans un fichier texte.
Le fichier contient la longueur totale et la séquence des villes.
*/
void sauvegarder_solution_texte(const Solution & solution)
{
    std::ofstream fichier("solution.txt");

    if (!fichier)
    {
        std::cout << "Impossible de creer le fichier solution.txt" << std::endl;
        return;
    }

    fichier << "Longueur totale : " << solution.longueur << std::endl;
    fichier << "Sequence trouvee :" << std::endl;

    for (int i = 0; i < solution.nb_villes; ++i)
    {
        fichier << solution.ordre[i];

        if (i < solution.nb_villes - 1)
        {
            fichier << " -> ";
        }
    }

    if (solution.nb_villes > 0)
    {
        fichier << " -> " << solution.ordre[0];
    }

    fichier << std::endl;

    fichier.close();

    std::cout << "Solution sauvegardee dans solution.txt" << std::endl;
}

/*
But : traiter un fichier TSP.
On lit l'instance, on teste chaque ville comme départ,
on applique le glouton puis OR-opt rework,
et on garde la meilleure solution.
*/
void traiter_fichier(std::string nom_fichier)
{
    InstanceTSP instance;
    Solution solution_rework;

    initialiser_instance(instance);
    initialiser_solution(solution_rework);

    std::cout << "====================================" << std::endl;
    std::cout << "Lecture de " << nom_fichier << std::endl;
    std::cout << "====================================" << std::endl;

    if (lire_instance(nom_fichier, instance))
    {
        afficher_instance(instance);

        std::cout << std::endl;
        std::cout << "-- OR-opt rework a partir de la solution gloutonne --" << std::endl;

        double meilleure_longueur_rework = -1;
        int meilleur_depart_rework = 0;

        for (int depart = 0; depart < instance.nb_villes; ++depart)
        {
            Solution temp_rework;

            initialiser_solution(temp_rework);

            methode_glouton(instance, temp_rework, depart);

            amelioration_or_opt_rework(instance, temp_rework);

            if (meilleure_longueur_rework == -1 ||
                temp_rework.longueur < meilleure_longueur_rework)
            {
                meilleure_longueur_rework = temp_rework.longueur;
                meilleur_depart_rework = depart;

                liberer_solution(solution_rework);

                solution_rework.nb_villes = temp_rework.nb_villes;
                solution_rework.longueur = temp_rework.longueur;

                solution_rework.ordre = new int[temp_rework.nb_villes];

                for (int i = 0; i < temp_rework.nb_villes; ++i)
                {
                    solution_rework.ordre[i] = temp_rework.ordre[i];
                }
            }

            liberer_solution(temp_rework);
        }

        std::cout << std::endl;
        std::cout << "Solution OR-opt rework obtenue depuis le depart : "
                  << meilleur_depart_rework << std::endl;

        afficher_solution(solution_rework);

        sauvegarder_solution_texte(solution_rework);

        afficher_solution_sfml(instance, solution_rework);
    }
    else
    {
        std::cout << "Probleme lors de l'ouverture du fichier : "
                  << nom_fichier << std::endl;
    }

    liberer_solution(solution_rework);
    liberer_instance(instance);
}

/*
But : lancer le programme avec un ou plusieurs fichiers TSP donnés en argument.
Exemple :
./voyageur_de_commerce att48.tsp
*/
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage : " << argv[0] << " fichier1.tsp fichier2.tsp ..."
                  << std::endl;

        return 1;
    }

    for (int i = 1; i < argc; ++i)
    {
        std::cout << std::endl;

        traiter_fichier(argv[i]);
    }

    return 0;
}