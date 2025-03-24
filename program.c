#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VehicalManagement.h"




void testGarage()

{
       //Number of vehicles to add to the garage

       int numVehicles;

 

       //Prompt the user to enter how many vehicles to store

       printf("Enter number of vehicles you would like to store: ");

       scanf("%d", &numVehicles);

 

       //Must clear the input stream from newline

       getc(stdin);

 

       //Create a new garage

       char ** garage = createGarage(numVehicles);


       //Display the contents of the garage
       printf("Display the vehicle before removal:\n");
       displayGarage(garage, numVehicles);

        // Ask user which vehicle to remove
        int index;
        printf("\nEnter index of vehicle to remove (0 to %d): ", numVehicles - 1);
        scanf("%d", &index);
        getchar();

        if (index >= 0 && index < numVehicles) {
            garage = removeVehicle(garage, numVehicles--, index);
            printf("\nGarage after removal:\n");
            displayGarage(garage, numVehicles);
        } else {
            printf("\nInvalid index! No vehicle removed.\n");
        }

        // Free remaining memory
        for (int i = 0; i < numVehicles; i++) {
            free(garage[i]);
        }
        free(garage);
    }


int main()
{
    testGarage();


    return EXIT_SUCCESS;
}