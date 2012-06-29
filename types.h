typedef enum { FALSE, TRUE } boolean;

typedef struct {
	char *name;
	int addr;
	boolean is_data; 
} label;

typedef char word[2];

typedef enum { IMMEDIATE, DIRECT, RELATIVE, REGISTER } addressing;

typedef struct {
	addressing at;
	word value;
} argument;

struct {
	char* name;
	int code;
} commands[] = {
	{"mov", 0 },
	{"cmp", 1 },
	{"add", 2 },
	{"sub", 3 },
	{"ror", 4 },
	{"shr", 5 },
	{"lea", 6 },
	{"inc", 7 },
	{"dec", 10 },
	{"jmp", 11 },
	{"bne", 12 },
	{"red", 13 },
	{"prn", 14 },
	{"jsr", 15 },
	{"rts", 16 },
	{"hlt", 17 } 
};
