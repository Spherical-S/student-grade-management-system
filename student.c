#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student * studentConstruct(int ID, const char * name){
	Student * s = malloc(sizeof(Student));
	s->ID = ID;
	s->name = name;
	return s;
}


void studentDestruct(Student *s){
	free(s->name);
	free(s->grades);
	free(s);
}


void displayStudent(Student * s){
	printf("------- Student Information -------\n");
	printf("ID: %d\nName: %s\nGPA: %f\n", s->ID, s->name, s->gpa);
	printf("-----------------------------------\n");
}


int addGrade(Student * s, double grade){
	
	if(s->gradeCount == 0){
		s->grades = malloc(0);
	}
	
	s->grades = realloc(s->grades, (s->gradeCount + 1) * sizeof(double));
	if (s->grades == NULL) {
		printf("Error: memory allocation failed\n");
		fclose(file);
		return 1;
	}
	s->grades[s->gradeCount] = grade;
	s->gradeCount++;
	
}