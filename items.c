#include "items.h"
#include "rooms.h"
#include "characters.h"



//structure representing an item
struct Item* item(char* name, struct Item* next){
	struct Item* temp = (struct Item*) malloc(sizeof(struct Item));
	temp->name = name;
	temp->next = next;
	return temp;
}

//goal: take an item from a room and store it in the players inventory
//param name: the name of the item we are taking
//param player: the player that is taking the item
void add_item(char* name, struct Character* player){
	struct Item* roomTemp = player->room->items; //temp for navigating through the list
	struct Item* playerTemp = player->inventory; //temp for navigating to player inventory
	struct Item* nextnode;	//store the matching item 

	if(roomTemp->next == NULL){			//make sure there is an item to take
		printf("no items in this room\n");
		return;
	}

	if(strcmp(roomTemp->next->name, name) == 0){ //if the first node is a match, automatically remove it
		nextnode = roomTemp->next;
		roomTemp->next = nextnode->next;
	}

	else{										
		while((roomTemp->next != NULL) && (strcmp(roomTemp->next->name, name) != 0)){ //navigate to the item in the room
			roomTemp = roomTemp->next;
		}
		printf("arg name5: %s\n", name);
		if(strcmp(roomTemp->name, name) != 0){  //check that the item is correct
			printf("name:.%s. \n", name);
			printf("temp->name: %s\n", roomTemp->name);
			printf("this item does not exist in the room\n");
			return;
		}
		else{                  //remove the item from the room and set it to nextnode
			nextnode = roomTemp->next;
			roomTemp->next = nextnode->next;       

		}
	}
	
	while(playerTemp->next != NULL){	//navigate to the last spot in player inventory
		playerTemp = playerTemp->next;
	}

	playerTemp->next = nextnode;	//add item to the last spot in player inventory
	printf("you picked up %s\n", nextnode->name);

	return;
			
}

//goal: remove item from a players list of items and drop it into a room
//param name: name of the item to remove
//param player: the head of the list we are removing from
void drop_item(char* name, struct Character* player){

        struct Item* roomTemp = player->room->items; //temp for navigating through the list
        struct Item* playerTemp = player->inventory; //temp for navigating to player inventory
        struct Item* nextnode;  //store the matching item 

        if(playerTemp->next == NULL){			//make sure there is an item to remove
                printf("no items in this invetory\n");
                return;
        }

        if(strcmp(playerTemp->next->name, name) == 0){ //if the first node is a match, automatically remove it
                nextnode = playerTemp->next;
                playerTemp->next = nextnode->next;
        }

        else{
                while((playerTemp->next != NULL) && (strcmp(playerTemp->next->name, name) != 0)){ //navigate to the item in the inventory
                        playerTemp = playerTemp->next;
                }
                printf("arg name5: %s\n", name);
                if(strcmp(playerTemp->name, name) != 0){  //check that the item is correct
                        printf("name:.%s. \n", name);
                        printf("temp->name: %s\n", playerTemp->name);
                        printf("this item does not exist in the room\n");
                        return;
                }
                else{                  //remove the item from the inventory and set it to nextnode
                        nextnode = playerTemp->next;
                        playerTemp->next = nextnode->next;

                }
        }

        while(roomTemp->next != NULL){		//navigate to the last node of list
                roomTemp = roomTemp->next;
        }	

        roomTemp->next = nextnode;	//add the item to the last node of lisst
        printf("you dropped %s\n", nextnode->name);
	
        return;

}
 

	
	
	
