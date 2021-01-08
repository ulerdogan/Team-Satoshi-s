/*
TEAM SATOSHI'S
Project: Airlines Reservation System

Ulaş Erdoğan - 040190230
Serdar Yaşar - 010190077
*/

#include <stdio.h>
#include <conio.h>  // included this library to take getch() function to keep console window opened at the end of the program
#include <string.h> // included this library to use string functions
#include <stdlib.h>
#include <time.h>

#define AIR_NAME_LENGTH 20 // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
#define PASSWORD_LENGTH 20 // the maximum length of the adminstrator passwords is being controlled by "PASSWORD_LENGTH" macro
#define NAME_LENGTH 30     // the maximum length of the name is being controlled by "NAME_LENGTH" macro
#define SEAT_ROW 50 

int globalBoolean = 1; // a global variable to control main loop

// the function prototypes

int isAdminSignedUp(); // check if adminstrator of the system signed up

void createPassword(); // provide the sign up for the first time and make the password changes

void showMainMenu(); // function that shows the main menu

void design(); // menu switches designing function

int showAdminMenu(); // function that shows the admin menu

int adminLogin(); // function that provides log in by password check

int generateFlightCode(); // generating flight codes for the flights

void seatOrder(int flightCode, int passengerCapacity);

void addFlight(); // function that records flights to file database

int listFlights(); // function that lists and prints available flights

void deleteFlight(); // function that deletes the chosen flight

void editFlight(); // function that edits the chosen flight

void listPassFlight();

int bookingIdGenerator();

void selectSeat(int flightCode, int passengerCapacity, char seatNumber[2]);

void bookPassFlight();

void listPassBooking();

void deletePassBooking();

int showPassMenu();

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

typedef struct _Seat
{
    // "flight code, airlines, departure airport, destination airport, time of departure, time of destination and passenger capacity" records
    int flightCode;                    // between 1111 - 9999
    char seatTable[SEAT_ROW][6];

}Seat;

// a structuro of the bookings that passengers recorded
typedef struct _Booking
{
    char name[NAME_LENGTH];            // a string array to keep passengers names
    char surname[NAME_LENGTH];
    unsigned long long int personalId; // a variable to keep the passengers personal ID
    char seatNumber[2];                    // a variable to keep seat data of booking
    int bookingId;                     // a variable to keep assigned booking ID to passengers
    int flightCode;                    // between 1111 - 9999
    char airlines[AIR_NAME_LENGTH];    // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
    char depAirport[AIR_NAME_LENGTH];  // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
    char destAirport[AIR_NAME_LENGTH]; // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
    float timeOfDep;                   // "HH.MM" format : time of departure
    float timeOfDest;
    int passengerCapacity; // passenger capacities of the planes
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
    FILE *pwPtr;                        // pointer for password file database
    pwPtr = fopen("password.txt", "r"); // opening the password file to check is it existing

    // check the file database and find a adminstrator password
    if (pwPtr == NULL)
    {
        // if there are not a password, return 0 and express that admin must be signed up
        return 0;
    }
    else
    {
        // if there are a password, return 1 and express that there is an admin
        return 1;
    }
    fclose(pwPtr); // closing the password file database
}

