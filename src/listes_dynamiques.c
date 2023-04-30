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

bool estVide(const Liste* liste) {
	return liste->tete == NULL && liste->queue == NULL;
}

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
									bool (*critere)(size_t position, const Info* info)) {
	//Ne rien faire si la liste est déjà vide
	if (!liste->tete) return;

	Element* courant = liste->tete;
	size_t index = 0;

	while (courant) {
		//Si l'élément passe le critère, il doit être supprimé
		if (critere(index, &courant->info)) {
			//Lier le maillon précédent s'il existe, du maillon courant, vers le maillon suivant
			if (courant->precedent) courant->precedent->suivant = courant->suivant;
			else
				//Sinon il faudra définir la tête comme le prochain élément
				liste->tete = courant->suivant;

			//Lier le maillon suivant s'il existe, du maillon courant, vers le maillon précédent
			if (courant->suivant) courant->suivant->precedent = courant->precedent;
			else
				//Sinon il faudra définir la queue comme l'élément précédent
				liste->queue = courant->precedent;

			Element* prochain = courant->suivant;
			free(courant);
			courant = prochain;
		} else {
			courant = courant->suivant;
			//Sinon on passe juste à l'élément suivant
		}
		index++;
	}
}

void vider(Liste* liste, size_t position) {
	//Ne rien faire si la liste est déjà vide
	if (!liste->tete) return;

	//Parcours la liste et supprime les valeurs une fois avoir atteint
	// ou dépassé la position donnée
	size_t index = 0;
	Element* courant = liste->tete;
	while (courant) {
		if (index < position) {
			courant = courant->suivant;
			index++;
			continue;
		} else if (index == position) {
			liste->queue = courant->precedent;

			//De plus si position=0, il faut changer la tête:
			if (position == 0) {
				liste->tete = NULL;
				//La queue de la liste sera NULL à ce moment,
				// pas besoin de a remettre à NULL
			} else {
				//S'il y a des éléments avant, définir le dernier maillon comme NULL
				courant->precedent->suivant = NULL;
			}
		}
		Element* prochain = courant->suivant;
		free(courant);
		if (prochain) prochain->precedent = NULL;//TODO: est-ce utile ?
		courant = prochain;
		index++;
	}
}

bool sontEgales(const Liste* liste1, const Liste* liste2) {
	Element *courant1 = liste1->tete, *courant2 = liste2->tete;

	while (courant1 || courant2) {
		//Si l'un des pointeurs est vide, une des listes est plus courte que l'autre
		// elles ne sont donc pas égales !
		if ((!courant1 && courant2) || (courant1 && !courant2)) { return false; }

		//Compare les 2 valeurs sur le maillon courant des 2 listes
		if (courant1->info != courant2->info) {
			return false;
			break;
		}
		courant1 = courant1->suivant;
		courant2 = courant2->suivant;
	}
	//Si on arrive ici, toutes les valeurs sont bien identiques
	// et les 2 listes ont la même longueur
	return true;
}
