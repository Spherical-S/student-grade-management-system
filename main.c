#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "myheader.h"

int main(int argc, char * * argv){

    FILE * fptr = fopen("StudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return EXIT_FAILURE;
    }

    Student * * students = malloc(3 * sizeof(Student *));

    Student * s1;
    Student * s2;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);

    displayStudent(s2);
    printGrades(s2);

    Student * s3 = studentConstruct(3764532, "Kamren", "Gregory");
    addGrade(s3, 65.4);
    addGrade(s3, 70.2);
    displayStudent(s3);
    printGrades(s3);
    
    calculateGPA(s1);
    calculateGPA(s2);
    calculateGPA(s3);

    students[0] = s1;
    students[1] = s2;
    students[2] = s3;

    writeAllStudentsToCSV(students, 3);

}