#include <stdio.h>
#include <stdlib.h>

//* Data Structure Definitions

typedef struct {
  char FN[24];    //firstname
  char MI;        //middle initial
  char LN[16];    //lastname
} Nametype;

typedef struct {
  Nametype name;
  int ID;
  char course[8]; //BSCS, BSIS, BSIT
  int yrLevel;
} Studtype;

//* Function Prototypes

void displayHeader();
// This function will display the field titles such as ID, Lastnames, etc. This will be called once only and will be called before any call to displayStudent().

void displayStudent(Studtype student);
// This function will display all the field members of the given Studtype record in 1 horizontal line. After every 20 records displayed, call the OS command “Pause” to halt/stop until any key is pressed in the keyboard.

void readAppendFile();
// This function will read the contents of a file whose name will be inputted by the user and append its contents to another file whose name will also be inputted by the user. Notes: GIGO (Garbage In Garbage Out). Before writing to the file, make sure the data are correct by displaying data on the screen.

//* Problem Specification: 
// Create the program (named: readAppendfile.c) that will: 
//    1) READ the file created in Exercise #2 "test.dat" (with at least 5 student records) and 
//    2) APPEND the student records to the file given in exercise #1. ("students.dat")

int main(){
  readAppendFile();

  // After successfully appending our file, we can go back to our readFile.c and run it so that we can see the newly written data displayed.

  return 0;
}

void displayHeader(){
  printf("\n\n");
  printf("%-10s", "ID No.");
  printf("%-16s", "Lastname");
  printf("%-24s", "Firstname");
  printf("%-3s", "MI");
  printf("%-8s", "Course");
  printf("%5s", "Year");
  printf("\n");
}
void displayStudent(Studtype student){
  printf("\n");
  printf("%-10d", student.ID);
  printf("%-16s", student.name.LN);
  printf("%-24s", student.name.FN);
  printf("%-3c", student.name.MI);
  printf("%-8s", student.course);
  printf("%5d", student.yrLevel);
}
void readAppendFile(){
  FILE *A;   // "students.dat"
  FILE *B;   // "test.dat"

  A = fopen("students.dat", "ab");
  // Our mode for file pointer A is "ab" because we're APPENDING data from "test.dat" to "students.dat". Automatically, our file pointer would point at the EOF (end of file) because we are using "ab" mode. So, our file pointer is ready to append new data from other files.

  B = fopen("test.dat", "rb");
  // Our mode for file pointer B is "rb" because we want to READ data from "test.dat" so that we can then append the read data to "students.dat".

  if (A != NULL && B != NULL){
    Studtype student;

    displayHeader();

    // Loop to read data from "test.dat" then append to "students.dat"
    while (fread(&student, sizeof(Studtype), 1, B)){
      // In a way, checks if its a valid ID (??) or NOT NULL
      if (student.ID > 0){
        fwrite(&student, sizeof(Studtype), 1, A);
        displayStudent(student);
      }
    }
    fclose(A);
    fclose(B);
    // We must not forget to close both files after doing any file manipulation.
  }
}

