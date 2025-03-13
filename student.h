#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    int ID;
    char * name;
    double * grades;
	int numGrades;
	double gpa; //0 if not calculated
} Student;

Student * studentConstruct(int ID, const char * name);
void studentDestruct(Student *s);
void displayStudent(Student * s);
int addGrade(Student * s, double grade);

#endif
