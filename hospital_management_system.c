#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

typedef struct PatientInfo
{
    char full_name[50];

    char date_of_birth[12];

    char phone_number[15];

    char doctor[50];

    char gender;

    int serial;

    char confirmation[10];

    char time[10];

    char room[15];

    char bed[15];

    struct PatientInfo *next;

} PatientInfo;

//----------------------------------------This function is responsible for handling the patient appointment process---------------------------------------
int appointment(PatientInfo **first_PatientInfo, FILE *file_ptr);

//---------------------------------------- This function displays a confirmation message----------------------------------------------------------
void confirmation();

void confirmation_bed(const char *filename);
//---------------------------------------- This function is used to handle the admin access functionality---------------------------------------
int adminAccess(FILE *file_ptr);

//---------------------------------------- This function is used to display the hospital information---------------------------------------
int information();

//---------------------------------------- This function is used to handle password authentication---------------------------------------
int PASSWORD();

//---------------------------------------- This function is used to display a waiting message---------------------------------------
void waiting();

//---------------------------------------- This function is used to add a new patient's information to the system---------------------------------------
int add_patientinfo(PatientInfo **first_PatientInfo, FILE *file_ptr);

//----------------------------------------This function is used to free the memory occupied by the linked list of patient records.---------------------------------------
void freeLinkedList(PatientInfo *head);

//----------------------------------------This function is used to read the patient data from a file and display it.---------------------------------------
void readFromFile(const char *filename, int choice);

void Confirm_appointment_bed(const char *filename, int choice);

void deletePatient(int id);

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

