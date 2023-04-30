#include "include/listes_dynamiques.h"
#include <stdio.h>
// tests ici

int main() {
	Liste* liste = initialiser();
	afficher(liste, FORWARD);
	afficher(liste, BACKWARD);
	insererEnTete(liste, (const Info*) 4);
	size_t taille = longueur(liste);
	printf("%d", (unsigned) taille);
}
