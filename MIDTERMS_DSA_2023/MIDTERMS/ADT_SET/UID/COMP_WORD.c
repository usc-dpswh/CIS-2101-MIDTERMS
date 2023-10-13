#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char SET;

void insertElem(SET *main, unsigned char elem){
  *main = *main | 1 << elem;
}
void deleteElem(SET *main, unsigned char elem){
  *main = *main & ~(1 << elem);
}
bool isMember(SET main, unsigned char elem){
  return main & (1 << elem);
}
SET setUnion(SET A, SET B){
  return A | B;
}
SET setIntersection(SET A, SET B){
  return A & B;
}
SET setDifference(SET A, SET B){
  return A & ~B;
}
void displayBitPattern(SET main){
  int mask;

  for (mask = 1 << sizeof(SET) * 8 - 1 ; mask != 0 ; mask = mask >> 1){
    printf("%d", main & mask ? 1 : 0);
  }
  printf("\n");
}
void displayElem(SET main){
  int mask = 1 << sizeof(SET) * 8 - 1;
  int counter;

  printf("{ ");
  for (counter = sizeof(SET) * 8 - 1 ; counter != 0 ; counter--){
    printf("%d ", (mask & main) ? counter : 0);
  }
  printf("}\n");
}

int main(){
  SET A = 36;
  displayBitPattern(A);
  displayElem(A);
  
  
}