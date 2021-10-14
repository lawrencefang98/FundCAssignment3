/*******************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Name:YiJiang Wang
 *******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*******************************************************************************
Function prototypes 
 Author: YIJIANG WANG
*******************************************************************************/
void saveAdminstaff(AdminStaff_t adminstaffs[], int numAdminStaff);
void saveDoctors(Doctor_t doctors[], int numDoctor);
void savePatients(PatientInfo_t patients[], int numPatient);
int deletefile(void);
int mergefile(void);

/*******************************************************************************
 * This function save all adminstaffs.
 * inputs:
 * - adminstaffs: the array of all adminstaffs
 * - numAdminStaff: the number of adminstaffs
 * outputs:
 * - none
*******************************************************************************/
void saveAdminstaff(AdminStaff_t adminstaffs[], int numAdminStaff)
{
    FILE* file = fopen("Adminstaff.txt", "w");
	/*open file failed*/
	if (file == NULL)
	{
		printf("Save failed.\n");
		return;
	}
	/*write each adminstaffs*/
	int i;
	fprintf(file, "%d\n", numAdminStaff);
	for (i = 0; i < numAdminStaff; i++)
	{
		fprintf(file, "%i\n", numAdminStaff[i].staffUser.userID);
		fprintf(file, "%c\n", numAdminStaff[i].staffUser.firstName);
		fprintf(file, "%c\n", numAdminStaff[i].staffUser.lastName);
		fprintf(file, "%i\n", numAdminStaff[i].staffUser.dateOfBirth.day);
		fprintf(file, "%i\n", numAdminStaff[i].staffUser.dateOfBirth.month);
        fprintf(file, "%i\n", numAdminStaff[i].staffUser.dateOfBirth.year);
		fprintf(file, "%c\n", numAdminStaff[i].staffUser.email);
        fprintf(file, "%i\n", numAdminStaff[i].staffUser.phoneNo);
        fprintf(file, "%c\n", numAdminStaff[i].staffUser.address);
        fprintf(file, "%c\n", numAdminStaff[i].staffUser.gender);
        fprintf(file, "%c\n", numAdminStaff[i].jobTitle);
    }
	fclose(file);
}

/*******************************************************************************
 * This function save all doctors.
 * inputs:
 * - doctors: the array of all doctors
 * - numDoctor: the number of doctors
 * outputs:
 * - none
*******************************************************************************/
void void saveDoctors(Doctor_t doctors[], int numDoctor);
{
    FILE* file = fopen("Doctor.txt", "w");
	/*open file failed*/
	if (file == NULL)
	{
		printf("Save failed.\n");
		return;
	}
	/*write each doctors*/
	int i;
	fprintf(file, "%d\n", numDoctor);
	for (i = 0; i < numDoctor; i++)
	{
		fprintf(file, "%i\n", doctors[i].doctorUser.userID);
		fprintf(file, "%c\n", doctors[i].doctorUser.firstName);
		fprintf(file, "%c\n", doctors[i].doctorUser.lastName);
		fprintf(file, "%i\n", doctors[i].doctorUser.dateOfBirth.day);
		fprintf(file, "%i\n", doctors[i].doctorUser.dateOfBirth.month);
        fprintf(file, "%i\n", doctors[i].doctorUser.dateOfBirth.year);
		fprintf(file, "%c\n", doctors[i].doctorUser.email);
        fprintf(file, "%i\n", doctors[i].doctorUser.phoneNo);
        fprintf(file, "%c\n", doctors[i].doctorUser.address);
        fprintf(file, "%c\n", doctors[i].doctorUser.gender);
        fprintf(file, "%i\n", doctors[i].doctorId);
        fprintf(file, "%i\n", doctors[i].startDate.day);
        fprintf(file, "%i\n", doctors[i].startDate.month);
        fprintf(file, "%i\n", doctors[i].startDate.year);
        fprintf(file, "%i\n", doctors[i].endDate.day);
        fprintf(file, "%i\n", doctors[i].endDate.month);
        fprintf(file, "%i\n", doctors[i].endDate.year);
	}
	fclose(file);
}

