#include<dataManipulation.h>>
#include<stdio.h>

User_t createUser(Clinic_t clinic) {
    if (userListCount == MAX_USERS) {
        return NULL;
    }
    User_t newUser;
    char firstNameInput[MAX_NAME_LENGTH];
    char lastNameInput[MAX_NAME_LENGTH];
    printf("Please enter user's first name:");
    scanf("%20s", firstNameInput);
    newUser.firstName = firstNameInput;
    printf("Please enter user's last name:");
    scanf("%20s", lastNameInput);
    newUser.lastName = lastNameInput;
    printf("Please enter user's Birthday");s
}

void deleteUser(Clinic_t clinic, User_t userToDelete);
User_t searchUser(Clinic_t clinic;
void editUser(Clinic_t clinic, User_t userToEdit, int editOption);
void userToString(User_t userToDisplay);


/**
 * getDate()
 * Function takes user input and returns a date
 * Error checking provided
 * @return Date_t date from user input in a valid range
**/

Date_t getDate() {
    date_t returnedDate;
    while (TRUE) {
        printf("Enter Date: day>");
        scanf("%i", &returnedDate.day);
        if (returnedDate.day < 1 || returnedDate.day > 31) {
            printf("Invalid day. ");
        }
        else {
            break;
        }
    }
    while (TRUE) {
        printf("Enter Date: month>");
        scanf("%i", &returnedDate.month);
        if (returnedDate.month < 1 || returnedDate.month > 12) {
            printf("Invalid month. ");
        }
        else {
            break;
        }
    }
    while (TRUE) {
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