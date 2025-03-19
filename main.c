#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "myheader.h"

int main(int argc, char * * argv){

    if (argc != 0){

        int testNum = strtol(argv[1]);

        switch(testNum){
            case 0:
                testReadCSV();
                break;
            case 1:
                testWriteCSV();
                break;
            case 2:
                testCalculateGPA();
                break;
            case 3:
                testSortByName();
                break;
            case 4:
                testSortByID();
                break;
            case 5:
                testSortByGPA();
                break;
            default:
                printf("Invalid test number\n");
        }

    }

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