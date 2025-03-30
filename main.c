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
    
    //menu option 
    StudentList * students = readAllStudentsFromCSV();

    if (students == NULL) {
        printf("Error allocating memory!\n");
        return EXIT_FAILURE;
    }
    
    int choiceMain;
    int exitSelected = 0;
    Student * sptr;
    while (exitSelected == 0) {
        printf("Welcome to the Student Grade Management System\n\n");
        printf("Click 1 to add a new student.\n");
        printf("Click 2 to view all student details.\n");
        printf("Click 3 to search for a specific student.\n");
        printf("Click 4 to sort the current list of students\n");
        printf("Click 5 to Exit.\n");
        printf("Enter your choice (1, 2, 3, 4 or 5): ");
        scanf("%d", &choiceMain);

        switch (choiceMain) {
            case 1: //Add a new student
                int ID;
                char first[50] = "";
                char last[50] = "";
                printf("Enter the student's ID: ");
                scanf("%d", &ID);
                printf("Enter the student's first name: ");
                scanf("%s", first);
                printf("Enter the student's last name: ");
                scanf("%s", last);

                Student * addNewStudent = studentConstruct(ID, first, last);

                if(addNewStudent == NULL){
                    exitSelected = 1;
                    break;
                }

                int numGrades;
                printf("How many grades does the student have? ");
                scanf("%d", &numGrades);

                double grade;

                for (int i = 0; i < numGrades; i++) {
                    printf("Enter grade %d: ", i + 1);
                    scanf("%lf", &grade);
                    if(addGrade(addNewStudent, grade) == 1){
                        exitSelected = 1;
                        break;
                    }
                }

                if(exitSelected == 1){
                    break;
                }

                addNewStudent->next = students->head;
                students->head = addNewStudent;
                students->count += 1;

                FILE * fptr = fopen("StudentData.csv", "w");

                if(fptr == NULL){
                    printf("Error opening file.\n");
                    exitSelected = 1;
                    break;
                }

                writeAllStudentsToCSV(fptr, students);
                
                printf("Student added successfully!\n");
                break;

            case 2: //display all students

                printf("\nAll Students' Details:\n");

                sptr = students->head;
                while(sptr != NULL){
                    displayStudent(sptr);
                    sptr = sptr->next;
                }

                break;
            
            case 3: //search for a specific student

                int searchChoice;
                printf("Search by:\n");
                printf("1. ID\n");
                printf("2. Name\n");
                printf("Enter your choice (1 or 2): ");
                scanf("%d", &searchChoice);

                int found = 0;
                sptr = students->head;
            
                switch (searchChoice) {
                    case 1: // Search by ID
                        int searchStudentID;
                        printf("Enter the student's ID: ");
                        scanf("%d", &searchStudentID);
            
                        while (sptr != NULL) {
                            if (sptr->ID == searchStudentID) {
                                displayStudent(sptr);
                                printf("\nGrade Bar Chart:\n");
                                printBarChart(sptr);
                                found = 1;
                                break;
                            }
                            sptr = sptr->next;
                        }
            
                        if (found == 0) {
                            printf("Student not found.\n");
                        }
                        break;

                    case 2: // Search by name
                        char searchFirst[50] = "";
                        char searchLast[50] = "";
                        printf("Enter the student's first name: ");
                        scanf("%s", searchFirst);
                        printf("Enter the student's last name: ");
                        scanf("%s", searchLast);

                        char * searchFullName = joinStrings(searchFirst, searchLast);
            
                        while (sptr != NULL) {
                            if (strcmp(sptr->name, searchFullName) == 0) {
                                displayStudent(sptr);
                                printf("\nGrade Bar Chart:\n");
                                printBarChart(sptr);
                                found = 1;
                                break;
                            }
                            sptr = sptr->next;
                        }
            
                        if (found == 0) {
                            printf("Student not found.\n");
                        }

                        free(searchFullName);

                        break;
            
                    default:
                        printf("Invalid choice!\n");
                }
                break;
            case 4: //sort students
                int choice;
                StudentList * sortedStudents;
                
                printf("How do you want to sort the students?\n");
                printf("1. By GPA\n");
                printf("2. By ID\n");
                printf("3. By Name\n");
                printf("Enter your choice (1, 2, or 3): ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        sortedStudents = sortByGPA(students);
                        printf("Students sorted by GPA:\n");
                        break;
                    case 2:
                        sortedStudents = sortByID(students);
                        printf("Students sorted by ID:\n");
                        break;
                    case 3:
                        sortedStudents = sortByName(students);
                        printf("Students sorted by Name:\n");
                        break;
                    default:
                        printf("Invalid choice.\n");
                }

                sptr = sortedStudents->head;
                while(sptr != NULL){
                    displayStudent(sptr);
                    sptr = sptr->next;
                }

                studentListDestruct(sortedStudents->head, sortedStudents);

                break;
            
            case 5: //exit program

                printf("Exiting the program.\n");
                exitSelected = 1;
                break;

            default:
                printf("Invalid selection, try again.\n");
        }

    }

    studentListDestruct(students->head, students);

}
