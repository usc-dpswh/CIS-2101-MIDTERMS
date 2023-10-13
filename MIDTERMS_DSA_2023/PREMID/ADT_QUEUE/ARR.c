#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5

typedef struct {
  int elem[MAX];
  int front;
  int rear;
} QUEUE;


// helper functions
bool isEmpty(QUEUE main){
  return main.front == -1 && main.rear == -1;
}
bool isFull(QUEUE main){
  return main.rear == MAX-1;
}

QUEUE init(){
  QUEUE newLine;

  newLine.rear = -1;
  newLine.front = -1;
  printf("Initialized queue.\n");

  return newLine;
}
void enqueue(QUEUE *main, int newData){
  if (isEmpty(*main)){
    main->front++;
    main->rear++;
    main->elem[main->rear] = newData;
    printf("Enqueue %d successful\n", newData);
  } else if (main->rear < MAX-1){
    main->rear++;
    main->elem[main->rear] = newData;
    printf("Enqueue %d successful\n", newData);
  } else {
    printf("Queue overflow.\n");
  }
}
void dequeue(QUEUE *main){
  if (isEmpty(*main)){
    printf("Queue underflow.\n");
  } else if (main->front == main->rear){
    printf("dequeue(%d)\n", main->elem[main->front]);
    main->front = main->rear = -1;
  } else {
    printf("dequeue(%d)\n", main->elem[main->front]);
    main->front++;
  }
}
void peek(QUEUE main){
  if (!isEmpty(main)){
    printf("peek(%d)\n", main.elem[main.rear]);
  }
}
void display(QUEUE main){
  if (!isEmpty(main)){
    for (; main.front <= main.rear ; main.front++){
      printf("[%d] => ", main.elem[main.front]);
    }
    printf("NULL\n");
  } else {
    printf("Queue underflow.\n");
  }
}

int main(){
  QUEUE Chowking = init();

  enqueue(&Chowking, 1);
  enqueue(&Chowking, 2);
  enqueue(&Chowking, 3);

  display(Chowking);

  dequeue(&Chowking);

  display(Chowking);

  dequeue(&Chowking);
  dequeue(&Chowking);
  dequeue(&Chowking);     // queue underflow

  display(Chowking);      // queue underflow

  enqueue(&Chowking, 1);
  enqueue(&Chowking, 2);
  enqueue(&Chowking, 3);
  enqueue(&Chowking, 4);
  enqueue(&Chowking, 5);
  enqueue(&Chowking, 6);  // queue overflow

  peek(Chowking);
}