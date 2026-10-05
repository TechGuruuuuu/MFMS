#include <stdio.h>

#include "common.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

/* Main Menu */
void displayMenu(void)
{
    printf("\n");
    printf("============================================\n");
    printf("     MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("============================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
    printf("============================================\n");
}

/* Main Program */
int main(void)
{
    int choice;

    printf("\nWelcome to the Municipal Financial Management System!\n");

    do
    {
        displayMenu();

        choice = readInt("Choose an option: ", 1, 6);

        switch (choice)
        {
            case 1:
                employeeMenu();
                break;

            case 2:
                budgetMenu();
                break;

            case 3:
                supplierMenu();
                break;

            case 4:
                assetMenu();
                break;

            case 5:
                reportsMenu();
                break;

            case 6:
                printf("\nThank you for using the MFMS.\n");
                printf("Goodbye!\n");
                break;
        }

    } while (choice != 6);

    return 0;
}