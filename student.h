#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    int ID;
    char * name;
    double * grades;
	int numGrades;
	double gpa; //0 if not calculated
} Student;

void displayStudent(Student * s);
int addGrade(Student * s, double grade);

#endif
