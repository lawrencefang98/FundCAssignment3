/******************************************************************************
 *                               HEADER GUARDS                                *
 ******************************************************************************/

#ifndef FINAL_AT3_LOGIN_H
#define FINAL_AT3_LOGIN_H

/******************************************************************************
 *                               HEADER FILES                                 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"

/******************************************************************************
 *                          PREPROCESSOR DIRECTIVES                           *
 ******************************************************************************/

#define MAX_FILE_NAME 30
#define MAX_FILE_SZ 1024
#define LOGIN_DB "login_database.txt"

#define MAX_PASS_LEN 20
#define MIN_PASS_LEN 8

#define ID_LEN 8
#define MAX_CLINIC_SZ 50
#define BUF_SIZE 4096

/******************************************************************************
 *                                 STRUCTURES                                 *
 ******************************************************************************/

typedef struct user {
    char username[ID_LEN + 1];
    char password[MAX_PASS_LEN + 1];
} user_t;

/******************************************************************************
 *                            FUNCTION PROTOTYPES                             *
 ******************************************************************************/

/* User Menu */
_Noreturn void loginMenu();
void printMenu();

/* Menu Options */
void loginUser(int* total_p);
void addUser(user_t accounts[], int* total_p);
void saveUser(user_t accounts[], int* total_p);
void deleteUser(user_t accounts[], int* total_p);

/* Validity Check */
int validCred(const char credentials[]);

/* Debugging */
int checkChar(const char string[]);
int checkCharNum(const char string[]);
int checkSpace(const char string[]);
int checkPeriod(const char string[]);

/******************************************************************************
 *                                FUNCTIONS                                   *
 ******************************************************************************/

/******************************************************************************
 *  AUTHOR: Mandana Ebrahimian
 *  FUNCTION: loginMenu()          PURPOSE: Executes the relevant functions
 *                                          based on user input.
 *
 *  INPUT: N/A
 *  OUTPUT: N/A
 *****************************************************************************/

_Noreturn void loginMenu()
{
    user_t accounts[MAX_CLINIC_SZ + 1] = {0};

    int choice = 0;

    int total = 0;
    int* total_p = &total;

    printMenu();
    scanf("%d", &choice);

    while(1)
    {
        if (choice == 1)
        {
            loginUser(total_p);
            printf("\n\n");
            printMenu();
            scanf("%d", &choice);
        }

        else if (choice == 2)
        {
            addUser(accounts, total_p);
            printf("\n\n");
            printMenu();
            scanf("%d", &choice);
        }

        else if (choice == 3)
        {
            exit(EXIT_SUCCESS);
        }

        else
        {
            printf("\nERROR | Invalid menu choice. Please try again.\n");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);
        }
    }
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: printMenu()          PURPOSE:  Prints the login menu
 *
 * INPUT: N/A
 * OUTPUT: N/A
 *****************************************************************************/

void printMenu()
{
    printf("\n                    LOGIN MENU                    ");
    printf("\n--------------------------------------------------");
    printf("\nPlease choose from the following options: ");
    printf("\n  1. Login to an account");
    printf("\n  2. Create an account");
    printf("\n  3. Exit the program");
    printf("\n\nEnter your choice: ");
}

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: printMenu()          PURPOSE:  Prints the login menu
 *
 * INPUT: N/A
 * OUTPUT: N/A
 *****************************************************************************/

void addUser(user_t accounts[], int* total_p)
{
    /* 'i' acts as a placeholder for *total_p */
    int i = *total_p;

    printf("\n\n");

    printf("\n                CREATE AN ACCOUNT                ");
    printf("\n--------------------------------------------------");

    /* Total users must not exceed the maximum clinic size */
    if(i <= MAX_CLINIC_SZ)
    {
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *                           USER DATA: ID                           *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        printf("\nADD USER | Enter your employee ID: ");
        scanf("%8s", accounts[i].username);

        if(validCred(accounts[i].username) > 1)
        {
            printf("ERROR | Account already exists.");
            exit(EXIT_FAILURE);
        }

        /* Debug: Username may only include numeric characters */
        while(checkCharNum(accounts[i].username) == 0)
        {
            printf("ERROR | Employee ID may only include numbers.");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%8s", accounts[i].username);
        }

        /* Debug: User will be prompted to enter user ID with no spaces */
        while(checkSpace(accounts[i].username) == 1)
        {
            printf("ERROR | Your employee ID not contain spaces.");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%20s", accounts[i].username);
            break;
        }

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *                        USER DATA: PASSWORD                        *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        printf("ADD USER | Enter your password: ");
        scanf("%20s", accounts[i].password);

        /* Debug: User will be prompted to enter pass with no special chars */
        while(checkChar(accounts[i].password) == 0)
        {
            printf("\nERROR | You may only include alphanumeric characters.");
            printf("\nADD USER | Enter your password: ");
            scanf("%20s", accounts[i].password);
            break;
        }

        /* Debug: User will be prompted to enter pass with no spaces */
        while(checkSpace(accounts[i].password) == 1)
        {
            printf("\nERROR | Your password must not contain spaces.");
            printf("\nADD USER | Enter your password: ");
            scanf("%20s", accounts[i].password);
            break;
        }

        /* Debug: User will be prompted to enter pass > or == min characters */
        while(strlen(accounts[i].password) < MIN_PASS_LEN)
        {
            printf("\nERROR | Your password must be at least 10 characters.\n");
            printf("\nADD USER | Enter your password: ");
            scanf("%20s", accounts[i].password);
            break;
        }

        /* Debug: User will be prompted to enter pass > max characters */
        while(strlen(accounts[i].password) > MAX_PASS_LEN)
        {
            printf("\nERROR | Your password must not be greater than 20"
                   "characters.");

            printf("\nADD USER | Enter your password: ");
            scanf("%20s", accounts[i].password);
            break;
        }
    }

    else
    {
        printf("Maximum number of users reached.\n");

        --i;
    }

    ++i;

    /* '*total_p' updated with value of 'i' */
    *total_p = i;

    /* User is saved to account file */
    saveUser(accounts, total_p);
}


