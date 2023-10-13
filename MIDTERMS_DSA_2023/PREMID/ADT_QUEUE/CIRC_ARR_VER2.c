#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 8

typedef struct {
  int elem[MAX];
  int front;
  int rear;
} QUEUE;

// helper functions
bool isEmpty(QUEUE main){
  return (main.rear + 1) % MAX == main.front;
}
bool isFull(QUEUE main){
  return (main.rear + 2) % MAX == main.front;
}

// main functions
void initQueue(QUEUE *main){
  main->rear = 3;
  main->front = 4;
  printf("Initialized queue.\n");
}
void enqueue(QUEUE *main, char newData){
  if (!isFull(*main)){
    main->rear = (main->rear + 1) % MAX;
    main->elem[main->rear] = newData;
  } else {
    printf("Queue overflow.\n");
  }
}
void dequeue(QUEUE *main){
  if (!isEmpty(*main)){
    main->front = (main->front + 1) % MAX;
  } else {
    printf("Queue underflow.\n");
  }
}
void displayQueue(QUEUE main){
  int x;

  for (x = main.front ; x != main.rear ; x = (x + 1) % MAX){
    printf("%d => ", main.elem[x]);
  }
  printf("%d => NULL\n", main.elem[x]);
}

int main(){
  QUEUE Dianne;
  
  initQueue(&Dianne);

  enqueue(&Dianne, 1);
  enqueue(&Dianne, 2);
  enqueue(&Dianne, 3);
  enqueue(&Dianne, 4);
  enqueue(&Dianne, 5);
  enqueue(&Dianne, 6);
  enqueue(&Dianne, 7);
  enqueue(&Dianne, 8);    // queue overflow
  enqueue(&Dianne, 9);    // queue overflow

  displayQueue(Dianne);
}