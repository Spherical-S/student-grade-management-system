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
    Student * s3;

    s1 = createStudentFromCSVLine(fptr);
    s2 = createStudentFromCSVLine(fptr);
    s3 = createStudentFromCSVLine(fptr);
    
    calculateGPA(s1);
    calculateGPA(s2);
    calculateGPA(s3);

    students[0] = s1;
    students[1] = s2;
    students[2] = s3;

    Student * * sortedByGPA = sortByGPA(students, 3);
    Student * * sortedByID = sortByID(students, 3);
    Student * * sortedByName = sortByName(students, 3);

    for(int i = 0; i<3; i++){
        printf("%f ", sortedByGPA[i]->gpa);
    }

    printf("\n");

    for(int i = 0; i<3; i++){
        printf("%d ", sortedByID[i]->ID);
    }

    printf("\n");

    for(int i = 0; i<3; i++){
        printf("%s ", sortedByName[i]->name);
    }

    printf("\n");

    printBarChart(s1);

    writeAllStudentsToCSV(students, 3);

}