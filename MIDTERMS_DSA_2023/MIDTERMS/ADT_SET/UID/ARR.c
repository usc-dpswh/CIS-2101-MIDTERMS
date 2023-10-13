#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 5

typedef struct {
  int *elem;
  int count;
} SET;

void init(SET* main){
  main->elem = (int*)calloc(1, sizeof(int) * MAX);
  if (main->elem != NULL){
    printf("Successfully initialized SET.\n");
  }
  main->count = 0;
}
SET setUnion(SET A, SET B){
  SET C;
  init(&C);
  int A_INDEX = 0;
  int B_INDEX = 0;
  int C_INDEX = 0;

  while (A_INDEX < A.count || B_INDEX < B.count){

    // if SET C is full and SET A or B still has elements to be copied
    if (C.count == MAX && (A_INDEX < A.count || B_INDEX < B.count)){
      C.elem = (int*)realloc(C.elem, sizeof(int) * (MAX * 2));
    }

    // if we have copied all elements from SET A, copy SET B elements instead
    if (A_INDEX == A.count && B_INDEX < B.count){
      C.elem[C_INDEX] = B.elem[B_INDEX];
      B_INDEX++;
      C_INDEX++;
      C.count++;

    // if we have copied all elements from SET B, copy SET A elements instead
    } else if (B_INDEX == B.count && A_INDEX < A.count){
      C.elem[C_INDEX] = A.elem[C_INDEX];
      A_INDEX++;
      C_INDEX++;
      C.count++;

    // if A < B, copy A
    } else if (A.elem[A_INDEX] < B.elem[B_INDEX]){
      C.elem[C_INDEX] = A.elem[A_INDEX];
      A_INDEX++;
      C_INDEX++;
      C.count++;

    // if B < A, copy B
    } else if (B.elem[B_INDEX] < A.elem[A_INDEX]){
      C.elem[C_INDEX] = B.elem[B_INDEX];
      B_INDEX++;
      C_INDEX++;
      C.count++;

    // if A == B, copy either
    } else {
      C.elem[C_INDEX] = A.elem[A_INDEX];
      A_INDEX++;
      B_INDEX++;
      C_INDEX++;
      C.count++;
    }
  }
  return C;
}
SET intersection(SET A, SET B){
  SET C;
  init(&C);
  int A_INDEX = 0;
  int B_INDEX = 0;
  int C_INDEX = 0;

  while (A_INDEX < A.count || B_INDEX < B.count){
    // A < B, move A
    if (A.elem[A_INDEX] < B.elem[B_INDEX]){
      A_INDEX++;
    } else if (B.elem[B_INDEX] < A.elem[A_INDEX]){
      B_INDEX++;
    } else {
      C.elem[C_INDEX] = A.elem[A_INDEX];
      C.count++;

      A_INDEX++;
      B_INDEX++;
      C_INDEX++;
    }
  }
  return C;
}
SET difference(SET A, SET B){
  SET C;
  init(&C);
  int A_INDEX = 0;
  int B_INDEX = 0;
  int C_INDEX = 0;

  while (A_INDEX < A.count && B_INDEX < B.count){
    if (A.elem[A_INDEX] < B.elem[B_INDEX]){
      C.elem[C_INDEX] = A.elem[A_INDEX];
      C.count++;
      A_INDEX++;
      C_INDEX++;
    } else if (B.elem[B_INDEX] < A.elem[A_INDEX]){
      B_INDEX++;
    } else {
      A_INDEX++;
      B_INDEX++;
    }
  }
  return C;
}
void display(SET A){
  int x;

  printf("{ ");
  for (x = 0 ; x < A.count ; x++){
    printf("%d ", A.elem[x]);
  }
  printf("}\n");
}

int main(){
  SET A;
  SET B;
  SET C;

  init(&A);
  init(&B);
  init(&C);

  A.elem[0] = 1;    B.elem[0] = 2;
  A.elem[1] = 3;    B.elem[1] = 3;
  A.elem[2] = 6;    B.elem[2] = 8;
  A.elem[3] = 8;    B.elem[3] = 9;

  A.count = 4;
  B.count = 4;

  C = setUnion(A, B);
  display(C);

  C = intersection(A, B);
  display(C);

  C = difference(A, B);
  display(C);
}