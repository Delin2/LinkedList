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
	}else if(strcmp(ptr->symbol, sym) == 0){
		ptr->count+=1;
		return;
	}else{
		while(ptr->next!=NULL && strcmp(ptr->next->symbol, sym) != 0) 	/*Checks if symbol exists in the list. If the symbol already exist in the list then increment count by 1*/
				ptr=ptr->next;

        if(ptr->next!=NULL && strcmp(ptr->next->symbol, sym) == 0)
        {
            if(ptr->next->count++ == ptr->count)
            {
                printf("%s %s\n", ptr->symbol, ptr->next->symbol);
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
		newNode->count+=1;
		strcpy(newNode->symbol, sym);
		newNode->next = NULL;
		(*t)->next = newNode;
		*t = (*t)->next;
	}
}

void printList(struct node *h){
	if(h == NULL){
		printf("List is empty\n");
	}else{
		while(h != NULL){
			printf("   %s %d\n", h->symbol, h->count);
			h = h->next;
		}
	}
}

int main(void){
	int i, numNodes = 0;
	char userInput[64];
	char command[64];
	char command2[64];
	struct node *head, *tail;
	head=tail=NULL;

	printf("command?");

	while(fgets(userInput, 63, stdin)){
		if(userInput == NULL){
			printf("Input not valid");
		}else{
			sscanf(userInput, "%s %s", command, command2);

			if(strcmp(command, "ins") == 0)
			{
				insertNode(&head, &tail, command2);
			}
			else if(strcmp(command, "del") == 0)
			{

			}
			else if(strcmp(command, "fde") == 0)
			{

			}
			else if(strcmp(command, "pst") == 0)
			{

			}
			else if(strcmp(command, "prl") == 0)
			{
				printList(head);
			}
			else if(strcmp(command, "pcr") == 0)
			{

			}
			else if(strcmp(command, "ppr")==0)
			{

			}
			else if(strcmp(command, "psu")==0)
			{

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
