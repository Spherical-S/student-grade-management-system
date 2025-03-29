#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student{
    int ID;
    char * name;
    double * grades;
	int numGrades;
	double gpa; //0 if not calculated
    struct Student * next;
} Student;

typedef struct{
    Student * head;
    int count;
}StudentList;

char * joinStrings(const char * s1, const char * s2);
Student * studentConstruct(int ID, const char * first, const char * last);
void studentDestruct(Student *s);
void displayStudent(Student * s);
void printGrades(Student * s);
void printBarChart(Student * s);
int addGrade(Student * s, double grade);
double calculateGPA(Student * s);
Student * deepCopyStudent(Student * s);
StudentList * sortByGPA(StudentList * students);
StudentList * sortByName(StudentList * students);
StudentList * sortByID(StudentList * students);

StudentList * studentListConstruct();
void studentListDestruct(Student * ptr, StudentList * sList);

StudentList * merge_sort(StudentList * students, int sortType);
#endif
