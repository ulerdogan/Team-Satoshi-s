/*
TEAM SATOSHI'S
Project: Airlines Reservation System

Ulaş Erdoğan - 040190230
Serdar Yaşar - 010190077
*/

#include <stdio.h>
#include <conio.h> // included this library to take getch() function to keep console window opened at the end of the program
#define AIRPORT_NAME_LENGTH 20

// the function prototypes

// check if adminstrator of the system signed up
int isAdminSignedUp();
// provide the sign up for the first time and make the password changes
void createPassword();

// structs that we used in our program

// a structure of the fligths that recorded to the system
struct Flight {
    // "flight code, departure airport, destination airport, time of departure, time of destination and passenger capacity" records
    int flightCode;
    char depAirport[AIRPORT_NAME_LENGTH]; // the maximum length of the airport names' strings are being controlled by "AIRPORT_NAME_LENGTH" macro
    char destAirport[AIRPORT_NAME_LENGTH]; // the maximum length of the airport names' strings are being controlled by "AIRPORT_NAME_LENGTH" macro
    char timeOfDep[5]; // "HH.MM" format
    char timeOfDest[5]; // "HH.MM" format
    int passengerCapacity;
};

int main() {

    // the loop that keeps the program running
    while (1) {

        // keep the program going by admin signing up menu or by the main menu according to sign up status (use password record as control)
        if (isAdminSignedUp == 0) {
            // the adminstrators sign up by creating password
            createPassword();
        } else {

        }




    }

    // end of the program statement and provide that the program doesn't end without user permission
    getch();
    return 0;
}

// our functions

// a function that checks if adminstrator of the system signed up
int isAdminSignedUp() {
    // check the file database and find a adminstrator password
    ;
    if(;) {
        // if there are a password, return 1 and express that there is an admin
        return 1;
    } else {
        // if there are not a password, return 0 and express that admin must be signed up
        return 0;
    }
}

// a function that provides the sign up for the first time and makes the password changes
void createPassword(){
    // check if there are record on the password database, clean it
    if(;){
        ;
    }

    // record new password
    ;

}
