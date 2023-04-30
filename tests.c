#include "include/listes_dynamiques.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	//Chiffres à passer par adresse dans les insertions
	const Info chiffres[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	// Initialisation
	Liste* liste = initialiser();
	if (!liste) {
		printf("Erreur d'initialisation");
		return EXIT_FAILURE;
	}
	printf("Affichage FORWARD: ");
	afficher(liste, FORWARD);
	printf("Longueur: %ld\n", longueur(liste));
	printf("estVide: %s\n", estVide(liste) ? "true" : "false");

	// insererEnTete
	printf("\ninsererEnTete 4\n");
	insererEnTete(liste, &chiffres[4]);
	printf("insererEnTete 6\n");
	insererEnTete(liste, &chiffres[6]);
	printf("insererEnTete 9\n");
	insererEnTete(liste, &chiffres[9]);

	// Affichage FORWARD et BACKWARD
	printf("Affichage FORWARD: ");
	afficher(liste, FORWARD);
	printf("Affichage BACKWARD: ");
	afficher(liste, BACKWARD);

	// insererEnQueue
	printf("\ninsererEnQueue 7\n");
	insererEnQueue(liste, &chiffres[7]);
	printf("Affichage FORWARD: ");
	afficher(liste, FORWARD);
	printf("insererEnQueue 3\n");
	insererEnQueue(liste, &chiffres[3]);
	printf("Affichage FORWARD: ");
	afficher(liste, FORWARD);
	printf("Longueur: %ld\n", longueur(liste));
	printf("estVide: %s\n", estVide(liste) ? "true" : "false");


	printf("Longueur: %ld\n", longueur(liste));
}
