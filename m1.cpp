/*
* Filename:		m1.cpp
* Project:      Major Assignment 1
* Programmer:	Sarah Jasim
* Date:			2023-2-6
* Description:  This program is meant to keep track of fares for flights and display information about them based on DS focused assignment 2.
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
	char* destination;
	char* date;
	float* flightFare;
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
* DESCRIPTION	: It deletes a node, using three parameters. The key to this 
*				  function is relinking pointers around the node before deleting.
*
* PARAMETERS	: FlightNode* node  : node to delete
*				  FlightNode **head : pointer to head of list
*				  FlightNode **tail : pointer to tail of list
*
* RETURNS		: returns nothing	: The assumption is that the node is valid
*/

void deleteNode(FlightNode* node, FlightNode** head, FlightNode** tail)
{
	//If node is NULL, it returns immediately.
	if (node == NULL)
	{
		return deleteNode;
	}
}