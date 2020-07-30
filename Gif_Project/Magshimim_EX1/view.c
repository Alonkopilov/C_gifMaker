#include "wiew.h"

/*
	play the movie!!
	display the images each for the duration of the frame one by one and close the window
	input: a linked list of frames to display
	output: none
*/
void play(FrameNode* list, int colorCode) // O(n)
{
	cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
	FrameNode* head = list;
	int imgNum = FIRST_IMG, playCount = 0;
	IplImage* image;
	while (playCount < GIF_REPEAT)
	{
		while (list != NULL)
		{
			image = cvLoadImage(list->frame->path, colorCode);
			IplImage* pGrayImg = 0;
			pGrayImg = cvCreateImage(cvSize(image->width, image->height), image->depth, COLOR_CODE);
			if (!image) //The image is empty - shouldn't happen since we checked already.
			{
				printf("Could not open or find image number %d", imgNum);
			}
			else
			{
				cvShowImage("Display window", image); //display the image
				cvWaitKey(list->frame->duration); //wait
				list = list->next;
				cvReleaseImage(&image);
			}
			imgNum++;
		}
		list = head; //rewind
		playCount++;
	}
	cvDestroyWindow("Display window");
	return;
}

/*
	play the movie in reverse
	display the images in reverse order each for the duration of the frame one by one and close the window
	input: a linked list of frames to display
*/
void playInReverse(FrameNode* list) // O(n)
{
	FrameNode* newListHead = 0;

	if (!list)
	{
		printf("**The frames list is empty!\n");
		return;
	}

	newListHead = copyFrameList(list);
	reverseAllFrames(&newListHead);

	play(newListHead, COLOR);
	freeGif(&newListHead);
}