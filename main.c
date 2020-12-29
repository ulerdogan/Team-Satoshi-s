/*
TEAM SATOSHI'S
Project: Airlines Reservation System

Ulaş Erdoğan - 040190230
Serdar Yaşar - 010190077
*/

#include <stdio.h>
#include <conio.h>  // included this library to take getch() function to keep console window opened at the end of the program
#include <string.h> // included this library to use string functions

#define AIR_NAME_LENGTH 20 // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
#define PASSWORD_LENGTH 20 // the maximum length of the adminstrator passwords is being controlled by "PASSWORD_LENGTH" macro
#define NAME_LENGTH 30     // the maximum length of the name is being controlled by "NAME_LENGTH" macro

// a global variable to control main loop
int globalBoolean = 1;

// the function prototypes

// check if adminstrator of the system signed up
int isAdminSignedUp();
// provide the sign up for the first time and make the password changes
void createPassword();
// function that shows the main menu
void showMainMenu();
// menu switches designing function
void design();
// function that shows the admin menu
int showAdminMenu();
// function that provides log in by password check
int adminLogin();
// generating flight codes for the flights
int generateFlightCode();
// function that records flights to file database
void addFlight();
// function that lists and prints available flights
void listFlights();
// function that deletes the chosen flight
void deleteFlight();

// structs that we used in our program

// a structure of the fligths that recorded to the system
typedef struct _Flight
{
    // "flight code, airlines, departure airport, destination airport, time of departure, time of destination and passenger capacity" records
    int flightCode;                    // between 1111 - 9999
    char airlines[AIR_NAME_LENGTH];    // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
    char depAirport[AIR_NAME_LENGTH];  // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
    char destAirport[AIR_NAME_LENGTH]; // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
    float timeOfDep;                   // "HH.MM" format : time of departure
    float timeOfDest;                  // "HH.MM" format : time of destination
    int passengerCapacity;             // passenger capacities of the planes
} Flight;

// a structuro of the bookings that passengers recorded
typedef struct _Booking
{
    char name[NAME_LENGTH]; // a string array to keep passengers names
    int personalId;         // a variable to keep the passengers personal ID
    int seatNumber;         // a variable to keep seat data of booking
    int bookingId;          // a variable to keep assigned booking ID to passengers
    Flight flightInfo;      // flight data of the bookings
} Booking;

int main()
{
    // the loop that keeps the program running
    while (globalBoolean)
    {
        // keep the program going by admin signing up menu or by the main menu according to sign up status (use password record as control)
        if (isAdminSignedUp() == 0)
        {
            createPassword(); // the adminstrators sign up by creating password
        }
        else
        {
            showMainMenu();
        }
    }

    getch(); // end of the program statement and provide that the program doesn't end without user permission
    return 0;
}

// functions

// a function that makes menu switch designs
void design()
{
    printf("\n\n||||||||||||||||||||||||-------------||||||||||||||||||||||||\n");
    printf("|||||||||||||||||| << SATOSHI'S AIRPORT >> ||||||||||||||||||\n");
    printf("||||||||||||||||||||||||-------------||||||||||||||||||||||||\n\n");
}

// a function that checks if adminstrator of the system signed up
int isAdminSignedUp()
{
    // check the file database and find a adminstrator password
    if (fopen("password.txt", "r") == NULL)
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
    FILE *pwPtr;                    // pointer for password file database
    char password[PASSWORD_LENGTH]; // a string that keeps new password
    // check if are there record on the password database
    //if there are not a password record, create password and provide sign up; else verify the old password and change it
    if (fopen("password.txt", "r") == NULL)
    {
        design(); // designing
        printf("Please enter your new password (less than 20 characters): ");
        scanf("%s", password);
        pwPtr = fopen("password.txt", "w");
        fprintf(pwPtr, "%s", password);
    }
    // section to verify old password and change it
    else
    {
        design();                             // designing
        char oldPassword[3][PASSWORD_LENGTH]; // a string array to verify be used in verifing passwords
        printf("Please, verify your password: ");
        scanf("%s", oldPassword[1]); // 1 indexed element is for checking old password
        printf("Please, verify your password again: ");
        scanf("%s", oldPassword[2]); // 2 indexed element is for checking old password

        pwPtr = fopen("password.txt", "r");  // open file to read old password
        fscanf(pwPtr, "%s", oldPassword[0]); // 0 indexed element is for getting and checking password from file database

        if (!strcmp(oldPassword[1], oldPassword[2]) && !strcmp(oldPassword[0], oldPassword[1])) // && !strcmp(oldPassword[0], DOSYADAKİ ŞİFRE) FILE OKUYUP KARŞILAŞTIRMA ÖZELLİĞİ EKLENECEK
        {
            design(); // designing
            printf("Please enter your new password (less than 20 characters): ");
            scanf("%s", password);
            pwPtr = fopen("password.txt", "w");
            fprintf(pwPtr, "%s", password);
        }
        else
        {
            design(); // designing
            printf("The passwords that you entered didn't match...");
        }
    }
    fclose(pwPtr);
}

