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

void readFile();
// This function reads the student records in the given file 1 record at a time and calls displayStudent() to display all the fields in the given record. Note that the name of the file will be inputted by the user from the keyboard.

int main(){
  readFile();

  return 0;
}

// Notice that the formatting of spaces in displayHeader() and displayStudent() is the same so that everything will be lined upon display.
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
void readFile(){
  char FILENAME[24];
  FILE *fp;
  Studtype student;
  int count = 0;

  printf("Enter the file you want to open: ");
  scanf("%s", &FILENAME);

  fp = fopen(FILENAME, "rb");

  if (fp != NULL){
    // Called only once
    displayHeader();

    // fread() parameters explanation:
    // &student           =>    put the data read from "students.dat" into Studtype student
    // sizeof(Studtype)   =>    what kind of data we want to read (in bytes)
    // 1                  =>    how many Studtype we want to read per iteration
    // fp                 =>    what file pointer we're using
    while (fread(&student, sizeof(Studtype), 1, fp) != 0){
      displayStudent(student);
      // count++;

      // if (count == 20){
      //   printf("\n");
      //   system("pause");
      // }
    }
    fclose(fp);
  } else {
    printf("fopen() unsuccessful\n");
  }
}
