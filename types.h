#ifndef TYPES_H
#define TYPES_H

#define LABEL_NAME_SIZE 30

typedef enum { FALSE, TRUE } boolean;

/* enum for label types: regular, extern or entry */
typedef enum { REGULAR, EXTERN, ENTRY } label_type;
typedef char word[2];

/* Addressing type of an argument. */
typedef enum { IMMEDIATE, DIRECT, RELATIVE=3, REGISTER } addressing;

/* Argument of a command. */
typedef struct {
	/* Argument addressing type */
addressing atype;

	/* Argument value */
	word value;

	/* Save [a]bsolute, [r]elative, or [e]xternal for the linker */
	char link_directive;
} argument;

/* Struct to represent a label of a line. */
typedef struct {
	char name[LABEL_NAME_SIZE];
	int addr;
	boolean is_data;
	label_type ltype;
} label;

/* A reference to a label from a command. */
typedef struct {
	char name[LABEL_NAME_SIZE];
	int source_line;
	int addr;
	argument *arg;
} label_ref;

/* Entry definition for a label defined as entry. */
typedef struct {
	char name[LABEL_NAME_SIZE];
	int source_line;
	int addr;
} label_entry;

typedef struct {
	int code;
	argument args[2];
} command;


#endif /* TYPES-H */