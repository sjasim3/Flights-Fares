/*
* Filename	  : m1.cpp
* Project     : DS Major Assignment 1
* Programmer  : Sarah Jasim
* Date		  : 2023-2-6
* Description : This program is meant to keep track of fares for flights and display  
*               information about them based on DS focused assignment 2.
*/

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>	// needed for malloc

//warnings
#pragma warning(disable: 6001)
#pragma warning(disable: 4996)

//constants
#define MAX_CHAR_LENG 29
#define MIN_CHAR_LENG 1
#define CHAR_LENG 30


struct FlightNode
{
	FlightNode* head;
	struct FlightNode* prev;
	char* destination;
	char* date;
	double fare;
	struct FlightNode* next;
	FlightNode* tail;
};


//prototypes
void fillFlightInfo(struct FlightNode** head, char* destination, char* date);
void printFlightInfo(struct FlightNode* head);
struct FlightNode* newAllocNode(char* destination, char* date, double fare);
struct FlightNode* findFlight(FlightNode* head, char* destination, char* date);
void deleteNode(FlightNode* node, FlightNode** head, FlightNode** tail);


int main()
{
	//Adding a new node in a doubly linked list
	 




	return 0;

}





/*
* Function:			fillFlightInfo()
* Parameters:		struct FlightNode** head, char* destination, char* date
* Return values:	None
* Description:		This function adds a new flight to the list of flights by
*					creating a new FlightNode structure using newAllocNode
*					function, updating the head pointer to point to the newly
*					created node, and updating the next field of the previous
*					head node to point to the newly created node.
*/

void fillFlightInfo(struct FlightNode** head, char* sDestination, char* sDate, double sFlightFare)
{
	struct FlightNode* newNode = newAllocNode(sDestination, sDate, sFlightFare);
	if (!newNode)
	{
		printf("Error: memory allocation failed\n");
		return;
	}

	if (*head == NULL)
	{
		*head = newNode;
		return;
	}

	struct FlightNode* curr = *head;
	while (curr->next != NULL && strcmp(curr->next->date, sDate) < 0)
	{
		curr = curr->next;
	}
	while (curr->next != NULL && strcmp(curr->next->date, sDate) == 0 && strcmp(curr->next->destination, sDestination) < 0)
	{
		curr = curr->next;
	}
	while (curr->next != NULL && strcmp(curr->next->date, sDate) == 0 && strcmp(curr->next->destination, sDestination) == 0 && curr->next->flightFare < sFlightFare)
	{
		curr = curr->next;
	}

	newNode->next = curr->next;
	curr->next = newNode;
}






/*
* Function:			printFlightInfo()
* Parameters:		struct FlightNode* head
* Return values:	None
* Description:		This function prints all the flights in the list by
*					traversing the linked list starting from the head node
*					and printing the destination, date, and fare fields of each
*					FlightNode structure in the list.
*/

void printFlightInfo(struct FlightNode* head)
{
	while (head != NULL)
	{
		//printig the destination, date, and fare of the flight with a width of 35 characters and left-justified
		printf("%-35s\n", head->destination);
		printf("%-35s\n", head->date);
		printf("%-.2f\n", head->fare);

		head = head->next;
	}
}




/*
* Function:			FlightNode newAllocNode()
* Parameters :		char* destination, char* date
* Return values :	None
* Description :		This function creates a new FlightNode structure, allocates
*					memory for its destination and date fields, copies the values of
*					destination and date into these fields, and sets the next field to
*					NULL. It returns a pointer to the newly created FlightNode structure.

*/

struct FlightNode* newAllocNode(char* destination, char* date, double fare)
{
	struct FlightNode* newNode = (struct FlightNode*)malloc(sizeof(struct FlightNode));
	newNode->destination = (char*)malloc(CHAR_LENG);
	if (newNode->destination == NULL)
	{
		printf("Memory allocation failed.\n");
		return 0;
	}

	newNode->date = (char*)malloc(CHAR_LENG);
	if (newNode->date == NULL)
	{
		printf("Memory allocation failed.\n");
		return 0;
	}

	strcpy(newNode->destination, destination);
	strcpy(newNode->date, date);
	newNode->next = NULL;

	return newNode;
}





/*
* FUNCTION		: struct FlightNode* findFlight()
* 
* DESCRIPTION	: Finds a flight in a linked list of flights
* 
* PARAMETERS	: FlightNode* head  : head of list
*				  char* destination : pointer to null-terminated string containing destination
*				  char* date	    : pointer to null-terminated string containing date
* 
* RETURNS		: return current : a pointer to the node containing a flight,
*									if both the destination and date are matched
*				  return NULL	 : if a flight is not found
*/

struct FlightNode* findFlight(FlightNode* head, char* destination, char* date)
{
	FlightNode* current = head;
	while (current != NULL)
	{
		//it returns a pointer to the node containing a flight,
		//if both the destination and date are matched
		if (strcmp(current->destination, destination) == 0 && strcmp(current->date, date) == 0)
		{
			return current;
		}
		//moves current to the next node in the linked list 
		current = current->next;
	}
	//returns null otherwise
	return NULL;
}





/*
* FUNCTION		: void deleteNode()
*
* DESCRIPTION	: Deletes a node in a linked list of flights, using three parameters. The key to 
*				  this function is relinking pointers around the node before deleting.
*
* PARAMETERS	: FlightNode* node  : Pointer to the node to be deleted.
*				  FlightNode **head : Pointer to a pointer to the head of the linked list of flights.
*				  FlightNode **tail : Pointer to a pointer to the tail of the linked list of flights.
*
* RETURNS		: returns nothing	: The assumption is that the node is valid.
*/

void deleteNode(FlightNode* node, FlightNode** head, FlightNode** tail)
{
	//If node or *head or *tail is NULL, it returns
	if (node == NULL || *head == NULL || *tail == NULL)
	{
		return;
	}
	
	//If the node to be deleted is a head and not NULL, the head is updated to point to the next node
	if (*head == node)
	{
		*head = node->next;
	}

	//If the node to be deleted is a tail, and it is not NULL, the head is updated to point to the previous node
	if (*tail == node)
	{
		*tail = node->prev;
	}
	
	//Deleting the node without breaking the connection
	if (node->prev != NULL)
	{
		node->prev->next = node->next;
	}
	if (node->next != NULL) 
	{
		node->next->prev = node->prev;
	}

	//The node is freed to release its memory
	free(node);
}
