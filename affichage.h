#pragma once

#include "tsp.h"
#include "algorithmes.h"

/*
But : afficher graphiquement la meilleure solution avec SFML.
La fonction ouvre une fenêtre, dessine le trajet puis les villes.
*/
void afficher_solution_sfml(const InstanceTSP & instance, const Solution & solution);
