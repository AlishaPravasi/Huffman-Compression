#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode {
  int frequency;
  int c;
  struct treeNode* left;
  struct treeNode* right;
  struct treeNode* parent;
}tnode;

typedef struct node {
  tnode* value;
  struct node* next;
} LinkedList;


LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, tnode* newValue);
void llAddInOrder(LinkedList** ll, tnode* newNode);
tnode* llDeleteFirstNode(LinkedList** ll);
void llFree(LinkedList* ll);
#endif