// a function to show the main menu
void showMainMenu()
{
    design(); // designing

    int choice; // variable that will be returned as choice
    printf("1. Enter as adminstrator\n");
    printf("2. Enter as passenger\n");
    printf("0. Exit from the program\n");
    printf("\nPlease make your login option: ");
    scanf("%d", &choice);

    // pass to main menu if the adminstrator has signed up
    switch (choice)
    {
    // adminstrator login option
    case 1:
        // make admin log in and show options in admin menu
        adminLogin();
        break;

    // passenger menu option
    case 2:
        printf("passenger\n");
        break;

    // exiting from the program option
    case 0:
        printf("\nThe program has successfully closed.\nSEE YOU LATER!\n");
        globalBoolean = 0; // to end main loop of the program
        break;

    // default option for false inputs
    default:
        printf("\n!!!!! An error occurred");
    }
}

// a function to open adminstrator menu if the admin has loginned succesfully
int showAdminMenu()
{
    design(); // designing

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
}

// a function to provide access to the admin menu by password checking
int adminLogin()
{
    design(); // designing

    FILE *pwPtr;                        // pointer for password file database
    char password[2][PASSWORD_LENGTH];  // a string array that keeps passwords entered and signupped to match to login
    pwPtr = fopen("password.txt", "r"); // open file to read password from file database
    fscanf(pwPtr, "%s", password[0]);   // 0 indexed element is for getting and checking password from file database

    printf("Please enter the admin password: ");
    scanf("%s", password[1]); // 1 indexed element is for getting password from user and compare

    fclose(pwPtr); // close the file

    // comparing the passwords and if the input is correct, continue to the program
    if (!strcmp(password[0], password[1]))
    {
        int boolean = 1; // a boolean variable to control while loop
        while (boolean)
        {
            switch (showAdminMenu())
            {
            // adding a new flight
            case 1:
                addFlight();
                break;
            // editing current flights
            case 2:
                break;
            // deleting flights
            case 3:
                deleteFlight();
                break;
            // listing current flights
            case 4:
                listFlights();
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
                boolean = 0;
                break;
            // default option for false inputs
            default:
                printf("\n!!!!! An error occurred");
            }
            printf("\n");
        }
    }
    else
    {
        printf("\nThe password you entered is not correct!");
        return 0; // if the password is not correct return to the main menu: the same return with 0 indexed option in the adminstrator menu
    }
}

// generating flight codes for the flights
int generateFlightCode()
{
    int firstFlightCode = 1111;

    Flight controlFlight; // a control struct to the file database
    Flight *cfPtr;        // pointer for control flight struct
    cfPtr = &controlFlight;

    FILE *flPtr; // pointer for flights file database

    flPtr = fopen("flights.txt", "r"); // open the file

    // read the file database until the end of the file
    // on each line of the file database, the flight codes will be incremented by 1
    while (!feof(flPtr))
    {
        fscanf(flPtr, "%d", &cfPtr->flightCode);
        fscanf(flPtr, "%s", cfPtr->airlines);
        fscanf(flPtr, "%s", cfPtr->depAirport);
        fscanf(flPtr, "%s", cfPtr->destAirport);
        fscanf(flPtr, "%f", &cfPtr->timeOfDep);
        fscanf(flPtr, "%f", &cfPtr->timeOfDest);
        fscanf(flPtr, "%d", &cfPtr->passengerCapacity);
        firstFlightCode = cfPtr->flightCode;
    }
    // to restart the flight code sequence
    if (firstFlightCode == 9999)
        firstFlightCode = 1110;

    fclose(flPtr); // close the file

    // one more of the last flight code will be assigned to new flight
    return ++firstFlightCode;
}

// a function to add flights by adminstrator to file database
void addFlight()
{
    design(); // designing

    Flight newFlight; // creation of flight struct to make records
    Flight *nfPtr;    // pointer to manage struct
    nfPtr = &newFlight;

    FILE *flPtr; // pointer for flights file database

    // create file database if does not exist
    if (fopen("flights.txt", "r") == NULL)
    {
        flPtr = fopen("flights.txt", "w");
        fclose(flPtr);
    }

    // inputting required informations
    nfPtr->flightCode = generateFlightCode();
    printf("Please enter the airlines: ");
    scanf("%s", nfPtr->airlines);
    printf("\nPlease enter the departure airport: ");
    scanf("%s", nfPtr->depAirport);
    printf("\nPlease enter the destination airport: ");
    scanf("%s", nfPtr->destAirport);
    printf("\nPlease enter the time of departure: ");
    scanf("%f", &nfPtr->timeOfDep);
    printf("\nPlease enter the time of destination: ");
    scanf("%f", &nfPtr->timeOfDest);
    printf("\nPlease enter the capacity of the plane: ");
    scanf("%d", &nfPtr->passengerCapacity);

    // open the file, handle the inputted information and close
    flPtr = fopen("flights.txt", "a");
    fprintf(flPtr, "%d %s %s %s %.2f %.2f %d\n", nfPtr->flightCode, nfPtr->airlines, nfPtr->depAirport, nfPtr->destAirport, nfPtr->timeOfDep, nfPtr->timeOfDest, nfPtr->passengerCapacity);
    printf("\n The flight has recorded succesfully...\n");
    fclose(flPtr);
}

