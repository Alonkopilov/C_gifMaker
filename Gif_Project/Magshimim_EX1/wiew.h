#ifndef VIEWH
#define VIEWH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_IMG 1
#define BLACK_AND_WHITE CV_LOAD_IMAGE_GRAYSCALE
#define COLOR CV_LOAD_IMAGE_COLOR

#include <opencv2\core\core_c.h>
#include <opencv2\highgui\highgui_c.h>
#include <stdio.h>
#include "LinkedList.h"

#define GIF_REPEAT 5

void play(FrameNode* list, int colorCode);
void playInReverse(FrameNode* list);

#endif