/*******************************************************************************
 * This function save all patients.
 * inputs:
 * - patients: the array of all patients
 * - numPatient: the number of patients
 * outputs:
 * - none
*******************************************************************************/
void savePatients(PatientInfo_t patients[], int numPatient)
{
    FILE* file = fopen("Patients.txt", "w");
	/*open file failed*/
	if (file == NULL)
	{
		printf("Save failed.\n");
		return;
	}
	/*write each patients*/
	int i;
	fprintf(file, "%d\n", numPatient);
	for (i = 0; i < numPatient; i++)
	{
		fprintf(file, "%i\n", patients[i].patientUser.userID);
		fprintf(file, "%c\n", patients[i].patientUser.firstName);
		fprintf(file, "%c\n", patients[i].patientUser.lastName);
		fprintf(file, "%i\n", patients[i].patientUser.dateOfBirth.day);
		fprintf(file, "%i\n", patients[i].patientUser.dateOfBirth.month);
        fprintf(file, "%i\n", patients[i].patientUser.dateOfBirth.year);
		fprintf(file, "%c\n", patients[i].patientUser.email);
        fprintf(file, "%i\n", patients[i].patientUser.phoneNo);
        fprintf(file, "%c\n", patients[i].patientUser.address);
        fprintf(file, "%c\n", patients[i].patientUser.gender);
        fprintf(file, "%c\n", patients[i].bloodType);
        fprintf(file, "%i\n", patients[i].patientUser.primaryDoctor.doctorId);
        fprintf(file, "%i\n", patients[i].medicalRecordHistory.dateOfEntry.day);
        fprintf(file, "%i\n", patients[i].medicalRecordHistory.dateOfEntry.month);
        fprintf(file, "%i\n", patients[i].medicalRecordHistory.dateOfEntry.year);
        fprintf(file, "%i\n", patients[i].medicalRecordHistory.dateOfEntry.day);
        fprintf(file, "%i\n", patients[i].medicalRecordHistory.doctorVisited.endDate.day);
        fprintf(file, "%i\n", patients[i].medicalRecordHistory.doctorVisited.endDate.month);
        fprintf(file, "%i\n", patients[i].medicalRecordHistory.doctorVisited.endDate.year);
        fprintf(file, "%c\n", patients[i].medicalRecordHistory.description);
	}
	fclose(file);
}

/*******************************************************************************
 * This function delete the file.
 * inputs:
 * - file: store data in text files
 * outputs:
 * - none
*******************************************************************************/
int deletefile()
{
    char filename[10];
    printf("The file to delete:");
    gets(filename);
    if( remove(filename) == 0 )
        printf("%s. successfully deleted\n", filename);
    else
        perror("Error deleting file");
    return 0;
}

/*******************************************************************************
 * This function merge files into a single file
 * inputs:
 * - file: store data in text files
 * outputs:
 * - none
*******************************************************************************/
int mergefile()
{
   // Open three files to be merged
   FILE *fp1 = fopen("Adminstaff.txt", "r");
   FILE *fp2 = fopen("Patient.txt", "r");
   FILE *fp3 = fopen("Doctor.txt", "r");
  
   // Open file to store the result
   FILE *fp4 = fopen("Clinic.txt", "w");
   char c;
  
   if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL)
   {
         puts("Could not open files");
         exit(0);
   }
  
   // Copy contents of first file to file4.txt
   while ((c = fgetc(fp1)) != EOF)
      fputc(c, fp4);
  
   // Copy contents of second file to file4.txt
   while ((c = fgetc(fp2)) != EOF)
      fputc(c, fp4);
      
   // Copy contents of third file to file4.txt
   while ((c = fgetc(fp3)) != EOF)
      fputc(c, fp4);
  
   printf("Merged Adminstaff.txt, Patient.txt and Doctor.txt into Clinic.txt");
  
   fclose(fp1);
   fclose(fp2);
   fclose(fp3);
   fclose(fp4);
   return 0;
}
