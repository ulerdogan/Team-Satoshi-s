/*
TEAM SATOSHI'S
Project: Airlines Reservation System

Ulaş Erdoğan - 040190230
Serdar Yaşar - 010190077
*/

#include <stdio.h>
#include <conio.h> // included this library to take getch() function to keep console window opened at the end of the program
#include <string.h> // included this library to use string functions
#include"design.h"

#define AIRPORT_NAME_LENGTH 20 // the maximum length of the airport names' strings are being controlled by "AIRPORT_NAME_LENGTH" macro
#define PASSWORD_LENGTH 20 // the maximum length of the adminstrator passwords is being controlled by "PASSWORD_LENGTH" macro
#define NAME_LENGTH 30 // the maximum length of the name is being controlled by "NAME_LENGTH" macro

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
// function that shows the main menu
int showMainMenu();
// menu switches designing function
void design();
// function that shows the admin menu
int showAdminMenu();

// structs that we used in our program

// a structure of the fligths that recorded to the system
typedef struct _Flight
{
    // "flight code, departure airport, destination airport, time of departure, time of destination and passenger capacity" records
    unsigned short int flightCode; // between 1111 - 9999
    char depAirport[AIRPORT_NAME_LENGTH]; // the maximum length of the airport names' strings are being controlled by "AIRPORT_NAME_LENGTH" macro
    char destAirport[AIRPORT_NAME_LENGTH]; // the maximum length of the airport names' strings are being controlled by "AIRPORT_NAME_LENGTH" macro
    char timeOfDep[5]; // "HH.MM" format : time of departure
    char timeOfDest[5]; // "HH.MM" format : time of destination
    unsigned short int passengerCapacity; // passenger capacities of the planes (%hu)
} Flight;

// a structuro of the bookings that passengers recorded
typedef struct _Booking
{
    char name[NAME_LENGTH]; // a string array to keep passengers names
    unsigned long long personalId; // a variable to keep the passengers personal ID (%llu)
    unsigned short int seatNumber; // a variable to keep seat data of booking (%hu)
    unsigned short int bookingId; // a variable to keep assigned booking ID to passengers (%hu)
    Flight flightInfo; // flight data of the bookings
} Booking;

int main()
{
    // the loop that keeps the program running
    while (True)
    {
        // keep the program going by admin signing up menu or by the main menu according to sign up status (use password record as control)
        if (isAdminSignedUp() == 0)
        {
            createPassword(); // the adminstrators sign up by creating password
        }
        else
        {
            // pass to main menu if the adminstrator has signed up
            switch(showMainMenu())
            {
                // adminstrator login option
                case 1:
                    // show options in admin menu
                    switch (showAdminMenu())
                    {
                        // adding a new flight
                        case 1:
                            break;
                        // editing current flights
                        case 2:
                            break;
                        // deleting flights
                        case 3:
                            break;
                        // listing current flights
                        case 4:
                            break;
                        // listing bookings   
                        case 5:
                            break;
                        // changing password option
                        case 6:
                            createPassword();
                            break;
                        // returning to main menu option
                        case 0:
                            break;                      
                        // default option for false inputs                                                                             
                        default:
                            printf("\n!!!!! An error occurred");
                    }
                    break;
                // passenger menu option
                case 2:
                    printf("passenger\n");
                    break;
                // exiting from the program option
                case 0:
                    printf("\nThe program has successfully closed.\nSEE YOU LATER!\n");

                    getch(); // end of the program statement and provide that the program doesn't end without user permission
                    return 0;
                // default option for false inputs
                default:
                    printf("\n!!!!! An error occurred");
            }
        }
    }

    getch(); // end of the program statement and provide that the program doesn't end without user permission
    return 0;
}

// functions

// a function that makes menu switch designs
void design(){
    printf("\n\n||||||||||||||||||||||||-------------||||||||||||||||||||||||\n");
    printf("|||||||||||||||||| << SATOSHI'S AIRPORT >> ||||||||||||||||||\n");
    printf("||||||||||||||||||||||||-------------||||||||||||||||||||||||\n\n");
}

