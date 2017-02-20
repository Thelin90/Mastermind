//
//  Header.h
//  Mastermind
//
//  Created by Björn Kristensson on 16/12/12.
//  Copyright (c) 2012 Björn Kristensson. All rights reserved.
//

void show_menu();
int get_selection();
void run_selection(int selection);
int pause();
void GenerateSequence(char sequenceP[], int letterNum, char maxLetter);
void GetInput(char guess[], int guessNumber, char maxLetter, int letterNum);
int CheckInput(char *input, char *sequence, int letterNum);
int playGame(void);
void rules();


