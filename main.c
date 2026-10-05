/* ============================================================
   MUNICIPAL FINANCIAL MANAGEMENT SYSTEM
   Group Project - First Year, Second Semester
   
   GROUP 1 - Employee Management
   GROUP 2 - Budget Management
   GROUP 3 - Supplier Management
   GROUP 4 - Asset Management, Reports & Main Menu
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* =========================
   COMMON DEFINITIONS
   (used by all groups)
   ========================= */

#define MAX 100
#define NAME_LEN 50
#define EMAIL_LEN 60
#define TEL_LEN 30
#define DEPT_LEN 50
#define TYPE_LEN 50
#define COND_LEN 30

/* =========================
   FUNCTION PROTOTYPES
   ========================= */

/* Input helpers (shared) */
void  clearInputBuffer(void);
int   readInt(const char *prompt, int min, int max);
float readFloat(const char *prompt);
void  readString(const char *prompt, char *buffer, int size);

/* Group 1 - Employee */
void employeeMenu(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void calculateSalary(void);
int  employeeIDExists(int id);

/* Group 2 - Budget */
void budgetMenu(void);
void addBudget(void);
void displayBudgets(void);
void calculateBudget(void);

/* Group 3 - Supplier */
void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
int  supplierIDExists(int id);

/* Group 4 - Asset, Reports, Main */
void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);
int  assetIDExists(int id);

void reportsMenu(void);
void employeeReport(void);
void budgetReport(void);
void supplierReport(void);
void assetReport(void);

void displayMenu(void);

/* ============================================================
   SHARED INPUT HELPER FUNCTIONS
   (used by all 4 groups)
   ============================================================ */

void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int readInt(const char *prompt, int min, int max)
{
    char line[100];
    char *end;
    long value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("Input error. Try again.\n");
            continue;
        }

        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '\0')
        {
            printf("Input cannot be empty.\n");
            continue;
        }

        value = strtol(line, &end, 10);

        if (*end != '\0')
        {
            printf("Invalid number. Please enter digits only.\n");
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
    char line[100];
    char *end;
    double value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("Input error. Try again.\n");
            continue;
        }

        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '\0')
        {
            printf("Input cannot be empty.\n");
            continue;
        }

        value = strtod(line, &end);

        if (*end != '\0')
        {
            printf("Invalid number. Please enter a valid amount.\n");
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
            printf("Input error. Try again.\n");
            continue;
        }

        if (strchr(buffer, '\n') == NULL)
        {
            clearInputBuffer();
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0)
        {
            printf("Input cannot be empty.\n");
            continue;
        }

        return;
    }
}

/* ============================================================
   GROUP 1 - EMPLOYEE MANAGEMENT
   ============================================================ */

int employeeID[MAX];
char employeeName[MAX][NAME_LEN];
char employeeDepartment[MAX][DEPT_LEN];
float basicSalary[MAX];
float housingAllowance[MAX];
float transportAllowance[MAX];

int employeeCount = 0;

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

void addEmployee(void)
{
    int id;

    if (employeeCount >= MAX)
    {
        printf("Employee storage is full.\n");
        return;
    }

    do
    {
        id = readInt("Enter Employee ID: ", 1, 999999);

        if (employeeIDExists(id))
        {
            printf("Employee ID already exists.\n");
        }

    } while (employeeIDExists(id));

    employeeID[employeeCount] = id;

    readString("Enter Employee Name: ", employeeName[employeeCount], NAME_LEN);
    readString("Enter Department: ", employeeDepartment[employeeCount], DEPT_LEN);

    basicSalary[employeeCount]        = readFloat("Enter Basic Salary: N$");
    housingAllowance[employeeCount]   = readFloat("Enter Housing Allowance: N$");
    transportAllowance[employeeCount] = readFloat("Enter Transport Allowance: N$");

    employeeCount++;

    printf("\nEmployee added successfully!\n");
}

