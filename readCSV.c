#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void addStudentToCSV(FILE * file, Student *s, int lastStudent) {

	char first[50] = "";
	char last[50] "";
	char * dupeName = strdup(s->name);

	//Split the name into first and last name
	char * token = strtok(dupeName, " ");
    if (token != NULL) {
        strcpy(first, token);

        token = strtok(NULL, " ");
        if (token != NULL) {
            strcpy(last, token);
        }
    }

	free(dupeName);

    //FORMAT: ID,FirstName,LastName,GPA,Grade1,Grade2,...,GradeN
    fprintf(file, "%d,%s,%s,", s->ID, first, last);

	if(s->numGrades == 0){ //ensure no comma is printed after gpa if the student has no grades
		if(lastStudent == 0){
			fprintf(file, "%.2f\n", s->gpa);
		}else{
			fprintf(file, "%.2f", s->gpa);
		}
	}else{
		fprintf(file, "%.2f,", s->gpa);
	}
	
	for (int i = 0; i < s->numGrades; i++) {

		if(i == s->numGrades-1){
			if(lastStudent == 1){
				fprintf(file, "%.2f", s->grades[i]);
			}else{
				fprintf(file, "%.2f\n", s->grades[i]);
			}
		}else{
			fprintf(file, "%.2f,", s->grades[i]);
		}

	}
	
}	

void writeAllStudentsToCSV(FILE * file, StudentList * sList){

	int lastStudent = 0;

	Student * sptr = sList->head;

	while(sptr != NULL){

		if(sptr->next == NULL){
			lastStudent = 1;
		}

		addStudentToCSV(file, sptr, lastStudent);
		
		sptr = sptr->next;
	}

	fclose(file);
}


Student * createStudentFromCSVLine(FILE * file) {

	char first[50];
	char last[50];
	int ID;

	fscanf(file, "%d,%100[^,],%100[^,],", &ID, first, last);

	Student * s = studentConstruct(ID, first, last);

	if(s == NULL){
		return NULL;
	}

	fscanf(file, "%lf,", &s->gpa);

	if(feof(file)){
		calculateGPA(s);
		return s;
	}

	char gradesString[1024];

	fgets(gradesString, 1024, file);

	double grade;

	char * token = strtok(gradesString, ",");
	while(token != NULL) {
        grade = strtod(token, NULL);
		addGrade(s, grade);
        token = strtok(NULL, ",");
    }

	calculateGPA(s);
	
	return s;
}

StudentList * readAllStudentsFromCSV() {

    FILE * fptr = fopen("StudentData.csv", "r");

    if (fptr == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

	StudentList * sList = studentListConstruct();

	if(sList == NULL){
		return NULL;
	}

    while (!feof(fptr)) {

        Student * newStudent = createStudentFromCSVLine(fptr);

		if(newStudent == NULL){
			studentListDestruct(sList->head, sList);
			return NULL;
		}

		newStudent->next = sList->head;
		sList->head = newStudent;
		sList->count += 1;

    }

    fclose(fptr);
    return sList;
}