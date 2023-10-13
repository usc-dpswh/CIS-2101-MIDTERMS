#include <stdio.h>
#include <stdlib.h>
#define MAX 5

// Struct definitions of Ver 1-4
typedef struct {
  int elem[MAX];
  int count;
} VER1, *VER2;

typedef struct {
  int *elem;
  int count;
} VER3, *VER4;

void populate_ver1(VER1 *main){
  int x;

  for (x = 0 ; x < MAX ; x++){
    main->elem[x] = x+1;
  }
}
void populate_ver2(VER2 main){
  int x;

  for (x = 0 ; x < MAX ; x++){
    main->elem[x] = x+1;
  }
}
void populate_ver3(VER3 *main){
  int x;

  for (x = 0 ; x < MAX ; x++){
    main->elem[x] = x+1;
  }
}
void populate_ver4(VER4 main){
  int x;

  for (x = 0 ; x < MAX ; x++){
    main->elem[x] = x+1;
  }
}

void deleteAt(VER1 *main, int index){
  int shift;

  if (index >= 0 && index < MAX){
    for (; index < MAX ; index++){
      main->elem[index] = main->elem[index+1];
    }
    main->count--;
  }
}
void locate(VER1 *main, int find){
  int x;

  for (x = 0 ; x < main->count && main->elem[x] != find; x++){};

  if (x < main->count){
    printf("%d FOUND!", find);
  } else {
    printf("%d NOT FOUND!", find);
  }
}

int main(){
  VER1 Dog;
  VER2 Cat;
  // VER3 Dinosaur;
  VER4 Alligator;

  // Initializations
  // Ver 1
  Dog.count = 5;
  populate_ver1(&Dog);
  deleteAt(&Dog, 3);
  locate(&Dog, 3);
  locate(&Dog, 4);

  // Ver 2
  // Cat = (VER2)malloc(sizeof(VER1));
  // Cat->count = 0;
  // populate_ver2(Cat);

  // // Ver 3
  // Dinosaur.elem = (int*)malloc(sizeof(int) * MAX);
  // Dinosaur.count = 0;
  // populate_ver3(&Dinosaur);

  // // Ver 4
  // Alligator = (VER4)malloc(sizeof(VER3));
  // Alligator->elem = (int*)malloc(sizeof(int) * MAX);
  // Alligator->count = 0;
  // populate_ver4(Alligator);

}