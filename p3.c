/*
** Dennis Lin
** DL142745
** Noah
** Fr_12:35
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
  char symbol[11];
  int count;
  struct node *next;
} node;

//Inserting nodes
void insertNode(struct node **h, struct node **t, char *sym){
	struct node *newNode;
	struct node *ptr;
	struct node *temp;

	if ((newNode = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}else if ((ptr = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}else if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}

	/*Sets newNode symbol with the value given from parameter*/
	strcpy(newNode->symbol, sym);
	ptr=*h;
	if(*h == NULL){ /*If list is empty*/
		newNode->next = NULL;
		newNode->count=1;
		*h = newNode;
		*t = newNode;
	}else if(strcmp((*h)->symbol, sym) == 0){
		(*h)->count+=1;
		return;
	}else{
		while(ptr->next!=NULL && strcmp(ptr->next->symbol, sym) != 0) 	/*Checks if symbol exists in the list. If the symbol already exist in the list then increment count by 1*/
				ptr=ptr->next;

        if(ptr->next!=NULL && strcmp(ptr->next->symbol, sym) == 0)
        {
            if(ptr->next->count++ == ptr->count)
            {
                temp = ptr->next;
                ptr->next = ptr->next->next;
                ptr = *h;

                while(ptr->next!=NULL && ptr->next->count >= temp->count)
                    ptr = ptr->next;
                if(ptr == *h && temp->count > ptr->count)
                {
                    temp->next = *h;
                    *h = temp;
                }
                else
                {
                    temp->next = ptr->next;
                    ptr->next = temp;
                }

                while(ptr->next!=NULL)
                    ptr = ptr->next;

                *t = ptr;
            }
            return;
        }
		/*List is not empty and if symbol doesn't exist in list already then add it to the tail and set count to 1 */
		newNode->count=1;
		strcpy(newNode->symbol, sym);
		newNode->next = NULL;
		(*t)->next = newNode;
		*t = (*t)->next;
	}
}

//Delete node if symbol is in list
void delNode(struct node **h, char *sym){
	struct node *temp;
	struct node *ptr;
	
	if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}else if ((ptr = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}
	
	ptr=*h;
	if(ptr == NULL) /*Checks if list is empty*/
	{
		printf("List is empty. Nothing to delete.\n");
		return;
	}else if(strcmp(ptr->symbol, sym) == 0) /*Check is symbol is the head*/
	{
		if(ptr->count == 1)
		{
			temp = ptr->next;
			*h = temp;
		}
		else
		{
			if(ptr->count-- == ptr->next->count){
				temp = ptr;
				*h = ptr->next;
				ptr = *h;
				
				while(ptr->next != NULL && ptr->next->count > temp->count)
					ptr = ptr->next;
				temp->next = ptr->next;
				ptr->next = temp;
			}
		}
	}else{/*If symbol is not in head, checks if symbol is in list. 
			If symbol is in list, decrement count and sort. 
			If symbol is not in list then nothing is deleted.*/
		while(ptr->next!=NULL && strcmp(ptr->next->symbol, sym) != 0)
			ptr = ptr->next;
		
		if(ptr->next!=NULL && strcmp(ptr->next->symbol, sym) == 0)
        {
			if(ptr->next->count == 1)
			{
				ptr->next = ptr->next->next;				
			}
			else if(ptr->next->count-- == ptr->next->next->count)
			{
				temp = ptr->next;
				ptr->next = ptr->next->next;
				ptr = *h;
				
				while(ptr->next!=NULL && ptr->next->count > temp->count)
					ptr = ptr->next;
				
				temp->next = ptr->next;
				ptr->next = temp;
			}
		}
	}
}

//Delete any node with count less than or equal to value
void fde(struct node **h, char *v){
	struct node *temp;
	struct node *ptr;
	
	if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}else if ((ptr = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}
	
	
	int val = atoi(v);   /*converts char* into int*/
	ptr = *h;
	
	if(val == NULL)   /*If value is not an int*/
		printf("Value not valid.\n");
	else if(*h == NULL)   /*If list is empty*/
		printf("List is empty.\n");
	else	
	{
		if(ptr == *h && ptr->count <= val){  //Check if head is greater than value.
			*h = NULL;
		}
		
		while(ptr->next != NULL && ptr->next->count > val)  //Search for node count less than or equal to value.
			ptr = ptr->next;
		ptr->next = NULL;
	}
}