// a function that provides the sign up for the first time and makes the password changes
void createPassword()
{
    FILE *pwPtr;                       // pointer for password file database
    char password[2][PASSWORD_LENGTH]; // a string that keeps entered new passwords

    FILE *tpwPtr; // a temporary file database opening to chech does the file exists
    tpwPtr = fopen("password.txt", "r");
    // check if are there record on the password database
    //if there are not a password record, create password and provide sign up; else verify the old password and change it
    if (tpwPtr == NULL)
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
        char oldPassword[2][PASSWORD_LENGTH]; // a string array to verify be used in verifing passwords
        printf("Please, verify your old password: ");
        scanf("%s", oldPassword[1]); // 1 indexed element is for checking old password

        pwPtr = fopen("password.txt", "r");  // open file to read old password
        fscanf(pwPtr, "%s", oldPassword[0]); // 0 indexed element is for getting and checking password from file database

        if (!strcmp(oldPassword[1], oldPassword[0])) // if the passwords that entered and read from database match, get new password and change it
        {
            design(); // designing
            printf("Please enter your new password (less than 20 characters): ");
            scanf("%s", password[0]);
            printf("Please enter your new password again: ");
            scanf("%s", password[1]);
            if (!strcmp(password[1], password[0]))
            {
                pwPtr = fopen("password.txt", "w");
                fprintf(pwPtr, "%s", password[0]);
                printf("\nThe password has succesfully changed...\nYou are redirected to the main menu.");
            }
            else
            {
                design(); // designing
                printf("The passwords that you entered didn't match...\nYou are redirected to the main menu.");
            }
        }
        else
        {
            design(); // designing
            printf("The passwords that you entered didn't match...\nYou are redirected to the main menu.");
        }
    }
    fclose(tpwPtr); // closing the files
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
        showPassMenu();
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
    char password[2][PASSWORD_LENGTH];  // a string array that keeps passwords entered and sign upped to match to login
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
            // a switch case that calls the menu functions by the return of show admin menu function
            switch (showAdminMenu())
            {
            // adding a new flight
            case 1:
                addFlight();
                break;
            // editing current flights
            case 2:
                editFlight();
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
                boolean = 0; // to be returned to main menu after the password changing process
                break;
            // returning to main menu option
            case 0:
                boolean = 0; // ending the while loop and returning to main menu
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

void seatOrder(int flightCode, int passengerCapacity)
{
    int rowConstant = passengerCapacity/6;
    int i,j; //i satır j sütun için
    Seat *seatInfoPtr, seatInfo;
    seatInfoPtr = &seatInfo;

    seatInfoPtr->flightCode = flightCode;
    seatInfoPtr->seatTable[rowConstant][6];

    for(i=0; i < rowConstant; i++)
    {
        for(j=0; j<=5; j++)
        {
            seatInfoPtr->seatTable[i][j] = '+';
        }
    }

    FILE *seatfPtr;
    
    if ((seatfPtr = fopen("seatInfo.dat","wb"))==NULL)
    {
        printf("%s","File could not be opened!\n");
    }
    else
    {
        fwrite(seatInfoPtr, sizeof(Seat), 1, seatfPtr);
        fclose(seatfPtr);
    }
}

// a function to add flights by adminstrator to file database
void addFlight()
{
    design(); // designing

    Flight newFlight; // creation of flight struct to make records
    Flight *nfPtr;    // pointer to manage struct
    nfPtr = &newFlight;

    FILE *flPtr; // pointer for flights file database

    FILE *tflPtr;                       // pointer for temporary flight database handler
    tflPtr = fopen("flights.txt", "r"); // opening file to check does it exist

    // create file database if does not exist to prevent errors
    if (tflPtr == NULL)
    {
        flPtr = fopen("flights.txt", "w");
        fclose(flPtr);
    }
    fclose(tflPtr); // closing the file that we opened to check

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

    seatOrder(nfPtr->flightCode, nfPtr->passengerCapacity);
}

// a function to list added flights from the file database
int listFlights()
{
    design(); // designing

    FILE *flPtr; // pointer for flights file database

    FILE *tflPtr;                       // pointer for temporary flight database handler
    tflPtr = fopen("flights.txt", "r"); // opening file to check does it exist

    // create file database if does not exist to prevent errors
    if (tflPtr == NULL)
    {
        flPtr = fopen("flights.txt", "w");
        fclose(flPtr);
    }
    fclose(tflPtr); // closing the file that we opened to check

    flPtr = fopen("flights.txt", "r"); // opening file database to read lines

    Flight readFlight; // struct for placing the flight informations that have read
    Flight *rfPtr;     // pointer to manage struct
    rfPtr = &readFlight;

    int counter = 1; // a variable to count the flight records

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
        printf("%2d- %d %s %s %s %.2f %.2f %d\n", counter, rfPtr->flightCode, rfPtr->airlines, rfPtr->depAirport, rfPtr->destAirport, rfPtr->timeOfDep, rfPtr->timeOfDest, rfPtr->passengerCapacity);
        fscanf(flPtr, "%d", &rfPtr->flightCode);
        fscanf(flPtr, "%s", rfPtr->airlines);
        fscanf(flPtr, "%s", rfPtr->depAirport);
        fscanf(flPtr, "%s", rfPtr->destAirport);
        fscanf(flPtr, "%f", &rfPtr->timeOfDep);
        fscanf(flPtr, "%f", &rfPtr->timeOfDest);
        fscanf(flPtr, "%d", &rfPtr->passengerCapacity);
        counter++; //increment counter
    }

    fclose(flPtr); // close the file

    if (counter == 1)
    {
        printf("There are not any flight records!");

        // show that there are any records
        return 0;
    }
    else
    {
        //show that there are records
        return 1;
    }
}

