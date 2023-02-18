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

//Warnings
#pragma warning(disable: 6001)
#pragma warning(disable: 4996)


//constants
#define CHAR_LENG 30
#define ERROR -1


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
void fillFlightInfo(struct FlightNode** head, char* destination, char* date, double fare);
void printFlightInfo(struct FlightNode* head);
struct FlightNode* newAllocNode(char* destination, char* date, double fare);
struct FlightNode* findFlight(FlightNode* head, char* destination, char* date);
void deleteNode(FlightNode* node, FlightNode** head, FlightNode** tail);


int main()
{	 
	//inicializations and declarations
	FlightNode* head = NULL;
	FlightNode* destHead = NULL;
	FlightNode* tail = NULL;
	FlightNode* destTail = NULL;
	char* desInput = NULL;
	char* dateInput = NULL;
	char* fareInput = NULL;
	int strLeng = sizeof(char) * CHAR_LENG;
	desInput = (char*)malloc(strLeng);
	dateInput = (char*)malloc(strLeng);
	fareInput = (char*)malloc(strLeng);

	if (desInput == NULL || dateInput == NULL || fareInput == NULL)
	{
		printf("Out of memory\n");
		return ERROR;
	}

	while (1)
	{
		//destination input
		fflush(stdin);
		printf("Destination: ");
		fgets(desInput, strLeng, stdin);
		desInput[strcspn(desInput, "\r\n")] = 0;
		if (strcmp(desInput, ".") == 0)
		{
			break;
		}

		//date input
		fflush(stdin);
		printf("Date: ");
		fgets(dateInput, strLeng, stdin);
		//Fix lines at the end when printing all information contained
		dateInput[strcspn(dateInput, "\r\n")] = 0;
		if (strcmp(dateInput, ".") == 0)
		{
			break;
		}

		//Fare Input
		fflush(stdin);
		printf("Fare: ");
		fgets(fareInput, strLeng, stdin);
		fareInput[strcspn(fareInput, "\r\n")] = 0;
		if (strcmp(fareInput, ".") == 0)
		{
			break;
		}
		fillFlightInfo(&head, desInput, dateInput, atof(fareInput));
		fillFlightInfo(&destHead, desInput, dateInput, atof(fareInput));
	}

	printf("\nSorted by fare:\n");
	printFlightInfo(head);
	printf("			");

	printf("\nSorted by destination:\n");
	printFlightInfo(destHead);
	printf("			");

	fflush(stdin);
	printf("Destination: ");
	fgets(desInput, strLeng, stdin);
	desInput[strcspn(desInput, "\r\n")] = 0;

	fflush(stdin);
	printf("Date: ");
	fgets(dateInput, strLeng, stdin);
	dateInput[strcspn(dateInput, "\r\n")] = 0;

	FlightNode* searching = findFlight(destHead, desInput, dateInput);
	if (searching != NULL)
	{
		printf("Fare: %.2f\n", searching->fare);

		fflush(stdin);
		printf("New Fare: ");
		fgets(fareInput, strLeng, stdin);
		fareInput[strcspn(fareInput, "\r\n")] = 0;

		if ((atof(fareInput) < searching->fare + 0.001) && (atof(fareInput) > searching->fare - 0.001))
		{
			printf("No changes");
		}
		else
		{
			searching->fare = atof(fareInput);
			FlightNode* find = findFlight(head, desInput, dateInput);
			if (find != NULL)
			{
				deleteNode(find, &head, &tail);
			}
			fillFlightInfo(&head, desInput, dateInput, atof(fareInput));
		}
	}
	else
	{
		printf("Flight not found!");
	}

	printf("\nSorted by fare:\n");
	printFlightInfo(head);

	printf("\nSorted by destination:\n");
	printFlightInfo(destHead);

	free(desInput);
	free(dateInput);
	free(fareInput);

	struct FlightNode* prev;
	while (head != NULL)
	{
		free(head->destination);
		free(head->date);
		prev = head;
		head = head->next;
		free(prev);
	}

	while (destHead != NULL)
	{
		free(destHead->destination);
		free(destHead->date);
		prev = destHead;
		destHead = destHead->next;
		free(prev);
	}

	return 0;
}






/*
* Function:			fillFlightInfo()
* Parameters:		struct FlightNode** head, char* destination, char* date, double fare
* Return values:	None
* Description:		This function adds a new flight to the existing linked list
*					of flights based on its date, destination, and fare,
*					while maintaining the sorted order.
*/

void fillFlightInfo(struct FlightNode** head, char* destination, char* date, double fare)
{
	struct FlightNode* newNode = newAllocNode(destination, date, fare);
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
	while (curr->next != NULL && strcmp(curr->next->date, date) < 0)
	{
		curr = curr->next;
	}
	while (curr->next != NULL && strcmp(curr->next->date, date) == 0 && strcmp(curr->next->destination, destination) < 0)
	{
		curr = curr->next;
	}
	while (curr->next != NULL && strcmp(curr->next->date, date) == 0 && strcmp(curr->next->destination, destination) == 0 && curr->next-> fare < fare)
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
* Parameters :		char* destination, char* date, double fare
* Return values :	None
* Description :		This function creates a new FlightNode structure, allocates
*					memory for its destination, date. and fare fields, copies the values of
*					destination, date and fare into these fields, and sets the next field to
*					NULL. It returns a pointer to the newly created FlightNode structure.
*/

struct FlightNode* newAllocNode(char* destination, char* date, double fare)
{
	struct FlightNode* newNode = (struct FlightNode*)malloc(sizeof(struct FlightNode));

	if (newNode == NULL)
	{
		printf("Error: memory allocation failed\n");
		return NULL;
	}

	newNode->destination = (char*)malloc(sizeof(char) * (strlen(destination) + 1));
	if (newNode->destination != NULL)
	{
		strcpy(newNode->destination, destination);
	}
	else
	{
		printf("Error: memory allocation failed\n");
		free(newNode);
		return NULL;
	}

	newNode->date = (char*)malloc(sizeof(char) * (strlen(date) + 1));
	if (newNode->date != NULL)
	{
		strcpy(newNode->date, date);
	}
	else
	{
		printf("Error: memory allocation failed\n");
		free(newNode->destination);
		free(newNode);
		return NULL;
	}

	newNode->fare = fare;
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