void displayEmployees(void)
{
    int i;
    float gross;

    if (employeeCount == 0)
    {
        printf("\nNo employees registered.\n");
        return;
    }

    printf("\n================ EMPLOYEES ================\n");

    for (i = 0; i < employeeCount; i++)
    {
        gross = basicSalary[i] + housingAllowance[i] + transportAllowance[i];

        printf("\nEmployee ID: %d\n", employeeID[i]);
        printf("Name: %s\n", employeeName[i]);
        printf("Department: %s\n", employeeDepartment[i]);
        printf("Basic Salary: N$%.2f\n", basicSalary[i]);
        printf("Housing Allowance: N$%.2f\n", housingAllowance[i]);
        printf("Transport Allowance: N$%.2f\n", transportAllowance[i]);
        printf("Gross Salary: N$%.2f\n", gross);
    }
}

void searchEmployee(void)
{
    int option;
    int id;
    int i;
    int found = 0;
    char searchName[NAME_LEN];

    printf("\nSearch Employee by:\n");
    printf("1. ID\n");
    printf("2. Name\n");

    option = readInt("Enter option: ", 1, 2);

    if (option == 1)
    {
        id = readInt("Enter Employee ID to search: ", 1, 999999);

        for (i = 0; i < employeeCount; i++)
        {
            if (employeeID[i] == id)
            {
                printf("\nEmployee found!\n");
                printf("Name: %s\n", employeeName[i]);
                printf("Department: %s\n", employeeDepartment[i]);
                printf("Basic Salary: N$%.2f\n", basicSalary[i]);

                found = 1;
                break;
            }
        }
    }
    else
    {
        readString("Enter Employee Name to search: ", searchName, NAME_LEN);

        for (i = 0; i < employeeCount; i++)
        {
            if (strcmp(employeeName[i], searchName) == 0)
            {
                printf("\nEmployee found!\n");
                printf("ID: %d\n", employeeID[i]);
                printf("Department: %s\n", employeeDepartment[i]);
                printf("Basic Salary: N$%.2f\n", basicSalary[i]);

                found = 1;
            }
        }
    }

    if (!found)
    {
        printf("Employee not found.\n");
    }
}

void calculateSalary(void)
{
    int id;
    int i;
    float grossSalary;
    int found = 0;

    id = readInt("Enter Employee ID: ", 1, 999999);

    for (i = 0; i < employeeCount; i++)
    {
        if (employeeID[i] == id)
        {
            grossSalary =
                basicSalary[i]
                + housingAllowance[i]
                + transportAllowance[i];

            printf("\nEmployee: %s\n", employeeName[i]);
            printf("Basic Salary: N$%.2f\n", basicSalary[i]);
            printf("Housing Allowance: N$%.2f\n", housingAllowance[i]);
            printf("Transport Allowance: N$%.2f\n", transportAllowance[i]);
            printf("Gross Salary: N$%.2f\n", grossSalary);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Employee not found.\n");
    }
}

void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("        EMPLOYEE MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Employee Salary\n");
        printf("5. Back\n");

        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1: addEmployee();      break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee();   break;
            case 4: calculateSalary();  break;
            case 5: break;
        }

    } while (choice != 5);
}

/* ============================================================
   GROUP 2 - BUDGET MANAGEMENT
   ============================================================ */

char budgetDepartment[MAX][DEPT_LEN];
float allocatedBudget[MAX];
float expenditure[MAX];

int budgetCount = 0;

void addBudget(void)
{
    if (budgetCount >= MAX)
    {
        printf("Budget storage is full.\n");
        return;
    }

    readString("Enter Department: ", budgetDepartment[budgetCount], DEPT_LEN);

    allocatedBudget[budgetCount] = readFloat("Enter Allocated Budget: N$");
    expenditure[budgetCount]     = readFloat("Enter Expenditure: N$");

    budgetCount++;

    printf("\nBudget added successfully!\n");
}

void displayBudgets(void)
{
    int i;
    float remaining;

    if (budgetCount == 0)
    {
        printf("\nNo budgets registered.\n");
        return;
    }

    printf("\n================ BUDGETS ================\n");

    for (i = 0; i < budgetCount; i++)
    {
        remaining = allocatedBudget[i] - expenditure[i];

        printf("\nDepartment: %s\n", budgetDepartment[i]);
        printf("Allocated Budget: N$%.2f\n", allocatedBudget[i]);
        printf("Expenditure: N$%.2f\n", expenditure[i]);
        printf("Remaining Budget: N$%.2f\n", remaining);

        if (expenditure[i] <= allocatedBudget[i])
        {
            printf("Status: WITHIN BUDGET\n");
        }
        else
        {
            printf("Status: OVER BUDGET\n");
        }
    }
}

