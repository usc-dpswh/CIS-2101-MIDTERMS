/******************************************************************
 * Project Name:  List, Set and Dictionary                        *
 * Programmer  :  Put your Name here                              *
 * Date Completed: March 25, 2023                                 *
 ******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VH_SIZE     0XC    //size of Virtual Heap
#define OPEN_DSIZE  0XA    //size of Open Hash Table
#define CLOSE_DSIZE 0XC    //size of Close Hash Table
#define LIST_SIZE   0XF    //size of the array implementation of List
/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct {  
	char name[24];          	// Chocolate name  
 	int  weight;            	// Chocolate weight in grams  
}chocoDesc;

typedef struct {
	char prodID[8];          	//  product ID uniquely identifies the products; EMPTY or DELETED   
	chocoDesc prodDesc;     	//  product description 
	float prodPrice;        	//  product price 
	int prodQty;            	//  product count or quantity   
}product;                   //  product record  

typedef struct {
	product elem;            
	int next;                
}prodNode;                 	// Product node, used in cursor-based implementation of Set  


/************************
 * Virtual Heap         *
 ************************/
typedef struct {
	prodNode VH_node[VH_SIZE];
	int avail;
}VHeap;

/******************************************
 * Cursor-Based Implementation of SET     *
 ******************************************/
typedef struct {
   int elemIndex;        	// index of the 1st element in the set  
   int count;            	// holds the actual number of elements in the set  
   VHeap *VHptr;         	// holds the pointer to the virtual heap  
}cursorSet;            

/********************************************
 * Open Hashing Implementation of Dictionary*
 ********************************************/
typedef struct {
	int header[OPEN_DSIZE];  // array of sets   
	int count;               // total number of elements in the dictionary  
	VHeap *dicVHptr;         // holds the pointer to the virtual heap  
}openDic;


/**********************************************
 * Closed Hashing with 2 pass loading          *
 **********************************************/
#define EMPTY   "empty"     // stored in product ID field  
#define DELETED  "del"      // stored in product ID field * 

typedef product closeDic[CLOSE_DSIZE];   //Definition of the closed hash dictionary
  
typedef struct {
	product prod[LIST_SIZE];
	int last;   //index of the last element; -1 if list is empty	
}List;



/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
//---Problem #1 ---
void initVHeap(VHeap *VH);
cursorSet initCursorSet(VHeap *VH);
void displayVHeap(VHeap V);
void displaySet(cursorSet A);
// Needs the VHeap variable to initialize the virtual heap itself
// Needs the cursorSet variable to initialize the SET using cursor based implementation

//---Problem #2 ---
int mallocInVHeap(VHeap *VH);
void insertSorted(cursorSet *A, product P);
void populateSet(cursorSet *A);

//---Problem #3 ---
int openHash(char *IDen);                
openDic initOpenDict(VHeap *VH);
openDic convertToOpenDict(cursorSet *A);
void displayOpenDict(openDic D);

//---Problem #4 ---
void freeInVHeap(VHeap *VH, int ndx);
void deleteDict(openDic *D, char *IDen);

//---Problem #5 ---
int closeHash(char *ID);
void initCloseDict(closeDic CD);
closeDic * convertToCloseDict(openDic *D);	
void displayCloseDict(closeDic CD);



/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *                                                                                  *
 ***********************************************************************************/
