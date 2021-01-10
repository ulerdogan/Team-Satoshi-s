/*
TEAM SATOSHI'S
Project: Airlines Reservation System
Ulaş Erdoğan - 040190230
Serdar Yaşar - 010190077
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // included this library to take getch() function to keep console window opened at the end of the program
#include <string.h> // included this library to use string functions
#include <time.h>   // included this library to use randomity in srand function

#define AIR_NAME_LENGTH 20 // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
#define PASSWORD_LENGTH 20 // the maximum length of the adminstrator passwords is being controlled by "PASSWORD_LENGTH" macro
#define NAME_LENGTH 30     // the maximum length of the name is being controlled by "NAME_LENGTH" macro
#define SEAT_ROW 50        // the maximum length of the planes seat row numbers

int globalBoolean = 1; // a global variable to control main loop

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
//Function to create seat database of each flight
void seatOrder(int flightCode, int passengerCapacity);
// function that records flights to file database
void addFlight();
// function that lists and prints available flights
int listFlights();
// function that deletes the chosen flight
void deleteFlight();
// function that edits the chosen flight
void editFlight();
// function that list bookings
int listBookings();
//Function that lists available flights to passenger
int listPassFlight();
//Function that generates unique booking ID
int bookingIdGenerator();
//With this function, passenger can select an available seat for him/her. Database of seat records are updated according to passengers' choice
int selectSeat(int flightCode, int passengerCapacity);
//Function that creates booking record for passenger
void bookPassFlight();
//Function that lists booking records of passenger
void listPassBooking();
//Function that deletes booking record of passenger
void deletePassBooking();
//Function that show options menu for passenger
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

//a structure that used for holding seat informations of any particular fligt
typedef struct _Seat
{

    int flightCode;              // between 1111 - 9999
    char seatTable[SEAT_ROW][6]; //seatTable is a matrix array for representing seat order of planes

} Seat;

// a structure of the bookings that passengers recorded
typedef struct _Booking
{
    char name[NAME_LENGTH]; // a string array to keep passengers names
    char surname[NAME_LENGTH];
    unsigned long long int personalId; // a variable to keep the passengers personal ID
    int seatNumber;                    // a variable to keep seat data of booking
    int bookingId;                     // a variable to keep assigned booking ID to passengers
    int flightCode;                    // between 1111 - 9999
    char airlines[AIR_NAME_LENGTH];    // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
    char depAirport[AIR_NAME_LENGTH];  // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
    char destAirport[AIR_NAME_LENGTH]; // the maximum length of the airport and airlines names' strings are being controlled by "AIR_NAME_LENGTH" macro
    float timeOfDep;                   // "HH.MM" format : time of departure
    float timeOfDest;                  // "HH.MM" format : time of destination
    int passengerCapacity;             // passenger capacities of the planes
} Booking;

// main function that computer runs on
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

    int choice; // a variable to keep users choice input

    // printing the menu list
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
                listBookings();
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

// generating flight codes for the flights: this function increment the last flight code by 1
int generateFlightCode()
{
    int firstFlightCode = 1110;

    Flight controlFlight; // a control struct to the file database
    Flight *cfPtr;        // pointer for control flight struct
    cfPtr = &controlFlight;

    FILE *flPtr; // pointer for flights file database

    flPtr = fopen("flights.txt", "r"); // open the file

    // read the first line of the file database
    fscanf(flPtr, "%d", &cfPtr->flightCode);
    fscanf(flPtr, "%s", cfPtr->airlines);
    fscanf(flPtr, "%s", cfPtr->depAirport);
    fscanf(flPtr, "%s", cfPtr->destAirport);
    fscanf(flPtr, "%f", &cfPtr->timeOfDep);
    fscanf(flPtr, "%f", &cfPtr->timeOfDest);
    fscanf(flPtr, "%d", &cfPtr->passengerCapacity);

    // read the file database until the end of the file
    // control the lines and find the last flight code on the database
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

//Function to create seat database of each flight
void seatOrder(int flightCode, int passengerCapacity) //Function gets flight code and passenger capacity of particular flight as parameters
{
    int rowConstant = passengerCapacity / 6; //Variable for expressing the seat row numbers of the plane
    int i, j;                                //Subscript variables of seatTable array
    Seat *seatInfoPtr, seatInfo;             //Struct variable which stores flightcode and seat informations of particular flight in its members
    seatInfoPtr = &seatInfo;                 //Pointer for seatInfo

    seatInfoPtr->flightCode = flightCode;   //Value of flightCode is assigned to seatInfoPtr->flightCode member
    seatInfoPtr->seatTable[rowConstant][6]; //seatInfoPtr->seatTable[][] member holds seat information of plane as a table

    //In for loop elements of seatInfoPtr->seatTable[][] member is initialized to '+'.  '+' symbol means "available seat"
    for (i = 0; i < rowConstant; i++)
    {
        for (j = 0; j <= 5; j++)
        {
            seatInfoPtr->seatTable[i][j] = '+'; //Array elements are initialized to '+' row by row
        }
    }

    FILE *seatfPtr; //File pointer of "seatInfo.dat" binary file. This file stores seatInfo records

    //If file could not be opened for any reason, an error will be prompted to the screen
    if ((seatfPtr = fopen("seatInfo.dat", "ab")) == NULL)
    {
        printf("%s", "File could not be opened!\n");
    }
    else
    {
        //Struct variable seatInfo is written to the "seatInfo.dat" binary file
        fwrite(seatInfoPtr, sizeof(Seat), 1, seatfPtr);
        fclose(seatfPtr); //Closing "seatInfo.dat"
    }
} //End function

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
    printf("\nPlease enter the time of departure (HH.MM): ");
    scanf("%f", &nfPtr->timeOfDep);
    printf("\nPlease enter the time of destination (HH.MM): ");
    scanf("%f", &nfPtr->timeOfDest);
    printf("\nPlease enter the capacity of the plane: ");
    scanf("%d", &nfPtr->passengerCapacity);

    // open the file, handle the inputted information and close (recording all string as uppercase to preventing unmatches about casing)
    flPtr = fopen("flights.txt", "a");
    fprintf(flPtr, "%d %s %s %s %.2f %.2f %d\n", nfPtr->flightCode, strupr(nfPtr->airlines), strupr(nfPtr->depAirport), strupr(nfPtr->destAirport), nfPtr->timeOfDep, nfPtr->timeOfDest, nfPtr->passengerCapacity);
    printf("\n The flight has recorded succesfully...\n");
    fclose(flPtr);

    //
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
        else
        {
            printf("\n The flight has succesfuly removed.");
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
                    printf("\nPlese enter the new time of departure of the flight (HH.MM): ");
                    scanf("%f", &efPtr->timeOfDep);
                    break;
                case 5:
                    printf("\nPlese enter the new time of destination of the flight (HH.MM): ");
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
                fprintf(tflPtr, "%d %s %s %s %.2f %.2f %d\n", efPtr->flightCode, strupr(efPtr->airlines), strupr(efPtr->depAirport), strupr(efPtr->destAirport), efPtr->timeOfDep, efPtr->timeOfDest, efPtr->passengerCapacity);
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

//Function gets airport informations from passenger and compare them with flight records from "flights.txt" file; lists available flights to passenger
int listPassFlight()
{
    design(); //designing

    FILE *fPtr; // File pointer for "flights.txt" database

    //If file could not be opened for any reason, an error will be prompted to the screen
    if ((fPtr = fopen("flights.txt", "r")) == NULL)
    {
        printf("%s", "Our service is temporarily unavailable. Please try again later!");
    }
    else
    {
        char cmpdepAirport[AIR_NAME_LENGTH], cmpdestAirport[AIR_NAME_LENGTH]; //Arrays for getting information about departure and destination airport from passenger
        Flight *fpassPtr, fpassFlight;                                        // For holding dep. and dest. informations are which came from "flights.txt" database
        fpassPtr = &fpassFlight;                                              // Pointer of fpassFlight

        //This section gets departure and destination informations from passenger
        printf("%s", "Please Enter the Name of Departure Airport and Press Enter: ");
        scanf("%s", cmpdepAirport);
        printf("\n%s", "Please Enter the Name of Destination Airport and Press Enter: ");
        scanf("%s", cmpdestAirport);
        printf("%s", "\n");

        //This section gets first flight record from "flights.txt" database
        fscanf(fPtr, "%d", &fpassPtr->flightCode);
        fscanf(fPtr, "%s", fpassPtr->airlines);
        fscanf(fPtr, "%s", fpassPtr->depAirport);
        fscanf(fPtr, "%s", fpassPtr->destAirport);
        fscanf(fPtr, "%f", &fpassPtr->timeOfDep);
        fscanf(fPtr, "%f", &fpassPtr->timeOfDest);
        fscanf(fPtr, "%d", &fpassPtr->passengerCapacity);

        FILE *afPtr; //File pointer of "t_avFlights.txt". This file will hold available flight records temporarily for passenger

        //If file could not be opened for any reason, an error will be prompted to the screen
        if ((afPtr = fopen("t_avFlights.txt", "w")) == NULL)
        {
            printf("\n%s", "!!!!! An error occurred!");
        }
        else
        { //Counter variable. If departure and destination informations are which scanned from "flights.txt" and scanned from passenger are identical, value will be incremented by one
            int *iPtr, i = 1;
            iPtr = &i; //Pointer of counter variable

            //While statement checks if there are matches between airport informations and writes available flight records to "t_avFlights.txt" file.
            while (!feof(fPtr)) //While pointer does not reached to EOF
            {
                //Checking matches
                if ((strcmp(strupr(cmpdepAirport), fpassPtr->depAirport) == 0) && (strcmp(strupr(cmpdestAirport), fpassPtr->destAirport) == 0))
                {
                    //If there is a match, flight record will be written to "t_avFlights.txt" file
                    fprintf(afPtr, "%d %s %s %s %.2f %.2f %d\n", fpassPtr->flightCode, fpassPtr->airlines, fpassPtr->depAirport,
                            fpassPtr->destAirport, fpassPtr->timeOfDep, fpassPtr->timeOfDest, fpassPtr->passengerCapacity);

                    //Available flight record is also printed to the screen for informing
                    printf("%d%c %d %s %s %s %.2f %.2f %d\n", i, ')', fpassPtr->flightCode, fpassPtr->airlines, fpassPtr->depAirport,
                           fpassPtr->destAirport, fpassPtr->timeOfDep, fpassPtr->timeOfDest, fpassPtr->passengerCapacity);

                    *iPtr += 1; //Counter is incremented by 1
                }

                //If there is no match, another flight record is scanned and checking is repeated
                fscanf(fPtr, "%d", &fpassPtr->flightCode);
                fscanf(fPtr, "%s", fpassPtr->airlines);
                fscanf(fPtr, "%s", fpassPtr->depAirport);
                fscanf(fPtr, "%s", fpassPtr->destAirport);
                fscanf(fPtr, "%f", &fpassPtr->timeOfDep);
                fscanf(fPtr, "%f", &fpassPtr->timeOfDest);
                fscanf(fPtr, "%d", &fpassPtr->passengerCapacity);
            }
            fclose(fPtr);  //Closing "flights.txt"
            fclose(afPtr); //Closing "t_avFlights.txt"

            //If there in no any match, an information statement is printed to the screen
            if (i == 1)
            {
                printf("\n%s\n", "No flight found suitable for your preferences!");
                return showPassMenu();
            }
        }
    }
} //End function

//Function creates a booking record after passenger chooses one of available flights
void bookPassFlight()
{
    listPassFlight(); //Listing available flights

    FILE *afPtr; //File pointer of "t_avFlights.txt". This file is holding available flight records temporarily for passenger

    //If file could not be opened for any reason, an error will be prompted to the screen
    if ((afPtr = fopen("t_avFlights.txt", "r")) == NULL)
    {
        printf("\n%s\n", "!!!!! An error occurred!");
    }
    else
    {
        Booking *bInfoPtr, bookingInfo; //This structure will hold informations for creating booking record of passenger
        bInfoPtr = &bookingInfo;        //Pointer of bookingInfo

        //This section gets first flight record from "t_avFlights.txt" file
        fscanf(afPtr, "%d", &bInfoPtr->flightCode);
        fscanf(afPtr, "%s", bInfoPtr->airlines);
        fscanf(afPtr, "%s", bInfoPtr->depAirport);
        fscanf(afPtr, "%s", bInfoPtr->destAirport);
        fscanf(afPtr, "%f", &bInfoPtr->timeOfDep);
        fscanf(afPtr, "%f", &bInfoPtr->timeOfDest);
        fscanf(afPtr, "%d", &bInfoPtr->passengerCapacity);

        int passPref; //Variable for getting flight code of which passenger prefers

        //Getting flight code of which passenger prefers
        printf("\n%s", "Please enter the flight code is which you prefer from above: ");
        scanf("%d", &passPref);

        //While statement checks if there are matches between flight codes and assigns flight informations to members of "bookingInfo" struct
        while (!feof(afPtr)) //While pointer does not reached to EOF
        {
            // ask the user until he/she enters a valid code from the matching list
            while (passPref != bInfoPtr->flightCode)
            {
                printf("\n%s", "You did not choose from the matching list.");
                printf("\n%s", "Please enter the flight code is which you prefer from above: ");
                scanf("%d", &passPref);
            }

            //Checking matches
            if (passPref == bInfoPtr->flightCode)
            {
                //Name of passenger is requested
                printf("\n%s", "Please enter your name: ");
                scanf("%30s", bInfoPtr->name);

                //Surname of passenger is requested
                printf("\n%s", "Please enter your surname: ");
                scanf("%30s", bInfoPtr->surname);

                //Personal ID number of passenger is requested
                printf("\n%s", "Please enter your ID number: ");
                scanf("%11llu", &bInfoPtr->personalId);

                bInfoPtr->seatNumber = selectSeat(bInfoPtr->flightCode, bInfoPtr->passengerCapacity);

                //bookingIdGenerator creates a random bookingId for this particular booking record
                bInfoPtr->bookingId = bookingIdGenerator();

                FILE *bookingfPtr; //File pointer of "bookings.txt". This file will hold booking records of each passenger.
                bookingfPtr = fopen("bookings.txt", "a");

                //Booking record is written to the "bookings.txt" file
                fprintf(bookingfPtr, "%s %s %11llu %d %d %ld %s %s %s %.2f %.2f\n", strupr(bInfoPtr->name), strupr(bInfoPtr->surname),
                        bInfoPtr->personalId, bInfoPtr->seatNumber, bInfoPtr->bookingId, bInfoPtr->flightCode, strupr(bInfoPtr->airlines),
                        strupr(bInfoPtr->depAirport), strupr(bInfoPtr->destAirport), bInfoPtr->timeOfDep, bInfoPtr->timeOfDest);

                fclose(bookingfPtr); //Closing "bookings.txt"
                
                system("cls"); // clear previous screens

                //Sharing booking ID with passenger
                printf("\n%s\t%d\n%s\n", "Thank You for Choosing SATOSHI's AIRPORT! Your Booking Code is:", bInfoPtr->bookingId,
                       "You can cancel your booking by using your booking code!");
            }

            //If there is no match, another flight record is scanned and checking is repeated
            fscanf(afPtr, "%d", &bInfoPtr->flightCode);
            fscanf(afPtr, "%s", bInfoPtr->airlines);
            fscanf(afPtr, "%s", bInfoPtr->depAirport);
            fscanf(afPtr, "%s", bInfoPtr->destAirport);
            fscanf(afPtr, "%f", &bInfoPtr->timeOfDep);
            fscanf(afPtr, "%f", &bInfoPtr->timeOfDest);
            fscanf(afPtr, "%d", &bInfoPtr->passengerCapacity);
        }
        fclose(afPtr);             //Closing "t_avFlights.txt"
        remove("t_avFlights.txt"); //Preferred flight record is assigned to booking struct. So, storing "t_avFlights.txt" file is not necesssary anymore and it is removed
    }
} //End function

//Function generates a unique booking ID while booking process
int bookingIdGenerator()
{
    int generatedId; //Variable for holding unique booking ID

    srand(time(NULL));                    //Seed by time
    generatedId = 10000 + rand() % 89999; //Generating 5 digit random number

    Booking *bInfoPtr, bookingInfo; //This structure is holding booking records of each passenger
    bInfoPtr = &bookingInfo;        //Pointer of bookingInfo
    FILE *bookingfPtr;              //File pointer of "bookings.txt"

    //If file could not be opened for any reason, an error will be prompted to the screen
    if ((bookingfPtr = fopen("bookings.txt", "r")) == NULL)
    {
        printf("\n%s", "!!!!! An error occurred");
    }
    else
    {
        //This section gets first booking record from "bookings.txt" file. Aim is comparing generatedId with bookingId
        fscanf(bookingfPtr, "%s", bInfoPtr->name);
        fscanf(bookingfPtr, "%s", bInfoPtr->surname);
        fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
        fscanf(bookingfPtr, "%d", &bInfoPtr->seatNumber);
        fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
        fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
        fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
        fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
        fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
        fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
        fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);

        while (!feof(bookingfPtr)) //While pointer does not reached to EOF
        {
            //If generatedId is equal to bookingId of scanned booking record, then randomizing process repeats and new Id is created
            if (generatedId == bInfoPtr->bookingId)
            {
                generatedId = 10000 + rand() % 89999;
            }

            //If generatedId is not equal to bookingId of previously scanned booking record, other booking record is scanned and comparing process repeats
            fscanf(bookingfPtr, "%s", bInfoPtr->name);
            fscanf(bookingfPtr, "%s", bInfoPtr->surname);
            fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
            fscanf(bookingfPtr, "%d", &bInfoPtr->seatNumber);
            fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
            fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
            fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
            fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
            fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);
        }
        fclose(bookingfPtr); //Closing "bookings.txt"
    }

    return generatedId; //generatedId is returned as a value of function
} //End function

//With this function, passenger can select an available seat for him/her. Database of seat records are updated according to passengers' choice
int selectSeat(int flightCode, int passengerCapacity)
{
    Seat *seatInfoPtr, seatInfo; //Struct variable which stores flightcode and seat informations of particular flight in its members
    seatInfoPtr = &seatInfo;     //Pointer of seatInfo

    int *countPtr, counter = 0; //Counter variable. It will be used for writing seat preference data to specific location of "seatInfo.dat" database
    countPtr = &counter;        //Pointer of counter
    int rowPref;                //Variable to receive passenger's preferred seat row information
    int columnPref;             //Variable to receive passenger's preferred seat column information

    FILE *seatfPtr; //File pointer for "seatInfo.dat" database

    //If file could not be opened for any reason, an error will be prompted to the screen
    if ((seatfPtr = fopen("seatInfo.dat", "rb+")) == NULL)
    {
        printf("%s", "File could not be opened!\n");
    }
    else
    {
        /*While statement scans the "seatInfo.dat" database to check if there is match between flight codes are which is received from 
        passenger and scanned from "seatInfo.dat" database records. If there is a match, seat selection screen will be displayed*/
        while (!feof(seatfPtr))
        {
            fread(seatInfoPtr, sizeof(Seat), 1, seatfPtr); //Reading first record from "seatInfo.dat" database

            if (flightCode == seatInfoPtr->flightCode)
            {
                break; //If there is a match, then it is not necessary to scan another records anymore
            }
            else
            {
                *countPtr += 1; //If there is not match, counter variable is incremented by one and scanning process is repeated
            }
        }

        //This section is applied according to the flightcode match

        int i, j;                       //Subscript variables for seatInfoPtr->seatTable[][] member
        printf("\t0\t1\t2\t3\t4\t5\n"); //Column headers for seat table

        //Nested for loops prints the seat table
        for (i = 0; i < passengerCapacity / 6; i++)
        {
            printf("%d\t", i); //Row headers for seat table

            for (j = 0; j < 6; j++)
            {
                printf("%c\t", seatInfoPtr->seatTable[i][j]);
            }
            printf("\n");
        }

        fseek(seatfPtr, 0, SEEK_SET); // The position of the file pointer is set to the beginning of the file

        //Printf line informs the passenger about seat selecting process
        printf("\n%s\n%s\n\n", "Please choose avaliable seat from above. At seat table '+' means that seat is available and '.' means that seat is not available.",
               "If you want to choose one of available seats, please enter the row number and column number of that seat respectively.");

        printf("%s", "Row number you want to choose: ");
        scanf("%d", &rowPref); //Getting seat row preference from passenger
        printf("%s", "Column number you want to choose: ");
        scanf("%d", &columnPref); //Getting seat column preference from passenger

        //If passenger selects not available seat, he/she is forced to select another available seat
        while (seatInfoPtr->seatTable[rowPref][columnPref] == '.' || rowPref < 0 || rowPref >= passengerCapacity / 6 || columnPref < 0 || columnPref > 5)
        {
            printf("\n%s\n", "You entered the number of not available seat. Please choose seats that have '+' mark!");
            printf("%s", "Row number you want to choose: ");
            scanf("%d", &rowPref);
            printf("\n%s", "Column number you want to choose: ");
            scanf("%d", &columnPref);
        }

        //If passenger selects available seat, that seat is stamped as not free
        if (seatInfoPtr->seatTable[rowPref][columnPref] == '+')
        {
            seatInfoPtr->seatTable[rowPref][columnPref] = '.';
        }

        //Changed seat table is overwritten to "seatInfo.dat" database in its location for updating the database
        fseek(seatfPtr, counter * sizeof(Seat), SEEK_SET);
        fwrite(seatInfoPtr, sizeof(Seat), 1, seatfPtr);
        fclose(seatfPtr); //Closing "seatInfo.dat"
    }
    return 10 * rowPref + columnPref; //Seat number information is returned for saving it in "booking.txt" file
}

