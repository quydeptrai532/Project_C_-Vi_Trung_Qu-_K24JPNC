#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "datatype.h"
#include "function.h"

#define MAX_STUDENTS 100
#define MAX_TEACHERS 50

Student students[MAX_STUDENTS];
int studentCount = 0;
Teacher teachers[MAX_TEACHERS];
int teacherCount = 0;
int currentStudentID = 1;
int currentTeacherID =1;

// Ham id
 void generateTeacherID(char *id) {
    sprintf(id, "TID%04d", currentTeacherID);
    currentTeacherID++;
}

void generateStudentID(char *id) {
    sprintf(id, "ID%04d", currentStudentID);
    currentStudentID++;
}
// Ham kiem tra
int isValidEmail(const char *email) {
    int atPos = -1, dotPos = -1;
    int len = strlen(email);
    int i, atCount = 0, dotCount = 0;
    for (i = 0; i < len; i++) {
        if (email[i] == '@') {
            atPos = i;
            atCount++;
        }
        if (email[i] == '.') {
            dotPos = i;
            dotCount++;
        }
    }

    if (atCount != 1 || dotCount < 1) {
        return 0;
    }

    return (atPos != -1 && dotPos != -1 && dotPos > atPos + 1 && atPos > 0 && dotPos < len - 1);
}

int isValidPhoneNumber(const char *phoneNumber) {
    int len = strlen(phoneNumber);
    if (len < 10 || len > 11) return 0;
    if (phoneNumber[0] != '0') return 0;
    int i;
    for (i = 0; i < len; i++) {
        if (!isdigit(phoneNumber[i])) return 0;
    }
    return 1;
}
void removeSpaces(char *name) {
    char temp[100];
    int j = 0;
    int i;
    int leadingSpace = 1; 

    for (i = 0; name[i] != '\0'; i++) {
        if (name[i] != ' ' || (j > 0 && temp[j - 1] != ' ')) {
            temp[j++] = name[i];
            leadingSpace = 0; 
        } else if (!leadingSpace) {
            temp[j++] = name[i];
        }
    }
    temp[j] = '\0';
    strcpy(name, temp);
}
// Ham kiem tra cua giao vien
   void trimWhitespace(char *str) {
    int i = 0, j = 0;
    while (str[i] == ' ') {
        i++;
    }
    while (str[i] != '\0') {
        str[j++] = str[i++];
    }
    str[j] = '\0';
    j--;
    while (j >= 0 && str[j] == ' ') {
        str[j--] = '\0';
    }
}


int isValidTeacherData(Teacher *teacher) {
    trimWhitespace(teacher->name);
    if (!isValidPhoneNumber(teacher->phoneNumber)) {
        printf("Invalid phone number. It must be 10 or 11 digits.\n");
        return 0;
    }
    if (!isValidEmail(teacher->email)) {
        printf("Invalid email. It must be in the format 'example@gmail.com'.\n");
        return 0;
    }
    return 1;
}



// Ham File
void loadDataFromFile() {
    FILE *file = fopen("StudentData.bin", "rb");
    if (file == NULL) {
        printf("No data file found. Starting with an empty database.\n");
        return;
    }
    fread(&studentCount, sizeof(int), 1, file);
    fread(&currentStudentID, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);
    fclose(file);
    printf("Student data loaded successfully.\n");
}

