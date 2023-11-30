#include "rooms.h"
#include "items.h"
#include "characters.h"
#include<time.h>
#include<string.h>

//goal: test function that prints out each room with their corresponding characters and items. Also prints them out for the avatar
//param array: array of rooms for accessing the game board
//param avatar: the player
void TESTBOARD(struct Room* array[9], struct Character* avatar){
	struct Character* tempChar;
	struct Item* tempItem;

	for(int i = 0; i < 9; i++){
		printf("room%i| ", (i+1));	//print out the room structs name
		printf("%s| ", array[i]->name);
		
		tempChar = array[i]->characters;	//print out the characters in that room
		printf("chars: ");
		while(tempChar != NULL){
			printf("%s ", tempChar->name);
			tempChar = tempChar->next;
		}

		printf("| ");

		tempItem = array[i]->items;		//print out the items in that room
		printf("items: ");
		while(tempItem != NULL){
			printf("%s ", tempItem->name);
			tempItem = tempItem->next;
		}

		printf("\n");		
	}
		if(avatar->next != NULL){			//print out characters that are linked to the avatar
			printf("\navatar->next: %s\n", avatar->next->name);
		}else{printf("\nNull\n");}

		printf("\n");

}

//goal: print out a list of the commands for the player
void help(){

	printf("\nCommands: \n");
	printf("help - show the list of commands\n");
	printf("list - look up the list of items, players, and rooms\n");
	printf("look - print the items and characters in your room, as well as any adjacent rooms\n");
	printf("go DIRECTION - move to an adjacent room in the DIRECTION north, south, east, or west\n");
	printf("take ITEM - add the specified ITEM to your inventory. ITEM must be in the room\n");
	printf("drop ITEM - remove the specified ITEM from you inventory. ITEM must be in you inventory, and will be dropped into the room\n");
	printf("inventory - show the items currently in your inventory\n");
	printf("clue CHARACTER - make a guess about which CHARACTER is the murderer. The room and item will also match if the correct ones are in the same room\n");

}

//goal: print out a list of the items, players, and rooms in the game
void list(){
	
	printf("\nitems: pencil, pen, crayon, marker, fork, katana\n");
	printf("players: joe, bob, frank, carl, jim\n");
	printf("rooms: bathroom, bedroom, kitchen, living room, hallway, basement, garage, dining room, yard\n");

}

//goal: print out the players current position, the adjacent rooms to the player, and items and characters in the players room
void look(struct Character* player){
	struct Character* tempChar = player->room->characters;
	struct Item* tempItem = player->room->items;
	
	printf("\nyou are in the %s\n", player->room->name);			//see what room player is in
	
	while(tempChar != NULL){
		if((strcmp(tempChar->name, "head") != 0) && (strcmp(tempChar->name, "player") != 0)){	//list the other characters in the room, besides the head and player
			printf("%s is in the room, ", tempChar->name);
		}
		tempChar = tempChar->next;
	}
	printf("\n");

	while(tempItem != NULL){
		if(strcmp(tempItem->name, "head") != 0){	//list all items in the room
			printf("there is %s in the room,", tempItem->name);	
		}
		tempItem = tempItem->next;
	}

	printf("\n");

	if(player->room->north != NULL){		//list room to the north
		printf("to the north is %s\n", player->room->north->name);
	}if(player->room->south != NULL){		//list room to the south
		printf("to the south is %s\n", player->room->south->name);
	}if(player->room->east != NULL){		//list room to east
		printf("to the east is %s\n", player->room->east->name);
	}if(player->room->west != NULL){		//list room to the west
		printf("to the west is %s\n", player->room->west->name);
	}

}

