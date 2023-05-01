#pragma once

#include <iostream>
using namespace std;


class node {
public:
	int data;
	node* next;
};

class LinkedList {
public:
	node* head = NULL;
	LinkedList* next = NULL;

	void insertAtEnd(int data) {
		node* temp = head;
		if (temp == NULL) {
			head = new node();
			head->data = data;
			head->next = NULL;
			return;
		}
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new node();
		temp->next->data = data;
		temp->next->next = NULL;
	}
	int isFull() {
		
		node* current = head;
		bool flagWhite = false;
		bool flagBlack = false;
		// if first node is -2
		// and next node is not -1
		// means white is not present
		if (current->data == -2) {
			if (current->next->data != -1)
				return 0;
		}


		while (current != NULL) {
			// if current node is -2
			// and next node is -1
			// means black is not present
			if (current->data == -2) {
				if (current->next->data == -1)
					return 1;
				else
					// means white is present and black is present
					return -1;
			}
			current = current->next;
		}
	}


	void removeAll() {
		node* temp = head;
		while (temp != NULL) {
			node* next = temp->next;
			delete temp;
			temp = next;
		}
		head = NULL;
	}
	void print() {
		node* temp = head;
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

};

class LinkedList_2D{
public:
	LinkedList* head = NULL;

	void insertAtEnd(LinkedList *list) {
		LinkedList* temp = head;
		if (temp == NULL) {
			head = list;
			return;
		}
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = list;

	}
	int isFull()
	{
		LinkedList* currentRow = head;
		bool flagWhite = false;
		bool flagBlack = false;
		while (currentRow != NULL) {
			int result = currentRow->isFull();
			if (result == -1) {
				return -1;
			}
			else if (result == 0) {
				flagBlack = true;
			}
			else if (result == 1) {
				flagWhite = true;
			}
			if (flagBlack && flagWhite) {
				return -1;
			}
			currentRow = currentRow->next;
		}	
		if (flagBlack && flagWhite) {
			return -1;
		}
		else if (flagBlack) {
			return 0;
		}
		else if (flagWhite) {
			return 1;
		}
	}
	void removeAll() {
		LinkedList* temp = head;
		while (temp != NULL) {
			LinkedList* next = temp->next;
			temp->removeAll();
			delete temp;
			temp = next;
		}
		head = NULL;
	}
	void print() {
		LinkedList* temp = head;
		while (temp != NULL) {
			temp->print();
			temp = temp->next;
		}
		cout << endl;
	}
};

class QuadTree {
public:
	QuadTree* TopLeft;
	QuadTree* TopRight;
	QuadTree* BottomLeft;
	QuadTree* BottomRight;
	int data;
	QuadTree() {
		TopLeft = NULL;
		TopRight = NULL;
		BottomLeft = NULL;
		BottomRight = NULL;
		data = -1;
	}
	void constructTree(LinkedList_2D* list2D)
	{
		// Check if list is empty
		if (list2D == NULL || list2D->head == NULL) {
			return ;
		}

		// Check if list is a leaf node
		int isFullResult = list2D->isFull();
		if (isFullResult == 0 || isFullResult == 1) {
			data = isFullResult;
		}

		// Split the list into four quadrants
		LinkedList_2D* topLeft = new LinkedList_2D();
		LinkedList_2D* topRight = new LinkedList_2D();
		LinkedList_2D* bottomLeft = new LinkedList_2D();
		LinkedList_2D* bottomRight = new LinkedList_2D();

		LinkedList* row = list2D->head;
		while (row != NULL) {
			node* current = row->head;
			int count = 0;
			while (current != NULL) {
				if (count % 2 == 0) {
					if (row->isFull() == -1) {
						bottomLeft->insertAtEnd(current->data);
					}
					else {
						topLeft->insertAtEnd(current->data);
					}
				}
				else {
					if (row->isFull() == -1) {
						bottomRight->insertAtEnd(new LinkedList(current->data));
					}
					else {
						topRight->insertAtEnd(new LinkedList(current->data));
					}
				}
				count++;
				current = current->next;
			}
			row = row->next;
		}

		// Recursively call the function on each quadrant
		QuadTreeNode* qTopLeft = linkedListToQuadTree(topLeft);
		QuadTreeNode* qTopRight = linkedListToQuadTree(topRight);
		QuadTreeNode* qBottomLeft = linkedListToQuadTree(bottomLeft);
		QuadTreeNode* qBottomRight = linkedListToQuadTree(bottomRight);


	}
	void print() {
		if (data == 0) {
			cout << "0 ";
			return;
		}
		else if (data == 1) {
			cout << "1 ";
			return;
		}
		else {
			cout << "X ";
		}
		if (TopLeft != NULL) {
			TopLeft->print();
		}
		if (TopRight != NULL) {
			TopRight->print();
		}
		if (BottomLeft != NULL) {
			BottomLeft->print();
		}
		if (BottomRight != NULL) {
			BottomRight->print();
		}
		
	}

};