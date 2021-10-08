#include <stdio.h>
/**
 * Author: Lawrence Fang
 * Header file for data manipulation
**/

/* PREPROCESSING DIRECTIVES */
#define MAX_USERS 200
#define MAX_PATIENTS 150
#define MAX_DOCTORS 20
#define MAX_ADMIN_STAFF 30 
#define MAX_NAME_LENGTH 20
#define MAX_EMAIL_LENGTH 50
#define MAX_ADDRESS_LENGTH 255
#define MAX_RECORD_DESCRIPTION_LENGTH 2000
#define MAX_PHONENO_LENGTH 10
#define MAX_JOB_TITLE_LENGTH 50



/* STRUCTURE DEFINITIONS */

/**
 * Author: Lawrence Fang
 * Stores entire clinic informatio
**/

struct Clinic {
    User_t userList[MAX_USERS];
    PatientInfo_t patientList[MAX_PATIENTS];
    Doctor_t doctorList[MAX_DOCTORS];
    AdminStaff_t adminStaffList[MAX_ADMIN_STAFF];
};
typedef struct Clinic Clinic_t;

/**
 * Author: Lawrence Fang
 * Stores personal information about every user in the system
**/
struct User {
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
 * Stores date in a dd/mm/yyyy format.
**/
struct Date {
    int day;
    int month;
    int year; 
};
typedef struct Date Date_t;

/**
 * Author: Lawrence Fang
 * Stores information related to a patient's medical information
**/
struct PatientInfo {
    User_t patientUser;
    char bloodType[3];
    Doctor_t primaryDoctor;
    MedicalRecord_t*  medicalRecordHistory;

};
typedef struct PatientInfo PatientInfo_t;

/**
 * Author: Lawrence Fang
 * Medical record information represented in linked list structure
 * Linked list structure chosen due to unknown size of medical records for each user
**/
struct MedicalRecord {
    Date_t dateOfEntry;
    Doctor_t doctorVisited;
    char description[MAX_RECORD_DESCRIPTION_LENGTH];
    MedicalRecord_t* next = NULL;
};
typedef struct MedicalRecord MedicalRecord_t;

/**
 * Author: Lawrence Fang
 * Stores information related to a doctor's information
**/
struct Doctor {
    User_t doctorUser;
    int doctorId;
    Date_t startDate;
    Date_t endDate;
};
typedef struct Doctor Doctor_t;

/**
 * Author: Lawrence Fang
 * Stores information related to administrative staff
**/
struct AdminStaff {
    User_t staffUser;
    char jobTitle[MAX_JOB_TITLE_LENGTH];
};
typedef struct AdminStaff AdminStaff_t;

/* FUNCTION DEFINITIONS */

User_t createUser();
void deleteUser(User_t userToDelete);
User_t searchUser();
void editUser(User_t userToEdit);
