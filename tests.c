#include "include/listes_dynamiques.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define afficherForward(liste)                                                      \
	do {                                                                             \
		printf("Affichage FORWARD de '%s': ", #liste);                                \
		afficher(liste, FORWARD);                                                     \
	} while (0)

#define checkPointeur(liste)                                                        \
	do {                                                                             \
		if ((liste) == NULL) {                                                        \
			printf("Erreur d'initialisation sur le pointeur %s...\n\n", #liste);       \
			return EXIT_FAILURE;                                                       \
		}                                                                             \
	} while (0)

// Critère pour supprimerSelonCritere pour retirer les valeurs paires
//et celles en position < 4
bool retirerNbsPairsEtPosInferieurA4(size_t position, const Info* info) {
	return position < 4 || *info % 2 == 0;
}

int main(void) {
	//Chiffres à passer par adresse dans les insertions
	const Info chiffres[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	Info valeurElement = 0;//valeur de l'élément retiré par suppression

	// Tests initialisation
	printf("Tests initialisation\n");
	Liste* liste = initialiser();
	checkPointeur(liste);
	afficherForward(liste);
	printf("Longueur: %ld\n", longueur(liste));
	assert(longueur(liste) == 0);
	printf("estVide: %s\n", estVide(liste) ? "true" : "false");
	assert(estVide(liste));

	// Tests insererEnTete
	printf("\nTests insererEnTete()\n");
	afficherForward(liste);
	printf("insererEnTete 4\n");
	assert(insererEnTete(liste, &chiffres[4]) == OK);
	afficherForward(liste);
	assert(liste->tete->info == 4);
	assert(liste->queue->info == 4);
	printf("insererEnTete 6\n");
	insererEnTete(liste, &chiffres[6]);
	afficherForward(liste);
	assert(liste->tete->info == 6);
	assert(liste->queue->info == 4);
	printf("insererEnTete 9\n");
	insererEnTete(liste, &chiffres[9]);
	assert(liste->tete->info == 9);
	assert(longueur(liste) == 3);

	// Tests affichage FORWARD et BACKWARD
	afficherForward(liste);
	printf("\nAffichage BACKWARD de 'liste': ");
	afficher(liste, BACKWARD);

	// Tests insererEnQueue
	printf("\nTests insererEnQueue()\n");
	afficherForward(liste);
	printf("insererEnQueue 7\n");
	assert(liste->queue->info == 4);
	assert(insererEnQueue(liste, &chiffres[7]) == OK);
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
	afficherForward(liste);
	printf("Suppression...\n");
	assert(liste->tete->info == 9);
	assert(supprimerEnTete(liste, &valeurElement) == OK);
	afficherForward(liste);
	assert(longueur(liste) == 4);
	assert(valeurElement == 9);
	assert(liste->tete->info == 6);

	// Tests supprimerEnQueue
	printf("\nTests supprimerEnQueue()\n");
	assert(liste->queue->info == 3);
	afficherForward(liste);
	printf("Suppression...\n");
	assert(supprimerEnQueue(liste, &valeurElement) == OK);
	afficherForward(liste);
	assert(longueur(liste) == 3);
	assert(valeurElement == 3);
	assert(liste->queue->info == 7);

	//Tests que la suppression en tête ou en queue
	//retourne l'exception LISTE_VIDE sur une liste vide
	printf("\nTests supprimerEnTete() et supprimerEnQueue() sur liste vide\n");
	Liste* liste2 = initialiser();
	checkPointeur(liste2);
	assert(supprimerEnTete(liste2, &valeurElement) == LISTE_VIDE);
	assert(supprimerEnQueue(liste2, &valeurElement) == LISTE_VIDE);
	afficherForward(liste2);


	printf("\nTests sontEgales() et vider()\n");
	//Créer et initialiser deux listes avec les nombres 0 à 19
	Liste* liste3 = initialiser();
	Liste* liste4 = initialiser();
	assert(sontEgales(liste3, liste4));//2 listes vides sont égales
	for (Info i = 0; i < 20; i++) {
		insererEnQueue(liste3, &i);
		insererEnQueue(liste4, &i);
	}
	afficherForward(liste3);
	afficherForward(liste4);
	assert(sontEgales(liste3, liste4));
	vider(liste4, 22);//vider au dela de la taille
	printf("Vidage au dela de la taille...\n");
	afficherForward(liste4);
	//liste4 n'a pas changé -> toujours égal à liste3 :
	assert(sontEgales(liste3, liste4));

	printf("Vidage depuis la position 15...\n");
	vider(liste4, 15);//vider la fin de la liste4
	afficherForward(liste4);
	assert(liste4->queue->info == 14);
	assert(sontEgales(liste3, liste4) == false);
	printf("Vidage depuis la position 0 (tout)...\n");
	vider(liste4, 0);//vider tout
	assert(estVide(liste4));
	afficherForward(liste4);

	//Tests supprimerSelonCritere
	printf("\nTests supprimerSelonCritere()\n");
	printf("Appliquer critere1() pour retirer les valeurs paires "
			 "et celles en position < 4\n");
	afficherForward(liste3);
	printf("Suppression à l'aide du critère...\n");
	supprimerSelonCritere(liste3, &retirerNbsPairsEtPosInferieurA4);
	afficherForward(liste3);
	assert(liste3->tete->info == 5);
	assert(liste3->tete->suivant->info == 7);
	assert(liste3->tete->suivant->suivant->info == 9);
	assert(liste3->queue->info == 19);
	assert(longueur(liste3) == 8);

	//Tests plus avancés sur supprimerSelonCritere
	printf("\nTests supprimerSelonCritere() qui vide complètement la pile\n");
	Liste* liste5 = initialiser();
	insererEnQueue(liste5, &chiffres[3]);
	supprimerSelonCritere(
		liste5,
		&retirerNbsPairsEtPosInferieurA4);//un seul élément à supprimer
	assert(estVide(liste5));
	Liste* liste6 = initialiser();
	insererEnQueue(liste6, &chiffres[3]);
	insererEnQueue(liste6, &chiffres[5]);
	supprimerSelonCritere(liste6,
								 &retirerNbsPairsEtPosInferieurA4);//2 éléments à supprimer
	assert(estVide(liste6));

	//Libère la mémoire pour toutes les listes
	free(liste);
	free(liste2);
	free(liste3);
	free(liste4);
	free(liste5);
	free(liste6);
	printf("\nTous les tests passent !\n\n");
	return EXIT_SUCCESS;
}
