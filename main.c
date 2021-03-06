#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encryption.h"
#include "dataManipulation.h"
#include "compression.h"
#include "login.h"
#include "filehanding.h"


/**************** Function prototypes *******************/

void printMenu1(void);
void printdoctor(void);
void printstaff(void);
void for_doctor(Clinic_t *clinicPtr);
void for_staff(Clinic_t *clinicPtr);
void loginMenu();
/********************************************************************************
Main1
*******************************************************************************/
int main(void){ 

    Clinic_t clinic;
    Clinic_t *clinicPtr = &clinic;
    createClinic(clinicPtr);
    
    int check=0;
    int choice1=0;
    char selection1[256];

    do{
        printMenu1();
        printf("Enter your choice>");
        scanf("%s",selection1);/*reads the input stream and stores it in selection*/
        choice1=atoi(selection1);
        switch (choice1) {

            case 1: 
            /*Add function for the doctor*/
                for_doctor(clinicPtr);
            break;
                 
            case 2: 
            /* Add function for admin*/
                for_staff(clinicPtr);
            break;

            case 3:
            /* Save doctor to database*/
                saveDoctors(clinicPtr);
            break; 
                
            case 4:
            /* save patient */
                savePatients(clinicPtr);
            break; 
                
            case 5:
            /* save admin */
                saveAdminstaff(clinicPtr);
            break; 

            case 6:
            /* Save users*/
                saveUsers(clinicPtr);
            break; 
                
            case 7:
            /* delete from database*/
                deletefile();
            break;
            
             case 8:
            /* merge */
                mergefile();
            break;

            case 9:
            /* compress the file*/
                compression();
            break; 

            case 10:
            /* Encrypt the file*/
                loginMenu();
            break; 
         
            case 11:
                check=1;
            break;

            default:
                printf("Invalid choice.");
            break;
            }
    }while (check == 0);
    
            
        return 1;
}


void printMenu1(void){
    printf("\n\n"
         "1. For Doctor\n" 
         "2. For Admin\n"
         "3. Save Doctors to Database\n"
         "4. Save Patients to Database\n"
         "5. Save Admin Staff to Database\n" 
         "6. Save Users to Database\n"
         "7. Delete file\n"
         "8. Merge files\n"
         "9. Compress the file\n"
         "10. Encrypt the file\n"
         "11. Exit the program\n");
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
         "11. Return to Main Menu\n");
    
}


void for_doctor(Clinic_t *clinicPtr){/*items to return*/
    char userinput1[256];
    int select1=0;
    int checkp=0;
    char temp;
    do{
        printdoctor();
        printf("\nEnter your choice>");
        scanf("%c",&temp);
        scanf("%s",userinput1);
        select1=atoi(userinput1);
        switch (select1){

            case 1:
                createPatient(clinicPtr);
                break; 

            case 2:
                searchPatient(clinicPtr);
                break;

            case 3:
                displayPatientList(clinicPtr);
                break;
            case 4:
                checkp=1;
                break;
            default:
                printf("Invalid choice.");
        }
    }while(checkp==0);
}

void for_staff(Clinic_t *clinicPtr){

    char userinput2[2]; 
    int select2;
    int checks=0;
    do{
        printstaff();
        printf("Enter your choice>");
        scanf("%s", userinput2);
        select2=atoi(userinput2);
        switch (select2){

            case 1:
                createUser(clinicPtr);
                break;

            case 2:
                editUser(clinicPtr);
                break;
    
            case 3:
                deleteLastUser(clinicPtr);
                break;

            case 4:
                searchUser(clinicPtr);
                break;

            case 5:
                displayUserList(clinicPtr);
                break;
   
            case 6:
                createDoctor(clinicPtr);
                break;

            case 7:
                createAdminStaff(clinicPtr);
                break;
        
            case 8:
                editAdminStaffTitle(clinicPtr);
                break;
            
            case 9:
                displayDoctorList(clinicPtr);
                break;
            
            case 10:
                displayAdminStaffList(clinicPtr);
                break;   
                
            case 11:
                checks =1;
                break;
                
            default:
                printf("Invalid choice.");
                break;
        }
    }while (checks==0);
}


 
