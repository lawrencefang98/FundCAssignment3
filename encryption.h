/******************************************************************************
 *                          PREPROCESSOR DIRECTIVES                           *
 ******************************************************************************/

#define MAX_FILE_NAME 30
#define MAX_FILE_SZ 1024
#define LOGIN_DB "login_database.txt"

#define MAX_PASS_LEN 20
#define MIN_PASS_LEN 8

#define BUF_SIZE 4096

/******************************************************************************
 *                     FUNCTION PROTOTYPES  |  ENCRYPTION                     *
 ******************************************************************************/

/* Menus */
_Noreturn void securityMenu();
void printSecurity();
void encryptMenu(char input_b[], char output_b[], char key[]);
void decryptMenu(char input_b[], char output_b[], char key[]);

/* Menu Options */
char readFile(char filename[], char input_b[]);
void encryptDecrypt(char input_b[], char output_b[], char key[]);
void writeFile(char filename[], char input_b[], char output_b[]);

