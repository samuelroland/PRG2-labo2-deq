/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.c
 Auteur(s)      : Samuel Roland, Nathan Rayburn, Leonard Klasen
 Date creation  : 27.04.2023

 Description    : Implémentation de la liste doublement chaînée

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 12.2.1
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Initialise la liste
 * @return le pointeur sur la liste ou NULL en cas de mémoire insuffisante
 */
Liste* initialiser(void) {
	Liste* ptr = (Liste*) calloc(1, sizeof(Liste));
	if (!ptr) return NULL;
	ptr->tete = NULL;
	ptr->queue = NULL;
	return ptr;
}

/**
 * Retourne vrai si la liste est vide, faux sinon
 * @param liste
 * @return vrai si la liste est vide, faux sinon
 */
bool estVide(const Liste* liste) {
	return liste->tete == NULL && liste->queue == NULL;
}

/**
 * Parcours la liste pour calculer sa longueur
 * @param liste
 * @return la longueur de la liste
 */
size_t longueur(const Liste* liste) {
	Element* courant = liste->tete;
	size_t longueur = 0;
	while (courant) {
		longueur++;
		courant = courant->suivant;
	}
	return longueur;
}

/**
 * Permet d'afficher le contenu de la liste
 * @param liste
 * @param Un mode FORWARD ou BACKWARD pour lire en avant ou en arrière
 */
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

/**
 * Insère un nouvel élément au début de la liste
 * @param liste
 * @param info: pointeur sur la valeur à insérer dans la liste
 * @return OK si l'insertion s'est déroulée avec succès, sinon MEMOIRE_INSUFFISANTE
 */
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

/**
 * Insère un nouvel élément à la fin de la liste
 * @param liste
 * @param info: pointeur sur la valeur à insérer dans la liste
 * @return OK si l'insertion s'est déroulée avec succès, sinon MEMOIRE_INSUFFISANTE
 */
Status insererEnQueue(Liste* liste, const Info* info) {
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

/**
 * Supprime l'élément en tête de liste
 * @param liste
 * @param info: renvoie l'info stockée dans l'élément en tête de liste
 * @return LISTE_VIDE si la liste passée en paramètre est vide, sinon OK
 */
Status supprimerEnTete(Liste* liste, Info* info) {
	if (!liste->tete) return LISTE_VIDE;

	//Change la tête de la liste au second élément (peut être NULL)
	Element* element = liste->tete;
	*info = element->info;

	//Rédéfinit le 2ème maillon comme le premier
	liste->tete = element->suivant;
	if (liste->tete) liste->tete->precedent = NULL;

	// La liste pourrait être vide s'il n'y avait qu'un élément
	if (!liste->tete) liste->queue = NULL;

	free(element);
	return OK;
}

/**
 * Supprime l'élément en fin de liste
 * @param liste
 * @param info: renvoie l'info stockée dans l'élément en fin de liste
 * @return LISTE_VIDE si la liste passée en paramètre est vide, sinon OK
 */
Status supprimerEnQueue(Liste* liste, Info* info) {
	if (!liste->queue) return LISTE_VIDE;

	Element* element = liste->queue;
	*info = element->info;

	//Rédéfinit l'avant dernier maillon comme le dernier
	liste->queue = element->precedent;
	if (liste->queue) liste->queue->suivant = NULL;

	// La liste pourrait être vide s'il n'y avait qu'un élément
	if (!liste->queue) liste->tete = NULL;

	free(element);
	return OK;
}

/**
 * Supprime tous les éléments de la liste qui vérifient le critère passé en paramètre
 * tout en restituant la mémoire allouée.
 * @param liste
 * @param critere: pointeur sur une fonction prenant la position et la valeur en paramètre 
 * et retournant vrai si le critère passe sur cet élément
 */
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

/**
 * Supprime tous les éléments de la liste à partir de la position 'position'
 * tout en restituant la mémoire allouée.
 * @param liste
 * @param position - position à partir duquel on supprime
 */
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
				// pas besoin de la remettre à NULL
			} else {
				//S'il y a des éléments avant, définir le dernier maillon comme NULL
				courant->precedent->suivant = NULL;
			}
		}
		Element* prochain = courant->suivant;
		free(courant);

		//On définit par précaution la valeur 'precedent' du prochain maillon s'il existe,
		// même si ce prochain maillon sera supprimé au tour suivant.
		if (prochain) prochain->precedent = NULL;

		courant = prochain;
		index++;
	}
}

/**
 * Retourne vrai si les 2 listes passées en paramètre sont égales
 * donc avec les mêmes infos et le même ordre, faux sinon
 * @param liste1
 * @param liste2
 * @return Retourne vrai si les 2 listes sont égales, sinon faux.
 */
bool sontEgales(const Liste* liste1, const Liste* liste2) {
	Element *courant1 = liste1->tete, *courant2 = liste2->tete;

	while (courant1 && courant2) {
		//Compare les 2 valeurs sur le maillon courant des 2 listes
		if (courant1->info != courant2->info) { return false; }
		courant1 = courant1->suivant;
		courant2 = courant2->suivant;
	}
	//Si les 2 pointeurs sont vides une fois sorti du while, alors c'est égal
	//Sinon cela signifie qu'une liste a les mêmes éléments, mais qu'elle est plus courte
	return !courant1 && !courant2;
}
