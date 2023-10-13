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

void writeFile();
// This function writes at least 5 student records to the file whose name will be inputted by the user. The student record will be stored in the file 1 record at a time or all records are written once ONLY (i.e executing 1 fwrite() statement ONLY).

int main(){
  writeFile();
}

void displayHeader(){
    printf("\n\n");
    printf("%-10s", "ID No.");
    printf("%-16s", "Lastname");
    printf("%-24s", "Firstname");
    printf("%-3s", "MI");
    printf("%-8s", "Course");
    printf("%5s", "Year");
    printf("\n\n");
}
void displayStudent(Studtype S){
    printf("\n");
    printf("%-10d", S.ID);
    printf("%-16s", S.name.LN);
    printf("%-24s", S.name.FN);
    printf("%-3c", S.name.MI);
    printf("%-8s", S.course);
    printf("%5d", S.yrLevel);
}
void writeFile(){

  // These are the students we will WRITE to the FILE.

  // Since the focus is on writing to the file, student record variables can be declared and initialized instead of inputting from the keyboard.
  Studtype newStudent_1 = 
    {{"ACHILLE", 'M', "LANUTAN"}, 22103514, "BSIT", 2};
  Studtype newStudent_2 =
    {{"DIANNE", 'A', "YUVALLOS"}, 22103518, "COMM", 1};
  Studtype newStudent_3 = 
    {{"XANDER", 'J', "LABIDE"}, 22103515, "BSIT", 2};
  Studtype newStudent_4 = 
    {{"JASPER", 'L', "MARBELLA"}, 22103516, "BSIT", 3};
  Studtype newStudent_5 = 
    {{"JAN CARLO", 'A', "JUAB"}, 22103517, "BSCS", 4};

  // 1) GIGO (Garbage In Garbage Out). Before writing to the file, make sure the data are correct by displaying data on the screen.
  printf("These are the students to be WRITTEN to the FILE.\n");
  displayHeader();

  displayStudent(newStudent_1);
  displayStudent(newStudent_2);
  displayStudent(newStudent_3);
  displayStudent(newStudent_4);
  displayStudent(newStudent_5);

  
  FILE *fp;

  // Code for writing these to file
  fp = fopen("test.dat", "wb");

  printf("\n\t\tWRITING TO FILE...\n");
  if (fp != NULL){

    // fwrite() parameters explanation
    // &newStudent_1       =>    what we want to write TO the FILE
    // sizeof(Studtype)    =>    type of data to be added to FILE (in bytes)
    // 1                   =>    how many Studtype we want to add
    // fp                  =>    file we want to write to
    fwrite(&newStudent_1, sizeof(Studtype), 1, fp);
    fwrite(&newStudent_2, sizeof(Studtype), 1, fp);
    fwrite(&newStudent_3, sizeof(Studtype), 1, fp);
    fwrite(&newStudent_4, sizeof(Studtype), 1, fp);
    fwrite(&newStudent_5, sizeof(Studtype), 1, fp);

    fclose(fp);
    // After writing to our file, since our mode is "wb" which is to write binary to "test.dat", we need to close our file first so that we can then read our file in mode "rb".
  }

  // Code for reading the newly written students from the file "test.dat"
  // We display these newly written students as well to verify that our fwrite() executed properly and without any errors whatsoever
  fp = fopen("test.dat", "rb");

  printf("\n\t\tDISPLAYING DATA FROM FILE...\n");
  if (fp != NULL){

    rewind(fp);
    // we need to rewind our FILE pointer because after executing fwrite(), our file pointer would be at the end of the file and not at the beginning.
    // since we want to read the data, we want to return to the first line of the FILE so that we can read starting from the very first Studtype inserted.

    Studtype student;

    displayHeader();
    while (fread(&student, sizeof(Studtype), 1, fp)){
      displayStudent(student);
    }

    fclose(fp);
  }  
}

