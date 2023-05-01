#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "header.h"
using namespace std;
using namespace cv;

// Method to convert image in 2D DMA
int** convertTo2DArray(Mat img, int **array, int *row, int *col)
{
	array = new int* [img.rows];
    for (int i = 0; i < img.rows; i++)
    {
		array[i] = new int[img.cols];
	}
	// To convert image in 2D DMA
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            // if pexil is black save 0 else 1
            if (img.at<uchar>(i, j) == 0)
            {
                array[i][j] = 0;
            }
            else
            {
                array[i][j] = 1;
            }
		}
	}
    *row = img.rows;
    *col = img.cols;
    return array;
}

// Method to print 2D DMA
void print2DArray(int** array, int rows, int cols)
{
	// To print 2D DMA
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
			std::cout << array[i][j] << "";
		}
		std::cout << std::endl;
	}
}

// Method to convert 2D DMA to 2D Linked List
LinkedList_2D* convertTo2DLinkedList(int** array, int rows, int cols)
{
    LinkedList_2D* linkedList2D = new LinkedList_2D();
    linkedList2D->head = NULL;

    // To convert 2D DMA to 2D Linked List
    for (int i = 0; i < rows; i++)
    {
        LinkedList* linkedList = new LinkedList();

        // To store the indices of contiguous white pixels in the row
        int whiteStart = -1, whiteEnd = -1;
        for (int j = 0; j < cols; j++)
        {
            if (array[i][j] == 1) // if pixel is white
            {
                if (whiteStart == -1) // if start of white block
                {
                    whiteStart = j;
                }
                whiteEnd = j;
            }
            else // if pixel is not white
            {
                if (whiteStart != -1) // if end of white block
                {
                    linkedList->insertAtEnd(whiteStart);
                    linkedList->insertAtEnd(whiteEnd);
                    whiteStart = -1;
                    whiteEnd = -1;
                }
            }
        }
        if (whiteStart != -1) // if end of row has white block
        {
            linkedList->insertAtEnd(whiteStart);
            linkedList->insertAtEnd(whiteEnd);
        }
        linkedList->insertAtEnd(-2); // End of white pixels

        // To store the indices of contiguous black pixels in the row
        int blackStart = -1, blackEnd = -1;
        for (int j = 0; j < cols; j++)
        {
            if (array[i][j] == 0) // if pixel is black
            {
                if (blackStart == -1) // if start of black block
                {
                    blackStart = j;
                }
                blackEnd = j;
            }
            else // if pixel is not black
            {
                if (blackStart != -1) // if end of black block
                {
                    linkedList->insertAtEnd(blackStart);
                    linkedList->insertAtEnd(blackEnd);
                    blackStart = -1;
                    blackEnd = -1;
                }
            }
        }
        if (blackStart != -1) // if end of row has black block
        {
            linkedList->insertAtEnd(blackStart);
            linkedList->insertAtEnd(blackEnd);
        }
        linkedList->insertAtEnd(-1); // End of black pixels

        linkedList2D->insertAtEnd(linkedList);
    }

    return linkedList2D;
}


int main()
{
    // To read an bmp image from the disk
    string path = "t2.bmp";
    Mat img = imread(path, IMREAD_GRAYSCALE);
    if (img.empty())
    {
		cout << "Could not read the image: " << path << endl;
		return 1;
	}

    // TO open a window and display an image
    //namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    //cv::imshow("First OpenCV Application", img);
    //cv::moveWindow("First OpenCV Application", 0, 45);
    //cv::waitKey(0);
    //cv::destroyAllWindows();

    // To convert image in 2D DMA
    int row, col;
    int** array = NULL;
    array = convertTo2DArray(img, array, &row, &col);

    //print2DArray(array, row, col);
    
    // To convert 2D DMA to 2D Linked List
    LinkedList_2D* linkedList2D = NULL;

    linkedList2D = convertTo2DLinkedList(array, row, col);
    
    // To print 2D Linked List
    //linkedList2D->print();

    // Check if 2D Linked List is full
    //cout<< linkedList2D->isFull() << endl;

    // To convert 2D Linked List to Quad Tree
    QuadTree* quadTree = new QuadTree();
    quadTree->constructTree(linkedList2D);
    
    // To print Quad Tree
    //quadTree->print();


    return 0;
}


