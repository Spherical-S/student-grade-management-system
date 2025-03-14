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

double calculateGPA(Student * s){

	double totalGradePoints = 0;

	for (int i = 0; i<s->numGrades; i++){

		if(s->grades[i] >= 90){
			totalGradePoints += 4.3; //A+
		}else if(s->grades[i] >= 85){
			totalGradePoints += 4.0; //A
		}else if(s->grades[i] >= 80){
			totalGradePoints += 3.7; //A-
		}else if(s->grades[i] >= 77){
			totalGradePoints += 3.3; //B+
		}else if(s->grades[i] >= 73){
			totalGradePoints += 3.0; //B
		}else if(s->grades[i] >= 70){
			totalGradePoints += 2.7; //B-
		}else if(s->grades[i] >= 65){
			totalGradePoints += 2.3; //C+
		}else if(s->grades[i] >= 60){
			totalGradePoints += 2.0; //C
		}else if(s->grades[i] >= 50){
			totalGradePoints += 1.0; //D
		}else{
			totalGradePoints += 0.0; //F
		}

	}

	s->gpa = totalGradePoints/s->numGrades;

	return s->gpa;

}