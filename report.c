#include <stdio.h>
#include "reports.h"

/* Employee Report */
void employeeReport(void)
{
    int i;
    float total = 0;
    float average;
    float highest = 0;
    float lowest = 0;
    float salary;

    printf("\n===== EMPLOYEE REPORT =====\n");

    if (employeeCount == 0)
    {
        printf("No employees available.\n");
        return;
    }

    for (i = 0; i < employeeCount; i++)
    {
        salary =
            basicSalary[i] +
            housingAllowance[i] +
            transportAllowance[i];

        total += salary;

        if (i == 0)
        {
            highest = salary;
            lowest = salary;
        }
        else
        {
            if (salary > highest)
            {
                highest = salary;
            }

            if (salary < lowest)
            {
                lowest = salary;
            }
        }
    }

    average = total / employeeCount;

    printf("Total Employees: %d\n", employeeCount);
    printf("Total Salary: N$ %.2f\n", total);
    printf("Average Salary: N$ %.2f\n", average);
    printf("Highest Salary: N$ %.2f\n", highest);
    printf("Lowest Salary: N$ %.2f\n", lowest);
}

/* Budget Report */
void budgetReport(void)
{
    int i;
    int overBudgetCount = 0;
    float totalAllocated = 0;
    float totalExpenditure = 0;
    float totalRemaining;

    printf("\n===== BUDGET REPORT =====\n");

    if (budgetCount == 0)
    {
        printf("No budgets available.\n");
        return;
    }

    for (i = 0; i < budgetCount; i++)
    {
        totalAllocated += allocatedBudget[i];
        totalExpenditure += expenditure[i];
    }

    totalRemaining =
        totalAllocated - totalExpenditure;

    printf("Total Allocated Budget: N$ %.2f\n",
           totalAllocated);

    printf("Total Expenditure: N$ %.2f\n",
           totalExpenditure);

    printf("Total Remaining Budget: N$ %.2f\n",
           totalRemaining);

    printf("\nDepartments Over Budget:\n");

    for (i = 0; i < budgetCount; i++)
    {
        if (expenditure[i] > allocatedBudget[i])
        {
            printf("- %s\n", budgetDepartment[i]);
            overBudgetCount++;
        }
    }

    if (overBudgetCount == 0)
    {
        printf("No departments are over budget.\n");
    }
}

/* Supplier Report */
void supplierReport(void)
{
    int i;

    printf("\n===== SUPPLIER REPORT =====\n");

    if (supplierCount == 0)
    {
        printf("No suppliers available.\n");
        return;
    }

    printf("Total Suppliers: %d\n", supplierCount);

    for (i = 0; i < supplierCount; i++)
    {
        printf("\nSupplier %d\n", i + 1);
        printf("ID: %d\n", supplierID[i]);
        printf("Name: %s\n", supplierName[i]);
        printf("Email: %s\n", supplierEmail[i]);
        printf("Telephone: %s\n",
               supplierTelephone[i]);
        printf("Town/Location: %s\n",
               supplierTown[i]);
    }
}

/* Asset Report */
void assetReport(void)
{
    int i;
    float totalValue = 0;

    printf("\n===== ASSET REPORT =====\n");

    if (assetCount == 0)
    {
        printf("No assets available.\n");
        return;
    }

    for (i = 0; i < assetCount; i++)
    {
        totalValue += purchaseValue[i];
    }

    printf("Total Assets: %d\n", assetCount);
    printf("Total Asset Value: N$ %.2f\n",
           totalValue);

    printf("\nAsset Details:\n");

    for (i = 0; i < assetCount; i++)
    {
        printf("\nID: %d\n", assetID[i]);
        printf("Name: %s\n", assetName[i]);
        printf("Type: %s\n", assetType[i]);
        printf("Value: N$ %.2f\n",
               purchaseValue[i]);
        printf("Department: %s\n",
               assetDepartment[i]);
        printf("Condition: %s\n",
               assetCondition[i]);
    }
}

/* Reports Menu */
void reportsMenu(void)
{
    int choice;

    do
    {
        printf("\n===== REPORTS =====\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");

        choice = readInt("Choose an option: ", 1, 5);

        switch (choice)
        {
            case 1:
                employeeReport();
                break;

            case 2:
                budgetReport();
                break;

            case 3:
                supplierReport();
                break;

            case 4:
                assetReport();
                break;

            case 5:
                printf("Returning to main menu...\n");
                break;
        }

    } while (choice != 5);
}
