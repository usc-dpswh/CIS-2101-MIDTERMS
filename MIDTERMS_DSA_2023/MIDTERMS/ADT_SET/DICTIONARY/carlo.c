#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 15
#define PACKING_DENSITY (int)(MAX_SIZE * 0.8)
#define EMPTY -69
#define DELETED -420

typedef struct {
    int elem;
    int link;
} Node;

typedef struct {
    Node nodes[MAX_SIZE];
    int avail;
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

int main(void) {
    Dictionary dict;

    initDictionary(&dict);
    insertElem(&dict, 1);
    insertElem(&dict, 13);
    insertElem(&dict, 25);
    displayDictionary(dict);
    deleteElem(&dict, 25);
    displayDictionary(dict);
    return 0;
}

void initDictionary(Dictionary *dict) {
    int index;

    for (index = 0; index < PACKING_DENSITY; index++) {
        dict->nodes[index].elem = EMPTY;
        dict->nodes[index].link = -1;
    }

    for (index = PACKING_DENSITY; index < MAX_SIZE - 1; index++) {
        dict->nodes[index].link = index + 1;
    }

    dict->nodes[index].link = -1;
    dict->avail = PACKING_DENSITY;
}

int getHash(int data) { return data % PACKING_DENSITY; }

bool isMember(Dictionary dict, int data) {
    int index = getHash(data);

    while (dict.nodes[index].elem != EMPTY && dict.nodes[index].elem != data &&
          dict.nodes[index].link != -1) {
        index = dict.nodes[index].link;
    }

    return (dict.nodes[index].elem == data);
}

void insertElem(Dictionary *dict, int data) {
    if (!isMember(*dict, data)) {
        int index = getHash(data);

        if (dict->nodes[index].elem == EMPTY ||
            dict->nodes[index].elem == DELETED) {
            dict->nodes[index].elem = data;
        } else {
            int node = allocSpace(dict);

            if (node != -1) {
                dict->nodes[node].elem = data;
                dict->nodes[node].link = dict->nodes[index].link;
                dict->nodes[index].link = node;
            }
        }
    }
}

void deleteElem(Dictionary *dict, int data) {
    int index = getHash(data);

    if (dict->nodes[index].elem == data) {
        dict->nodes[index].elem = DELETED;
    } else {
        int *trav = &dict->nodes[index].link;

        while (*trav != -1 && dict->nodes[*trav].elem != data) {
            trav = &dict->nodes[*trav].link;
        }

        if (*trav != -1) {
            int temp = *trav;
            *trav = dict->nodes[*trav].link;
            deallocSpace(dict, temp);
        }
    }
}

int allocSpace(Dictionary *dict) {
    int space = dict->avail;

    if (space != -1) {
        dict->avail = dict->nodes[space].link;
    }

    return space;
}

void deallocSpace(Dictionary *dict, int index) {
    if (index > -1 && index < MAX_SIZE) {
        dict->nodes[index].link = dict->avail;
        dict->avail = index;
    }
}

void displayDictionary(Dictionary dict) {
    int index;
    int trav;

    for (index = 0; index < PACKING_DENSITY; index++) {
        printf("%03d[ %03d | %03d ] ", index, dict.nodes[index].elem,
              dict.nodes[index].link);

        for (trav = dict.nodes[index].link; trav != -1;
            trav = dict.nodes[trav].link) {
            printf("%03d[ %03d | %03d ] ", trav, dict.nodes[trav].elem,
                  dict.nodes[trav].link);
        }

        printf("\n");
    }
}