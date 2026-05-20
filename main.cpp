#include <iostream>
#include "tsp.h"
#include "algorithmes.h"
/*
But : traiter complètement un fichier TSP.
La fonction lit d'abord l'instance contenue dans le fichier.
Ensuite, elle teste l'algorithme glouton en prenant chaque ville comme ville de départ.
Elle garde la meilleure solution gloutonne trouvée.
Puis elle applique OR-opt pour essayer d'améliorer les solutions obtenues.
À la fin, elle affiche la meilleure solution gloutonne et la meilleure solution améliorée.
*/
void traiter_fichier(std::string nom_fichier)
{
    InstanceTSP instance;
    Solution solution;
    Solution solution_or_opt;
    Solution solution_rework;

    initialiser_instance(instance);
    initialiser_solution(solution);
    initialiser_solution(solution_or_opt);
    initialiser_solution(solution_rework); 

    std::cout << "====================================" << std::endl;
    std::cout << "Lecture de " << nom_fichier << std::endl;
    std::cout << "====================================" << std::endl;

    if (lire_instance(nom_fichier, instance))
    {
        afficher_instance(instance);

        std::cout << std::endl;
        std::cout << "Algorithme glouton + OR-opt + OR-opt rework :" << std::endl; 

        double meilleure_longueur = -1;
        double meilleure_longueur_or_opt = -1;
        double meilleure_longueur_rework = -1; 

        int meilleur_depart = 0;
        int meilleur_depart_or_opt = 0;
        int meilleur_depart_rework = 0; 

        for (int depart = 0; depart < instance.nb_villes; ++depart)
        {
            Solution temp;
            Solution temp_or_opt;
            Solution temp_rework; 

            initialiser_solution(temp);
            initialiser_solution(temp_or_opt);
            initialiser_solution(temp_rework); 

            methode_glouton(instance, temp, depart);

            // Copie de la solution gloutonne pour l'ancien OR-opt
            temp_or_opt.nb_villes = temp.nb_villes;
            temp_or_opt.longueur = temp.longueur;
            temp_or_opt.ordre = new int[temp.nb_villes];

            for (int i = 0; i < temp.nb_villes; ++i)
            {
                temp_or_opt.ordre[i] = temp.ordre[i];
            }

            // copie de la solution gloutonne pour OR-opt rework
            temp_rework.nb_villes = temp.nb_villes;
            temp_rework.longueur = temp.longueur;
            temp_rework.ordre = new int[temp.nb_villes];

            for (int i = 0; i < temp.nb_villes; ++i)
            {
                temp_rework.ordre[i] = temp.ordre[i];
            }

            // Ancienne amélioration OR-opt
            amelioration_or_opt(instance, temp_or_opt);

            // nouvelle amélioration OR-opt rework
            amelioration_or_opt_rework(instance, temp_rework);

            // Meilleure solution gloutonne
            if (meilleure_longueur == -1 ||
                temp.longueur < meilleure_longueur)
            {
                meilleure_longueur = temp.longueur;
                meilleur_depart = depart;

                liberer_solution(solution);

                solution.nb_villes = temp.nb_villes;
                solution.longueur = temp.longueur;
                solution.ordre = new int[temp.nb_villes];

                for (int i = 0; i < temp.nb_villes; ++i)
                {
                    solution.ordre[i] = temp.ordre[i];
                }
            }

            // Meilleure solution avec ancien OR-opt
            if (meilleure_longueur_or_opt == -1 ||
                temp_or_opt.longueur < meilleure_longueur_or_opt)
            {
                meilleure_longueur_or_opt = temp_or_opt.longueur;
                meilleur_depart_or_opt = depart;

                liberer_solution(solution_or_opt);

                solution_or_opt.nb_villes = temp_or_opt.nb_villes;
                solution_or_opt.longueur = temp_or_opt.longueur;
                solution_or_opt.ordre = new int[temp_or_opt.nb_villes];

                for (int i = 0; i < temp_or_opt.nb_villes; ++i)
                {
                    solution_or_opt.ordre[i] = temp_or_opt.ordre[i];
                }
            }

            // meilleure solution avec OR-opt rework
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

            liberer_solution(temp);
            liberer_solution(temp_or_opt);
            liberer_solution(temp_rework); 
        }

        std::cout << std::endl;
        std::cout << "Meilleur depart glouton : " << meilleur_depart << std::endl;
        afficher_solution(solution);

        std::cout << std::endl;
        std::cout << "Solution OR-opt obtenue depuis le depart : "
                  << meilleur_depart_or_opt << std::endl;
        afficher_solution(solution_or_opt);

        
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

    liberer_solution(solution);
    liberer_solution(solution_or_opt);
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
//.\voyageur_de_commerce.exe att48.tsp