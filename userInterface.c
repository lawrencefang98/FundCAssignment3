#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <encryption.h>
#include "dataManipulation.h"


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

    struct User *userListcount
    struct patientInfo *patientListcount
    struct doctor *doctorListcount
    struct adminstaff *adminListcount

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
         "2. Display Patient Information\n"
         "3. View All Patient Details\n"
         "4. Return to Main Menu");
}

void printstaff(){
        printf("\n\n"
         "1. Add New User\n"
         "2. Edit User\n"
         "3. Delete Last Created User\n"
         "4. Display User Information\n"
         "5. View All User Details\n"
         "6. Add New Doctor\n"
         "7. Add New Admin Staff\n"
         "8. Edit Admin Staff Title\n"           
         "9. View all doctor details\n"
         "10. View all staff details\n"
         "11. Return to Main Menu\n";
    
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


 
