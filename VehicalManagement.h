#include <stdlib.h>
#ifndef VEHICAL_MANAGEMENT
#define VEHICAL_MANAGEMENT


#define MAX_YEAR 0x7FF 
#define MAX_VALUE 0x1FFFFF000



void copyMemory(char* dest, char* source, size_t size);

char* createVehicle();

 
void displayVehicle(char* vehicle);

 
char** createGarage(int numOfVehicles);

 
void displayGarage(char** garage, int numOfVehicles);

 
char ** removeVehicle(char** garage, int numOfVehicles, int indexOfRemoveVehicle);

#endif