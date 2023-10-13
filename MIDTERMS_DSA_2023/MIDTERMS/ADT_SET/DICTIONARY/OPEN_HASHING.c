#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define MAX 26

typedef struct node {
  char *elem;
  struct node* link;
} *LIST;

typedef LIST Dictionary[MAX];

// Function Prototypes
void init(Dictionary main);
int Hash(char data);
void insertElem(Dictionary main, char *newData);
void deleteElem(Dictionary main, char *deleteThis);
bool isMember(Dictionary main, char *data);
void displayDictionary(Dictionary main);

int main(){
  Dictionary German;

  init(German);

  insertElem(German, "Dog");
  insertElem(German, "Indian");
  insertElem(German, "Ant");
  insertElem(German, "Nigga");
  insertElem(German, "Nice");
  insertElem(German, "Enzo");

  // insertElem(German, 'B');
  // insertElem(German, 'C');
  // insertElem(German, 'Z');
  
  // displayDictionary(German);

  // deleteElem(German, 'A');

  displayDictionary(German);

}

void init(Dictionary main){
  int x;

  for (x = 0 ; x < MAX ; x++){
    main[x] = NULL;
  }
}
int Hash(char data){
  return toupper(data)-'A';
}
bool isMember(Dictionary main, char *data){
  LIST trav;
  int index = Hash(*data);

  for (trav = main[index] ; trav != NULL && strcmp(trav->elem, data) != 0 ; trav = trav->link){};

  return trav != NULL;
}
void insertElem(Dictionary main, char *newData){
  int index = Hash(newData[0]);

  // we must first check if its unique using isMember
  if (!isMember(main, newData)){
    LIST newNode = (LIST)malloc(sizeof(struct node));

    // perform insert first
    if (newNode != NULL){
      newNode->elem = newData;
      newNode->link = main[index];
      main[index] = newNode;
    }
  }
}
void deleteElem(Dictionary main, char *deleteThis){
  LIST *trav;
  LIST temp;
  int index = Hash(*deleteThis);

  if (main[index] == NULL){
    printf("That element does not exist.\n");
  } else {
    for (trav = &main[index] ; *trav != NULL && strcmp((*trav)->elem, deleteThis) != 0 ; trav = &(*trav)->link){};

    if (*trav != NULL){
      temp = *trav;
      *trav = temp->link;
      free(temp);
    }
  }
}
void displayDictionary(Dictionary main){
  int group;
  LIST trav;

  for (group = 0 ; group < MAX ; group++){
    printf("%02d | ", group);
    for (trav = main[group] ; trav != NULL ; trav = trav->link){
      printf("%s => ", trav->elem);
    }
    printf("\n");
  }
  printf("\n");
}

