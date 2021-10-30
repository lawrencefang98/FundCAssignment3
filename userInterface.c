#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <encryption.h>

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

struct Clinic {
    User_t userList[MAX_USERS];
    PatientInfo_t patientList[MAX_PATIENTS];
    Doctor_t doctorList[MAX_DOCTORS];
    AdminStaff_t adminStaffList[MAX_ADMIN_STAFF];
};
typedef struct Clinic Clinic_t;


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

struct Date {
    int day;
    int month;
    int year; 
};
typedef struct Date Date_t;


struct PatientInfo {
    User_t patientUser;
    char bloodType[3];
    Doctor_t primaryDoctor;
    MedicalRecord_t*  medicalRecordHistory;

};
typedef struct PatientInfo PatientInfo_t;


struct MedicalRecord {
    Date_t dateOfEntry;
    Doctor_t doctorVisited;
    char description[MAX_RECORD_DESCRIPTION_LENGTH];
    MedicalRecord_t* next = NULL;
};
typedef struct MedicalRecord MedicalRecord_t;

struct Doctor {
    User_t doctorUser;
    int doctorId;
    Date_t startDate;
    Date_t endDate;
};
typedef struct Doctor Doctor_t;


struct AdminStaff {
    User_t staffUser;
    char jobTitle[MAX_JOB_TITLE_LENGTH];
};
typedef struct AdminStaff AdminStaff_t;


/**************** Function prototypes *******************/

void printMenu1(void);
void printdoctor(void);
void printstaff(void);
void for_doctor(/*items to return*/)
void for_staff(/*items to return*/)
/********************************************************************************
Main1
*******************************************************************************/
int main(void){ 

    PatientInfo_t Patientinfo[MAX_PATIENTS]; 
    Doctor_t doctorinfo[MAX_DOCTORS];
    admin_s admin_t[MAX_ADMIN_STAFF];


    int check=1;
    int choice1=0;
    char selection1[256];

  /*  login function

    loginmenu();*/

/* need a return from login menu to write a if function to go to the next menu*/
    printMenu1();
    printf("Enter your choice>");
    scanf("%s",selection1);/*reads the input stream and stores it in selection*/
    choice1=atoi(selection1);
            
    while (choice>6|| choice1<1 || check==0){
    
        check=1;
        printf("Invalid choice.");
        printMenu1();
        printf("Enter your choice>");
        scanf("%s",selection1);/*reads the input stream and stores it in selection*/
        choice1=atoi(selection1);
          
      }

    switch (choice1) {

        case 1: 
        /*Add function for the doctor*/
        break;
                 
        case 2: 
        /* Add function for admin*/
        break;

        case 3:
        /* Save to database*/
        break; 

        case 4:
        /* read from database*/
        break; 

        case 5:
        /*compress the file*/
        break; 

        case 6:
        /* Encrypt the file*/
         break; 
            
        case 7:
        /* decrypt the file*/
         break; 
           }
            
                return 1;
}


void printMenu1(void){
    printf("\n\n"
         "1. For Doctor\n" 
         "2. For Admin\n"
         "3. Save to Database\n"
         "4. Read from Database\n"
         "5. Compress the file\n"
         "6. Encrypt the file\n"
         "7. Decyrpt the file\n"
         "8. Exit the program\n");
}

void printdoctor(){
    printf("\n\n"
         "1. Add New Patient\n"
         "2. Edit Existing Patient Details\n"
         "3. Delete Patient\n"
         "4. Display Patient Information\n"
         "5. View All Patient Details\n"
         "6. Search All Patient Details\n"
         "7. Return to Main Menu");
}

void printstaff(){
        printf("\n\n"
         "1. Add New Patient\n"
         "2. Edit Existing Patient Details\n"
         "3. Delete Patient\n"
         "4. Display Patient Information\n"
         "5. View All Patient Details\n"
         "6. Search All Patient Details\n"
         "7. Add New Doctor\n"
         "8. Edit existing doctor details\n"
         "9. View all doctor details\n");
}


void for_doctor(){/*items to return*/

    char userinput1[256];
    int select1=0;
    int pcount=0;
    int checkp=0;
    
    
    printdoctor(); 

    printf("\nEnter your choice>");
    scanf("%c",&temp);
    scanf("%s",userinput1);
    select1=atoi(userinput1);

    while (select1>7 || select1<1 || checkp==0){
    checkp=1;
    printf("Invalid choice.");
    printdoctor();
    printf("\nEnter your choice>");
    scanf("%s",userinput1);
    select1=atoi(userinput1);

    }

    switch (select1){

    case 1:
    
    /*create user*/
    

    else{

        printf("Patient List is full"); /*for the doctor to input*/
    }
    
    break;
            
    case 2:

    break;
    
    case 3:

    break;

    case 4:

    break;

    case 5:

    break;
   
    case 6:

    break;
    }
}

void for_staff(/*items to return*/){

    
    
    
    printstaff(); 

    printf("Enter your choice>");
    scanf("%s",userinput2);
    select2=atoi(userinput2);


    while (select2>9 || select2<1 || checks==0){
    checks=1;
    printf("Invalid choice.");
    printpatient();
    printf("Enter your choice>");
    scanf("%s",userinput2);
    select2=atoi(userinput2);

    }

    switch (select2){

    case 1:

    break;

    case 2:

    break;
    
    case 3:

    break;

    case 4:

    break;

    case 5:

    break;
   
    case 6:

    break;

    case 7:

    break;

    case 8:

    break;
    }
}


 
