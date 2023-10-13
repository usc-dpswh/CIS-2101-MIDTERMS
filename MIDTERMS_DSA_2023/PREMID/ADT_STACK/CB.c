#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5

// typedef struct {
//   int index;
//   int link;
// } NodeType;

// typedef struct {
//   NodeType A[MAX];
//   int Avail;
// } VirtualHeap;

typedef struct {

  struct {
    int elem;
    int link;
  } NodeType[MAX];
  int Avail;
} VirtualHeap;

// helper functions
int allocSpace(VirtualHeap *main){
  int space = main->Avail;

  if (space != -1){
    main->Avail = main->NodeType[space].link;
    return space;
  }
}
void deallocSpace(VirtualHeap *main, int index){
  if (index >= 0 && index < MAX){
    main->NodeType[index].link = main->Avail;
    main->Avail = index;
  }
}
bool isEmpty(int top){
  return top == -1;
}
// bool isFull(int top){
//   return top == 0;
// }

// main functions
void init(VirtualHeap *main, int *top){
  int x;

  for (x = -1 ; x < MAX ; x++){
    main->NodeType[x+1].link = x; 
  }
  main->Avail = MAX-1;
  *top = -1;
}
void push(int *top, VirtualHeap *main, int newData){
  int newNode = allocSpace(main);

  if (newNode != -1){
    main->NodeType[newNode].elem = newData;
    main->NodeType[newNode].link = *top;
    *top = newNode;
    printf("Pushed %d\n", newData);
  } else {
    printf("Stack overflow\n");
  }
}
void pop(int *top, VirtualHeap *main){
  int temp;
  if (!isEmpty(*top)){
    printf("Popped %d\n", main->NodeType[*top].elem);
    temp = *top;
    *top = main->NodeType[temp].link;
    deallocSpace(main, temp);
  } else {
    printf("Stack underflow.\n");
  }
}
void display(int head, VirtualHeap main){
  if (head != -1){
    for (; head != -1 ; head = main.NodeType[head].link){
      printf("[%d]\n", main.NodeType[head].elem);
    }
  } else {
    printf("Stack underflow.\n");
  }
}
void peek(int top, VirtualHeap main){
  if (top != -1){
    printf("top() => %d\n", main.NodeType[top].elem);
  } else {
    printf("Stack underflow.\n");
  }
}
void makeNull(VirtualHeap *main);

int main(){
  VirtualHeap Otin;
  int top;

  init(&Otin, &top);

  push(&top, &Otin, 1);
  push(&top, &Otin, 2);
  push(&top, &Otin, 3);

  display(top, Otin);

  pop(&top, &Otin);

  display(top, Otin);

  peek(top, Otin);

  pop(&top, &Otin);
  pop(&top, &Otin);
  pop(&top, &Otin);     // stack underflow

  display(top, Otin);   // stack underflow

  push(&top, &Otin, 1);
  push(&top, &Otin, 2);
  push(&top, &Otin, 3);
  push(&top, &Otin, 4);
  push(&top, &Otin, 5);
  push(&top, &Otin, 6); // stack overflow
}