// a function to delete the chosen flight record
void deleteFlight()
{
    // listing flights before the choosing operation and direct to the deleting operation if there are records
    if (listFlights() == 1)
    {

        // a variable that keeps the index of the chosen flight
        int deleted;
        printf("\nPlease write the index of the flight that you want to delete: ");
        scanf("%d", &deleted);

        Flight deletedFlight; // a control struct to the file database
        Flight *dfPtr;        // pointer for control flight struct
        dfPtr = &deletedFlight;

        int counter = 1;       // a counter to find the flight that want to be deleted.
        int deleteChecker = 1; // a variable that will check the false inputs and if any delete operation doesn't process gives alert

        FILE *flPtr;                       // pointer for flights file database
        flPtr = fopen("flights.txt", "r"); // open the file to find the flight

        FILE *tflPtr;                         // pointer for flights temporary file database
        tflPtr = fopen("t_flights.txt", "w"); // open the file to record the flights temporarily

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
                deleteChecker++; // increment on every passing index
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

        // if the counter for the records and counter for the passed records are equal, it means any delete operation didn't happened
        if (deleteChecker == counter)
        {
            printf("\n!!!!! An error occurred");
        }

        fclose(flPtr);  // close the file
        fclose(tflPtr); // close the file

        // after the deleting and copying process, delete the main file database and make the temporary file, main file
        remove("flights.txt");
        rename("t_flights.txt", "flights.txt");
    }
}

// a function to edit the flights that recorded
void editFlight()
{
    // listing flights before the choosing operation and direct to the editing operation if there are records
    if (listFlights() == 1)
    {

        // a variable that keeps the index of the chosen flight
        int edited;
        printf("\nPlease write the index of the flight that you want to edit: ");
        scanf("%d", &edited);

        // a variable that keeps the index of the chosen data type
        int type;
        printf("\n1. Airline\n2. Departure Airport\n3. Destination Airport\n4. Time of Departure\n5. Time of Destination\n6. Capacity\n");
        printf("\nPlease write the index of the data type you want to change: ");
        scanf("%d", &type);

        Flight editedFlight; // a control struct to the file database
        Flight *efPtr;       // pointer for control flight struct
        efPtr = &editedFlight;

        int counter = 1;       // a counter to find the flight that want to be deleted.
        int deleteChecker = 1; // a variable that will check the false inputs and if any edit operation doesn't process gives alert

        FILE *flPtr;                       // pointer for flights file database
        flPtr = fopen("flights.txt", "r"); // open the file to read the flights

        FILE *tflPtr;                         // pointer for flights temporary file database
        tflPtr = fopen("t_flights.txt", "w"); // open the file to record the flights temporarily

        // reading the first records on the data
        fscanf(flPtr, "%d", &efPtr->flightCode);
        fscanf(flPtr, "%s", efPtr->airlines);
        fscanf(flPtr, "%s", efPtr->depAirport);
        fscanf(flPtr, "%s", efPtr->destAirport);
        fscanf(flPtr, "%f", &efPtr->timeOfDep);
        fscanf(flPtr, "%f", &efPtr->timeOfDest);
        fscanf(flPtr, "%d", &efPtr->passengerCapacity);

        // read the file until the end of file database and record all of the flight to a temporary database except the one want to be deleted
        while (!feof(flPtr))
        {
            // if the flight record that read is not one want to be edit, write it to the temporary file
            if (counter != edited)
            {
                fprintf(tflPtr, "%d %s %s %s %.2f %.2f %d\n", efPtr->flightCode, efPtr->airlines, efPtr->depAirport, efPtr->destAirport, efPtr->timeOfDep, efPtr->timeOfDest, efPtr->passengerCapacity);
                deleteChecker++; // increment on every passing index
            }
            else
            {
                //get inputs from the adminstrator about the data that adminstrator wanted to change
                switch (type)
                {
                case 1:
                    printf("\nPlese enter the new airlines of the flight: ");
                    scanf("%s", &efPtr->airlines);
                    break;
                case 2:
                    printf("\nPlese enter the new departure airport of the flight: ");
                    scanf("%s", efPtr->depAirport);
                    break;
                case 3:
                    printf("\nPlese enter the new destination airport of the flight: ");
                    scanf("%s", efPtr->destAirport);
                    break;
                case 4:
                    printf("\nPlese enter the new time of departure of the flight: ");
                    scanf("%f", &efPtr->timeOfDep);
                    break;
                case 5:
                    printf("\nPlese enter the new time of destination of the flight: ");
                    scanf("%f", &efPtr->timeOfDest);
                    break;
                case 6:
                    printf("\nPlese enter the capacity of the flight: ");
                    scanf("%d", &efPtr->passengerCapacity);
                    break;
                default:
                    printf("!!!!! An error occurred");
                }
                // then write the edited data to the temporary file database
                fprintf(tflPtr, "%d %s %s %s %.2f %.2f %d\n", efPtr->flightCode, efPtr->airlines, efPtr->depAirport, efPtr->destAirport, efPtr->timeOfDep, efPtr->timeOfDest, efPtr->passengerCapacity);
            }
            fscanf(flPtr, "%d", &efPtr->flightCode);
            fscanf(flPtr, "%s", efPtr->airlines);
            fscanf(flPtr, "%s", efPtr->depAirport);
            fscanf(flPtr, "%s", efPtr->destAirport);
            fscanf(flPtr, "%f", &efPtr->timeOfDep);
            fscanf(flPtr, "%f", &efPtr->timeOfDest);
            fscanf(flPtr, "%d", &efPtr->passengerCapacity);

            counter++;
        }

        // if the counter for the records and counter for the passed records are equal, it means any edit operation didn't happened
        if (deleteChecker == counter)
        {
            printf("\n!!!!! An error occurred");
        }

        fclose(flPtr);  // close the file
        fclose(tflPtr); // close the file

        // after the deleting and copying process, delete the main file database and make the temporary file, main file
        remove("flights.txt");
        rename("t_flights.txt", "flights.txt");
    }
}