void saveDataToFile() {
    FILE *file = fopen("StudentData.bin", "wb");
    if (file == NULL) {
        printf("Failed to save data to file.\n");
        return;
    }
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(&currentStudentID, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
    printf("Student data saved successfully.\n");
}
void saveTeacherDataToFile() {
    FILE *file = fopen("TeacherData.bin", "wb");
    if (file == NULL) {
        printf("Failed to save teacher data to file.\n");
        return;
    }
    fwrite(&teacherCount, sizeof(int), 1, file);
    fwrite(&currentTeacherID, sizeof(int), 1, file);
    fwrite(teachers, sizeof(Teacher), teacherCount, file);
    fclose(file);
    printf("Teacher data saved successfully.\n");
}
void loadTeacherDataFromFile() {
    FILE *file = fopen("TeacherData.bin", "rb");
    if (file == NULL) {
        printf("No teacher data file found. Starting with an empty teacher database.\n");
        return;
    }
    fread(&teacherCount, sizeof(int), 1, file);
    fread(&currentTeacherID, sizeof(int), 1, file);
    fread(teachers, sizeof(Teacher), teacherCount, file);
    fclose(file);
    printf("Teacher data loaded successfully.\n");
}



// Student Functions
void addStudent() {
    if (studentCount < MAX_STUDENTS) {
        generateStudentID(students[studentCount].id);
        printf("Enter student name: ");
        scanf(" %[^\n]", students[studentCount].name);
        removeSpaces(students[studentCount].name);

        printf("Enter student age: ");
        scanf("%d", &students[studentCount].age);

        while (1) {
            printf("Enter student email: ");
            scanf("%s", students[studentCount].email);
            if (isValidEmail(students[studentCount].email)) break;
            printf("Invalid email. Please try again. Email must be abc@xyz.com\n");
        }

        while (1) {
            printf("Enter student phone number: ");
            scanf("%s", students[studentCount].phoneNumber);
            if (isValidPhoneNumber(students[studentCount].phoneNumber)) break;
            printf("Invalid phone number. Please try again.Phone Number must be(10-11) Number\n");
        }

        studentCount++;
    } else {
        printf("Student list is full!\n");
    }
}

void editStudent() {
    char idToEdit[10];
    int i;
    printf("Enter the student ID to edit: ");
    scanf("%s", idToEdit);
    int found = -1;
    for (i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, idToEdit) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        printf("Editing student with ID %s:\n", students[found].id);
        printf("Enter new name: ");
        scanf(" %[^\n]", students[found].name);
        removeSpaces(students[found].name);

        printf("Enter new age: ");
        scanf("%d", &students[found].age);

        while (1) {
            printf("Enter new email: ");
            scanf("%s", students[found].email);
            if (isValidEmail(students[found].email)) break;
            printf("Invalid email. Please try again.\n");
        }

        while (1) {
            printf("Enter new phone number: ");
            scanf("%s", students[found].phoneNumber);
            if (isValidPhoneNumber(students[found].phoneNumber)) break;
            printf("Invalid phone number. Please try again.\n");
        }

        printf("Student information updated successfully.\n");
    } else {
        printf("Student ID not found.\n");
    }
}

void deleteStudent() {
    char idToDelete[10];
    int i;
    printf("Enter the student ID to delete: ");
    scanf("%s", idToDelete);
    int found = -1;
    for (i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, idToDelete) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        for (i = found; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        printf("Student deleted successfully.\n");
    } else {
        printf("Student ID not found.\n");
    }
}

void displayAllStudents() {
    int i;

    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("+-----+----------+----------------------+-------------------------------+---------------+\n");
    printf("| No. | ID       | Name                 | Email                         | Phone Number  |\n");
    printf("+-----+----------+----------------------+-------------------------------+---------------+\n");

    for (i = 0; i < studentCount; i++) {
        printf("| %-3d | %-8s | %-20s | %-30s | %-13s |\n",
               i + 1,
               students[i].id,
               students[i].name,
               students[i].email,
               students[i].phoneNumber);
    }

    printf("+-----+----------+----------------------+-------------------------------+---------------+\n");
}

void searchStudentByName() {
    char searchName[100];
    int i;  
    printf("Enter student name to search: ");
    scanf("%s", searchName);
    removeSpaces(searchName);

    int found = 0;
    for (i = 0; i < studentCount; i++) {
        if (strstr(students[i].name, searchName) != NULL) {
            printf("Found Student: ID: %s, Name: %s, Age: %d, Email: %s, Phone: %s\n",
                   students[i].id, students[i].name, students[i].age, students[i].email, students[i].phoneNumber);
            found = 1;
        }
    }
    if (!found) {
        printf("No student found with the name: %s\n", searchName);
    }
}

void sortStudentByName() {
    int i, j;
    Student temp;
    for (i = 0; i < studentCount - 1; i++) {
        for (j = i + 1; j < studentCount; j++) {
            if (strcmp(students[i].name, students[j].name) > 0) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Students have been sorted by name.\n");
}

//Teacher Functions
void addTeacher() {
    Teacher newTeacher;
    generateTeacherID(newTeacher.id);
    
	printf("Generated teacher ID: %s\n", newTeacher.id);
    printf("Enter teacher name: ");
    scanf(" %[^\n]%*c", newTeacher.name);
    printf("Enter teacher age: ");
    scanf("%d", &newTeacher.age);
    printf("Enter teacher email: ");
    scanf("%s", newTeacher.email);
    printf("Enter teacher phone number: ");
    scanf("%s", newTeacher.phoneNumber);
   
    if (isValidTeacherData(&newTeacher)) {
        teachers[teacherCount++] = newTeacher;
        saveTeacherDataToFile();
        printf("Teacher added successfully!\n");
    } else {
        printf("Teacher data is invalid. Please try again.\n");
    }
}




void deleteTeacher() {
    char idToDelete[10];
    int i;
    printf("Enter the teacher ID to delete: ");
    scanf("%s", idToDelete);

    int found = -1;
    for (i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].id, idToDelete) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (i = found; i < teacherCount - 1; i++) {
            teachers[i] = teachers[i + 1];
        }
        teacherCount--;
        printf("Teacher deleted successfully.\n");
    } else {
        printf("Teacher ID not found.\n");
    }
}

