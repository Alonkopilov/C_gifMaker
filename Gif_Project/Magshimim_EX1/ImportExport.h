#ifndef IMPORTEXPORTH
#define IMPORTEXPORTH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define ERROR_WAIT 4000

void handleException(char* token);
void saveProject(FrameNode* head, char* path);
FrameNode* loadProject(char* path);

#endif