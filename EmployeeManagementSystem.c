#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PATH_LEN 1028

char current_file_path[MAX_PATH_LEN] = {0};
int tempIntPosition;

int counter;
char filename[100] = "";

struct Employees{
    int id;
    char name[100];
    int age;
    char department[100];
    char position[50];
    int days;
    float salary;
}employee[100];

int isID7Digits(int id) { 
    if (id < 1000000 || id > 9999999) {
        return 0;
    }
    return 1;
}
int isFieldEmpty(int i) { 
    if(employee[i].id != 0 && strlen(employee[i].name) > 0 && 
    employee[i].age > 0 && strlen(employee[i].department) > 0 &&
    strlen(employee[i].position) > 0 && employee[i].days > 0) {
        return 1;    
    }
    return 0;
}
void displayMenu(){ 
    printf("1. Add New Employee\n2. View All Employee\n3. Update Employee Information\n4. Delete Employee Record\n5. Search/Sort Employees\n6. Compute Employee Salary\n7. Exit\n");
}

void displayPosition(){ 
    printf("Choose among the positions:\n1. Manager\n2. Staff\n 3. Clerk\n 4. Others\n");
}
bool validateFullPath(const char* path) {
    if (path == NULL || strlen(path) == 0) {
        printf("[Error] Path is empty.\n");
        return false;
    }

    const char* invalidChars = "<>\"|?*!@#$%^&()+=[]{}`~;,'";

    for (int i = 0; path[i] != '\0'; ++i) {
        if (strchr(invalidChars, path[i])) {
            printf("[Error] Path contains invalid character '%c'.\n", path[i]);
            return false;
        }
    }

    int len = strlen(path);
    if (len < 4 || strcmp(path + len - 4, ".txt") != 0) {
        printf("[Error] File must end with .txt extension.\n");
        return false;
    }
    return true;
}