void listPassFlight()
{
    design();

    FILE *fPtr; // File pointer for "flights.txt" database

    if ((fPtr = fopen("flights.txt", "r")) == NULL)
    {
        printf("%s", "Our service is temporarily unavailable. Please try again later!");
    }
    else
    {  
        char cmpdepAirport[AIR_NAME_LENGTH], cmpdestAirport[AIR_NAME_LENGTH];
        Flight *fpassPtr, fpassFlight; // For holding dep. and dest. informations are which came from "flight.txt" database for comparing
        fpassPtr = &fpassFlight;

        printf("%s", "Please Enter the Name of Departure Airport and Press Enter\n");
        scanf("%s", cmpdepAirport);
        printf("\n%s", "Please Enter the Name of Destination Airport and Press Enter\n");
        scanf("%s", cmpdestAirport);

        fscanf(fPtr, "%d", &fpassPtr->flightCode);
        fscanf(fPtr, "%s", fpassPtr->airlines);
        fscanf(fPtr, "%s", fpassPtr->depAirport);
        fscanf(fPtr, "%s", fpassPtr->destAirport);
        fscanf(fPtr, "%f", &fpassPtr->timeOfDep);
        fscanf(fPtr, "%f", &fpassPtr->timeOfDest);
        fscanf(fPtr, "%d", &fpassPtr->passengerCapacity);

        FILE *afPtr;

        if ((afPtr = fopen("t_avFlights.txt", "w")) == NULL)
        {
            printf("%s", "An error occured!");
        }
        else
        {   int *iPtr, i = 1;
            iPtr = &i;

            while (!feof(fPtr))
            {

                if ((strcmp(strupr(cmpdepAirport), fpassPtr->depAirport) == 0) && (strcmp(strupr(cmpdestAirport), fpassPtr->destAirport) == 0))
                {
                    fprintf(afPtr, "%d %s %s %s %.2f %.2f %d\n", fpassPtr->flightCode, fpassPtr->airlines, fpassPtr->depAirport,
                    fpassPtr->destAirport, fpassPtr->timeOfDep, fpassPtr->timeOfDest, fpassPtr->passengerCapacity);

                    printf("%d %d %s %s %s %.2f %.2f %d\n", i, fpassPtr->flightCode, fpassPtr->airlines, fpassPtr->depAirport,
                    fpassPtr->destAirport, fpassPtr->timeOfDep, fpassPtr->timeOfDest, fpassPtr->passengerCapacity);

                    *iPtr += 1;
                }

                fscanf(fPtr, "%d", &fpassPtr->flightCode);
                fscanf(fPtr, "%s", fpassPtr->airlines);
                fscanf(fPtr, "%s", fpassPtr->depAirport);
                fscanf(fPtr, "%s", fpassPtr->destAirport);
                fscanf(fPtr, "%f", &fpassPtr->timeOfDep);
                fscanf(fPtr, "%f", &fpassPtr->timeOfDest);
                fscanf(fPtr, "%d", &fpassPtr->passengerCapacity);
            } 

            if (i == 1)
            {
                printf("%s", "No flight found suitable for your preferences!");
                // return showAdminMenu gibi bir şey gelecek
            }

            fclose(fPtr);
            fclose(afPtr);
        }
    }
}


