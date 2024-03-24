#include <ncurses.h>
#include <cstdlib>
#include <ctime>
//Backgammon v0.2

#define BOARD_Y 21
#define BOARD_X 58
#define HOME_BOARD_X 6
#define DICE_Y 5
#define DICE_X 10
#define START_MENU_Y 9
#define START_MENU_X 28
#define PAUSE_MENU_Y 8
#define PAUSE_MENU_X 28
#define TITLE_Y 7
#define TITLE_X 60
#define MENU_LIST_LENGTH 4
#define PAUSE_LIST_LENGTH 3
#define START_MENU_ID 0
#define PAUSE_MENU_ID 1
#define GAME_ARRAY_Y 15
#define GAME_ARRAY_X 13
#define UPDATE 0
#define CLEAR 1
#define DIRECTION_UP (-1)
#define DIRECTION_DOWN 1

struct game_t {
    char active_printable{};
    int active_player = 1;
    int P1_score = 0;
    int P2_score = 0;
    int width{};
    int height{};
    int partTo{};
    int partFrom{};
    int distance{};
    int diceValue1{};
    int diceValue2{};
    int diceValues{};
    int prevMove{};
    int X_from{};
    int Y_from{};
    int X_to{};
    int Y_to{};
    int Y_array_cord{};
    int X_array_cord {};
    int barPawns_X{};
    int barPawns_Y{};
    int max_right{};
    int max_left{};
    int pawnsHome1 = 0;
    int pawnsHome2 = 0;
    int ifStarted = 0;
    bool doublet = false;
    bool ifRolled{};

