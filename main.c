//
//  main.c
//  Mastermind
//
//  Created by Björn Kristensson on 14/12/12.
//  Copyright (c) 2012 Björn Kristensson. All rights reserved.


#include <stdio.h>
#include "Header.h"

int choice;

int main()
{
    do{
        show_menu();
        run_selection(get_selection());
    }while(pause());
    return 0;
}

/* Skriv en meny till skärmen */
void show_menu()
{
    printf ("\n**** Meny ****\n");
    printf ("1. Play the Game\n");
    printf ("2. Read the rules\n");
    printf ("3. Exit\n\n");
}

int get_selection()
{
	int choise;
    printf("\nChoose between 1 and 3: ");
    scanf("%d", &choise);
    
	do {
		if (choise < 1 || choise > 3) {  //Ifall valt nummer är utanför 1-3, visa felmeddelande
			printf("Error! Choose between 1 and 3: ");
            scanf("%d", &choise);
		}
	} while (choise < 1 || choise > 3);
	return choise;
}

void run_selection(int selection)
{
    int myChoice = selection;
    switch ( myChoice ) {
        case 1:
            playGame();
            break;
        case 2:
            rules();
            break;
        default:
            exit(0);
            break;
    }
}

/* Visar reglerna*/
void rules() {
    printf("Rules\n");
    printf("Your object is to crack the code. The code can be of different sizes");
    printf(" depending on how hard you want it. To start the game, you will have");
    printf(" to enter three choices. First is a letter A - F, this is to determine");
    printf(" how many different \"pegs\" you want in the game.");
    printf("Second is how long code you want. 1 - 11 pegs in a row.");
    printf("Third is how hard you want the game to change around the pegs.");
    printf(" Press in 1 - 10 ( It won't make much of a difference, but 1 usually");
    printf(" makes the code slightly easier when having 4 pegs or more.)\n");
    printf("Example to start the game:  E  (Enter), 8 (Enter), 2 (Enter)\n");
    printf("In the end of the game, you will get the statistic on how many attempts");
    printf("you needed, average on all games for that round and an question if");
    printf(" you want to play it again or not.\n");
    printf("\nHappy cracking!\n");
}

int pause()
{
    int c;
    printf("\n\nPress Enter To Continue!");
    /* Tömmer inmatningsströmmen */
    while((c = getchar()) != '\n' && c != EOF);
    getchar();
    return 1;
}