/*
 * Brainfuck interpreter in Node.js
 *
 * Authors:
 *  Ville-Pekka Lahti <vp@wdr.fi>
 */

var codemem = []; // brainfuck code goes here
var progmem = []; // bf program memory
var inmem =   []; // bf input buffer

// initializing memory cursors
var codecursor = 0;
var memcursor = 0;
var incursor = 0;

// initializing memory
for (var i = 0; i < 30000; i++) {
	codemem[i] = 0;
	progmem[i] = 0;
	inmem[i] = 0;
}

// put bf code from commandline argument
if (typeof process.argv[2] !== "undefined") {
	for (var i = 0; i < process.argv[2].length; i++) {
		codemem[i] = process.argv[2].charAt(i);
	}
}

// put input from commandline argument
if (typeof process.argv[3] !== "undefined") {
	for (var i = 0; i < process.argv[3].length; i++) {
		inmem[i] = process.argv[3].charAt(i);
	}
}

console.log("BRAINFUCK INTERPRETER BY VP");
console.log("---------------------------");

// loop 'till the end of code
while (codemem[codecursor]) {
	var brackets = 0;
	switch (codemem[codecursor]) {
		case '+':
			// increment of memory at current place
			progmem[memcursor]++;
			break;
		case '-':
			// decrement of memory at current place
			progmem[memcursor]--;
			break;
		case '>':
			// move the memory cursor one step right
			memcursor++;
			break;
		case '<':
			// move the memory cursor one step left
			memcursor--;
			break;
		case '.':
			// print a character from memory at current place
			process.stdout.write(String.fromCharCode(progmem[memcursor]));
			break;
		case ',':
			// put the next character available from input buffer to memory at current place
			// Because of JavaScript's autocast, let's convert inputs properly
			switch (typeof inmem[incursor]) {
				case "string":
					progmem[memcursor] = inmem[incursor++].charCodeAt(0);
					break;
				case "number":
					progmem[memcursor] = inmem[incursor++];
					break;
			}
			break;
		case '[':
			// skip a block [ ] if current place of memory is zero
			if (!progmem[memcursor]) {
				brackets = 1;
				while (brackets > 0 && codemem[codecursor] != '0') {
					codecursor++;
					switch (codemem[codecursor]) {
						case '[':
							brackets++;
							break;
						case ']':
							brackets--;
							break;
					}
				}
			}
			break;
		case ']':
			// jump to the beginning of a block [ ] if current place of memory is nonzero
			if (progmem[memcursor]) {
				brackets = 1;
				while (brackets > 0 && codemem[codecursor] != '0') {
					codecursor--;
					switch (codemem[codecursor]) {
						case ']':
							brackets++;
							break;
						case '[':
							brackets--;
							break;
					}
				}
			}
			break;
	}
	codecursor++;
}
console.log("---------------------------");
console.log("--------TERMINATED!--------");