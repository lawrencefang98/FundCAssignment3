#include "dataManipulation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * createClinic
 * Constructor clinic and sets default values to counters
 *
**/
void createClinic(Clinic_t clinic) {

    clinic.userListCount = 0;
    clinic.adminStaffCount = 0;
    clinic.doctorListCount = 0;
    clinic.patientListCount = 0;
}

/**
 * createUser
 * Takes input for user information and store in clinic's user list
 *
 * 
**/
void createUser(Clinic_t clinic) {
    if (clinic.userListCount == MAX_USERS) {
        printf("Maximum amount of users reached\n");
        return;
    }
    User_t newUser;
    
    /*Need to create function for name input*/
    char firstNameInput[MAX_NAME_LENGTH];
    printf("Please enter user's first name:");
    scanf("%20s", firstNameInput);
    strcpy(newUser.firstName, firstNameInput);
    
    char lastNameInput[MAX_NAME_LENGTH];
    printf("Please enter user's last name:");
    scanf("%20s", lastNameInput);
    strcpy(newUser.lastName, lastNameInput);
    
    printf("Please enter user's Birthday:\n");
    newUser.dateOfBirth = getDate();
    
    char emailInput[MAX_EMAIL_LENGTH];
    printf("Please enter user's email:");
    scanf("%50s", emailInput);
    strcpy(newUser.email, emailInput);

    char addressInput[MAX_ADDRESS_LENGTH];
    printf("Please enter user's address:");
    scanf("%255s", addressInput);
    strcpy(newUser.address, addressInput);

    newUser.phoneNo = getPhoneNo();

    printf("Please enter user's gender (M/F):");
    scanf(" %c", &newUser.gender);

    newUser.userID = 1000+clinic.userListCount;
    clinic.userListCount++;
    
    printf("New user creation information");
    userToString(newUser);
}

void deletelastUser(Clinic_t clinic, User_t userToDelete);
User_t searchUser(Clinic_t clinic);
void editUser(Clinic_t clinic, User_t userToEdit, int editOption);

void userToString(User_t userToDisplay) {
    printf("User Information for user ID: %i\n", userToDisplay.userID);
    printf("First Name: %s\n", userToDisplay.firstName);
    printf("Last name: %s\n", userToDisplay.lastName);
    printf("Date of Birth: ");
    printDate(userToDisplay.dateOfBirth);
    printf("Email: %s\n", userToDisplay.email);
    printf("Phone No:%i\n", userToDisplay.phoneNo);
    printf("Address: %s\n", userToDisplay.address);
    printf("Gender: %c\n", userToDisplay.gender);
}


/**
 * getDate()
 * Function takes user input and returns a date
 * Error checking provided
 * @return Date_t date from user input in a valid range
**/

Date_t getDate() {
    Date_t returnedDate;
    while (1) {
        printf("Enter Date: day>");
        scanf("%i", &returnedDate.day);
        if (returnedDate.day < 1 || returnedDate.day > 31) {
            printf("Invalid day. ");
        }
        else {
            break;
        }
    }
    while (1) {
        printf("Enter Date: month>");
        scanf("%i", &returnedDate.month);
        if (returnedDate.month < 1 || returnedDate.month > 12) {
            printf("Invalid month. ");
        }
        else {
            break;
        }
    }
    while (1) {
        printf("Enter Date: year>");
        scanf("%i", &returnedDate.year);
        if (returnedDate.year < 1900 || returnedDate.year > 2021) {
            printf("Invalid year. ");
        }
        else {
            break;
        }
    }
    return returnedDate;
}

/**
 * printDate
 * Function takes a Date and prints it out in string format
 * @param Date_t date to covert to string in format dd/mm/yyyy
**/
void printDate(Date_t date) {
    printf("%i", date.day);
    printf("/");
    printf("%i", date.month);
    printf("/");
    printf("%i", date.year);
    printf("\n");
}

/**
 * getPhone
 * Function gets user input and checks if it is all digits
 * @return user's phone number
 **/
int getPhoneNo() {
    while (1) {
        char input[10];
        int invalidInput = 0;
        printf("Please enter user's phone number:");
        scanf("%s", input);
        int i;
        for (i = 0; i < strlen(input); i++) {
            /* Checks ASCII value to see if character is a number */
            if (input[i] < 48 || input[i] > 57) {
                printf("Please enter digits only!\n");
                invalidInput = 1;
                break;
            }
        }
        if (invalidInput) {
            continue;
        }
        return atoi(input);
    }
}