//goal: move the suspect to the players room, test for room, item and player matches
//param answer: Array containing the names of the correct room, item, and character
//param suspectName: the characters that player calls clue on
//param player: the avatar
//param charNames: the scrambled array of character names so we can determine which character struct the name belongs in
//param characters: an array of all characters in the game, so we can cross reference the name to the struct
int clue(char* answer[3], char* suspectName, struct Character* player, char* charNames[5], struct Character* characters[5]){
	struct Character* suspect;				//char struct of the suspect to pass to move
	struct Character* roomCharTemp = player->room->characters;	//char struct for iterating through the characters in the room
	struct Item* roomItemTemp = player->room->items;		//used for iterating through the rooms items
	struct Item* playerItemTemp = player->inventory;		//used for iterating through the players inventory
	int numMatch = 0;						//used to determine if the player has won (3 matches)
	
	for(int i = 0; i < 5; i++){				//determine which char struct corresponds to the name
		if(strcmp(suspectName, charNames[i]) == 0){
			suspect = characters[i];
			printf("you accused: %s\n", suspect->name);
			break;
		}
	}
		
	if(suspect == NULL){					//if the player has called a nonexistant character, we return and allow them to type the command correctly
		printf("the character doesn't exist. Try again.\n");
		return -1;					//-1 will not fulfill the condition to win or to increment clueCount
	}
	move_character(suspect, player->room);		//move the character to the players room

	if(strcmp(player->room->name, answer[0]) == 0){	//test whether the room is a match with the answer
		printf("room match!\n");
		numMatch += 1;					//if so, increment
	}

	while(roomItemTemp != NULL){					//test whether or not there are items in the room that match the item answer
                if(strcmp(roomItemTemp->name, answer[1]) == 0){
                        printf("item match!\n");
                        numMatch += 1;			
                        break;				
                }
                roomItemTemp = roomItemTemp->next;
	}

        while(playerItemTemp != NULL){					//test whether or not there are items in the players inventory that match the item answer
                if(strcmp(playerItemTemp->name, answer[1]) == 0){
                        printf("item match!\n");
                        numMatch += 1;
                        break;
                }
                playerItemTemp = playerItemTemp->next;
        }

        while(roomCharTemp != NULL){					//test whether any of the characters in the room fulfill that character answer
                if(strcmp(roomCharTemp->name, answer[2]) == 0){
                        printf("character match!\n");
                        numMatch += 1;
                        break;
                }
                roomCharTemp = roomCharTemp->next;
        }

	if(numMatch == 3){					//determine if the player has won or not
		printf("you won!\n");
		printf("the room was: %s\n", answer[0]);
		printf("the item was: %s\n", answer[1]);
		printf("the character was: %s\n", answer[2]);
		return 1;
	}
		
	if(numMatch == 0){
		printf("you did not find any matches\n");
	}	

	return 0;		//the player did not win

}

//goal: move the player in the specified direction
//param player: the player to move
//param direction: the direction to move(north, south, east or west)
void go(char* direction, struct Character* player){
	
	if((strcmp(direction, "north") == 0) && (player->room->north != NULL)){		//if direction is north and north is valid
		move_character(player, player->room->north);				//move north
		printf("you moved north into the %s\n", player->room->name);
	}

	else if((strcmp(direction, "south") == 0) && (player->room->south != NULL)){	//if direction is south and south is valid
                move_character(player, player->room->south);				//move south
		printf("you moved south into the %s\n", player->room->name);
        }

	else if((strcmp(direction, "east") == 0) && (player->room->east != NULL)){	//if direction is east and east is valid
                move_character(player, player->room->east);				//move east
		printf("you moved east into the %s\n", player->room->name);
        }

	else if((strcmp(direction, "west") == 0) && (player->room->west != NULL)){	//if direction is west and west is valid
                move_character(player, player->room->west);				//move west
		printf("you moved west into the %s\n", player->room->name);
        }
	
	else{										//player did not input a valid direction
		printf("try a different direction\n");
	}

}

//goal: print the items in the players inventory
//param player: the player whos inventory we must see
void inventory(struct Character* player){
	struct Item* temp = player->inventory->next;

	printf("your inventory has: ");
	while(temp != NULL){				//loop through the inventory
		printf("%s, ", temp->name);
		temp = temp->next;		
	}
	
	printf("\n");	
	
}

