#include <iostream>
#include <fstream>
#include <optional>
#include <SFML/Graphics.hpp>

#include "tsp.h"
#include "algorithmes.h"

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
But : afficher graphiquement la solution avec SFML.

Version simple :
- on ouvre une fenêtre ;
- on adapte les coordonnées à la taille de la fenêtre ;
- on trace les lignes du trajet en noir ;
- on trace les villes avec des points rouges.
*/
void afficher_solution_sfml(const InstanceTSP & instance, const Solution & solution)
{
    if (!instance.possede_coordonnees)
    {
        std::cout << "Pas de coordonnees, affichage SFML impossible." << std::endl;
        return;
    }

    int largeur = 1000;
    int hauteur = 800;
    int marge = 50;

    sf::RenderWindow fenetre(
        sf::VideoMode(sf::Vector2u(largeur, hauteur)),
        "Voyageur de commerce"
    );

    double min_x = instance.villes[0].x;
    double max_x = instance.villes[0].x;
    double min_y = instance.villes[0].y;
    double max_y = instance.villes[0].y;

    for (int i = 0; i < instance.nb_villes; ++i)
    {
        if (instance.villes[i].x < min_x)
        {
            min_x = instance.villes[i].x;
        }

        if (instance.villes[i].x > max_x)
        {
            max_x = instance.villes[i].x;
        }

        if (instance.villes[i].y < min_y)
        {
            min_y = instance.villes[i].y;
        }

        if (instance.villes[i].y > max_y)
        {
            max_y = instance.villes[i].y;
        }
    }

    double ecart_x = max_x - min_x;
    double ecart_y = max_y - min_y;

    if (ecart_x == 0)
    {
        ecart_x = 1;
    }

    if (ecart_y == 0)
    {
        ecart_y = 1;
    }

    while (fenetre.isOpen())
    {
        while (const std::optional event = fenetre.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                fenetre.close();
            }
        }

        fenetre.clear(sf::Color::White);

        /*
        Partie 1 : dessiner le trajet.
        On relie chaque ville à la ville suivante.
        Le modulo permet de relier la dernière ville à la première.
        */
        for (int i = 0; i < solution.nb_villes; ++i)
        {
            int ville_a = solution.ordre[i];
            int ville_b = solution.ordre[(i + 1) % solution.nb_villes];

            float x1 = marge + (instance.villes[ville_a].x - min_x) * (largeur - 2 * marge) / ecart_x;
            float y1 = marge + (instance.villes[ville_a].y - min_y) * (hauteur - 2 * marge) / ecart_y;

            float x2 = marge + (instance.villes[ville_b].x - min_x) * (largeur - 2 * marge) / ecart_x;
            float y2 = marge + (instance.villes[ville_b].y - min_y) * (hauteur - 2 * marge) / ecart_y;

            sf::Vertex ligne[2];

            ligne[0].position = sf::Vector2f(x1, y1);
            ligne[0].color = sf::Color::Black;

            ligne[1].position = sf::Vector2f(x2, y2);
            ligne[1].color = sf::Color::Black;

            fenetre.draw(ligne, 2, sf::PrimitiveType::Lines);
        }

        /*
        Partie 2 : dessiner les villes.
        Chaque ville est représentée par un petit point rouge.
        */
        for (int i = 0; i < instance.nb_villes; ++i)
        {
            float x = marge + (instance.villes[i].x - min_x) * (largeur - 2 * marge) / ecart_x;
            float y = marge + (instance.villes[i].y - min_y) * (hauteur - 2 * marge) / ecart_y;

            sf::CircleShape point(4);
            point.setFillColor(sf::Color::Red);
            point.setPosition(sf::Vector2f(x - 4, y - 4));

            fenetre.draw(point);
        }

        fenetre.display();
    }
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