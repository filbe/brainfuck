
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	uint8_t *mem = malloc(50000);
	uint8_t *vol = malloc(50000);
	memset(mem, 0, 50000);
	memset(vol, 0, 50000);

	if (argc > 1) {
		strcpy(vol, argv[1]);
	}

	while(*vol) {
		switch(*vol) {
			case '+':
			(*mem)++;
			break;
			case '-':
			(*mem)--;
			break;
			case '>':
			mem++;
			break;
			case '<':
			mem--;
			break;
			case '.':
			putchar(*mem);
			break;
			case ',':
				*mem = getchar();
			break;
			case '[':
			if (*mem == 0) {
				int pairs = 1;
				while (pairs > 0) {
					vol++;
					switch(*vol) {
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
			if (*mem != 0) {
				int pairs = 1;
				while (pairs > 0) {
					vol--;
					switch(*vol) {
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