void bookPassFlight()
{
    listPassFlight();

    int passPref;

    printf("\n%s\n", "Please enter the flight code is which you prefer from above");
    scanf("%d", &passPref);

    FILE *afPtr;

    if ((afPtr = fopen("t_avFlights.txt", "r")) == NULL)
    {
        printf("%s", "An error occured!");
        //return mainmenu
    }
    else
    {   
        Booking *bInfoPtr, bookingInfo;
        bInfoPtr = &bookingInfo;

        fscanf(afPtr, "%d", &bInfoPtr->flightCode);
        fscanf(afPtr, "%s", bInfoPtr->airlines);
        fscanf(afPtr, "%s", bInfoPtr->depAirport);
        fscanf(afPtr, "%s", bInfoPtr->destAirport);
        fscanf(afPtr, "%f", &bInfoPtr->timeOfDep);
        fscanf(afPtr, "%f", &bInfoPtr->timeOfDest);
        fscanf(afPtr, "%d", &bInfoPtr->passengerCapacity);

        int *iPtr, i = 1; //It is an indexer for determining subscript of flightInfo[]
        iPtr = &i;

        while (!feof(afPtr))
        {
            if (passPref == bInfoPtr->flightCode)
            {
                *iPtr += 1;
            }

            fscanf(afPtr, "%d", &bInfoPtr->flightCode);
            fscanf(afPtr, "%s", bInfoPtr->airlines);
            fscanf(afPtr, "%s", bInfoPtr->depAirport);
            fscanf(afPtr, "%s", bInfoPtr->destAirport);
            fscanf(afPtr, "%f", &bInfoPtr->timeOfDep);
            fscanf(afPtr, "%f", &bInfoPtr->timeOfDest);
            fscanf(afPtr, "%d", &bInfoPtr->passengerCapacity);
        }

        fclose(afPtr);
        remove("t_avFlights.txt");
    
        if (i == 2)
        {
            printf("\n%s\n", "Please enter your name:");
            scanf("%30s", bInfoPtr->name);

            printf("\n%s\n", "Please enter your surname:");
            scanf("%30s", bInfoPtr->surname);

            printf("\n%s\n", "Please enter your ID number:");
            scanf("%11llu", &bInfoPtr->personalId);

            selectSeat(bInfoPtr->flightCode, bInfoPtr->passengerCapacity, bInfoPtr->seatNumber);
            
            bInfoPtr->bookingId = bookingIdGenerator();

            FILE *bookingfPtr;

            if ((bookingfPtr = fopen("PassengerBookingInfo.txt", "a")) == NULL)
            {
                printf("%s", "An error occured!");
                //return mainmenu
            }
            else
            {   
                fprintf(bookingfPtr, "%s %s %11llu %d %d %ld %s %s %s %.2f %.2f\n", strupr(bInfoPtr->name), strupr(bInfoPtr->surname), 
                bInfoPtr->personalId, bInfoPtr->seatNumber, bInfoPtr->bookingId, bInfoPtr->flightCode, strupr(bInfoPtr->airlines), 
                strupr(bInfoPtr->depAirport), strupr(bInfoPtr->destAirport), bInfoPtr->timeOfDep, bInfoPtr->timeOfDest);

                fclose(bookingfPtr);

                printf("\n%s\t%d\n%s\n", "Thank You for Choosing SATOSHI's AIRPORT! Your Booking Code is:", bInfoPtr->bookingId,
               "You can cancel your booking by using your booking code!");
            }
        }
    }    
}


