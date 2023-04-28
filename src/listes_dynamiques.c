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

bool estVide(const Liste *liste) {
    return longueur(liste) == 0;
}

size_t longueur(const Liste *liste) {
    Element *courant = liste->tete;

    if (!courant) return 0;

    size_t longueur = 1;

    while (!courant->suivant) {
        courant = courant->suivant;
        longueur++;
    }
    return longueur;
}

void afficher(const Liste *liste, Mode mode) {

    if (estVide(liste)) {
        printf("[]");
        return;
    }

    if (mode == FORWARD) {
        Element *courant = liste->tete;
        printf("[");
        while (!courant) {
            printf("%d", courant->info);
            courant = courant->suivant;
        }
        printf("]");

    } else {
        Element *courant = liste->queue;
        printf("[");
        while (!courant) {
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

Status insererEnQueue(Liste *liste, const Info *info) {
    //vérifier si la tableau est vide ou non
    //vérifier si la capacité permet un élément de plus
    //return mémoire insuffisante
    //pointer sur le dernier élément
    //insérer l'élément suivant.
    //return OK
    Element *courant = (Element *) calloc(1, sizeof(Element));

    if (!courant) return MEMOIRE_INSUFFISANTE;

    if (longueur(liste) == 0) {
        liste->tete = courant;
    }

    liste->queue = courant;
    courant->info = *info;
    courant = courant->precedent;
    courant->suivant = liste->queue;

    return OK;
}


