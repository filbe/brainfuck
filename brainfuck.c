/*
 * Brainfuck interpreter in C
 *
 * Authors:
 *  Ville-Pekka Lahti <vp@wdr.fi>
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PGMEMSIZE 30000

int main(int argc, char *argv[])
{
	uint8_t *mem = malloc(PGMEMSIZE); // brainfuck program memory
	uint8_t *vol = malloc(PGMEMSIZE); // brainfuck code memory
	uint8_t *in = malloc(PGMEMSIZE); // input buffer

	// initializing memory
	memset(mem, 0, PGMEMSIZE);
	memset(vol, 0, PGMEMSIZE);
	memset(in, 0, PGMEMSIZE);

	// put bf code from commandline argument
	if (argc > 1) {
		strcpy(vol, argv[1]);
	}

	// put input from commandline argument
	if (argc > 2) {
		strcpy(in, argv[2]);
	}

	while (*vol) {
		switch (*vol) {
		case '+':
			// increment of memory at current place
			(*mem)++;
			break;
		case '-':
			// decrement of memory at current place
			(*mem)--;
			break;
		case '>':
			// move the pointer one step right
			mem++;
			break;
		case '<':
			// move the pointer one step left
			mem--;
			break;
		case '.':
			// print a char at current memptr place
			putchar(*mem);
			break;
		case ',':
			// put a char from input buffer to mem. could've been done with getchar()
			*mem = *in;
			in++;
			break;
		case '[':

			if (*mem == 0) {
				// skip a block [ ] if current place of memory is zero
				int pairs = 1;
				while (pairs > 0) {
					vol++;
					switch (*vol) {
					case '[':
						pairs++;
						break;
					case ']':
						pairs--;
						break;
					}
				}
			}
			break;
		case ']':
			// jump to the beginning of a block [ ] if current place of memory is nonzero
			if (*mem != 0) {
				int pairs = 1;
				while (pairs > 0) {
					vol--;
					switch (*vol) {
					case ']':
						pairs++;
						break;
					case '[':
						pairs--;
						break;
					}
				}
			}
			break;
		}
		vol++;
	}
	return 0;
}
