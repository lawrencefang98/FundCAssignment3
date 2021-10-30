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
void add_doctor();

/******login****/
void printMenu();
_Noreturn void loginMnu();
void addUser(user t accounts[], int* total_p);
void saveUser(user_t accounts[], int* total_p);
int checkCharNum(const char password[]);int checkChar(const char password[])
int checkChar(const char password[]);
int checkSpace(const char password[])
int checkUser(const char* user)
int checkPass(const char* pass)
void loginUser();

/****File handling***/
User_t createUser();
void deleteUser(User_t userToDelete);
User_t searchUser();
void editUser(User_t userToEdit);

/********************************************************************************
Main1
*******************************************************************************/
int main(void){ 

    PatientInfo_t Patientinfo[MAX_PATIENTS]; 
    Doctor_t doctorinfo[MAX_DOCTORS];
    admin_s admin_t[MAX_ADMIN_STAFF];

    int admincount=0;
    int doctorcount=0;
    int patientcount=0;
    int admincount=0;
    int usercount=0;

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


void add_doctor(){/*items to return*/

    Clinic_t clinicinfo;
    PatientInfo_t PatInfo;
    /*MedicalRecord_t medInfo;*/

    char userinput1[256];
    int select1=0;
    char temp,temp1,temp2,temp3,temp4,temp5,temp6;/*temp7;*/
    int pcount=0;
    int checkp=0;
    char birthdayin[365]; 
    char monthin[365];
    char yearin[365];
    char phonenum[200];
    int checka=1; 
    int checkb=1;
    int checkc=1;
    
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
    
    if (pcount<MAX_PATIENTS){
    printf("\nEnter First Name>"); 
    scanf("%c",&temp1);
    scanf("%[^\n]",clinicinfo.patientList->patientUser.firstName);
    
    printf("Enter Last Name>"); 
    scanf("%c",&temp1);
    scanf("%[^\n]",clinicinfo.patientList->patientUser.lastName);

    printf("Enter birthday: day>");
    scanf("%s",birthdayin);
    clinicinfo.patientList->patientUser.dateOfBirth.day=atoi(birthdayin);

    while(clinicinfo.patientList->patientUser.dateOfBirth.day<1||clinicinfo.patientList->patientUser.dateOfBirth.day>31||checka==0){
        
        checka=1;
        printf("Invalid day. Enter birthday: day>");
        scanf("%s",birthdayin); 
        clinicinfo.patientList->patientUser.dateOfBirth.day=atoi(birthdayin);
    }

        printf("Enter birthday: month>");
        scanf("%s",monthin);
        clinicinfo.patientList->patientUser.dateOfBirth.month=atoi(monthin);

    while(clinicinfo.patientList->patientUser.dateOfBirth.month<1||clinicinfo.patientList->patientUser.dateOfBirth.month>12||checkb==0)
{
        checkb=1;
        printf("Invalid month. Enter birthday: month>");
        scanf("%s",monthin);
        clinicinfo.patientList->patientUser.dateOfBirth.month=atoi(monthin);
}

        printf("Enter birthday: year>");
        scanf("%s",yearin);
        clinicinfo.patientList->patientUser.dateOfBirth.year=atoi(yearin);

    while(clinicinfo.patientList->patientUser.dateOfBirth.year<1900||clinicinfo.patientList->patientUser.dateOfBirth.year>2021||checkc==0)
{
        checkc=1;
        printf("Invalid year. Enter birthday: year>");
        scanf("%s",yearin);
        clinicinfo.patientList->patientUser.dateOfBirth.year=atoi(yearin);
}

        printf("Enter Email ID>"); 
        scanf("%c",&temp2);
        scanf("%50[^\n]",clinicinfo.patientList->patientUser.email);

        printf("Enter Phone Number>"); 
        scanf("%c",&temp3);
        scanf("%9[^\n]",phonenum);
        clinicinfo.patientList->patientUser.phoneNo=atoi(phonenum);

        printf("Enter Address>"); 
        scanf("%c",&temp4);
        scanf("%255[^\n]",clinicinfo.patientList->patientUser.address);

        printf("Enter Gender (Enter M or F)>"); 
        scanf("%c",&temp5);
        scanf("%1[^\n]",clinicinfo.patientList->patientUser.gender);

        printf("Enter Bloodtype>"); 
        scanf("%c",&temp6);
        scanf("%2[^\n]",PatInfo.bloodType);
        
        printf("\nEnter Doctor's First Name>"); 
        scanf("%c",&temp7);
        scanf("%[^\n]",clinicinfo.doctorList->doctorUser.firstName);
        
        printf("\nEnter Doctor's Last Name>"); 
        scanf("%c",&temp7);
        scanf("%[^\n]",clinicinfo.doctorList->doctorUser.lastName);
        
        

    pcount++;

    }

    else{

        printf("Patient List is full");
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

void add_staff(/*items to return*/){

    char userinput2[256];
    int select2=0;
    char tem,tem1,tem2,tem3,tem4,tem5,tem6,tem7;
    int checks;
    
    printstaff(); 

    printf("Enter your choice>");
    scanf("%s",userinput2);/*reads the input stream and stores it in selection*/
    select2=atoi(userinput2);


    while (select2>9 || select2<1 || checks==0){
    checks=1;
    printf("Invalid choice.");
    printpatient();
    printf("Enter your choice>");
    scanf("%s",userinput2);/*reads the input stream and stores it in selection*/
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


 