    int gameArray[GAME_ARRAY_Y][GAME_ARRAY_X] = {
            {1,0,0,0,2,0,0,2,0,0,0,0,1},
            {1,0,0,0,2,0,0,2,0,0,0,0,1},
            {1,0,0,0,2,0,0,2,0,0,0,0,0},
            {1,0,0,0,0,0,0,2,0,0,0,0,0},
            {1,0,0,0,0,0,0,2,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {2,0,0,0,0,0,0,1,0,0,0,0,0},
            {2,0,0,0,0,0,0,1,0,0,0,0,0},
            {2,0,0,0,1,0,0,1,0,0,0,0,0},
            {2,0,0,0,1,0,0,1,0,0,0,0,2},
            {2,0,0,0,1,0,0,1,0,0,0,0,2}
    };

    const int gameArray_template[GAME_ARRAY_Y][GAME_ARRAY_X] = {
            {1,0,0,0,2,0,0,2,0,0,0,0,1},
            {1,0,0,0,2,0,0,2,0,0,0,0,1},
            {1,0,0,0,2,0,0,2,0,0,0,0,0},
            {1,0,0,0,0,0,0,2,0,0,0,0,0},
            {1,0,0,0,0,0,0,2,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0},
            {2,0,0,0,0,0,0,1,0,0,0,0,0},
            {2,0,0,0,0,0,0,1,0,0,0,0,0},
            {2,0,0,0,1,0,0,1,0,0,0,0,0},
            {2,0,0,0,1,0,0,1,0,0,0,0,2},
            {2,0,0,0,1,0,0,1,0,0,0,0,2}
    };

    char board[BOARD_Y][BOARD_X] = {
            "   13  14  15  16  17  18       19  20  21  22  23  24   ",
            "//==========================o==========================\\\\",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||                         | |                         ||",
            "||                        [BAR]                        ||",
            "||                         | |                         ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "\\\\==========================o==========================//",
            "   12  11  10   9   8   7       6   5   4   3   2   1    ",
            "                                                         ",
            "  Player 1:       R(oll, P(ass, E(xit       Player 2:    "
    };

    const char template_board[BOARD_Y][BOARD_X] = {
            "   13  14  15  16  17  18       19  20  21  22  23  24   ",
            "//==========================o==========================\\\\",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||                         | |                         ||",
            "||                        [BAR]                        ||",
            "||                         | |                         ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "||  |   o   |   o   |   o  | |  |   o   |   o   |   o  ||",
            "\\\\==========================o==========================//",
            "   12  11  10   9   8   7       6   5   4   3   2   1    ",
            "                                                         ",
            "  Player 1:       R(oll, P(ass, E(xit       Player 2:    "
    };

    const char homeBoard[BOARD_Y][HOME_BOARD_X] = {
            "     ",
            "  O-O",
            "  | |",
            "  | |",
            "  | |",
            "  | |",
            "  | |",
            "  O-O",
            "     ",
            "     ",
            "     ",
            "  O-O",
            "  | |",
            "  | |",
            "  | |",
            "  | |",
            "  | |",
            "  O-O",
            "     ",
            "     ",
            "     ",

    };

    const char Dieces[6][DICE_Y][DICE_X] = {
            {
                    " ======= ",
                    "|       |",
                    "|   o   |",
                    "|       |",
                    " ======= "
            },
            {
                    " ======= ",
                    "| o     |",
                    "|       |",
                    "|     o |",
                    " ======= "
            },
            {
                    " ======= ",
                    "| o     |",
                    "|   o   |",
                    "|     o |",
                    " ======= "
            },
            {
                    " ======= ",
                    "| o   o |",
                    "|       |",
                    "| o   o |",
                    " ======= "
            },
            {
                    " ======= ",
                    "| o   o |",
                    "|   o   |",
                    "| o   o |",
                    " ======= "
            },
            {
                    " ======= ",
                    "| o   o |",
                    "| o   o |",
                    "| o   o |",
                    " ======= "
            }
    };

    const char title[TITLE_Y][TITLE_X]{
        "BBBB  AAAAA  CCCC K   K  GGGG AAAAA M   M M   M  OOO  NN  N",
        "B   B A   A C     K  K  G     A   A MM MM MM MM O   O NN  N",
        "B   B A   A C     K K   G     A   A M M M M M M O   O N N N",
        "BBBB  AAAAA C     KK    G GG  AAAAA M   M M   M O   O N N N",
        "B   B A   A C     K K   G   G A   A M   M M   M O   O N N N",
        "B   B A   A C     K  K  G   G A   A M   M M   M O   O N  NN",
        "BBBB  A   A  CCCC K   K  GGGG A   A M   M M   M  OOO  N  NN"
    };

    const char startMenu[START_MENU_Y][START_MENU_X] = {
            "    B A C K G A M M O N    ",
            "o=========================o",
            "|                         |",
            "|       Start Game        |",
            "|       Load Game         |",
            "|       Leaderboard       |",
            "|       Quit              |",
            "|                         |",
            "o=========================o"
    };
    const char pauseMenu[PAUSE_MENU_Y][PAUSE_MENU_X] = {
            "         P A U S E         ",
            "o=========================o",
            "|                         |",
            "|        Resume           |",
            "|        Save Game        |",
            "|        Quit             |",
            "|                         |",
            "o=========================o"
    };
};


////FUN() RESPONSIBLE FOR SAVING GAME ARRAY TO THE PROGRESS TEXT FILE
void saveGameArrayToFile(struct game_t *game, FILE *outputFile) {
    if (outputFile != nullptr) {
        for (int row = 0; row < GAME_ARRAY_Y; row++) {
            for (int column = 0; column < GAME_ARRAY_X; column++) {
                fprintf(outputFile, "%d ", game->gameArray[row][column]);
            }
            fprintf(outputFile, "\n");
        }
    }
}

////FUN() RESPONSIBLE FOR SAVING DATA TO THE PROGRESS TEXT FILE
void saveToFile(const char* fileName, struct game_t *game) {
    FILE *outputFile = fopen(fileName, "w");
    if (outputFile != nullptr) {
        fprintf(outputFile, "%d\n", game->active_player);
        fprintf(outputFile, "%d\n", game->ifStarted);
        fprintf(outputFile, "%d\n", game->pawnsHome1);
        fprintf(outputFile, "%d\n", game->pawnsHome2);
        fprintf(outputFile, "%d\n", game->P1_score);
        fprintf(outputFile, "%d\n", game->P2_score);
        saveGameArrayToFile(game, outputFile);
        fclose(outputFile);
    }
}
////FUN() RESPONSIBLE FOR LOADING THE GAME ARRAY TO THE PROGRESS TEXT FILE
void loadGameArrayFromFile(struct game_t *game, FILE *inputFile) {
    if (inputFile != nullptr) {
        for (int row = 0; row < GAME_ARRAY_Y; row++) {
            for (int column = 0; column < GAME_ARRAY_X; column++) {
                fscanf(inputFile, "%d", &game->gameArray[row][column]);
            }
        }
    }
}


////FUN() RESPONSIBLE FOR LOADING DATA TO THE PROGRESS TEXT FILE
void loadFromFile(const char* fileName, struct game_t *game) {
    FILE *inputFile = fopen(fileName, "r");
    if (inputFile != nullptr) {
        fscanf(inputFile, "%d", &game->active_player);
        fscanf(inputFile, "%d", &game->ifStarted);
        fscanf(inputFile, "%d", &game->pawnsHome1);
        fscanf(inputFile, "%d", &game->pawnsHome2);
        fscanf(inputFile, "%d", &game->P1_score);
        fscanf(inputFile, "%d", &game->P2_score);
        loadGameArrayFromFile(game, inputFile);
        fclose(inputFile);
    }
}


////FUN() RESPONSIBLE FOR SETTING ARRAY COORDINATES
void getArrayCoordinates(struct game_t *game){
    game->Y_array_cord = (((game->height / 2) + (BOARD_Y / 2) * -1)) + 2; //getting the coordinates of right upper corner of the board
    game->X_array_cord = ((game->width / 2) - (BOARD_X / 2)) + 4;
}

////FUN() RESPONSIBLE FOR GETTING AND SETTING USER SCREEN SETTINGS AND ARRAY COORDINATES
void getDimensions(struct game_t *game){
    int height, width;
    getmaxyx(stdscr, height, width);
    game->width = width;
    game->height = height;
    getArrayCoordinates(game); //calling a function to set coordinates
}


////FUN() RESPONSIBLE FOR DEALING WITH CLICKING JUST THE COLUMN WHEN CHOSING THE PAWN
void getFromMouseX(struct game_t *game){
    int startRow, direction;
    if (game->Y_from <= 5){ //if on the upper board, set start to 5, direction down and part to 1 (upper)
        startRow = 5;
        direction = -1;
        game->partFrom = 1;
    }
    else if (game->Y_from >= 9){ //if on the lower board, set start to 9, direction up and part to 2 (lower)
        startRow = 9;
        direction = 1;
        game->partFrom = 2;
    }

    for (int i = 0; i<=5; i++) {
        if (game->gameArray[(i * direction) + startRow][game->X_from] != 0){
            game->Y_from = startRow + (i * direction); //iterate through the column until you encounter pawn
            break;
        }
    }
}

////FUN() RESPONSIBLE FOR DEALING WITH CLICKING JUST THE COLUMN WHEN PLACING THE PAWN
void getToMouseX(struct game_t *game){
    int startRow, direction;
    if (game->Y_to <= 5){ //if on the upper board, set start to 0, direction up and part to 1 (upper)
        startRow = 0;
        direction = 1;
        game->partTo = 1;
    }
    else if (game->Y_to >= 9){ //if on the lower board, set start to 14, direction down and part to 2 (lower)
        startRow = 14;
        direction = -1;
        game->partTo = 2;
    }

    for (int i = 0; i<=5; i++) {
        if (game->gameArray[(i * direction) + startRow][game->X_to] == 0){
            game->Y_to = (i * direction) + startRow; //iterate through the column until you encounter free space
            break;
        }
    }
}

////FUN() RESPONSIBLE FOR ASSIGNING MOUSE COORDINATES TO APPROPRIATE VARIABLES (MOUSE COORDINATES RESPONSIBLE FOR FIRST CLICK)
void getCords_From(struct game_t *game) {
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, nullptr); //allow mouse 1 button to be clicked
    int choice;
    MEVENT event; //for getting mouse coordinates (event.x and event.y)
    if ((choice = getch()) != ERR) {
        if (getmouse(&event) == OK) { //checking if function "getmouse" succeeded
            if ((event.x - game->X_array_cord) % 4 == 0) { // checking only for X coordinates that contains columns on them
                game->Y_from = event.y - game->Y_array_cord; // setting coordinate that it corresponds to the coordinates of the gameArray board
                game->X_from = (event.x - game->X_array_cord) / 4; // setting coordinate that it corresponds to the coordinates of the gameArray board (separator = 4)
                getFromMouseX(game); // user can click wherever he wants on specific column and this function will choose appropriate place for pawn
//                mvprintw(5,0, "From X: %d", game->X_from);
//                mvprintw(6,0, "From Y: %d", game->Y_from);
            }
        }
    }
}
////FUN() RESPONSIBLE FOR ASSIGNING MOUSE COORDINATES TO APPROPRIATE VARIABLES (MOUSE ifCOORDINATES RESPONSIBLE FOR SECOND CLICK)
void getCords_To(struct game_t *game) {
    keypad(stdscr, TRUE);
    mousemask(BUTTON1_CLICKED, nullptr); //allow mouse 1 button to be clicked
    int choice;
    MEVENT event; //for getting mouse coordinates (event.x and event.y)
    if ((choice = getch()) != ERR) {
        if (getmouse(&event) == OK) { //checking if function "getmouse" succeeded
            if ((event.x - game->X_array_cord) % 4 == 0) { // checking only for X coordinates that contains columns on them
                game->Y_to = event.y - game->Y_array_cord; // setting coordinate that it corresponds to the coordinates of the gameArray board
                game->X_to = (event.x - game->X_array_cord) / 4; // setting coordinate that it corresponds to the coordinates of the gameArray board (separator = 4)
                getToMouseX(game); // user can click wherever he wants on specific column and this function will choose appropriate place for pawn
//                mvprintw(7,0, "To X: %d", game->X_to);
//                mvprintw(8,0, "To Y: %d", game->Y_to);
            }
        }
    }
}


