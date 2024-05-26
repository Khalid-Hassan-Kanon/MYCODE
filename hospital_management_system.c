#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>   // Header for console input/output (specific to Windows)
#include <windows.h> // Header providing access to Windows API functions
#include <time.h>    // Header for time functions
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_LOGIN_LENGTH 50

#define MAX_PASSWORD_LENGTH 50

// Structure to hold information about a patient
typedef struct PatientInfo
{
    char full_name[50];     // Full name of the patient
    char date_of_birth[12]; // Date of birth of the patient (Format: YYYY-MM-DD)
    char phone_number[15];  // Phone number of the patient
    char doctor[50];        // Name of the doctor the patient needs an appointment with
    char gender;            // Gender of the patient ('M' for male, 'F' for female, 'O' for others)
    int serial;             // Unique serial number or ID assigned to the patient
    char confirmation[10];  // Confirmation status of the appointment or bed booking ('Confirmed', 'Pending', etc.)
    char app_date[12];
    char time[10];            // Appointment time
    char room[15];            // Room number
    char bed[15];             // Bed number
    struct PatientInfo *next; // Pointer to the next PatientInfo structure in a linked list
} PatientInfo;
typedef struct Bloodinfo
{
    char Donar_name[50];
    char contact_no[25];
    char group[50];
    struct Bloodinfo *next;
} Bloodinfo;

Bloodinfo *first_blood = NULL; // global pointer for link list used in bloodbamk

typedef struct Doctor
{
    char Name[100];
    char Dept[100];
    char contact[50];
    char salary[25];
    char id[5];
    struct Doctor *newdoc;
} Docinifo;
Docinifo *first_doc = NULL; // global pointer for link list used in Doctor's list

#define MAX_NAME_LENGTH 50
#define MAX_NUMBER_LENGTH 20

typedef struct EmergencyContact
{
    char name[MAX_NAME_LENGTH];
    char number[MAX_NUMBER_LENGTH];
    struct EmergencyContact *next;
} EmergencyContact;
EmergencyContact *emergencyContacts = NULL;
//----------------------------------------This function is responsible for handling the patient appointment process---------------------------------------
int appointment(PatientInfo **first_PatientInfo, FILE *file_ptr);

//---------------------------------------- This function displays a confirmation message----------------------------------------------------------
void confirmation();

//---------------------------------------- This function displays a confirmation message for bed appointments----------------------------------------------------------
void confirmation_bed(const char *filename);

//---------------------------------------- This function is used to handle the admin access functionality---------------------------------------
int adminAccess(FILE *file_ptr);

//---------------------------------------- This function is used to display the hospital information---------------------------------------
int information();

//---------------------------------------- This function is used to handle password authentication---------------------------------------
// int PASSWORD();

//---------------------------------------- This function displays a waiting message---------------------------------------
void waiting();

//---------------------------------------- This function is used to add a new patient's information to the system---------------------------------------
int add_patientinfo(PatientInfo **first_PatientInfo, FILE *file_ptr);

//----------------------------------------This function is used to free the memory occupied by the linked list of patient records.---------------------------------------
void freeLinkedList(PatientInfo *head);

//----------------------------------------This function is used to read the patient data from a file and display it.---------------------------------------
void readFromFile(const char *filename, int choice);

//----------------------------------------This function is used to confirm appointments or bed bookings.---------------------------------------
void Confirm_appointment_bed(const char *filename, int choice);

//----------------------------------------This function is used to delete a patient's information from the system.---------------------------------------
void deletePatient(int id);

//----------------------------------------This function displays guidelines for adding patient information.---------------------------------------

void PatientGuideline();
//----------------------------------This function prompts the user for a password without echoing it to the console.----------
void getPassword(char *password);

//---------------------------------------------------This function adds blood to the blood bank.-----------------------------------------
void Addblood();

//--------------------------------------------------This function takes blood from the blood bank.--------------------------------------
void TakeBlood();

//---------------------This function checks if the input password matches the actual password.-----------------
bool checkPassword(const char *inputPassword);

//---------------------------------------------This function displays the status of the blood bank.----------------------------------
void showbloodbank();

//----------------------------------------------This function authenticates a user before granting access to certain functionalities.
bool authenticate();

//-------------------------------------------------This function displays information about doctors.-----------------------------------
void ShowDoctors(int choise);

//---------------------------------------------------This function manages blood bank operations.---------------------------------------
void Bloddbank();

void Doctors(); // Declaration for the main menu function

void Display_donor(); // Declaration for displaying donor information

void AddDoctor(); // Declaration for adding a new doctor

void SearchPatients(const char *filename); // Declaration for searching patients in a file

// Function to save emergency contacts to a file
void saveEmergencyContactsToFile(const char *filename);

// Function to delete an emergency contact by name
void deleteEmergencyContactFromFile(const char *nameToDelete);

// Function to display all emergency contacts
void displayEmergencyContactsFromFile();

// Function to add a new emergency contact
void addEmergencyContactToFile();

void EmergencyContacts(); // Function to handle emergency contacts

void doc_Patient(); // Function to display patient information based on doctor's name

// Helper function to compare two strings in a case-insensitive manner
// Returns 1 if strings are equal (ignoring case), otherwise returns 0
int compareCaseInsensitive(const char *str1, const char *str2);

// Helper function to convert a string to lowercase
void toLowerString(char *str);

void clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    // Assume POSIX compliant system (Linux, macOS)
    printf("\033[H\033[J"); // ANSI escape code to clear screen
#endif
}

void pressEnterToContinue()
{
    printf("\n\t\t\t\tPress Enter to continue...");
    while (getchar() != '\n')
        ;      // Clear input buffer
    getchar(); // Wait for Enter
}

