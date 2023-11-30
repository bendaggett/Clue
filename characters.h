#include <stdio.h>
#include <stdlib.h>

//structure representing a character
struct Character{
        char* name;
        struct Item* inventory;
        struct Room* room;
	struct Character *next;
};

//goal: constructer for a character
//param name: the characters name
//param inventory: the characters items
//param room: the room the character starts in
//param next: used to link characters together if they are in the same room
struct Character* character(char* name, struct Item* inventory, struct Room* room, struct Character* next);

//Goal: move the character in the given direction
//param player: the player to move
//param room: the destination room
void move_character(struct Character* player, struct Room* destination);
