
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                       PRE-PROCESSING DIRECTIVES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define MAX_FILE_NAME 30
#define MAX_PASS_SIZE 20
#define MAX_NAME_LENGTH 20

/* Variables - delete later */
int i;
int j;
int n;

char in_filename[];
char out_filename[];
char plaintext[];
int ciphertext[];
char decrypt[];

int key[];

char firstName[];
char lastName[];
char username[];
char password[];



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                           FUNCTION PROTOTYPES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: encryptMenu()          PURPOSE:  Prompts user for file encryption
 *
 * INPUT: File to be encrypted - plaintext
 * OUTPUT: Encrypted file - ciphertext
 *****************************************************************************/

void encryptMenu();


/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: decryptMenu()          PURPOSE: User prompts for decryption
 *
 * INPUT: File to be decrypted - ciphertext
 * OUTPUT: Decrypted file - plaintext
 *****************************************************************************/

void decryptMenu();


/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: encryptFile()              PURPOSE: Encrypt the plaintext file
 *
 * INPUT: plaintext file
 * OUTPUT: ciphertext file
 *****************************************************************************/

void encryptFile(char plaintext[], int ciphertext[], int key[]);


/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: decryptFile()              PURPOSE: Decrypts the ciphertext file
 *
 * INPUT: ciphertext file
 * OUTPUT: plaintext file
 *****************************************************************************/

void decryptFile(int ciphertext[], char decrypt[], int key[]);


/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: manageUser()          PURPOSE: Username and password management
 *
 * INPUT:   firstName[], lastname[], username[], password[]
 *              - Registering users --> void registerUser();
 *              - Deleting user and pass --> void deleteUser():
 *              - Changing user and pass --> void changeUser();
 *****************************************************************************/

void manageUser();
void registerUser();
void deleteUser();
void changeUser();


/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: validPass()            PURPOSE: Validates username + pass
 *
 * INPUT: username and password
 * OUTPUT:  - valid = continue to encryption/decryption
 *          -  invalid = exit/ prompt for valid credentials
 *****************************************************************************/

void validPass();
void checkAlpha(); /* passwords must include both char and int values */
void checkNum();


/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: readData()         PURPOSE: Calculate file char length --> 'n'
 *
 * INPUT: text file
 * OUTPUT: char total
 *****************************************************************************/

void readData(char plaintext[], int ciphertext[]);


/******************************************************************************
 * AUTHOR: Mandana Ebrahimian
 * FUNCTION: keygen();          PURPOSE: Generate random key of 'n' length
 *
 * INPUT: text file char length
 * OUTPUT: cipher key
 *****************************************************************************/

void keygen();

