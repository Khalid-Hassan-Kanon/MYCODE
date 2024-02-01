#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int UserChoice()
{
    int choice;
    printf("Enter your choice:\n");
    printf("1. Rock\n");
    printf("2. Paper\n");
    printf("3. Scissors\n");
    scanf("%d", &choice);
    return choice;
}
int compterChoice()
{
    int choice;
    srand(time(NULL));
    int randomNumber = rand() % 3 + 1;

    if (randomNumber == 1)
    {
        return 1;
    }
    else if (randomNumber == 2)
    {
        return 2;
    }
    else
    {
        return 3;
    }
    return choice;
}

int main()
{

    int userchoice = UserChoice();
    printf("Your choice : ");
    switch (userchoice)
    {
    case 1:
        printf("Rock\n");
        break;
    case 2:
        printf("Paper\n");
        break;
    case 3:
        printf("Scissors\n");
        break;
    default:
        break;
    }
    printf("Computer choice : ");

    int CompterChoice = compterChoice();
    switch (CompterChoice)
    {
    case 1:
        printf("Rock\n");
        break;
    case 2:
        printf("Paper\n");
        break;
    case 3:
        printf("Scissors\n");
        break;
    default:
        break;
    }
    if (userchoice == CompterChoice)
    {
        printf("It's a tie!\n");
    }
    else if (userchoice == 1 && CompterChoice == 2 || userchoice == 2 && CompterChoice == 3 || userchoice == 3 && CompterChoice == 1)
    {
        printf("Computer Wins\n");
    }
    else
    {
        printf("You Wins\n");
    }

    return 0;
}