#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "orderList_mmart2_204.h"

orderList *createItem(void) {
	/*Temp to hold orderList and str for foodItem*/
	orderList *temp = dmalloc(sizeof(orderList));
	char *str = NULL;

	while(1){
		str = dmalloc(50);
		printf("food item: ");
		fgets(str, 50, stdin);
		if(str[0] == '\n') {
			free(str);
			break;
		}else {
			str[strcspn(str, "\n")] = 0;
			insert(str, &temp);
		}
	}


	return temp;
}

int insert(char *str, orderList **s) {
	foodNode *curr = (*s)->head;
	foodNode *temp = dmalloc(sizeof(foodNode));
	temp->data = str;
	(*s)->count++;

	if(curr == NULL) {
		/*Head is null*/
		(*s)->head = temp;
	}else if(strcmpi(str, curr->data) == 0){
		/*Duplicate fooditem*/
		free(temp);
		(*s)->count--;
		return 0;
	}else if(strcmpi(str, curr->data) < 0) {
		/*Heads str is less than new str*/
		temp->next = curr;
		(*s)->head = temp;
	}else {
		while(curr->next != NULL) {
			if(strcmpi(str, curr->next->data) == 0){
				/*Duplicate fooditem*/
				(*s)->count--;
				free(temp);
				return 0;
			}else if(strcmpi(str, curr->next->data) < 0) {
				/*If str is less than next string then inserts*/
				temp->next = curr->next;	
				curr->next = temp;
				return 1;
			}	
			curr = curr->next;
		}
		
		/*Inserts at end if is greatest item*/
		curr->next = temp;
	}
	return 1;
}

void printItems(orderList *s) {
	foodNode *current = s->head;
	foodNode *temp;
	while(current != NULL) {
		printf("%s\n", current->data);
		free(current->data);
		temp = current;
		current = current->next;
		free(temp);
        }
	free(s);
}

int main(void) {
	char *buffer = NULL;
	robotOrder *tempRobot = NULL;
	robotOrder *deliveryList = NULL;
	robotOrder *current;

	printf("******************************************************\nWelcome to GMU's Starship Robots Delivery\n* Central Dispatch System\n*****************************************************\n");
	while(1) {
		/*Inital user choice*/
		buffer = dmalloc(10);
		printf("New delivery order? (y/n) ");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = 0;

		/*Input validation*/
		while(tolower(buffer[0]) != 'n' && tolower(buffer[0]) != 'y'){	
			printf("Invalid Input Try again\n");
			printf("New delivery order? (y/n) ");
			fgets(buffer, sizeof(buffer), stdin);
			buffer[strcspn(buffer, "\n")] = 0;
		}

		/*Continues if yes*/
		if(tolower(buffer[0]) == 'y'){
			free(buffer);
			tempRobot = dmalloc(sizeof(robotOrder));

			/*Gets Robot Number name*/
			buffer = dmalloc(10);
			printf("Robot Number: ");
			fgets(buffer, 10, stdin);
			buffer[strcspn(buffer, "\n")] = 0;
			tempRobot->robotNum = atoi(buffer);
			free(buffer);

			/*Gets delivery Order name*/
			buffer = dmalloc(50);
			printf("Delivery Address for new delivery order: ");
			fgets(buffer, 50, stdin);
			buffer[strcspn(buffer, "\n")] = 0;
			tempRobot->deliverTo = buffer;
			
			/*Gets Restauraunt*/
			buffer = dmalloc(50);
			printf("Restaurant from which to pick up food: ");
			fgets(buffer, 50, stdin);
			buffer[strcspn(buffer, "\n")] = 0;
			tempRobot->restaurant = buffer;

			tempRobot->data = createItem();
			
			tempRobot->next = deliveryList;
			deliveryList = tempRobot;
		}else if(tolower(buffer[0]) == 'n') {
			free(buffer);

			current = deliveryList;
	
			printf("List of Deliveries:\n");
			while(current != NULL) {
				printf("Robot Num %i: Delivery order from %s had %i food item(s)\n",current->robotNum,current->restaurant,current->data->count);
				free(current->restaurant);
				printItems(current->data);
				printf("Deliver to: %s\n", current->deliverTo);
				free(current->deliverTo);
				tempRobot = current;
				current = current->next;
				free(tempRobot);
				
			}
			exit(1);
		}

		printf("\n");
	}
	return 0;
}