// a function to list added flights from the file database
void listFlights()
{
    design(); // designing

    FILE *flPtr; // pointer for flights file database

    // create file database if does not exist to prevent errors
    if (fopen("flights.txt", "r") == NULL)
    {
        flPtr = fopen("flights.txt", "w");
        fclose(flPtr);
    }

    flPtr = fopen("flights.txt", "r"); // opening file database to read lines

    Flight readFlight; // struct for placing the flight informations that have read
    Flight *rfPtr;     // pointer to manage struct
    rfPtr = &readFlight;

    int counter = 1; // a variable to count the flight recors

    // reading the first records on the data
    fscanf(flPtr, "%d", &rfPtr->flightCode);
    fscanf(flPtr, "%s", rfPtr->airlines);
    fscanf(flPtr, "%s", rfPtr->depAirport);
    fscanf(flPtr, "%s", rfPtr->destAirport);
    fscanf(flPtr, "%f", &rfPtr->timeOfDep);
    fscanf(flPtr, "%f", &rfPtr->timeOfDest);
    fscanf(flPtr, "%d", &rfPtr->passengerCapacity);

    // keep reading data from the file while not end of the file then print them
    while (!feof(flPtr))
    {
        printf("%d- %d %s %s %s %.2f %.2f %d\n", counter, rfPtr->flightCode, rfPtr->airlines, rfPtr->depAirport, rfPtr->destAirport, rfPtr->timeOfDep, rfPtr->timeOfDest, rfPtr->passengerCapacity);
        fscanf(flPtr, "%d", &rfPtr->flightCode);
        fscanf(flPtr, "%s", rfPtr->airlines);
        fscanf(flPtr, "%s", rfPtr->depAirport);
        fscanf(flPtr, "%s", rfPtr->destAirport);
        fscanf(flPtr, "%f", &rfPtr->timeOfDep);
        fscanf(flPtr, "%f", &rfPtr->timeOfDest);
        fscanf(flPtr, "%d", &rfPtr->passengerCapacity);
        counter++; //increment counter
    }

    if (counter == 1)
    {
        printf("There are not any flight records!");
    }

    fclose(flPtr); // close the file
}

// a function to delete the chosen flight record
void deleteFlight()
{
    // listing flights before the choosing operation
    listFlights();

    // a variable that keeps the index of the
    int deleted;
    printf("\nPlease write the index of the flight that you want to delete: ");
    scanf("%d", &deleted);

    Flight deletedFlight; // a control struct to the file database
    Flight *dfPtr;        // pointer for control flight struct
    dfPtr = &deletedFlight;

    int counter = 1; // a counter to find the flight that want to be deleted.

    FILE *flPtr;                       // pointer for flights file database
    flPtr = fopen("flights.txt", "r"); // open the file to find the flight

    FILE *tflPtr;                         // pointer for flights file database
    tflPtr = fopen("t_flights.txt", "w"); // open the file to find the flight

    // reading the first records on the data
    fscanf(flPtr, "%d", &dfPtr->flightCode);
    fscanf(flPtr, "%s", dfPtr->airlines);
    fscanf(flPtr, "%s", dfPtr->depAirport);
    fscanf(flPtr, "%s", dfPtr->destAirport);
    fscanf(flPtr, "%f", &dfPtr->timeOfDep);
    fscanf(flPtr, "%f", &dfPtr->timeOfDest);
    fscanf(flPtr, "%d", &dfPtr->passengerCapacity);

    // read the file until the end of file database and record all of the flight to a temporary database except the one want to be deleted
    while (!feof(flPtr))
    {
        // if the flight record that read is not one want to be deleted, write it to the temporary file
        if (counter != deleted)
        {
            fprintf(tflPtr, "%d %s %s %s %.2f %.2f %d\n", dfPtr->flightCode, dfPtr->airlines, dfPtr->depAirport, dfPtr->destAirport, dfPtr->timeOfDep, dfPtr->timeOfDest, dfPtr->passengerCapacity);
        }
        fscanf(flPtr, "%d", &dfPtr->flightCode);
        fscanf(flPtr, "%s", dfPtr->airlines);
        fscanf(flPtr, "%s", dfPtr->depAirport);
        fscanf(flPtr, "%s", dfPtr->destAirport);
        fscanf(flPtr, "%f", &dfPtr->timeOfDep);
        fscanf(flPtr, "%f", &dfPtr->timeOfDest);
        fscanf(flPtr, "%d", &dfPtr->passengerCapacity);

        counter++;
    }

    fclose(flPtr);  // close the file
    fclose(tflPtr); // close the file

    // after the deleting and copying process, delete the main file database and make the temporary file, main file
    remove("flights.txt");
    rename("t_flights.txt", "flights.txt");
}