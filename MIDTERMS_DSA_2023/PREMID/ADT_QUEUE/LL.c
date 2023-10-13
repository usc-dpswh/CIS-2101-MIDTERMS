#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
  int elem;
  struct node* link;
} *Node;

typedef struct queue {
  Node rear;
  Node front;
} QUEUE;

// helper functions
bool isEmpty();

// main functions
QUEUE init(){
  QUEUE newLine;

  newLine.rear = NULL;
  newLine.front = NULL;
  printf("Initialized queue.\n");

  return newLine;
}
void enqueue(QUEUE *main, int newData){
  Node newNode = (Node)malloc(sizeof(struct node));

  if (newNode != NULL){
    newNode->elem = newData;
    newNode->link = NULL;
  }

  if (main->front == NULL && main->rear == NULL){
    main->front = main->rear = newNode;
    printf("Enqueue %d successful.\n", newData);
  } else {
    main->rear->link = newNode;
    main->rear = newNode;
    printf("Enqueue %d successful.\n", newData);
  }
}
void dequeue(QUEUE *main){
  Node temp;
  if (main->front == NULL && main->rear == NULL){
    printf("Queue underflow.\n");
    
  } else if (main->front == main->rear){
    printf("Dequeue %d successful.\n", main->front->elem);
    free(main->front);
    main->front = main->rear = NULL;
  } else {
    printf("Dequeue %d successful.\n", main->front->elem);
    temp = main->front;
    main->front = temp->link;
    free(temp);
  }
}
void peek(QUEUE main){
  if (main.front != NULL && main.rear != NULL){
    printf("peek(%d)\n", main.rear->elem);
  }
}
void front(QUEUE main){
  if (main.front != NULL && main.rear != NULL){
    printf("front(%d)\n", main.front->elem);
  }
}
void display(QUEUE main){
  if (main.front != NULL){
    Node trav;
    for (trav = main.front ; trav != NULL ; trav = trav->link){
      printf("%d => ", trav->elem);
    }
    printf("NULL\n");
  }
}

int main(){
  QUEUE SnG = init();

  enqueue(&SnG, 1);
  enqueue(&SnG, 2);
  enqueue(&SnG, 3);

  peek(SnG);
  front(SnG);

  display(SnG);

  dequeue(&SnG);

  display(SnG);

  dequeue(&SnG);
  dequeue(&SnG);
  dequeue(&SnG);    // queue underflow
}