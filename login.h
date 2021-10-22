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
    char userID[ID_LEN + 1];
    char password[MAX_PASS_LEN + 1];
} user_t;

/******************************************************************************
 *                            FUNCTION PROTOTYPES                             *
 ******************************************************************************/

/* User Menu */
_Noreturn void loginMenu();
void printMenu();

/* Menu Options */
void loginUser();
void addUser(user_t accounts[], int* total_p);
void saveUser(user_t accounts[], int* total_p);
void deleteUser(user_t accounts[], int* total_p);

/* Validity Check */
int checkChar(const char password[]);
int checkCharNum(const char password[]);
int checkSpace(const char password[]);
int checkPass(const char* pass);
int checkUser(const char* user);