//Display stat of list
void pst(struct node **h, struct node **t){
	int numNodes = 0;
	float total = 0, avg = 0;
	struct node *ptr;
	
	if ((ptr = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}
	
	ptr = *h;
	if(*h == NULL)
		printf("List is empty.\n");
	else{
		while(ptr){
			numNodes += 1;
			ptr = ptr->next;
		}
		ptr = *h;
		
		while(ptr){
			total += (ptr->count);
			ptr = ptr->next;
		}
		avg = total/numNodes;
		printf("No. of nodes = %d\nMax. count = %d\nMin. count = %d\nAvg. count = %.1f\n", numNodes, (*h)->count, (*t)->count, avg);
	}
}

//Print node symbol and count if it is within range
void pcr(struct node **h, char *v1, char *v2){
	struct node *ptr;
	
	if ((ptr = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}
	
	
	int val1 = atoi(v1);   /*converts char* into int*/
	int val2 = atoi(v2);
	ptr = *h;
	
	if(ptr == NULL)
		printf("The list is empty\n");
	else if(val1 < 0 || val2 < 0)
		printf("One or both value is negative\n");
	else if(val1 > val2)
		printf("Range not valid\n");
	else
	{
		if(ptr == *h && ptr->count < val1) /*If the lower bound range is bigger than head*/
			return;
		else if(ptr == *h && ptr->count >= val1 && ptr->count <= val2)
			printf("   %s %d\n", ptr->symbol, ptr->count);
		
		while(ptr != NULL)
		{
			if(ptr != *h && ptr->count >= val1 && ptr->count <= val2)
				printf("   %s %d\n", ptr->symbol, ptr->count);
			ptr = ptr->next;
		}
	}
}

//Search list for prefix
void ppr(struct node **h, const char *prefix){
	struct node *ptr;
	
	if ((ptr = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}
	
	ptr = *h;
	if(ptr == NULL)
		printf("The list is empty\n");
	else if(prefix == NULL)
		printf("Invalid prefix\n");
	else{
		size_t prefixLen = strlen(prefix);   //Assigns value depending on preffix length
		
		while(ptr != NULL){
			if(strncmp(ptr->symbol, prefix, prefixLen) == 0)
				printf("   %s %d\n", ptr->symbol, ptr->count);
			ptr = ptr->next;
		}
	}
}

/*Search list for suffix*/
void psu(struct node **h, const char *suffix){
	struct node *ptr;
	size_t ptrLen, suffixLen;
	
	if ((ptr = (struct node *)malloc(sizeof(struct node))) == NULL){
		printf("Node allocation failed. \n");
		exit(1);
	}
		
	ptr = *h;
	if(ptr == NULL)
		printf("The list is empty\n");
	else if(suffix == NULL)
		printf("Invalid suffix\n");
	else{
		suffixLen = strlen(suffix);   //Assigns value depending on suffix length
		
		while(ptr != NULL){
			ptrLen = strlen(ptr->symbol);
			if(strncmp(ptr->symbol + ptrLen - suffixLen, suffix, suffixLen) == 0)
				printf("   %s %d\n", ptr->symbol, ptr->count);
			ptr = ptr->next;
		}
	}
}

/*Prints the list*/
void printList(struct node *h){
	if(h == NULL)   /*checks if list is empty*/
	{
		printf("List is empty\n");
	}
	else   /*Prints the node symbol and count then goes to next node*/
	{
		while(h != NULL)
		{
			printf("   %s %d\n", h->symbol, h->count);
			h = h->next;
		}
	}
}

int main(void){
	int i;
	char userInput[64];
	char command[64];
	char command2[64];
	char command3[64];
	struct node *head, *tail;
	head=tail=NULL;

	printf("command?");

	while(fgets(userInput, 63, stdin)){
		if(userInput == NULL){
			printf("Input not valid");
		}else{
			sscanf(userInput, "%s %s %s", command, command2, command3);

			if(strcmp(command, "ins") == 0)
			{
				insertNode(&head, &tail, command2);
			}
			else if(strcmp(command, "del") == 0)
			{
				delNode(&head, command2);
			}
			else if(strcmp(command, "fde") == 0)
			{
				fde(&head, command2);
			}
			else if(strcmp(command, "pst") == 0)
			{
				pst(&head, &tail);
			}
			else if(strcmp(command, "prl") == 0)
			{
				printList(head);
			}
			else if(strcmp(command, "pcr") == 0)
			{
				pcr(&head, command2, command3);
			}
			else if(strcmp(command, "ppr")==0)
			{
				ppr(&head, command2);
			}
			else if(strcmp(command, "psu")==0)
			{
				psu(&head, command2);
			}
			else if(strcmp(command, "end")==0)
			{
				break;
			}
			else
			{
				printf("Invalid command. Please try again.\n");
			}
		}
		printf("command?");
	}
	return 0;
}
