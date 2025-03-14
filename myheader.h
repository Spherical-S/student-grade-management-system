#ifndef MYHEADER_H
#define MYHEADER_H
#include "student.h"
#include <stdio.h>

Student * createStudentFromCSVLine(FILE * file);
int addStudentToCSV(FILE * file, Student *s);
int writeAllStudentsToCSV(Student * * students, int count);

#endif