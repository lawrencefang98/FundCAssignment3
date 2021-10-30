#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
     * Author: Lawrence Fang
     * Header file for data manipulation
    **/

/* PREPROCESSING DIRECTIVES */
#define MAX_USERS 100
#define MAX_PATIENTS 75
#define MAX_DOCTORS 10
#define MAX_ADMIN_STAFF 15
#define MAX_NAME_LENGTH 20
#define MAX_EMAIL_LENGTH 50
#define MAX_ADDRESS_LENGTH 255
#define MAX_RECORD_DESCRIPTION_LENGTH 2000
#define MAX_PHONENO_LENGTH 10
#define MAX_JOB_TITLE_LENGTH 50
#define TRUE 1
#define FALSE 0

/* STRUCTURE DEFINITIONS */

/**
     * Author: Lawrence Fang
     * Stores date in a dd/mm/yyyy format.
    **/
struct Date
{
    int day;
    int month;
    int year;
};
typedef struct Date Date_t;

/**
     * Author: Lawrence Fang
     * Stores personal information about every user in the system
    **/
struct User
{
    int userID;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    Date_t dateOfBirth;
    char email[MAX_EMAIL_LENGTH];
    int phoneNo;
    char address[MAX_ADDRESS_LENGTH];
    char gender;
};
typedef struct User User_t;

/**
     * Author: Lawrence Fang
     * Stores information related to a doctor's information
    **/
struct Doctor
{
    int userId;
    int doctorId;
    Date_t startDate;
};
typedef struct Doctor Doctor_t;

/**
     * Author: Lawrence Fang
     * Medical record information represented in linked list structure
     * Linked list structure chosen due to unknown size of medical records for each user
    **/
struct MedicalRecord
{
    Date_t dateOfEntry;
    char description[MAX_RECORD_DESCRIPTION_LENGTH];
};
typedef struct MedicalRecord MedicalRecord_t;

/**
     * Author: Lawrence Fang
     * Stores information related to a patient's medical information
    **/
struct PatientInfo
{
    int userID;
    char bloodType[3];
    int primaryDoctorID;
};
typedef struct PatientInfo PatientInfo_t;

/**
     * Author: Lawrence Fang
     * Stores information related to administrative staff
    **/
struct AdminStaff
{
    int userId;
    int staffId;
    char jobTitle[MAX_JOB_TITLE_LENGTH];
    Date_t startDate;
};
typedef struct AdminStaff AdminStaff_t;

/**
     * Author: Lawrence Fang
     * Stores entire clinic informatio
    **/

struct Clinic
{
    User_t userList[MAX_USERS];
    PatientInfo_t patientList[MAX_PATIENTS];
    Doctor_t doctorList[MAX_DOCTORS];
    AdminStaff_t adminStaffList[MAX_ADMIN_STAFF];
    int patientListCount;
    int doctorListCount;
    int adminStaffCount;
    int userListCount;
};
typedef struct Clinic Clinic_t;
/*Constructor for Clinic*/
void createClinic(Clinic_t *clinic);

/* FUNCTION DEFINITIONS */

/*User Related Functions*/
void createUser(Clinic_t *clinic);
void deleteLastUser(Clinic_t *clinic);
void searchUser(Clinic_t *clinic);
void editUser(Clinic_t *clinic);
void userToString(User_t userToDisplay);
User_t getUser(Clinic_t *clinic);
void displayUserList(Clinic_t *clinic);
int getPhoneNo();

/*Staff Related Functions*/
void createDoctor(Clinic_t *clinic);
void createAdminStaff(Clinic_t *clinic);
void editAdminStaffTitle(Clinic_t *clinic);
AdminStaff_t getAdminStaff(Clinic_t *clinic);
void doctorToString(Doctor_t doctorToDisplay);
void adminStaffToString(AdminStaff_t adminStaffToDisplay);
void displayDoctorList(Clinic_t *clinic);
void displayAdminStaffList(Clinic_t *clinic);

/*Patient Related Functions*/
void createPatient(Clinic_t *clinic);
void patientInfoToString(PatientInfo_t patientInfoToDisplay);
void displayPatientList(Clinic_t *clinic);
void searchPatient(Clinic_t *clinic);
PatientInfo_t getPatient(Clinic_t *clinic);

