#include <stdio.h>
#include <stdlib.h>
#define MAX 8

typedef char SET[MAX];

void init(SET main){
  int x;
  
  for (x = 0 ; x < MAX ; x++){
    main[x] = 0;
  }
}
void displaySet(SET main){
  int x;

  for (x = 0 ; x < MAX ; x++){
    if (main[x] == 1){
      printf("%d", x);
    } else {
      printf("");
    }
  }
  printf("\n");
}
void displayBits(SET main){
  int x;

  for (x = 0 ; x < MAX ; x++){
    printf("%d", main[x] == 1 ? 1 : 0);
  }
  printf("\n");
}
void insertElem(SET main, char index){
  if (index < MAX){
    main[index] = 1;
  }
}
void deleteElem(SET main, char index){
  if (index < MAX){
    main[index] = 0;
  }
}
SET* setUnion(SET A, SET B){
  SET *C = (SET*)calloc(1, sizeof(SET));
  int x;

  if (C != NULL){
    for (x = 0 ; x < MAX ; x++){
      (*C)[x] = A[x] | B[x];
    }  
  }
  return C;
}
SET* setIntersection(SET A, SET B){
  SET *C = (SET*)calloc(1, sizeof(SET));
  int x;

  if (C != NULL){
    for (x = 0 ; x < MAX ; x++){
      (*C)[x] = A[x] & B[x];
    }
  }
  return C;
}
SET* setDifference(SET A, SET B){
  SET *C = (SET*)calloc(1, sizeof(SET));
  int x;

  if (C != NULL){
    for (x = 0 ; x < MAX ; x++){
      (*C)[x] = A[x] & ~B[x];
    }
  }
  return C;
}

int main(){
  SET A = {0};
  SET B = {0};
  SET *C;

  insertElem(A, 1);
  insertElem(A, 3);
  insertElem(A, 5);
  insertElem(A, 6);

  insertElem(B, 2);
  insertElem(B, 4);
  insertElem(B, 5);
  insertElem(B, 6);

  // // SET A = {1,3,5,6}
  // // SET B = {2,4,5,6}
  // // AUB = {1,2,3,4,5,6}

  printf("SET A\n");
  displayBits(A);
  printf("SET B\n");
  displayBits(B);

  C = setUnion(A, B);
  printf("SET C\n");
  displayBits(*C);
  // displaySet(*C);

  C = setIntersection(A, B);
  printf("SET C\n");
  displayBits(*C);

  C = setDifference(A, B);
  printf("SET C\n");
  displayBits(*C);
}