// a function that checks if adminstrator of the system signed up
int isAdminSignedUp()
{
    // check the file database and find a adminstrator password
    if (fopen("password.txt", "r") == NULL) // True IS TEMPORARY
    {
        // if there are not a password, return 0 and express that admin must be signed up
        return 0;
    }
    else
    {
        // if there are a password, return 1 and express that there is an admin
        return 1;
    }
}

// a function that provides the sign up for the first time and makes the password changes
void createPassword()
{
    FILE *pwPtr; // pointer for password file database
    char password[PASSWORD_LENGTH]; // a string that keeps new password
    // check if are there record on the password database
    //if there are not a password record, create password and provide sign up; else verify the old password and change it
    if (fopen("password.txt", "r") == NULL)
    {
        design();
        printf("Please enter your new password (less than 20 characters): ");
        scanf("%s", password);
        pwPtr = fopen("password.txt", "w");
        fprintf(pwPtr, "%s", password);
    }
    // section to verify old password and change it
    else
    {
        design();
        char oldPassword[3][PASSWORD_LENGTH]; // a string array to verify be used in verifing passwords
        printf("Please, verify your password: ");
        scanf("%s", oldPassword[1]); // 1 indexed element is for checking old password
        printf("Please, verify your password again: ");
        scanf("%s", oldPassword[2]); // 2 indexed element is for checking old password

        pwPtr = fopen("password.txt", "r");  // open file to read old password
        fscanf(pwPtr, "%s", oldPassword[0]); // 0 indexed element is for getting and checking password from file database

        if (!strcmp(oldPassword[1], oldPassword[2]) && !strcmp(oldPassword[0], oldPassword[1])) // && !strcmp(oldPassword[0], DOSYADAKİ ŞİFRE) FILE OKUYUP KARŞILAŞTIRMA ÖZELLİĞİ EKLENECEK
        {
            design();
            printf("Please enter your new password (less than 20 characters): ");
            scanf("%s", password);
            pwPtr = fopen("password.txt", "w");
            fprintf(pwPtr, "%s", password);
        }
        else
        {
            design();
            printf("The passwords that you entered didn't match...");
        }
    }
    fclose(pwPtr);
}

// a function to show the main menu
int showMainMenu()
{
    design();

    int choice; // variable that will be returned as choice
    printf("1. Enter as adminstrator\n");
    printf("2. Enter as passenger\n");
    printf("0. Exit from the program\n");
    printf("\nPlease make your login option: ");
    scanf("%d", &choice);

    return choice;
}

// a function to open adminstrator menu if user choose to be logined as adminstrator
int showAdminMenu()
{
    design();

    FILE *pwPtr; // pointer for password file database
    char password[2][PASSWORD_LENGTH]; // a string array that keeps passwords entered and signupped to match to login 
    pwPtr = fopen("password.txt", "r");  // open file to read password from file database
    fscanf(pwPtr, "%s", password[0]); // 0 indexed element is for getting and checking password from file database

    printf("Please enter the admin password: ");
    scanf("%s", password[1]); // 1 indexed element is for getting password from user and compare

    // comparing the passwords and if the input is correct, continue to the program
    if(!strcmp(password[0], password[1]))
    {
        design();

        int choice;
        printf("1. Add a new flight\n");
        printf("2. Edit available flights\n");
        printf("3. Delete a flight\n");
        printf("4. List all available flights\n");
        printf("5. List all bookings\n");
        printf("6. Change your password\n");
        printf("0. Return to the main menu\n");
        printf("\nPlease make your menu option: ");
        scanf("%d", &choice);
        return choice;

    } else
    {
        printf("\nThe password you entered is not correct!");
        return 0; // same return with 6th option in the adminstrator menu: return to the main menu
    }
    

}