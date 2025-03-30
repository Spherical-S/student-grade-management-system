#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

//Helper method to combine first and last name into one variable
char * joinStrings(const char * s1, const char * s2){

	if (s1 == NULL || s2 == NULL){
        return NULL;
    }

	char * result = malloc((strlen(s1) + strlen(s2) + 2) * sizeof(char));
	if(result == NULL){
		printf("Error allocating memory!");
		return NULL;
	}
	result[0] = '\0';
	strcpy(result, s1);
	strcat(result, " ");
	strcat(result, s2);
	return result;
}

Student * studentConstruct(int ID, const char * first, const char * last){
	Student * s = malloc(sizeof(Student));

	if(s == NULL){
		return NULL;
	}

	s->ID = ID;
	s->name = joinStrings(first, last);

	if(s->name == NULL){
		return NULL;
	}

	s->gpa = 0;
	s->numGrades = 0;
	s->next = NULL;
	return s;
}


void studentDestruct(Student *s){
	free(s->name);
	free(s->grades);
	free(s);
}

StudentList * studentListConstruct(){

	StudentList * sList = malloc(sizeof(StudentList));

	if(sList == NULL){
		return NULL;
	}

	sList->head = NULL;
	sList->count = 0;
	return sList;

}



void studentListDestruct(Student *ptr, StudentList *sList){

    if (ptr == NULL){
        return;
    }

    studentListDestruct(ptr->next, sList);

    studentDestruct(ptr);

    if (ptr == sList->head){
        free(sList);
    }

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

	if(s->numGrades == 0){
		return 0;
	}

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

Student * deepCopyStudent(Student * s){
	Student * newStudent = malloc(sizeof(Student));
	if(newStudent == NULL){
		return NULL;
	}

	newStudent->ID = s->ID;
	newStudent->name = strdup(s->name);
	newStudent->gpa = s->gpa;
	newStudent->grades = malloc(s->numGrades * sizeof(double));
	newStudent->numGrades = s->numGrades;
	newStudent->next = s->next;
	
	for(int i = 0; i<s->numGrades; i++){
		newStudent->grades[i] = s->grades[i];
	}

	return newStudent;

}

StudentList * merge(StudentList * left, StudentList * right, int sortType){

	StudentList * result = studentListConstruct();

	Student * lptr = left->head;
	Student * rptr = right->head;
	Student * resultTail;

	while(lptr != NULL && rptr != NULL){

		//if left if the one to add
		if ((sortType == 0 && lptr->gpa >= rptr->gpa) || (sortType == 1 && lptr->ID <= rptr->ID) || (sortType == 2 && strcmp(lptr->name, rptr->name) <= 0)){

			if(result->head == NULL){
				result->head = lptr;
				resultTail = lptr;
			}else{
				resultTail->next = lptr;
				resultTail = lptr;
			}
			lptr = lptr->next;
			result->count += 1;

		}else{ //right is the one to add
				
			if(result->head == NULL){
				result->head = rptr;
				resultTail = rptr;
			}else{
				resultTail->next = rptr;
				resultTail = rptr;
			}
			rptr = rptr->next;
			result->count += 1;

		}

	}

	while(lptr != NULL){

		if(result->head == NULL){
			result->head = lptr;
			resultTail = lptr;
		}else{
			resultTail->next = lptr;
			resultTail = lptr;
		}
		lptr = lptr->next;
		result->count += 1;

	}

	while(rptr != NULL){

		if(result->head == NULL){
			result->head = rptr;
			resultTail = rptr;
		}else{
			resultTail->next = rptr;
			resultTail = rptr;
		}
		rptr = rptr->next;
		result->count += 1;

	}

	resultTail->next = NULL;

	return result;

}

StudentList * merge_sort(StudentList * students, int sortType){ //sortType 0 = sort by GPA, 1 = sort by ID, 2 = sort by name

	if (students->count <= 1){
		return students;
	}

	int middle = students->count/2;

	StudentList * left = studentListConstruct();
	StudentList * right = studentListConstruct();

	Student * leftTail;
	Student * rightTail;

	Student * sptr = students->head;
	int count = 0;

	while(count < middle){
		if(left->head == NULL){
			left->head = deepCopyStudent(sptr);
			leftTail = left->head;
		}else{
			leftTail->next = deepCopyStudent(sptr);
			leftTail = leftTail->next;
		}
		left->count += 1;
		sptr = sptr->next;
		count++;
	}

	while(sptr != NULL){
		if(right->head == NULL){
			right->head = deepCopyStudent(sptr);
			rightTail = right->head;
		}else{
			rightTail->next = deepCopyStudent(sptr);
			rightTail = rightTail->next;
		}
		right->count += 1;
		sptr = sptr->next;
		count++;
	}

	leftTail->next = NULL;
	rightTail->next = NULL;

	left = merge_sort(left, sortType);
	right = merge_sort(right, sortType);

	StudentList * merged = merge(left, right, sortType);
	
	studentListDestruct(students->head, students);
	//free(left);
	//free(right);
	
	return merged;

}

StudentList * sortByGPA(StudentList * students){

	StudentList * sList = studentListConstruct();
	Student * sptr = students->head;
	Student * tail = NULL;

	while(sptr != NULL){
		if(sList->head == NULL){
			sList->head = deepCopyStudent(sptr);
			tail = sList->head;
			tail->next = NULL;
		}else{
			tail->next = deepCopyStudent(sptr);
			tail = tail->next;
			tail->next = NULL;
		}
		sptr = sptr->next;
		sList->count += 1;
	}
	
	return merge_sort(sList, 0);

}

StudentList * sortByID(StudentList * students){

	StudentList * sList = studentListConstruct();
	Student * sptr = students->head;
	Student * tail = NULL;

	while(sptr != NULL){
		if(sList->head == NULL){
			sList->head = deepCopyStudent(sptr);
			tail = sList->head;
			tail->next = NULL;
		}else{
			tail->next = deepCopyStudent(sptr);
			tail = tail->next;
			tail->next = NULL;
		}
		sptr = sptr->next;
		sList->count += 1;
	}
	
	return merge_sort(sList, 1);

}

StudentList * sortByName(StudentList * students){

	StudentList * sList = studentListConstruct();
	Student * sptr = students->head;
	Student * tail = NULL;

	while(sptr != NULL){
		if(sList->head == NULL){
			sList->head = deepCopyStudent(sptr);
			tail = sList->head;
			tail->next = NULL;
		}else{
			tail->next = deepCopyStudent(sptr);
			tail = tail->next;
			tail->next = NULL;
		}
		sptr = sptr->next;
		sList->count += 1;
	}
	
	return merge_sort(sList, 2);

}
