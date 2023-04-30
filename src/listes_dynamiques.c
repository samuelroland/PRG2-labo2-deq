#include "../include/listes_dynamiques.h"
#include <stdio.h>
#include <stdlib.h>

Liste* initialiser(void) {
	Liste* ptr = (Liste*) calloc(1, sizeof(Liste));
	if (!ptr) return NULL;
	ptr->tete = NULL;
	ptr->queue = NULL;
	return ptr;
}

bool estVide(const Liste* liste) { return longueur(liste) == 0; }

size_t longueur(const Liste* liste) {
	Element* courant = liste->tete;
	size_t longueur = 0;
	while (courant) {
		longueur++;
		courant = courant->suivant;
	}
	return longueur;
}

void afficher(const Liste* liste, Mode mode) {
	printf("[");
	//Prendre le premier ou dernier élément
	Element* courant = (mode == FORWARD) ? liste->tete : liste->queue;
	//Parcours tous les éléments dans un sens donné par mode,
	// et s'arrête quand il n'y a plus d'élément
	while (courant) {
		printf("%d", courant->info);
		courant = (mode == FORWARD) ? courant->suivant : courant->precedent;
		if (courant) printf(",");//affiche une virgule sauf pour le dernier élément
	}
	printf("]\n");
}

Status insererEnTete(Liste* liste, const Info* info) {
	Element* courant = (Element*) calloc(1, sizeof(Element));

	if (!courant) return MEMOIRE_INSUFFISANTE;

	//Si la liste n'a pas de queue, la liste est vide
	// l'élément qu'on vient d'insérer est également la fin de la liste
	if (liste->queue == NULL) liste->queue = courant;

	courant->info = *info;
	//Si la liste a déjà une tête, donc qu'il y a au moins un élément existant
	// il faut lier les 2 premiers maillons (l'existant et le nouveau)
	if (liste->tete) {
		courant->suivant = liste->tete;
		courant->suivant->precedent = courant;
	}
	liste->tete = courant;

	return OK;
}

Status insererEnQueue(Liste* liste, const Info* info) {
	//vérifier si la tableau est vide ou non
	//vérifier si la capacité permet un élément de plus
	//return mémoire insuffisante
	//pointer sur le dernier élément
	//insérer l'élément suivant.
	//return OK
	Element* courant = (Element*) calloc(1, sizeof(Element));

	if (!courant) return MEMOIRE_INSUFFISANTE;

	if (liste->tete == NULL) { liste->tete = courant; }

	courant->info = *info;
	//Si la liste a déjà une queue, donc qu'il y a au moins un élément existant
	// il faut lier les 2 derniers maillons (l'existant et le nouveau)
	if (liste->queue) {
		courant->precedent = liste->queue;
		courant->precedent->suivant = courant;
	}
	liste->queue = courant;

	return OK;
}

Status supprimerEnTete(Liste* liste, Info* info) {
	if (!liste->tete) return LISTE_VIDE;

	Element* element = liste->tete;
	*info = element->info;
	liste->tete = element->suivant;
	liste->tete->precedent = NULL;
	free(element);
	return OK;
}

Status supprimerEnQueue(Liste* liste, Info* info) {
	if (!liste->queue) return LISTE_VIDE;

	Element* element = liste->queue;
	*info = element->info;
	liste->queue = element->precedent;
	liste->queue->suivant = NULL;
	free(element);
	return OK;
}

void supprimerSelonCritere(Liste* liste,
									bool (*critere)(size_t position, const Info* info)) {}
void vider(Liste* liste, size_t position) {}
bool sontEgales(const Liste* liste1, const Liste* liste2) {}