//goal: initialize the game board and play the game
void main(){
//START THE INITIALIZATION OF THE GAME BOARD
	srand(time(NULL));        //seed the rand with time

	char* roomNames[9] = {"bathroom", "bedroom", "kitchen", "living room", "hallway", "basement", "garage", "dining room", "yard"}; 
	char* charNames[5] = {"joe", "bob", "frank", "carl", "jim"};							//declare the name arrays for scrambling
	char* itemNames[6] = {"pencil", "pen", "crayon", "marker", "fork", "katana"};
	struct Character* char1; //declare all characters
	struct Character* char2;			
	struct Character* char3;
	struct Character* char4;
	struct Character* char5;
	struct Character* avatar;
	struct Item* item1;	//declare all items
	struct Item* item2;
	struct Item* item3;
	struct Item* item4;
	struct Item* item5;
	struct Item* item6;
	struct Room* room1;	//declare all rooms
	struct Room* room2;
	struct Room* room3;
	struct Room* room4;
	struct Room* room5;
	struct Room* room6;
	struct Room* room7;
	struct Room* room8;
	struct Room* room9;

	int upper = 8;	//The upper limit of rand
	int lower = 0;  //the lower limit of rand
	int i = 0;
	char* answer[3]; //array that stores the answers to the game. index 0 is room, index 1 is item, index2 is character	

	char* roomScram[9];	//the array of scrambled room names
	while(i < 9){	
		int num = ((rand() % (upper - lower + 1)) + lower);	//find random value between upper and lower
		if(roomNames[num] != NULL){				//check that the first array at i hasnt been set to null
			roomScram[i] = roomNames[num];			//transfer a random name from roomNames into roomScram
			roomNames[num] = NULL;				//set that index to NULL, so we don't transfer twice
			i+=1;
		}
		answer[0] = roomScram[num];				//will pick the last randomly selected room name as the answer
	}	

	char* itemScram[6];	//the array of scrambled item names
	upper = 5;
	i = 0;
	while(i < 6){
		int num = ((rand() % (upper - lower + 1)) + lower);	//copy of above while loop
		if(itemNames[num] != NULL){
			itemScram[i] = itemNames[num];
			itemNames[num] = NULL;
			i+=1;
		}
		answer[1] = itemScram[num];				//will pick the last randomly selected item name as the answer
	}
	

	char* charScram[5]; 	//the array of scrambled character names
        upper = 4;
	i = 0;
        while(i < 5){
                int num = ((rand() % (upper - lower + 1)) + lower);	//copy of above while loop
                if(charNames[num] != NULL){
                        charScram[i] = charNames[num];
                        charNames[num] = NULL;
                        i+=1;
                }
		answer[2] = charScram[num % 3];				//will pick the last randomly selected character name as the answer
        }

	item1 = item(itemScram[0], NULL);				//initialize the items with their randomized names
	item2 = item(itemScram[1], NULL);
	item3 = item(itemScram[2], NULL);
	item4 = item(itemScram[3], NULL);
	item5 = item(itemScram[4], NULL);
	item6 = item(itemScram[5], NULL);
	char1 = character(charScram[0], item("head", NULL), NULL, NULL);	//initialize characters with randomized names, and heads for their inventory
	char2 = character(charScram[1], item("head", NULL), NULL, NULL);
	char3 = character(charScram[2], item("head", NULL), NULL, NULL);	
	char4 = character(charScram[3], item("head", NULL), NULL, NULL);
	char5 = character(charScram[4], item("head", NULL), NULL, NULL);
	avatar = character("player", item("head", NULL), NULL, NULL);
	room1 = room(roomScram[0], item("head", item1), character("head", NULL, NULL, NULL), NULL, NULL, NULL, NULL);	//initialize rooms with randomized names, heads for 
	room2 = room(roomScram[1], item("head", item2), character("head", NULL, NULL, char1), NULL, NULL, NULL, NULL);	//items list and heads for their character list
	room3 = room(roomScram[2], item("head", NULL), character("head", NULL, NULL, char2), NULL, NULL, NULL, NULL);
	room4 = room(roomScram[3], item("head", NULL), character("head", NULL, NULL, char3), NULL, NULL, NULL, NULL);
	room5 = room(roomScram[4], item("head", item3), character("head", NULL, NULL, NULL), NULL, NULL, NULL, NULL);
	room6 = room(roomScram[5], item("head", item4), character("head", NULL, NULL, char4), NULL, NULL, NULL, NULL);
	room7 = room(roomScram[6], item("head", item5), character("head", NULL, NULL, char5), NULL, NULL, NULL, NULL);
	room8 = room(roomScram[7], item("head", NULL), character("head", NULL, NULL, NULL), NULL, NULL, NULL, NULL);
	room9 = room(roomScram[8], item("head", item6), character("head", NULL, NULL, NULL), NULL, NULL, NULL, NULL);

	char1->room = room2;		//assign the rooms back to the characters for easier access
	char2->room = room3;
	char3->room = room4;
	char4->room = room6;
	char5->room = room7;

	upper = 3;						//randomize the position of avatar
	int num = ((rand() % (upper - lower + 1)) + lower);	//must be random value of 0-3 so that it ends up in a room that is not taken by a character
	if(num == 0){						//the options for avatar are rooms 1, 5, 8, or 9. They will always be random rooms because
		room1->characters->next = avatar;		//the name has been randomized
		avatar->room = room1;
	}else if(num == 1){
		room5->characters->next = avatar;
		avatar->room = room5;
	}else if(num == 2){
		room8->characters->next = avatar;
		avatar->room = room8;
	}else{
		room9->characters->next = avatar;
		avatar->room = room9;
	}
	
	room1->south = room4; room1->east = room2;						//Link each room, based on what directions they should be on the game board
	room2->south = room5; room2->west = room1; room2->east = room3;
	room3->south = room6; room3->west = room2;
	room4->north = room1; room4->south = room7; room4->east = room5;
	room5->north = room2; room5->south = room8; room5->east = room6; room5->west = room4;
	room6->north = room3; room6->south = room9; room6->west = room5;
	room7->north = room4; room7->east = room8;
	room8->north = room5; room8->east = room9; room8->west = room7;
	room9->north = room6; room9->west = room8;

//END INITIALIZATION OF THE GAME BOARD----------------------------------------------------------------------------------------------------------------------------------
	
	printf("\nWelcome to clue, a text based adventure game where you must solve a murder. You have to find out who commited the murder, where it happened, and the instrument");
	printf("\nthey used. If you can isolate the murderer and the weapon in the right room, you will solve the case. You can type 'help' to get started\n");

	struct Room* roomArray[9] = {room1, room2, room3, room4, room5, room6, room7, room8, room9}; //create an array of the rooms to pass to the different functions
	struct Character* charArray[5] = {char1, char2, char3, char4, char5}; //create an array of the characters for easily passing to the clue function
	int ret;	//clue's return value will be assigned to this
	int clueCount = 0;	//number of times clue has been called
	char *buffer;		//to store user input
    	size_t bufsize = 32;	//size of buffer

    	buffer = (char *)malloc(bufsize * sizeof(char));	//allocate memory for the buffer

	while(clueCount < 10){          //main loop for playing the game. As long as player has not called clue 10 times, keep playing
		printf("\n enter a command: \n");						      
		getline(&buffer,&bufsize,stdin);        // get the input, put it into the buffer
		char* command = strtok(buffer, " ");    //take the first word as command
		char* arg = strtok(NULL, " \n");	//separates the second word to pass as an argument
			
		if(strcmp(command, "test\n") == 0){        //cheat code! only used for debug
			TESTBOARD(roomArray, avatar);
		}
		else if(strcmp(command, "help\n") == 0){	//print out list of commands
			help();				
		}
		else if(strcmp(command, "list\n") == 0){	//print list of items, rooms, players
			list();
		}
		else if(strcmp(command, "look\n") == 0){   //look command
			look(avatar);
		}
		else if(strcmp(command, "inventory\n") == 0){
			inventory(avatar);
		}
		else if(strcmp(command, "take") == 0){           //take an item and put in inventory
			add_item(arg, avatar);
		}
		else if(strcmp(command, "drop") == 0){         //drop item from inventory into room
			drop_item(arg, avatar);

		}
		else if(strcmp(command, "go") == 0){  //go a direction
			go(arg, avatar);
		}
		else if(strcmp(command, "clue") == 0){               //guess the character
			ret = clue(answer, arg, avatar, charScram, charArray);
			if(ret == 1){			//if it returns 1, player won
				break;
			}
			else if(ret == 0){		//if it returns 0, player did not win and clue increments
				clueCount += 1;
			}
		}
		else{							//deal with gibberish
			printf("that command doesn't exist\n");
		}

		printf("you have %i guesses left\n", (10 - clueCount));
		if(clueCount == 10){
			printf("you lost. \n");
		}


	}

	        free(char1); free(char2);	//free all Malloc'd memory
                free(char3); free(char4);
                free(char5); free(avatar);
                
                free(item1); free(item2);
                free(item3); free(item4);
                free(item5); free(item6);
                
                free(room1); free(room2);
                free(room3); free(room4);   
                free(room5); free(room6);
                free(room7); free(room8);
                free(room9);

                free(buffer);
	


}











