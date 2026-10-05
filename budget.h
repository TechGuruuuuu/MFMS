#ifndef BUDGET_H
#define BUDGET_H

#include "common.h"

/* Budget data */
extern char budgetDepartment[MAX][DEPT_LEN];
extern float allocatedBudget[MAX];
extern float expenditure[MAX];
extern int budgetCount;

/* Budget functions */
void addBudget(void);
void displayBudgets(void);
void calculateBudget(void);
void budgetMenu(void);
void budgetReport(void);

#endif