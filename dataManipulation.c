#include "dataManipulation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



/**
 * createUser
 * Takes input for user information and store in clinic's user list
 *@param Clinic_t clinic: pointer to clinic
 * 
**/
void createUser(Clinic_t *clinic) {
    if (clinic->userListCount == MAX_USERS) {
        printf("Maximum amount of users reached\n");
        return;
    }
    
    User_t *newUserPtr = &clinic->userList[clinic->userListCount];

    char firstNameInput[MAX_NAME_LENGTH];
    printf("Please enter user's first name:");
    scanf("%20s", firstNameInput);
    strcpy(newUserPtr->firstName, firstNameInput);
    
    char lastNameInput[MAX_NAME_LENGTH];
    printf("Please enter user's last name:");
    scanf("%20s", lastNameInput);
    strcpy(newUserPtr->lastName, lastNameInput);
    
    printf("Please enter user's Birthday:\n");
    newUserPtr->dateOfBirth = getDate();
    
    char emailInput[MAX_EMAIL_LENGTH];
    printf("Please enter user's email:");
    scanf("%50s", emailInput);
    strcpy(newUserPtr->email, emailInput);

    char addressInput[MAX_ADDRESS_LENGTH];
    printf("Please enter user's address:");
    scanf(" %[^\n]%*c", addressInput);
    strcpy(newUserPtr->address, addressInput);

    newUserPtr->phoneNo = getPhoneNo();

    printf("Please enter user's gender (M/F):");
    scanf(" %c", &newUserPtr->gender);

    newUserPtr->userID = 1000 + clinic->userListCount;
    
    clinic->userListCount += 1;
    
    printf("\n");
    printf("New user creation information\n\n");
    userToString(clinic->userList[clinic->userListCount - 1]);
    printf("\n");
}

/**
 * deleteUser
 * Takes input for user information and deletes user from clinic
 *@param Clinic_t clinic: pointer to clinic
 * 
**/
void deleteUser(Clinic_t clinic) {

}
/**
 * searchUser
 * Takes input for user information and looks for a user if it exists and displays user info
 *@param Clinic_t clinic: pointer to clinic
 * 
**/
void searchUser(Clinic_t *clinic) {
    User_t searchedUser = getUser(clinic);
    
    if (searchedUser.userID == 0) {
        printf("No user found!\n");
    }
    else {
        printf("\n");
        printf("User found! Displaying user information.\n\n");
        userToString(searchedUser);
    }
}

/**
 * editUser
 * Takes input and looks for user if it exists, prompts user for which option to edit. Prompts to see if user wants to continue editing the same user
 *@param Clinic_t clinic: pointer to clinic
 * 
**/
void editUser(Clinic_t *clinic) {
    User_t searchedUser = getUser(clinic);
    if (searchedUser.userID == 0) {
        printf("No user found!\n");
        return;
    }
    int userListArrayIndex = searchedUser.userID - 1000;
    while (TRUE) {    
        printf("1. First Name\n");
        printf("2. Last Name\n");
        printf("3. Date of Birth\n");
        printf("4. Email\n");
        printf("5. Phone No\n");
        printf("6. Address\n");
        printf("7. Gender\n");
        printf("Please select which option you wish to change:");
        char editChoice;
        scanf(" %c", &editChoice);
        int invalidChoice = 0;
        switch (editChoice)
        {
            case '1':
                char firstNameInput[MAX_NAME_LENGTH];
                printf("Please enter user's first name:");
                scanf("%20s", firstNameInput);
                strcpy(clinic->userList[userListArrayIndex].firstName, firstNameInput);
                break;
            case '2':
                char lastNameInput[MAX_NAME_LENGTH];
                printf("Please enter user's last name:");
                scanf("%20s", lastNameInput);
                strcpy(clinic->userList[userListArrayIndex].lastName, lastNameInput);
                break;
            case '3':
                printf("Please enter user's Birthday:\n");
                clinic->userList[userListArrayIndex].dateOfBirth = getDate();
                break;
            case '4':
                char emailInput[MAX_EMAIL_LENGTH];
                printf("Please enter user's email:");
                scanf("%50s", emailInput);
                strcpy(clinic->userList[userListArrayIndex].email, emailInput);
                break;
            case '5':
                clinic->userList[userListArrayIndex].phoneNo = getPhoneNo();
                break;
            case '6':
                char addressInput[MAX_ADDRESS_LENGTH];
                printf("Please enter user's address:");
                scanf(" %[^\n]%*c", addressInput);
                strcpy(clinic->userList[userListArrayIndex].address, addressInput);
            default:
                printf("Invalid option selected\n");
                invalidChoice = 1;
                break;    
        }
        if (invalidChoice) {
            continue;
        }
        char continueChoice;
        printf("Would you like to continue editing this user? (Y/N)");
        scanf(" %c", &continueChoice);
        if (toupper(continueChoice) == 'N') {
            break;
        }
    }
}

