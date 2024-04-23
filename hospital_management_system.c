#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>   // Header for console input/output (specific to Windows)
#include <windows.h> // Header providing access to Windows API functions
#include <time.h>    // Header for time functions

// Structure to hold information about a patient
typedef struct PatientInfo
{
    char full_name[50];       // Full name of the patient
    char date_of_birth[12];   // Date of birth of the patient (Format: YYYY-MM-DD)
    char phone_number[15];    // Phone number of the patient
    char doctor[50];          // Name of the doctor the patient needs an appointment with
    char gender;              // Gender of the patient ('M' for male, 'F' for female, 'O' for others)
    int serial;               // Unique serial number or ID assigned to the patient
    char confirmation[10];    // Confirmation status of the appointment or bed booking ('Confirmed', 'Pending', etc.)
    char time[10];            // Appointment time
    char room[15];            // Room number
    char bed[15];             // Bed number
    struct PatientInfo *next; // Pointer to the next PatientInfo structure in a linked list
} PatientInfo;

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
int PASSWORD();

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
    int choice, re;
    PatientInfo *first_PatientInfo = NULL;
    FILE *file_ptr = NULL;

    while (1)
    {
        printf("\n\n\n");
        printf("\n\n\n"); // Add spacing for better alignment
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t#               MAIN MENU                       #\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t#  ENTER 1 FOR ADMIN ACCESS                     #\n");
        printf("\t\t\t\t\t\t#  ENTER 2 FOR APPOINTMENT                      #\n");
        printf("\t\t\t\t\t\t#  ENTER 3 FOR MORE INFORMATION                 #\n");
        printf("\t\t\t\t\t\t#  ENTER 0 FOR EXIT                             #\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n\n");
        printf("\t\t\t\t\t\tENTER Your choice: "); // Prompt for user input

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            re = PASSWORD();
            if (re == 1)
            {
                adminAccess(file_ptr); // Call adminAccess function
            }
            break;
        case 2:
            appointment(&first_PatientInfo, file_ptr);
            break;
        case 3:
            information();
            break;
        case 0:
            printf("\t\t\t\t\t\t---------------------------------------------------------------------\n");
            printf("\t\t\t\t\t\t|               Exiting the program. Goodbye!                       |\n");
            printf("\t\t\t\t\t\t---------------------------------------------------------------------\n");

            freeLinkedList(first_PatientInfo);
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
        printf("\t\t\t\t\t\t| 1. New Patient Registration                    |\n");
        printf("\t\t\t\t\t\t| 2. To See Confirmation                         |\n");
        printf("\t\t\t\t\t\t| 3. Booking Bed                                 |\n");
        printf("\t\t\t\t\t\t| 4. Patient Guideline                           |\n");
        printf("\t\t\t\t\t\t| 0. Back to Main Menu                           |\n");
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
    printf("1. Confirmation for Bed\n");
    printf("2. Confirmation for appointment\n");

    int choise;
    printf("Enter choice: ");
    scanf("%d", &choise); // Read user's choice

    FILE *file_ptr = fopen("patient_info.bin", "rb"); // Open the file for reading

    if (file_ptr == NULL)
    {
        printf("File cannot be opened!\n");
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
                printf("\t\t\t\t\t| Confirmation:   %-20s|\n", patient.confirmation);
                printf("\t\t\t\t\t| Room Number:    %-20s|\n", patient.room);
                printf("\t\t\t\t\t| Bed Number:     %-20s|\n", patient.bed);
                printf("\t\t\t\t\t-------------------------------------\n");
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
                printf("\t\t\t\t\t-------------------------------------\n");
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
        printf("\t\t\t\t\t\t#               MAIN MENU                        #\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t# Enter 1 to Appoint Patient Bed / Appointment   #\n");
        printf("\t\t\t\t\t\t# Enter 2 to Display All Patients Information    #\n");
        printf("\t\t\t\t\t\t# Enter 3 for DOCTOR Management                  #\n");
        printf("\t\t\t\t\t\t# Enter 4 to Remove Patients Information         #\n");
        printf("\t\t\t\t\t\t# Enter 5 to Make a Bill                         #\n");
        printf("\t\t\t\t\t\t# Enter 6 to Update Blood Bank                   #\n");
        printf("\t\t\t\t\t\t# Enter 0 to EXIT                                #\n");
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
            re = PASSWORD(); // Call function to handle password authentication
            if (re)
            {
                // Access to doctor's salary granted
                // You can add the logic to display doctor's salary here
            }
            else
            {
                // Access denied
            }
            pressEnterToContinue(); // Pause before returning to the menu
            break;
        case 4:

            readFromFile("patient_info.bin", choice);
            int deleteId;
            printf("Enter the ID of the patient you want to delete: "); // Prompt user to enter patient ID for deletion
            scanf("%d", &deleteId);                                     // Read patient ID from user input
            deletePatient(deleteId);                                    // Call function to delete patient information
            clearScreen();                                              // Clear the screen
            break;
        case 5:
            // Handle case 5
            break;
        case 6:
            // Handle case 6
            break;
        case 0:
            clearScreen(); // Clear the screen
            return 0;      // Return 0 to indicate successful completion

        default:
            printf("\t\t\t\tInvalid choice. Please enter a valid option.\n"); // Display message for invalid input
        }
    }
}

