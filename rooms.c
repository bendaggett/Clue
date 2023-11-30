#include "rooms.h"
#include "items.h"
#include "characters.h"
 

      
//goal: constructor for a room
//param name: name of the room
//param items: list of items in the room
//param characters: list of characters in the room
//param north: adjacent room to the north
//param south: adjacent room to the south
//param east: adjacent room to east
//param west: adjacent room to the west
struct Room* room(char* name, struct Item* items, struct Character* characters, struct Room* north, struct Room* south, struct Room* east, struct Room* west){
	struct Room* temp = (struct Room*) malloc(sizeof(struct Room));     //allocate memory for the room
	temp->name = name;
	temp->items = items;
	temp->characters = characters;
	temp->north = north;
	temp->south = south;
	temp->east = east;
	temp->west = west;
	
	return temp;

}

