#include "../include/listes_dynamiques.h"
#include <stdlib.h>

Liste *initialiser(void) {
	Liste *ptr = (Liste *) calloc(1, sizeof(Liste));
	(*ptr).tete = NULL;
	(*ptr).queue = NULL;
	return ptr;
}