int information()
{
    clearScreen();
    printf("\n\n\n"); // Add spacing for better alignment
    printf("\t\t\t\t-------------------------------------------------\n");
    printf("\t\t\t\t|               MORE INFORMATION MENU           |\n");
    printf("\t\t\t\t-------------------------------------------------\n");
    printf("\t\t\t\t| 1. Available Doctors                          |\n");
    printf("\t\t\t\t| 2. Doctor Time Table                          |\n");
    printf("\t\t\t\t| 3. Available Blood                            |\n");
    printf("\t\t\t\t| 4. Emergency Number                           |\n");
    printf("\t\t\t\t| 0. Back to Main Menu                          |\n");
    printf("\t\t\t\t-------------------------------------------------\n\n");

    printf("\t\t\t\tEnter your choice: ");
    pressEnterToContinue();
    clearScreen();
    return 0;
}

int PASSWORD()
{
    int i = 0;
    char pass[50], ch, paSs[] = "h";

    printf("Enter a password: ");
    while (1)
    {
        ch = getch();
        if (ch == 13)
        { // Enter key pressed
            pass[i] = '\0';
            break;
        }
        else if (ch == 8 && i > 0)
        {
            printf("\b \b"); // Erase the last asterisk
            i--;
        }
        else if (i < 49)
        {
            pass[i++] = ch;
            printf("*");
        }
    }

    int c = strcmp(paSs, pass);
    if (c == 0)
    {
        clearScreen();
        printf("\n\n\n"); // Add some spacing for better alignment
        printf("\t\t\t\t\t\t#################################################\n");
        printf("\t\t\t\t\t\t#               ACCESS GRANTED                  #\n");
        printf("\t\t\t\t\t\t#               ACCESS GRANTED                  #\n");
        printf("\t\t\t\t\t\t#################################################\n\n");
        waiting();
        return 1;
    }
    else
    {
        clearScreen();
        printf("\n\n\n"); // Add some spacing for better alignment
        printf("\t\t\t\t\t\t#################################################\n");
        printf("\t\t\t\t\t\t#               ACCESS DENIED                   #\n");
        printf("\t\t\t\t\t\t#               ACCESS DENIED                   #\n");
        printf("\t\t\t\t\t\t#################################################\n\n");
        waiting();
        return 0;
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
        strcpy(new_Patient->time, "\0");              // Initialize appointment time
        strcpy(new_Patient->room, "\0");              // Initialize room number
        strcpy(new_Patient->bed, "\0");               // Initialize bed number
        new_Patient->next = NULL;                     // Set next pointer to NULL

        printf("\n\t\tConfirm with 'O' or change/cancel with 'C'.\n");
        char choice;
        if (scanf(" %c", &choice) == 1)
        {
            if (choice == 'C' || choice == 'c')
            {
                free(new_Patient); // Free memory if user chooses to cancel
                clearScreen();     // Clear the screen
                continue;          // Restart the loop
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
                printf("Enter Appointment Time: ");
                scanf("%s", patient.time);                 // Input appointment time
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
    clearScreen(); // Clear the screen

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
        printf("\t\t\t\t\t1.To Confirm Bed\n");
        printf("\t\t\t\t\t2.To Confirm appointment\n");
        printf("\t\t\t\t\t9. Exit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice2) == 1)
        {
            if (choice2 == 9)
            {
                return;
            }
            Confirm_appointment_bed(filename, choice2); // Confirm bed or appointment based on choice
        }
    }
    if (choice != 4)
    {
        pressEnterToContinue(); // Prompt to press enter to continue
        clearScreen();          // Clear the screen
    }
    return;
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
    printf("Enter Your ID: ");
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

            printf("Bed Booking is Pending.\n");
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

    rewind(file_ptr); // Move file pointer to the beginning
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
    printf("4. Doctor's Name: Maximum 50 characters\n");
    printf("5. Gender: 'M' for Male, 'F' for Female\n");
    printf("6. Confirmation Status: 'Confirmed' or 'Pending'\n\n");
    printf("Make sure to follow these guidelines for accurate data entry.\n\n");
}
