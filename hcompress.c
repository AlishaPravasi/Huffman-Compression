#include "linkedList2.h"
#include <stdbool.h>

tnode* generateFreqTable(char* fileName)
{
  FILE* file = fopen(fileName, "r");
  tnode* charsInFile = (tnode*) malloc(128*sizeof(tnode));
  for(int i = 0; i < 128; i++)
    {
      charsInFile[i].c = i;
      charsInFile[i].frequency = 0;
      charsInFile[i].parent = NULL;
      charsInFile[i].left = NULL;
      charsInFile[i].right = NULL;
    }
  
  int endOfFile = fgetc(file);
  while(endOfFile != -1)
    {
      charsInFile[endOfFile].frequency++;
      endOfFile = fgetc(file);
    }
  return charsInFile;
}

tnode* createHuffmanTree(tnode* frequencies)
{
  LinkedList* treeNodes = llCreate();
  for(int i = 0; i < 128; i++)
    {
      llAddInOrder(&treeNodes, &frequencies[i]);
    }
  for(int i = 0; i < 127; i++)
    {
      tnode* smallest = llDeleteFirstNode(&treeNodes);
      tnode* secondSmallest = llDeleteFirstNode(&treeNodes);
      tnode* replacement = (tnode*) malloc(sizeof(tnode));
      replacement->c = -1;
      replacement->frequency = (smallest->frequency + secondSmallest->frequency);
      replacement->left = smallest;
      replacement->right = secondSmallest;
      smallest->parent = replacement;
      secondSmallest->parent = replacement;
      llAddInOrder(&treeNodes, replacement);
    }
  return treeNodes->value;
}

void encodeFile(char* fileName, tnode* frequencies)
{
  FILE* file = fopen(fileName, "r");
  int endOfFile = fgetc(file);
  char* hufFileName = (char*)malloc((sizeof(fileName)+4)*(sizeof(char)));
  hufFileName = strcat(fileName, ".huf");
  FILE* hufFile = fopen(hufFileName, "w");
  int i = 0;
  int numOfBits = 0;
  unsigned char theByte = 0;
  int temp = 7;
  char bits[100];
  while(endOfFile != -1)
    {
      i = 0;
      tnode* charToEncode = &frequencies[endOfFile];
      while(charToEncode->parent != NULL)
	{
	  if(charToEncode->parent->left == charToEncode)
	    {
	      bits[i] = 0;
	    }
	  if(charToEncode->parent->right == charToEncode)
	    {
	      bits[i] = 1;
	    }
	  charToEncode = charToEncode->parent;
	  i++;
	}
      int j = 0;
      while(j < i)
	{
	  if(bits[i-j-1] == 1)
	    {
	      theByte |= 1 << temp;
	    }
	  else
	    {
	      theByte |= 0 << temp;
	    }
	  numOfBits++;
	  if(numOfBits == 8)
	    {
	      fputc(theByte, hufFile);
	      theByte = 0;
	      numOfBits = 0;
	      temp = 8;
	    }
	  j++;
	  temp--;
	}
       endOfFile = fgetc(file);
    }
  int paddedZeroes = 8 - numOfBits;
  while(paddedZeroes > 0)
     {
       theByte<<=paddedZeroes;
       theByte+=0;
       paddedZeroes--;
     }
  fputc(theByte, hufFile);
  free(hufFileName);
}

void decodeFile(char* fileName, tnode* treeRoot)
{
  FILE* file = fopen(fileName, "r");
  char* txtFileName = (char*)malloc((sizeof(fileName)+4)*(sizeof(char)));
  txtFileName = strcat(fileName, ".txt");
  FILE* txtFile = fopen(txtFileName, "w");
  char endOfFile = fgetc(file);
  tnode* temp;
  int bit;
  temp = treeRoot;
  bool test = true;
  fseek(file, 0, SEEK_END);
  int numOfBytes = ftell(file);
  fseek(file, 0, SEEK_SET);
  for(int k = 0; k < numOfBytes; k++)
    {
      for(int i = 7; i >= 0; i--)
	{
	  bit = (endOfFile>>i)&1;
	  if(bit == 0)
	    {
	      temp = temp->left; 
	    }
	  else
	    {
	      temp = temp->right;
	    }
	  if(temp->right == NULL)
	    {
	      fputc((char)temp->c, txtFile);
	      temp = treeRoot;
	    }
	}
      endOfFile = fgetc(file);
    }
  free(txtFileName);
}

void freeTree(tnode* root)
{
  if(root->left != NULL)
    {
      freeTree(root->right);
      freeTree(root->left);
      free(root);
      printf("freed root\n");
    }
}

int main(int argc, char *argv[])
{

  // Check the make sure the input parameters are correct
  
  if (argc != 3)
    {
      printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);
      exit(1);
    }
  
  // Create the frequency table by reading the generic file
  
  tnode* leafNodes = generateFreqTable("decind.txt");
  
  // Create the huffman tree from the frequency table
  
  tnode* treeRoot = createHuffmanTree(leafNodes);
  
  // encode
  //  printTree(treeRoot, 0);
  if (strcmp(argv[1], "-e") == 0)
    {
      // Pass the leafNodes since it will process bottom up
      
      encodeFile(argv[2], leafNodes);
    }
  else
    { // decode
    
      // Pass the tree root since it will process top down
      
      decodeFile(argv[2], treeRoot);
    }
  //freeTree(treeRoot);
  return 0;
}
