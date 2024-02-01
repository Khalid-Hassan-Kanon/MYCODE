#include <stdio.h>
#include <conio.h>
#include <string.h>

int main()
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
        else if (i < 49)
        { // Limit the password to 49 characters
            pass[i++] = ch;
            printf("*");
        }
    }

    int c = strcmp(paSs, pass);
    if (c == 0)
    {
        printf("\nACCESS GRANTED\n");
    }
    else
    {
        printf("\nACCESS DENIED\n");
    }

    return 0;
}