void saveUser(user_t accounts[], int* total_p)
{
    FILE * file_p = fopen(LOGIN_DB,"w");
    rewind(file_p);
    file_p = fopen(LOGIN_DB,"a");

    if(file_p != NULL)
    {
        int i = 0;

        while(i <= *total_p)
        {
            fprintf(file_p, "%-8s %-20s\n",
                    accounts[i].username,
                    accounts[i].password);

            break;
        }

        fclose(file_p);
    }

    else
    {
        printf("ERROR | Read error.");
    }
}


int checkCharNum(const char string[])
{
    int i = 0;

    if(string[i] >= '0' && string[i] <= '9')
        return 1;

    else
        return 0;
}


int checkChar(const char string[])
{
    int i = 0;

    /* String only contains alphanumeric characters */
    if((string[i] >= 'A' && string[i] <= 'Z') ||
       (string[i] >= 'a' && string[i] <= 'z') ||
       (string[i] >= '0' && string[i] <= '9'))
    {
        return 1;
    }

    else
        return 0;
}

int checkSpace(const char string[])
{
    int i = 0;

    if(string[i] == ' ') /* String contains a space */
        return 1;

    else
        return 0;  /* String doesn't contain a space */
}

int checkPeriod(const char string[])
{
    int i = 0;

    if(string[i] == '.') /* String contains a period */
        return 1;

    else
        return 0;  /* String doesn't contain a period */
}

/* Read existing account information from file */
int validCred(const char credentials[])
{
    FILE *file_p = file_p = fopen(LOGIN_DB, "r");

    int i = 0; /* Counter variable for substring occurrences */

    char word[MAX_PASS_LEN + 1] = {'\0'};
    char text_b[MAX_FILE_SZ + 1] = {'\0'}; /* Buffer for text file contents */

    strcpy(word, credentials);

    if (file_p == NULL)
    {
        printf("ERROR | Read error.\n");
        exit(EXIT_FAILURE);
    }

    else
    {

        /* https://stackoverflow.com/questions/20253177/how-to-count-how-many-times-a-word-appears-in-a-txt-file*/
        while(fgets(text_b, MAX_FILE_SZ, file_p) != NULL)
        {
            char* ptr = text_b;

            while((ptr = (strstr(ptr,word))) != NULL)
            {
                i++;
                ++ptr;
            }
        }
    }

    return i;
}


void loginUser(int* total_p)
{
    int j = 0; /* Counter variable for failed password attempts */

    user_t login; /* Struct 'login' used for login input */

    if(total_p == 0)
    {
        printf("\nERROR | No user accounts exist.\n");
        loginMenu();
    }

    else
    {
        printf("\nLOGIN | User ID: ");
        scanf("%8s", login.username);

        printf("LOGIN | Password: ");
        scanf("%8s", login.password);

        if(validCred(login.username) == 1 && validCred(login.password) == 1)
        {
            printf("\n\n\n");
            printf("                LOGIN SUCCESSFUL                ");
            printf("\n\n\n");

            cipherMenu();
        }

        else
        {
            if(j > 2)
            {
                printf("\nERROR | Too many failed login attempts.\n");
                /* TODO: return to main menu */
                exit(EXIT_FAILURE);
            }

            while(validCred(login.username) == 0 ||
                  validCred(login.password) == 0)
            {
                printf("\nERROR | Invalid username or password.\n");
                j++;
                break;
            }

            while(checkCharNum(login.username) == 0)
            {
                printf("\nERROR | Your username may only include numeric "
                       "characters.\n");
                j++;
                break;
            }

            while(checkSpace(login.username) == 1 ||
                  checkSpace(login.username) == 1)
            {
                printf("\nERROR | Your credentials may not include spaces.\n");
                j++;
                break;
            }

            while(checkPeriod(login.username) == 1 ||
                  checkPeriod(login.username) == 1)
            {
                printf("\nERROR | Your credentials may not include spaces.\n");
                j++;
                break;
            }

            while(checkChar(login.password) == 0)
            {
                printf("\nERROR | Your password may only include alphanumeric "
                       "characters.\n");
                j++;
                break;
            }
        }
    }
}

#endif /* FINAL_AT3_LOGIN_H */
