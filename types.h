typedef boolean int;
#define TRUE 1
#define FALSE 0

struct {
	char *name;
	int addr;
	boolean is_data; 
} Label;

typedef word char[2];