//Function to list all bookings of a passenger
void listPassBooking()
{
    char passName[NAME_LENGTH];    //Variable for getting name of passenger
    char passSurName[NAME_LENGTH]; //Variable for getting surname of passenger
    unsigned long long int passId; //Variable for getting personal ID of passenger

    //This section receives the name-surname and ID number of passenger for checking the booking records
    design();
    printf("%s", "Welcome to our list booking service.\n\nPlease enter your name: ");
    scanf("%30s", passName);
    printf("\n%s", "Please enter your surname: ");
    scanf("%30s", passSurName);
    printf("\n%s", "Please enter your ID number: ");
    scanf("%11llu", &passId);

    FILE *bookingfPtr; //File pointer of "bookings.txt"

    //If file could not be opened for any reason, an error will be prompted to the screen
    if ((bookingfPtr = fopen("bookings.txt", "r+")) == NULL)
    {
        printf("\n%s", "!!!!! An error occurred");
    }
    else
    {
        Booking *bInfoPtr, bookingInfo; //This structure will hold booking records are which came from "Passenger Booking Info.txt" file
        bInfoPtr = &bookingInfo;        //Pointer of bookingInfo

        //This section gets first booking record from "bookings.txt" file
        fscanf(bookingfPtr, "%s", bInfoPtr->name);
        fscanf(bookingfPtr, "%s", bInfoPtr->surname);
        fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
        fscanf(bookingfPtr, "%d", &bInfoPtr->seatNumber);
        fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
        fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
        fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
        fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
        fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
        fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
        fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);

        printf("\n%s\n\n", "Informations about your booking records as shown below:"); //This header will be prompted before displaying booking records

        //Counter variable. If name-surname and personal ID informations are which scanned from "bookings.txt" and scanned from passenger are identical, value will be incremented by one
        int *iPtr, i = 1;
        iPtr = &i; //Pointer of counter

        //While statement checks if there are matches between given (from passenger) name-surname-personalId and scanned name-surname-personalId from "bookings.txt"
        while (!feof(bookingfPtr)) //While pointer does not reached to EOF
        {
            //Checking name-surname and personal ID informations are which scanned from "bookings.txt" and scanned from passenger are identical
            if (((strcmp(strupr(passName), bInfoPtr->name) == 0) && (strcmp(strupr(passSurName), bInfoPtr->surname) == 0)) && (passId == bookingInfo.personalId))
            {
                //If there is match, booking record is displayed
                printf("%s %s %llu %d %d %d %s %s %s %.2f %.2f\n", bInfoPtr->name, bInfoPtr->surname, bInfoPtr->personalId, bInfoPtr->seatNumber,
                       bInfoPtr->bookingId, bInfoPtr->flightCode, bInfoPtr->airlines, bInfoPtr->depAirport, bInfoPtr->destAirport,
                       bInfoPtr->timeOfDep, bInfoPtr->timeOfDest);

                *iPtr += 1; //Counter is incremented by 1
            }

            //If there is no match, another booking record is scanned and checking is repeated
            fscanf(bookingfPtr, "%s", bInfoPtr->name);
            fscanf(bookingfPtr, "%s", bInfoPtr->surname);
            fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
            fscanf(bookingfPtr, "%d", &bInfoPtr->seatNumber);
            fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
            fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
            fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
            fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
            fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);
        }
        fclose(bookingfPtr); //Closing "bookings.txt"

        //If there is not any match, a message will be prompted as below
        if (i == 1)
        {
            printf("%s\n", "You have no current booking available.");
        }
    }
} //End function