int bookingIdGenerator()
{
    int generatedId;
    
    srand(time(NULL));
    generatedId = 10000 + rand() % 89999;

    Booking *bInfoPtr, bookingInfo; //This variable and pointer is used for receiving booking informations (except fligt informations) from "Passenger Booking Info.txt" file
    bInfoPtr = &bookingInfo;
    FILE *bookingfPtr;

    if ((bookingfPtr = fopen("PassengerBookingInfo.txt", "r")) == NULL)
    {
        printf("%s", "An error occured!");
    }
    else
    {
        fscanf(bookingfPtr, "%s", bInfoPtr->name);
        fscanf(bookingfPtr, "%s", bInfoPtr->surname);
        fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
        fscanf(bookingfPtr, "%d", bInfoPtr->seatNumber);
        fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
        fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
        fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
        fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
        fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
        fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
        fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);

        while (!feof(bookingfPtr))
        {
            if (generatedId == bInfoPtr->bookingId)
            {
                generatedId = 10000 + rand() % 89999;
            }
        
            fscanf(bookingfPtr, "%s", bInfoPtr->name);
            fscanf(bookingfPtr, "%s", bInfoPtr->surname);
            fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
            fscanf(bookingfPtr, "%d", bInfoPtr->seatNumber);
            fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
            fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
            fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
            fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
            fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);
        }
        fclose(bookingfPtr);
    }
    
    return generatedId;
}

void selectSeat(int flightCode, int passengerCapacity, char seatNumber[])
{
    Seat *seatInfoPtr, seatInfo;
    seatInfoPtr = &seatInfo;

    int *countPtr, counter = 0; //fseek yazarken hangi recorda gideceğimizi gösterecek
    countPtr = &counter;
    
    FILE *seatfPtr;
    if ((seatfPtr = fopen("seatInfo.dat","rb"))==NULL)
    {
        printf("%s","File could not be opened!\n");
    }
    else
    {
        fread(seatInfoPtr, sizeof(Seat), 1, seatfPtr);
        
        while(!feof(seatfPtr))
        {
            if (flightCode == seatInfoPtr->flightCode)
            {
                int i,j; //i satır j sütun için
                printf("\t0\t1\t2\t3\t4\t5\n");
                    
                for(i=0; i < passengerCapacity/6; i++)
                {   
                    printf("%d\t", i);

                    for(j=0; j < 6; j++)
                    {   
                        seatInfoPtr->seatTable[i][j] = '+';
                        printf("%c\t", seatInfoPtr->seatTable[i][j]);
                    }
                    printf("\n");
                }
            }

            *countPtr +=1;
            fread(seatInfoPtr, sizeof(Seat), 1, seatfPtr);
        }
        fclose(seatfPtr);

        printf("\n%s\n%s\n", "Please choose avaliable seat from above. At seat table '+' means that seat is available and '.' means that seat is not available.",
        "If you want to choose one of available seats, please enter the row number and column number of that seat respectively.");

        printf("%s\n", "Row number you want to choose:");
        scanf("%d", &seatNumber[0]);
        printf("%s\n", "Column number you want to choose:");
        scanf("%d",&seatNumber[1]);

        if(seatInfoPtr->seatTable[seatNumber[0]][seatNumber[1]] == '+')
        {
            seatInfoPtr->seatTable[seatNumber[0]][seatNumber[1]] == '.';
            
            if ((seatfPtr = fopen("seatInfo.dat","wb+"))==NULL)
            {
                printf("%s","File could not be opened!\n");
            }
            else
            {
                fseek(seatfPtr, counter*sizeof(Seat), SEEK_SET);
                fwrite(seatInfoPtr, sizeof(Seat), 1, seatfPtr);
                fclose(seatfPtr);
            }
        }
    }
}