void calculateBudget(void)
{
    int i;

    if (budgetCount == 0)
    {
        printf("\nNo budgets registered.\n");
        return;
    }

    printf("\n========== BUDGET STATUS ==========\n");

    for (i = 0; i < budgetCount; i++)
    {
        printf("%s: ", budgetDepartment[i]);

        if (expenditure[i] <= allocatedBudget[i])
        {
            printf("WITHIN BUDGET\n");
        }
        else
        {
            printf("OVER BUDGET\n");
        }
    }
}

void budgetMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("          BUDGET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Budget\n");
        printf("2. Display Budgets\n");
        printf("3. Calculate Budget Status\n");
        printf("4. Back\n");

        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice)
        {
            case 1: addBudget();       break;
            case 2: displayBudgets();  break;
            case 3: calculateBudget(); break;
            case 4: break;
        }

    } while (choice != 4);
}

/* ============================================================
   GROUP 3 - SUPPLIER MANAGEMENT
   ============================================================ */

int supplierID[MAX];
char supplierName[MAX][NAME_LEN];
char supplierEmail[MAX][EMAIL_LEN];
char supplierTelephone[MAX][TEL_LEN];
char supplierTown[MAX][DEPT_LEN];

int supplierCount = 0;

int supplierIDExists(int id)
{
    int i;
    for (i = 0; i < supplierCount; i++)
    {
        if (supplierID[i] == id)
        {
            return 1;
        }
    }
    return 0;
}

void addSupplier(void)
{
    int id;

    if (supplierCount >= MAX)
    {
        printf("Supplier storage is full.\n");
        return;
    }

    do
    {
        id = readInt("Enter Supplier ID: ", 1, 999999);

        if (supplierIDExists(id))
        {
            printf("Supplier ID already exists.\n");
        }

    } while (supplierIDExists(id));

    supplierID[supplierCount] = id;

    readString("Enter Supplier Name: ", supplierName[supplierCount], NAME_LEN);
    readString("Enter Email: ", supplierEmail[supplierCount], EMAIL_LEN);
    readString("Enter Telephone Number: ", supplierTelephone[supplierCount], TEL_LEN);
    readString("Enter Town/Location: ", supplierTown[supplierCount], DEPT_LEN);

    supplierCount++;

    printf("\nSupplier added successfully!\n");
}

void displaySuppliers(void)
{
    int i;

    if (supplierCount == 0)
    {
        printf("\nNo suppliers registered.\n");
        return;
    }

    printf("\n================ SUPPLIERS ================\n");

    for (i = 0; i < supplierCount; i++)
    {
        printf("\nSupplier ID: %d\n", supplierID[i]);
        printf("Name: %s\n", supplierName[i]);
        printf("Email: %s\n", supplierEmail[i]);
        printf("Telephone: %s\n", supplierTelephone[i]);
        printf("Town/Location: %s\n", supplierTown[i]);
    }
}

void searchSupplier(void)
{
    int option;
    int id;
    int i;
    int found = 0;
    char searchName[NAME_LEN];

    printf("\nSearch Supplier by:\n");
    printf("1. ID\n");
    printf("2. Name\n");

    option = readInt("Enter option: ", 1, 2);

    if (option == 1)
    {
        id = readInt("Enter Supplier ID to search: ", 1, 999999);

        for (i = 0; i < supplierCount; i++)
        {
            if (supplierID[i] == id)
            {
                printf("\nSupplier found!\n");
                printf("Name: %s\n", supplierName[i]);
                printf("Email: %s\n", supplierEmail[i]);
                printf("Telephone: %s\n", supplierTelephone[i]);
                printf("Town: %s\n", supplierTown[i]);

                found = 1;
                break;
            }
        }
    }
    else
    {
        readString("Enter Supplier Name to search: ", searchName, NAME_LEN);

        for (i = 0; i < supplierCount; i++)
        {
            if (strcmp(supplierName[i], searchName) == 0)
            {
                printf("\nSupplier found!\n");
                printf("ID: %d\n", supplierID[i]);
                printf("Email: %s\n", supplierEmail[i]);
                printf("Telephone: %s\n", supplierTelephone[i]);
                printf("Town: %s\n", supplierTown[i]);

                found = 1;
            }
        }
    }

    if (!found)
    {
        printf("Supplier not found.\n");
    }
}

void supplierMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("         SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back\n");

        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice)
        {
            case 1: addSupplier();      break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier();   break;
            case 4: break;
        }

    } while (choice != 4);
}

/* ============================================================
   GROUP 4 - ASSET MANAGEMENT, REPORTS & MAIN MENU
   ============================================================ */

int assetID[MAX];
char assetName[MAX][NAME_LEN];
char assetType[MAX][TYPE_LEN];
float purchaseValue[MAX];
char assetDepartment[MAX][DEPT_LEN];
char assetCondition[MAX][COND_LEN];

int assetCount = 0;

int assetIDExists(int id)
{
    int i;
    for (i = 0; i < assetCount; i++)
    {
        if (assetID[i] == id)
        {
            return 1;
        }
    }
    return 0;
}

void addAsset(void)
{
    int id;

    if (assetCount >= MAX)
    {
        printf("Asset storage is full.\n");
        return;
    }

    do
    {
        id = readInt("Enter Asset ID: ", 1, 999999);

        if (assetIDExists(id))
        {
            printf("Asset ID already exists.\n");
        }

    } while (assetIDExists(id));

    assetID[assetCount] = id;

    readString("Enter Asset Name: ", assetName[assetCount], NAME_LEN);
    readString("Enter Asset Type: ", assetType[assetCount], TYPE_LEN);

    purchaseValue[assetCount] = readFloat("Enter Purchase Value: N$");

    readString("Enter Department: ", assetDepartment[assetCount], DEPT_LEN);
    readString("Enter Condition: ", assetCondition[assetCount], COND_LEN);

    assetCount++;

    printf("\nAsset added successfully!\n");
}

void displayAssets(void)
{
    int i;

    if (assetCount == 0)
    {
        printf("\nNo assets registered.\n");
        return;
    }

    printf("\n================ ASSETS ================\n");

    for (i = 0; i < assetCount; i++)
    {
        printf("\nAsset ID: %d\n", assetID[i]);
        printf("Name: %s\n", assetName[i]);
        printf("Type: %s\n", assetType[i]);
        printf("Purchase Value: N$%.2f\n", purchaseValue[i]);
        printf("Department: %s\n", assetDepartment[i]);
        printf("Condition: %s\n", assetCondition[i]);
    }
}

void searchAsset(void)
{
    int option;
    int id;
    int i;
    int found = 0;
    char searchName[NAME_LEN];

    printf("\nSearch Asset by:\n");
    printf("1. ID\n");
    printf("2. Name\n");

    option = readInt("Enter option: ", 1, 2);

    if (option == 1)
    {
        id = readInt("Enter Asset ID to search: ", 1, 999999);

        for (i = 0; i < assetCount; i++)
        {
            if (assetID[i] == id)
            {
                printf("\nAsset found!\n");
                printf("Name: %s\n", assetName[i]);
                printf("Type: %s\n", assetType[i]);
                printf("Purchase Value: N$%.2f\n", purchaseValue[i]);
                printf("Department: %s\n", assetDepartment[i]);
                printf("Condition: %s\n", assetCondition[i]);

                found = 1;
                break;
            }
        }
    }
    else
    {
        readString("Enter Asset Name to search: ", searchName, NAME_LEN);

        for (i = 0; i < assetCount; i++)
        {
            if (strcmp(assetName[i], searchName) == 0)
            {
                printf("\nAsset found!\n");
                printf("ID: %d\n", assetID[i]);
                printf("Type: %s\n", assetType[i]);
                printf("Purchase Value: N$%.2f\n", purchaseValue[i]);
                printf("Department: %s\n", assetDepartment[i]);
                printf("Condition: %s\n", assetCondition[i]);

                found = 1;
            }
        }
    }

    if (!found)
    {
        printf("Asset not found.\n");
    }
}

void assetMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("           ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back\n");

        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice)
        {
            case 1: addAsset();      break;
            case 2: displayAssets(); break;
            case 3: searchAsset();   break;
            case 4: break;
        }

    } while (choice != 4);
}

