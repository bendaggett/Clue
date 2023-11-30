#include "characters.h"
#include "rooms.h"
#include "items.h"

//goal: constructer for a character
//param name: the characters name
//param inventory: the characters items
//param room: the room the character starts in
//param next: used to link characters together if they are in the same room
struct Character* character(char* name, struct Item* inventory, struct Room* room, struct Character* next){
	struct Character* temp = (struct Character*) malloc(sizeof(struct Character));
	temp->name = name;
	temp->inventory = inventory;	
	temp->room = room;
	temp->next = next;
	return temp;

}

//Goal: move the character in the given direction
//param player: the player to move
//param room: the destination room
void move_character(struct Character* player, struct Room* destination){
	struct Character* temp = player->room->characters; //used to navigate to character when removing character from their room
	struct Character* nextnode;			
	char* name = player->name;
	
	

	while((temp->next != NULL) && (strcmp(temp->next->name, name) != 0)){ //navigate to the character in the room
		temp = temp->next;
	}
	nextnode = temp->next;				//get the character
	temp->next = nextnode->next;			//unlink from list
	player->room = destination;
	player->next = NULL;
		
//	printf("player->next %s\n", player->next->name);
	temp = player->room->characters;				//reset temp to put character in destination room
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = player;
	
}	
