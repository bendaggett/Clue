#include <stdio.h>
#include <stdlib.h>

//structure representing an item
struct Item{
	char* name;
	struct Item* next;
};

//used to call a character
struct Character;

//goal: constructor for item
//param name: the items name
//param next: the next item in a list
struct Item* item(char* name, struct Item* next);

//goal: take an item from a room and store it in the players inventory
//param name: the name of the item we are taking
//param player: the player that is taking the item
void add_item(char* name, struct Character* player);

//goal: drop an item from players inventory and store it in the room
//param name: the name of the item we are dropping
//param player: the player that is dropping the item
void drop_item(char* name, struct Character* player);


