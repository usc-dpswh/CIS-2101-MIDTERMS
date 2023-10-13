#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5


typedef struct {
  int rear;
  int front;
} Queue;

typedef struct {
  struct {
    int elem;
    int link;
  } NodeType[MAX];

  int avail;
} VirtualHeap;

// helper functions
int allocSpace(VirtualHeap *main){
  int space = main->avail;

  if (space != -1){
    main->avail = main->NodeType[space].link;
  }
  return space;
}
void deallocSpace(VirtualHeap *main, int index){
  if (index >= 0 && index < MAX){
    main->NodeType[index].link = main->avail;
    main->avail = index;
  }
}

// main functions
void initQ(VirtualHeap *mainVH, Queue *mainQ){
  int x;
  // init VH
  for (x = MAX-1 ; x >= 0 ; x--){
    mainVH->NodeType[x].link = x-1;
  }
  mainVH->avail = MAX-1;
  // init Q
  mainQ->front = -1;
  mainQ->rear = -1;

  printf("Initialized queue.\n");
}
void enqueue(Queue *mainQ, VirtualHeap *mainVH, int newData){
  int newNode = allocSpace(mainVH);

  if (newNode != -1){

    // if there is no element
    if (mainQ->front == -1 && mainQ->rear == -1){
      mainVH->NodeType[newNode].elem = newData;
      mainVH->NodeType[newNode].link = mainVH->avail;
      
      mainQ->front = mainQ->rear = newNode;
    // more than one element
    } else {
      mainVH->NodeType[newNode].elem = newData;
      mainVH->NodeType[newNode].link = mainVH->avail;

      mainQ->rear = newNode;
    }
  } else {
    printf("Enqueue unsuccessful.\n");
  }
}
void dequeue(Queue *mainQ, VirtualHeap *mainVH){
  if (mainQ->front == -1 && mainQ->rear == -1){
    printf("Queue underflow.\n");
  } else if (mainQ->front == mainQ->rear){
    mainQ->front = mainQ->rear = -1;
  } else {
    mainQ->front = mainVH->NodeType[mainQ->front].link;
  }
}
void display(Queue mainQ, VirtualHeap mainVH){
  for (; mainQ.front >= mainQ.rear ; mainQ.front = mainVH.NodeType[mainQ.front].link){
    printf("%d => ", mainVH.NodeType[mainQ.front].elem);
  }
  printf("-1\n");
}

int main(){
  VirtualHeap Dog;
  Queue Cat;

  initQ(&Dog, &Cat);

  dequeue(&Cat, &Dog);

  enqueue(&Cat, &Dog, 1);
  enqueue(&Cat, &Dog, 2);
  enqueue(&Cat, &Dog, 3);

  display(Cat, Dog);

  enqueue(&Cat, &Dog, 4);
  enqueue(&Cat, &Dog, 5);
  enqueue(&Cat, &Dog, 6);   // Queue unsuccessful

}