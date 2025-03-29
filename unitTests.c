#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "myheader.h"

//Test 0: reading CSV
void testReadCSV(){
    FILE * fptr = fopen("expected/testStudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    StudentList * students = studentListConstruct();

    Student * s1;
    Student * s2;
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);

    students->head = s1;
    s1->next = s2;
    s2->next = s3;
    students->count = 3;

    printf("%d %s\n", s1->ID, s1->name);
    printf("%d %s\n", s2->ID, s2->name);
    printf("%d %s\n", s3->ID, s3->name);

    studentListDestruct(s1, students);

    fclose(fptr);
}

//Test 1: writing CSV
void testWriteCSV(){

    FILE * fptr = fopen("expected/testWriteStudentData.csv", "w");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    StudentList * students = studentListConstruct();

    Student * s1;
    Student * s2;

    s1 = studentConstruct(123456, "First", "Last");
    s2 = studentConstruct(654321, "Jane", "Doe");

    addGrade(s1, 56.762);
    addGrade(s1, 77);
    addGrade(s2, 100);

    students->head = s1;
    s1->next = s2;
    students->count = 2;

    writeAllStudentsToCSV(fptr, students);

    fclose(fptr);

    FILE * fptr2 = fopen("expected/testWriteStudentData.csv", "r");

    if(fptr2 == NULL){
        printf("Error opening file.\n");
        return;
    }

    char c = fgetc(fptr2);

    while(c != EOF){
        printf("%c",c);
        c = fgetc(fptr2);
    }

    studentListDestruct(s1, students);

    fclose(fptr2);
    
}

//Test 2: calculating GPA
void testCalculateGPA(){
    FILE * fptr = fopen("expected/testStudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    StudentList * students = studentListConstruct();

    Student * s1;
    Student * s2;
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);

    students->head = s1;
    s1->next = s2;
    s2->next = s3;
    students->count = 3;

    printf("%.2f\n", s1->gpa);
    printf("%.2f\n", s2->gpa);
    printf("%.2f\n", s3->gpa);

    studentListDestruct(s1, students);

    fclose(fptr);
}

//Test 3: sorting by name
void testSortByName(){
    FILE * fptr = fopen("expected/testStudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    StudentList * students = studentListConstruct();

    Student * s1;
    Student * s2;
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);

    students->head = s1;
    s1->next = s2;
    s2->next = s3;
    students->count = 3;

    StudentList * sortedByName = sortByName(students);

    Student * sptr = sortedByName->head;

    while(sptr != NULL){
        printf("%s\n", sptr->name);
        sptr = sptr->next;
    }

    studentListDestruct(s1, students);

    fclose(fptr);
}

//Test 4: sorting by id
void testSortByID(){
    FILE * fptr = fopen("expected/testStudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    StudentList * students = studentListConstruct();

    Student * s1;
    Student * s2;
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);

    students->head = s1;
    s1->next = s2;
    s2->next = s3;
    students->count = 3;

    StudentList * sortedByID = sortByID(students);

    Student * sptr = sortedByID->head;

    while(sptr != NULL){
        printf("%d\n", sptr->ID);
        sptr = sptr->next;
    }

    studentListDestruct(s1, students);

    fclose(fptr);
}

//Test 5: sorting by GPA
void testSortByGPA(){
    FILE * fptr = fopen("expected/testStudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    StudentList * students = studentListConstruct();

    Student * s1;
    Student * s2;
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);

    students->head = s1;
    s1->next = s2;
    s2->next = s3;
    students->count = 3;

    StudentList * sortedByGPA = sortByGPA(students);

    Student * sptr = sortedByGPA->head;

    while(sptr != NULL){
        printf("%.2f\n", sptr->gpa);
        sptr = sptr->next;
    }

    studentListDestruct(s1, students);

    fclose(fptr);
}