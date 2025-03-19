#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    int ID;
    char * name;
    double * grades;
	int numGrades;
	double gpa; //0 if not calculated
} Student;

Student * studentConstruct(int ID, const char * first, const char * last);
void studentDestruct(Student *s);
void displayStudent(Student * s);
void printGrades(Student * s);
int addGrade(Student * s, double grade);
double calculateGPA(Student * s);
Student * * sortByGPA(Student * * students);

#endif
