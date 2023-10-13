#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 8

typedef struct {
  int elem[MAX];
  int front;
  int rear;
  int count;
} QUEUE;

// helper functions
bool isEmpty(QUEUE main){
  return main.count == 0;
}
bool isFull(QUEUE main){
  return main.count == MAX;
}

// main functions
void initQueue(QUEUE *main){
  main->count = 0;
  main->rear = 3;
  main->front = 4;
  printf("Initialized queue.\n");
}
void enqueue(QUEUE *main, char newData){
  if (!isFull(*main)){
    main->rear = (main->rear + 1) % MAX;
    main->elem[main->rear] = newData;
    main->count++;
    printf("enqueue() successful\n");
  } else {
    printf("Queue overflow.\n");
  }
}
void dequeue(QUEUE *main){
  if (!isEmpty(*main)){
    main->front = (main->front + 1) % MAX;
    main->count--;
    printf("dequeue() successful\n");
  } else {
    printf("Queue underflow.\n");
  }
}
void displayQueue(QUEUE main){
  int x;
  if (!isEmpty(main)){
    for (x = main.front ; x != main.rear ; x = (x+1) % MAX){
      printf("%d => ", main.elem[x]);
    }
    printf("%d => NULL\n", main.elem[x]);
  }
}

int main(){
  QUEUE Chowking;

  initQueue(&Chowking);

  displayQueue(Chowking);

  enqueue(&Chowking, 1);
  enqueue(&Chowking, 2);
  enqueue(&Chowking, 3);
  enqueue(&Chowking, 4);
  enqueue(&Chowking, 5);
  enqueue(&Chowking, 6);
  enqueue(&Chowking, 7);
  enqueue(&Chowking, 8);
  enqueue(&Chowking, 9);    // queue overflow

  displayQueue(Chowking);

}