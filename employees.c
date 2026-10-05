#include <stdio.h>
#include <string.h>
#include "employees.h"

/* Employee data */
int employeeID[MAX];
char employeeName[MAX][NAME_LEN];
char employeeDepartment[MAX][DEPT_LEN];
float basicSalary[MAX];
float housingAllowance[MAX];
float transportAllowance[MAX];
int employeeCount = 0;

/* Check whether an employee ID already exists */
int employeeIDExists(int id)
{
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        if (employeeID[i] == id)
        {
            return 1;
        }
    }

    return 0;
}

/* Add employee */
void addEmployee(void)
{
    int id;

    if (employeeCount >= MAX)
    {
        printf("\nEmployee storage is full.\n");
        return;
    }

    printf("\n===== ADD EMPLOYEE =====\n");

    while (1)
    {
        id = readInt("Enter Employee ID: ", 1, 999999);

        if (employeeIDExists(id))
        {
            printf("Employee ID already exists. Please use another ID.\n");
        }
        else
        {
            break;
        }
    }

    employeeID[employeeCount] = id;

    readString(
        "Enter Employee Name: ",
        employeeName[employeeCount],
        NAME_LEN
    );

    readString(
        "Enter Department: ",
        employeeDepartment[employeeCount],
        DEPT_LEN
    );

    basicSalary[employeeCount] =
        readFloat("Enter Basic Salary (N$): ");

    housingAllowance[employeeCount] =
        readFloat("Enter Housing Allowance (N$): ");

    transportAllowance[employeeCount] =
        readFloat("Enter Transport Allowance (N$): ");

    employeeCount++;

    printf("\nEmployee added successfully!\n");
}

/* Display all employees */
void displayEmployees(void)
{
    int i;
    float grossSalary;

    printf("\n===== EMPLOYEE LIST =====\n");

    if (employeeCount == 0)
    {
        printf("No employees have been added yet.\n");
        return;
    }

    for (i = 0; i < employeeCount; i++)
    {
        grossSalary =
            basicSalary[i] +
            housingAllowance[i] +
            transportAllowance[i];

        printf("\nEmployee %d\n", i + 1);
        printf("ID: %d\n", employeeID[i]);
        printf("Name: %s\n", employeeName[i]);
        printf("Department: %s\n", employeeDepartment[i]);
        printf("Basic Salary: N$ %.2f\n", basicSalary[i]);
        printf("Housing Allowance: N$ %.2f\n",
               housingAllowance[i]);
        printf("Transport Allowance: N$ %.2f\n",
               transportAllowance[i]);
        printf("Gross Salary: N$ %.2f\n", grossSalary);
    }
}

/* Search employee */
void searchEmployee(void)
{
    int choice;
    int id;
    int i;
    int found = 0;
    char name[NAME_LEN];

    if (employeeCount == 0)
    {
        printf("\nNo employees have been added yet.\n");
        return;
    }

    printf("\n===== SEARCH EMPLOYEE =====\n");
    printf("1. Search by Employee ID\n");
    printf("2. Search by Employee Name\n");

    choice = readInt("Choose an option: ", 1, 2);

    if (choice == 1)
    {
        id = readInt("Enter Employee ID: ", 1, 999999);

        for (i = 0; i < employeeCount; i++)
        {
            if (employeeID[i] == id)
            {
                printf("\nEmployee found!\n");
                printf("ID: %d\n", employeeID[i]);
                printf("Name: %s\n", employeeName[i]);
                printf("Department: %s\n",
                       employeeDepartment[i]);

                found = 1;
                break;
            }
        }
    }
    else
    {
        readString("Enter Employee Name: ", name, NAME_LEN);

        for (i = 0; i < employeeCount; i++)
        {
            if (strcmp(employeeName[i], name) == 0)
            {
                printf("\nEmployee found!\n");
                printf("ID: %d\n", employeeID[i]);
                printf("Name: %s\n", employeeName[i]);
                printf("Department: %s\n",
                       employeeDepartment[i]);

                found = 1;
                break;
            }
        }
    }

    if (!found)
    {
        printf("\nEmployee not found.\n");
    }
}

/* Calculate employee salary */
void calculateSalary(void)
{
    int id;
    int i;
    int found = 0;
    float grossSalary;

    if (employeeCount == 0)
    {
        printf("\nNo employees have been added yet.\n");
        return;
    }

    printf("\n===== CALCULATE SALARY =====\n");

    id = readInt("Enter Employee ID: ", 1, 999999);

    for (i = 0; i < employeeCount; i++)
    {
        if (employeeID[i] == id)
        {
            grossSalary =
                basicSalary[i] +
                housingAllowance[i] +
                transportAllowance[i];

            printf("\nEmployee: %s\n", employeeName[i]);
            printf("Basic Salary: N$ %.2f\n",
                   basicSalary[i]);
            printf("Housing Allowance: N$ %.2f\n",
                   housingAllowance[i]);
            printf("Transport Allowance: N$ %.2f\n",
                   transportAllowance[i]);
            printf("Gross Salary: N$ %.2f\n",
                   grossSalary);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nEmployee not found.\n");
    }
}

/* Employee menu */
void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Back to Main Menu\n");

        choice = readInt("Choose an option: ", 1, 5);

        switch (choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                calculateSalary();
                break;

            case 5:
                printf("Returning to main menu...\n");
                break;
        }

    } while (choice != 5);
}