/*
 -----------------------------------------------------------------------------------
 Nom du fichier : tests.c
 Auteur(s)      : Samuel Roland, Nathan Rayburn, Leonard Klasen
 Date creation  : 27.04.2023

 Description    : Suite de tests sur l'implémentation de la liste doublement
                  chaînée

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 12.2.1
 -----------------------------------------------------------------------------------
*/

#include "include/listes_dynamiques.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//Listes de chiffres à utiliser par adresse pour les insertions
const Info chiffres[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// Afficher la liste en mode FORWARD
#define afficherForward(liste)                                                      \
	do {                                                                             \
		printf("Affichage FORWARD de '%s': ", #liste);                                \
		afficher(liste, FORWARD);                                                     \
	} while (0)

// Arrête le programme si le pointeur est NULL
#define checkPointeur(liste)                                                        \
	do {                                                                             \
		if ((liste) == NULL) {                                                        \
			printf("Erreur d'initialisation sur le pointeur %s...\n\n", #liste);       \
			return EXIT_FAILURE;                                                       \
		}                                                                             \
	} while (0)

// Remplit une liste avec des données de tests
#define remplirListe(liste)                                                         \
	do {                                                                             \
		insererEnQueue(liste, &chiffres[1]);                                          \
		insererEnQueue(liste, &chiffres[3]);                                          \
		insererEnQueue(liste, &chiffres[4]);                                          \
		insererEnQueue(liste, &chiffres[8]);                                          \
	} while (0)

/**
 * Permet de créer et remplir une liste pour les tests
 * @return la liste remplie
 */
Liste* creerEtRemplirListe(void) {
	Liste* liste = initialiser();
	remplirListe(liste);
	return liste;
}

//Permet de vider et libérer la mémoire pour une liste à la fin de chaque test
#define viderEtLiberer(liste)                                                       \
	do {                                                                             \
		vider(liste, 0);                                                              \
		free(liste);                                                                  \
	} while (0)

// Critère pour supprimerSelonCritere pour retirer les valeurs paires
//et celles en position < 4
bool retirerNbsPairsEtPosInferieurA4(size_t position, const Info* info) {
	return position < 4 || *info % 2 == 0;
}

int main(void) {
	//Chiffres à passer par adresse dans les insertions
	Info valeurElement = 0;//valeur de l'élément retiré par suppression

	/// Tests initialisation
	{
		printf("Tests initialiser()\n");
		Liste* liste = initialiser();
		checkPointeur(liste);
		afficherForward(liste);
		printf("Longueur: %zu\n", longueur(liste));
		assert(longueur(liste) == 0);
		printf("estVide: %s\n", estVide(liste) ? "true" : "false");
		assert(estVide(liste));

		viderEtLiberer(liste);
	}

	/// Tests affichage FORWARD et BACKWARD
	{
		Liste* liste = creerEtRemplirListe();
		printf("\nAffichage BACKWARD de 'liste': ");
		afficher(liste, BACKWARD);
		afficherForward(liste);
		viderEtLiberer(liste);
	}

	/// Tests insererEnTete
	{
		Liste* liste = initialiser();
		printf("\nTests insererEnTete()\n");
		afficherForward(liste);

		printf("insererEnTete 4\n");
		assert(insererEnTete(liste, &chiffres[4]) == OK);
		afficherForward(liste);
		assert(liste->tete->info == 4);
		assert(liste->queue->info == 4);

		printf("insererEnTete 6\n");
		insererEnTete(liste, &chiffres[6]);
		assert(liste->tete->suivant != NULL);
		afficherForward(liste);
		assert(liste->tete->info == 6);
		assert(liste->queue->info == 4);

		printf("insererEnTete 9\n");
		insererEnTete(liste, &chiffres[9]);
		afficherForward(liste);
		assert(liste->tete->info == 9);
		assert(longueur(liste) == 3);
		viderEtLiberer(liste);
	}


	/// Tests insererEnQueue
	{
		Liste* liste = creerEtRemplirListe();
		printf("\nTests insererEnQueue()\n");
		afficherForward(liste);

		printf("insererEnQueue 7\n");
		assert(liste->queue->info == 8);
		assert(insererEnQueue(liste, &chiffres[7]) == OK);
		assert(liste->queue->info == 7);
		assert(liste->queue->precedent != NULL);
		afficherForward(liste);

		printf("insererEnQueue 3\n");
		insererEnQueue(liste, &chiffres[3]);
		assert(liste->queue->info == 3);
		afficherForward(liste);
		printf("Longueur: %zu\n", longueur(liste));
		assert(longueur(liste) == 6);
		printf("estVide: %s\n", estVide(liste) ? "true" : "false");
		assert(estVide(liste) == false);
		viderEtLiberer(liste);
	}

	/// Tests supprimerEnTete
	{
		Liste* liste = creerEtRemplirListe();
		printf("\nTests supprimerEnTete()\n");
		afficherForward(liste);
		printf("Suppression...\n");
		assert(liste->tete->info == 1);

		assert(supprimerEnTete(liste, &valeurElement) == OK);
		afficherForward(liste);
		assert(longueur(liste) == 3);
		assert(valeurElement == 1);
		assert(liste->tete->info == 3);
		assert(liste->tete->precedent == NULL);

		//Test sur une liste de 1 élément, la queue doit également être à zéro
		Liste* liste2 = initialiser();
		checkPointeur(liste2);
		insererEnQueue(liste2, &chiffres[4]);
		assert(supprimerEnTete(liste2, &valeurElement) == OK);
		afficherForward(liste2);
		assert(liste2->queue == NULL);
		viderEtLiberer(liste);
		viderEtLiberer(liste2);
	}

	/// Tests supprimerEnQueue
	{
		Liste* liste = creerEtRemplirListe();
		printf("\nTests supprimerEnQueue()\n");
		assert(liste->queue->info == 8);
		afficherForward(liste);
		printf("Suppression...\n");

		assert(supprimerEnQueue(liste, &valeurElement) == OK);
		afficherForward(liste);
		assert(longueur(liste) == 3);
		assert(valeurElement == 8);
		assert(liste->queue->info == 4);
		assert(liste->queue->suivant == NULL);

		//Test sur une liste de 1 élément, la tête doit également être à zéro
		Liste* liste2 = initialiser();
		insererEnQueue(liste2, &chiffres[4]);
		assert(supprimerEnQueue(liste2, &valeurElement) == OK);
		assert(liste2->tete == NULL);
		viderEtLiberer(liste);
		viderEtLiberer(liste2);
	}

	/// Tests que la suppression en tête ou en queue
	/// retourne l'exception LISTE_VIDE sur une liste vide
	{
		printf("\nTests supprimerEnTete() et supprimerEnQueue() sur liste vide\n");
		Liste* liste = initialiser();
		checkPointeur(liste);
		assert(supprimerEnTete(liste, &valeurElement) == LISTE_VIDE);
		assert(supprimerEnQueue(liste, &valeurElement) == LISTE_VIDE);
		afficherForward(liste);
		viderEtLiberer(liste);
	}

	/// Tests sontEgales et vider()
	{
		printf("\nTests sontEgales() et vider()\n");
		//Créer et initialiser deux listes avec les nombres 0 à 19
		Liste* liste1 = initialiser();
		Liste* liste2 = initialiser();
		assert(sontEgales(liste1, liste2));//2 listes vides sont égales
		for (Info i = 0; i < 20; i++) {
			insererEnQueue(liste1, &i);
			insererEnQueue(liste2, &i);
		}
		afficherForward(liste1);
		afficherForward(liste2);
		assert(sontEgales(liste1, liste2));

		printf("Vidage au-delà de la taille...\n");
		vider(liste2, 22);
		afficherForward(liste2);
		//liste4 n'a pas changé -> toujours égal à liste3 :
		assert(sontEgales(liste1, liste2));

		printf("Vidage depuis la position 15...\n");
		vider(liste2, 15);
		afficherForward(liste2);
		assert(liste2->queue->info == 14);
		assert(sontEgales(liste1, liste2) == false);

		printf("Vidage depuis la position 0 (tout)...\n");
		vider(liste2, 0);
		assert(estVide(liste2));
		afficherForward(liste2);
		viderEtLiberer(liste1);
		viderEtLiberer(liste2);
	}

	/// Tests supprimerSelonCritere
	{
		Liste* liste = initialiser();
		for (Info i = 0; i < 20; i++) { insererEnQueue(liste, &i); }
		printf("\nTests supprimerSelonCritere()\n");
		afficherForward(liste);
		printf("Suppression à l'aide du critere1() pour retirer les valeurs paires "
				 "et celles en position < 4\n");
		supprimerSelonCritere(liste, &retirerNbsPairsEtPosInferieurA4);
		afficherForward(liste);
		assert(liste->tete->info == 5);
		assert(liste->tete->suivant->info == 7);
		assert(liste->tete->suivant->suivant->info == 9);
		assert(liste->queue->info == 19);
		assert(longueur(liste) == 8);
		viderEtLiberer(liste);
	}

	/// Tests que supprimerSelonCritere même si le critère supprime tous les éléments
	{
		printf("\nTests supprimerSelonCritere() qui vide complètement la pile\n");
		Liste* liste1 = initialiser();
		insererEnQueue(liste1, &chiffres[3]);
		supprimerSelonCritere(
			liste1,
			&retirerNbsPairsEtPosInferieurA4);//un seul élément à supprimer
		assert(estVide(liste1));
		Liste* liste2 = initialiser();
		insererEnQueue(liste2, &chiffres[3]);
		insererEnQueue(liste2, &chiffres[5]);
		supprimerSelonCritere(
			liste2,
			&retirerNbsPairsEtPosInferieurA4);//2 éléments à supprimer
		assert(estVide(liste2));
		viderEtLiberer(liste1);
		viderEtLiberer(liste2);
	}

	printf("\nTous les tests passent !\n\n");
	return EXIT_SUCCESS;
}
