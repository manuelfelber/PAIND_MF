/*
 * Hash.c
 *
 *  Created on: 27.10.2016
 *      Author: Manuel Felber
 */

#include "Hash.h"

//djb2 algorithmus http://www.cse.yorku.ca/~oz/hash.html
unsigned long getHash(uint8_t *str){
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}
