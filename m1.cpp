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

//prototypes
void fillFlightInfo(struct FlightNode** head, char* destination, char* date);
void printFlightInfo(struct FlightNode* head);
struct FlightNode* newAllocNode(char* destination, char* date);

//constants
#define CHAR_LENG 30

struct FlightNode
{
	char* destination;
	char* date;
	struct FlightNode* next;
};

int main()
{
	struct FlightNode* head = NULL;

	char destination[CHAR_LENG];
	char date[CHAR_LENG];

	int i = 0;

	//Prompting the user for flight info & fill in the flight info
	while (1)
	{
		fflush(stdin);	//used to clear the input buffer after reading a string
		printf("Enter a flight destination: ");		//Prompting the user for destination of the flight
		fgets(destination, CHAR_LENG, stdin);
		destination[strcspn(destination, "\n")] = 0;

		if (strcmp(destination, ".") == 0)
		{
			break;
		}

		fflush(stdin);	//used to clear the input buffer after reading a string
		printf("Enter a flight date: "); 	//Prompting the user for date of the flight
		fgets(date, CHAR_LENG, stdin);
		date[strcspn(date, "\n")] = 0;

		if (strcmp(date, ".") == 0)
		{
			break;
		}

		//Fill in the struct with flight info
		fillFlightInfo(&head, destination, date);
	}

	//print all flight info
	printFlightInfo(head);

	//Free memory allocated for flight info
	struct FlightNode* current = head;
	while (current != NULL)
	{
		struct FlightNode* temp = current;
		current = current->next;

		free(temp->destination);
		free(temp->date);
		free(temp);
	}
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

void fillFlightInfo(struct FlightNode** head, char* destination, char* date)
{
	struct FlightNode* newNode = newAllocNode(destination, date);
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

	struct FlightNode* last = *head;
	while (last->next != NULL)
	{
		last = last->next;
	}

	last->next = newNode;
}




/*
* Function:			printFlightInfo()
* Parameters:		struct FlightNode* head
* Return values:	None
* Description:		This function prints all the flights in the list by
*					traversing the linked list starting from the head node
*					and printing the destination and date fields of each
*					FlightNode structure in the list.
*/

void printFlightInfo(struct FlightNode* head)
{
	while (head != NULL)
	{
		//printig the destination and date with a width of 35 characters and left-justified
		printf("%-35s %-35s\n", head->destination, head->date);

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

struct FlightNode* newAllocNode(char* destination, char* date)
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