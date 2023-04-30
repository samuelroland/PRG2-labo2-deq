#include "include/listes_dynamiques.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define afficherForward(liste)                                                      \
	do {                                                                             \
		printf("Affichage FORWARD de '%s': ", #liste);                                \
		afficher(liste, FORWARD);                                                     \
	} while (0)

// Critère pour supprimerSelonCritere pour retirer les valeurs paires et celles en position < 4
bool critere1(size_t position, const Info* info) {
	return position < 4 || *info % 2 == 0;
}

int main(void) {
	//Chiffres à passer par adresse dans les insertions
	const Info chiffres[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	Status status;
	Info valeurElement = 0;

	// Tests initialisation
	printf("Tests initialisation\n");
	Liste* liste = initialiser();
	if (!liste) {
		printf("Erreur d'initialisation de liste");
		return EXIT_FAILURE;
	}
	afficherForward(liste);
	printf("Longueur: %ld\n", longueur(liste));
	assert(longueur(liste) == 0);
	printf("estVide: %s\n", estVide(liste) ? "true" : "false");
	assert(estVide(liste));

	// Tests insererEnTete
	printf("\ninsererEnTete 4\n");
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
	afficherForward(liste);
	printf("Affichage BACKWARD: ");
	afficher(liste, BACKWARD);

	// Tests insererEnQueue
	printf("\ninsererEnQueue 7\n");
	assert(liste->queue->info == 4);
	status = insererEnQueue(liste, &chiffres[7]);
	assert(status == OK);
	assert(liste->queue->info == 7);
	afficherForward(liste);
	printf("insererEnQueue 3\n");
	insererEnQueue(liste, &chiffres[3]);
	assert(liste->queue->info == 3);
	afficherForward(liste);
	printf("Longueur: %ld\n", longueur(liste));
	assert(longueur(liste) == 5);
	printf("estVide: %s\n", estVide(liste) ? "true" : "false");
	assert(estVide(liste) == false);

	// Tests supprimerEnTete
	printf("\nTests supprimerEnTete()\n");
	assert(liste->tete->info == 9);
	status = supprimerEnTete(liste, &valeurElement);
	assert(status == OK);
	assert(longueur(liste) == 4);
	assert(valeurElement == 9);
	assert(liste->tete->info == 6);

	// Tests supprimerEnQueue
	printf("\nTests supprimerEnQueue()\n");
	assert(liste->queue->info == 3);
	status = supprimerEnQueue(liste, &valeurElement);
	assert(status == OK);
	assert(longueur(liste) == 3);
	assert(valeurElement == 3);
	assert(liste->queue->info == 7);

	//Tests que la suppression en tête ou en queue
	//retourne l'exception LISTE_VIDE sur une liste vide
	printf("\nTests supprimerEnTete et supprimerEnQueue sur liste vide\n");
	Liste* liste2 = initialiser();
	if (!liste2) {
		printf("Erreur d'initialisation de liste2");
		return EXIT_FAILURE;
	}
	//TODO: transform to macro ? ^^
	status = supprimerEnQueue(liste2, &valeurElement);
	assert(status == LISTE_VIDE);
	status = supprimerEnTete(liste2, &valeurElement);
	assert(status == LISTE_VIDE);

	printf("\nTests sontEgales() et vider()\n");
	//Créer et initialiser deux listes avec les nombres 0 à 19
	Liste* liste3 = initialiser();
	Liste* liste4 = initialiser();
	for (Info i = 0; i < 20; i++) {
		insererEnQueue(liste3, &i);
		insererEnQueue(liste4, &i);
	}
	afficherForward(liste3);
	afficherForward(liste4);
	assert(sontEgales(liste3, liste4));
	vider(liste4, 22);//vider au dela de la taille
	afficherForward(liste4);
	//liste4 n'a pas changé -> toujours égal à liste3 :
	assert(sontEgales(liste3, liste4));
	vider(liste4, 15);//vider la fin de la liste4
	afficherForward(liste4);
	assert(liste4->queue->info == 14);
	assert(sontEgales(liste3, liste4) == false);
	vider(liste4, 0);//vider tout
	assert(estVide(liste4));
	afficherForward(liste4);

	//Tests supprimerSelonCritere
	printf("\nTests supprimerSelonCritere()\n");
	printf("Appliquer critere1() pour retirer les valeurs paires "
			 "et celles en position < 4\n");
	supprimerSelonCritere(liste3, &critere1);
	assert(liste3->tete->info == 5);
	assert(liste3->tete->suivant->info == 7);
	assert(liste3->tete->suivant->suivant->info == 9);
	assert(liste3->queue->info == 19);
	assert(longueur(liste3) == 8);
	afficherForward(liste3);

	printf("\nTests supprimerSelonCritere() qui vide complètement la pile\n");
	Liste* liste5 = initialiser();
	insererEnQueue(liste5, &chiffres[3]);
	supprimerSelonCritere(liste5, &critere1);
	assert(estVide(liste5));
	Liste* liste6 = initialiser();
	insererEnQueue(liste6, &chiffres[3]);
	insererEnQueue(liste6, &chiffres[5]);
	supprimerSelonCritere(liste6, &critere1);
	assert(estVide(liste5));


	printf("\nTous les tests passent !\n\n");
}
