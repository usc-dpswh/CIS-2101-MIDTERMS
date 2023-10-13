#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5

typedef struct {
  int elem[MAX];
  int top;   
} STACK;

// main functions
void init(STACK *main){
  main->top = -1;
}
void top(STACK *main){
  if (main->top != -1){
    printf("top() => %d\n", main->elem[main->top]);
  }
}
void pop(STACK *main){
  if (main->top != -1){
    printf("Popped %d successfully.\n", main->elem[main->top]);
    main->top--;
  } else {
    printf("Stack underflow.\n");
  }
}
void push(STACK *main, int newData){
  if (main->top != MAX){
    main->top++;
    main->elem[main->top] = newData;
    printf("Pushed %d successfully.\n", newData);
  } else {
    printf("Stack overflow.\n");
  }
}

void display(STACK main){
  int x;

  if (main.top != -1){
    for (x = main.top ; x >= 0 ; x--){
      printf("[%d]\n", main.elem[x]);
    }
  } else {
    printf("Stack underflow.\n");
  }
}

// helper functions
bool isFull(STACK main){
  return main.top == MAX-1;
}
bool isEmpty(STACK main){
  return main.top == -1;
}

int main(){
  STACK dishes;
  int retval;

  init(&dishes);

  retval = isEmpty(dishes);
  printf("isEmpty() => %d\n", retval);
  retval = isFull(dishes);
  printf("isFull() => %d\n", retval);

  display(dishes);

  pop(&dishes);

  push(&dishes, 1);
  push(&dishes, 2);
  push(&dishes, 3);
  push(&dishes, 4);
  push(&dishes, 5);

  top(&dishes);

  retval = isFull(dishes);
  printf("isFull() => %d\n", retval);

  display(dishes);

  pop(&dishes);
  pop(&dishes);

  display(dishes);

  pop(&dishes);
  pop(&dishes);
  pop(&dishes);
  pop(&dishes); // stack underflow

  display(dishes);  // stack underflow
}