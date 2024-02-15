#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

int appointment();
void confirmation();
int adminAccess();
int information();
int PASSWORD();
void waiting();
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
    printf("\n\t\t\tPress Enter to continue...");
    while (getchar() != '\n')
        ;      // Clear input buffer
    getchar(); // Wait for Enter
}

int main()
{
    int choice, re;

    while (1)
    {
        clearScreen();
        printf("\n\n\n");
        printf("\n\n\n"); // Add spacing for better alignment
        printf("\t\t\t\t#################################################\n");
        printf("\t\t\t\t#               MAIN MENU                       #\n");
        printf("\t\t\t\t#################################################\n");
        printf("\t\t\t\t#  ENTER 1 FOR ADMIN ACCESS                     #\n");
        printf("\t\t\t\t#  ENTER 2 FOR APPOINTMENT                      #\n");
        printf("\t\t\t\t#  ENTER 3 FOR MORE INFORMATION                 #\n");
        printf("\t\t\t\t#  ENTER 0 FOR EXIT                             #\n");
        printf("\t\t\t\t#################################################\n\n");
        printf("\t\t\t\tENTER Your choice: "); // Prompt for user input
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:

            re = PASSWORD();
            if (re == 1)
            {
                adminAccess(); // Call adminAccess function
            }
            break;
        case 2:
            appointment();
            break;
        case 3:
            information();
            break;
        case 0:
            printf("\t\t\t\t#####################################################################\n");
            printf("\t\t\t\t#               Exiting the program. Goodbye!                       #\n");
            printf("\t\t\t\t#####################################################################\n");
            exit(0);
        default:
            printf("\t\t\t\tInvalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

int appointment()
{
    pressEnterToContinue();

    clearScreen();
    int choice;
    printf("\t\t\t\t#################################################\n");
    printf("\t\t\t\t#           Appointment     MENU                #\n");
    printf("\t\t\t\t#################################################\n");
    printf("\t\t\t\t# 0. FOR Registration                           #\n");
    printf("\t\t\t\t# ENTER ID IF ALREADY HAVE Registration         #\n");
    printf("\t\t\t\t#################################################\n\n");
    scanf("%d", &choice);

    if (choice == 0)
    {

        clearScreen();

        printf("\t\tNAME:            \n");
        printf("\t\tAGE:             \n");
        printf("\t\tNUMBER:          \n");
        printf("\t\tDOCTOR:          \n");
        printf("\t\tgender (M/F): :  \n");
        printf("\t\t# 0. Back to Main Menu \n");
    }
    else
    {

        printf("Confirmation...\n");
        confirmation();
    }
    pressEnterToContinue();

    clearScreen();
    return 0;
}

void confirmation()
{
    int confirmation_code = 1;
    if (confirmation_code == 1)
    {
        printf("\t\t\t\tROOM NUMBER\n");
        printf("\t\t\t\tSERIAL NUMBER\n");
    }
    else
    {
        printf("\t\t\t\tCOME BACK AFTER SOME TIME\n");
    }
}

int adminAccess()
{
    int choice, re;

    while (1)
    {
        clearScreen();

        printf("\n\n\n"); // Add spacing for better alignment
        printf("\t\t\t\t#################################################\n");
        printf("\t\t\t\t#               MAIN MENU                       #\n");
        printf("\t\t\t\t#################################################\n");
        printf("\t\t\t\t# 1. Appoint Patient in Bed                      #\n");
        printf("\t\t\t\t# 2. Display Patients (Serial Number required)   #\n");
        printf("\t\t\t\t# 3. DOCTOR SALARY (PASSWORD NEEDED)             #\n");
        printf("\t\t\t\t# 4. Appoint NEW DOCTOR Patients                #\n");
        printf("\t\t\t\t# 5. Make Bill                                   #\n");
        printf("\t\t\t\t# 6. Update Blood Bank                           #\n");
        printf("\t\t\t\t# 0. EXIT                                        #\n");
        printf("\t\t\t\t#################################################\n\n");
        printf("\t\t\t\tENTER Your choice: "); // Prompt for user input
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            // Handle case 1
            break;
        case 2:
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
            // Handle case 4
            break;
        case 5:
            // Handle case 5
            break;
        case 6:
            // Handle case 6
            break;
        case 0:
            return 0; // Exit the function
        default:
            printf("\t\t\t\tInvalid choice. Please enter a valid option.\n");
        }
    }
    return 0;
}

int information()
{
    clearScreen();
    printf("\n\n\n"); // Add spacing for better alignment
    printf("\t\t\t\t#################################################\n");
    printf("\t\t\t\t#               MORE INFORMATION MENU           #\n");
    printf("\t\t\t\t#################################################\n");
    printf("\t\t\t\t# 1. Available Doctors                          #\n");
    printf("\t\t\t\t# 2. Doctor Time Table                          #\n");
    printf("\t\t\t\t# 3. Available Blood                            #\n");
    printf("\t\t\t\t# 4. Emergency Number                           #\n");
    printf("\t\t\t\t# 0. Back to Main Menu                          #\n");
    printf("\t\t\t\t#################################################\n\n");
    printf("\t\t\t\tEnter your choice: ");

    pressEnterToContinue();

    clearScreen();

    return 0;
}
int PASSWORD()
{
    int i = 0;
    char pass[50], ch, paSs[] = "hello world";

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
        printf("\t\t#################################################\n");
        printf("\t\t#               ACCESS GRANTED                  #\n");
        printf("\t\t#               ACCESS GRANTED                  #\n");
        printf("\t\t#################################################\n\n");
        waiting();
        return 1;
    }
    else
    {
        clearScreen();

        printf("\n\n\n"); // Add some spacing for better alignment
        printf("\t\t#################################################\n");
        printf("\t\t#               ACCESS DENIED                   #\n");
        printf("\t\t#              ACCESS DENIED                    #\n");
        printf("\t\t#################################################\n\n");

        waiting();
        return 0;
    }
}
void waiting()
{

    const char pattern[] = {'\\', '|', '/', '-'};
    int i = 0;

    printf("\t\t\t\t\t Please wait   "); // Add spacing for the pattern

    for (int i = 0; i < 7; i++)
    {                // Loop 10 times
        printf("*"); // Print a dot

        Sleep(500); // Sleep for another 500 milliseconds
    }
}
