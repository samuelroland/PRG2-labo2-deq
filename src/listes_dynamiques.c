#include "../include/listes_dynamiques.h"
#include <stdio.h>
#include <stdlib.h>

Liste *initialiser(void) {
	Liste *ptr = (Liste *) calloc(1, sizeof(Liste));
	if (!ptr) return NULL;
	ptr->tete = NULL;
	ptr->queue = NULL;
	return ptr;
}

void afficher(const Liste *liste, Mode mode) {

	if (estVide(liste)) {
		printf("[]");
		return;
	}

	if (mode == FORWARD) {
		Element *courant = liste->tete;
		printf("[");
		for (size_t i = 0; i < longueur(liste); ++i) {
			printf("%d", courant->info);
			courant = courant->suivant;
		}
		printf("]");

	} else {
		Element *courant = liste->queue;
		printf("[");
		for (size_t i = longueur(liste); i > 0; --i) {
			printf("%d", courant->info);
			courant = courant->precedent;
		}
		printf("]");
	}
}

Status insererEnTete(Liste *liste, const Info *info) {

	Element *ptr = (Element *) calloc(1, sizeof(Element));

	if (!ptr) return MEMOIRE_INSUFFISANTE;

	if (longueur(liste) == 1) liste->queue = ptr;

	ptr->info = *info;
	ptr->suivant = liste->tete;
	ptr->precedent = NULL;
	liste->tete = ptr;

	return OK;
}