/**
 * userToString
 * Prints out user information 
 *@param User_t usertoDisplay
 * 
**/
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
 * Checks that dates are valid (1<DD<31, 1<MM<12, 1900<YYYY<2021)
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

/**
 * getUser
 * Function gets user input and checks if there is an associated user
 * @return user_t user, returns blank user if not found
 **/
User_t getUser(Clinic_t *clinic) {
    printf("Please enter user's ID:");
        int idInput;
        scanf("%i", &idInput);
        int i;
        for (i=0; i<clinic->userListCount; i++) {
            if (clinic->userList[i].userID == idInput) {
                return clinic->userList[i];
            }
        }
    Date_t emptyDate = {0,0,0};    
    User_t noUser = {0,"","", emptyDate, "", 0,"",'0'};
    return noUser;    
}

void createDoctor(Clinic_t *clinic) {
    if (clinic->doctorListCount == MAX_DOCTORS) {
        printf("Maximum amount of doctors reached\n");
        return;
    }

    else if (clinic->userListCount == 0) {
        printf("No users in system\n");
        return;
    }
    
    while (TRUE) {
        printf("User ID to tie doctor information is required\n");
        User_t doctorUser = getUser(clinic);
        if (doctorUser.userID == 0) {
            printf("Invalid user. Please try again\n\n");
            continue;
        }
        Doctor_t *newDoctorPtr = &clinic->doctorList[clinic->doctorListCount];
        newDoctorPtr->userId = doctorUser.userID;
        newDoctorPtr->doctorId = 2000 + clinic->doctorListCount;
        printf("Please enter doctor's start date:\n");
        newDoctorPtr->startDate = getDate();
        
        clinic->doctorListCount += 1;
        
        printf("\n");
        printf("New doctor creation information\n\n");
        doctorToString(clinic->doctorList[clinic->doctorListCount - 1]);
        printf("\n");
        break;
    }
}
void deleteDoctor(Clinic_t *clinic);

void createAdminStaff(Clinic_t *clinic) {
    if (clinic->adminStaffCount == MAX_ADMIN_STAFF) {
        printf("Maximum amount of admin staff reached\n");
        return;
    }

    else if (clinic->userListCount == 0) {
        printf("No users in system\n");
        return;
    }
    
    while (TRUE) {
        printf("User ID to tie admin staff information is required\n");
        User_t adminUser = getUser(clinic);
        if (adminUser.userID == 0) {
            printf("Invalid user. Please try again\n\n");
            continue;
        }
        AdminStaff_t *newAdminStaffPtr = &clinic->adminStaffList[clinic->adminStaffCount];
        newAdminStaffPtr->userId = adminUser.userID;
        newAdminStaffPtr->staffId = 3000 + clinic->adminStaffCount;
        printf("Please enter admin staff's job title:");
        char jobTitleInput[MAX_JOB_TITLE_LENGTH];
        scanf(" %[^\n]%*c", jobTitleInput);
        strcpy(newAdminStaffPtr->jobTitle, jobTitleInput);
        printf("Please enter admin staff's start date:\n");
        newAdminStaffPtr->startDate = getDate();
        
        clinic->adminStaffCount += 1;
        
        printf("\n");
        printf("New admin staff creation information\n\n");
        adminStaffToString(clinic->adminStaffList[clinic->adminStaffCount - 1]);
        printf("\n");
        break;
    }
}

