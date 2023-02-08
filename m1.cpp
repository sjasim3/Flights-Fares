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


struct FlightNode
{
	struct FlightNode* head;
	struct FlightNode* prev;
	char* sDestination;
	char* sDate;
	float* sFlightFare;
	struct FlightNode* next;
	struct FlightNode* tail;
};


int main()
{
	//Adding a new node in a doubly linked list
	 




	return 0;

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
		if (strcmp(current->sDestination, destination) == 0 && strcmp(current->sDate, date) == 0)
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