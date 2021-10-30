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
    #define TRUE 1
    #define FALSE 0


    /* STRUCTURE DEFINITIONS */

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
     * Stores information related to a doctor's information
    **/
    struct Doctor {
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
    struct MedicalRecord {
        Date_t dateOfEntry;
        char description[MAX_RECORD_DESCRIPTION_LENGTH];
    };
    typedef struct MedicalRecord MedicalRecord_t;

    /**
     * Author: Lawrence Fang
     * Stores information related to a patient's medical information
    **/
    struct PatientInfo {
        int userID;
        char bloodType[3];
        int primaryDoctorID;
    };
    typedef struct PatientInfo PatientInfo_t;

    /**
     * Author: Lawrence Fang
     * Stores information related to administrative staff
    **/
    struct AdminStaff {
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

    struct Clinic {
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


    /*Date Functions*/
    Date_t getDate();
    void printDate(Date_t date);
