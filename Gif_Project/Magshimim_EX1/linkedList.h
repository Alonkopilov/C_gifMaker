#ifndef LINKEDLISTH
#define LINKEDLISTH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000
#define FALSE 0
#define TRUE !FALSE
#define MIN_DURATION 0
#define SCAN_ONCE 1
#define COLOR_CODE 1
#define LIST_BEGINNING 1
#define ONE 1

// Frame struct
typedef struct Frame
{
	char		name[MAX_LEN];
	unsigned int	duration;
	char		path[MAX_LEN];
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

int checkValidDir(char* dir);
void freeGif(FrameNode** head);
void myFgets(char str[], int n);
void printFrames(FrameNode* head);
void removeFrame(FrameNode** head);
int getAmountOfFrames(FrameNode* head);
void reverseAllFrames(FrameNode** head);
void changeFrameIndex(FrameNode** head);
void changeFrameDuration(FrameNode** head);
void changeAllFramesDuration(FrameNode** head);
FrameNode* copyFrameList(FrameNode* listToCopy);
void checkDurationInput(int scanResult, int* duration);
int checkFrameExist(FrameNode* head, char* frameToCheck);
void insertAtEnd(FrameNode** head, FrameNode* newFrameNode);
void getFrameProperties(char dir[MAX_LEN], char name[MAX_LEN], int* time);
int checkInput(FrameNode** head, char dir[MAX_LEN], char name[MAX_LEN], int* time);
void addFrameToList(FrameNode** head, char name[MAX_LEN], int* time, char dir[MAX_LEN]);

#endif