/*Date Functions*/
Date_t getDate();
void printDate(Date_t date);

/*********************************************************************************/

/**
 * createClinic
 * Constructor for creating clinic structure
 *@param Clinic_t clinic: pointer to clinic
**/
void createClinic(Clinic_t *clinic)
{
    clinic->userListCount = 0;
    clinic->adminStaffCount = 0;
    clinic->doctorListCount = 0;
    clinic->patientListCount = 0;
}

/**
 * createUser
 * Takes input for user information and store in clinic's user list
 *@param Clinic_t clinic: pointer to clinic
 * 
**/
void createUser(Clinic_t *clinic)
{
    if (clinic->userListCount == MAX_USERS)
    {
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

    while (TRUE)
    {
        printf("Please select user's gender\n");
        printf("1. Male\n");
        printf("2. Female\n");
        printf("Select 1 or 2:");
        char genderSelection;
        scanf(" %c", &genderSelection);
        int invalidOption = 0;
        switch (genderSelection)
        {
        case '1':
            newUserPtr->gender = 'M';
            break;
        case '2':
            newUserPtr->gender = 'F';
            break;
        default:
            invalidOption = 1;
            printf("Invalid option. Try again!\n");
            break;
        }
        if (invalidOption)
        {
            continue;
        }
        break;
    }

    newUserPtr->userID = 1000 + clinic->userListCount;

    clinic->userListCount += 1;

    printf("\n");
    printf("New user creation information\n\n");
    userToString(clinic->userList[clinic->userListCount - 1]);
    printf("\n");
}

/**
 * deleteLastUser
 * Prints out information of user to be deleted and asks for confirmation
 *@param Clinic_t clinic: pointer to clinic
 * 
**/
void deleteLastUser(Clinic_t *clinic)
{
    if (clinic->userListCount == 0)
    {
        printf("No users in system\n");
        return;
    }
    printf("User to be deleted");
    userToString(clinic->userList[clinic->userListCount - 1]);
    char deleteChoice;
    printf("Do you wish to delete this user? (Y/N)");
    scanf(" %c", &deleteChoice);
    if (deleteChoice == 'y' || deleteChoice == 'Y')
    {
        clinic->userListCount -= 1;
        printf("User deleted.\n");
    }
    else
    {
        printf("User not deleted.\n");
    }
}

/**
 * searchUser
 * Asks for user information and looks for a user if it exists and displays user info
 *@param Clinic_t clinic: pointer to clinic
 * 
**/
void searchUser(Clinic_t *clinic)
{
    User_t searchedUser = getUser(clinic);

    if (searchedUser.userID == 0)
    {
        printf("No user found!\n");
    }
    else
    {
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
void editUser(Clinic_t *clinic)
{
    User_t searchedUser = getUser(clinic);
    if (searchedUser.userID == 0)
    {
        printf("No user found!\n");
        return;
    }
    int userListArrayIndex = searchedUser.userID - 1000;
    while (TRUE)
    {
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
        if (invalidChoice)
        {
            continue;
        }
        char continueChoice;
        printf("Would you like to continue editing this user? (Y/N)");
        scanf(" %c", &continueChoice);
        if (continueChoice == 'N' || continueChoice == 'n')
        {
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
void userToString(User_t userToDisplay)
{
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
 * getUser
 * Function gets user input and checks if there is an associated user
 * @param Clinic_t clinic: pointer to clinic
 * @return user_t user, returns blank user if not found
 **/
User_t getUser(Clinic_t *clinic)
{
    printf("Please enter user's ID:");
    int idInput;
    scanf("%i", &idInput);
    int i;
    for (i = 0; i < clinic->userListCount; i++)
    {
        if (clinic->userList[i].userID == idInput)
        {
            return clinic->userList[i];
        }
    }
    Date_t emptyDate = {0, 0, 0};
    User_t noUser = {0, "", "", emptyDate, "", 0, "", '0'};
    return noUser;
}

/**
 * displayUserList
 * Displays all users in system
 * @param Clinic_t clinic: pointer to clinic
 **/
void displayUserList(Clinic_t *clinic)
{
    if (clinic->userListCount == 0)
    {
        printf("No users in system.\n");
        return;
    }
    int i;
    for (i = 0; i < clinic->userListCount; i++)
    {
        User_t userToDisplay = clinic->userList[i];
        printf("%i,", userToDisplay.userID);
        printf("%s,", userToDisplay.firstName);
        printf("%s,", userToDisplay.lastName);
        printf("%i-%i-%i,", userToDisplay.dateOfBirth.day, userToDisplay.dateOfBirth.month, userToDisplay.dateOfBirth.year);
        printf("%s,", userToDisplay.email);
        printf("%i,", userToDisplay.phoneNo);
        printf("%s,", userToDisplay.address);
        printf("%c\n", userToDisplay.gender);
    }
}

/**
 * getPhone
 * Function gets user input and checks if it is all digits
 * @return user's phone number
 **/
int getPhoneNo()
{
    while (1)
    {
        char input[10];
        int invalidInput = 0;
        printf("Please enter user's phone number:");
        scanf("%s", input);
        int i;
        for (i = 0; i < strlen(input); i++)
        {
            /* Checks ASCII value to see if character is a number */
            if (input[i] < 48 || input[i] > 57)
            {
                printf("Please enter digits only!\n");
                invalidInput = 1;
                break;
            }
        }
        if (invalidInput)
        {
            continue;
        }
        return atoi(input);
    }
}

/**
 * createDoctor
 * Takes input for doctor information and stores in clinic's doctor list
 * @param Clinic_t clinic: pointer to clinic
 **/
void createDoctor(Clinic_t *clinic)
{
    if (clinic->doctorListCount == MAX_DOCTORS)
    {
        printf("Maximum amount of doctors reached\n");
        return;
    }

    else if (clinic->userListCount == 0)
    {
        printf("No users in system\n");
        return;
    }

    while (TRUE)
    {
        printf("User ID to tie doctor information is required\n");
        User_t doctorUser = getUser(clinic);
        if (doctorUser.userID == 0)
        {
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
/**
 * createAdminStaff
 * Takes input for admin staff's information and store in clinic's admin list
 * @return user_t user, returns blank user if not found
 **/
void createAdminStaff(Clinic_t *clinic)
{
    if (clinic->adminStaffCount == MAX_ADMIN_STAFF)
    {
        printf("Maximum amount of admin staff reached\n");
        return;
    }

    else if (clinic->userListCount == 0)
    {
        printf("No users in system\n");
        return;
    }

    while (TRUE)
    {
        printf("User ID to tie admin staff information is required\n");
        User_t adminUser = getUser(clinic);
        if (adminUser.userID == 0)
        {
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

/**
 * editAdminStaffTitle
 * Looks for staff ID, and edits the chosen staff's ID
 * @param Clinic_t clinic: pointer to clinic
 **/
void editAdminStaffTitle(Clinic_t *clinic)
{
    while (TRUE)
    {
        AdminStaff_t adminStaff = getAdminStaff(clinic);
        if (adminStaff.userId == 0)
        {
            printf("Invalid staff ID");
            continue;
        }
        AdminStaff_t *AdminStaffPtr = &clinic->adminStaffList[clinic->adminStaffCount];
        printf("Please enter admin staff's job title:");
        char jobTitleInput[MAX_JOB_TITLE_LENGTH];
        scanf(" %[^\n]%*c", jobTitleInput);
        strcpy(AdminStaffPtr->jobTitle, jobTitleInput);
        break;
    }
}

/**
 * getAdminStaff
 * Function gets user input and checks if there is an associated staff and returns the staff
 * @param Clinic_t clinic: pointer to clinic
 * @return AdminStaff_t admin staff, returns blank user if not found
 **/
AdminStaff_t getAdminStaff(Clinic_t *clinic)
{
    printf("Please enter admin staff ID:");
    int idInput;
    scanf("%i", &idInput);
    int i;
    for (i = 0; i < clinic->adminStaffCount; i++)
    {
        if (clinic->adminStaffList[i].staffId == idInput)
        {
            return clinic->adminStaffList[i];
        }
    }
    Date_t emptyDate = {0, 0, 0};
    AdminStaff_t noUser = {0, 0, "", emptyDate};
    return noUser;
}

/**
 * doctorToString
 * Prints out doctor information
 * @param Doctor_t doctorToDisplay
 **/
void doctorToString(Doctor_t doctorToDisplay)
{
    printf("Doctor Information for userID: %i\n", doctorToDisplay.userId);
    printf("Doctor ID: %i\n", doctorToDisplay.doctorId);
    printf("Start date:");
    printDate(doctorToDisplay.startDate);
    printf("\n");
}

/**
 * adminStaffToString
 * Prints out staff information
 * @param AdminStaff_t adminStaffToDisplay
 **/
void adminStaffToString(AdminStaff_t adminStaffToDisplay)
{
    printf("Admin Staff Information for userID: %i\n", adminStaffToDisplay.userId);
    printf("Staff ID: %i\n", adminStaffToDisplay.staffId);
    printf("Job Title: %s\n", adminStaffToDisplay.jobTitle);
    printf("Start date:");
    printDate(adminStaffToDisplay.startDate);
    printf("\n");
}

/**
 * displayDoctorList
 * Displays all doctors in system
 * @param Clinic_t clinic: pointer to clinic
 **/
void displayDoctorList(Clinic_t *clinic)
{
    if (clinic->doctorListCount == 0)
    {
        printf("No doctors in system.\n");
        return;
    }
    int i;
    for (i = 0; i < clinic->doctorListCount; i++)
    {
        Doctor_t doctorToDisplay = clinic->doctorList[i];
        printf("%i,", doctorToDisplay.userId);
        printf("%i,", doctorToDisplay.doctorId);
        printf("%i-%i-%i\n", doctorToDisplay.startDate.day, doctorToDisplay.startDate.month, doctorToDisplay.startDate.year);
    }
}

/**
 * displayAdminStaffList
 * Displays all admin staff in system
 * @param Clinic_t clinic: pointer to clinic
 **/
void displayAdminStaffList(Clinic_t *clinic)
{
    if (clinic->adminStaffList == 0)
    {
        printf("No staff in system.\n");
        return;
    }
    int i;
    for (i = 0; i < clinic->adminStaffCount; i++)
    {
        AdminStaff_t staffToDisplay = clinic->adminStaffList[i];
        printf("%i,", staffToDisplay.userId);
        printf("%s,", staffToDisplay.jobTitle);
        printf("%i-%i-%i\n", staffToDisplay.startDate.day, staffToDisplay.startDate.month, staffToDisplay.startDate.year);
    }
}

/**
 * createPatient
 * Function gets user input, creates a patient and  stores info in patient list
 * @return user_t user
 **/
void createPatient(Clinic_t *clinic)
{
    if (clinic->patientListCount == MAX_PATIENTS)
    {
        printf("Maximum amount of patients reached\n");
        return;
    }
    else if (clinic->userListCount == 0)
    {
        printf("No users in system\n");
        return;
    }
    else if (clinic->doctorListCount == 0)
    {
        printf("No doctors in system\n");
        return;
    }

    PatientInfo_t *newPatientPtr = &clinic->patientList[clinic->patientListCount];
    while (TRUE)
    {
        printf("User ID to tie patient information is required\n");
        User_t patientUser = getUser(clinic);
        if (patientUser.userID == 0)
        {
            printf("Invalid user. Please try again\n\n");
            continue;
        }
        else
        {
            newPatientPtr->userID = patientUser.userID;
            while (TRUE)
            {
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
                switch (bloodChoice)
                {
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
                if (invalidChoice)
                {
                    continue;
                }
                break;
            }

            printf("Assign primary doctor to patient\n");
            while (TRUE)
            {
                printf("Select a doctor to assign\n");
                int i;
                for (i = 0; i < clinic->doctorListCount; i++)
                {
                    printf("%i. Doctor id: %i\n", i, clinic->doctorList[i].doctorId);
                }
                char doctorSelected;
                printf("Enter selection:");
                scanf(" %c", &doctorSelected);
                int doctorOption = atoi(&doctorSelected);
                if (doctorSelected > 0 || doctorSelected < clinic->doctorListCount)
                {
                    newPatientPtr->primaryDoctorID = clinic->doctorList[doctorOption].doctorId;
                    break;
                }
                else
                {
                    printf("Invalid choice. Try again.\n");
                }
            }
        }
        break;
    }

    printf("New Patient Information\n\n");
    patientInfoToString(clinic->patientList[clinic->patientListCount]);
    printf("\n");
    clinic->patientListCount += 1;
}

/**
 * patientInfoToString
 * Prints out patient information
 * @param PatientInfo_t patientInfoToDisplay
 **/
void patientInfoToString(PatientInfo_t patientInfoToDisplay)
{
    printf("Patient User Id: %i\n", patientInfoToDisplay.userID);
    printf("Patient Blood Type: %s\n", patientInfoToDisplay.bloodType);
    printf("Patient primary doctor: %i\n", patientInfoToDisplay.primaryDoctorID);
}

/**
 * searchUser
 * Asks for user information and looks for a patient if it exists and displays user info
 *@param Clinic_t clinic: pointer to clinic
**/
void searchPatient(Clinic_t *clinic)
{
    PatientInfo_t searchedPatient = getPatient(clinic);
    if (searchedPatient.userID == 0) {
        printf("No patient found!\n");
    }
    else
    {
        printf("\n");
        printf("Patient found! Displaying patient information.\n\n");
        patientInfoToString(searchedPatient);
    }
    
}

/**
 * getPatient
 * Function gets user input and checks if there is an associated patient
 * @param Clinic_t clinic: pointer to clinic
 * @return PatientInfo_t patient, returns blank user if not found
 **/
PatientInfo_t getPatient(Clinic_t *clinic)
{
    printf("Please enter patient's user ID:");
    int idInput;
    scanf("%i", &idInput);
    int i;
    for (i = 0; i < clinic->patientListCount; i++)
    {
        if (clinic->patientList[i].userID == idInput)
        {
            return clinic->patientList[i];
        }
    }
    PatientInfo_t emptyPatient = {0, "", 0};
    return emptyPatient;
}

/**
 * displayPatientList
 * Displays all patients in system
 * @param Clinic_t clinic: pointer to clinic
 **/
void displayPatientList(Clinic_t *clinic)
{
    if (clinic->patientListCount == 0)
    {
        printf("No patients in system.\n");
        return;
    }
    int i;
    for (i = 0; i < clinic->patientListCount; i++)
    {
        PatientInfo_t patientInfoToDisplay = clinic->patientList[i];
        printf("%i,", patientInfoToDisplay.userID);
        printf("%s,", patientInfoToDisplay.bloodType);
        printf("%i\n", patientInfoToDisplay.primaryDoctorID);
    }
}

/**
 * getDate()
 * Function takes user input and returns a date
 * Checks that dates are valid (1<DD<31, 1<MM<12, 1900<YYYY<2021)
 * @return Date_t date from user input in a valid range
**/

Date_t getDate()
{
    Date_t returnedDate;
    while (TRUE)
    {
        printf("Enter Date: day>");
        scanf("%i", &returnedDate.day);
        if (returnedDate.day < 1 || returnedDate.day > 31)
        {
            printf("Invalid day. ");
        }
        else
        {
            break;
        }
    }
    while (TRUE)
    {
        printf("Enter Date: month>");
        scanf("%i", &returnedDate.month);
        if (returnedDate.month < 1 || returnedDate.month > 12)
        {
            printf("Invalid month. ");
        }
        else
        {
            break;
        }
    }
    while (TRUE)
    {
        printf("Enter Date: year>");
        scanf("%i", &returnedDate.year);
        if (returnedDate.year < 1900 || returnedDate.year > 2021)
        {
            printf("Invalid year. ");
        }
        else
        {
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
void printDate(Date_t date)
{
    printf("%02i", date.day);
    printf("/");
    printf("%02i", date.month);
    printf("/");
    printf("%i", date.year);
    printf("\n");
}