////FUN() RESPONSIBLE FOR COLORING THE BOARD WITH BLACK AND WHITE
void defaultColor(struct game_t *game, int row, int centre, int iteration){
    attron(COLOR_PAIR(3));
    mvprintw((game->height / 2) + centre + row, (game->width / 2) - (BOARD_X / 2) + iteration, "%c",
             game->board[row][iteration]);
    attroff(COLOR_PAIR(3));
}

////FUN() RESPONSIBLE FOR COLORING PAWNS
void colors(struct game_t *game, int row, int centre, int iteration, int mode){
    switch (mode) {
        case 1:
            attron(COLOR_PAIR(1));
            attron(A_BOLD);
            mvprintw((game->height / 2) + centre + row, (game->width / 2) - (BOARD_X / 2) + iteration, "%c",
            game->board[row][iteration]);
            attroff(A_BOLD);
            attroff(COLOR_PAIR(1));
            break;
        case 2:
            attron(COLOR_PAIR(2));
            attron(A_BOLD);
            mvprintw((game->height / 2) + centre + row, (game->width / 2) - (BOARD_X / 2) + iteration, "%c",
            game->board[row][iteration]);
            attroff(A_BOLD);
            attroff(COLOR_PAIR(2));
            break;
    }

}

////FUN() RESPONSIBLE FOR COLORING THE PAWNS ON THE GAME BOARD
void colorPawn(struct game_t *game, int row, int centre) {
    init_pair(1, COLOR_RED, COLOR_WHITE); // setting color pairs in order to color board
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_YELLOW, COLOR_WHITE);
    for (int c = 0; c < BOARD_X; c++) {
        if (game->board[row][c] == 'X') { //for X pawns set color to red and background to white
            colors(game, row, centre, c, 1);
        } else if (game->board[row][c] == 'Y') { //for Y pawns set color to blue and background to white
            colors(game, row, centre, c, 2);
        } else { //for every other place on board set color to black and background to white
            defaultColor(game, row, centre, c);
        }
    }
}

////FUN() RESPONSIBLE FOR PRINTING DICE
void printDice(int dice, int y, int x, struct game_t *game){
    start_color();
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(3));
    for(int i=0; i<DICE_Y;++i){
        mvprintw(y+i,x, "%s", game->Dieces[dice][i]);
    }
    attroff(COLOR_PAIR(3));
}

////FUN() RESPONSIBLE FOR PRINTING HOME BOARD TO GAME BOARD
void printHome(struct game_t *game){
    start_color();
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(3));
    for (int i =0; i<BOARD_Y; ++i){
        mvprintw(27+i, 133, "%s", game->homeBoard[i]);
    }
    mvprintw(31, 136, "%d", game->pawnsHome2);
    mvprintw(41, 136, "%d", game->pawnsHome1);
    attroff(COLOR_PAIR(3));

}


////FUN() RESPONSIBLE FOR PRINTING BOARD
void printBoard(struct game_t *game){
    clear();
    game->active_printable = 'b';
    int centre = (BOARD_Y/2) * -1;
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    for (int i =0; i<BOARD_Y; ++i){
        mvprintw((game->height/2)+centre+i,(game->width/2)-(BOARD_X/2), "%s", game->board[i]);
        colorPawn(game, i, centre);
    }
    printHome(game); // calling function to print home board
    attron(A_REVERSE);
    mvprintw(49, 98, "Player turn: %d", game->active_player);
    mvprintw(47, 88, "%d", game->P1_score);
    mvprintw(47, 130, "%d", game->P2_score);
    mvprintw(47, 136, "%d", game->diceValues);
    attroff(A_REVERSE);

    move(0,0);
}


////FUN() RESPONSIBLE FOR REPLACING PAWNS ON GAME BOARD
void updateBoardMode(struct game_t *game, int i, int j){
    switch (game->gameArray[i][j]) {
        case 0:
            game->board[i+2][4+(j*4)] = game->template_board[i+2][4+(j*4)];
            break;
        case 1:
            game->board[i+2][4+(j*4)] = 'X';
            break;
        case 2:
            game->board[i+2][4+(j*4)] = 'Y';
            break;
    }
}


////FUN() RESPONSIBLE FOR REPLACING PAWNS ON GAME BOARD TO ACHIEVE DEFAULT PLACEMENT (RESETTING BOARD)
void clearBoardMode(struct game_t *game, int i, int j){
    switch (game->gameArray_template[i][j]) {
        case 0:
            game->board[i+2][4+(j*4)] = game->template_board[i+2][4+(j*4)];
            break;
        case 1:
            game->board[i+2][4+(j*4)] = 'X';
            break;
        case 2:
            game->board[i+2][4+(j*4)] = 'Y';
            break;
    }
}



