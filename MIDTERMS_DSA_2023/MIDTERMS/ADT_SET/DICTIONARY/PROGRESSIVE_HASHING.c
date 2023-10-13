#include <stdio.h>
#include <stdbool.h>
#define MAX 7
#define PACKD (int)(MAX * 0.8)
#define EMPTY -1
#define DELETED -2

typedef struct {
  int elem;
  int link;
} NodeType;

typedef struct {
  NodeType Node[MAX];
  int Avail;
} Dictionary;

// Dictionary Functions
void initDictionary(Dictionary *dict);
int getHash(int data);
bool isMember(Dictionary dict, int data);
void insertElem(Dictionary *dict, int data);
void deleteElem(Dictionary *dict, int data);

// Helper Functions
int allocSpace(Dictionary *dict);
void deallocSpace(Dictionary *dict, int index);
void displayDictionary(Dictionary dict);

int main(){
  Dictionary Webster;

  initDictionary(&Webster);

  displayDictionary(Webster);
  printf("\n");

  insertElem(&Webster, 15);
  insertElem(&Webster, 20);
  displayDictionary(Webster);

}

// Helper Functions
int allocSpace(Dictionary *dict){
  int retval = dict->Avail;

  if (retval != -1){
    dict->Avail = dict->Node[retval].link;
  }
  return retval;
}
void deallocSpace(Dictionary *dict, int index){
  if (index >= 0 && index < MAX){
    dict->Node[index].link = dict->Avail;
    dict->Avail = index;
  }
}
void displayDictionary(Dictionary dict) {
    int index;
    int trav;

    for (index = 0; index < PACKD ; index++) {
        printf("%02d[ %d | %d ] ", index, dict.Node[index].elem,
              dict.Node[index].link);

        for (trav = dict.Node[index].link; trav != -1;
            trav = dict.Node[trav].link) {
            printf("%02d[ %d | %d ] ", trav, dict.Node[trav].elem,
                  dict.Node[trav].link);
        }

        printf("\n");
    }
}

// Dictionary Functions
void initDictionary(Dictionary *dict){
  int x;
  // loop to initialize PRIME DATA AREA
  for (x = 0 ; x < PACKD ; x++){
    dict->Node[x].elem = EMPTY;
    dict->Node[x].link = -1;
  }

  // loop to initialize SYNONYM DATA AREA
  for (x = PACKD ; x < MAX ; x++){
    dict->Node[x].elem = EMPTY;
    dict->Node[x].link = x+1;
  }
  dict->Node[x].link = -1;
  dict->Avail = PACKD;
}
int getHash(int data){
  return data % PACKD;
}
bool isMember(Dictionary dict, int data){
  int index;

  for (index = getHash(data) ; dict.Node[index].elem != EMPTY && dict.Node[index].elem != data && dict.Node[index].link != -1 ; index = dict.Node[index].link){};

  // returns TRUE if elem at Node[index] is == data
  return dict.Node[index].elem == data;
}
void insertElem(Dictionary *dict, int data){
  // dont forget to always get the hash value first
  if (!isMember(*dict, data)){
    int index = getHash(data);

    // we only insert if the elem at our hash value is either EMPTY || DELETED
    if (dict->Node[index].elem == EMPTY ||
        dict->Node[index].elem == DELETED){
        dict->Node[index].elem = data;
    } else {
      // else block means that there is collision of hash value
      int newNode = allocSpace(dict);

      if (newNode != -1){
        dict->Node[newNode].elem = data;
        dict->Node[newNode].link = dict->Node[index].link;
        dict->Node[index].link = newNode;
      }
    }
  }
}
void deleteElem(Dictionary *dict, int data){
  int index = getHash(data);
  // if index at hash value is == data
  if (dict->Node[index].elem == data){
    dict->Node[index].elem = DELETED;
  } else {
    // traverse to find the element from the group
    int *trav;
    int temp;

    // traverse until we reach end OR we find the element we want to delete from dictionary
    for (trav = &(dict->Node[index].link) ; *trav != -1 && dict->Node[*trav].elem != data ; trav = &(dict->Node[*trav].link)){};

    if (*trav != -1){
      temp = *trav;
      *trav = dict->Node[temp].link;
      deallocSpace(dict, temp);
    }
  }
}