int main()
{
    int re;
    char choice;
    PatientInfo *first_PatientInfo = NULL;
    FILE *file_ptr = NULL;

    while (1)
    {
        clearScreen();

        printf("\n\n\n");
        printf("\n\n\n"); // Add spacing for better alignment
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t#               MAIN MENU                       #\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t#  ENTER 1 FOR ADMIN ACCESS                     #\n\n");
        printf("\t\t\t\t\t\t#  ENTER 2 FOR APPOINTMENT                      #\n\n");
        printf("\t\t\t\t\t\t#  ENTER 3 FOR MORE INFORMATION                 #\n\n");
        printf("\t\t\t\t\t\t#  ENTER 0 FOR EXIT                             #\n\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n\n");
        printf("\t\t\t\t\t\tENTER Your choice: "); // Prompt for user input

        scanf(" %c", &choice); // Note the space before %c to consume whitespace

        switch (choice)
        {
        case '1':

            if (authenticate())
            {
                adminAccess(file_ptr); // Call adminAccess function
            }
            break;
        case '2':
            appointment(&first_PatientInfo, file_ptr);
            break;
        case '3':
            information();
            break;
        case '0':
            printf("\t\t\t\t\t\t---------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t|               Exiting the program. Goodbye!                       |\n");
            printf("\t\t\t\t\t\t---------------------------------------------------------------------\n");

            freeLinkedList(first_PatientInfo);
            if (file_ptr != NULL)
                fclose(file_ptr);
            exit(0);
        default:
            printf("\t\t\t\tInvalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

/**
 * @brief Handles the patient appointment process.
 *
 * This function presents a menu for various appointment-related actions such as
 * new patient registration, confirmation viewing, bed booking, and displaying
 * patient guidelines. It continuously prompts the user for input until the
 * user chooses to return to the main menu.
 *
 * @param first_PatientInfo Pointer to the pointer of the first PatientInfo node in the linked list.
 * @param file_ptr Pointer to the file where patient information is stored.
 * @return Returns 0 when the function completes execution.
 */
int appointment(PatientInfo **first_PatientInfo, FILE *file_ptr)
{
    clearScreen(); // Clears the screen before displaying the menu
    int choice;    // Variable to store the user's choice

    // Loop to display appointment menu and handle user input
    while (1)
    {
        // Display appointment menu
        printf("\t\t\t\t\t\t--------------------------------------------------\n");
        printf("\t\t\t\t\t\t|           Appointment     MENU                 |\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t| 1. New Patient Registration                    |\n\n");
        printf("\t\t\t\t\t\t| 2. To See Confirmation                         |\n\n");
        printf("\t\t\t\t\t\t| 3. Booking Bed                                 |\n\n");
        printf("\t\t\t\t\t\t| 4. Patient Guideline                           |\n\n");
        printf("\t\t\t\t\t\t| 0. Back to Main Menu                           |\n\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n\n");

        // Prompt for user input
        printf("Enter your choice: ");
        // Validate user input for non-integer values
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n')
                ;     // Clear input buffer
            continue; // Continue to the beginning of the loop
        }

        // Switch case to handle user choice
        switch (choice)
        {
        case 1:
            clearScreen();                                // Clears the screen before adding new patient info
            add_patientinfo(first_PatientInfo, file_ptr); // Calls function to add new patient info
            break;
        case 2:
            clearScreen();  // Clears the screen before displaying confirmation
            confirmation(); // Calls function to display confirmation
            break;
        case 3:
            clearScreen();                        // Clears the screen before booking bed
            confirmation_bed("patient_info.bin"); // Calls function to book bed
            break;
        case 4:
            clearScreen();      // Clears the screen before displaying patient guidelines
            PatientGuideline(); // Calls function to display patient guidelines
            pressEnterToContinue();
            clearScreen();
            break;
        case 0:

            clearScreen(); // Clears the screen before returning to main menu
            return 0;      // Returns 0 to indicate successful completion of the function
        default:
            printf("Invalid choice!\n"); // Prints error message for invalid choice
        }
    }

    return 0; // Returns 0 when the function completes execution
}

/**
 * @brief Displays confirmation details for either bed or appointment.
 *
 * This function prompts the user to choose between confirmation for bed or appointment,
 * then displays the corresponding details of the patient's information. It reads data
 * from the "patient_info.bin" file.
 */
void confirmation()
{
    // Display options for confirmation
    printf("\n\n\n");

    printf("\t\t\t\t\t\t-------------------------------------------------\n");
    printf("\t\t\t\t\t\t|               Emergency Number Management     |\n");
    printf("\t\t\t\t\t\t-------------------------------------------------\n");
    printf("\t\t\t\t\t\t| 1. Confirmation for Bed                        |\n\n");
    printf("\t\t\t\t\t\t| 2. Confirmation for appointment                |\n\n");
    printf("\t\t\t\t\t\t| 0. Exit                                        |\n\n");
    printf("\t\t\t\t\t\t-------------------------------------------------\n");
    int choise;
    printf("\t\t\t\t\t\tEnter choice: ");
    scanf("%d", &choise); // Read user's choice

    FILE *file_ptr = fopen("patient_info.bin", "rb"); // Open the file for reading

    if (file_ptr == NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }
    if (choise == 0)
    {
        fclose(file_ptr); // Close the file
        clearScreen();
        return;
    }
    int id;
    printf("Enter ID: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input for ID.\n");
        fclose(file_ptr);
        return;
    }
    clearScreen();
    PatientInfo patient;
    int found = 0;
    // Loop to search for patient information in the file
    while (fread(&patient, sizeof(PatientInfo), 1, file_ptr) == 1)
    {
        if (id == patient.serial)
        {
            // Display confirmation details based on user's choice
            if (choise == 1)
            {
                // Display bed confirmation details
                printf("\t\t\t\t\t----------------------------------------\n");
                printf("\t\t\t\t\t| Name:           %-20s|\n", patient.full_name);
                printf("\t\t\t\t\t| Date of Birth:  %-20s|\n", patient.date_of_birth);
                printf("\t\t\t\t\t| Phone Number:   %-20s|\n", patient.phone_number);
                printf("\t\t\t\t\t| Doctor:         %-20s|\n", patient.doctor);
                printf("\t\t\t\t\t| Gender:         %-20c|\n", patient.gender);
                printf("\t\t\t\t\t| ID:             %-20d|\n", patient.serial);
                printf("\t\t\t\t\t| Room Number:    %-20s|\n", patient.room);
                printf("\t\t\t\t\t| Bed Number:     %-20s|\n", patient.bed);
                printf("\t\t\t\t\t----------------------------------------\n");
                found = 1;

                break; // Stop searching after finding the patient
            }
            else if (choise == 2)
            {
                // Display appointment confirmation details
                printf("\t\t\t\t\t----------------------------------------\n");
                printf("\t\t\t\t\t| Name:           %-20s|\n", patient.full_name);
                printf("\t\t\t\t\t| Date of Birth:  %-20s|\n", patient.date_of_birth);
                printf("\t\t\t\t\t| Phone Number:   %-20s|\n", patient.phone_number);
                printf("\t\t\t\t\t| Doctor:         %-20s|\n", patient.doctor);
                printf("\t\t\t\t\t| Gender:         %-20c|\n", patient.gender);
                printf("\t\t\t\t\t| ID:             %-20d|\n", patient.serial);
                printf("\t\t\t\t\t| Confirmation:   %-20s|\n", patient.confirmation);
                printf("\t\t\t\t\t| Time:           %-20s|\n", patient.time);
                printf("\t\t\t\t\t| Date:           %-20s|\n", patient.app_date);
                printf("\t\t\t\t\t----------------------------------------\n");
                found = 1;

                break; // Stop searching after finding the patient
            }
        }
    }

    // Display message if patient not found
    if (!found)
    {
        printf("Patient with ID %d not found.\n", id);
    }

    fclose(file_ptr);       // Close the file
    pressEnterToContinue(); // Prompt user to press Enter to continue
    clearScreen();          // Clear the screen
}

/**
 * @brief Handles the admin access functionality.
 *
 * This function displays a menu for administrative tasks such as appointing patient bed/appointment,
 * displaying patient information, managing doctors, removing patient information, making a bill,
 * and updating the blood bank. It reads and writes data to the "patient_info.bin" file.
 *
 * @param file_ptr Pointer to the file for patient information.
 * @return Returns 0 upon successful completion.
 */
int adminAccess(FILE *file_ptr)
{
    clearScreen();                               // Clear the screen
    int choice, re;                              // Declare variables for user choice and return value
    file_ptr = fopen("patient_info.bin", "ab+"); // Open the file for reading and writing

    if (file_ptr == NULL)
    {
        printf("Unable to open file patient_info.bin\n"); // Display error message if file cannot be opened
        return 1;                                         // Return 1 to indicate failure
    }

    while (1)
    {
        printf("\n\n\n"); // Add spacing for better alignment
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t|               MAIN MENU                        |\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t| Enter 1 to Appoint Patient Bed / Appointment   |\n\n");
        printf("\t\t\t\t\t\t| Enter 2 to Display All Patients Information    |\n\n");
        printf("\t\t\t\t\t\t| Enter 3 for Search Patients By Serial Number   |\n\n");
        printf("\t\t\t\t\t\t| Enter 4 for DOCTOR Management                  |\n\n");
        printf("\t\t\t\t\t\t| Enter 5 to Remove Patients Information         |\n\n");
        printf("\t\t\t\t\t\t| Enter 6 to Make a Bill                         |\n\n");
        printf("\t\t\t\t\t\t| Enter 7 For Blood Bank                         |\n\n");
        printf("\t\t\t\t\t\t| Enter 8 For Emergency Number Management        |\n\n");
        printf("\t\t\t\t\t\t| Enter 0 to EXIT                                |\n\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n\n");
        printf("\t\t\t\tENTER Your choice: "); // Prompt for user input
        if (scanf("%d", &choice) != 1)
        {
            // If user enters non-integer input
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n')
                ;     // Clear input buffer
            continue; // Continue to the beginning of the loop
        }

        switch (choice)
        {
        case 1:
            readFromFile("patient_info.bin", choice); // Read and display patient information
            clearScreen();                            // Clear the screen
            break;
        case 2:
            readFromFile("patient_info.bin", choice); // Read and display patient information
            clearScreen();                            // Clear the screen
            break;
        case 3:
            SearchPatients("patient_info.bin");
            break;
        case 4:
            Doctors();
            break;
        case 5:
            readFromFile("patient_info.bin", choice);
            int deleteId;
            printf("Enter the ID of the patient you want to delete: "); // Prompt user to enter patient ID for deletion
            scanf("%d", &deleteId);                                     // Read patient ID from user input
            deletePatient(deleteId);                                    // Call function to delete patient information
            clearScreen();                                              // Clear the screen
            break;
        case 6:
            // Handle case 5
            break;
        case 7:
            Bloddbank();
            break;
        case 8:
            EmergencyContacts();
            break;
        case 0:
            fclose(file_ptr);
            clearScreen(); // Clear the screen
            return 0;      // Return 0 to indicate successful completion

        default:
            printf("\t\t\t\tInvalid choice. Please enter a valid option.\n"); // Display message for invalid input
        }
    }
}

int information()
{
    while (1)
    {
        clearScreen();
        printf("\n\n\n");
        printf("\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t|               MORE INFORMATION MENU           |\n");
        printf("\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t| 1. Available Doctors                          |\n\n");
        printf("\t\t\t\t\t| 2. Available Blood                            |\n\n");
        printf("\t\t\t\t\t| 3. Emergency Number                           |\n\n");
        printf("\t\t\t\t\t| 0. Back to Main Menu                          |\n\n");
        printf("\t\t\t\t\t-------------------------------------------------\n\n");

        int choice;
        printf("\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            ShowDoctors(choice);
            break;
        case 2:
            showbloodbank();
            break;
        case 3:
            displayEmergencyContactsFromFile();
            pressEnterToContinue();
            clearScreen();
            break;
        case 0:
            clearScreen();
            return 0;
        default:
            printf("\t\t\t\tInvalid choice. Please enter a valid option.\n");
            break;
        }
    }
}

void getPassword(char *password)
{
    int i = 0;
    char ch;

    printf("Enter a password: ");
    while (1)
    {
        ch = getch();
        if (ch == 13)
        { // Enter key pressed
            password[i] = '\0';
            break;
        }
        else if (ch == 8 && i > 0)
        {
            printf("\b \b"); // Erase the last asterisk
            i--;
        }
        else if (i < MAX_PASSWORD_LENGTH - 1)
        {
            password[i++] = ch;
            printf("*");
        }
    }
}

bool checkPassword(const char *inputPassword)
{
    time_t currentTime;
    struct tm *localTime;

    // Get the current time
    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    // Format the current time without seconds
    char actualPassword[MAX_PASSWORD_LENGTH];
    // strftime(actualPassword, sizeof(actualPassword), "%a %b %d %I:%M %p %Y", localTime);
    strftime(actualPassword, sizeof(actualPassword), "%Y", localTime);
    // Print the formatted current time
    printf("%s\n", actualPassword);

    // Compare input password with the actual password
    return strcmp(actualPassword, inputPassword) == 0;
}
// Wed May 08 09:30 PM 2024
bool authenticate()
{
    char password[MAX_PASSWORD_LENGTH];
    getPassword(password);

    // Clear input buffer
    while (getchar() != '\n')
        ;

    if (strlen(password) < 1)
    {
        puts("\nPassword cannot be empty.");
        return false;
    }

    if (!checkPassword(password))
    {
        clearScreen();
        puts("\n\n\n\t\t\t\t\t\t#################################################");
        puts("\t\t\t\t\t\t#               ACCESS DENIED                   #");
        puts("\t\t\t\t\t\t#               ACCESS DENIED                   #");
        puts("\t\t\t\t\t\t#################################################\n\n");
        waiting();
        return false;
    }
    else
    {
        clearScreen();
        puts("\n\n\n\t\t\t\t\t\t#################################################");
        puts("\t\t\t\t\t\t#               ACCESS GRANTED                  #");
        puts("\t\t\t\t\t\t#               ACCESS GRANTED                  #");
        puts("\t\t\t\t\t\t#################################################\n\n");
        waiting();
        return true;
    }
}

void waiting()
{

    int i = 0;
    printf("\t\t\t\t\t Please wait   "); // Add spacing for the pattern
    for (int i = 0; i < 7; i++)
    {                // Loop 10 times
        printf("*"); // Print a dot
        Sleep(150);  // Sleep for another 100 milliseconds
    }
}

/**
 * @brief Adds a new patient's information to the system.
 *
 * This function prompts the user to input various details of a new patient,
 * validates the input, and adds the patient's information to the system.
 * It also writes the patient's information to the "patient_info.bin" file.
 *
 * @param first_PatientInfo Pointer to the pointer of the first node in the linked list of patient records.
 * @param file_ptr Pointer to the file for patient information.
 * @return Returns 1 upon successful addition of patient information.
 */
int add_patientinfo(PatientInfo **first_PatientInfo, FILE *file_ptr)
{
    file_ptr = fopen("patient_info.bin", "ab+"); // Open the file for reading and appending
    if (file_ptr == NULL)
    {
        printf("Failed to create file.\n"); // Display error message if file cannot be created
        return 0;                           // Exit with error
    }

    while (1)
    {
        PatientInfo *new_Patient = (PatientInfo *)malloc(sizeof(PatientInfo)); // Allocate memory for new patient
        if (new_Patient == NULL)
        {
            printf("Memory allocation failed.\n"); // Display error message if memory allocation fails
            return 0;                              // Exit with error
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ; // Clear input buffer

        printf("\t\tENTER YOUR FULL NAME: ");
        fgets(new_Patient->full_name, 50, stdin);                             // Input patient's full name
        new_Patient->full_name[strcspn(new_Patient->full_name, "\n")] = '\0'; // Remove newline

        printf("\t\tENTER YOUR DATE OF BIRTH (Format: YYYY-MM-DD): ");
        fgets(new_Patient->date_of_birth, 12, stdin);                                 // Input patient's date of birth
        new_Patient->date_of_birth[strcspn(new_Patient->date_of_birth, "\n")] = '\0'; // Remove newline

        printf("\t\tENTER YOUR PHONE NUMBER: ");
        fgets(new_Patient->phone_number, 15, stdin);                                // Input patient's phone number
        new_Patient->phone_number[strcspn(new_Patient->phone_number, "\n")] = '\0'; // Remove newline

        printf("\t\tENTER THE NAME OF THE DOCTOR YOU NEED AN APPOINTMENT WITH: ");
        fgets(new_Patient->doctor, 50, stdin);                          // Input doctor's name for appointment
        new_Patient->doctor[strcspn(new_Patient->doctor, "\n")] = '\0'; // Remove newline

        printf("\t\tENTER YOUR GENDER: (M/F/O(Others)): ");
        scanf(" %c", &new_Patient->gender); // Input patient's gender
        srand(time(NULL));

        // Generate a random serial number for the patient
        new_Patient->serial = rand() % 1000;
        strcpy(new_Patient->confirmation, "Pending"); // Set confirmation status to Pending
        strcpy(new_Patient->app_date, "Pending");
        strcpy(new_Patient->time, "\0"); // Initialize appointment time
        strcpy(new_Patient->room, "\0"); // Initialize room number
        strcpy(new_Patient->bed, "\0");  // Initialize bed number
        new_Patient->next = NULL;        // Set next pointer to NULL

        printf("\n\t\tConfirm with 'O' or cancel with 'C'.");
        char choice;
        if (scanf(" %c", &choice) == 1)
        {
            if (choice == 'C' || choice == 'c')
            {
                printf("Your appointment has been canceled\n");
                pressEnterToContinue();
                free(new_Patient); // Free memory if user chooses to cancel
                clearScreen();     // Clear the screen
                return 0;
            }
            else if (choice == 'O' || choice == 'o')
            {
                // Process the entry
                if (*first_PatientInfo == NULL)
                {
                    *first_PatientInfo = new_Patient; // Update pointer if list is empty
                }
                else
                {
                    // Traverse the list to find the last node and append the new node
                    PatientInfo *temp = *first_PatientInfo;
                    while (temp->next != NULL)
                    {
                        temp = temp->next;
                    }
                    temp->next = new_Patient;
                }

                // Write patient's information to file
                fwrite(new_Patient, sizeof(PatientInfo), 1, file_ptr);
                clearScreen(); // Clear the screen
                // Display confirmation message with patient's details
                printf("\t\t\t\t\t| Name:           %-20s|\n", new_Patient->full_name);
                printf("\t\t\t\t\t| Date of Birth:  %-20s|\n", new_Patient->date_of_birth);
                printf("\t\t\t\t\t| Phone Number:   %-20s|\n", new_Patient->phone_number);
                printf("\t\t\t\t\t| Doctor:         %-20s|\n", new_Patient->doctor);
                printf("\t\t\t\t\t| Gender:         %-20c|\n", new_Patient->gender);
                printf("\t\t\t\t\t| ID:             %-20d|\n", new_Patient->serial);
                printf("\t\t\t\t\t| Confirmation:   %-20s|\n", new_Patient->confirmation);
                printf("\n\t\t\t\t\tPlease wait for confirmation...\n");
                fclose(file_ptr);       // Close the file after writing
                pressEnterToContinue(); // Wait for user input
                clearScreen();          // Clear the screen
            }
            else
            {
                printf("Invalid choice. Please enter 'O' to confirm or 'C' to change/cancel.\n"); // Display error message for invalid input
                free(new_Patient);                                                                // Free memory
                continue;                                                                         // Restart the loop
            }
        }

        break; // Exit the loop if input is processed successfully
    }

    return 1; // Return 1 upon successful addition of patient information
}

/**
 * @brief Confirms the appointment or bed for a patient.
 *
 * This function allows confirming either a bed or an appointment for a patient.
 * It prompts the user to enter the patient's ID and the necessary details based on the choice.
 * It then updates the patient's information in the file with the confirmation details.
 *
 * @param filename The name of the file containing patient information.
 * @param choice The choice indicating whether to confirm bed (1) or appointment (2).
 */
void Confirm_appointment_bed(const char *filename, int choice)
{
    FILE *file = fopen(filename, "rb+"); // Open the file for reading and writing
    if (file == NULL)
    {
        printf("Unable to open file %s\n", filename); // Display error message if file cannot be opened
        return;
    }

    int id;
    printf("Enter patient ID: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input for patient ID.\n"); // Display error message for invalid input
        fclose(file);                              // Close the file
        return;
    }

    PatientInfo patient;
    int found = 0; // Flag to indicate if patient is found

    while (fread(&patient, sizeof(PatientInfo), 1, file) == 1)
    {
        if (id == patient.serial)
        {
            found = 1; // Patient found

            if (choice == 1)
            {
                printf("Enter Room Number: ");
                getchar();                                        // Consume newline character left in buffer
                fgets(patient.room, sizeof(patient.room), stdin); // Input room number
                patient.room[strcspn(patient.room, "\n")] = '\0'; // Remove newline
                printf("Enter Bed Number: ");
                fgets(patient.bed, sizeof(patient.bed), stdin); // Input bed number
                patient.bed[strcspn(patient.bed, "\n")] = '\0'; // Remove newline
                printf("Bed confirmed.\n");
            }
            else if (choice == 2)
            {
                printf("Enter Appointment Time (HOUR:MIN): ");
                scanf("%s", patient.time); // Input appointment time
                printf("Enter Appointment Date(yy-mm-dd): ");
                scanf("%s", patient.app_date);             // Input appointment time
                strcpy(patient.confirmation, "Confirmed"); // Set confirmation status to Confirmed
                printf("Appointment confirmed.\n");
            }

            // Move the file pointer back to the beginning of the current record
            fseek(file, -sizeof(PatientInfo), SEEK_CUR);

            // Write the updated patient data
            fwrite(&patient, sizeof(PatientInfo), 1, file);

            break; // Exit loop after confirming appointment/bed
        }
    }

    if (!found)
    {
        printf("Patient with ID %d not found.\n", id); // Display error message if patient not found
    }

    fclose(file); // Close the file
}

/**
 * @brief Reads patient information from the file and displays it.
 *
 * This function reads patient information from the file specified by `filename`
 * and displays it on the screen. It also provides an option to confirm bed or appointment.
 *
 * @param filename The name of the file containing patient information.
 * @param choice The choice indicating whether to confirm bed (1) or appointment (2).
 */
void readFromFile(const char *filename, int choice)
{

    clearScreen();                           // Clear the screen
    FILE *file_ptr = fopen(filename, "rb+"); // Open the file for reading and writing

    if (file_ptr == NULL)
    {
        printf("File cannot be open!\n"); // Display error message if file cannot be opened
        return;
    }

    printf("Patient List:\n");
    PatientInfo patient;

    // Read data until the end of the file
    while (fread(&patient, sizeof(PatientInfo), 1, file_ptr) == 1)
    {
        // Display patient information
        printf("\t\t\t\t\t----------------------------------------\n");
        printf("\t\t\t\t\t| Name:           %-20s|\n", patient.full_name);
        printf("\t\t\t\t\t| Date of Birth:  %-20s|\n", patient.date_of_birth);
        printf("\t\t\t\t\t| Phone Number:   %-20s|\n", patient.phone_number);
        printf("\t\t\t\t\t| Doctor:         %-20s|\n", patient.doctor);
        printf("\t\t\t\t\t| Gender:         %-20c|\n", patient.gender);
        printf("\t\t\t\t\t| ID:             %-20d|\n", patient.serial);
        printf("\t\t\t\t\t| Confirmation:   %-20s|\n", patient.confirmation);
        printf("\t\t\t\t\t| Date:           %-20s|\n", patient.app_date);
        printf("\t\t\t\t\t| Time:           %-20s|\n", patient.time);
        printf("\t\t\t\t\t| Room Number:    %-20s|\n", patient.room);
        printf("\t\t\t\t\t| Bed Number:     %-20s|\n", patient.bed);
        printf("\t\t\t\t\t-------------------------------------\n");
    }

    fclose(file_ptr); // Close the file

    if (choice == 1)
    {
        int choice2;
        printf("\n\n\n");

        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t|               Emergency Number Management     |\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t| 1. To Confirm Bed                             |\n\n");
        printf("\t\t\t\t\t\t| 2. To Confirm appointment                     |\n\n");
        printf("\t\t\t\t\t\t| 0. Exit                                       |\n\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
        if (scanf("%d", &choice2) == 1)
        {
            if (choice2 == 0)
            {
                return;
            }
            Confirm_appointment_bed(filename, choice2); // Confirm bed or appointment based on choice
        }
    }
    if (choice != 5)
    {
        pressEnterToContinue(); // Prompt to press enter to continue
        clearScreen();          // Clear the screen
    }
    return;
}

void SearchPatients(const char *filename)
{
    clearScreen(); // Clear the screen

    FILE *file_ptr = fopen(filename, "rb+"); // Open the file for reading and writing

    if (file_ptr == NULL)
    {
        printf("File cannot be open!\n"); // Display error message if file cannot be opened
        return;
    }

    PatientInfo patient;
    int p_id, found = 0;
    printf("Enter Patient Serial Number\n");
    scanf("%d", &p_id);
    // Read data until the end of the file
    while (fread(&patient, sizeof(PatientInfo), 1, file_ptr) == 1)
    {
        if (patient.serial == p_id)
        {
            // Display patient information
            printf("\t\t\t\t\t----------------------------------------\n");
            printf("\t\t\t\t\t| Name:           %-20s|\n", patient.full_name);
            printf("\t\t\t\t\t| Date of Birth:  %-20s|\n", patient.date_of_birth);
            printf("\t\t\t\t\t| Phone Number:   %-20s|\n", patient.phone_number);
            printf("\t\t\t\t\t| Doctor:         %-20s|\n", patient.doctor);
            printf("\t\t\t\t\t| Gender:         %-20c|\n", patient.gender);
            printf("\t\t\t\t\t| ID:             %-20d|\n", patient.serial);
            printf("\t\t\t\t\t| Confirmation:   %-20s|\n", patient.confirmation);
            printf("\t\t\t\t\t| Confirmation:   %-20s|\n", patient.app_date);
            printf("\t\t\t\t\t| Time:           %-20s|\n", patient.time);
            printf("\t\t\t\t\t| Room Number:    %-20s|\n", patient.room);
            printf("\t\t\t\t\t| Bed Number:     %-20s|\n", patient.bed);
            printf("\t\t\t\t\t-------------------------------------\n");
            found = 1;
        }
    }
    if (!found)
    {
        printf("Patient with ID %d not found.\n", p_id);
    }
    pressEnterToContinue(); // Prompt to press enter to continue
    clearScreen();
}
/**
 * @brief Frees the memory occupied by the linked list of patient records.
 *
 * This function traverses the linked list starting from the head node and frees
 * the memory allocated for each node.
 *
 * @param head Pointer to the head of the linked list.
 */
void freeLinkedList(PatientInfo *head)
{
    PatientInfo *current = head; // Initialize current pointer to the head of the linked list
    PatientInfo *next;           // Pointer to store the next node to be freed

    // Traverse the linked list
    while (current != NULL)
    {
        next = current->next; // Store the next node before freeing the current node
        free(current);        // Free the memory occupied by the current node
        current = next;       // Move to the next node
    }
}

/**
 * @brief Confirm bed booking for a patient.
 *
 * This function searches for the patient with the given ID in the patient information file,
 * updates their bed status to "Pending", and writes the updated information back to the file.
 *
 * @param filename The name of the patient information file.
 */
void confirmation_bed(const char *filename)
{
    FILE *file = fopen(filename, "rb+"); // Open the patient information file for reading and writing
    if (file == NULL)
    {
        printf("Unable to open file %s\n", filename); // Check if file opening failed
        return;
    }

    int id;
    printf("\t\t\t\t\tEnter Your ID: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input for patient ID.\n");
        fclose(file);
        return;
    }

    PatientInfo patient;
    while (fread(&patient, sizeof(PatientInfo), 1, file) == 1) // Iterate through the file
    {
        if (id == patient.serial) // Check if the ID matches the patient's ID
        {
            strcpy(patient.bed, "Pending"); // Update bed status to "Pending"

            fseek(file, -sizeof(PatientInfo), SEEK_CUR); // Move file pointer back to update the record

            fwrite(&patient, sizeof(PatientInfo), 1, file); // Write the updated record back to file

            printf("\t\t\t\t\tBed Booking is Pending.\n");
            pressEnterToContinue();
            clearScreen();
            fclose(file);
            return;
        }
    }

    printf("Patient with ID %d not found.\n", id); // If patient with given ID is not found
    fclose(file);                                  // Close the file
}

/**
 * @brief Delete a patient record from the file based on ID.
 *
 * This function opens the patient information file for reading and writing.
 * It creates a temporary file to store records excluding the one to be deleted.
 * The patient record with the specified ID is skipped while copying data to the temporary file.
 * After copying, it closes the original file, reopens it for writing, and copies back the data
 * from the temporary file, excluding the record to be deleted.
 *
 * @param id The ID of the patient to be deleted.
 */
void deletePatient(int id)
{
    FILE *file_ptr = fopen("patient_info.bin", "rb+"); // Open the file for reading and writing

    FILE *temp = fopen("temp.bin", "wb+"); // Create a temporary file
    if (temp == NULL || file_ptr == NULL)
    {
        printf("File cannot be open!\n");
        return;
    }

    PatientInfo patient;
    int found = 0; // Flag to indicate if the patient with the given ID is found

    // Read data from the original file and write to the temporary file, excluding the record to be deleted
    while (fread(&patient, sizeof(PatientInfo), 1, file_ptr) == 1)
    {
        if (patient.serial != id)
        {
            fwrite(&patient, sizeof(PatientInfo), 1, temp);
        }
        else
        {
            found = 1; // Patient with given ID found
        }
    }

    // rewind(file_ptr); // Move file pointer to the beginning
    fclose(file_ptr); // Close the original file

    file_ptr = fopen("patient_info.bin", "wb"); // Reopen the original file for writing
    if (file_ptr == NULL)
    {
        printf("Error opening original file for writing.\n");
        fclose(temp);
        return;
    }

    // Rewrite the modified data from the temporary file to the original file
    rewind(temp);
    while (fread(&patient, sizeof(PatientInfo), 1, temp) == 1)
    {
        if (patient.serial != id)
        {
            fwrite(&patient, sizeof(PatientInfo), 1, file_ptr);
        }
    }

    fclose(temp);                // Close the temporary file
    if (remove("temp.bin") != 0) // Remove the temporary file
    {
        printf("Error removing temporary file.\n");
    }
    fclose(file_ptr); // Close the original file
    if (!found)
    {
        printf("Patient with ID %d not found.\n", id);
    }
    else
    {
        printf("Patient with ID %d deleted successfully.\n", id);
    }
    pressEnterToContinue(); // Pause before continuing
}

void PatientGuideline()
{
    printf("\n\t\t **** How it Works? ****\n\n");
    printf(" -> You have to entry information in this formate:\n");
    printf("1. Full Name: Maximum 50 characters\n");
    printf("2. Date of Birth: Format (YYYY-MM-DD)\n");
    printf("3. Phone Number: Maximum 15 characters (unique for each patient)\n");
    printf("4. Doctor's Name: Maximum 50 characters(Information-> Available Doctors)\n");
    printf("5. Gender: 'M' for Male, 'F' for Female\n");
    printf("6. Confirmation Status: 'Confirmed' or 'Pending'\n\n");
    printf("Make sure to follow these guidelines for accurate data entry.\n\n");
}

void DeletedDoctors()
{
    FILE *file_ptr = fopen("Doctors.bin", "rb+");
    FILE *temp = fopen("temp.bin", "wb+");

    if (temp == NULL || file_ptr == NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }

    Docinifo current_doc;
    char doc_id[6];
    int found = 0;

    printf("\t\t\t\t\t\tEnter the Doctor's ID you want to remove:");
    while (getchar() != '\n')
        ;
    fgets(doc_id, sizeof(doc_id), stdin);
    doc_id[strcspn(doc_id, "\n")] = '\0'; // Remove trailing newline

    while (fread(&current_doc, sizeof(current_doc), 1, file_ptr) == 1)
    {
        if (strcmp(current_doc.id, doc_id) != 0)
        {
            fwrite(&current_doc, sizeof(current_doc), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file_ptr);

    file_ptr = fopen("Doctors.bin", "wb");

    if (file_ptr == NULL)
    {
        printf("Error opening original file for writing.\n");
        fclose(temp);
        return;
    }

    rewind(temp);

    while (fread(&current_doc, sizeof(current_doc), 1, temp) == 1)
    {
        fwrite(&current_doc, sizeof(current_doc), 1, file_ptr);
    }

    fclose(temp);

    if (remove("temp.bin") != 0)
    {
        printf("Error removing temporary file.\n");
    }

    fclose(file_ptr);

    if (!found)
    {
        printf("\t\t\t\t\tDoctor with ID %s not found.\n", doc_id);
        pressEnterToContinue();
    }
    else
    {
        printf("\t\t\t\t\tDoctor with ID %s deleted successfully.\n", doc_id);
        pressEnterToContinue();
    }
}

void ShowDoctors(int choice)
{
    clearScreen();
    Docinifo doctor_info;
    FILE *doctorlist = fopen("Doctors.bin", "rb+"); // Open in binary read mode
    if (doctorlist == NULL)
    {
        printf("Error: File not found!\n");
        return;
    }

    while (fread(&doctor_info, sizeof(Docinifo), 1, doctorlist) == 1)
    {
        // Print doctor's information
        printf("\t\t\t\t\t----------------------------------------\n");
        printf("\t\t\t\t\tName:    %s\n", doctor_info.Name);
        printf("\t\t\t\t\tDept:    %s\n", doctor_info.Dept);
        printf("\t\t\t\t\tContact: %s\n", doctor_info.contact);
        if (choice == 3)
        {
            printf("\t\t\t\t\tSalary:  %s\n", doctor_info.salary);
            printf("\t\t\t\t\tID:      %s\n", doctor_info.id);
        }
        printf("\t\t\t\t\t----------------------------------------\n");
    }

    fclose(doctorlist);
    pressEnterToContinue();
}

void AddDoctor()
{
    FILE *fnew = NULL;
    Docinifo *new_doctor = NULL, *temp = NULL;

    fnew = fopen("Doctors.bin", "ab+"); // Open in binary append mode
    if (fnew == NULL)
    {
        printf("Error: File not found!\n");
        return;
    }

    new_doctor = (Docinifo *)malloc(sizeof(Docinifo));
    if (new_doctor == NULL)
    {
        printf("Error while allocating memory!\n");
        fclose(fnew); // Close the file before returning
        return;
    }

    // Clear input buffer
    while (getchar() != '\n')
        ;

    printf("Enter the name of Doctor: ");
    fgets(new_doctor->Name, sizeof(new_doctor->Name), stdin);
    new_doctor->Name[strcspn(new_doctor->Name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the speciality of the Doctor (Department): ");
    fgets(new_doctor->Dept, sizeof(new_doctor->Dept), stdin);
    new_doctor->Dept[strcspn(new_doctor->Dept, "\n")] = '\0'; // Remove trailing newline

    printf("Enter Contact no: ");
    fgets(new_doctor->contact, sizeof(new_doctor->contact), stdin);
    new_doctor->contact[strcspn(new_doctor->contact, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the salary of the doctor (BDT): ");
    fgets(new_doctor->salary, sizeof(new_doctor->salary), stdin);
    new_doctor->salary[strcspn(new_doctor->salary, "\n")] = '\0'; // Remove trailing newline

    printf("Enter ID: ");
    fgets(new_doctor->id, sizeof(new_doctor->id), stdin);
    new_doctor->id[strcspn(new_doctor->id, "\n")] = '\0'; // Remove trailing newline

    new_doctor->newdoc = NULL;

    // Writing to the file
    fwrite(new_doctor, sizeof(Docinifo), 1, fnew);
    fclose(fnew);
    clearScreen();
    printf("\t\t\t\t\t----------------------------------------\n");
    printf("\t\t\t\t\tName:    %s\n", new_doctor->Name);
    printf("\t\t\t\t\tDept:    %s\n", new_doctor->Dept);
    printf("\t\t\t\t\tContact: %s\n", new_doctor->contact);
    printf("\t\t\t\t\tSalary:  %s\n", new_doctor->salary);
    printf("\t\t\t\t\tID:      %s\n", new_doctor->id);
    printf("\t\t\t\t\t----------------------------------------\n");
    printf("\t\t\t\t\tDoctor information added and file updated!\n");
    free(new_doctor);
    pressEnterToContinue();
}

void Bloddbank()

{
    clearScreen();
    int choice;
    while (1)
    {
        printf("\t\t\t\t\t\t----------------------------------------------\n");
        printf("\t\t\t\t\t\t|               Blood Bank MENU              |\n");
        printf("\t\t\t\t\t\t----------------------------------------------\n");
        printf("\t\t\t\t\t\t| Enter 1 to Add Blood Collection            |\n\n");
        printf("\t\t\t\t\t\t| Enter 2 to Take Blood                      |\n\n");
        printf("\t\t\t\t\t\t| Enter 3 to Display Donor Information       |\n\n");
        printf("\t\t\t\t\t\t| Enter 0 to Go Back                         |\n\n");
        printf("\t\t\t\t\t\t----------------------------------------------\n");

        printf("\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            Addblood();
            clearScreen();
            break;
        case 2:
            TakeBlood();
            clearScreen();
            break;
        case 3:
            Display_donor();
            clearScreen();
            break;
        case 0:
            clearScreen();
            return;
        default:
            printf("\t\t\t\tInvalid choice. Please enter a valid option.\n"); // Display message for invalid input
            clearScreen();
            Sleep(700);
        }
    }
}

void Addblood()
{
    FILE *fnew = NULL, *f_read = NULL;
    Bloodinfo *new_donar = NULL, *temp = NULL, donar_info;
    fnew = fopen("Blood.txt", "a"); // opening file for storing bloodbank
    if (fnew == NULL)
    {
        printf("Error:  File not found!\n");
        return; // Exit function on error
    }
    new_donar = (Bloodinfo *)malloc(sizeof(Bloodinfo));

    if (new_donar == NULL)
    {
        printf("Error while allocating memory !\n");
        return;
    }

    while (getchar() != '\n')
        ;
    printf("Enter the name of donor:");
    fgets(new_donar->Donar_name, 50, stdin);

    printf("Enter the blood group: ");
    fgets(new_donar->group, 50, stdin);

    printf("Contact no:");
    fgets(new_donar->contact_no, 25, stdin);
    new_donar->next = NULL;

    if (first_blood == NULL)
    {
        first_blood = new_donar;
    }
    else
    {
        temp = new_donar;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_donar;
    }
    // writing to the file
    fprintf(fnew, "Name:%sContact:%sGroup:%s\n", new_donar->Donar_name, new_donar->contact_no, new_donar->group); // Add newline for clarity

    fclose(fnew);
    printf("Blood Bank Updated!\n");
    pressEnterToContinue();
}

void TakeBlood()
{
    FILE *fread = NULL, *fwrite = NULL;
    Bloodinfo donor_info;
    char blood[50];
    int blood_taken = 0;
    int found = 0;

    printf("Enter the blood group you need:\n");

    while (getchar() != '\n')
        ;
    fgets(blood, 50, stdin);

    fread = fopen("Blood.txt", "r");
    fwrite = fopen("temp.txt", "w");

    if (fread == NULL || fwrite == NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }

    // Reads the file line by line
    while (fgets(donor_info.Donar_name, sizeof(donor_info.Donar_name), fread) != NULL && !feof(fread))
    {
        if (donor_info.Donar_name[0] == '\n' && donor_info.Donar_name[1] == '\0')
        {
            continue; // Skip to the next iteration of the loop
        }
        if (fgets(donor_info.contact_no, sizeof(donor_info.contact_no), fread) == NULL ||
            fgets(donor_info.group, sizeof(donor_info.group), fread) == NULL)
        {
            break; // Handle end of file or error
        }

        // Compare the blood group
        if (strcmp(donor_info.group + 6, blood) == 0 && blood_taken != 1)
        {
            printf("%s", donor_info.Donar_name);
            printf("%s", donor_info.contact_no);
            printf("%s", donor_info.group);

            // Decrease the quantity of blood
            int quantity;
            sscanf(donor_info.group + 6 + strlen(blood), "%d", &quantity);
            quantity--;

            // Write the updated data to the temporary file
            fprintf(fwrite, "%s%sBlood: %s %d\n", donor_info.Donar_name, donor_info.contact_no, blood, quantity);

            found = 1;
            blood_taken++;
        }
        else
        {
            // Write unchanged data to the temporary file
            fprintf(fwrite, "%s%s%s", donor_info.Donar_name, donor_info.contact_no, donor_info.group);
        }
    }

    fclose(fread);
    fclose(fwrite);

    if (found == 1)
    {
        remove("Blood.txt");
        rename("temp.txt", "Blood.txt");
        printf("%s is taken from the bank!\n", blood);
    }
    else
    {
        remove("temp.txt");
        printf("Blood not found!\n");
    }
    pressEnterToContinue();
    clearScreen();
}

void showbloodbank()
{
    clearScreen();
    FILE *fptr = NULL;
    char ch;
    int cap = 0, cbp = 0, can = 0, cbn = 0, cabp = 0, cabn = 0, cop = 0, con = 0;

    // Open the file for reading
    fptr = fopen("Blood.txt", "r");
    if (fptr == NULL)
    {
        printf("Error while opening file!\n");
        return; // Exit the function if opening fails
    }

    // Read the file character by character
    while ((ch = fgetc(fptr)) != EOF)
    {
        if (ch == 'A')
        {
            if (fgetc(fptr) == '+')
            {
                cap++;
            }
            else
            {
                can++;
                fseek(fptr, -1, SEEK_CUR);
            }
        }
        else if (ch == 'B')
        {
            if (fgetc(fptr) == '+')
            {
                cbp++;
            }
            else
            {
                cbn++;
                fseek(fptr, -1, SEEK_CUR);
            }
        }
        else if (ch == 'O')
        {
            if (fgetc(fptr) == '+')
            {
                cop++;
            }
            else
            {
                con++; // Assuming O- follows O+
                fseek(fptr, -1, SEEK_CUR);
            }
        }
        else if (ch == 'A' && fgetc(fptr) == 'B')
        {
            if (fgetc(fptr) == '+')
            {
                cabp++;
            }
            else
            {
                cabn++;
                fseek(fptr, -1, SEEK_CUR);
            }
        }
    }

    // Close the file
    fclose(fptr);
    printf("\n\n\n\n");
    printf("\t\t\t\t\t---------------------------------------\n");
    // Print the counts for each blood type
    printf("\t\t\t\t\tTotal A+ blood: %-5d\n", cap);
    printf("\t\t\t\t\tTotal A- blood: %-5d\n", can);
    printf("\t\t\t\t\tTotal B+ blood: %-5d\n", cbp);
    printf("\t\t\t\t\tTotal B- blood: %-5d\n", cbn);
    printf("\t\t\t\t\tTotal AB+ blood: %-5d\n", cabp);
    printf("\t\t\t\t\tTotal AB- blood: %-5d\n", cabn);
    printf("\t\t\t\t\tTotal O+ blood: %-5d\n", cop);
    printf("\t\t\t\t\tTotal O- blood: %-5d\n", con);
    printf("\t\t\t\t\t----------------------------------------\n");
    pressEnterToContinue();
    clearScreen();
}

void Doctors()
{
    clearScreen();

    int choice;
    while (1)
    {

        clearScreen();
        printf("\n\n\n"); // Add spacing for better alignment
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t|              Doctor Management MENU            |\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t| Enter 1 For Add Doctor's record                |\n\n");
        printf("\t\t\t\t\t\t| Enter 2 For Delete Doctor                      |\n\n");
        printf("\t\t\t\t\t\t| Enter 3 For Display All Doctor                 |\n\n");
        printf("\t\t\t\t\t\t| Enter 4 For Display Doctor's Patient           |\n\n");
        printf("\t\t\t\t\t\t| Enter 0 For Exit                               |\n\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            AddDoctor();
            break;
        case 2:
            DeletedDoctors();

            break;
        case 3:
            ShowDoctors(choice);
            break;
        case 4:
            doc_Patient();
            break;
        case 0:
            clearScreen();
            return;
        default:
            printf("\n\t\t\t\tInvalid choice. Please enter a valid option.\n");
            Sleep(700);
        }
    }
}

void Display_donor()
{
    FILE *fread = NULL;
    Bloodinfo donor;

    fread = fopen("Blood.txt", "r"); // Open file for reading
    if (fread == NULL)
    {
        printf("Error: File not found or could not be opened!\n");
        return; // Exit function on error
    }

    printf("Donor Information:\n");
    printf("-------------------------------------------------\n");
    while (fscanf(fread, "Name: %49[^\n]\nContact: %24[^\n]\nGroup: %49[^\n]\n", donor.Donar_name, donor.contact_no, donor.group) == 3)
    {
        printf("\t\t\t\t\tName: %s\n\t\t\t\t\tContact: %s\n\t\t\t\t\tGroup: %s\n", donor.Donar_name, donor.contact_no, donor.group);
        printf("-------------------------------------------------\n");
    }
    pressEnterToContinue();
    clearScreen();
    fclose(fread);
}

void EmergencyContacts()
{
    int choice;
    char nameToDelete[MAX_NAME_LENGTH];
    do
    {
        clearScreen();
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t|               Emergency Number Management     |\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t| 1. Add Emergency Contact                      |\n\n");
        printf("\t\t\t\t\t\t| 2. Display Emergency Contacts                 |\n\n");
        printf("\t\t\t\t\t\t| 3. Save Emergency Contacts to File            |\n\n");
        printf("\t\t\t\t\t\t| 4. Delete Emergency Contact                   |\n\n");
        printf("\t\t\t\t\t\t| 0. Exit                                       |\n\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left in the input buffer

        switch (choice)
        {
        case 1:
            addEmergencyContactToFile();
            break;
        case 2:
            displayEmergencyContactsFromFile();
            pressEnterToContinue();
            clearScreen();
            break;
        case 3:
            saveEmergencyContactsToFile("emergency_contacts.txt");
            printf("\t\t\t\t\tEmergency contacts saved to file.\n");
            pressEnterToContinue();
            clearScreen();
            break;
        case 4:
            printf("Enter the name of emergency contact to delete: ");
            fgets(nameToDelete, MAX_NAME_LENGTH, stdin);
            nameToDelete[strcspn(nameToDelete, "\n")] = '\0'; // Remove trailing newline
            deleteEmergencyContactFromFile(nameToDelete);
            pressEnterToContinue();
            clearScreen();
            break;
        case 0:
            clearScreen();
            break;
        default:
            printf("Invalid choice. Please enter a number between 0 and 4.\n");
            break;
        }
    } while (choice != 0);
}

void addEmergencyContactToFile()
{
    clearScreen();
    FILE *file = fopen("emergency_contacts.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for appending.\n");
        return;
    }

    char name[MAX_NAME_LENGTH];
    char number[MAX_NUMBER_LENGTH];
    printf("Enter name: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove trailing newline

    printf("Enter number: ");
    fgets(number, MAX_NUMBER_LENGTH, stdin);
    number[strcspn(number, "\n")] = '\0'; // Remove trailing newline

    fprintf(file, "%s,%s\n", name, number);
    fclose(file);
}

void displayEmergencyContactsFromFile()
{
    clearScreen();
    FILE *file = fopen("emergency_contacts.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    char name[MAX_NAME_LENGTH];
    char number[MAX_NUMBER_LENGTH];
    printf("Emergency Contacts:\n");
    printf("\t\t\t\t\t+------------------------------------------+\n");
    printf("\t\t\t\t\t| %-20s | %-15s |\n", "Name", "Number");
    printf("\t\t\t\t\t+------------------------------------------+\n");

    while (fscanf(file, "%49[^,],%19[^\n]%*c", name, number) == 2)
    {
        printf("\t\t\t\t\t| %-20s | %-15s |\n", name, number);
    }

    fclose(file);
    printf("\t\t\t\t\t+------------------------------------------+\n");
}

void saveEmergencyContactsToFile(const char *filename)
{
    FILE *inputFile = fopen("emergency_contacts.txt", "r");
    if (inputFile == NULL)
    {
        printf("Error opening input file for reading.\n");
        return;
    }

    FILE *outputFile = fopen(filename, "w");
    if (outputFile == NULL)
    {
        printf("Error opening output file for writing.\n");
        fclose(inputFile);
        return;
    }

    char line[MAX_NAME_LENGTH + MAX_NUMBER_LENGTH + 2]; // +2 for comma and newline
    while (fgets(line, sizeof(line), inputFile) != NULL)
    {
        fputs(line, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

void deleteEmergencyContactFromFile(const char *nameToDelete)
{
    FILE *inputFile = fopen("emergency_contacts.txt", "r");
    if (inputFile == NULL)
    {
        printf("Error opening input file for reading.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file for writing.\n");
        fclose(inputFile);
        return;
    }

    char name[MAX_NAME_LENGTH];
    char number[MAX_NUMBER_LENGTH];
    int deleted = 0;
    while (fscanf(inputFile, "%49[^,],%19[^\n]%*c", name, number) == 2)
    {
        if (strcmp(name, nameToDelete) != 0)
        {
            fprintf(tempFile, "%s,%s\n", name, number);
        }
        else
        {
            deleted = 1;
        }
    }

    fclose(inputFile);
    fclose(tempFile);

    if (deleted)
    {
        remove("emergency_contacts.txt");
        rename("temp.txt", "emergency_contacts.txt");
        printf("Emergency contact '%s' deleted successfully.\n", nameToDelete);
    }
    else
    {
        remove("temp.txt");
        printf("Emergency contact '%s' not found.\n", nameToDelete);
    }
}

void toLowerString(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
}

int compareCaseInsensitive(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if (tolower(*str1) != tolower(*str2))
        {
            return 0; // Not equal
        }
        str1++;
        str2++;
    }
    if (*str1 || *str2)
    {
        return 0; // Lengths are different
    }
    return 1; // Equal
}

void doc_Patient()
{
    clearScreen();
    char d_name[20];
    while (getchar() != '\n')
        ;
    printf("\t\tENTER DOCTOR'S NAME: ");
    fgets(d_name, sizeof(d_name), stdin);
    d_name[strcspn(d_name, "\n")] = '\0';

    FILE *file_ptr = fopen("patient_info.bin", "rb");
    if (file_ptr == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }
    printf("\t\t\t\t\tDisplay All Patient of Doctor %s.\n", d_name);
    PatientInfo patient;
    int found = 0;

    toLowerString(d_name); // Convert input doctor's name to lowercase

    while (fread(&patient, sizeof(PatientInfo), 1, file_ptr) == 1)
    {
        if (compareCaseInsensitive(patient.doctor, d_name))
        {
            printf("\t\t\t\t\t----------------------------------------\n");
            printf("\t\t\t\t\t| Name:           %-20s|\n", patient.full_name);
            printf("\t\t\t\t\t| Date of Birth:  %-20s|\n", patient.date_of_birth);
            printf("\t\t\t\t\t| Phone Number:   %-20s|\n", patient.phone_number);
            printf("\t\t\t\t\t| Doctor:         %-20s|\n", patient.doctor);
            printf("\t\t\t\t\t| Gender:         %-20c|\n", patient.gender);
            printf("\t\t\t\t\t| ID:             %-20d|\n", patient.serial);
            printf("\t\t\t\t\t| Confirmation:   %-20s|\n", patient.confirmation);
            printf("\t\t\t\t\t| Date:           %-20s|\n", patient.app_date);
            printf("\t\t\t\t\t| Time:           %-20s|\n", patient.time);
            printf("\t\t\t\t\t| Room Number:    %-20s|\n", patient.room);
            printf("\t\t\t\t\t| Bed Number:     %-20s|\n", patient.bed);
            printf("\t\t\t\t\t-------------------------------------\n");
            found = 1;
        }
    }

    fclose(file_ptr);

    if (!found)
    {
        printf("\t\t\t\tNo patients found for doctor: %s\n", d_name);
    }
    pressEnterToContinue();
    clearScreen();
}