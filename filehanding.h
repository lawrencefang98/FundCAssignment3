/*******************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Name:YiJiang Wang
 *******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*******************************************************************************
Function prototypes 
 Author: YIJIANG WANG
*******************************************************************************/
void saveAdminstaff(Clinic_t *clinic);
void saveDoctors(Clinic_t *clinic);
void savePatients(Clinic_t *clinic);
void saveUsers(Clinic_t *clinic);
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

void saveAdminstaff(Clinic_t *clinic)
{
	int numAdminStaff = clinic->adminStaffCount;
	FILE* file = fopen("Adminstaff.txt", "w");
	/*open file failed*/
	if (file == NULL)
	{
        printf("Save failed.\n");
        return;
	}
	/*write each adminstaffs*/
	fprintf(file, "Number of staff: %i\n", numAdminStaff);
	int i;
	for (i = 0; i < numAdminStaff; i++)
	{
		AdminStaff_t staffToPrint = clinic->adminStaffList[i];
		fprintf(file, "User ID: %i,", staffToPrint.userId);
		fprintf(file, "Staff ID: %i,", staffToPrint.staffId);
		fprintf(file, "Job Title: %s,", staffToPrint.jobTitle);
		fprintf(file, "Start Date: %i/%i/%i\n", staffToPrint.startDate.day, staffToPrint.startDate.month, staffToPrint.startDate.year);
    }
	fclose(file); /* close the file*/
}

/*******************************************************************************
 * This function save all doctors.
 * inputs:
 * - doctors: the array of all doctors
 * - numDoctor: the number of doctors
 * outputs:
 * - none
*******************************************************************************/

void saveDoctors(Clinic_t *clinic) {
    int numDoctor = clinic->doctorListCount;
	FILE* file = fopen("Doctor.txt", "w");
	/*open file failed*/
	if (file == NULL)
	{
		printf("Save failed.\n");
		return;
	}
	/*write each doctors*/
	int i;
	fprintf(file, "Number of Doctors: %d\n", numDoctor);
	for (i = 0; i < numDoctor; i++)
	{
		Doctor_t doctorToPrint = clinic->doctorList[i];
		fprintf(file, "User ID: %i,", doctorToPrint.userId);
		fprintf(file, "Doctor ID: %i,", doctorToPrint.doctorId);
		fprintf(file, "Start Date: %i/%i/%i\n", doctorToPrint.startDate.day, doctorToPrint.startDate.month, doctorToPrint.startDate.year);
	}
	fclose(file); /* close the file*/
}


/*******************************************************************************
 * This function save all patients.
 * inputs:
 * - patients: the array of all patients
 * - numPatient: the number of patients
 * outputs:
 * - none
*******************************************************************************/
void savePatients(Clinic_t *clinic)
{
    int numPatient = clinic->patientListCount;
	FILE* file = fopen("Patients.txt", "w");
	/*open file failed*/
	if (file == NULL)
	{
		printf("Save failed.\n");
		return;
	}
	/*write each patients*/
	int i;
	fprintf(file, "Number of patients: %d\n", numPatient);
	for (i = 0; i < numPatient; i++)
	{
		PatientInfo_t patientToPrint = clinic->patientList[i];
		fprintf(file, "User ID: %i,", patientToPrint.userID);
		fprintf(file, "Blood type: %s,", patientToPrint.bloodType);
		fprintf(file, "Primary Doctor ID: %i\n", patientToPrint.primaryDoctorID);
		
	}
	fclose(file); /* close the file*/
}

void saveUsers(Clinic_t *clinic)
{
    int numUsers = clinic->userListCount;
	FILE* file = fopen("Users.txt", "w");
	/*open file failed*/
	if (file == NULL)
	{
		printf("Save failed.\n");
		return;
	}
	/*write each users*/
	int i;
	fprintf(file, "Number of Users: %d\n", numUsers);
	for (i = 0; i < numUsers; i++)
	{
		User_t userToPrint = clinic->userList[i];
		fprintf(file, "User ID: %i,", userToPrint.userID);
		fprintf(file, "First Name: %s,", userToPrint.firstName);
		fprintf(file, "Last Name: %s,", userToPrint.firstName);
		fprintf(file, "Date of birth: %i/%i/%i,", userToPrint.dateOfBirth.day, userToPrint.dateOfBirth.month, userToPrint.dateOfBirth.year);
		fprintf(file, "Email: %s,", userToPrint.email);
		fprintf(file, "Address: %s,", userToPrint.address);
		fprintf(file, "Gender: %s\n", userToPrint.gender);
	}
	fclose(file); /* close the file*/
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
    scanf("%s", filename);
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
   /* Open four files to be merged */
   FILE *fp1 = fopen("Adminstaff.txt", "r");
   FILE *fp2 = fopen("Patients.txt", "r");
   FILE *fp3 = fopen("Doctor.txt", "r");
   FILE *fp4 = fopen("Users.txt", "r");
  
   /* Open files to store the result */
   FILE *fp5 = fopen("Clinic.txt", "w");
   char c;
  
   if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL || fp5 == NULL)
   {
         puts("Could not open files");
         return 1;
   }
  
   /* Copy contents of first file to file5.txt */
   while ((c = fgetc(fp1)) != EOF)
      fputc(c, fp5);
  
   /* Copy contents of second file to file5.txt */
   while ((c = fgetc(fp2)) != EOF)
      fputc(c, fp5);
      
   /* Copy contents of third file to file5.txt */
   while ((c = fgetc(fp3)) != EOF)
      fputc(c, fp5);
	
  /* Copy contents of fourth file to file5.txt */
  while ((c = fgetc(fp4)) != EOF)
      fputc(c, fp5);

   printf("Merged Adminstaff.txt, Patient.txt, Doctor.txt and Users.txt into Clinic.txt");
  
 /* close the file*/
   fclose(fp1);
   fclose(fp2);
   fclose(fp3);
   fclose(fp4);
   fclose(fp5); 
   return 0;
}











