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

    int choiceMain;
    
    while (1) {
        printf("Welcome to the Student  Grade Management System\n\n");
        printf("Click 1 to add a new student.\n");
        printf("Click 2 to view all student details.\n");
        printf("Click 3 to search for a specific student.\n");
        printf("Click 4 to Exit.);
        printf("Enter your choice (1, 2, 3 or 4): ");
        scanf("%d", &choiceMain);

        if (choiceMain >= 1 && choiceMain <= 4) {
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    switch (choiceMain) {
        case 1:
            int ID;
                char first[50]
                char last[50];
                printf("Enter the student's ID: ");
                scanf("%d", &ID);
                printf("Enter the student's first name: ");
                scanf("%s", first);
                printf("Enter the student's last name: ");
                scanf("%s", last);

                Student * addNewStudent = studentConstruct(ID, first, last);

                int numGrades;
                printf("How many grades does the student have? ");
                scanf("%d", &numGrades);
                for (int i = 0; i < numGrades; i++) {
                    double grade;
                    printf("Enter grade %d: ", i + 1);
                    scanf("%lf", &grade);
                    addGrade(addNewStudent, grade);
                }

            //in progress
                FILE * fptr2 = fopen("StudentData.csv", "w");
                if (fptr2 == NULL) {
                    printf("Error opening file.\n");
                    return EXIT_FAILURE;
                }
                
                addStudentToCSV(fptr2, addNewStudent, 1);

                fclose(fptr2);
                printf("Student added successfully!\n");
                break;
            
        case 2:
            printf("\nAll Students' Details:\n");
            //in progress
                    displayStudent();
                break;
        case 3:
            printf("Student detail: ");
            break;
        
        case 4:
            printf("Exiting the program.");
            break;
    }


    int numStudents = 0;
    Student * * students = readAllStudentsFromCSV(&numStudents);

    int choice;
    Student * * sortedStudents;
    
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
            sortedStudents = sortByGPA(students, numStudents);
            printf("Students sorted by GPA:\n");
            break;
        case 2:
            sortedStudents = sortByID(students, numStudents);
            printf("Students sorted by ID:\n");
            break;
        case 3:
            sortedStudents = sortByName(students, numStudents);
            printf("Students sorted by Name:\n");
            break;
    }
}
