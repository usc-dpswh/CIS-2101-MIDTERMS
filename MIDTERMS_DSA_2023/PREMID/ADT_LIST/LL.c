#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int elem;
  struct node* link;
} *LIST;

void initList(LIST *main);
void insertFirst(LIST *main, int newData);
void insertLast(LIST *main, int newData);
void isMember(LIST *main, int find);
void deleteElem(LIST *main, int delete);
void deleteAll(LIST *main);
void deleteEven(LIST *main);

int main(){
  LIST usc;
  initList(&usc);

  insertFirst(&usc, 1);
  insertFirst(&usc, 2);
  insertFirst(&usc, 3);
  insertFirst(&usc, 4);
  insertFirst(&usc, 5);
  insertFirst(&usc, 6);
  // insertLast(&usc, 4);
  // insertLast(&usc, 5);
  // insertLast(&usc, 6);
  isMember(&usc, 3);
  // deleteElem(&usc, 1);
  // deleteElem(&usc, 5);
  deleteEven(&usc);
  deleteAll(&usc);
}

void initList(LIST *main){
  *main = NULL;
}
void insertFirst(LIST *main, int newData){
  LIST newNode = (LIST)malloc(sizeof(struct node));

  if (newNode != NULL){
    newNode->elem = newData;
    newNode->link = *main;
    *main = newNode;
  }
}
void insertLast(LIST *main, int newData){
  LIST *trav;
  LIST newNode = (LIST)malloc(sizeof(struct node));

  if (newNode != NULL){
    newNode->elem = newData;
    newNode->link = NULL;
  }

  // traverse to end of list
  for (trav = main ; *trav != NULL ; trav = &(*trav)->link){};

  *trav = newNode;
}
void isMember(LIST *main, int find){
  LIST *trav;

  for (trav = main ; *trav != NULL && (*trav)->elem != find ; trav = &(*trav)->link){};

  printf("%s", *trav != NULL ? "FOUND\n" : "NOT FOUND\n");
}
void deleteElem(LIST *main, int delete){
  LIST temp;
  LIST *trav;

  for (trav = main ; *trav != NULL && (*trav)->elem != delete ; trav = &(*trav)->link){};

  if (*trav != NULL){
    temp = *trav;
    *trav = temp->link;
    free(temp);
  } else {
    printf("Not a valid element to delete.\n");
  }
}
void deleteEven(LIST *main){
  LIST *trav = NULL;
  LIST temp = NULL;

  trav = main;
  while(*trav != NULL){
    if ((*trav)->elem % 2 == 0){
      temp = *trav;
      *trav = temp->link;
      free(temp);
    } else {
      trav = &(*trav)->link;
    }
  }
}
void deleteAll(LIST *main){
  LIST trav;
  LIST temp;

  for (trav = *main ; trav != NULL ; free(temp)){
    temp = trav;
    trav = temp->link;
  }
  *main = NULL;
}
