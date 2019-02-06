#include <stdio.h>
#include <stddef.h>
// OPS as array of DOSTUFF structs, OP is a delegate
#define RUN_OPS(OPS, OP);\
	char counter;\
	for (counter = 0, OP = OPS[counter].run; counter < sizeof(OPS) / sizeof(OP); counter++, OP = OPS[counter].run)

typedef struct {
	// Elke delegate kan meegegeven worden
	void* (*run)(void*);
} DOSTUFF;

void printInt(int a, char* multiplyType)
{
	// Getal printen
	printf("Operatie Type\tResultaat\n");
	printf("%s\t\t%i \n", multiplyType, a);
	return;
}

void multiplyInt(int a, int b){
	printInt(a * b, "*");
	return;
}

void extractInt(int a, int b){
	printInt(a - b, "-");
	return;
}

void addInt(int a, int b){
	printInt(a + b, "+");
	return;
}

void getModulo(int a, int b){
	printInt(a % b, "%");
	return;
}

int main()
{ 
	// Opslaan in array
	DOSTUFF stuff[4] = { { &addInt }, { &multiplyInt }, { &extractInt }, { getModulo } };
	
	void (*operation)(void*);
	
	RUN_OPS(stuff, operation){
		// Functies waar we 6 en 4 in gooien.
		operation(6, 4);
	}
	
    return 0;
}