////FUN() RESPONSIBLE FOR ITERATING THROUGH GAME ARRAY BOARD AND THEN EITHER UPDATING IT OR CLEARING
void updateBoard(struct game_t *game, int mode){
    for (int i = 0; i < GAME_ARRAY_Y; i++){
        for (int j = 0; j < GAME_ARRAY_X; j++){ //iterating through the board
            if (mode == 0){ // for mode == 0, calling function to update state of the board
                updateBoardMode(game, i, j);
            }
            else { // for mode == 1, calling function to clear of the board
                clearBoardMode(game, i, j);
            }
        }
    }
}

////FUN() RESPONSIBLE FOR ITERATING THROUGH GAME ARRAY BOARD AND THEN EITHER UPDATING IT OR CLEARING
void updateGameArray(struct game_t *game){
    for (int i = 0; i < GAME_ARRAY_Y; i++){
        for (int j = 0; j < GAME_ARRAY_X; j++){ // iterating through gameArray
            game->gameArray[i][j] = game->gameArray_template[i][j]; // clearing the gameArray and setting it state to default
        }
    }
}


////FUN() RESPONSIBLE FOR PRINTING TITLE ON THE MENU SCREEN
void printTitle(struct game_t *game){
    int centre = (TITLE_Y/2) * -1;
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    for (int i =0; i<TITLE_Y; ++i){
        mvprintw((game->height/2)+centre+i -15,(game->width/2)-(TITLE_X/2), "%s", game->title[i]);
    }
    refresh();
}

////FUN() RESPONSIBLE FOR COLORING THE SELECTED OPTION IN START MENU
void colorStartMenuChoice(struct game_t *game, int centre, int i){
    attron(A_REVERSE);
    mvprintw((game->height/2)+centre+i,(game->width/2)-(START_MENU_X/2), "%s", game->startMenu[i]);
    attroff(A_REVERSE);
}

////FUN() RESPONSIBLE FOR PRINTING START MENU
void printStartMenu(int selected, struct game_t *game){
    clear();
    printTitle(game); // calling function to print title of the game
    game->active_printable = 's';
    int centre = (START_MENU_Y/2) * -1;
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    for (int i =0; i<START_MENU_Y; ++i){
        if (i == selected+3){
            colorStartMenuChoice(game, centre, i);
        }
        else{
            mvprintw((game->height/2)+centre+i,(game->width/2)-(START_MENU_X/2), "%s", game->startMenu[i]);
        }

    }
    attroff(COLOR_PAIR(1));
    mvprintw(43, 92, "Jakub Flizikowski  197566");
    move(0,0);
}


////FUN() RESPONSIBLE FOR PRINTING PAUSE MENU
void printPauseMenu(int selected, struct game_t *game){
    clear();
    int centre = (PAUSE_MENU_Y/2) * -1;
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(1));
    for (int i =0; i<PAUSE_MENU_Y; ++i){
        if (i == selected+3){
            attron(A_REVERSE);
            mvprintw((game->height/2)+centre+i,(game->width/2)-(PAUSE_MENU_X/2), "%s", game->pauseMenu[i]);
            attroff(A_REVERSE);
        }
        else{
            mvprintw((game->height/2)+centre+i,(game->width/2)-(PAUSE_MENU_X/2), "%s", game->pauseMenu[i]);
        }

    }
    refresh();
    attroff(COLOR_PAIR(1));
}




////FUN() RESPONSIBLE FOR ARROW KEY UP
int keyUP(int selected, int menuListLength){
    selected--; //decrementation of selected option
    if (selected == menuListLength-(menuListLength+1)){ // checking if the selected is already on top
        return 0;
    }
    else{
        return selected;
    }
}

////FUN() RESPONSIBLE FOR ARROW KEY DOWN
int keyDown(int selected, int menuListLength){
    selected++; //incrementation of selected option
    if (selected == menuListLength){ // checking if the selected is already at bottom
        return menuListLength-1;
    }
    else{
        return selected;
    }
}

////FUN() CASE RESPONSIBLE FOR OPTIONS OF START MENU
void caseEnterStarMenu(int selected, struct game_t *game){
    switch(selected){
        case 0: //start button
            if (game->ifStarted == 0){ //clearing the board, and setting the flag to 0 - game not started yet
                updateBoard(game, CLEAR);
                refresh();
            }
            else { //updating the loaded board
                updateBoard(game, UPDATE);
                refresh();
            }
            break;
        case 1:
            mvprintw(0,0, "Wybrano: %s", game->startMenu[selected+3]);
            loadFromFile("progress.txt", game); // calling a function to load up progress text file
            updateBoard(game, UPDATE); // updating the state of the board
            getch();
            break;
        case 2:
            mvprintw(0,0, "Wybrano: %s", game->startMenu[selected+3]);
            getch();
            break;
        case 3:
        default:
            break;
    }
}


////FUN() CASE RESPONSIBLE FOR OPTIONS OF PAUSE MENU
void caseEnterPauseMenu(int selected, struct game_t *game){
    switch(selected){
        case 0:
            printBoard(game); // back to the game
            break;
        case 1:
            mvprintw(0,0, "Wybrano: %s", game->pauseMenu[selected+3]);
            saveToFile("progress.txt", game); // calling function to save the progress
            getch();
            printBoard(game);
            break;
        case 2:
        default:
            printStartMenu(selected-2, game); // calling function to print start menu
            updateBoard(game, CLEAR); //RESPONSIBLE FOR CLEARING THE BOARD
            updateGameArray(game); // clearing gameArray - setting it to default state
            game->active_player = 1; // setting flags to player one and game not started yet
            game->ifStarted = 0;
            game->pawnsHome1 = 0;
            game->pawnsHome2 = 0;
            game->P1_score = 0;
            game->P2_score = 0;
            break;
    }
    refresh();
}


