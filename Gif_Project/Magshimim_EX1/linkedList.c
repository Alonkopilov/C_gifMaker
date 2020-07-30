#include "linkedList.h"
#include <opencv2\highgui\highgui_c.h>

/*
	Gets a linked list of frames and prints every frame details
	input: The first node of a FrameNode linked list
*/
void printFrames(FrameNode* head) // O(n)
{
	FrameNode* current = head;

	printf("\t%-20s%-20s%-20s\n", "Name", "Duration", "Path");
	while (current)
	{
		printf("\t%-20s%-20d%-20s\n", current->frame->name, current->frame->duration, current->frame->path);
		current = current->next;
	}
}

/*
	Gets a linked list of frames creates and adds a new frame, requesting from the user the frame properties.
	input: Pointer to the first node of a FrameNode linked list
*/
void addFrameToList(FrameNode** head, char name[MAX_LEN], int* time, char dir[MAX_LEN]) // O(n)
{
	Frame* newFrame = 0;
	FrameNode* newFrameNode = 0;

	newFrame = (Frame*)malloc(sizeof(Frame)); //Allocates heap memory for the new Frame
	strncpy(newFrame->name, name, MAX_LEN);
	strncpy(newFrame->path, dir, MAX_LEN);
	newFrame->duration = *time;

	newFrameNode = (FrameNode*)malloc(sizeof(FrameNode)); //Allocates heap memory for the new FrameNode
	newFrameNode->frame = newFrame;
	newFrameNode->next = NULL;

	insertAtEnd(head, newFrameNode); //Inserts the new node to the end of the list of frames
}

/*
	Moves a requested frame to a new index.
	input: a pointer to the first node of a linked list
*/
void changeFrameIndex(FrameNode** head) // O(n)
{
	char frameName[MAX_LEN] = { 0 };
	int newIndex = 0, counter = ONE, nodeToMoveIndex = 0;
	FrameNode* originalHead = *head, *nodeToMove = NULL, *current = originalHead, *prev = NULL, *temp = NULL;

	printf("Enter the frame you want to move: ");
	myFgets(frameName, MAX_LEN);

	printf("Enter the new index: ");
	scanf("%d", &newIndex);

	while (current != NULL && strcmp(current->frame->name, frameName)) //Goes through all frames until the requested frame to move is found
	{
		counter++;
		prev = current;
		current = current->next;
	}
	nodeToMoveIndex = counter; //Save the index of the frameNode to move
	nodeToMove = current; //Save the pointer of the frameNode to move
	
	if (current != NULL && counter != newIndex && newIndex > 0 && newIndex <= getAmountOfFrames(*head)) //Checks if a frame name was found and the new index to move is not the index of the node itself
	{
		if (prev != NULL)
		{
			prev->next = nodeToMove->next; //Cut "node to move" from list
		}
		else //If the "node to move" is in the beginning
		{
			*head = originalHead->next;
			originalHead = *head;
		}

		current = *head;
		counter = ONE;

		if (newIndex == LIST_BEGINNING) //If requested to move the node to the beginning
		{
			nodeToMove->next = originalHead;
			*head = nodeToMove; //Update the moved node as the beginning of the list
		}
		else
		{
			while (current != NULL && counter < newIndex - ONE) //Goes through the nodes until the new index for the node we want to move
			{
				counter++;
				current = current->next;
			}
			temp = current->next;
			current->next = nodeToMove;
			nodeToMove->next = temp;
		}
	}
}

/*
	Gets a linked list and returns it's length
	input: The first node of a linked list
	output: The amount of nodes in the list
*/
int getAmountOfFrames(FrameNode* head) // O(n)
{
	int len = 0;
	FrameNode* current = head;

	while (current)
	{
		len++;
		current = current->next;
	}

	return len;
}

/*
	Gets a list of frames and changes every frame's duration from user input
	input: Pointer to the first node of a FrameNode linked list
*/
void changeAllFramesDuration(FrameNode** head) // O(n)
{
	FrameNode* current = *head;
	char frameToCheck[MAX_LEN] = { 0 };
	int newDuration = 0;

	printf("Enter the duration for all frames: ");
	checkDurationInput(scanf("%d", &newDuration), &newDuration);
	getchar();

	if (*head) //Checks if list is empty
	{
		while (current != NULL)
		{
			current->frame->duration = newDuration;
			current = current->next;
		}
	}
}

/*
	Gets a list of frames and changes a certain frame's duration from user input
	input: Pointer to the first node of a FrameNode linked list
*/
void changeFrameDuration(FrameNode** head) // O(n)
{
	FrameNode* current = *head;
	char frameToCheck[MAX_LEN] = { 0 };
	int newDuration = 0, changed = 0;

	printf("Enter the name of the frame: ");
	myFgets(frameToCheck, MAX_LEN);

	printf("Enter the new duration for this frame: ");
	checkDurationInput(scanf("%d", &newDuration), &newDuration);

	while (current != NULL && changed != TRUE)
	{
		if (!strcmp(current->frame->name, frameToCheck))
		{
			current->frame->duration = newDuration;
			changed = TRUE;
		}
		current = current->next;
	}
	if (!changed) //If none of the frames were changed
	{
		printf("**\"%s\" is not in the list of frames\n\n", frameToCheck);
	}
}

