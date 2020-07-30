#include "linkedList.h"
#include "ImportExport.h"

#pragma warning(disable:4996)

/*
	Gets the frame list and saves the project into a text file
	input: a linked list of frames, a path to save the project
*/
void saveProject(FrameNode* head, char* path) // O(n)
{
	FILE* gifFile = fopen(path, "w");
	FrameNode* current = head;

	if (gifFile == NULL)
	{
		printf("Unable to open file..\n");
		return;
	}
	while (current)
	{
		fprintf(gifFile, "%s*%d*%s\n", current->frame->name, current->frame->duration, current->frame->path);
		current = current->next;
	}

	fclose(gifFile);
}

/*
	Gets a project path and loads all the frames
	input: A path where a project is saved
	output: A linked list of all the frame nodes
*/
FrameNode* loadProject(char* path) //O(n)
{
	FILE* gifFile = fopen(path, "r");
	FrameNode* head = 0;
	char* token = 0;
	char line[MAX_LEN] = { 0 };
	char name[MAX_LEN] = { 0 };
	int time = 0;
	char dir[MAX_LEN] = { 0 };

	if (!gifFile)
	{
		printf("Unable to open file.. Exiting..\n\n");
		Sleep(ERROR_WAIT);
		exit(0);
	}
	else
	{
		while (fgets(line, MAX_LEN, gifFile)) //Reads a line
		{
			line[strlen(line) - ONE] = 0;
			token = strtok(line, "*"); //Gets the name of the frame
			handleException(token);
			strcpy(name, token);

			token = strtok(NULL, "*"); //Gets the duration of the frame
			handleException(token);
			time = atoi(token);

			token = strtok(NULL, "*"); //Gets the directory of the frame
			handleException(token);
			strcpy(dir, token);

			if (!checkInput(&head, dir, name, &time)) //Checks the input of all the frame properties read
			{
				handleException(NULL);
			}

			addFrameToList(&head, name, &time, dir);
		}
		
	}

	fclose(gifFile);

	return head;
}

/*
	Gets a value and checks if it's NULL. This function can also be called with NULL when an exception has appeared 
	input: a frame property token after the split function
*/
void handleException(char* token)
{
	if (token == NULL)
	{
		printf("An error has occurred while reading arguments from project.. Exiting..\n\n");
		Sleep(ERROR_WAIT);
		exit(0);
	}
}
