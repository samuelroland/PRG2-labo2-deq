#include "include/listes_dynamiques.h"

// tests ici

int main() {
	Liste *liste = initialiser();
	afficher(liste, FORWARD);
	afficher(liste, BACKWARD);
}