////FUN() USING ARROWS TO NAVIGATE ANY MENU (START/PAUSE)
int switchMenuMoving(int menuListLength, int menu, struct game_t *game){
    int input;
    int selected = 0; // setting default position of selected option to the highest one
    while(1){
        switch (menu){
            case 0:
                printStartMenu(selected, game); // printing start menu
                break;
            case 1:
                printPauseMenu(selected, game); // printing pause menu
                break;
        }
        input = getch(); // waiting for user to click either arrow key up or down
        switch (input){
            case KEY_UP:
                selected =keyUP(selected, menuListLength); // calling function to handle key up
                break;

            case KEY_DOWN:
                selected = keyDown(selected, menuListLength); // calling funcyion yo handle key down
                break;
            case KEY_ENTER: // if enter key is pressed
            case 10:
                switch (menu){
                    case 0:
                        caseEnterStarMenu(selected, game); // calling function to evaluate chosen option on start menu
                        return selected;
                    case 1:
                        caseEnterPauseMenu(selected, game); // calling function to evaluate chosen option on pause menu
                        return selected;
                }

        }
    }
}

////FUN() RESPONSIBLE FOR HANDLING START MENU
int StartMenu(struct game_t *game){
    keypad(stdscr, TRUE);
    noecho();
    return switchMenuMoving(MENU_LIST_LENGTH, START_MENU_ID, game);
}


////FUN() RESPONSIBLE FOR HANDLING PAUSE MENU
int PauseMenu(struct game_t *game){
    keypad(stdscr, TRUE);
    noecho();
    return switchMenuMoving(PAUSE_LIST_LENGTH,PAUSE_MENU_ID, game);

}

////FUN() RESPONSIBLE FOR CREATING RANDOM VALUES FOR DICES
void giveRandom(struct game_t *game) {
     std::srand(static_cast<unsigned int>(std::time(nullptr))); // creating random seed related to actual time
     game->diceValue1 = std::rand() % 6 + 1; // assigning value of the first throw to the first dice value
     game->diceValue2 = std::rand() % 6 + 1; // assigning value of the second throw to the second dice value
}


////FUN() RESPONSIBLE FOR CHANGING ACTIVE PLAYER AND PRINTING INT
void changeActivePlayer(struct game_t *game){
    game->active_player++; // incrementation of active player
    if (game->active_player == 3){ // checking if second player has changed
        game->active_player = 1;
    }
    game->ifRolled = false; // setting flag false to enable next player to throw dices

}

////FUN() RESPONSIBLE FOR GATHERING RANDOM VALUES AND PRINTING DICES
void rollDices(struct game_t *game){
    if (!game->ifRolled){ //ENABLES PLAYER TO THROW DICES ONLY ONCE PER TURN
        giveRandom(game); // calling function to give new random values
        if (game->diceValue1 == game->diceValue2){ // checking for doublet
            game->diceValues = 2*(game->diceValue1 + game->diceValue2);
            game->doublet = true; // setting the flag to true
        }
        else {
            game->diceValues = game->diceValue1 + game->diceValue2;
            game->doublet = false; // setting the flag to true
        }
        move(0,0);
        game->ifRolled = true; // enables player to throw dices only once per turn
    }

}

////FUN() RESPONSIBLE FOR ROLLING JUST ONE DICE FOR START OF THE GAME
void rollDice(struct game_t *game){
    giveRandom(game);
    printDice(game->diceValue1 - 1, (game->height) / 2 - 17, (game->width) / 2 - 5, game);
    move(0,0);
}


////FUN() RESPONSIBLE FOR PUTTING PAWN ON THE BAR AFTER BEING KNOCKED
void putPawnOnBar_GA(struct game_t *game){
    switch(game->active_player){
        case 2: //Y
            game->gameArray[game->barPawns_X][6] = 1; // set the pawn on gameArray
            game->barPawns_X++; //increment the value of pawns on bar for P1
            break;
        case 1: //X
            game->gameArray[14-game->barPawns_Y][6] = 2; // set the pawn on gameArray
            game->barPawns_Y++; //increment the value of pawns on bar for P2
            break;
    }

}

////FUN() RESPONSIBLE FOR PUTTING PAWN ON THE BAR AFTER BEING KNOCKED
void removePawnFromBar_GA(struct game_t *game){
    switch(game->active_player){
        case 1: //Y
            game->barPawns_X--; //decrement the value of pawns on bar for P1
            game->gameArray[game->barPawns_X][6] = 0; // set the pawn on gameArray
            break;
        case 2: //X
            game->barPawns_Y--; //decrement the value of pawns on bar for P2
            game->gameArray[14-game->barPawns_Y][6] = 0; // set the pawn on gameArray
            break;
    }

}



////FUN() RESPONSIBLE FOR ASSIGNING VALUES TO GAME ARRAY FOR OPERATION OF KNOCKING A PAWN
void knockingPawn_GA(struct game_t *game, int pawnToBeKnocked_Y, int pawnToBeKnocked_X, int direction){
    if (game->gameArray[game->Y_to + direction][game->X_to] != game->active_player){ // checking if there is the same pawn underneath
        game->gameArray[pawnToBeKnocked_Y][pawnToBeKnocked_X] = game->active_player; // replacing pawn with other one
        game->gameArray[pawnToBeKnocked_Y-direction][pawnToBeKnocked_X] = 0; // clearing place above (or below)
        putPawnOnBar_GA(game); // calling function to place pawn on bar
    }
}

////FUN() RESPONSIBLE FOR CHECKING IF THERE CAN BE PERFORMED KNOCKING DOWN PAWN
void ifCanKnock(struct game_t *game){
    if (game->Y_to == 1 || game->Y_to == 13){ // knocking only works when we place our pawn on either 1st or 13th column - so we check that
        napms(500); // wait half second to imitate visual effect of knocking pawn
        int pawnToBeKnocked_Y;
        int pawnToBeKnocked_X = game->X_to;
        switch (game->Y_to){ // cases for different parts of board
            case 1:
                pawnToBeKnocked_Y = game->Y_to - 1;
                knockingPawn_GA(game, pawnToBeKnocked_Y, pawnToBeKnocked_X, DIRECTION_UP); // calling function to handle knocking on gameArray
                break;
            case 13:
                pawnToBeKnocked_Y = game->Y_to + 1;
                knockingPawn_GA(game, pawnToBeKnocked_Y, pawnToBeKnocked_X, DIRECTION_DOWN); // calling function to handle knocking on gameArray
                break;
        }
    }
}


