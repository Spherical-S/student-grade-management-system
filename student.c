#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

//Helper method to combine first and last name into one variable
char * joinStrings(const char * s1, const char * s2){
	char * result = malloc((strlen(s1) + strlen(s2) + 2) * sizeof(char));
	if(result == NULL){
		printf("Error allocating memory!");
		return NULL;
	}
	strcpy(result, s1);
	strcat(result, " ");
	strcat(result, s2);
	return result;
}

Student * studentConstruct(int ID, const char * first, const char * last){
	Student * s = malloc(sizeof(Student));
	s->ID = ID;
	s->name = joinStrings(first, last);
	s->gpa = 0;
	s->numGrades = 0;
	s->grades = malloc(0);
	return s;
}


void studentDestruct(Student *s){
	free(s->name);
	free(s->grades);
	free(s);
}


void displayStudent(Student * s){
	printf("------- Student Information -------\n");
	printf("ID: %d\nName: %s\nGPA: %.2f\n", s->ID, s->name, s->gpa);
	printf("-----------------------------------\n");
}

void printGrades(Student * s){
	for (int i = 0; i<s->numGrades; i++){
		printf("%.2f ", s->grades[i]);
	}
	printf("\n");
}


int addGrade(Student * s, double grade){
	
	if(s->numGrades == 0){
		s->grades = malloc(0);
	}
	
	s->grades = realloc(s->grades, (s->numGrades + 1) * sizeof(double));
	if (s->grades == NULL) {
		printf("Error: memory allocation failed\n");
		return 1;
	}
	s->grades[s->numGrades] = grade;
	s->numGrades++;
	
	return 0;

}