
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char mem[50000];
	char vol[50000];
	char in[50000];
	uint16_t memcur = 0;
	uint16_t volcur = 0;
	uint16_t incur = 0;

	for (int i=0;i<50000;i++) {
		mem[i] = 0;
		vol[i] = 0;
		in[i] = EOF;
	}

	if (argc > 1) {
		strcpy(vol, argv[1]);
	}
	if (argc > 2) {
		strcpy(in, argv[2]);
	}

	while(vol[volcur]) {
		switch(vol[volcur]) {
			case '+':
			mem[memcur]++;
			break;
			case '-':
			mem[memcur]--;
			break;
			case '>':
			memcur++;
			break;
			case '<':
			memcur--;
			break;
			case '.':
			printf("%c", mem[memcur]);
			break;
			case ',':
				mem[memcur] = in[incur++];
			break;
			case '[':
			if (mem[memcur] == 0) {
				int pairs = 1;
				while (pairs > 0) {
					volcur++;
					switch(vol[volcur]) {
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
			if (mem[memcur] != 0) {
				int pairs = 1;
				while (pairs > 0) {
					volcur--;
					switch(vol[volcur]) {
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
		volcur++;
	}
	return 0;
}
