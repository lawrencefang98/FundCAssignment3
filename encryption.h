/******************************************************************************
 *                          PREPROCESSOR DIRECTIVES                           *
 ******************************************************************************/

#define MAX_FILE_NAME 30
#define MAX_FILE_SIZE 1000
#define LOGIN_DB "login_database.txt"

#define MAX_PASS_LENGTH 20
#define MIN_PASS_LENGTH 8

#define MAX_ID_LENGTH 10
#define MAX_CLINIC_SIZE 50

#define BUF_SIZE 4096

/* Define boolean data type */
typedef int bool;
#define TRUE 1
#define FALSE 0

/******************************************************************************
 *                                 STRUCTURES                                 *
 ******************************************************************************/

typedef struct user {
    int userID[MAX_ID_LENGTH + 1];
    char password[MAX_PASS_LENGTH + 1];
} user_t;

/******************************************************************************
 *                      FUNCTION PROTOTYPES  |  PASSWORD                      *
 ******************************************************************************/

/* User Menu */
_Noreturn void loginMenu();
void printMenu();

/* Menu Options */
void loginUser(user_t accounts[], int* total_p);
void addUser(user_t accounts[], int* total_p);
void saveUser(user_t accounts[], int* total_p);
void deleteUser(user_t accounts[], int* total_p);

/* Validity Check */
bool checkChar(const char password[]);
bool checkPass(int pass_buff[11], user_t accounts[], int* total_p);
bool checkUser(int userID_buff[11], user_t accounts[], int* total_p);



/******************************************************************************
 *                     FUNCTION PROTOTYPES  |  ENCRYPTION                     *
 ******************************************************************************/

/* Menus */
void securityMenu();
void printSecurity();
void encryptMenu(char input_b[BUF_SIZE], char output_b[BUF_SIZE],
                 char key[MAX_PASS_LENGTH]);
void decryptMenu(char input_b[BUF_SIZE], char output_b[BUF_SIZE],
                 char key[MAX_PASS_LENGTH]);


/* Menu Options */
char readFile(char filename[], char input_b[BUF_SIZE]);

char encryptText(char plaintext_b[BUF_SIZE], char ciphertext_b[BUF_SIZE],
                 char key[MAX_PASS_LENGTH]);

char decryptText(char plaintext_b[BUF_SIZE], char ciphertext_b[BUF_SIZE],
                 char key[MAX_PASS_LENGTH]);

void writeFile(char filename[], char input_b[BUF_SIZE], 
               char output_b[BUF_SIZE]);