////FUN() RESPONSIBLE FOR CHANGING VALUES IN GAME ARRAY WHEN PAWN IS CHANGING ITS PALCE (TO BE UPDATED LATER ON)
void changePlace_GA(struct game_t *game){
    game->gameArray[game->Y_from][game->X_from] = 0; // clearing the place of taken pawn
    switch (game->active_player) {
        case 1:
            game->gameArray[game->Y_to][game->X_to] = 1; // for P1 placing pawn "X"
            break;
        case 2:
            game->gameArray[game->Y_to][game->X_to] = 2; // for P2 placing pawn "Y"
            break;
    }
}

////FUN() RESPONSIBLE FOR CHECKING IF PAWN CAN BE PLACES ON CERTAIN COLUMN
bool ifPossibleSwitch(struct game_t *game, int row, int coordinateX) {
    switch (game->active_player){
        case 1:
            if (game->gameArray[row][coordinateX] == 2){
                return false; // if there is opponent pawn the move is impossible
            }
            else {
                return true;
            }
        case 2:
            if (game->gameArray[row][coordinateX] == 1){
                return false; // if there is opponent pawn the move is impossible
            }
            else {
                return true;
            }
    }
    return true;
}


////FUN() RESPONSIBLE FOR CHECKING CHOSEN COLUMN IF MOVE IS POSSIBLE
bool ifMovePossible(struct game_t *game, int coordinateX){
    int startRow, direction;
    if (game->Y_to <= 5){
        startRow = 1; // start from second place since it does not matter what is at first place
        direction = 1;
    }
    else {
        startRow = 13; // start from second to last place since it does not matter what is at last place
        direction = -1;
    }

    for (int i = 0; i<5; i++) {
        int rowToCheck = (i * direction) + startRow;
        if(ifPossibleSwitch(game, rowToCheck, coordinateX)){ //iterating through column and calling function to return boolean value
            continue;
        }
        else {
            return false; // if there is one false call than move is impossible
        }
    }
    return true; // if there is no false calls than move is possible
}

////FUN() RESPONSIBLE FOR HANDLING OPERATIONS IN CASE OF POSSIBLE MOVE ON BOARD
void makeMove(struct game_t *game){
//    mvprintw(0,0, "weszlo po ruchu do move");
//    getch();
    changePlace_GA(game);
    updateBoard(game, UPDATE);
    printBoard(game);
    ifCanKnock(game); // check for possible knocking
    updateBoard(game, UPDATE);
    refresh();
    printBoard(game);
    refresh();
}


////FUN() RESPONSIBLE FOR CALCULATING THE DIFFERENCE BETWEEN SELECTED PAWN TO THE SELECTED PLACE
int evaluateDifference(struct game_t *game){
    int difference = abs(game->X_from - game->X_to); // absolute value is the difference between pawns in respect to distance
    if (game->partFrom == game->partTo){ // if pawn is "taken from" and "taken to" from the same part
        if ((game->X_from <= 5 && game->X_to >= 7) || (game->X_from >= 7 && game->X_to <= 5)){ // if taken from left side to right side or from right to left
            return difference - 1; // we do not count bar column so subtracting one from the difference
        }
    }
    else { // if pawns are from different parts - upper and lower
        difference = game->X_from + game->X_to; // then addition is the difference between pawns in respect to distance
        if (game->X_to >= 7) { // if on right side
            return difference;
        }
        else {
            return difference + 1; // if on left side we add one to calculate te difference including bar
        }
    }
    return difference;
}


bool ifInHomeEvaluation(struct game_t *game){
    if (game->gameArray[row][column] == game->active_player){ // checking for active player's pawns
        switch (game->active_player){
            case 1:
                if (row >= 9 && column >= 7){ // if pawn is located in the upper right part of the board continue (home)
                    continue;
                }
                else {
                    return false; // if not than return that there is min. one pawn not in home
                }
            case 2:
                if (row <= 5  && column >= 7){  // if pawn is located in the lower right part of the board continue (home)
                    continue;
                }
                else {
                    return false; // if not than return that there is min. one pawn not in home
                }
        }
    }
}
////FUN() RESPONSIBLE FOR CHECKING IF ALL OF THE PAWNS OF PARTICULAR PLAYER ARE IN OPPONENTS HOME
bool ifInHome(struct game_t *game){
    for (int row = 0; row < GAME_ARRAY_Y; row++) {
        for (int column = 0; column < GAME_ARRAY_X; column++) { // iterating through entire gameArray
            if (game->gameArray[row][column] == game->active_player){ // checking for active player's pawns
                switch (game->active_player){
                    case 1:
                        if (row >= 9 && column >= 7){ // if pawn is located in upper right part of the board continue (home)
                            continue;
                        }
                        else {
                            return false; // if not than return that there is min. one pawn not in home
                        }
                    case 2:
                        if (row <= 5  && column >= 7){  // if pawn is located in lower right part of the board continue (home)
                            continue;
                        }
                        else {
                            return false; // if not than return that there is min. one pawn not in home
                        }
                }
            }

        }
    }
    return true;
}


////FUN() RESPONSIBLE FOR SETTING COORDINATE OF PAWN ON LEFT AND ON RIGHT IN RIGHT SIDE OF BOARD
void getMaxSides(struct game_t *game, int part){
    int row;
    switch (part) {
        case 1:
            row = 14;
            break;
        case 2:
            row = 0;
            break;
    }
    for(int column = 7; column < 13; column++){ // iterate through columns between X=7 and X=12
        if (game->gameArray[row][column] == game->active_player){ // first from left
            game->max_left = column;
        }
        else{
            continue;
        }
    }

    for(int column = 12; column > 6; column--){ // iterate through columns between X=12 and X=7
        if (game->gameArray[row][column] == game->active_player){ // first from right
            game->max_right = column;
        }
        else{
            continue;
        }
    }

}

////FUN() RESPONSIBLE FOR HANDLING OPERATIONS TO MAKE A MOVE
void makeMoveHome(struct game_t *game){
    updateBoard(game, UPDATE);
    refresh();
    printBoard(game);
    refresh();
}