/* ---------- REPORTS ---------- */

void employeeReport(void)
{
    int i;
    float total = 0;
    float average;
    float highest;
    float lowest;
    float salary;

    if (employeeCount == 0)
    {
        printf("\nNo employee data available.\n");
        return;
    }

    highest = basicSalary[0] + housingAllowance[0] + transportAllowance[0];
    lowest = highest;

    for (i = 0; i < employeeCount; i++)
    {
        salary = basicSalary[i] + housingAllowance[i] + transportAllowance[i];
        total += salary;

        if (salary > highest) highest = salary;
        if (salary < lowest)  lowest  = salary;
    }

    average = total / employeeCount;

    printf("\n========== EMPLOYEE REPORT ==========\n");
    printf("Total Employees: %d\n", employeeCount);
    printf("Average Salary: N$%.2f\n", average);
    printf("Highest Salary: N$%.2f\n", highest);
    printf("Lowest Salary: N$%.2f\n", lowest);
}

void budgetReport(void)
{
    int i;
    int overBudget = 0;
    float totalAllocated = 0;
    float totalExpenditure = 0;
    float remaining;

    if (budgetCount == 0)
    {
        printf("\nNo budget data available.\n");
        return;
    }

    for (i = 0; i < budgetCount; i++)
    {
        totalAllocated   += allocatedBudget[i];
        totalExpenditure += expenditure[i];
    }

    remaining = totalAllocated - totalExpenditure;

    printf("\n========== BUDGET REPORT ==========\n");
    printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
    printf("Total Expenditure: N$%.2f\n", totalExpenditure);
    printf("Remaining Budget: N$%.2f\n", remaining);

    printf("\nDepartments Exceeding Budget:\n");

    for (i = 0; i < budgetCount; i++)
    {
        if (expenditure[i] > allocatedBudget[i])
        {
            printf("- %s\n", budgetDepartment[i]);
            overBudget = 1;
        }
    }

    if (!overBudget)
    {
        printf("- None\n");
    }
}

void supplierReport(void)
{
    int i;

    printf("\n========== SUPPLIER REPORT ==========\n");

    if (supplierCount == 0)
    {
        printf("No suppliers registered.\n");
        return;
    }

    printf("Total Suppliers: %d\n", supplierCount);

    for (i = 0; i < supplierCount; i++)
    {
        printf("\n%d. %s\n", supplierID[i], supplierName[i]);
        printf("Email: %s\n", supplierEmail[i]);
        printf("Telephone: %s\n", supplierTelephone[i]);
        printf("Town: %s\n", supplierTown[i]);
    }
}

void assetReport(void)
{
    int i;

    printf("\n========== ASSET REPORT ==========\n");

    if (assetCount == 0)
    {
        printf("No assets registered.\n");
        return;
    }

    printf("Total Assets: %d\n", assetCount);

    for (i = 0; i < assetCount; i++)
    {
        printf("\nAsset ID: %d\n", assetID[i]);
        printf("Name: %s\n", assetName[i]);
        printf("Type: %s\n", assetType[i]);
        printf("Value: N$%.2f\n", purchaseValue[i]);
        printf("Department: %s\n", assetDepartment[i]);
        printf("Condition: %s\n", assetCondition[i]);
    }
}

void reportsMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("                 REPORTS\n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back\n");

        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1: employeeReport(); break;
            case 2: budgetReport();   break;
            case 3: supplierReport(); break;
            case 4: assetReport();    break;
            case 5: break;
        }

    } while (choice != 5);
}

/* ---------- MAIN MENU ---------- */

void displayMenu(void)
{
    printf("\n========================================\n");
    printf("   MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
    printf("========================================\n");
}

int main(void)
{
    int choice;

    do
    {
        displayMenu();
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice)
        {
            case 1: employeeMenu(); break;
            case 2: budgetMenu();   break;
            case 3: supplierMenu(); break;
            case 4: assetMenu();    break;
            case 5: reportsMenu();  break;
            case 6:
                printf("\nThank you for using the Municipal Financial Management System.\n");
                break;
        }

    } while (choice != 6);

    return 0;
}

/* ============================================================
   END OF PROGRAM
   ============================================================ */