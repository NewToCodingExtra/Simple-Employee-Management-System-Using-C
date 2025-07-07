# Simple-Employee-Management-System-Using-C

System Overview:
The Employee Management System is a console-based application developed in C that allows users to efficiently manage employee records. The system supports adding, viewing, updating, deleting, searching, and sorting employee data. It also computes employee salaries based on their position and days worked, and stores all data persistently in a text file.

Key features include:

Unique 7-digit employee ID validation

Employee data management (CRUD operations)

Search and sort employees by name or department

Salary computation with predefined daily rates for different positions

Data persistence through file saving and loading


Prerequisites
C compiler installed (e.g., gcc)

Visual Studio Code (VS Code) installed

Terminal or Command Prompt



How to Run in VS Code
Open the project folder in VS Code where your EmployeeManagementSystem.c file is located.

Compile the program:

Open the integrated terminal in VS Code (`Ctrl + `` or View > Terminal).

Run the following command to compile the code:

bash
gcc EmployeeManagementSystem.c -o EmployeeManagementSystem.exe
Run the program:

If you like working in the VS Code terminal, simply run:

bash
./EmployeeManagementSystem.exe
If you prefer to run the program outside VS Code:

Locate the compiled .exe file (usually in your project folder).

Right-click the .exe file and select Copy as path.

Open Command Prompt (cmd).

Right-click inside the Command Prompt window and select Paste, then press Enter.

The program will now run in the Command Prompt window.

Use the system by following the on-screen menu options.




How to Use the Program
After running the program and successfully loading or creating the employee record file, you will interact with the system through a menu-driven interface. The main menu options are:

text
1. Add New Employee
2. View All Employee
3. Update Employee Information
4. Delete Employee Record
5. Search/Sort Employees
6. Compute Employee Salary
7. Exit

Menu Options Explained:
1.Add New Employee

Enter a unique 7-digit Employee ID (validated to avoid duplicates).

Input employee details: Name, Age (between 18 and 80), Department, Position (choose from Manager, Staff, Clerk, Others), and Days Rendered.

The system saves the new employee record automatically.

2.View All Employee

Displays all employee records in a formatted table showing ID, Name, Age, Department, Position, Days Rendered, and Salary (if computed).

If no records exist, a message will inform you.

3.Update Employee Information

Enter the Employee ID of the record you want to update.

Modify any of the fields: Name, Age, Department, Position, Days Rendered.

Changes are saved automatically.

4.Delete Employee Record

Enter the Employee ID of the record you want to delete.

The system removes the employee from the records and saves the updated data.

5.Search/Sort Employees

Choose to search employees by Name or Department by entering keywords.

Or sort employees either by Name (ascending) or Salary (descending).

Results are displayed in a formatted table.

6.Compute Employee Salary

Calculates salary for all employees based on their position and days rendered.

Daily rates used: Manager = PHP 1500, Staff = PHP 1000, Clerk = PHP 800, Others = PHP 500.

Saves the computed salaries to the record file.

7.Exit

Exits the program safely.



Additional Instructions for Inputting the Record File Path and Name
When prompted to enter the directory path where you want to save or load your employee record file, simply paste the copied folder path as is.

You do NOT need to remove any quotation marks because the program automatically removes them for you.

After entering the folder path, press Enter.

Then, enter the file name you want to use for your record file. You can include the .txt extension or omit it — the program will add .txt automatically if you don’t include it.



Important Behavior of the Program Regarding the File
If the file you specify does not exist, the program will automatically create a new file at the given location.

If the file already exists, the program will load the existing data from that file so you can continue managing your employee records.
