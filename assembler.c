#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include "types.h"
#include "utils.h"

#define MOV_CODE 0
#define CMP_CODE 1
#define ADD_CODE 2
#define SUB_CODE 3
#define ROR_CODE 4
#define SHR_CODE 5
#define LEA_CODE 6
#define INC_CODE 7
#define DEC_CODE 10
#define JMP_CODE 11
#define BNE_CODE 12
#define RED_CODE 13
#define PRN_CODE 14
#define JSR_CODE 15
#define RTS_CODE 16
#define HLT_CODE 17

#define MAX_MEMORY_WORDS 2000
#define LINE_MAX_CHARS 80

command commands[MAX_MEMORY_WORDS];
word data[MAX_MEMORY_WORDS];
label labels[MAX_MEMORY_WORDS];

int commands_counter = 0;
int data_counter = 0;
int command_address = 0;
int line_counter = 0;
int label_counter = 0;
char *file_name;

void mov(void);
void cmp(void);
void add(void);
void sub(void);
void ror(void);
void shr(void);
void lea(void);
void inc(void);
void dec(void);
void jmp(void);
void bne(void);
void red(void);
void prn(void);
void jsr(void);
void rts(void);
void hlt(void);


/* Translation table for commands in the code. */
typedef struct {
	char* name;
	void (*func)(void);
} func_translate;
func_translate commands_table[] = {
	{ "mov", mov },
	{ "cmp", cmp },
	{ "add", add },
	{ "sub", sub },
	{ "ror", ror },
	{ "shr", shr },
	{ "lea", lea },
	{ "inc", inc },
	{ "dec", dec },
	{ "jmp", jmp },
	{ "bne", bne },
	{ "red", red },
	{ "prn", prn },
{ "jsr", jsr },
	{ "rts", rts },
	{ "hlt", hlt } ,
	{ "", NULL }
};

void parse_data(void);
void parse_string(void);
void parse_extern(void);
void parse_entry(void);

func_translate directives_table[] = {
	{ ".data", parse_data },
	{ ".string", parse_string },
	{ ".extern", parse_extern },
{ ".entry", parse_entry },
{ "", NULL }
};

void print_err(const char *format, ...) {
    va_list args;

    va_start(args, format);
    fprintf(stderr, "File: %s, Line: %d, ", file_name, line_counter);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

boolean parse_label(char *label) {
int len = strlen(label);
int i = 1;

if (len)
{
print_err("Label cannot have empty name");
	return FALSE;
}
if (strlen(label) > 30)
{
print_err("Label name is too long.");
	return FALSE;
}
/* first letter must be a letter */
if (!isalpha(label[0])) {
	print_err("Label must start with a letter.");
	return FALSE;
}
/* make sure only alphanumeric chars */
for (i = 1; label[i] != 0; i++)
{
if (!isalnum(label[i]))
{
	print_err("Label name must be alphanumeric.");
		return FALSE;
}
}
/* label name is ok, add it to labels table*/
strcpy(labels[label_counter++].name, label);
return TRUE;
}

/* this method parse and calls the right function from
   the functions tables defines (directives and commands)
   according to the string in the input */
boolean call_parse_func(func_translate funcs_table[], char *ftype, char *line) {
	int i;
	char *func;

	func = strtok(line, " \t");

	for (i = 0; funcs_table[i].func != NULL; i++) {
		if (strcmp(func, funcs_table[i].name) == 0) {
(*(funcs_table[i].func))();
		}
	}

	if (funcs_table[i].func == NULL) {
		print_err("Unknown %s: %s.", ftype, func);
		return FALSE;
	}

	return TRUE;
}

boolean parse(FILE *file, char* name) {
char line_buf[LINE_MAX_CHARS];
char *line = line_buf;
char *part;
boolean success = TRUE;
file_name = name;

	while (!feof(file)) {
	fgets(line, LINE_MAX_CHARS, file);
line_counter++;
/* check for label */
part = strchr(line, ':');
if (part != NULL) {
	if (part == line) {
		*part = 0;
	} else {
	part = strtok(line, ":");
	}

success = parse_label(part);
line = strtok(NULL, "");
}

	if (success) {
	line = trim(line);
if (*line == '.') {
		success = call_parse_func(directives_table, "directive", line);
	} else {
		success = call_parse_func(commands_table, "command", line);
	}
	}
}

return success;
}

void mov(void){ }
void cmp(void){ }
void add(void){ }
void sub(void){ }
void ror(void){ }
void shr(void){ }
void lea(void){ }
void inc(void){ }
void dec(void){ }
void jmp(void){ }
void bne(void){ }
void red(void){ }
void prn(void){ }
void jsr(void){ }
void rts(void){ }
void hlt(void){ }

void parse_data(void){ }
void parse_string(void){ }
void parse_extern(void){ }
void parse_entry(void){ }