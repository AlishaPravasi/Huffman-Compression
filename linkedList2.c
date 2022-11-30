#include "linkedList2.h"

/*LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, tnode* newValue);
void llFree(LinkedList* ll);
void llAddInOrder(LinkedList** ll, tnode* newNode);
tnode* llDeleteFirstNode(LinkedList** ll);
*/

LinkedList* llCreate()
{
  return NULL;
}
int llIsEmpty(LinkedList* ll)
{
  return (ll == NULL);
}
void llDisplay(LinkedList* ll)
{
  printf("[");
  while (ll != NULL)
  {
    printf("%c: %d, ",(char) (ll->value->c), ll->value->frequency);
    ll = ll->next;
  }
  printf("]\n");
}
void llAdd(LinkedList** ll, tnode* newValue)
{
  // Create the new node
  LinkedList* newNode = (LinkedList*)malloc(1*sizeof(LinkedList));
  newNode->value = newValue;
  newNode->next = NULL;

  // Find the end of the list
  LinkedList* p = *ll;
  if (p == NULL)
    {
      // Add first element
      *ll = newNode;
      // This is why we need ll to be a 
    }
  else
    {
      while (p->next != NULL)
	{
	  p = p->next;
	}

      // Attach it to the end
      p->next = newNode;
    }
}

tnode* llDeleteFirstNode(LinkedList** ll)                                      
{                                                                                
  LinkedList* p;                                                                 
                                                                                 
  //Linked list does not exist or the list is empty                              
  if(llIsEmpty(*ll))
    {
       return NULL;
    }
                                                                                 
  //Storing the head to a temporary variable                                     
  p = *ll;                                                                       
 
  //creating return value
  tnode* temp = p->value;
   
  //Moving head to the next node                                                 
  *ll = (*ll)->next;
    
  //Deleting the first node                                                      
  free(p);                                                                     
                                                                                 
  return temp;                                                                   
}                                                                                
                                                                                 
void llAddInOrder(LinkedList** ll, tnode* theTreeNode)                        
{                                                                                
    LinkedList* p;
    LinkedList* newNode = (LinkedList*) malloc(sizeof(LinkedList));
    newNode->next = NULL;
    newNode->value = theTreeNode;
    
    // Special case for the head end 
    if (*ll == NULL)
      {
	*ll = newNode;
	(*ll)->next = NULL;
      }
    else if((*ll)->value->frequency >= theTreeNode->frequency)                 
      {
	newNode->next = *ll;
        *ll = newNode;
      }                                                                          
    else                                                                         
      {                                                                          
        // Locate the node before the point of insertion 
	p = *ll;                                                          
        while (p->next != NULL && p->next->value->frequency < theTreeNode->frequency)   
          {                                                                      
            p = p->next;                                             
          }
	if(p->next != NULL)
	  {
	    newNode->next = p->next;                                           
	  }
	p->next = newNode;                                                 
      }                                                                          
}

void llFree(LinkedList* ll)
{
  LinkedList* p = ll;
  while (p != NULL)
    {
      LinkedList* oldP = p;
      p = p->next;
      free(oldP);
    }
}
/*int main()
{
  LinkedList* l = llCreate();
  LinkedList* newNode = llCreate();
  tnode * temp;
  for(int i = 0; i < 10; i++)
    {
      temp = (tnode*) malloc(sizeof(tnode));
      temp->frequency = i;
      llAddInOrder(&l, temp);
      llDisplay(l);
    }
 
  temp = (tnode*) malloc(sizeof(tnode));
  temp->frequency = 20;
  llAddInOrder(&l, temp);
  llDisplay(l);
  temp = (tnode*) malloc(sizeof(tnode));
  temp->frequency = 7;
  llAddInOrder(&l, temp);
  llDisplay(l);
  temp = (tnode*) malloc(sizeof(tnode));
  temp->frequency = -5;
  llAddInOrder(&l, temp);
  llDisplay(l);
  /*llAddInOrder(&l, &b);
  llDisplay(l);
  llAddInOrder(&l, &a);
  llDisplay(l);
  llAddInOrder(&l, &c);
  llDisplay(l);
  /* llAdd(&l, &a);
  llDisplay(l);
  llAdd(&l, &c);
  llDisplay(l);
  //  llAddInOrder(&l, newNode);
   llDisplay(l);
   printf("Going into llDeleteFirstNode\n");
  tnode* firstNode = llDeleteFirstNode(&l);
  printf("firstNode: %c \n", (char) firstNode->c);
  llDisplay(l);
  llFree(l);
  }*/
