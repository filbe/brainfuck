var codemem = [];
var progmem = [];
var inmem =   [];
for (var i = 0; i < 30000; i++) {
	codemem[i] = 0;
	progmem[i] = 0;
	inmem[i] = 0;
}
if (typeof process.argv[2] !== "undefined") {
	for (var i = 0; i < process.argv[2].length; i++) {
		codemem[i] = process.argv[2].charAt(i);
	}
}
if (typeof process.argv[3] !== "undefined") {
	for (var i = 0; i < process.argv[3].length; i++) {
		inmem[i] = process.argv[3].charAt(i);
	}
}
var codecursor = 0;
var memcursor = 0;
var incursor = 0;
console.log("BRAINFUCK INTERPRETER BY VP");
console.log("---------------------------");
var codestr = "";
while (codemem[codecursor] != '0') {
	var brackets = 0;
	switch (codemem[codecursor]) {
		case '+':
			progmem[memcursor]++;
			break;
		case '-':
			progmem[memcursor]--;
			break;
		case '>':
			memcursor++;
			break;
		case '<':
			memcursor--;
			break;
		case '.':
			process.stdout.write(String.fromCharCode(progmem[memcursor]));
			break;
		case ',':
			switch (typeof inmem[incursor]) {
				case "string":
					progmem[memcursor] = inmem[incursor].charCodeAt(0);
					break;
				case "number":
					progmem[memcursor] = inmem[incursor];
					break;
			}
			incursor++;
			break;
		case '[':
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