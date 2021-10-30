/******************************************************************************
 *                               HEADER GUARDS                                *
 ******************************************************************************/

#ifndef TEST_LOGIN_H
#define TEST_LOGIN_H

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
void loginMenu();
void printMenu();

/* Menu Options */
void loginUser(int* total_p);
void addUser(user_t accounts[], int* total_p);
void saveUser(user_t accounts[], int* total_p);

/* Validity Check */
int checkChar(const char password[]);
int checkCharNum(const char username[]);

/* Login Check */
int validCred(const char credentials[]);

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

void loginMenu()
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
            printMenu();
            scanf("%d", &choice);
        }

        else if (choice == 2)
        {
            addUser(accounts, total_p);
            printMenu();
            scanf("%d", &choice);
        }

        else if (choice == 3)
        {
            return;
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
    printf("\nLOGIN MENU | Enter your choice: ");
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
    /* Ignores spaces */
    char space;

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

        /* Debug: User already exists */
        printf("\nADD USER | Enter your employee ID: ");
        scanf("%c", &space); /* Reads all text (including spaces) */
        scanf("%[^\n]", accounts[i].username);

        while(validCred(accounts[i].username) > 0)
        {
            printf("\nERROR | Account already exists.\n");
            return;
        }

        /* Debug: Username may only include numeric characters */
        while(checkCharNum(accounts[i].username) == 0)
        {
            printf("ERROR | Your ID can only include numbers.\n");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].username);
            break;
        }

        /* Debug: User will be prompted to enter user ID with no spaces */
        while(strstr(accounts[i].username, " ") != NULL)
        {
            printf("ERROR | Your ID must not include spaces.\n");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].username);
            break;
        }

        while(strlen(accounts[i].username) > ID_LEN)
        {
            printf("ERROR | Your ID must not exceed 8 chars.\n");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].username);
            break;
        }

        while(strlen(accounts[i].username) < ID_LEN)
        {
            printf("ERROR | Your ID must not be less than 8 chars.\n");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].username);
            break;
        }

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *                        USER DATA: PASSWORD                        *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        printf("ADD USER | Enter your password: ");
        scanf("%c", &space); /* Reads all text (including spaces) */
        scanf("%[^\n]", accounts[i].password);

        /* Debug: User will be prompted to enter password with no spaces */
        while(strstr(accounts[i].password, " ") != NULL)
        {
            printf("\nERROR | Your password must not include spaces.\n");
            printf("\nADD USER | Enter your password: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].password);
            break;
        }

        /* Debug: User will be prompted to enter pass with no special chars */
        while(checkChar(accounts[i].password) == 0)
        {
            printf("\nERROR | Password can only = alphanumeric characters.\n");
            printf("ADD USER | Enter your password: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].password);
            break;
        }

        /* Debug: User will be prompted to enter pass > or == min characters */
        while(strlen(accounts[i].password) < MIN_PASS_LEN)
        {
            printf("\nERROR | Your password must be at least 8 characters.\n");
            printf("ADD USER | Enter your password: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].password);
            break;
        }

        /* Debug: User will be prompted to enter pass > max characters */
        while(strlen(accounts[i].password) > MAX_PASS_LEN)
        {
            printf("\nERROR | Your password must not exceed 20 characters.\n");
            printf("ADD USER | Enter your password: ");
            scanf("%c", &space); /* Reads all text (including spaces) */
            scanf("%[^\n]", accounts[i].password);
            break;
        }
    }

    else
    {
        printf("\nMaximum number of users reached.\n");
        --i;
    }

    ++i;

    /* '*total_p' updated with value of 'i' */
    *total_p = i;

    if(strcmp(accounts->username, "\0") != 0 &&
       strcmp(accounts->password, "\0") != 0)
    {
        /* User is saved to account file */
        saveUser(accounts, total_p);
    }
}


void saveUser(user_t accounts[], int* total_p)
{
    FILE * file_p = fopen(LOGIN_DB,"a");

    if(file_p != NULL)
    {
        int i = 0;

        while(i <= *total_p)
        {
            fprintf(file_p, "%-8s %-20s\n",
                    accounts[i].username,
                    accounts[i].password);
            i++;
        }
    }

    fclose(file_p);
}


int checkCharNum(const char username[])
{
    int i = 0;
    int j = 0;

    /*for(i = 0; i <= ID_LEN + 1; ++i)*/
    while(i <= ID_LEN + 1)
    {
        char ch = username[i++];

        if(ch >= '0' && ch <= '9')
            j++;

        else
            j = 0;
    }

    if(j > 0)
        return 1;

    else
        return 0;
}


int checkChar(const char password[])
{
    int i;

    /* String only contains alphanumeric characters */
    for(i = 0; i <= MAX_PASS_LEN + 1; i++)
    {
        char ch = password[i];

        if ((ch <= 'A' && ch >= 'Z') ||
            (ch <= 'a' && ch >= 'z') ||
            (ch <= '0' && ch >= '9'))
        {
            return 0;
        }

        else
           return 1;

    }

}


int validCred(const char credentials[])
{
    FILE *file_p = fopen(LOGIN_DB, "r");

    int i = 0; /* Counter variable for substring occurrences */

    char text_b[MAX_FILE_SZ + 1] = {'\0'}; /* Buffer for text file contents */

    if (file_p == NULL)
    {
        printf("ERROR | Read error.\n");
        exit(EXIT_FAILURE);
    }

    else
    {
        /* https://stackoverflow.com/questions/20253177/how-to-count-how-many-times-a-word-appears-in-a-txt-file*/
        while (fgets(text_b, MAX_FILE_SZ, file_p) != NULL)
        {
            char *ptr = text_b;

            while ((ptr = (strstr(ptr, credentials))) != NULL)
            {
                i++;
                ++ptr;
            }
        }
    }

    fclose(file_p);

    return i;
}



void loginUser(int* total_p)
{
    char space;

    /* Struct 'login' used for login input */
    user_t login;

    printf("\nLOGIN | User ID: ");
    scanf("%c", &space); /* Reads all text (including spaces) in a line */
    scanf("%[^\n]", login.username);

    printf("LOGIN | Password: ");
    scanf("%c", &space); /* Reads all text (including spaces) in a line */
    scanf("%[^\n]", login.password);

    if(total_p == 0)
    {
        printf("\nERROR | No accounts exist.\n");
        return;
    }

    else
    {
        if(validCred(login.username) == 1 && validCred(login.password) == 1)
        {
            printf("\n\n                LOGIN SUCCESSFUL                \n\n");

            cipherMenu();
        }


        /* Debug: User will be prompted to enter password with no spaces */
        else if(strstr(login.password, " ") != NULL)
        {
            printf("\nERROR | Your password must not include spaces.\n");
        }

        else if(checkCharNum(login.username) == 0)
        {
            printf("\nERROR | Your ID must only include numeric characters.\n");
        }

        /* Debug: User will be prompted to enter username with no spaces */
        else if(strstr(login.username, " ") != NULL)
        {
            printf("\nERROR | Your ID must not include spaces.\n");
        }

        else if(strcmp(login.username, "\0") == 0)
        {
            printf("\nERROR | Empty user ID.\n");
        }

        else if(strlen(login.username) < ID_LEN)
        {
            printf("\nERROR | User ID must not be less than 8 characters.\n");
        }

        else if(strlen(login.username) > ID_LEN)
        {
            printf("\nERROR | User ID must not exceed 8 characters.\n");
        }

        else if(strcmp(login.password, "\0") == 0)
        {
            printf("\nERROR | Empty password.\n");
        }

        else if(strlen(login.password) < MIN_PASS_LEN)
        {
            printf("\nERROR | Password must be at least 8 characters\n");
        }

        else if(strlen(login.password) > MAX_PASS_LEN)
        {
            printf("\nERROR | Password must not exceed 20 chars.\n");
        }

        else if(validCred(login.username) == 0 ||
                validCred(login.password) == 0)
        {
            printf("\nERROR | Incorrect username or password.\n");
            cipherMenu();
        }
    }
}

#endif /* TEST_LOGIN_H */