////FUN() RESPONSIBLE FOR CHANGING PLACE WHILE BEING IN HOME
bool changePlaceHomeBoardNormal(struct game_t *game){
    game->distance -= 1;
    if (game->distance == game->diceValue1 || game->distance == game->diceValue2) {

        getch();
        game->gameArray[game->Y_from][game->X_from] = 0;
        game->diceValues -= game->distance;
        if (game->diceValues < 0){
            game->diceValues = 0;
        }

        switch (game->active_player) {
            case 1:
                game->pawnsHome1++;
                break;
            case 2:
                game->pawnsHome2++;
                break;
        }
        makeMoveHome(game);

        return false;
    }
    return true;
}


////FUN() RESPONSIBLE FOR EVALUATING REMAINING VALUE OF MOVES FOR CHANGING PLACE IN HOME
void ifChangePlaceHome(struct game_t *game){
    if (game->diceValues < game->diceValue1 + game->diceValue2){
        game->diceValues = 0;
    }
    else {
        game->diceValues -= game->diceValue1;
        if (game->diceValues == game->diceValues - game->diceValue1){
            game->diceValues -= game->diceValue2;
        }
    }
}

////FUN() RESPONSIBLE FOR CHANGING PLACE WHILE BEING IN HOME
bool changePlaceHome(struct game_t *game){
    getMaxSides(game, game->active_player);
    if (game->X_from == game->max_right && (game->diceValue1 >= 13 - game->max_right || game->diceValue2 >= 13 - game->max_right)){
        game->distance = 13 - game->max_right;
        getch();
        game->gameArray[game->Y_from][game->X_from] = 0;
        ifChangePlaceHome(game);
        switch (game->active_player) {
            case 1:
                game->pawnsHome1++;
                break;
            case 2:
                game->pawnsHome2++;
                break;
        }
        makeMoveHome(game);

        return false;

    }
    if (game->distance != game->prevMove) {
        changePlaceHomeBoardNormal(game);
    }
    return true;
}

////FUN() RESPONSIBLE FOR MAKING MOVE WITH DOUBLET
bool changePlaceDoublet(struct game_t *game){
    game->prevMove = 0;
    if (game->distance == 2 * game->diceValues || game->distance == 2 * game->diceValue1 || game->distance == 2 * game->diceValue2 || game->distance == game->diceValue1 || game->distance == game->diceValue2){
        if (game->gameArray[game->Y_to][game->X_to] == 0){ //
            if (ifMovePossible(game, game->X_to)){
                game->diceValues -= game->distance;
                makeMove(game);
                return false;

            }
        }
    }
    return true;
}
////FUN() RESPONSIBLE FOR MAKING THE NORMAL MOVE
bool changePlaceNormal(struct game_t *game){
    if (game->distance == game->diceValues || game->distance == game->diceValue1 || game->distance == game->diceValue2){
        if (game->gameArray[game->Y_to][game->X_to] == 0){ //
            if (ifMovePossible(game, game->X_to) && game->distance != game->prevMove){
                game->diceValues -= game->distance;
                makeMove(game);
                game->prevMove = game->distance;
                return false;

            }
        }
    }
    return true;
}


////FUN() RESPONSIBLE FOR EVALUATING THE MOVE OF THE PLAYER
bool changePlaceEvaluation(struct game_t *game){
    if (ifInHome(game)){ // call to function to check if all pawns are in home
        if (game->pawnsHome1 == 15 | game->pawnsHome2 == 15){
            return false;
        }
        if (game->X_to == 14) {
            changePlaceHome(game);
            return false;
        }
    }
    if (game->doublet){ // checking if there is a doublet
        if (!changePlaceDoublet(game)){
            return false;
        }
        else {
            return true;
        }
    }
    else { // handling normal move
        if (!changePlaceNormal(game)){
            return false;
        }
        else {
            return true;
        }
    }
}

////FUN() RESPONSIBLE FOR CHANGING THE FIELDS ON GAME ARRAY BOARD
void changePlace(struct game_t *game) {
    while (true) {
        printDice(game->diceValue1 - 1, (game->height) / 2 - 17, (game->width) / 2 - 11, game);
        printDice(game->diceValue2 - 1, (game->height) / 2 - 17, (game->width) / 2 + 1, game);
        getCords_From(game); // get the coordinates of pawn to be changed
        while (true){
            getCords_To(game); // get the coordinates of place that player want to occupy with his pawn

            game->distance = evaluateDifference(game); // call to function to evaluate the distance between those places

            if ((game->X_to == game->X_from) && (game->partFrom == game->partTo)){ // player can leave the selected pawn by clicking second time on the same column
                break;
            }
            if(!changePlaceEvaluation(game)){ // calling a function that handles all the change place operations
                break;
            }
            else {
                continue;
            }
        }
        if (game->pawnsHome1 == 15 | game->pawnsHome2 == 15){
            break;
        }
        if (game->diceValues <= 0){ // doing loop as along as sum of dice values is not 0
            break;
        }
    }
    game->doublet = false; // setting doublet flag to false, default state
    game->prevMove = 0;
}


////FUN() RESPONSIBLE FOR HANDLING OPERATIONS IN CASE OF POSSIBLE MOVE WHILE IN BAR
void makeMoveBar(struct game_t *game){
    removePawnFromBar_GA(game);
    updateBoard(game, UPDATE);
    printBoard(game);
    ifCanKnock(game);
    updateBoard(game, UPDATE);
    refresh();
    printBoard(game);
    refresh();
}


////FUN() RESPONSIBLE FOR EVALUATING WHAT TO DO WHILE BEING ON BAR
void changePlaceBarEval(struct game_t *game){
    if (ifMovePossible(game, (game->X_to))){ // calling function to check if move is possible
        switch (game->active_player) {
            case 1:
                game->gameArray[game->Y_to][game->X_to] = 1; // placing pawn
                break;
            case 2:
                game->gameArray[game->Y_to][game->X_to] = 2; // placing pawn
                break;
        }
        makeMoveBar(game);
    }
}

////FUN() RESPONSIBLE FOR CHECKING PASSING ON BAR
bool changePlaceBarPass(struct game_t *game){
    if (!ifMovePossible(game, (13-game->diceValue1)) && !ifMovePossible(game, (13 - game->diceValue2))){ // checking if there are moves to perform
        mvprintw(36, 113, "No moves");
        napms(2000);
        return false;
    }
    return true;
}

