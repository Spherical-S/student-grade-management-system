#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int appendStudentToCSV(Student *s) {
	
    FILE *file = fopen("StudentData.csv", "a");
	
    if (file == NULL) {
        printf("Error: could not open file\n");
        return 1;
    }

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
    fprintf(file, "%d,%s,%s", s->ID, first, last);
	
	fprintf(file, "%.2f,", s->gpa);
	
	for (int i = 0; i < s->numGrades; i++) {
		if(i == s->numGrades-1){ //ensure new line is created at the end
			fprintf(file, "%.2f\n", s->grades[i]);
		}else{
			fprintf(file, "%.2f,", s->grades[i]);
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

	char gradesString[1024];

	fgets(gradesString, 1024, file);

	double grade;

	char * token = strtok(gradesString, ",");
	while(token != NULL) {
        grade = strtod(token, NULL);
		addGrade(s, grade);
        token = strtok(NULL, ",");
    }
	
	return s;
}