/*
	Gets a list of frames and removes a certain frame from the list, from user input
	input: Pointer to the first node of a FrameNode linked list
*/
void removeFrame(FrameNode** head) // O(n)
{
	FrameNode* current = *head;
	FrameNode* temp = NULL;
	char name[MAX_LEN] = { 0 };
	int gotRemoved = FALSE;

	printf("Enter the name of the frame you wish to erase: ");
	myFgets(name, MAX_LEN);

	if (*head) //Checks if the list is empty
	{
		if (!(strcmp((*head)->frame->name, name))) //Checks the first frame
		{
			*head = (*head)->next;
			free(current);
			gotRemoved = TRUE;
		}
		else
		{
			while (current->next != NULL) //Checks the rest of frames
			{
				if (!strcmp(current->next->frame->name, name))
				{
					gotRemoved = TRUE;
					temp = current->next; //Saves the pointer of the node we want to free
					current->next = temp->next;
					free(temp);
				}
				else
				{
					current = current->next;
				}
			}
		}
	}
	if (!gotRemoved) //If nothing had been removed
	{
		printf("**\"%s\" is not in the list of frames\n\n", name);
	}
}

/*
	Gets a list of frames and inserts a new frame node to the end of the list
	input: Pointer to the first node of a FrameNode linked list, a new frameNode to insert
*/
void insertAtEnd(FrameNode** head, FrameNode* newFrameNode) // O(n)
{
	FrameNode* current = *head;

	if (!*head) //Checks if the list is empty -> make the new frame the first node
	{
		*head = newFrameNode;
	}
	else
	{
		while (current->next != NULL)
		{
			current = current->next;
		}

		current->next = newFrameNode;
		newFrameNode->next = NULL;
	}
}

/*
	Gets a list of frames, a frame name and checks if that frame exist
	input: Pointer to the first node of a FrameNode linked list, a frame name to check
	output: True if the frame exist, else false
*/
int checkFrameExist(FrameNode* head, char* frameToCheck) // O(n)
{
	FrameNode* current = head;
	int exist = FALSE;

	while (current != NULL && exist != TRUE)
	{
		if (!strcmp(current->frame->name, frameToCheck))
		{
			exist = TRUE;
		}
		current = current->next;
	}
	
	return exist;
}

/*
	Gets a list of frames, a directory and checks if there is an openable image in that directory
	input: a directory to check
	output: true if the directory points to an openable image, else false
*/
int checkValidDir(char* dir) // O(1)
{
	IplImage* image = cvLoadImage(dir, COLOR_CODE);
	int validImage = 0;

	if (image) //Checks if the image is not empty
	{
		validImage = TRUE;
	}
	cvReleaseImage(&image);

	return validImage;
}

/*
	Gets empty variables of frame properties, and requests input for the new frame
	input: an empty directory string, empty frame name string, empty frame duration integer
*/
void getFrameProperties(char dir[MAX_LEN], char name[MAX_LEN], int* time) // O(1)
{
	printf("Please insert frame path: ");
	myFgets(dir, MAX_LEN);

	printf("Please insert frame duration (in muliseconds): ");
	checkDurationInput(scanf("%d", time), time);
	getchar();

	printf("Please choose a name for that frame: ");
	myFgets(name, MAX_LEN);
}

/*
	Gets the result of the frame duration input of the user and checks if it's valid.
	input: scanf results of the frame duration, the frame duration
*/
void checkDurationInput(int scanResult, int* duration)
{
	int chr = 0, rv = scanResult;

	while (rv != SCAN_ONCE || *duration < MIN_DURATION) //Checks if the duration is invalid or a number was not scanned
	{
		do {
			chr = getchar();
		} while ((chr != EOF) && (chr != '\n'));

		printf("**Please insert a valid value: ");
		rv = scanf("%d", duration);
	}
}


/*
	Gets a list of frames and frees the allocated memory of every FrameNode and Frame
	input: Pointer to the first node of a FrameNode linked list
*/
void freeGif(FrameNode** head) // O(n)
{
	FrameNode* temp = NULL;
	FrameNode* current = *head;

	while (current != NULL) //Until the end of the list
	{
		temp = current; //Saves the pointer of the node we want to free
		current = current->next;
		free(temp->frame);
		free(temp);
	}

	*head = NULL;
}

/*
	Gets the properties of a frame and checks if they are valid
	input: a pointer to a linked list of frames, frame directory, frame name and frame duration
	output: 1 if all properties are valid, else 0
*/
int checkInput(FrameNode** head, char dir[MAX_LEN], char name[MAX_LEN], int* time) // O(n)
{
	int flag = 0;

	if (checkFrameExist(*head, name))
	{
		printf("**The name is already taken, please enter another name\n\n");
	}
	else if (!checkValidDir(dir))
	{
		printf("**Unable to open file, please enter another directory\n\n");
	}
	else if (*time < MIN_DURATION)
	{
		printf("**Time argument is invalid\n\n");
	}
	else
	{
		flag = TRUE;
	}

	return flag;
}

/*
	A function will perform the fgets command and also remove the newline
	that might be at the end of the string - a known issue with fgets.
	input: the buffer to read into, the number of chars to read
*/
void myFgets(char str[], int n) // O(1)
{
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = 0;
}

/*
	Gets a linked list and reverses it.
	input: a pointer to a linked list to reverse
*/
void reverseAllFrames(FrameNode** head) //O(n)
{
	FrameNode* prev = NULL;
	FrameNode* current = *head;
	FrameNode* next = NULL;

	while (current != NULL)
	{
		next = current->next; //Save the pointer to the next node
		current->next = prev; //Set the next of the current node the previous node
		prev = current; //Move the previous node position ahead
		current = next; //Move the current node position ahead
	}

	*head = prev;
}

/*
	Copies a list of frames and returns the duplicate
	input: a linked list of frames to display
	output: a duplicate of the linked list
*/
FrameNode* copyFrameList(FrameNode* listToCopy) // O(n)
{
	FrameNode* current = listToCopy;
	FrameNode* newList = NULL;
	
	while (current->next != NULL)
	{
		addFrameToList(&newList, current->frame->name, &(current->frame->duration), current->frame->path);
		current = current->next;
	}

	return newList;
}
