#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VehicalManagement.h"


// create memory copy function to copy vehicle data
void copyMemory(char* dest, char* source, size_t size){
    for (size_t i = 0; i < size; i++){ // loop through each byte to copy
        dest[i] = source[i]; // copy byte from source to destination
    }
}

/*

Purpose: Dynamically allocates a string to store a vehicle's information. Specifically, the value and model year

are stored in the first 4 bytes. The remaining memory is for the description of the vehicle.

Parameters : None

Returns: a dynamically allocated block of memory containing the vehicle's information

*/

char* createVehicle() {
    unsigned int value, year;
    char description[100];
    printf("Enter vehicle value (max 2097151): ");
    scanf("%u", &value); // read vehicle's value from user input
    
    printf("Enter model year (max 2047): ");
    scanf("%u", &year); // read vehicle's year from user input
    
    getchar();  // Clear newline character
    
    printf("Enter vehicle description: ");
    fgets(description, sizeof(description), stdin);
    
    // remove newline character
    for (int i = 0; i < 100; i++) {
        if (description[i] == '\n') {
            description[i] = '\0'; // replace newline with null terminator
            break;
        }
    }
    size_t desSize = strlen(description) + 1; // calculate size of description, including the null terminator
    char* vehicle = (char*)malloc(4 + desSize); //allocate memory to store value and year, and description 

    if(vehicle == NULL){
        printf("memory allocation failed! \n");
        return NULL;
    }

    unsigned int dataStorage = (value << 11) | year & MAX_YEAR; 
    // shift those bit of value to the left and 
    // I use bitwise AND to make sure that the year is placed into the lower 11 bits 
    copyMemory(vehicle, (char*)&dataStorage, 4); // copy combined value and year into the first 4 bytes of the allocated memory

    //store description after the first 4 byte
    copyMemory(vehicle + 4, description, desSize);

    return vehicle;

}
/*

Purpose: Display the information stored in a vehicle

Parameters: char* representing all information stored for a vehicle

Returns: Nothing

*/

void displayVehicle(char* vehicle){
    // check if vehicle pointer is NULL
    if(vehicle == NULL){
        printf("vehicle is NULL. \n");
        return;
    }

    unsigned int dataStorage;
    copyMemory((char*)&dataStorage,vehicle, 4);
    unsigned int value = dataStorage >> 11; // use right shift to move the value bits to the right
    unsigned int year = dataStorage & MAX_YEAR; // use bitwise AND to get year bits
    printf("Vehicle Value: %u\nVehicle year: %u\nDescription: %s\n", value, year, vehicle +4);

}

/*

Purpose: Store multiple vehicles in an array. Dynamically allocates an array of char pointers.

Calls the createVehicle method for each vehicle to be created

Parameters: int - Number of vehicles to add to the array

Returns: a dynamically array of char*'s, each pointer representing a vehicle

*/
char** createGarage(int numOfVehicles){
    char** garage= (char**)malloc(numOfVehicles * sizeof(char*)); // allocate memory
    // check if the vehicle creation is failed 
    if(garage == NULL){
        printf("Memory allocation is failed. \n");
        return NULL;
    }
    for ( int i = 0; i < numOfVehicles; i++) {
        garage[i] = createVehicle();


    }
    return garage;

}
/*

Purpose: Display all the information stored for each vehicle in the garage. Calls

displayVehicle for each vehicle in the garage.

Parameters: char** - pointer to the garage

int - number of vehicles in the garage

Returns: Nothing.

*/
void displayGarage(char** garage, int numOfVehicles){
    if (garage == NULL){
        printf("garage is NULL. \n");
        return;
        
    }
    for( int i =0 ; i< numOfVehicles; i ++){
        printf("vehicle %d:\n" ,i + 1);
        displayVehicle(garage[i]);

    }

}

/*

Purpose: Remove a vehicle from the garage. Returns a new dynamically allocated garage with remaining cars stored in it.

Note that this function should free the garage passed in.

Parameters:  char** - pointer to current garage

int - number of vehicles in current garage

int - index of the vehicle to remove (0 based)

Returns: a reference to the new dynamically allocated garage

*/
char ** removeVehicle(char** garage, int numOfVehicles, int indexOfRemoveVehicle){
    //check invalid index
    if(garage == NULL || indexOfRemoveVehicle < 0 || indexOfRemoveVehicle >= numOfVehicles ){
        printf("invalid index. \n");
        return garage;
    }
    
    // allocate memory for new garage
    char** newGarage = (char**)malloc((numOfVehicles -1)* sizeof(char*));
    if(newGarage == NULL){
        printf("memory allocation is failed. \n");
        return garage;
    }


    int newIndex = 0;
    for(int i = 0; i < numOfVehicles; i++){
        if(i != indexOfRemoveVehicle){
            newGarage[newIndex++] = garage[i]; // copy vehicle pointer to new garage
        }else{
            free(garage[i]);// free the memory that is removed
        }
    }
        free(garage); //free the memory of the old garage
        return newGarage; // return pointer to new garage
    }