#include <stdio.h>
#include <stdlib.h>

int appointment();
void confirmation();
int adminAccess();
int information();

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
    int choice;

    while (1)
    {

        clearScreen();
        printf("ENTER 1 FOR ADMIN ACCESS\n");
        printf("ENTER 2 FOR APPOINTMENT\n");
        printf("ENTER 3 FOR MORE INFORMATION\n");
        printf("ENTER 0 FOR EXIT\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            adminAccess(); // Call adminAccess function
            break;
        case 2:
            appointment();
            break;
        case 3:
            information();
            break;
        case 0:
            printf("Exiting the program. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

int appointment()
{
    pressEnterToContinue();

    clearScreen();
    int choice;
    printf("ENTER 0 FOR Registration\n");
    printf("ENTER ID IF ALREADY HAVE Registration\n");
    scanf("%d", &choice);

    if (choice == 0)
    {

        clearScreen();
        printf("NAME:\n");
        printf("AGE:\n");
        printf("NUMBER:\n");
        printf("DOCTOR:\n");
        printf("gender (M/F): \n");
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
        printf("ROOM NUMBER\n");
        printf("SERIAL NUMBER\n");
    }
    else
    {
        printf("COME BACK AFTER SOME TIME\n");
    }
}

int adminAccess()
{

    printf("\t\t1. Appoint Patient in Bed\n");
    printf("\t\t2. Display Patients(their will be a function for giving Patients SERIAL NUMBER)\n");
    printf("\t\t3. DOCTOR SALARY(PASSWORD NEEDED)\n");
    printf("\t\t4. Appoint NEW DOCTOR Patients\n");
    printf("\t\t5. Make Bill\n");
    printf("\t\t6.For Update Blood Bank\n");
    pressEnterToContinue();
    clearScreen();

    return 0;
}

int information()
{
    printf("\t\tavailable doctor.\n");
    printf("\t\tdoctor time table.\n");
    printf("\t\tavailable blood.\n");
    printf("\t\temergency number.\n");
    pressEnterToContinue();

    clearScreen();

    return 0;
}
