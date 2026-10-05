#ifndef COMMON_H
#define COMMON_H

#define MAX 100
#define NAME_LEN 50
#define EMAIL_LEN 60
#define TEL_LEN 30
#define DEPT_LEN 50
#define TYPE_LEN 50
#define COND_LEN 30

void clearInputBuffer(void);
int readInt(const char *prompt, int min, int max);
float readFloat(const char *prompt);
void readString(const char *prompt, char *buffer, int size);

#endif