void displayAllTeachers() {
    int i;

    if (teacherCount == 0) {
        printf("No teachers to display.\n");
        return;
    }

    printf("+-----+----------+----------------------+-------------------------------+---------------+\n");
    printf("| No. | ID       | Name                 | Email                         | Phone Number  |\n");
    printf("+-----+----------+----------------------+-------------------------------+---------------+\n");

    for (i = 0; i < teacherCount; i++) {
        printf("| %-3d | %-8s | %-20s | %-30s | %-13s |\n",
               i + 1,
               teachers[i].id,
               teachers[i].name,
               teachers[i].email,
               teachers[i].phoneNumber);
    }

    printf("+-----+----------+----------------------+-------------------------------+---------------+\n");
}
void sortTeacherByName(){
	int i,j;
	Teacher temp;
	for(i=0;i<teacherCount-1;i++){
		for(j=i+1;j<teacherCount;j++){
			if(strcmp(teachers[i].name,teachers[j].name)>0){
				temp=teachers[i];
				teachers[i]=teachers[j];
				teachers[j]=temp;
			}
		}
		}
		printf("Teacher have been sorted by Name\n");
				
}

void editTeacher() {
    char idToEdit[10];
    printf("Enter the teacher ID to edit: ");
    scanf("%s", idToEdit);

    int found = -1;
    int i;
    for ( i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].id, idToEdit) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        Teacher *teacher = &teachers[found];
        printf("Editing teacher with ID %s:\n", teacher->id);

        printf("Enter new teacher name: ");
        scanf(" %[^\n]%*c", teacher->name);
        trimWhitespace(teacher->name);

        printf("Enter new teacher age: ");
        scanf("%d", &teacher->age);

        while (1) {
            printf("Enter new teacher email: ");
            scanf("%s", teacher->email);
            if (isValidEmail(teacher->email)) break;
            printf("Invalid email. Please try again.\n");
        }

        while (1) {
            printf("Enter new teacher phone number: ");
            scanf("%s", teacher->phoneNumber);
            if (isValidPhoneNumber(teacher->phoneNumber)) break;
            printf("Invalid phone number. Please try again.\n");
        }

        if (isValidTeacherData(teacher)) {
            saveTeacherDataToFile();
            printf("Teacher information updated successfully!\n");
        } else {
            printf("Teacher data is invalid. No changes were saved.\n");
        }
    } else {
        printf("Teacher ID not found.\n");
    }
}

// Menus
void displayMainMenu() {
    printf("\n=== Main Menu ===\n");
    printf("1. Admin Menu\n");
    printf("2. Teacher Menu\n");
    printf("3. Student Menu\n");
    printf("4. Class Menu\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void displayAdminMenu() {
    printf("\n==== Admin Menu ====\n");
    printf("1. Add Student\n");
    printf("2. Display All Students\n");
    printf("3. Edit Student\n");
    printf("4. Delete Student\n");
    printf("5. Search Student by Name\n");
    printf("6. Sort Students by Name\n");
    printf("7. Add Teacher\n");
    printf("8. Delete Teacher\n");
    printf("9. Display All Teachers\n");
    printf("10.Sort Teachers By Name\n");
    printf("11.Edit Teacher\n");
    printf("12. Back to Main Menu\n");
    printf("Enter your choice: ");
}

void displayTeacherMenu() {
    printf("\n=== Teacher Menu ===\n");
    printf("1. View All Students\n");
    printf("2. Search Student by Name\n");
    printf("3. Sort Students by Name\n");
    printf("4. Edit Student\n");
    printf("5. Delete Student\n");
    printf("6. Exit to Main Menu\n");
    printf("Enter your choice: ");
}

void displayStudentMenu() {
    printf("\n=== Student Menu ===\n");
    printf("1. View All Students\n");
    printf("2. Search Student by Name\n");
    printf("3. Exit to Main Menu\n");
    printf("Enter your choice: ");
}
void displayClassMenu(){
	printf("\n=== Class Menu ===\n");
	printf("1.Display ALL  Class\n");
	printf("2.Add Class\n");
	printf("3.Edit Class\n");
	printf("4.Delete Class\n");
	printf("5.Detail Class\n");
	printf("6.Exit to Main Menu\n");
	printf("Enter your choice:\n");
}

