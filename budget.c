#include <stdio.h>
#include "budget.h"

/* Budget data */
char budgetDepartment[MAX][DEPT_LEN];
float allocatedBudget[MAX];
float expenditure[MAX];
int budgetCount = 0;

/* Add a departmental budget */
void addBudget(void)
{
    if (budgetCount >= MAX)
    {
        printf("\nBudget storage is full.\n");
        return;
    }

    printf("\n===== ADD BUDGET =====\n");

    readString(
        "Enter Department: ",
        budgetDepartment[budgetCount],
        DEPT_LEN
    );

    allocatedBudget[budgetCount] =
        readFloat("Enter Allocated Budget (N$): ");

    expenditure[budgetCount] =
        readFloat("Enter Expenditure (N$): ");

    budgetCount++;

    printf("\nBudget added successfully!\n");
}

/* Display all budgets */
void displayBudgets(void)
{
    int i;
    float remaining;

    printf("\n===== BUDGET LIST =====\n");

    if (budgetCount == 0)
    {
        printf("No budgets have been added yet.\n");
        return;
    }

    for (i = 0; i < budgetCount; i++)
    {
        remaining =
            allocatedBudget[i] - expenditure[i];

        printf("\nDepartment: %s\n",
               budgetDepartment[i]);

        printf("Allocated Budget: N$ %.2f\n",
               allocatedBudget[i]);

        printf("Expenditure: N$ %.2f\n",
               expenditure[i]);

        printf("Remaining Budget: N$ %.2f\n",
               remaining);

        if (remaining >= 0)
        {
            printf("Status: Within Budget\n");
        }
        else
        {
            printf("Status: OVER BUDGET\n");
        }
    }
}

/* Calculate remaining budget */
void calculateBudget(void)
{
    int i;
    int found = 0;
    float remaining;

    if (budgetCount == 0)
    {
        printf("\nNo budgets have been added yet.\n");
        return;
    }

    printf("\n===== CALCULATE BUDGET =====\n");

    for (i = 0; i < budgetCount; i++)
    {
        remaining =
            allocatedBudget[i] - expenditure[i];

        printf("\nDepartment: %s\n",
               budgetDepartment[i]);

        printf("Allocated: N$ %.2f\n",
               allocatedBudget[i]);

        printf("Expenditure: N$ %.2f\n",
               expenditure[i]);

        printf("Remaining: N$ %.2f\n",
               remaining);

        if (remaining >= 0)
        {
            printf("Status: Within Budget\n");
        }
        else
        {
            printf("Status: OVER BUDGET\n");
            found = 1;
        }
    }

    if (!found)
    {
        printf("\nNo departments are over budget.\n");
    }
}

/* Budget menu */
void budgetMenu(void)
{
    int choice;

    do
    {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Add Budget\n");
        printf("2. Display Budgets\n");
        printf("3. Calculate Budget\n");
        printf("4. Back to Main Menu\n");

        choice = readInt("Choose an option: ", 1, 4);

        switch (choice)
        {
            case 1:
                addBudget();
                break;

            case 2:
                displayBudgets();
                break;

            case 3:
                calculateBudget();
                break;

            case 4:
                printf("Returning to main menu...\n");
                break;
        }

    } while (choice != 4);
}