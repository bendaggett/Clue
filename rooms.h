#include <stdio.h>
#include <stdlib.h>

//structure representing a room
struct Room{

	char* name;
	struct Item *items;
	struct Character *characters;
	struct Room *north;
	struct Room *south;
	struct Room *east;
	struct Room *west;
	
};

//goal: constructor for a room
//param name: name of the room
//param items: list of items in the room
//param characters: list of characters in the room
//param north: adjacent room to the north
//param south: adjacent room to the south
//param east: adjacent room to east
//param west: adjacent room to the west
struct Room* room(char* name, struct Item* items, struct Character* characters, struct Room* north, struct Room* south, struct Room* east, struct Room* west);
