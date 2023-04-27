#include "../include/listes_dynamiques.h"
#include <stdlib.h>

Liste *initialiser(void) {
    Liste *ptr = (Liste *) calloc(1, sizeof(Liste));
    (*ptr).tete = NULL;
    (*ptr).queue = NULL;
    return ptr;
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