int appointment(PatientInfo **first_PatientInfo, FILE *file_ptr)
{

    clearScreen();
    int choice;

    while (1)
    {
        printf("\t\t\t\t\t\t--------------------------------------------------\n");
        printf("\t\t\t\t\t\t|           Appointment     MENU                 |\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n");
        printf("\t\t\t\t\t\t| 1. New Patient Registration                    |\n");
        printf("\t\t\t\t\t\t| 2. To See Confirmation                         |\n");
        printf("\t\t\t\t\t\t| 3. Booking Bed                                 |\n");
        printf("\t\t\t\t\t\t| 4. Patient Guideline                           |\n");
        printf("\t\t\t\t\t\t| 0. Back to Main Menu                           |\n");
        printf("\t\t\t\t\t\t-------------------------------------------------\n\n");

        printf("Enter your choice: ");
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
            clearScreen();
            add_patientinfo(first_PatientInfo, file_ptr);
            break;
        case 2:
            clearScreen();
            confirmation();
            break;
        case 3:
            clearScreen();
            confirmation_bed("patient_info.bin");
            break;
        case 4:
            clearScreen();
            PatientGuideline();
            break;
        case 0:
            clearScreen();

            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

void confirmation()
{
    printf("1. Confirmation for Bed\n");
    printf("2. Confirmation for appointment\n");
    int choise;
    printf("Enter choise: ");
    scanf("%d", &choise);
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
    while (fread(&patient, sizeof(PatientInfo), 1, file_ptr) == 1)
    {
        if (id == patient.serial)
        {
            if (choise == 1)
            {
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

    if (!found)
    {
        printf("Patient with ID %d not found.\n", id);
    }

    fclose(file_ptr);
    pressEnterToContinue();
    clearScreen();
}

int adminAccess(FILE *file_ptr)
{
    clearScreen();
    int choice, re;
    file_ptr = fopen("patient_info.bin", "ab+"); // Open the file for reading and writing

    if (file_ptr == NULL)
    {
        printf("Unable to open file patient_info.bin\n");
        return 1;
    }
    while (1)
    {
        // clearScreen();
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
            readFromFile("patient_info.bin", choice);
            clearScreen();
            break;
        case 2:
            readFromFile("patient_info.bin", choice);
            clearScreen();
            // Handle case 2
            break;
        case 3:
            re = PASSWORD();
            if (re)
            {
                // Access to doctor's salary granted
                // You can add the logic to display doctor's salary here
            }
            else
            {
            }
            pressEnterToContinue(); // Pause before returning to the menu
            break;
        case 4:
            printf("Enter the ID of the patient you want to delete: ");
            int deleteId;

            scanf("%d", &deleteId);
            deletePatient(deleteId);
            clearScreen();
            break;
        case 5:
            // Handle case 5
            break;
        case 6:
            // Handle case 6
            break;
        case 0:
            clearScreen();
            return 0;

        default:
            printf("\t\t\t\tInvalid choice. Please enter a valid option.\n");
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

int add_patientinfo(PatientInfo **first_PatientInfo, FILE *file_ptr)
{
    file_ptr = fopen("patient_info.bin", "ab+");
    if (file_ptr == NULL)
    {
        printf("Failed to create file.\n");
        return 0; // Exit with error
    }

    PatientInfo *new_Patient = (PatientInfo *)malloc(sizeof(PatientInfo));
    if (new_Patient == NULL)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // Clear input buffer

    printf("\t\tENTER YOUR FULL NAME: ");
    fgets(new_Patient->full_name, 50, stdin);
    new_Patient->full_name[strcspn(new_Patient->full_name, "\n")] = '\0'; // Remove newline

    printf("\t\tENTER YOUR DATE OF BIRTH (Format: YYYY-MM-DD): ");
    fgets(new_Patient->date_of_birth, 12, stdin);
    new_Patient->date_of_birth[strcspn(new_Patient->date_of_birth, "\n")] = '\0'; // Remove newline

    printf("\t\tENTER YOUR PHONE NUMBER: ");
    fgets(new_Patient->phone_number, 15, stdin);
    new_Patient->phone_number[strcspn(new_Patient->phone_number, "\n")] = '\0'; // Remove newline

    printf("\t\tENTER THE NAME OF THE DOCTOR YOU NEED AN APPOINTMENT WITH: ");
    fgets(new_Patient->doctor, 50, stdin);
    new_Patient->doctor[strcspn(new_Patient->doctor, "\n")] = '\0'; // Remove newline

    printf("\t\tENTER YOUR GENDER: (M/F/O(Others)): ");
    scanf(" %c", &new_Patient->gender); // Note the space before %c to consume newline
    srand(time(NULL));

    // Generate and print a random number between 0 and RAND_MAX
    new_Patient->serial = rand() % 1000;
    strcpy(new_Patient->confirmation, "Pending");
    strcpy(new_Patient->time, "\0");
    strcpy(new_Patient->room, "\0");
    strcpy(new_Patient->bed, "\0");
    new_Patient->next = NULL;
    if (*first_PatientInfo == NULL)
    {
        *first_PatientInfo = new_Patient;
    }
    else
    {
        PatientInfo *temp = *first_PatientInfo;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_Patient;
    }

    if (file_ptr == NULL)
    {
        printf("Error opening file.\n");
        free(new_Patient);
        return 0;
    }
    printf("\t\tYour ID is %d\n\n", new_Patient->serial);
    printf("\t\tPlease wait for confirmation...\n");

    fwrite(new_Patient, sizeof(PatientInfo), 1, file_ptr);

    if (fclose(file_ptr) != 0)
    {
        printf("Error closing file.\n");
        return 0;
    }

    return 1;
}

void Confirm_appointment_bed(const char *filename, int choice)
{
    FILE *file = fopen(filename, "rb+");
    if (file == NULL)
    {
        printf("Unable to open file %s\n", filename);
        return;
    }

    int id;
    printf("Enter patient ID: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input for patient ID.\n");
        fclose(file);
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
                getchar(); // Consume newline character left in buffer
                fgets(patient.room, sizeof(patient.room), stdin);
                patient.room[strcspn(patient.room, "\n")] = '\0';
                printf("Enter Bed Number: ");
                fgets(patient.bed, sizeof(patient.bed), stdin);
                patient.bed[strcspn(patient.bed, "\n")] = '\0';
                printf("Bed confirmed.\n");
            }
            else if (choice == 2)
            {
                printf("Enter Appointment Time: ");
                scanf("%s", patient.time);
                strcpy(patient.confirmation, "Confirmed");
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
        printf("Patient with ID %d not found.\n", id);
    }

    fclose(file);
}

void readFromFile(const char *filename, int choice)
{
    clearScreen();

    FILE *file_ptr = fopen("patient_info.bin", "rb+"); // Open the file for reading and writing

    if (file_ptr == NULL)
    {
        printf("File cannot be open!\n");
        return;
    }

    printf("Patient List:\n");
    PatientInfo patient;

    // Read data until the end of the file
    while (fread(&patient, sizeof(PatientInfo), 1, file_ptr) == 1)
    {
        printf("\t\t\t\t\t----------------------------------------\n");
        printf("\t\t\t\t\t| Name:           %-20s|\n", patient.full_name);
        printf("\t\t\t\t\t| Date of Birth:  %-20s|\n", patient.date_of_birth);
        printf("\t\t\t\t\t| Phone Number:   %-20s|\n", patient.phone_number);
        printf("\t\t\t\t\t| Doctor:         %-20s|\n", patient.doctor);
        printf("\t\t\t\t\t| Gender:         %-20c|\n", patient.gender);
        printf("\t\t\t\t\t| ID:             %-20d|\n", patient.serial);
        printf("\t\t\t\t\t| Confirmation:   %-20s|\n", patient.confirmation);
        printf("\t\t\t\t\t| Time:           %-20s|\n", patient.time);
        printf("\t\t\t\t\t| Bed Number:     %-20s|\n", patient.room);
        printf("\t\t\t\t\t| Bed Number:     %-20s|\n", patient.bed);
        // printf("\t\t\t\t\t| Adress:         %-20s|\n", patient.next);
        printf("\t\t\t\t\t-------------------------------------\n");
    }

    fclose(file_ptr);

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
            Confirm_appointment_bed(filename, choice2);
        }
    }

    pressEnterToContinue();
    clearScreen();
}

void freeLinkedList(PatientInfo *head)
{
    PatientInfo *current = head;
    PatientInfo *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

void confirmation_bed(const char *filename)
{
    FILE *file = fopen(filename, "rb+");
    if (file == NULL)
    {
        printf("Unable to open file %s\n", filename);
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
    while (fread(&patient, sizeof(PatientInfo), 1, file) == 1)
    {
        if (id == patient.serial)
        {

            strcpy(patient.bed, "Pending");

            // Move the file pointer back to the beginning of the current record
            fseek(file, -sizeof(PatientInfo), SEEK_CUR);

            // Write the updated patient data
            fwrite(&patient, sizeof(PatientInfo), 1, file);

            printf("Bed Booking is Pending.\n");
            fclose(file);
            return;
        }
    }

    printf("Patient with ID %d not found.\n", id);
    fclose(file);
}

void deletePatient(int id)
{
    FILE *file_ptr = fopen("patient_info.bin", "rb+"); // Open the file for reading and writing

    FILE *temp = fopen("temp.bin", "wb+");
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

    rewind(file_ptr);
    fclose(file_ptr); // Close the original file

    file_ptr = fopen("patient_info.bin", "wb");
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

    fclose(temp); // Close the temporary file
    if (remove("temp.bin") != 0)
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
    pressEnterToContinue();
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