////FUN() RESPONSIBLE FOR HANDLING TAKING PAWN FROM BAR
void changePlaceBar(struct game_t *game){
    while (true){
        printDice(game->diceValue1 - 1, (game->height) / 2 - 17, (game->width) / 2 - 11, game);
        printDice(game->diceValue2 - 1, (game->height) / 2 - 17, (game->width) / 2 + 1, game);
        if(!changePlaceBarPass(game)){
            break;
        }
        getCords_To(game); // getting coordinates of place for pawn to be placed on
        game->distance = 13 - game->X_to; // evaluating the difference
        if (game->distance == game->diceValue1 || game->distance == game->diceValue2 ){ // checking if distance is equal to values on dices
            changePlaceBarEval(game); // calling function to evaluate placing pawn from bar
        }
        if (game->active_player == 1){ // checking if there are no pawns on bar
            if (game->barPawns_X == 0){
                break;
            }
        }
        else{
            if (game->barPawns_Y == 0){
                break;
            }
        }
    }
}


////FUN() RESPONSIBLE FOR HANDLING CHANGE PLACE ON BAR OPERATIONS
void gameChoiceBar(struct game_t *game){
    changePlaceBar(game);
    changeActivePlayer(game);
    updateBoard(game, UPDATE);
    refresh();
    printBoard(game);
    refresh();
}

////FUN() RESPONSIBLE FOR HANDLING CHANGE PLACE OPERATIONS
void gameChoiceNormal(struct game_t *game){
    changePlace(game);
    changeActivePlayer(game);
    updateBoard(game, UPDATE);
    refresh();
    printBoard(game);
    refresh();
}


////FUN() RESPONSIBLE FOR FINAL DECISION ABOUT WHO WILL START
void whoStartEvaluation(struct game_t *game, int player){
    game->ifRolled = false; // set ability for next player to throw dices
    game->ifStarted = 1; // set flag that game has started already
    if (player == 1){
        changeActivePlayer(game);
    }
    printBoard(game);
    mvprintw(16, 79, "                                                  ");
    mvprintw(16, 92, "Press any key to continue");
    mvprintw(17,97, "Player %d starts", player);
    getch();
    updateBoard(game, CLEAR);
    printBoard(game);
    refresh(); // basic printing and clearing the board once more

}


////FUN() RESPONSIBLE FOR ROLLING DICES AND THEN HANDLING OPERATION OF EVALUATION
void whoStart(struct game_t *game){
    updateBoard(game, CLEAR);
    mvprintw(16, 79, "Player 1 throwing dices. Press any key to continue");
    getch();
    rollDice(game); // get value of the first dice = P1
    int diceValue1_p1 = game->diceValue1;

    getch();
    changeActivePlayer(game); // change active player
    printBoard(game);
    refresh();
    mvprintw(16, 79, "Player 2 throwing dices. Press any key to continue");
    rollDice(game); // get value of the second dice = P2
    int diceValue1_p2 = game->diceValue1;

    getch();
    if (diceValue1_p1 > diceValue1_p2){ // when P1 thrown higher value
        whoStartEvaluation(game, 1); // call function to handle evaluation
    }
    else if (diceValue1_p1 < diceValue1_p2){ // when P2 thrown higher value
        whoStartEvaluation(game, 2); // call function to handle evaluation
    }
    else {
        changeActivePlayer(game); // when they are equal - call function once more
        whoStart(game);
    }
}


////FUN() RESPONSIBLE FOR EVALUATING POINTS FOR WIN
void switchIfWon(struct game_t *game){
    switch (game->active_player){
        case 1:
            if (game->barPawns_Y >= 1){
                game->P1_score += 3;
            }
            else {
                game->P1_score++;
                if (game->pawnsHome2 == 0){
                    game->P1_score++;
                }
            }
            break;
        case 2:
            if (game->barPawns_X >= 1){
                game->P2_score += 3;
            }
            else {
                game->P2_score++;
                if (game->pawnsHome1 == 0){
                    game->P2_score++;
                }
            }
            break;
    }
}


////FUN() RESPONSIBLE FOR HANDLING WINNING PROCESS
bool ifWon(struct game_t *game){
    if (game->pawnsHome1 == 15 | game->pawnsHome2 == 15){
        changeActivePlayer(game);
        mvprintw(0,0, "Wygrywa gracz %d", game->active_player);
        switchIfWon(game);
        getch();
        updateGameArray(game);
        updateBoard(game, CLEAR);
        printBoard(game);
        game->pawnsHome1 = 0;
        game->pawnsHome2 = 0;
        whoStart(game);
        return true;
    }
    return false;
}


////FUN() RESPONSIBLE FOR HANDLING INPUT WHILE BEING INSIDE GAME
void GameChoice(struct game_t *game){
    raw();
    keypad(stdscr, TRUE);
    char choice;

    while (true){
        if(game->active_printable == 's'){ // if there is a stat menu than break
            break;
        }
        refresh();
        ifWon(game);

        choice = getch();
        switch (choice) {
            case 'r':
            case 'R':
                rollDices(game);
                if((game->active_player == 1 && game->barPawns_X > 0) || (game->active_player == 2 & game->barPawns_Y >0)){ // if there are pawns on bar
                    gameChoiceBar(game); // calling function to handle bar operations
                }
                else {
                    gameChoiceNormal(game); // calling function to handle normal change place operations
                }
                break;
            case 'p':
            case 'P':
                changeActivePlayer(game);
                printBoard(game);
                break;
            case 'e':
            case 'E':
                PauseMenu(game);
                break;
            default:
                break;
        }
        refresh();
    }

}


////FUN() RESPONSIBLE FOR HANDLING GAME PROCESS
void playButton(struct game_t *game){
    refresh();
    printBoard(game);
    if (!game->ifStarted){
        whoStart(game);
    }
    refresh();
    GameChoice(game); // allowing player to use keyboard to navigate through available options to select
}

////FUN() MAIN RESPONSIBLE FOR ACTUAL GAME
int main()
{
    struct game_t game;
    initscr();
    getDimensions(&game);
    while (1){
        int choice = StartMenu(&game);
        switch (choice) {
            case 0:
                playButton(&game); //PREPARING BOARD AND HANDLING PLAYER CHOICES
                break;
            case 1:
            case 2:
                break;
            case 3:
                endwin();
                return 0;
        }
    }
}