void listPassBooking()
{
    char passName[NAME_LENGTH];    //It is used for receiving the name-surname of passenger
    char passSurName[NAME_LENGTH]; //
    unsigned long long int passId; // It is used for receiving the ID of passenger

    //This section receives the name-surname and ID number of passenger for checking the booking records
    printf("%s\n", "Welcome our list booking service. Please enter your name");
    scanf("%30s", passName);
    printf("%s\n", "Please enter your surname");
    scanf("%30s", passSurName);
    printf("%s\n", "Please enter your ID number");
    scanf("%11llu", &passId);

    /* Commonly used pointers' and variables' name are declared below. This time they are used for receiving booking and flight informations 
    from "Passenger Booking Info.txt" */

    FILE *bookingfPtr; //Commonly used file pointer of "Passenger Booking Info.txt" file

    // If the program fails reading "Passenger Booking Info.txt" for any reason, an error message will be prompted to the screen before returning to the passenger menu
    if ((bookingfPtr = fopen("PassengerBookingInfo.txt", "r+")) == NULL)
    {
        printf("%s", "An error occured!");
        //return passengermenu
    }
    else
    {
        Booking *bInfoPtr, bookingInfo; //This variable and pointer is used for receiving booking informations (except fligt informations) from "Passenger Booking Info.txt" file
        bInfoPtr = &bookingInfo;

        // This fscanf line reads booking informations (except fligt informations) of passenger from the "Passenger Booking Info.txt" file
        fscanf(bookingfPtr, "%s", bInfoPtr->name);
        fscanf(bookingfPtr, "%s", bInfoPtr->surname);
        fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
        fscanf(bookingfPtr, "%d", bInfoPtr->seatNumber);
        fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
        fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
        fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
        fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
        fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
        fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
        fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);

        printf("%s\n\n", "Informations about your booking records as shown below:"); //This header will be prompted before displaying booking records

        int *iPtr, i = 1;
        iPtr = &i;

        /*While statement is used for displaying matched booking records. Statement investigates if there is any match between given 
        passenger name - ID and scanned name - ID from "Passenger Booking Info.txt" file.*/
        while (!feof(bookingfPtr))
        {
            /* If given name-ID are matched with previously scanned name-ID of booking record from "Passenger Booking Info.txt" file, then display 
            the scanned booking record */
            if (((strcmp(strupr(passName), bInfoPtr->name) == 0) && (strcmp(strupr(passSurName), bInfoPtr->surname) == 0)) && (passId == bookingInfo.personalId))
            {
                printf("%s %s %llu %d %d %d %s %s %s %.2f %.2f\n", bInfoPtr->name, bInfoPtr->surname, bInfoPtr->personalId, bInfoPtr->seatNumber,
                       bInfoPtr->bookingId, bInfoPtr->flightCode, bInfoPtr->airlines, bInfoPtr->depAirport, bInfoPtr->destAirport,
                       bInfoPtr->timeOfDep, bInfoPtr->timeOfDest);

                *iPtr += 1;
            }

            /* This section is used for if there is no match between given name-ID and previously scanned name-ID of booking record, then 
            reading another booking record from "Passenger Booking Info.txt" file. After that matching test repeats */
            fscanf(bookingfPtr, "%s", bInfoPtr->name);
            fscanf(bookingfPtr, "%s", bInfoPtr->surname);
            fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
            fscanf(bookingfPtr, "%d", bInfoPtr->seatNumber);
            fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
            fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
            fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
            fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
            fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);
        }
        fclose(bookingfPtr); //After read all booking records and finished the matching tests, this line closes the "Passenger Booking Info.txt" file

        //If there is not any match, a message will be prompted as below
        if (i == 1)
        {
            printf("%s", "You have no current booking available. Would you like to book a flight?");
            //BURAYA BOOKPASSFLİGHT FONKS RETURN YAPILABİLİR
        }
    }
}


