#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void clearInputBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear remaining input */
    }
}

int readInt(const char *prompt, int min, int max)
{
    char input[100];
    char *end;
    long value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            continue;
        }

        value = strtol(input, &end, 10);

        while (*end == ' ' || *end == '\t')
        {
            end++;
        }

        if (*end != '\n' && *end != '\0')
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (value < min || value > max)
        {
            printf("Please enter a value between %d and %d.\n", min, max);
            continue;
        }

        return (int)value;
    }
}

float readFloat(const char *prompt)
{
    char input[100];
    char *end;
    double value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            continue;
        }

        value = strtod(input, &end);

        while (*end == ' ' || *end == '\t')
        {
            end++;
        }

        if (*end != '\n' && *end != '\0')
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (value < 0)
        {
            printf("Value cannot be negative.\n");
            continue;
        }

        return (float)value;
    }
}

void readString(const char *prompt, char *buffer, int size)
{
    while (1)
    {
        printf("%s", prompt);

        if (fgets(buffer, size, stdin) == NULL)
        {
            continue;
        }

        if (strchr(buffer, '\n') == NULL)
        {
            clearInputBuffer();
        }
        else
        {
            buffer[strcspn(buffer, "\n")] = '\0';
        }

        if (strlen(buffer) == 0)
        {
            printf("Input cannot be empty. Please try again.\n");
            continue;
        }

        return;
    }
}