#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main() {
    int mainChoice, adminChoice, teacherChoice, studentChoice,classchoice;

    loadDataFromFile();
    loadTeacherDataFromFile();

    while (1) { 
        displayMainMenu();
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1: { // Admin Menu
                int adminExit = 0; 
                while (!adminExit) {
                    displayAdminMenu();
                    scanf("%d", &adminChoice);
                    switch (adminChoice) {
                        case 1:
                            addStudent();
                            saveDataToFile();
                            break;
                        case 2:
                            displayAllStudents();
                            break;
                        case 3:
                        	displayAllStudents();
                            editStudent();
                            saveDataToFile();
                            break;
                        case 4:
                        	displayAllStudents();
                            deleteStudent();
                            saveDataToFile();
                            break;
                        case 5:
                            searchStudentByName();
                            break;
                        case 6:
                            sortStudentByName();
                            break;
                        case 7:
                            addTeacher();
                            saveTeacherDataToFile();
                            break;
                        case 8:
                        	displayAllTeachers();
                            deleteTeacher();
                            saveTeacherDataToFile();
                            break;
                        case 9:
                            displayAllTeachers();
                            break;
                        case 10:
                            sortTeacherByName();
                            displayAllTeachers();
                            break;
                        case 11:
                        	displayAllTeachers();
                            editTeacher();
                            saveTeacherDataToFile();
                            break;
                        case 12: 
                            adminExit = 1;
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                }
                break;
            }
            case 2: { // Teacher Menu
                int teacherExit = 0; 
                while (!teacherExit) {
                    displayTeacherMenu();
                    scanf("%d", &teacherChoice);
                    switch (teacherChoice) {
                        case 1:
                            displayAllStudents();
                            break;
                        case 2:
                            searchStudentByName();
                            break;
                        case 3:
                            sortStudentByName();
                            displayAllStudents();
                            break;
                        case 4:
                        	displayAllStudents();
                            editStudent();
                            saveDataToFile();
                            break;
                        case 5:
                        	displayAllStudents();
                            deleteStudent();
                            saveDataToFile();
                            break;
                        case 6: 
                            teacherExit = 1;
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                }
                break;
            }
            case 3: { // Student Menu
                int studentExit = 0; 
                while (!studentExit) {
                    displayStudentMenu();
                    scanf("%d", &studentChoice);
                    switch (studentChoice) {
                        case 1:
                            displayAllStudents();
                            break;
                        case 2:
                            searchStudentByName();
                            break;
                        case 3: 
                            studentExit = 1;
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                }
                break;
            }
            case 4: {
			
			
                    int classExit=0;
			        while(!classExit){
			        	displayClassMenu();
			        	scanf("%d",&classchoice);
			        	switch(classchoice){
					
			        	case 1: printf("None\n");
			        	        break;
			            case 2: printf("None\n");
			                    break;
			            case 3: printf("None\n");
			                    break;
			            case 4: printf("None\n");
			                    break;
			            case 5: printf("None\n");
			                    break;
			        	case 6:
			        		classExit=1;
			        	default: printf("None\n");
					
					} }
                    break; 
                }
            case 0: 
                saveDataToFile();
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