void deletePassBooking()
{
    int bookingId; // It is used for receiving the ID of passenger

    //This section receives the name-surname and ID number of passenger for checking the booking records
    printf("%s\n", "Please enter your booking code");
    scanf("%5d", &bookingId);

    /* Commonly used pointers' and variables' name are declared below. This time they are used for receiving booking and flight informations 
    from "Passenger Booking Info.txt" */

    FILE *bookingfPtr;  //Commonly used file pointer of "Passenger Booking Info.txt" file
    FILE *tbookingfPtr; //Commonly used file pointer of "Passenger Booking Info.txt" file

    // If the program fails reading "Passenger Booking Info.txt" for any reason, an error message will be prompted to the screen before returning to the passenger menu
    if ((bookingfPtr = fopen("PassengerBookingInfo.txt", "r")) == NULL)
    {
        printf("%s", "An error occured!");
        //return passengermenu
    }
    else
    { // If the program fails reading "Passenger Booking Info.txt" for any reason, an error message will be prompted to the screen before returning to the passenger menu
        if ((tbookingfPtr = fopen("t_PassengerBookingInfo.txt", "w")) == NULL)
        {
            printf("%s", "An error occured!");
            //return passengermenu
        }
        else
        {
            Booking *bInfoPtr, bookingInfo; //This variable and pointer is used for receiving booking informations (except fligt informations) from "Passenger Booking Info.txt" file
            bInfoPtr = &bookingInfo;

            // This fscanf line reads booking informations (except fligt informations) of passenger from the "Passenger Booking Info.txt" file
            fscanf(bookingfPtr, "%s", bInfoPtr->name);
            fscanf(bookingfPtr, "%s", bInfoPtr->surname);
            fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
            fscanf(bookingfPtr, "%d", bInfoPtr->seatNumber);
            fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
            fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
            fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
            fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
            fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);

            int *iPtr, i = 1;
            iPtr = &i;

            while (!feof(bookingfPtr))
            {
                /* If given name-ID are matched with previously scanned name-ID of booking record from "Passenger Booking Info.txt" file, then display 
            the scanned booking record */
                if (bookingId != bookingInfo.bookingId)
                {
                    fprintf(tbookingfPtr, "%s %s %llu %d %d %d %s %s %s %.2f %.2f\n", bInfoPtr->name, bInfoPtr->surname, bInfoPtr->personalId, 
                    bInfoPtr->seatNumber, bInfoPtr->bookingId, bInfoPtr->flightCode, bInfoPtr->airlines, bInfoPtr->depAirport, 
                    bInfoPtr->destAirport, bInfoPtr->timeOfDep, bInfoPtr->timeOfDest);
                }

                if (bookingId == bookingInfo.bookingId)
                {
                    *iPtr += 1;
                }

                /* This section is used for if there is no match between given name-ID and previously scanned name-ID of booking record, then 
                reading another booking record from "Passenger Booking Info.txt" file. After that matching test repeats */
                fscanf(bookingfPtr, "%s", bInfoPtr->name);
                fscanf(bookingfPtr, "%s", bInfoPtr->surname);
                fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
                fscanf(bookingfPtr, "%d", bInfoPtr->seatNumber);
                fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
                fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
                fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
                fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
                fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
                fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
                fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);
            }
            fclose(bookingfPtr); //After read all booking records and finished the matching tests, this line closes the "Passenger Booking Info.txt" file
            fclose(tbookingfPtr);

            if (i == 1)
            {
                printf("There is no booking to delete according to booking code that you entered!");
                //return mainmenu tarzı bir şey gelecek
            }
            else
            {
                printf("Your booking was successfully cancelled!");
            }
        }
    }
    remove("PassengerBookingInfo.txt");
    rename("t_PassengerBookingInfo.txt", "PassengerBookingInfo.txt");
}

int showPassMenu()
{
    int choice;
    printf("%s\n", "Welcome our passenger service! Please choose one of options below.");
    printf("1. Book a Flight\n");
    printf("2. List my Flights\n");
    printf("3. Cancel my flight\n");
    printf("0. Exit from the program\n");
    printf("\nPlease make your login option: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
        bookPassFlight();
        break;

        case 2:
        listPassBooking();
        break;

        case 3:
        deletePassBooking();
        break;

        case 0:
        printf("\nThe program has successfully closed.\nSEE YOU LATER!\n");
        break;

        default:
        printf("\n%s","!!!!! An error occurred");
        break;
    }
    return 0;
}