char* askUserDirectory() {
    char directory[MAX_PATH_LEN];
    char filename[MAX_PATH_LEN];
    char fullpath[MAX_PATH_LEN * 2]; 

    printf("Enter a directory path: ");
    fgets(directory, sizeof(directory), stdin);
    directory[strcspn(directory, "\n")] = '\0'; 
    
    int dir_len = strlen(directory);
    if(directory[0] == '"' && directory[dir_len - 1] == '"'){
        for(int i = 0; i < dir_len- 1; i++){
            directory[i - 1] = directory[i];
        }
        directory[dir_len - 2] = '\0';
    }
    for (int i = 0; directory[i] != '\0'; ++i) {
        if (directory[i] == '\\') {
            directory[i] = '/';
        }
    }

    
    if (dir_len > 0 && directory[dir_len - 1] == '/') {
        directory[dir_len - 1] = '\0';
    }

    printf("Enter file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';  

    if (strlen(filename) < 4 || strcmp(filename + strlen(filename) - 4, ".txt") != 0) {
        strcat(filename, ".txt");
    }

    snprintf(fullpath, sizeof(fullpath), "%s/%s", directory, filename);

    char* result = (char*)malloc(strlen(fullpath) + 1);
    if (!result) {
        fprintf(stderr, "Memory allocation failed!\n");
        return NULL;
    }
    strcpy(result, fullpath);

    return result;
}
char* convertIntPositionToString(int num) {
    switch (num) {
        case 1:
            return "Manager";
        case 2:
            return "Staff";
        case 3:
            return "Clerk";
        case 4:
            return "Others";
        default:
            return "Invalid Position";
    }
}

void saveToFile(){ 
    FILE *fp;

    fp = fopen(current_file_path, "w");
    if(fp == NULL){
        printf("Error: Cannot open or create file at %s\n", current_file_path);
        return;
    }

    for(int i = 0; i < counter; i++){
        employee[i].name[strcspn(employee[i].name, "\n")] = '\0';
        employee[i].department[strcspn(employee[i].department, "\n")] = '\0';
        fprintf(fp, "%d|%s|%d|%s|%s|%d|%.2f\n", 
                employee[i].id, 
                employee[i].name, 
                employee[i].age, 
                employee[i].department, 
                employee[i].position, 
                employee[i].days, 
                employee[i].salary);
    }

    fclose(fp);
    printf("Data saved successfully to %s\n\n", current_file_path);
}
void loadFromFile(){ 
    FILE *fp;

    fp = fopen(current_file_path, "r");
    if(fp == NULL){
        printf("File: %s: not found. Creating file at the given directory.\n", current_file_path);
        counter = 0;
        return;
    }

    counter = 0;
    while(fscanf(fp, "%d|%[^|]|%d|%[^|]|%[^|]|%d|%f\n",
          &employee[counter].id,
           employee[counter].name, 
          &employee[counter].age, 
           employee[counter].department, 
           employee[counter].position, 
          &employee[counter].days, 
          &employee[counter].salary) == 7){
        counter++;
    }
    fclose(fp);
    printf("Data loaded successfully from %s\n", current_file_path);
}

void addEmployee(int currentEmployee){ 
    int replicate;
    char temp;
    char ch;

    do{ 
        replicate = 0;
        printf("Enter your 7-digit Employee I.D.: ");

        if(scanf("%d%c", &employee[currentEmployee].id, &temp) != 2 || temp != '\n'){ 
            printf("Invalid input. Not an integer.\n");
            while((ch = getchar()) != '\n' && ch != EOF); 
            continue;
        }

        if(isID7Digits(employee[currentEmployee].id) == 0){ 
            printf("Invalid I.D.! It must be exactly 7 digits.\n");
            replicate = 1;
            continue;
        }

        for(int i = 0; i < currentEmployee; i++){ 
            if(employee[i].id == employee[currentEmployee].id){
                printf("I.D. already exists! Please enter a different one.\n");
                replicate = 1;
                break;
            }
        }

    }while(replicate != 0 || isID7Digits(employee[currentEmployee].id) == 0);

    printf("I.D. successfully added.\n\n");

    printf("Enter your Name: ");
    fgets(employee[currentEmployee].name, 100, stdin);
    employee[currentEmployee].name[strcspn(employee[currentEmployee].name, "\n")] = '\0';
    printf("Name successfully added.\n\n");

    while(true) {
        printf("Enter new Age: "); 
        while(scanf("%d%c", &employee[currentEmployee].age, &temp) != 2 || temp != '\n'){ 
            while((ch = getchar()) != '\n' && ch != EOF);
            printf("Invalid input. Not an integer.\n");
            continue;
        }
        if(employee[currentEmployee].age < 18 || employee[currentEmployee].age > 80){
            printf("Invalid age. Must be between 18 and 80.\n");
            continue;
        }
        break;
    }
    printf("Age successfully added.\n\n");

    
    printf("Enter your Department: ");
    fgets(employee[currentEmployee].department, 100, stdin);
    employee[currentEmployee].department[strcspn(employee[currentEmployee].department, "\n")] = '\0';
    printf("Department successfully added.\n\n");

    displayPosition();
    do{ 
        printf("Enter your Position: ");
        if(scanf("%d%c", &tempIntPosition, &temp) != 2 || temp != '\n'){ 
            while((ch = getchar()) != '\n' && ch != EOF);
            printf("Invalid input. Not an integer.\n");
            continue;
        }
    }while(tempIntPosition < 1 || tempIntPosition > 4);
    strcpy(employee[currentEmployee].position, convertIntPositionToString(tempIntPosition));
    printf("Position successfully added.\n\n");

    printf("Enter days Rendered: ");
    while(scanf("%d%c", &employee[currentEmployee].days, &temp) != 2 || temp != '\n'){ 
        printf("Invalid input. Not an integer.\n");
        while((ch = getchar()) != '\n' && ch != EOF);
        printf("Enter days Rendered: ");
    }
    printf("Days rendered successfully added.\n\n");

     saveToFile();
}

void viewAllEmployee(){ 
    if(counter == 0){
        printf("No employee records found.\n\n");
        return;
    }

    printf("\n%-10s %-20s %-5s %-15s %-10s %-12s %-10s\n", "ID", "Name", "Age", "Dept", "Pos", "Days", "Salary"); 
    for(int i = 0; i < counter; i++){
        if(isFieldEmpty(i) == 1){ 
            printf("%-10d %-20s %-5d %-15s %-10s %-12d ",
                employee[i].id, 
                employee[i].name, 
                employee[i].age, 
                employee[i].department, 
                employee[i].position, 
                employee[i].days);
        } else {
                printf("Error! Some fields are not filled.\n");
                return;
        }
        if(employee[i].salary == 0){ 
            printf("%-10s\n", "N/A");
        }else{
            printf("%.2f\n", employee[i].salary);
        }
    }
    printf("\n");
}


void updateEmployeeRecord(){ 
    if(counter == 0) {
        printf("No employee to update.\n\n");
        return;
    }
    int id, found = 0;
    char temp, ch;
    
    do {
        printf("Enter Employee ID to update: ");
        while(scanf("%d%c", &id, &temp) != 2 || temp != '\n'){
            while((ch = getchar()) != '\n' && ch != EOF);
            printf("Invalid input. Not an integer.\n");
            continue;
        }
        if(isID7Digits(id) == 0){
            printf("Invalid I.D.! It must be exactly 7 digits.\n");
        }
    } while (isID7Digits(id) == 0);
    

    for(int i = 0; i < counter; i++){ 
        if(employee[i].id == id){
            found = 1;
            
            printf("Enter new Name: "); 
            fgets(employee[i].name, 100, stdin);
            while(getchar() != '\n');
            employee[i].name[strcspn(employee[i].name, "\n")] = '\0';

            while(true) {
                printf("Enter new Age: "); 
                while(scanf("%d%c", &employee[i].age, &temp) != 2 || temp != '\n'){ 
                    while((ch = getchar()) != '\n' && ch != EOF);
                    printf("Invalid input. Not an integer.\n");
                    continue;
                }
                if(employee[i].age < 18 || employee[i].age > 80){
                    printf("Invalid age. Must be between 18 and 80.\n");
                    continue;
                }
                break;
            }
            
            printf("Enter new Department: "); 
            fgets(employee[i].department, 100, stdin);
            while(getchar() != '\n');
            employee[i].department[strcspn(employee[i].department, "\n")] = '\0';

            displayPosition();
            do{
                printf("Enter new Position: ");
                scanf("%d", &tempIntPosition);
            }while(tempIntPosition < 1 || tempIntPosition > 4);
            strcpy(employee[i].position, convertIntPositionToString(tempIntPosition));

            while(true) {
                printf("Enter new Days Rendered: ");
                while(scanf("%d%c", &employee[i].days, &temp) != 2 || temp != '\n'){
                    while((ch = getchar()) != '\n' && ch != EOF);
                    printf("Invalid input. Not an integer.\n");
                    continue;
                }
                break;
            }
            

            printf("Record updated successfully.\n\n");
            break;
        }
    }
    if(!found){
        printf("Employee ID not found.\n\n");
    }

    saveToFile();
}

void deleteEmployeeRecord(){ 
    if(counter == 0) {
        printf("No employee to delete.\n\n");
        return;
    }
    int id, found = 0;
    char temp, ch;
    do {
        printf("Enter Employee ID to delete: ");
        while(scanf("%d%c", &id, &temp) != 2 || temp != '\n'){
            while((ch = getchar()) != '\n' && ch != EOF);
            printf("Invalid input. Not an integer.\n");
            continue;
        }
        if(isID7Digits(id) == 0){
            printf("Invalid I.D.! It must be exactly 7 digits.\n");
        }
    } while (isID7Digits(id) == 0);

    for(int i = 0; i < counter; i++){
        if(employee[i].id == id){
            found = 1;
            for(int j = i; j < counter - 1; j++){
                employee[j] = employee[j + 1];
            }
            counter--; 
            printf("Employee deleted successfully.\n\n");
            break;
        }
    }

    if(!found){
        printf("Employee ID not found.\n\n");
    }

    saveToFile();
}
void searchAndSort(){ 

    if(counter == 0) {
        printf("No employee to search or sort.\n\n");
        return;
    }
    int option, found = 0;
    char keyword[100], ch;
    struct Employees tempEmp;
    
    printf("\nSearch and Sort Options:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Department\n");
    printf("3. Sort by Name (asc) and Salary (desc)\n");
    do {
        printf("Enter your choice: ");
        while (scanf("%d%c", &option, &ch) != 2 || ch != '\n') {
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("Invalid input. Not an integer.\n");
            continue;
        };
        if(option < 1 || option > 3){
            printf("Invalid choice. Please enter 1-3.\n");
            continue;
        }
    }while(option < 1 || option > 3);

    if(option == 1 || option == 2){

        if(option == 1){
            printf("Enter a name: ");
        } else { 
            printf("Enter a department: ");
        }
         
        fgets(keyword, 100, stdin);
        keyword[strcspn(keyword, "\n")] = '\0';

        printf("\n%-10s %-20s %-5s %-15s %-10s %-12s %-10s\n", "ID", "Name", "Age", "Dept", "Pos", "Days", "Salary");

        for(int i = 0; i < counter; i++){
            if((option == 1 && strstr(employee[i].name, keyword)) || (option == 2 && strstr(employee[i].department, keyword))){//Check if the inputted word is found in struct;
                if (isFieldEmpty(i) == 0){
                    if(option == 1){
                        printf("\n\nName found!, but error due to some fields not filled.\n");
                    }else {
                        printf("Error due to some fields not filled.\n");
                    }
                    continue;
                }
                
                printf("%-10d %-20s %-5d %-15s %-10s %-12d ", employee[i].id, employee[i].name, employee[i].age, employee[i].department, employee[i].position, employee[i].days);

                if(employee[i].salary == 0){
                    printf("%-10s\n", "N/A");
                }else{
                    printf("%.2f\n", employee[i].salary);
                }

                found = 1;
            }
        }
        if(!found){
            printf("No matching records found.\n");
        }
    }
    else if(option == 3){
        
        int choice;
        char ch, temp;

        if(counter == 1) {
            printf("\nSorted Employees by Name [A-Z]:\n");
            printf("%-5s %-18s %-5s %-15s %-6s %-6s %-10s\n", "ID", "Name", "Age", "Dept", "Pos", "Days", "Salary");
            printf("%-5d %-18s %-5d %-15s %-6s %-6d %-10.2f\n", employee[0].id, employee[0].name, employee[0].age, employee[0].department, employee[0].position, employee[0].days, employee[0].salary);
            return;
        } 
        
        do{
            printf("\n1.Sort by name(Ascending).\n2.Sory by salary(descending).\n\n");
            printf("Enter your choice: ");
            while(scanf("%d%c", &choice, &temp) != 2 || temp != '\n'){
                while((ch = getchar()) != '\n' && ch != EOF);
                printf("Invalid input. Not an integer.\n");
                continue;
            };
        }while(choice != 1 && choice != 2);

        if(choice == 1){
            for(int i = 0; i < counter - 1; i++) {
                for(int j = 0; j < counter - i - 1; j++) {
                    int nameComp = strcmp(employee[j].name, employee[j + 1].name);
                    if(nameComp > 0) {
                        tempEmp = employee[j];
                        employee[j] = employee[j + 1];
                        employee[j + 1] = tempEmp;
                    }
                }
            }
            printf("\nSorted Employees by Name [A-Z]:\n");
            printf("\n%-10s %-20s %-5s %-15s %-10s %-12s %-10s\n", "ID", "Name", "Age", "Dept", "Pos", "Days", "Salary");
            for(int i = 0; i < counter; i++){
                printf("%-10d %-20s %-5d %-15s %-10s %-12d ", employee[i].id, employee[i].name, employee[i].age, employee[i].department, employee[i].position, employee[i].days);
                if(employee[i].salary == 0){
                    printf("%-10s\n", "N/A");
                }else{
                    printf("%.2f\n", employee[i].salary);
                }
            }
        }else if (choice == 2){
            for(int i = 0; i < counter - 1; i++) {
                for(int j = 0; j < counter - i - 1; j++) {
                    if(employee[j].salary < employee[j + 1].salary) {
                        tempEmp = employee[j];
                        employee[j] = employee[j + 1];
                        employee[j + 1] = tempEmp;
                    }
                }
            }
            printf("\nSorted Employees by Salary [High-Low]:\n");
            printf("\n%-10s %-20s %-5s %-15s %-10s %-12s %-10s\n", "ID", "Name", "Age", "Dept", "Pos", "Days", "Salary");
            for(int i = 0; i < counter; i++){
                printf("%-10d %-20s %-5d %-15s %-10s %-12d ", employee[i].id, employee[i].name, employee[i].age, employee[i].department, employee[i].position, employee[i].days);
                if(employee[i].salary == 0){
                    printf("%-10s\n", "N/A");
                }else{
                    printf("%.2f\n", employee[i].salary);
                }
            }
        }else{
            printf("Invalid choice.\n");
        }
        
    }
    else{
        printf("Invalid option.\n");
    }
}

void computeEmployeeSalary(){ 
    if(counter == 0){
        printf("No employees to compute salary.\n\n");
        return;
    }

    for(int i = 0; i < counter; i++){
        float dailyRate = 0;

        if (strcmp(employee[i].position, "Manager") == 0) {
            dailyRate = 1500.00;
        } else if (strcmp(employee[i].position, "Staff") == 0) {
            dailyRate = 1000.00;
        } else if (strcmp(employee[i].position, "Clerk") == 0) {
            dailyRate = 800.00;
        } else if (strcmp(employee[i].position, "Others") == 0) {
            dailyRate = 500.00;
        } else {
            dailyRate = 0;
        }
        employee[i].salary = dailyRate * employee[i].days;
    }

    printf("Salaries computed for all employees successfully.\n\n");
    saveToFile();
}

void main(){
    int choice;
    char ch, temp;

    printf("\n============================================================================================================\n");
    printf("\t\t\t\t    EMPLOYEE MANAGEMENT SYSTEM");
    printf("\n============================================================================================================\n");
    
    while(true){
        char* tempPath = askUserDirectory();
        if (tempPath != NULL && validateFullPath(tempPath)) {
            strncpy(current_file_path, tempPath, sizeof(current_file_path) - 1);
            current_file_path[sizeof(current_file_path) - 1] = '\0';
            free(tempPath);
            break;
        } else {
            printf("[Error] Invalid file path or name. Please try again.\n");
            if (tempPath) free(tempPath);
        }
        free(tempPath);
    }
    loadFromFile();

    printf("\n======================================================================================================\n");
    printf("\t\t\t\t\t    START");
    printf("\n=====================================================================================================\n");

    do{
        printf("\n=================================\n\t    Main Menu\t        =\n=================================\n");
        displayMenu(); 
        printf("==================================================================================================\n");
        do{
            printf("Enter your choice: ");
            while(scanf("%d%c", &choice, &temp ) < 1 || choice > 7 || temp != '\n'){//Should be integer;
                printf("Invalid input. Not an integer.\n");
                while((ch = getchar()) != '\n' && ch != EOF);
                continue;
            }

        }while(choice < 1 || choice > 7);
            switch(choice){
                case 1:
                    addEmployee(counter);
                    counter++; 
                break;   
                case 2:
                    viewAllEmployee();
                break;

                case 3:
                    updateEmployeeRecord();  
                break;

                case 4:
                    deleteEmployeeRecord();
                break;

                case 5:
                    searchAndSort();
                break;

                case 6:
                    computeEmployeeSalary();
                break;
            }
    }while(choice != 7);

    printf("Exiting program. Goodbye!\n");

    printf("\n============================================================================================================================================================\n");
    printf("\t\t\t\t    END");
    printf("\n============================================================================================================================================================\n");

    getch();
}