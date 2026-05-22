#include <iostream>
#include "tsp.h"
#include "algorithmes.h"

/*
But : traiter un fichier TSP.
On lit l'instance, puis on construit une solution gloutonne pour chaque ville de depart.
Ensuite, on améliore chaque solution avec OR-opt rework.
On garde uniquement la meilleure solution obtenue avec OR-opt rework.
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
        std::cout << "OR-opt rework a partir d'une solution gloutonne :" << std::endl;

        double meilleure_longueur_rework = -1;
        int meilleur_depart_rework = 0;

        for (int depart = 0; depart < instance.nb_villes; ++depart)
        {
            Solution temp_rework;

            initialiser_solution(temp_rework);

            // On construit d'abord une solution gloutonne
            methode_glouton(instance, temp_rework, depart);

            // Puis on améliore cette solution avec OR-opt rework
            amelioration_or_opt_rework(instance, temp_rework);

            // On garde la meilleure solution OR-opt rework trouvée
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
    }
    else
    {
        std::cout << "Probleme lors de l'ouverture du fichier : "
                  << nom_fichier << std::endl;
    }

    liberer_solution(solution_rework);
    liberer_instance(instance);
}

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

// Exemple d'execution :
// .\voyageur_de_commerce.exe att48.tsp