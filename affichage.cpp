#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>

#include "affichage.h"

/*
- on ouvre une fenêtre ;
- on adapte les coordonnées à la taille de la fenêtre ;
- on trace les lignes du trajet en noir ;
- on trace les villes avec des points rouges ;
- la première ville du trajet est affichée en vert.
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
        Les villes normales sont en rouge.
        La première ville du trajet est en vert et un peu plus grosse.
        */
        for (int i = 0; i < instance.nb_villes; ++i)
        {
            float x = marge + (instance.villes[i].x - min_x) * (largeur - 2 * marge) / ecart_x;
            float y = marge + (instance.villes[i].y - min_y) * (hauteur - 2 * marge) / ecart_y;

            sf::CircleShape point(4);
            point.setFillColor(sf::Color::Red);

            if (i == solution.ordre[0])
            {
                point.setRadius(7);
                point.setFillColor(sf::Color::Green);
                point.setPosition(sf::Vector2f(x - 7, y - 7));
            }
            else
            {
                point.setPosition(sf::Vector2f(x - 4, y - 4));
            }

            fenetre.draw(point);
        }

        fenetre.display();
    }
}