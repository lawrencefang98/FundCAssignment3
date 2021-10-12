
/*Rose*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*********************directives**************/
#define MAX_PATIENTS 150 
#define MAX_DOCTORS 20 
#define MAX_NAME_LENGTH 20 
#define MAX_EMAIL_LENGTH 50 
#define MAX_ADDRESS_LENGTH 255 
#define MAX_DESCRIPTION_SIZE 2000

/*************struct definitions************/
struct date{ 
    int day;
    int month;
    int year;
};
struct patient{
    char firstname[MAX_NAME_LENGTH];
    char lastname [MAX_NAME_LENGTH];
    struct date birthday;
    char email[MAX_EMAIL_LENGTH];
    int phoneNo;
    char address[MAX_ADDRESS_LENGTH];
    char gender[1];
    char bloodtype;
    char description[MAX_DESCRIPTION_SIZE];
};

 struct doctor{
     char firstname[MAX_NAME_LENGTH];
    char lastname [MAX_NAME_LENGTH];
    struct date birthday;
    char email[MAX_EMAIL_LENGTH];
    int phoneNo;
    char gender[1];
 };

/**************** Function prototypes*******************/
void printMenu1(void);
void printpatient(void);
void printdoctor(void);
/*void display_patientlist(); 
void add_patient(); 
void edit_patientdetails(); 
void doctordetails();
void edit doctorsdetails();
void save(); 
void delete_patient(); */
/*******************************************************/

/********************************************************************************
Main1
*******************************************************************************/
int main(void){ 
    /*char dbFileName[] = "database";*/
            /*FILE* database;assigns a file pointer variable */
            /*struct patient patient_s[MAX_PATIENTS]; 
            struct doctor doctor_s[MAX_DOCTORS];
            int patientcount = 0;
            int doctorcount=0;
            
            int p,q;
            char selection2[256];
            char selection3[256];
            */
            int check=1;
            /*int patientcount = 0;*/
            int choice1=0;

            char selection1[256];
            /*char selection2[256];*/
        
            while(choice1!=4){

                printMenu1();
                printf("Enter your choice>");
                fgets(selection1,256,stdin);
                 choice1=atoi(selection1);
             

            while (choice1>4 || choice1<1 || check==0){
                check=1;
                printf("Invalid choice.");
                fflush(stdin);
                printMenu1();
                printf("Enter your choice>");
                fgets(selection1,256,stdin);
                    choice1=atoi(selection1);
            }
            switch (choice1) {
                 case 1: 
                printpatient();
                 break;
                 
                 case 2: 
                 printf("hello by");
                 printdoctor();
                 break;

                


            }
            }
            
                return 1;
}



void printMenu1(void){
printf("\n\n"
         "1. Enter/Modify Patient Details\n"
         "2. Enter/Modify Doctor Details\n"
         "3. Save the Program\n"
         "4. Exit the program\n");
}

 void printpatient(){
         printf("\n\n"
         "1. Add Patient\n"
         "2. Edit Existing Patient Details\n"
         "3. Delete Patient Details\n"
         "4. Save Patient Details to Database\n"
         "5. Read Patient Details from Database\n"
         "6. Exit the program\n");
         }

void printdoctor(){
         printf("\n\n"
         "1. Add Doctor\n"
         "2. Edit Existing Doctor Details\n"
         "3. Delete Doctor Details\n"
         "4. Save Doctor Details to Database\n"
         "5. Read Doctor Details from Database\n"
         "6. Exit the program\n");
         }

