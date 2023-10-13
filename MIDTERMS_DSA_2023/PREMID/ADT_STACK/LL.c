#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
  int elem;
  struct node* link;
} *Node;

typedef struct stack {
  Node top;
} STACK;

// helper functions
// bool isFull(STACK main){}
bool isEmpty(STACK main){
  return main.top == NULL;
}

// main functions
void init(STACK *main){
  main->top = NULL;
}
void top(STACK main){
  if (main.top != NULL){
    printf("top() => %d\n", main.top->elem);
  }
}
void pop(STACK *main){
  printf("pop()\n");
  Node temp;
  if (!isEmpty(*main)){
    temp = main->top;
    main->top = temp->link;
    free(temp);
  }
}
void push(STACK *main, int newData){
  Node newNode = (Node)malloc(sizeof(struct node));

  if (newNode != NULL){
    newNode->elem = newData;
    newNode->link = main->top;
    main->top = newNode;
    printf("Inserted %d\n", main->top->elem);
  }
}
void display(STACK main){
  Node trav;

  if (!isEmpty(main)){
    for (trav = main.top ; trav != NULL ; trav = trav->link){
      printf("[%d]\n", trav->elem);
    }
    printf("\n");
  } else {
    printf("Stack underflow.\n");
  }
}

int main(){
  STACK dishes;

  init(&dishes);

  push(&dishes, 1);
  push(&dishes, 2);
  push(&dishes, 3);
  push(&dishes, 4);

  display(dishes);

  top(dishes);

  pop(&dishes);
  pop(&dishes);
  pop(&dishes);

  display(dishes);

  pop(&dishes);
  pop(&dishes); // stack underflow

  display(dishes);
}