//Function to cancel particular booking by using the booking ID
void deletePassBooking()
{
    int bookingId; //Variable for getting the unique booking ID from passenger

    //This section receives the booking ID from passenger for checking the booking records
    printf("\n%s", "Please enter your booking code: ");
    scanf("%5d", &bookingId);

    FILE *bookingfPtr;  //File pointer of "bookings.txt"
    FILE *tbookingfPtr; //File pointer of "t_bookings.txt"

    //If "bookings.txt" file could not be opened for any reason, an error message will be prompted to the screen
    if ((bookingfPtr = fopen("bookings.txt", "r")) == NULL)
    {
        printf("\n%s", "!!!!! An error occurred");
    }
    else
    { //If "t_bookings.txt" file could not be opened for any reason, an error message will be prompted to the screen
        if ((tbookingfPtr = fopen("t_bookings.txt", "w")) == NULL)
        {
            printf("\n%s", "!!!!! An error occurred");
        }
        else
        {
            Booking *bInfoPtr, bookingInfo; //This structure will hold booking records are which came from "Passenger Booking Info.txt" file
            bInfoPtr = &bookingInfo;        //Pointer of bookingInfo

            //This section gets first booking record from "bookings.txt" file
            fscanf(bookingfPtr, "%s", bInfoPtr->name);
            fscanf(bookingfPtr, "%s", bInfoPtr->surname);
            fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
            fscanf(bookingfPtr, "%d", &bInfoPtr->seatNumber);
            fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
            fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
            fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
            fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
            fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
            fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);

            int *iPtr, i = 1; //Counter variable. If the booking IDs are which scanned from "bookings.txt" and scanned from passenger are identical, value will be incremented by one
            iPtr = &i;        //Pointer of counter

            //While statement checks if there are matches between given (from passenger) booking ID and scanned booking ID from "bookings.txt"
            while (!feof(bookingfPtr))
            {
                /* If given booking ID is NOT matched with previously scanned booking ID from "Passenger Booking Info.txt" file, the scanned 
                booking record will be written to "t_bookings.txt" file --> The new database*/
                if (bookingId != bookingInfo.bookingId)
                {
                    fprintf(tbookingfPtr, "%s %s %llu %d %d %d %s %s %s %.2f %.2f\n", bInfoPtr->name, bInfoPtr->surname, bInfoPtr->personalId,
                            bInfoPtr->seatNumber, bInfoPtr->bookingId, bInfoPtr->flightCode, bInfoPtr->airlines, bInfoPtr->depAirport,
                            bInfoPtr->destAirport, bInfoPtr->timeOfDep, bInfoPtr->timeOfDest);
                }

                if (bookingId == bookingInfo.bookingId)
                {
                    *iPtr += 1; //Counter is incremented by 1
                }

                //If there is no match, another booking record is scanned and checking is repeated
                fscanf(bookingfPtr, "%s", bInfoPtr->name);
                fscanf(bookingfPtr, "%s", bInfoPtr->surname);
                fscanf(bookingfPtr, "%llu", &bInfoPtr->personalId);
                fscanf(bookingfPtr, "%d", &bInfoPtr->seatNumber);
                fscanf(bookingfPtr, "%d", &bInfoPtr->bookingId);
                fscanf(bookingfPtr, "%d", &bInfoPtr->flightCode);
                fscanf(bookingfPtr, "%s", bInfoPtr->airlines);
                fscanf(bookingfPtr, "%s", bInfoPtr->depAirport);
                fscanf(bookingfPtr, "%s", bInfoPtr->destAirport);
                fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDep);
                fscanf(bookingfPtr, "%f", &bInfoPtr->timeOfDest);
            }
            fclose(bookingfPtr);  //Closing "bookings.txt"
            fclose(tbookingfPtr); //Closing "t_bookings.txt"

            // i==1 means that there is not any match between given booking ID and other booking IDs are which came from "bookings.txt"
            if (i == 1)
            {
                //There is not any match, it means that there is not an available booking record to delete
                printf("\nThere is no booking to delete according to booking code that you entered!\n");
            }
            else
            {
                //If i != 1, it means that there is an available booking record to delete and this record was deleted
                printf("\nYour booking was successfully cancelled!\n");
            }
        }
    }
    remove("bookings.txt");                   //Removing old databese. This database has the deleted booking record
    rename("t_bookings.txt", "bookings.txt"); //Renaming new database as "bookings.txt" New database has all booking records except the deleted one
} //End function

