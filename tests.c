#include "include/listes_dynamiques.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define afficherForward()                                                           \
	do {                                                                             \
		printf("Affichage FORWARD: ");                                                \
		afficher(liste, FORWARD);                                                     \
	} while (0)

int main(void) {
	//Chiffres à passer par adresse dans les insertions
	const Info chiffres[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	Status status;
	Info* valeurElement = calloc(1, sizeof(Info));

	// Tests initialisation
	printf("Tests initialisation\n");
	Liste* liste = initialiser();
	if (!liste) {
		printf("Erreur d'initialisation de liste");
		return EXIT_FAILURE;
	}
	afficherForward();
	printf("Longueur: %ld\n", longueur(liste));
	assert(longueur(liste) == 0);
	printf("estVide: %s\n", estVide(liste) ? "true" : "false");
	assert(estVide(liste));

	// Tests insererEnTete
	printf("\nTests insererEnTete 4\n");
	status = insererEnTete(liste, &chiffres[4]);
	assert(status == OK);
	assert(liste->tete->info == 4);
	assert(liste->queue->info == 4);
	printf("insererEnTete 6\n");
	insererEnTete(liste, &chiffres[6]);
	assert(liste->tete->info == 6);
	assert(liste->queue->info == 4);
	printf("insererEnTete 9\n");
	insererEnTete(liste, &chiffres[9]);
	assert(liste->tete->info == 9);
	assert(longueur(liste) == 3);

	// Tests affichage FORWARD et BACKWARD
	afficherForward();
	printf("Affichage BACKWARD: ");
	afficher(liste, BACKWARD);

	// Tests insererEnQueue
	printf("\nTests insererEnQueue 7\n");
	assert(liste->queue->info == 4);
	status = insererEnQueue(liste, &chiffres[7]);
	assert(status == OK);
	assert(liste->queue->info == 7);
	afficherForward();
	printf("insererEnQueue 3\n");
	insererEnQueue(liste, &chiffres[3]);
	assert(liste->queue->info == 3);
	afficherForward();
	printf("Longueur: %ld\n", longueur(liste));
	assert(longueur(liste) == 5);
	printf("estVide: %s\n", estVide(liste) ? "true" : "false");
	assert(estVide(liste) == false);

	// Tests supprimerEnTete
	printf("\nTests supprimerEnTete\n");
	assert(liste->tete->info == 9);
	status = supprimerEnTete(liste, valeurElement);
	assert(status == OK);
	assert(longueur(liste) == 4);
	assert(valeurElement != NULL && *valeurElement == 9);
	assert(liste->tete->info == 6);

	// Tests supprimerEnQueue
	printf("\nTests supprimerEnQueue\n");
	assert(liste->queue->info == 3);
	status = supprimerEnQueue(liste, valeurElement);
	assert(status == OK);
	assert(longueur(liste) == 3);
	assert(valeurElement != NULL && *valeurElement == 3);
	assert(liste->queue->info == 7);

	//Tests que la suppression en tête ou en queue
	//retourne l'exception LISTE_VIDE sur une liste vide
	Liste* liste2 = initialiser();
	if (!liste2) {
		printf("Erreur d'initialisation de liste2");
		return EXIT_FAILURE;
	}
	//TODO: transform to macro ? ^^
	status = supprimerEnQueue(liste2, valeurElement);
	assert(status == LISTE_VIDE);
	status = supprimerEnTete(liste2, valeurElement);
	assert(status == LISTE_VIDE);

	//Tests supprimerSelonCritere
	Liste* liste3 = initialiser();
	for (Info i = 0; i < 20; i++) { insererEnTete(liste3, &i); }
	// TODO

	
	printf("\nTous les tests passent !\n\n");
}
