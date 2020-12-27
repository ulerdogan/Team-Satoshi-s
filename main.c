/*
TEAM SATOSHI'S
Project: Airlines Reservation System

Ulaş Erdoğan - 040190230
Serdar Yaşar - 010190077
*/

#include <stdio.h>
#include <conio.h>             // included this library to take getch() function to keep console window opened at the end of the program
#define AIRPORT_NAME_LENGTH 20 // the maximum length of the airport names' strings are being controlled by "AIRPORT_NAME_LENGTH" macro

enum boolean
{
    False,
    True
}; // created an enumeration to be used in the loops

// the function prototypes

// check if adminstrator of the system signed up
int isAdminSignedUp();
// provide the sign up for the first time and make the password changes
void createPassword();

// structs that we used in our program

// a structure of the fligths that recorded to the system
typedef struct Flight
{
    // "flight code, departure airport, destination airport, time of departure, time of destination and passenger capacity" records
    unsigned short int flightCode;         // between 11111 - 99999
    char depAirport[AIRPORT_NAME_LENGTH];  // the maximum length of the airport names' strings are being controlled by "AIRPORT_NAME_LENGTH" macro
    char destAirport[AIRPORT_NAME_LENGTH]; // the maximum length of the airport names' strings are being controlled by "AIRPORT_NAME_LENGTH" macro
    char timeOfDep[5];                     // "HH.MM" format : time of departure
    char timeOfDest[5];                    // "HH.MM" format : time of destination
    unsigned short int passengerCapacity;
} Flight;

int main()
{
    // the loop that keeps the program running
    while (True)
    {
        // keep the program going by admin signing up menu or by the main menu according to sign up status (use password record as control)
        if (isAdminSignedUp == 0)
        {
            createPassword(); // the adminstrators sign up by creating password
        }
        else
        {

        }
    }

    
    getch(); // end of the program statement and provide that the program doesn't end without user permission
    return 0;
}

// functions

// a function that checks if adminstrator of the system signed up
int isAdminSignedUp()
{
    // check the file database and find a adminstrator password
    ;
    if (True) // True IS TEMPORARY
    { 
        // if there are a password, return 1 and express that there is an admin
        ;
        return 1;
    }
    else
    {
        // if there are not a password, return 0 and express that admin must be signed up
        ;
        return 0;
    }
}

// a function that provides the sign up for the first time and makes the password changes
void createPassword()
{
    // check if there are record on the password database, clean it
    if (True)// True IS TEMPORARY
    { 
        ;
    }

    // record new password
    ;
}
