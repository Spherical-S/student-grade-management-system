#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int addStudentToCSV(FILE * file, Student *s, int lastStudent) {

	char first[50];
	char last[50];

	//Split the name into first and last name
	char *token = strtok(s->name, " ");
    if (token != NULL) {
        strcpy(first, token);

        token = strtok(NULL, " ");
        if (token != NULL) {
            strcpy(last, token);
        }
    }

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

	return 0;
	
}	

int writeAllStudentsToCSV(FILE * file, Student * * students, int count){

	int lastStudent = 0;

	for(int i = 0; i<count; i++){

		if(i == count-1){
			lastStudent = 1;
		}

		if(addStudentToCSV(file, students[i], lastStudent) == 1){
			fclose(file);
			return 1;
		}
	}

	fclose(file);
	return 0;

}


Student * createStudentFromCSVLine(FILE * file) {

	char first[50];
	char last[50];
	int ID;

	fscanf(file, "%d,%100[^,],%100[^,],", &ID, first, last);

	Student * s = studentConstruct(ID, first, last);

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

Student * * readAllStudentsFromCSV(int * count) {

    FILE * fptr = fopen("StudentData.csv", "r");

    if (fptr == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    Student * * students = malloc(0);
    *count = 0;

    while (!feof(fptr)) {

        Student * newStudent = createStudentFromCSVLine(fptr);

        students = realloc(students, (*count + 1) * sizeof(Student *));
        students[*count] = newStudent;
        *count = *count + 1;

    }

    fclose(fptr);
    return students;
}