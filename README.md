# Team-Satoshi-s
## Project: Airlines Reservation System
---
An ITU Lesson: [EHB 110E](https://itu.edu.tr "Intr to Sci&Eng Comp (C)") Term Project by **Ulaş Erdoğan** and **Serdar Yaşar**
***
### What is the properties of the program?
Airlines reservation system with a file database.
The application will display an admin and passenger menu options at startup.
The admin menu will be accessible by entering a password. The admin menu will have options to add/edit/delete a flight, list available flights, list current bookings, to change admin password and to return to main menu.
Each flight will have information about airlines, flight code, departure airport and destination airport, time of departure, time of arrival and passenger capacity.
The list bookings option will display passenger names, seat numbers, and flight information as above.
The change password menu will ask for the current password and if it is entered correctly, will ask for the new password twice. If the newly entered passwords match, it will be recorded in the database and the application will exit to the main menu. If the passwords do not match or if the current password is not entered correctly, the application will prompt the user and will return to the main menu.
The passenger menu will have options to book a flight, cancel a booking, list booked flights for the passenger and to return to main menu.
In order to book a flight, the passenger will provide destination airport and departure airport at which point the application will display available flights for that departure and destination points with their flight number, departure and arrival time.
The passenger will select a flight from the list and then will be presented a screen to enter her/his name, id number, and enter seat number from a list of available seat numbers for that particular flight in order. The passenger will enter the required information one by one to finish the booking.
The application will assign a booking id for the booked flight and will display it. The cancel booking menu will ask for a booking id and will delete it if it can find it in the database. If the item cannot be found, the passenger will be prompted with a message.
The list bookings menu will ask for passenger name and id number and will display all the bookings for that particular passenger with their ids and flight information as above.
***
### How can i run it?
The **main.c** file is the source code of the program. You can compile it on your own computer or you can run **main.exe** on Windows computers.
**password.txt** file is the file database to record adminstrator password to reach adminstrator panel. You can use pre-setted password *1773* or delete this file and create this file database at the beginning of the program.
**flights.txt** file is the file database to record flights. You can delete this file and create in the program by adding flights or use the one that we add.
**bookings.txt** file is the file database to record bookings. You can delete this file and create in the program by booking or use the one that we add.
**seatInfo.dat** 