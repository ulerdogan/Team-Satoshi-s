#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// the function prototypes

//check if adminstrator of the system signed up
int isAdminSignedUp(); 

int main() {

    // the loop that keeps the program running
    while (1) {

        // keep the program going by admin signing up menu or by the main menu according to sign up status
        if (isAdminSignedUp == 0) {

        } else {

        }




    }

    // end of the program statement and provide that the program doesn't end without user permission
    getch();
    return 0;
}

// a function that checks if adminstrator of the system signed up
int isAdminSignedUp() {
    // check the file database and find a adminstrator password
    ;
    if() {
        // if there are a password, return 1 and express that there is an admin
        return 1;
    } else {
        // if there are not a password, return 0 and express that admin must be signed up
        return 0;
    }

    }
