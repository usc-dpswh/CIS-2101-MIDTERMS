#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct {
  int elem;
  int link;
} NodeType;

typedef struct node {
  NodeType Nodes[MAX];
  int Avail;
} *VirtualHeap;

void initHeap(int *head, VirtualHeap *main){
  *main = (VirtualHeap)malloc(sizeof(struct node));
  int x;

  if (main != NULL){
    for (x = -1 ; x < MAX-1 ; x++){
      (*main)->Nodes[x+1].link = x;
    }
    (*main)->Avail = MAX-1;
    *head = -1;
  }
}
void display(VirtualHeap main, int head){
  for (; head != -1 ; head = main->Nodes[head].link){
    printf("%d => ", main->Nodes[head].elem);
  }
  printf("-1\n");
}
int allocSpace(VirtualHeap *main){
  int space = (*main)->Avail;

  if ((*main)->Avail != -1){
    (*main)->Avail = (*main)->Nodes[space].link;
    return space;
  }
}
void deallocSpace(VirtualHeap *main, int index){
  if (index >= 0 && index < MAX){
    (*main)->Nodes[index].link = (*main)->Avail;
    (*main)->Avail = index;
  }
}
void insertFirstVH(int *head, VirtualHeap *main, int newData){
  if ((*main)->Avail != -1){
    int newNode = allocSpace(main);

    if (newNode != -1){
      (*main)->Nodes[newNode].elem = newData;
      (*main)->Nodes[newNode].link = *head;
      *head = newNode;
      printf("Inserted %d successfully.\n", newData);
    }
  } else {
    printf("Full.\n"); 
  }
}
void deleteElem(int *head, VirtualHeap *main, int delete){
  int *trav;
  int temp;

  for (trav = head ; *trav != -1 && (*main)->Nodes[*trav].elem != delete ; trav = &(*main)->Nodes[*trav].link){};

  if (*trav != -1){
    temp = *trav;
    *trav = (*main)->Nodes[temp].link;
    deallocSpace(main, temp);

    printf("Deleted %d successfully.\n", delete);
  } else {
    printf("That is not a valid element to delete.\n");
  }
}
void displayAvail(VirtualHeap main){
  int trav;

  for (trav = main->Avail ; trav != -1 ; trav = main->Nodes[trav].link){
    printf("%d => ", main->Nodes[trav].elem);
  }
  printf("-1\n");
}

int main(){
  VirtualHeap Dianne;
  int head;

  initHeap(&head ,&Dianne);

  insertFirstVH(&head, &Dianne, 1);
  insertFirstVH(&head, &Dianne, 2);
  insertFirstVH(&head, &Dianne, 3);
  insertFirstVH(&head, &Dianne, 4);
  insertFirstVH(&head, &Dianne, 5);
  insertFirstVH(&head, &Dianne, 6);

  display(Dianne, head);
  
  deleteElem(&head, &Dianne, 2);
  deleteElem(&head, &Dianne, 1);

  display(Dianne, head);

  displayAvail(Dianne);
}