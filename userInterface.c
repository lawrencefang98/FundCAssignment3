
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
    char bloodtype [2];
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
void add_patient(int pcount,struct patient patientinfo[]); 
void patientbirthday(int n,struct patient patientstr[]);
void doctorbirthday(int d, struct doctor doctorbirth[]);
void add_doctor(int dcount, struct doctor doctorinfo[]);

/*void display_patientlist(); 
void save(); 
void delete_patient(); */
/*******************************************************/

/********************************************************************************
Main1
*******************************************************************************/
int main(void){ 
    /*char dbFileName[] = "database";*/
            /*FILE* database;*/
            struct patient patient_s[MAX_PATIENTS]; 
            struct doctor doctor_s[MAX_DOCTORS];
    
           int doctorcount=0;
            
            /*int p,q;
            char selection2[256];
            char selection3[256];
            */
            int check=1;
            int patientcount = 0;
            int choice1=0;

            char selection1[256];
            /*char selection2[256];*/
        
          /*  while(choice1!=4){*/
          

                printMenu1();
                printf("Enter your choice>");
                scanf("%s",selection1);
                choice1=atoi(selection1);
            

            while (choice1>4 || choice1<1 || check==0){
                check=1;
                printf("Invalid choice.");
                printMenu1();
                printf("Enter your choice>");
                scanf("%s",selection1);
                choice1=atoi(selection1);
            }
            switch (choice1) {

                 case 1: 
                add_patient(patientcount,patient_s);
                 break;
                 
                 case 2: 
                add_doctor(doctorcount,doctor_s);
                 break;
                
                


         /*   }*/
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

void patientbirthday(int n,struct patient patientstr[]){

char birthdayin[365]; 
char monthin[365];
char yearin[365];

int checka=1;
int checkb=1;
int checkc=1;

printf("Enter birthday: day>");
scanf("%s",birthdayin);
patientstr[n].birthday.day=atoi(birthdayin);

while(patientstr[n].birthday.day<1||patientstr[n].birthday.day>31||checka==0)
{
    checka=1;
    printf("Invalid day. Enter birthday: day>");
    scanf("%s",birthdayin); 
    patientstr[n].birthday.day=atoi(birthdayin);
}

printf("Enter birthday: month>");
scanf("%s",monthin);
patientstr[n].birthday.month=atoi(monthin);

while(patientstr[n].birthday.month<1||patientstr[n].birthday.month>12||checkb==0)
{
    checkb=1;
    printf("Invalid month. Enter birthday: month>");
    scanf("%s",monthin);
    patientstr[n].birthday.month=atoi(monthin);
}

printf("Enter birthday: year>");
scanf("%s",yearin);
patientstr[n].birthday.year=atoi(yearin);

while(patientstr[n].birthday.year<1900||patientstr[n].birthday.year>2021||checkc==0)
{
    checkc=1;
    printf("Invalid year. Enter birthday: year>");
  scanf("%s",yearin);
    patientstr[n].birthday.year=atoi(yearin);
}


}

void add_patient(int pcount,struct patient patientinfo[]){

     char userinput1[256];
     int select1=0;
     char temp,temp1,temp2,temp3,temp4,temp5,temp6,temp7;
     int checkp;
     char phonenum[50];
   
         
        printpatient(); 

        printf("Enter your choice>");
        scanf("%s",userinput1);
        select1=atoi(userinput1);


            while (select1>6 || select1<1 || checkp==0){
                checkp=1;
                printf("Invalid choice.");
                printpatient();
                printf("Enter your choice>");
                scanf("%s",userinput1);
                select1=atoi(userinput1);

            }

switch (select1){

case 1:

    printf("\nEnter First Name>"); 
    scanf("%c",&temp);
    scanf("%[^\n]",patientinfo[pcount].firstname);

    printf("Enter Last Name>"); 
    scanf("%c",&temp1);
    scanf("%[^\n]",patientinfo[pcount].lastname);

    patientbirthday(pcount,patientinfo);

    printf("Enter Email ID>"); 
    scanf("%c",&temp2);
    scanf("%50[^\n]",patientinfo[pcount].email);

    printf("Enter Phone Number>"); 
    scanf("%c",&temp3);
    scanf("%9[^\n]",phonenum);
    patientinfo[pcount].phoneNo=atoi(phonenum);

    printf("Enter Address>"); 
    scanf("%c",&temp4);
    scanf("%255[^\n]",patientinfo[pcount].address);

    printf("Enter Gender (Enter M or F)>"); 
    scanf("%c",&temp5);
    scanf("%1[^\n]",patientinfo[pcount].gender);

    printf("Enter Bloodtype>"); 
    scanf("%c",&temp6);
    scanf("%2[^\n]",patientinfo[pcount].bloodtype);

    printf("Enter Description>"); 
    scanf("%c",&temp7);
    scanf("%2000[^\n]",patientinfo[pcount].description);
   

case 2:

printf("the greatest");

        }

}

void doctorbirthday(int d, struct doctor doctorbirth[]){

char birthdayin[365]; 
char monthin[365];
char yearin[365];

int checka=1; 
int checkb=1;
int checkc=1;

printf("Enter birthday: day>");
scanf("%s",birthdayin);
doctorbirth[d].birthday.day=atoi(birthdayin);

while(doctorbirth[d].birthday.day<1||doctorbirth[d].birthday.day>31||checka==0)
{
    checka=1;
    printf("Invalid day. Enter birthday: day>");
    scanf("%s",birthdayin); 
    doctorbirth[d].birthday.day=atoi(birthdayin);
}

printf("Enter birthday: month>");
scanf("%s",monthin);
doctorbirth[d].birthday.month=atoi(monthin);

while(doctorbirth[d].birthday.month<1||doctorbirth[d].birthday.month>12||checkb==0)
{
    checkb=1;
    printf("Invalid month. Enter birthday: month>");
    scanf("%s",monthin);
    doctorbirth[d].birthday.month=atoi(monthin);
}

printf("Enter birthday: year>");
scanf("%s",yearin);
doctorbirth[d].birthday.year=atoi(yearin);

while(doctorbirth[d].birthday.year<1900||doctorbirth[d].birthday.year>2021||checkc==0)
{
    checkc=1;
    printf("Invalid year. Enter birthday: year>");
  scanf("%s",yearin);
    doctorbirth[d].birthday.year=atoi(yearin);
}

}


void add_doctor(int dcount, struct doctor doctorinfo[]){

char userinput1[256];
     int select1=0;
     char temp,temp1,temp2,temp3,temp4;
     int checkp;
     char phonenum[50];
   
         
        printdoctor(); 

        printf("Enter your choice>");
        scanf("%s",userinput1);
        select1=atoi(userinput1);


            while (select1>6 || select1<1 || checkp==0){
                checkp=1;
                printf("Invalid choice.");
                printdoctor();
                printf("Enter your choice>");
                scanf("%s",userinput1);
                select1=atoi(userinput1);

            }

switch (select1){

case 1:

    printf("\nEnter First Name>"); 
    scanf("%c",&temp);
    scanf("%[^\n]",doctorinfo[dcount].firstname);

    printf("Enter Last Name>"); 
    scanf("%c",&temp1);
    scanf("%[^\n]",doctorinfo[dcount].lastname);

    doctorbirthday(dcount,doctorinfo);

    printf("Enter Email ID>"); 
    scanf("%c",&temp2);
    scanf("%50[^\n]",doctorinfo[dcount].email);

    printf("Enter Phone Number>"); 
    scanf("%c",&temp3);
    scanf("%9[^\n]",phonenum);
    doctorinfo[dcount].phoneNo=atoi(phonenum);

    printf("Enter Gender (Enter M or F)>"); 
    scanf("%c",&temp4);
    scanf("%1[^\n]",doctorinfo[dcount].gender);


case 2:

printf(" the greatest");

        }

}

