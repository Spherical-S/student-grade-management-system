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

void printBarChart(Student * s){
	printf("Grade visualization for %s, Student No. %d\n", s->name, s->ID);
 	for (int i = 0; i<s->numGrades; i++) {
 		printf("Course #%d | ", i);
 		
 		int numOfHash = s->grades[i] / 10;
 		for (int j = 0; j < numOfHash; j++) {
 			printf("#");
 		}
 		printf(" | (%.2f)\n", s->grades[i]);
 	}
	printf("Total GPA: %.2f\n", s->gpa);
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

	calculateGPA(s);
	
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

Student * * merge(Student * * left, int leftCount, Student * * right, int rightCount, int sortType){

	Student * * result = malloc((leftCount + rightCount) * sizeof(Student *));
	int i = 0;
	int j = 0;
	int k = 0;

	while(i < leftCount && j < rightCount){

		if (sortType == 0){ //gpa

			if (left[i]->gpa >= right[j]->gpa){
				result[k] = left[i];
				i++;
				k++;
			}else{
				result[k] = right[j];
				j++;
				k++;
			}

		}else if(sortType == 1){ //ID

			if (left[i]->ID <= right[j]->ID){
				result[k] = left[i];
				i++;
				k++;
			}else{
				result[k] = right[j];
				j++;
				k++;
			}

		}else{ //Name

			if (strcmp(left[i]->name, right[j]->name) <= 0){
				result[k] = left[i];
				i++;
				k++;
			}else{
				result[k] = right[j];
				j++;
				k++;
			}

		}

	}

	while(i < leftCount){

		result[k] = left[i];
		i++;
		k++;

	}

	while(j < rightCount){

		result[k] = right[j];
		j++;
		k++;

	}

	return result;

}

Student * * merge_sort(Student * * students, int count, int sortType){ //sortType 0 = sort by GPA, 1 = sort by ID, 2 = sort by name

	if (count <= 1){
		return students;
	}

	int middle = count/2;

	int leftCount = middle;
	Student * * left = malloc(leftCount * sizeof(Student *));
	
	int rightCount = count-middle;
	Student * * right = malloc(rightCount * sizeof(Student *));

	for (int i = 0; i<leftCount; i++){
		left[i] = students[i];
	}

	for (int i = leftCount; i<count; i++){
		right[i-leftCount] = students[i];
	}

	left = merge_sort(left, leftCount, sortType);
	right = merge_sort(right, rightCount, sortType);

	Student * * merged = merge(left, leftCount, right, rightCount, sortType);

	free(left);
	free(right);
	
	return merged;

}

Student * * sortByGPA(Student * * students, int count){
	
	return merge_sort(students, count, 0);

}

Student * * sortByID(Student * * students, int count){
	
	return merge_sort(students, count, 1);

}

Student * * sortByName(Student * * students, int count){
	
	return merge_sort(students, count, 2);

}
