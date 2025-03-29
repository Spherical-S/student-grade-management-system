#ifndef MYHEADER_H
#define MYHEADER_H
#include "student.h"
#include <stdio.h>

Student * createStudentFromCSVLine(FILE * file);
StudentList * readAllStudentsFromCSV();
void addStudentToCSV(FILE * file, Student *s, int lastStudent);
void writeAllStudentsToCSV(FILE * file, StudentList * sList);
void testReadCSV();
void testWriteCSV();
void testCalculateGPA();
void testSortByName();
void testSortByID();
void testSortByGPA();

#endif