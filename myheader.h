#ifndef MYHEADER_H
#define MYHEADER_H
#include "student.h"
#include <stdio.h>

Student * createStudentFromCSVLine(FILE * file);
Student * * readAllStudentsFromCSV(int * count);
void addStudentToCSV(FILE * file, Student *s, int lastStudent);
void writeAllStudentsToCSV(FILE * file, Student * * students, int count);
void testReadCSV();
void testWriteCSV();
void testCalculateGPA();
void testSortByName();
void testSortByID();
void testSortByGPA();

#endif