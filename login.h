
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
_Noreturn void loginMenu();
void printMenu();

/* Menu Options */
void loginUser(int* total_p);
void addUser(user_t accounts[], int* total_p);
void saveUser(user_t accounts[], int* total_p);

/* Validity Check */
int checkChar(const char password[]);
int checkCharNum(const char password[]);
int checkSpace(const char password[]);

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
            exit(EXIT_SUCCESS);
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
    printf("\n  Press [1] to login to an account");
    printf("\n  Press [2] to create an account");
    printf("\n  Press [3] to exit the program");
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

        /* Debug: Username may only include numeric characters */
        while(checkCharNum(accounts[i].username) == 0)
        {
            printf("ERROR | Employee ID may only include numbers.");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%8s", accounts[i].username);
        }

        while(strlen(accounts[i].username) > ID_LEN)
        {
            printf("ERROR | Your ID must not be greater than 8 chars.");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%8s", accounts[i].username);
        }

        while(strlen(accounts[i].username) < ID_LEN)
        {
            printf("ERROR | Your ID must not be less than 8 chars.");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%8s", accounts[i].username);
        }

        while((checkSpace(accounts[i].username) == 1))
        {
            printf("ERROR | Your ID must not include spaces.");
            printf("\nADD USER | Enter your employee ID: ");
            scanf("%8s", accounts[i].username);
        }

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *                        USER DATA: PASSWORD                        *
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        printf("ADD USER | Enter your password: ");
        scanf("%20s", accounts[i].password);

        /* Debug: User will be prompted to enter pass with no special chars */
        while(checkChar(accounts[i].password) == 0)
        {
            printf("ERROR | You may only include alphanumeric characters");
            printf("ADD USER | Enter your password: ");
            scanf("%20s", accounts[i].password);
            break;
        }

        /* Debug: User will be prompted to enter pass with no spaces */
        while(checkSpace(accounts[i].password) == 1)
        {
            printf("ERROR | Your password must not contain spaces");
            printf("ADD USER | Enter your password: ");
            scanf("%20s", accounts[i].password);
            break;
        }

        /* Debug: User will be prompted to enter pass > or == min characters */
        while(strlen(accounts[i].password) < MIN_PASS_LEN)
        {
            printf("\nERROR | Your password must be at least 8 characters.\n");
            printf("ADD USER | Enter your password: ");
            scanf("%20s", accounts[i].password);
            break;
        }

        /* Debug: User will be prompted to enter pass > max characters */
        while(strlen(accounts[i].password) > MAX_PASS_LEN)
        {
            printf("\nERROR | Your password must not be greater than 20"
                   "characters.");
            printf("ADD USER | Enter your password: ");
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
    FILE * file_p = fopen(LOGIN_DB,"a+");

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

    if(username[i] >= '0' && username[i] <= '9')
        return 1;

    else
        return 0;
}


int checkChar(const char password[])
{
    int i = 0;

    /* String only contains alphanumeric characters */
    if((password[i] >= 'A' && password[i] <= 'Z') ||
       (password[i] >= 'a' && password[i] <= 'z') ||
       (password[i] >= '0' && password[i] <= '9'))
    {
        return 1;
    }

    else
        return 0;
}

int checkSpace(const char password[])
{
    int i = 0;

    if(password[i] == ' ') /* String has a space */
        return 1;

    else
        return 0;  /* String doesn't have a space */
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
        while(fgets(text_b, MAX_FILE_SZ, file_p) != NULL)
        {
            char* ptr = text_b;

            while((ptr = (strstr(ptr,credentials))) != NULL)
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
    /* Counter variable for failed password attempts */
    int j = 0;

    /* Struct 'login' used for login input */
    user_t login;

    printf("\nLOGIN | User ID: ");
    scanf("%10s", login.username);

    printf("LOGIN | Password: ");
    scanf("%s", login.password);

    if(total_p == 0)
    {
        printf("ERROR | No accounts exist.");
    }

    else
    {
        if(validCred(login.username) == 1 && validCred(login.password) == 1)
        {
            printf("\n\n                LOGIN SUCCESSFUL                \n\n");

            cipherMenu();
        }

        else
        {
            while(validCred(login.username) == 0 ||
                  validCred(login.password) == 0)
            {
                printf("\nERROR | Incorrect username or password.");
                j++;
                break;
            }

            while(strcmp(login.username, "\0") == 0)
            {
                printf("\nERROR | Empty user ID.");
                j++;
                break;

            }

            while(strlen(login.username) < ID_LEN)
            {
                printf("\nERROR | User ID must not be less than 8 characters.");
                j++;
                break;
            }

            while(strlen(login.username) > ID_LEN)
            {
                printf("\nERROR | User ID must not exceed 8 characters.");
                j++;
                break;
            }

            while(strcmp(login.password, "\0") == 0)
            {
                printf("\nERROR | Empty password.");
                j++;
                break;
            }

            while(strlen(login.password) < MAX_PASS_LEN)
            {
                printf("\nERROR | Password must be at least 8 characters\n");
                j++;
                break;
            }

            while(strlen(login.password) > MAX_PASS_LEN)
            {
                printf("\nERROR | Password must not exceed 20 chars.\n");
                j++;
                break;
            }

            if(j > 3)
            {
                printf("\nERROR | Too many password attempts.");
                /* return to main menu */
                exit(EXIT_FAILURE);
            }
        }
    }
}

#endif /* TEST_LOGIN_H */
