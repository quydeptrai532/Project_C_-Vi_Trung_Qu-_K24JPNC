#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

void displayMainMenu();
void displayAdminMenu();
void displayTeacherMenu();
void displayStudentMenu();
void loadDataFromFile();
void saveDataToFile();
void addStudent();
void deleteStudent();
void editStudent();
void displayAllStudents();
void searchStudentByName();
void sortStudentByName();
void removeSpaces(char *name);
void addTeacher();
void deleteTeacher();
void displayAllTeachers();
void generateTeacherID(char *id);
void saveTeacherDataToFile();
void loadTeacherDataFromFile();
void sortTeacherByName();
void editTeacher();

#endif

