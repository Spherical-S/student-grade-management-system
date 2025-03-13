#ifndef MYHEADER_H
#define MYHEADER_H
#include "student.h"
#include <stdio.h>

Student * createStudentFromCSVLine(FILE * file);
int appendStudentToCSV(Student *s);

#endif