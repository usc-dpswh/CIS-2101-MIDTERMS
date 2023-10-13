#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

void updateFile(char *oldCourse, char *newCourse);
// Given an old course and new course as parameters, the function will:
//    1) read the contents of a file 1 record at a time and whose name will be inputted by the user. 
//    2) If the course field of the current read student record is equivalent to the old course, course is updated to new course. 
//    3) Changes will right away be reflected to the external file by writing the updated student record to the file. Hint: fseek() is needed here.

int main(){
  updateFile("BSIT", "BSDICK");
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
void updateFile(char *oldCourse, char *newCourse){
  
  // Let user input which student's course they want to change
  char TARGET_STUDENT[24];
  
  printf("Enter the student's FIRST NAME whose course you wish to change: ");
  scanf("%s", &TARGET_STUDENT);

  FILE *A;    // students.dat

  A = fopen("test.dat", "rb+");

  Studtype student;
  if (A != NULL){
    while (fread(&student, sizeof(Studtype), 1, A) != 0){
      
      // if the user inputted TARGET_STUDENT and its oldCourse matches...
      if (strcmp(student.name.FN, TARGET_STUDENT) == 0 &&
          strcmp(student.course, oldCourse) == 0)
      {
        // store/replace the student's old course with the newCourse
        strcpy(student.course, newCourse);

        // since for every successful fread() our FILE pointer automatically moves on to the next # of bytes based on our sizeof(Studtype), we must go back to where it once using fseek() so we can use fwrite() to overwrite the student whose course we wish to change. 
        // it must be noted that we use "-sizeof(Studtype)" having a dash or negative to indicate we want to move LEFT not RIGHT.
        fseek(A, (long)-sizeof(Studtype), SEEK_CUR);

        // after moving our FILE pointer to where it originally was, we commit the changes with fwrite()
        fwrite(&student, sizeof(Studtype), 1, A);

        // then we go back to where we once again but forward (without "-") as compared to the first fseek() -sizeof(Studtype)
        fseek(A, sizeof(Studtype), SEEK_CUR);

        printf("Successfully updated file.\n");
      } 
    }
  }
  fclose(A);
}

// void updateFile(char oldCourse[], char newCourse[]) {
//     const char srcFile[30];

//     printf("Enter the source file to update: ");
//     scanf(" %s", &srcFile);

//     StudType buffer;

//     FILE *fp = fopen(srcFile, "r+b"); //allows the mode to open the file for reading and writing
//     if (fp != NULL) {
//         while (fread(&buffer, sizeof(StudType), 1, fp) != 0) {
//             if (strcmp(buffer.course, oldCourse) == 0) {
//                 strcpy(buffer.course, newCourse); //the buffer will get the new course
//                 fseek(fp, -sizeof(StudType), SEEK_CUR); //reposition the file pointer to the current studRec that buffer had

//                 //recall that for everytime an fread is successful it moves to the beginning of the next studRec

//                 //hence in this case, we have to let it position back
//                 fwrite(&buffer, sizeof(StudType), 1, fp);
//                 //when this is successful we reposition it to where it was
//                 fseek(fp, sizeof(StudType), SEEK_CUR);
//             }
//         }
//     }
// }