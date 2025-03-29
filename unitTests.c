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

    Student * * students = malloc(3 * sizeof(Student *));

    Student * s1;
    Student * s2;
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);

    students[0] = s1;
    students[1] = s2;
    students[2] = s3;

    for(int i = 0; i<3; i++){
        printf("%d %s\n", students[i]->ID, students[i]->name);
    }

    studentDestruct(s1);
    studentDestruct(s2);
    studentDestruct(s3);
    free(students);

    fclose(fptr);
}

//Test 1: writing CSV
void testWriteCSV(){

    FILE * fptr = fopen("expected/testWriteStudentData.csv", "w");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    Student * * students = malloc(2 * sizeof(Student *));

    Student * s1;
    Student * s2;

    s1 = studentConstruct(123456, "First", "Last");
    s2 = studentConstruct(654321, "Jane", "Doe");
    addGrade(s1, 56.762);
    addGrade(s1, 77);
    addGrade(s2, 100);

    students[0] = s1;
    students[1] = s2;

    writeAllStudentsToCSV(fptr, students, 2);

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

    studentDestruct(s1);
    studentDestruct(s2);
    free(students);

    fclose(fptr2);
    
}

//Test 2: calculating GPA
void testCalculateGPA(){
    FILE * fptr = fopen("expected/testStudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    Student * * students = malloc(3 * sizeof(Student *));

    Student * s1;
    Student * s2;
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);

    students[0] = s1;
    students[1] = s2;
    students[2] = s3;

    for(int i = 0; i<3; i++){
        printf("%.2f\n", students[i]->gpa);
    }

    studentDestruct(s1);
    studentDestruct(s2);
    studentDestruct(s3);
    free(students);

    fclose(fptr);
}

//Test 3: sorting by name
void testSortByName(){
    FILE * fptr = fopen("expected/testStudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    Student * * students = malloc(3 * sizeof(Student *));

    Student * s1;
    Student * s2;
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);

    students[0] = s1;
    students[1] = s2;
    students[2] = s3;

    Student * * sortedByName = sortByName(students, 3);

    for(int i = 0; i<3; i++){
        printf("%s\n", sortedByName[i]->name);
    }

    studentDestruct(s1);
    studentDestruct(s2);
    studentDestruct(s3);
    free(students);

    fclose(fptr);
}

//Test 4: sorting by id
void testSortByID(){
    FILE * fptr = fopen("expected/testStudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    Student * * students = malloc(3 * sizeof(Student *));

    Student * s1;
    Student * s2;
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);

    students[0] = s1;
    students[1] = s2;
    students[2] = s3;

    Student * * sortedByID = sortByID(students, 3);

    for(int i = 0; i<3; i++){
        printf("%d\n", sortedByID[i]->ID);
    }

    studentDestruct(s1);
    studentDestruct(s2);
    studentDestruct(s3);
    free(students);

    fclose(fptr);
}

//Test 5: sorting by GPA
void testSortByGPA(){
    FILE * fptr = fopen("expected/testStudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    Student * * students = malloc(3 * sizeof(Student *));

    Student * s1;
    Student * s2;
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);

    students[0] = s1;
    students[1] = s2;
    students[2] = s3;

    Student * * sortedByGPA = sortByGPA(students, 3);

    for(int i = 0; i<3; i++){
        printf("%.2f\n", sortedByGPA[i]->gpa);
    }

    studentDestruct(s1);
    studentDestruct(s2);
    studentDestruct(s3);
    free(students);

    fclose(fptr);
}