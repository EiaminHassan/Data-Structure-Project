
# 🏫 Student Information System in C

This is a simple **Student Information Management System** written in C that allows user registration, login, and full CRUD operations (Create, Read, Update, Delete) on student records. It uses file handling to store and retrieve data.

## 🔧 Features

- 👤 User registration and login system
- ➕ Add new student information
- 🔍 Search students by ID, Name, Blood Group, Cell Number, or Email
- ✏️ Update existing student records
- 🗑️ Delete student records
- 📋 Display all students
- 💾 Data persistence using file system (no database required)

## 📁 Files

- `Student_info.c` - Main C program file.
- `user_data.txt` - Stores registered usernames and passwords.
- `student_data.txt` - Stores student records.

## 📦 How to Run

### 📌 Compile

Use GCC or any C compiler:

```bash
gcc Student_info.c -o student_info
```

### ▶️ Run

```bash
./student_info
```

### 📌 For Windows

If you're using Windows:

```bash
gcc Student_info.c -o student_info.exe
student_info.exe
```

## 📝 Usage

1. Register a new user or log in using an existing account.
2. Once logged in, you can:
   - Add new students
   - Search student records
   - Update or delete records
   - View all student information
   - Log out when done

## 💡 Highlights

- Uses `fread` and `fwrite` for binary file I/O.
- Utilizes linked lists to manage student data in memory.
- Clear cross-platform screen clearing (`cls` for Windows, `clear` for Linux/Mac).
- Colorful terminal UI (Windows-specific `system("color 3")`).

## 🛠️ Requirements

- C Compiler (GCC/MinGW/Turbo C, etc.)
- Basic knowledge of C programming
- Terminal or command line interface

## 📚 Learning Outcomes

This project is great for practicing:

- File handling
- Structs and pointers
- Linked lists
- User authentication logic
- Menu-driven console interfaces

## 🙌 Author

Created by **Eiamin Hassan** as a student project to demonstrate file handling and basic data structures in C.
