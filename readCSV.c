#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int csvFileWrite(Student *s) {
	
    FILE *file = fopen("StudentData.csv", "w");
	
    if (file == NULL) {
        printf("Error: could not open file\n");
        return 1;
    }

    //FORMAT: ID,Name,GPA,Grade1,Grade2,...,GradeN
    fprintf(file, "%d,%s,", s->ID, s->name);
	
	fprintf(file, "%.2f,", s->gpa);
	
	for (int i = 0; i < s->numGrades; i++) {
		if(i == s->numGrades-1){ //ensure last grade doesnt print a comma at the end
			fprintf(file, "%.2f", s->grades[i]);
		}else{
			fprintf(file, "%.2f,", s->grades[i]);
		}
	}

	fclose(file);
	return 0;
}	


int csvFileRead(FILE * file, Student *s) {

	fscanf(file, "%d,%100[^,],%f,", &s->ID, s->name, &s->gpa);
	
	double grade;
	
	while(fscanf(file, "%f,", &grade) != -1){
		addGrade(s, grade);
	}
	//while loop only adds until the second last grade due to no comma after the last grade
	fscanf(file, "%f\n", &grade);
	addGrade(s, grade);
	
	fclose(file);
	return 0;
}
