#include "linkedList.h"
#include "wiew.h"
#include "ImportExport.h"

#include <stdio.h>
#include <opencv2\highgui\highgui_c.h>

#pragma warning(disable:4996)

#define RESET -1

enum menuChoices{
	EXIT=0, ADD_FRAME, REMOVE_FRAME, CHANGE_FRAME_INDEX,CHANGE_FRAME_DURATION,
	CHANGE_ALL_FRAMES_DURATION, PRINT_FRAMES, PLAY_GIF, SAVE_GIF,
	PLAY_GIF_REVERSE, PLAY_GIF_BLACK_AND_WHITE
};
enum newProjectChoices{
	CREATE_NEW_PROJECT=0, LOAD_PROJECT
};

void printStartMenu();
void printChoicesMenu();
void getChoice(int* choice);
void executeUserChoice(FrameNode** frameList, int choice);
int main(void)
{
	FrameNode* frameList = 0;
	int choice = RESET;
	char path[MAX_LEN] = { 0 };

	printStartMenu();
	getChoice(&choice);
	while (choice != CREATE_NEW_PROJECT && choice != LOAD_PROJECT)
	{
		printf("**Please enter a choice from the menu\n\n");
		printStartMenu();
		getChoice(&choice);
	}
	if (choice == LOAD_PROJECT)
	{
		printf("Enter txt project file path: ");
		myFgets(path, MAX_LEN);
		frameList = loadProject(path);
	}

	choice = RESET;

	while (choice != EXIT)
	{
		printChoicesMenu();
		getChoice(&choice);
		executeUserChoice(&frameList, choice);
	}

	freeGif(&frameList);
	getchar();
	return 0;
}

/*
	Gets a list of frames and a choice from the menu, and executes it
	input: A pointer to the first node of a linked list of frames, a choice number
*/
void executeUserChoice(FrameNode** frameList, int choice)
{
	char dir[MAX_LEN];
	char name[MAX_LEN];
	char path[MAX_LEN] = { 0 };
	int time = 0;
	FrameNode* copy = *frameList;

	switch (choice)
	{
		case EXIT:
			printf("Bye!");
			break;

		case ADD_FRAME:
			getFrameProperties(dir, name, &time);
			while (!checkInput(frameList, dir, name, &time))
			{
				getFrameProperties(dir, name, &time);
			}
			addFrameToList(frameList, name, &time, dir);
			break;

		case REMOVE_FRAME:
			removeFrame(frameList);
			break;

		case CHANGE_FRAME_INDEX:
			changeFrameIndex(frameList);
			break;

		case CHANGE_FRAME_DURATION:
			changeFrameDuration(frameList);
			break;

		case CHANGE_ALL_FRAMES_DURATION:
			changeAllFramesDuration(frameList);
			break;

		case PRINT_FRAMES:
			printFrames(*frameList);
			break;

		case PLAY_GIF:
			play(*frameList, COLOR);
			break;

		case SAVE_GIF:
			printf("Enter a directory to save the project: ");
			myFgets(path, MAX_LEN);
			saveProject(*frameList, path);

			printf("PROJECT SUCCESSFULLY SAVED!\n");
			break;

		case PLAY_GIF_REVERSE:
			playInReverse(copy);
			break;

		case PLAY_GIF_BLACK_AND_WHITE:
			play(*frameList, BLACK_AND_WHITE);
			break;

		default:
			printf("**Please enter a choice from the menu\n");
			break;
	}
	printf("\n");
}

/*
	Gets a choice from user input
	input: an empty choice pointer
*/
void getChoice(int* choice)
{
	printf("Enter a choice: ");
	scanf("%d", choice);
	getchar();
}

/*
	Prints the start menu
*/
void printStartMenu()
{
	printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	printf("   [0] Create a new project\n");
	printf("   [1] Load existing project\n");
	printf("\n");
}

/*
	Prints the choices menu
*/
void printChoicesMenu()
{
	printf("What would you like to do?\n");
	printf("   [0] Exit\n");
	printf("   [1] Add new Frame\n");
	printf("   [2] Remove a Frame\n");
	printf("   [3] Change frame index\n");
	printf("   [4] Change frame duration\n");
	printf("   [5] Change duration of all frames\n");
	printf("   [6] List frames\n");
	printf("   [7] Play movie!\n");
	printf("   [8] Save project\n");
	printf("   [9] Play movie in reverse!\n");
	printf("  [10] Play movie in black & white!\n");
	printf("\n");
}


