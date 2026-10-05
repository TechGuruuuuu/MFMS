#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "common.h"

/* Employee data */
extern int employeeID[MAX];
extern char employeeName[MAX][NAME_LEN];
extern char employeeDepartment[MAX][DEPT_LEN];
extern float basicSalary[MAX];
extern float housingAllowance[MAX];
extern float transportAllowance[MAX];
extern int employeeCount;

/* Employee functions */
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void calculateSalary(void);
void employeeMenu(void);

#endif