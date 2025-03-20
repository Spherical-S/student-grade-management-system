#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "myheader.h"

int main(int argc, char * * argv){

    if (argc > 1){ //If there is a command line argument, it is for running unit tests

        long int testNum;
        char * endptr;

        testNum = strtol(argv[1], &endptr, 10);

        if(*endptr != '\0'){
            testNum = -1;
        }

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

        return EXIT_SUCCESS;

    }

    FILE * fptr = fopen("StudentData.csv", "r");

    if(fptr == NULL){
        printf("Error opening file.\n");
        return EXIT_FAILURE;
    }

    int choice;
    Student * * sortedStudents = NULL;
    
    while (1) {
        printf("How do you want to sort the students?\n");
        printf("1. By GPA\n");
        printf("2. By ID\n");
        printf("3. By Name\n");
        printf("Enter your choice (1, 2, or 3): ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    switch (choice) {
        case 1:
            sortedStudents = sortByGPA(students, 3);
            printf("Students sorted by GPA:\n");
            break;
        case 2:
            sortedStudents = sortByID(students, 3);
            printf("Students sorted by ID:\n");
            break;
        case 3:
            sortedStudents = sortByName(students, 3);
            printf("Students sorted by Name:\n");
            break;
    }

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

    FILE * fptr2 = fopen("StudentData.csv", "w");

    if(fptr2 == NULL){
        printf("Error opening file.\n");
        return EXIT_FAILURE;
    }

    writeAllStudentsToCSV(fptr2, students, 3);

    fclose(fptr);
    fclose(fptr2);

}