void deleteAdminStaff(Clinic_t *clinic);

void editAdminStaffTitle(Clinic_t *clinic) {
    while (TRUE) {
        AdminStaff_t adminStaff = getAdminStaff(clinic);
        if (adminStaff.userId == 0) {
            printf("Invalid staff ID");
            continue;       
        }
    AdminStaff_t *newAdminStaffPtr = &clinic->adminStaffList[clinic->adminStaffCount];
}

void doctorToString(Doctor_t doctorToDisplay) {
    printf("Doctor Information for userID: %i\n", doctorToDisplay.userId);
    printf("Doctor ID: %i\n", doctorToDisplay.doctorId);
    printf("Start date:");
    printDate(doctorToDisplay.startDate);
    printf("\n");
}

void adminStaffToString(AdminStaff_t adminStaffToDisplay) {
    printf("Admin Staff Information for userID: %i\n",adminStaffToDisplay.userId);
    printf("Staff ID: %i\n", adminStaffToDisplay.staffId);
    printf("Job Title: %s\n", adminStaffToDisplay.jobTitle);
    printf("Start date:");
    printDate(adminStaffToDisplay.startDate);
    printf("\n");
}

AdminStaff_t getAdminStaff(Clinic_t *clinic) {
    printf("Please enter admin staff ID:");
        int idInput;
        scanf("%i", &idInput);
        int i;
        for (i=0; i<clinic->adminStaffCount; i++) {
            if (clinic->adminStaffList[i].staffId == idInput) {
                return clinic->adminStaffList[i];
            }
        }
    Date_t emptyDate = {0,0,0};    
    AdminStaff_t noUser = {0, 0,"", emptyDate};
    return noUser;    
}


/**
 * createPatient
 * Function gets user input and checks if there is an associated user
 * @return user_t user
 **/
void createPatient(Clinic_t *clinic) {
    if (clinic->patientListCount == MAX_PATIENTS) {
        printf("Maximum amount of patients reached\n");
        return;
    }
    else if (clinic->userListCount == 0) {
        printf("No users in system\n");  
        return;
    }
    
    PatientInfo_t *newPatientPtr = &clinic->patientList[clinic->patientListCount];
    while (TRUE) {
        printf("User ID to tie patient information is required\n");
        User_t patientUser = getUser(clinic);
        if (patientUser.userID == 0) {
            printf("Invalid user. Please try again\n\n");
            continue;
        }
        else {
            while (TRUE) {
                printf("Possible patient's blood type\n");
                printf("1. AB+\n");
                printf("2. AB-\n");
                printf("3. A+\n");
                printf("4. A-\n");
                printf("5. B+\n");
                printf("6. B-\n");
                printf("7. O+\n");
                printf("8. O-\n");
                char bloodChoice;
                int invalidChoice = 0;
                printf("Select an option:");
                scanf(" %c", &bloodChoice);
                switch (bloodChoice) {
                    case '1':
                        strcpy(newPatientPtr->bloodType, "AB+");
                        break;
                    case '2':
                        strcpy(newPatientPtr->bloodType, "AB-");
                        break;
                    case '3':
                        strcpy(newPatientPtr->bloodType, "A+");
                        break;
                    case '4':
                        strcpy(newPatientPtr->bloodType, "A-");
                        break;
                    case '5':
                        strcpy(newPatientPtr->bloodType, "B+");
                        break;
                    case '6':
                        strcpy(newPatientPtr->bloodType, "B-");
                        break;
                    case '7':
                        strcpy(newPatientPtr->bloodType, "O+");
                        break;
                    case '8':
                        strcpy(newPatientPtr->bloodType, "O-");
                        break;
                    default:
                        printf("Invalid option selected, please try again\n");
                        invalidChoice = 1;
                        break;
                }
                if (invalidChoice) {
                    continue;
                }
                break; 
            }

            printf("Assign primary doctor to patient\n");
            
            printf("Enter doctor's ID:");

        }
        break;
    }
}

void deletePatient(Clinic_t *clinic);
PatientInfo_t searchPatient(Clinic_t *clinic);
void editPatientInfo(Clinic_t *clinic);