//Function to create passenger menu
int showPassMenu()
{
    int choice; //Variable for receiving the passengers' choice

    //This section shows options for passengers
    design();
    printf("%s\n\n", "Welcome to our passenger service! Please choose one of options below.");
    printf("1. Book a Flight\n");
    printf("2. List my Flights\n");
    printf("3. Cancel my flight\n");
    printf("0. Return main menu \n");
    printf("\nPlease make your login option: ");
    scanf("%d", &choice); // Getting passenger's choice

    //According to the choice, one of functions from below is activated
    switch (choice)
    {
    case 1: //If passenger wants to book a flight, this case is applied
        bookPassFlight();
        break;

    case 2: //If passenger wants to list his/her bookings, this case is applied
        listPassBooking();
        break;

    case 3: //If passenger wants to cancel his/her booking, this case is applied
        deletePassBooking();
        break;

    case 0: //If passenger wants to return to the main menu, this case is applied
        showMainMenu();
        break;

    default: //Default option for false inputs
        printf("\n%s", "!!!!! An error occurred");
        break;
    }
    return 0;
} //End function

// a function to list current bookings
int listBookings()
{
    design(); // designing

    FILE *flPtr; // pointer for flights file database

    FILE *tflPtr;                        // pointer for temporary flight database handler
    tflPtr = fopen("bookings.txt", "r"); // opening file to check does it exist

    // create file database if does not exist to prevent errors
    if (tflPtr == NULL)
    {
        flPtr = fopen("bookings.txt", "w");
        fclose(flPtr);
    }
    fclose(tflPtr); // closing the file that we opened to check

    flPtr = fopen("bookings.txt", "r"); // opening file database to read lines

    Booking readBooking; // struct for placing the flight informations that have read
    Booking *rbPtr;      // pointer to manage struct
    rbPtr = &readBooking;

    int counter = 1;

    // reading the first records on the data
    fscanf(flPtr, "%s", rbPtr->name);
    fscanf(flPtr, "%s", rbPtr->surname);
    fscanf(flPtr, "%ull", &rbPtr->personalId);
    fscanf(flPtr, "%d", &rbPtr->seatNumber);
    fscanf(flPtr, "%d", &rbPtr->bookingId);
    fscanf(flPtr, "%d", &rbPtr->flightCode);
    fscanf(flPtr, "%s", rbPtr->airlines);
    fscanf(flPtr, "%s", rbPtr->depAirport);
    fscanf(flPtr, "%s", rbPtr->destAirport);
    fscanf(flPtr, "%f", &rbPtr->timeOfDep);
    fscanf(flPtr, "%f", &rbPtr->timeOfDest);

    // keep reading data from the file while not end of the file then print them
    while (!feof(flPtr))
    {
        printf("%2d- %s %s %ull %d %d %d %s %s %s %.2f %.2f\n", counter, rbPtr->name, rbPtr->surname, rbPtr->personalId, rbPtr->seatNumber, rbPtr->bookingId, rbPtr->flightCode, rbPtr->airlines, rbPtr->depAirport, rbPtr->destAirport, rbPtr->timeOfDep, rbPtr->timeOfDest);
        fscanf(flPtr, "%s", rbPtr->name);
        fscanf(flPtr, "%s", rbPtr->surname);
        fscanf(flPtr, "%ull", &rbPtr->personalId);
        fscanf(flPtr, "%d", &rbPtr->seatNumber);
        fscanf(flPtr, "%d", &rbPtr->bookingId);
        fscanf(flPtr, "%d", &rbPtr->flightCode);
        fscanf(flPtr, "%s", rbPtr->airlines);
        fscanf(flPtr, "%s", rbPtr->depAirport);
        fscanf(flPtr, "%s", rbPtr->destAirport);
        fscanf(flPtr, "%f", &rbPtr->timeOfDep);
        fscanf(flPtr, "%f", &rbPtr->timeOfDest);
        counter++; //increment counter
    }

    fclose(flPtr); // close the file

    if (counter == 1)
    {
        printf("There are not any booking records!");

        // show that there are any records
        return 0;
    }
    else
    {
        //show that there are records
        return 1;
    }
} //End function
