//
//  Header.h
//  Mastermind


void show_menu();
int get_selection();
void run_selection(int selection);
int pause();
void GenerateSequence(char sequenceP[], int letterNum, char maxLetter);
void GetInput(char guess[], int guessNumber, char maxLetter, int letterNum);
int CheckInput(char *input, char *sequence, int letterNum);
int playGame(void);
void rules();


