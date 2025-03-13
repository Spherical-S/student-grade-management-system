#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

struct student {
	long ID;
	char name[30];
	float grades[10];
	float gpa;
}

int csvFileWrite(Student *s) {
    FILE *file = fopen("StudentData.csv", "w");
    if (file == NULL) {
        printf("Error: could not create file\n");
        return 1;
    }

    fprintf(file, "ID,Name,Grades,GPA\n");
    fprintf(file, "%ld,%s,", s->ID, s->name);
	    for (int i = 0; i < 10; i++) {
		fprintf(file, "%.2f,", s->grades[i]);
	    }
	    fprintf(file, "%.2f\n", s->gpa);

	    fclose(file);
	    return 0;
	}	


int csvFileRead(Student *s) {
	FILE *file = fopen("StudentData.csv", "r");
	if (file == NULL) {
		printf("Error: could not open file\n");
		return 1;
	}

	fscanf(file, "%ld,%29[^,],", &s->ID, s->name);
	for (int i = 0; i < 10; i++) {
		fscanf(file, "%f,", &s->grades[i]);
	}
	fscanf(file, "%f\n", &s->gpa);
	fclose(file);s
	return 0;
}
