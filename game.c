//
//  game.c
//  Mastermind
//
//  Created by Björn Kristensson on 16/12/12.
//  Copyright (c) 2012 Björn Kristensson. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Header.h"

#define MAXNUMBER 10
#define MAXDIFF 5
#define SCAN_NUM 3

/*
 Här skapar jag en array där jag låter koden sparas in i med hjälp av rand funktionen
 Låter en forloop ta en bokstav i taget och spara in i ett element i arrayen.
 */
void GenerateCode(char codeP[], int letter, char maxLetter)
{
    int diffrence = maxLetter - 'A' + 1;
    char current_letter;
    
    if (letter > 0) {
        int i = 0;
        
        for (i = 0; i < letter; i++) {
            current_letter = (rand() % diffrence) + 'A';
            codeP[i] = current_letter;
        }
        
    }
    printf("\n");
    
    return;
}

/*
 Här skapar jag en ny array som skall hålla användarens gissning,
 vad som är slutbokstav, hur många bokstäver i rad.
 
 */
void UserGuess(char guess[], int guessNumber, char maxLetter, int letter)
{
    int lettersInputted;
    int correctInput = 0;
    char curChar;
    
    printf("Enter guess %d: ", guessNumber);
    
    while (!correctInput) {
        lettersInputted = 0;
        
        curChar = getchar();
        
        while (curChar != '\n' && curChar != EOF) {
            
            if (curChar == ' ' || curChar == '\t') {
                curChar = getchar();
                continue;
            }
            
            //Låter användarens gissning bli stora bokstäver.
            curChar = toupper(curChar);
            
            /*
             Om användaren ligger inom gränsen för koden, spara in gissningen i en 
             array.
            */
            if (curChar >= 'A' && curChar <= maxLetter &&
                lettersInputted < letter) {
                guess[lettersInputted++] = curChar;
                curChar = getchar();
            }
            
            else if (curChar != '\n' && curChar != EOF) {
                while (curChar != '\n' && curChar != EOF)
                    curChar = getchar();
                lettersInputted = -1;
            }
        }
        if (lettersInputted == letter)
            correctInput = 1;
        
        if (!correctInput) {
            printf("Pattern must have exactly %d characters,", letter);
            printf(" all between A and %c\nTry again:", maxLetter);
        }
    }
    return;
}

/*
 Här geneomför jag en kontroll av användarens gissning och vad som är själva koden.
 Jag använder mig av memset för att nollställa minnet för själva testningen.
*/
int CheckInput(char *input, char *sequence, int letterNum)
{
    int letterChecked[MAXNUMBER];
    int charUsed[MAXNUMBER];
    int exact = 0, inexact = 0, index = 0, index2 = 0;
    
    memset(letterChecked, 0, sizeof(int) * MAXNUMBER);
    memset(charUsed, 0, sizeof(int) * MAXNUMBER);
    
    /*
     En nästad for loop går igenom de två arrayerna och ser vilka bokstäver som
     är satta på rätt plats.
     */
    for (index = 0; index <= letterNum - 1; index++) {
        for (index2 = 0; index2 <= letterNum - 1; index2++) {
            
            if (input[index2] == sequence[index] && index == index2 &&
                charUsed[index2] == 0) {
                
                exact++;
                letterChecked[index] = 1;
                charUsed[index2] = 1;
                break;
            }
        }
        
    }
    
    /*
     En nästad for loop går igenom de två arrayerna och ser vilka bokstäver som
     är rätt men på fel plats.
     */
    for (index = 0; index <= letterNum - 1; index++) {
        
        for (index2 = 0; index2 <= letterNum - 1; index2++) {
            if (input[index2] == sequence[index] && letterChecked[index] == 0 &&
                charUsed[index2] == 0) {
                
                inexact++;
                
                letterChecked[index] = 1;
                charUsed[index2] = 1;
                break;
            }
        }
    }
    printf("%d Black pegs and %d white pegs.\n\n", exact, inexact);
    /*
     Om man gissat rätt, returnera 1 så statistiken skrivs ut.
     */
    if (exact == letterNum)
        return 1;
    
    return 0;
}

int playGame(void)
{
    char maxLetter, curLetter;
    char sequence[MAXNUMBER];
    char guess[MAXNUMBER];
    unsigned int seed;
    
    int continuing = 0, found = 0;
    int scanReturn, gamesPlayed = 0, guesses = 0, letterNum, totalGuesses;
    double guessAverage = 0.0;
    
    /*
     En while loop med en do while inuti som först tar in själva grunden för spelet
     och sen ifall något skulle vara fel visar aktuellt felmeddelande.
     */
    while (!continuing) {
        printf("Enter max letter, number of letters and seed: ");
        scanReturn = scanf(" %c %d %u", &maxLetter, &letterNum, &seed);
        
        do {
            curLetter = getchar();
        } while (curLetter != EOF && curLetter != '\n');
        
        if (islower(maxLetter))
            maxLetter = toupper(maxLetter);
        
        if (scanReturn != SCAN_NUM || !isalpha(maxLetter)) {
            printf("Bad format for one or more values\n");
            continue;
        }
        
        if ((maxLetter - 'A') > MAXDIFF) {
            printf("Max letter must be between A and F\n");
            continue;
        }
        
        if (letterNum < 1 || letterNum > MAXNUMBER) {
            printf("Number of letters must be between 1 and 10\n");
            continue;
        }
        
        continuing = 1;
    }
    
    srand(seed);
    
    totalGuesses = 0;
    
    while (continuing) {
        printf("\nStarting the game...\n");
        gamesPlayed++;
        GenerateCode(sequence, letterNum, maxLetter);
        
        guesses = 0;
        found = 0;
        
        /*
          Ifall man inte knäckt koden så kontrollera gissningen. Ifall knäckt
          så blir found sant (dvs 1), och skriv ut statistiken.
         */
        while (!found) {
            guesses++;
            UserGuess(guess, guesses, maxLetter, letterNum);
            found = CheckInput(guess, sequence, letterNum);
        }
        
        totalGuesses += guesses;
        guessAverage = (double)totalGuesses / gamesPlayed;
        
        printf("You broke the code in %d attempts.", guesses);
        printf("  Current average: %6.3f\n\n", guessAverage);
        
        printf("Another game [Y/N]? ");
        scanf(" %c", &curLetter);
        
        curLetter = toupper(curLetter);
        
        /*
         Ifall man vill spela igen så gå tillbaka till starten, annars tillbaka till menyn. 
         */
        if (curLetter == 'Y')
            continuing = 1;
        else
            continuing = 0;
        
        do {
            curLetter = getchar();
        } while (curLetter != '\n' && curLetter != EOF);
        
    }
    return 0;
}