int main( ) 
{	
/*---------------------------------------------------------------------------------
 * 	Problem #1 ::  1) Initializes the virtual heap and the cursor Set             *
 *                 2) Displays the contents  virtual heap and cursor Set          *
 *--------------------------------------------------------------------------------*/
printf("\n\n\nProblem #1:: "); 
printf("\n------------");
 	//Declare variables needed for Problem #1
	VHeap Container;
	cursorSet SET_A;

 	//Function Calls for Problem #1
	initVHeap(&Container);
	SET_A = initCursorSet(&Container);
	displayVHeap(Container);

/*---------------------------------------------------------------------------------
 * 	Problem #2 ::  1) Populates the Cursor set which is sorted in ascending order *
 *                    according to ID                                             *
 *                 2) Displays the Cursor set                                     * 
 *--------------------------------------------------------------------------------*/	 
	printf("\n\n\nProblem #2:: "); 
	printf("\n------------\n");
	
	populateSet(&SET_A);
	displaySet(SET_A);
	
// printf("Returned Value is %d", returnedValue);
 	//Function Calls for Problem #2

/*---------------------------------------------------------------------------------
 * 	Problem #3 ::  1) Converts the Cursor set into an Open Hash Dictionary        *      
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the empty Cursor set.                              * 
 *--------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #3:: "); 
	printf("\n------------");
	//Declare variables needed for Problem #3
	openDic B;
	
 	//Function Calls for Problem #3
	B = convertToOpenDict(&SET_A);
	displayOpenDict(B);
	displaySet(SET_A);

/*---------------------------------------------------------------------------------
 * 	Problem #4 ::  1) Perform 3 delete operations on the Open Hash Dictionary     *
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the Virtual Heap                                   * 
 *--------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #4:: "); 
	printf("\n------------");	
 //Declare variables needed for Problem #4
	

//Function Calls for Problem #4	    
    
    

/*------------------------------------------------------------------------------------
 * 	Problem #5 :: 1) Converts the Open Hash Dictionary into a Closed Hash Dictionary *
 *                2) Displays the Closed Hash Dictionary                             * 
 *                3) Displays the virtual heap                                       *
 *---------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #5:: ");
	printf("\n------------");
	//Declare variables needed for Problem #5
	
	
	//Function Calls for Problem #5

	

	return 0;
}

/************************************************************
 *  Problem 1:: Function Definitions                          *
 ************************************************************/
void initVHeap(VHeap *V) {
    int index;

    for (index = VH_SIZE - 1; index >= 0; index--) {
        strcpy(V->VH_node[index].elem.prodID, "    ");
        V->VH_node[index].next = index - 1;
    }

    V->avail = VH_SIZE - 1;
}

cursorSet initCursorSet(VHeap *VH)
{
	return (cursorSet){-1,0,VH};
}

void displayVHeap(VHeap V)
{
	//Variable Declaration here
	int i,j;

	printf("\n\nDetails of the Virtual Heap :: ");
	printf("\n------------------------------");
	printf("\nAvailable Index  ::  %d", V.avail);       		//Complete this statement
	printf("\nVHeap Address    ::  %d" , &V.VH_node);       	//Complete this statemet
	
	printf("\n\n%10s", "Index");
	printf("%10s", "Prod ID");
	printf("%15s", "Next Field");
	printf("\n%10s%10s%15s", "-----", "-------","----------");	
  
	//Write your code here 
	for (i = 0 ; i < VH_SIZE ; i++){
		printf("\n%10d%10s%15d",
			i,
			V.VH_node[i].elem.prodID,
			V.VH_node[i].next);
	}
	
	
	// printf("\n\n"); system("Pause");
	
}

void displaySet(cursorSet A)
{
	int x;
	product p;
	
	printf("\n\nDetails of the Set :: ");
	printf("\n---------------------");
	printf("\nNo. of elements ::  %d", A.count );      //Complete this code
	printf("\n\n%-7s", "ID");
	printf("%-12s","Choco Name");
	printf("%-15s","Choco Weight");
	printf("%-10s","VHeap Index");
	printf("\n%-7s%-12s%-15s%-10s", "--", "----------", "------------", "-----------");

	//Write your code here
	for (x = A.elemIndex ; x < A.count && x != -1 ; x = A.VHptr->VH_node[x].next){
		printf("\n%-7s%-12s%-15d%-10d", 
			A.VHptr->VH_node[x].elem.prodID,
			A.VHptr->VH_node[x].elem.prodDesc.name,
			A.VHptr->VH_node[x].elem.prodDesc.weight,
			x);
	}

	// printf("\n\n"); system("Pause");	
}


/************************************************************
 *  Problem 2:: Function Definitions                         *
 ************************************************************/
int mallocInVHeap(VHeap *VH)
{
	int space = VH->avail;

	if (space != -1){
		VH->avail = VH->VH_node[space].next;
	}
	return space;
}


void insertSorted(cursorSet *A, product P)
{
	int trav;
	
	// Check if ID already exists, essentially our isMember() since this is SET
	for (trav = A->elemIndex ; trav != -1 && strcmp(A->VHptr->VH_node[trav].elem.prodID, P.prodID) != 0 ; trav = A->VHptr->VH_node[trav].next){};

	if (trav != -1){
		printf("Product with ID [%s] already exists!\n", P.prodID);
	} else {
		// If ID is unique, continue insertSorted
		int *trav;
		
		for (trav = &A->elemIndex ; *trav != -1 && strcmp(A->VHptr->VH_node[*trav].elem.prodID, P.prodID) < 0 ; trav = &A->VHptr->VH_node[*trav].next){};

		int newNode = mallocInVHeap(A->VHptr);

		if (newNode != -1){
			A->count++;
			A->VHptr->VH_node[newNode].elem = P;
			A->VHptr->VH_node[newNode].next = *trav;
			*trav = newNode;
		}
	}
}


void populateSet(cursorSet *A)
{
	const int COUNT = 15;
	product data[] = {
        {"1701", {"Toblerone", 135}, 150.75, 20},
        {"1356", {"Ferrero", 200}, 250.75, 85},
        {"1109", {"Patchi", 50}, 99.75, 35},
        {"1550", {"Cadbury", 120}, 200.00, 30},
        {"1807", {"Mars", 100}, 150.75, 20},
        {"1201", {"Kitkat", 50}, 97.75, 40},
        {"1450", {"Ferrero", 100}, 150.50, 50},
        {"1701", {"Toblerone", 50}, 90.75, 80},
        {"1601", {"Meiji", 75}, 75.50, 60},
        {"1310", {"Nestle", 100}, 124.50, 70},
        {"1807", {"Valor", 120}, 149.50, 90},
        {"1455", {"Tango", 75}, 49.50, 100},
        {"1703", {"Toblerone", 100}, 125.75, 60},
        {"1284", {"Lindt", 100}, 250.75, 15},
        {"1688", {"Guylian", 50}, 99.75, 35},
    };
    //Inserts each element of the array to the cursor set
    //Write your code here!!
	
	// Loop to insert each element of the data[] array to the cursorSet pointing to the VHeap (since CursorSet shares VH)
	int size = sizeof(data) / sizeof(data[0]);
	int x;

	for (x = 0 ; x < size ; x++){
		insertSorted(A, data[x]);
	}
	printf("Populated cursorSet\n");
}



/************************************************************
 *  Problem 3:: Function Definitions                        *
 ************************************************************/
int openHash(char *prodID) {
    int x, val = 0;
    for (x = 0; prodID[x] != '\0'; x++) {
        val += prodID[x] - '0';
    }
    return val % OPEN_DSIZE;
}


openDic initOpenDict(VHeap *VH)
{
	openDic newDic;
	int x;

	for (x = 0 ; x < OPEN_DSIZE ; x++){
		newDic.header[x] = -1;
	}
	newDic.dicVHptr = VH;
	newDic.count = 0;

	return newDic;
}

openDic convertToOpenDict(cursorSet *A)
{
	openDic newOpenDic;
	newOpenDic = initOpenDict(A->VHptr);
	int trav = A->elemIndex;

	// Loop to remove/delete elements from cursorSet
	for (; trav != -1 ; trav = A->VHptr->VH_node[trav].next){

		int hash = openHash(A->VHptr->VH_node->elem.prodID);
		int *ptrav;

		for (ptrav = &newOpenDic.header[hash] ; *ptrav != -1 ; ptrav = &newOpenDic.dicVHptr->VH_node[*ptrav].next){};

		int newNode = mallocInVHeap(A->VHptr);

		if (newNode != -1){
			A->count--;
			newOpenDic.count++;
			newOpenDic.dicVHptr->VH_node[newNode].elem = A->VHptr->VH_node[*ptrav].elem;
			newOpenDic.dicVHptr->VH_node->next = -1;
			*ptrav = newNode;
		}
	}
	// Deleted elements will be stored inside dictionary

	// EACH GROUP in the dictionary is sorted in ascending order according to ID
	printf("\nConverted to Open Dictionary\n");
	return newOpenDic;
}



void displayOpenDict(openDic D)
{
	//Variable declaration here 
	
	printf("\n\nDetails of the Open Hash Dictionary:: ");
	printf("\n-------------------------------------");
	
	printf("\nNo. of elements :: %d", D.count);
	printf("\n\n%-7s", "GROUPS");
	printf("%15s","ID Numbers");
	printf("\n%-7s%15s", "------","----------\n");
	
	//Write your code here
	int x, y;

	for (x = 0 ; x < OPEN_DSIZE ; x++){
		printf("%02d | ", D.header[x]);
		for (y = D.header[x] ; y != -1 ; y = D.dicVHptr->VH_node[y].next){
			printf("%-7s => ", 
			D.dicVHptr->VH_node[y].elem.prodID);
		}
		printf("\n");
	}
	printf("\n");

    // printf("\n\n"); system("Pause");	
}


/************************************************************
 *  Problem 4:: Function Definitions                        *
 ************************************************************/
void freeInVHeap(VHeap *VH, int ndx)
{

}

void deleteDict(openDic *D, char *IDen)
{

}


/************************************************************
 *  Problem 5:: Function Definitions                        *
 ************************************************************/
int closeHash(char *ID)
{

}



void initCloseDict(closeDic CD)
{


}

closeDic * convertToCloseDict(openDic *D)
{
    
}	

void displayCloseDict(closeDic CD)
{
 	//Variable declaration here


	printf("\n\nDetails of Closed Hash Dictionary :: ");
	printf("\n-------------------------------------");
	printf("\n\n%-6s", "Index");
	printf("%-10s", "ChocoID");
	printf("%-15s", "Choco Name");
	printf("\n%-6s%-10s%-15s", "-----", "-------", "----------"); 
	
	//Write your code here

	
	printf("\n\n"); system("Pause");

}

