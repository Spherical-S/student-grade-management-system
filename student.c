#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

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