#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User structure
struct User
{
    char username[50];
    char password[50];
};

// Student self referential structure
struct Student
{
    int id;
    char name[50];
    char bloodGroup[5];
    char cellNumber[15];
    char mail[50];
    struct Student *next;
};
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
// Function prototypes
void displayMenu();
void addUser();
int loginUser();
void addStudent(FILE *file);
void addStudent2(FILE *file);
void updateStudent(FILE *file, struct Student *head);
void searchStudent(FILE *file);
void deleteStudent(FILE *file);
void deleteStudent2(FILE *file, int searchId);
void displayStudent(struct Student *student);
void displayAllStudents(struct Student *head);
void clearList(struct Student *head);
struct Student *loadStudents(FILE *file);

// Main function
int main()
{
    system("color 3");
    FILE *userFile = fopen("user_data.txt", "a+"); // for storing user name and password
    FILE *file = fopen("student_data.txt", "a+");  // for storing students information

    if (userFile == NULL || file == NULL)
    {
        printf("Error opening files!\n");
        return 1;
    }

    int choice;
    int loggedInUser = -1; // User not logged in initially

    do
    {
        if (loggedInUser == -1)
        {
            printf("\t\t\t\t\t\t--- User Authentication ---\n");
            printf("\t\t\t\t\t\t1. Register\n");
            printf("\t\t\t\t\t\t2. Login\n");
            printf("\t\t\t\t\t\t3. Exit\n");
            printf("\t\t\t\t\t\tEnter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                clearScreen();
                addUser();
                break;
            case 2:
                clearScreen();
                loggedInUser = loginUser();
                break;
            case 3:
                clearScreen();
                printf("Exiting the program.\n");
                return 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
        else
        {
            displayMenu();
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                clearScreen();
                addStudent(file);
                break;
            case 2:
                clearScreen();
                updateStudent(file, loadStudents(file));
                break;
            case 3:
                clearScreen();
                searchStudent(file);
                break;
            case 4:
                clearScreen();
                deleteStudent(file);
                break;
            case 5:
                clearScreen();
                clearList(loadStudents(file));
                displayAllStudents(loadStudents(file));
                break;
            case 6:
                clearScreen();
                loggedInUser = -1; // Log out the user
                printf("Logged out successfully.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }

    }
    while (1);

    fclose(userFile);
    fclose(file);
    return 0;
}


// Function to display the main menu
void displayMenu()
{
    printf("\t\t\t\t\t\t******************************\n");
    printf("\t\t\t\t\t\t*    Student Information     *\n");
    printf("\t\t\t\t\t\t*           System           *\n");
    printf("\t\t\t\t\t\t******************************\n");
    printf("\t\t\t\t\t\t|1. Add New Student          |\n");
    printf("\t\t\t\t\t\t|2. Update Student Info      |\n");
    printf("\t\t\t\t\t\t|3. Search Student           |\n");
    printf("\t\t\t\t\t\t|4. Delete Student           |\n");
    printf("\t\t\t\t\t\t|5. Display All Students     |\n");
    printf("\t\t\t\t\t\t|6. Logout                   |\n");
    printf("\t\t\t\t\t\t******************************\n");
}

// Function to add a new user
void addUser()
{
    struct User user;
    printf("Enter a new username: ");
    scanf("%s", user.username);

    printf("Enter a password: ");
    scanf("%s", user.password);

    FILE *userFile = fopen("user_data.txt", "a+");
    if (userFile == NULL)
    {
        printf("Error opening user data file!\n");
        return;
    }

    fwrite(&user, sizeof(struct User), 1, userFile);
    fclose(userFile);

    printf("User registered successfully.\n");
}

// Function to log in a user
int loginUser()
{
    struct User user;
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    FILE *userFile = fopen("user_data.txt", "a+");
    if (userFile == NULL)
    {
        printf("Error opening user data file!\n");
        return -1;
    }

    while (fread(&user, sizeof(struct User), 1, userFile) == 1)
    {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) // compare string
        {
            fclose(userFile);
            printf("Login successful. Welcome, %s!\n",username);
            return 1; // User logged in successfully
        }
    }

    fclose(userFile);
    printf("Login failed. Invalid username or password.\n");
    return -1; // User not logged in
}

// Function to add a new student
void addStudent(FILE *file)
{
    struct Student student;
    printf("Enter Student ID: ");
    scanf("%d", &student.id);

    fseek(stdin, 0, SEEK_END); /*set the file position indicator for the
                                  standard input stream (stdin) to the end of the file.*/

    printf("Enter Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    strtok(student.name, "\n"); // Remove newline character

    printf("Enter Blood Group: ");
    fgets(student.bloodGroup, sizeof(student.bloodGroup), stdin);
    strtok(student.bloodGroup, "\n");

    printf("Enter Cell Number: ");
    fgets(student.cellNumber, sizeof(student.cellNumber), stdin);
    strtok(student.cellNumber, "\n");

    printf("Enter Email: ");
    fgets(student.mail, sizeof(student.mail), stdin);
    strtok(student.mail, "\n");

    fseek(file, 0, SEEK_END);
    fwrite(&student, sizeof(struct Student), 1, file);
    printf("Student added successfully.\n");
}

// Function to update student information
void updateStudent(FILE *file, struct Student *head)
{
    printf("Enter id to update: ");
    int searchId;
    scanf("%d", &searchId);
    struct Student *current = head;

    while (current != NULL)
    {
        if (current->id == searchId)
        {
            displayStudent(current);
            deleteStudent2(file,searchId);
            addStudent2(file);
            return;
        }
        current = current->next;
    }

    printf("Student with ID %d not found.\n", searchId);
}

// Function to search for a student
void searchStudent(FILE *file)
{
    int choice;
    printf("Search student by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Blood Group\n");
    printf("4. Cell Number\n");
    printf("5. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    int searchId;
    char searchString[50];
    struct Student student;

    fseek(file, 0, SEEK_SET);
    switch (choice)
    {
    case 1:
        printf("Enter Student ID: ");
        scanf("%d", &searchId);
        while (fread(&student, sizeof(struct Student), 1, file) == 1) // true when i find the data field of a student in the file
        {
            if (student.id == searchId)
            {
                displayStudent(&student);
                break;
            }
        }
        break;
    case 2:
        printf("Enter Student Name: ");
        scanf("%s", searchString);
        while (fread(&student, sizeof(struct Student), 1, file) == 1)
        {
            if (strcmp(student.name, searchString) == 0)
            {
                displayStudent(&student);
                break;
            }
        }
        break;
    case 3:
        printf("Enter Blood Group: ");
        scanf("%s", searchString);
        while (fread(&student, sizeof(struct Student), 1, file) == 1)
        {
            if (strcmp(student.bloodGroup, searchString) == 0)
            {
                displayStudent(&student);
                break;
            }
        }
        break;
    case 4:
        printf("Enter Cell Number: ");
        scanf("%s", searchString);
        while (fread(&student, sizeof(struct Student), 1, file) == 1)
        {
            if (strcmp(student.cellNumber, searchString) == 0)
            {
                displayStudent(&student);
                break;
            }
        }
        break;
    case 5:
        printf("Enter Email: ");
        scanf("%s", searchString);
        while (fread(&student, sizeof(struct Student), 1, file) == 1)
        {
            if (strcmp(student.mail, searchString) == 0)
            {
                displayStudent(&student);
                break;
            }
        }
        break;
    default:
        printf("Student not found.\n");
        break;
    }
}

// Function to delete a student
void deleteStudent(FILE *file)
{
    int searchId;
    printf("Enter Student ID to delete: ");
    scanf("%d", &searchId);

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error creating temporary file.\n");
        return;
    }

    struct Student student;

    // Copy all records to temp file except the one to be deleted
    fseek(file, 0, SEEK_SET);
    while (fread(&student, sizeof(struct Student), 1, file) == 1)
    {
        if (student.id != searchId)
        {
            fwrite(&student, sizeof(struct Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("student_data.txt");
    rename("temp.txt", "student_data.txt");

    printf("Student with ID %d deleted successfully.\n", searchId);

    // Reopen the file for further operations
    file = fopen("student_data.txt", "a+");
}

// Function to display a student's information
void displayStudent(struct Student *student)
{
    printf("\n*********************************\n");
    printf("*   Student Information         *\n");
    printf("*********************************\n");
    printf("ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Blood Group: %s\n", student->bloodGroup);
    printf("Cell Number: %s\n", student->cellNumber);
    printf("Email: %s\n", student->mail);
    printf("********************************\n");
}

// Function to display all students
void displayAllStudents(struct Student *head)
{
    struct Student *current = head;

    while (current != NULL)
    {
        displayStudent(current);
        current = current->next;
    }
}

// Function to clear the linked list
void clearList(struct Student *head)
{
    struct Student *current = head;
    struct Student *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

// Function to load students from file into a linked list
struct Student *loadStudents(FILE *file)
{
    struct Student *head = NULL;
    struct Student *current = NULL;
    struct Student temp;

    fseek(file, 0, SEEK_SET);

    while (fread(&temp, sizeof(struct Student), 1, file) == 1)
    {
        struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
        if (newStudent == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        *newStudent = temp;
        newStudent->next = NULL;

        if (head == NULL)
        {
            head = newStudent;
            current = newStudent;
        }
        else
        {
            current->next = newStudent;
            current = newStudent;
        }
    }

    return head;
}
// Function to delete a student
void deleteStudent2(FILE *file, int searchId)
{
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error creating temporary file.\n");
        return;
    }

    struct Student student;

    // Copy all records to temp file except the one to be deleted
    fseek(file, 0, SEEK_SET);
    while (fread(&student, sizeof(struct Student), 1, file) == 1)
    {
        if (student.id != searchId)
        {
            fwrite(&student, sizeof(struct Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("student_data.txt");
    rename("temp.txt", "student_data.txt");

    // Reopen the file for further operations
    file = fopen("student_data.txt", "a+");
}
// Function to add updated student
void addStudent2(FILE *file)
{
    struct Student student;
    printf("Enter Updated Student ID: ");
    scanf("%d", &student.id);

    fseek(stdin, 0, SEEK_END); // Clear input buffer

    printf("Enter Updated Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    strtok(student.name, "\n"); // Remove newline character

    printf("Enter Updated Blood Group: ");
    fgets(student.bloodGroup, sizeof(student.bloodGroup), stdin);
    strtok(student.bloodGroup, "\n");

    printf("Enter Updated Cell Number: ");
    fgets(student.cellNumber, sizeof(student.cellNumber), stdin);
    strtok(student.cellNumber, "\n");

    printf("Enter Updated Email: ");
    fgets(student.mail, sizeof(student.mail), stdin);
    strtok(student.mail, "\n");

    fseek(file, 0, SEEK_END);
    fwrite(&student, sizeof(struct Student), 1, file);
    printf("Student updated successfully.\n");
}
