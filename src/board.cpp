#include "board.h"

#include <iostream>
#include <iomanip>

board::board(int size, int win, char p1_symbol) : size(size), win(win), p1_symbol(p1_symbol), areas(size, std::vector<char>(size)){
    // Initialize board areas
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++)
            areas[x][y] = 0;

    // Determine player 2 symbol based on player 1 symbol
    if (p1_symbol == 'x')
        p2_symbol = 'o';
    else if (p1_symbol == 'o')
        p2_symbol = 'x';
    else {
        p1_symbol = 'x';
        p2_symbol = 'o';
    }
}

void board::print() const{
    // Clear console (for Windows)
    //system("clear");

    // Column labels
    std::cout << std::string(5, ' ');
    for (int x = 0; x < size; x++) {
        std::cout << std::setw(1) << static_cast<char>(x + 65) << "   ";
    }
    std::cout << '\n';

    // Top horizontal line
    std::cout << std::string(3, ' ') << '.' << std::string(4 * size - 1, '-') << ".\n";

    for (int y = 0; y < size; y++) {
        // Row labels, vertical lines, and marks
        std::cout << std::setw(2) << y + 1 << " | ";
        for (int x = 0; x < size; x++) {
            if (areas[x][y] == 0)
                std::cout << ' ';
            else
                std::cout << areas[x][y];
            if (x < size - 1)
                std::cout << " | ";
        }
        std::cout << " | " << y + 1;

        // Horizontal lines
        if (y < size - 1) {
            std::cout << "\n   |";
            for (int i = 0; i < size - 1; i++)
                std::cout << std::string(3, '-') << '+';
            std::cout << std::string(3, '-') << "|";
        }
        std::cout << '\n';
    }

    // Bottom horizontal line
    std::cout << std::string(3, ' ') << '\'' << std::string(4 * size - 1, '-') << "\'\n";

    // Column labels
    std::cout << std::string(5, ' ');
    for (int x = 0; x < size; x++) {
        std::cout << std::setw(1) << static_cast<char>(x + 65) << "   ";
    }
    std::cout << "\n\n";
}

void board::reset() {
    // Reset all areas to 0
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++)
            areas[x][y] = 0;
}

bool board::taken(char cords[2]) const{
    // Check if the specified area is taken
    if(areas[static_cast<int>(cords[0])-65][static_cast<int>(cords[1])-49]==0)
        return false;
    else 
        return true;
}

void board::set_mark(char cords[2], char mark){
    // Set mark in the specified area
    areas[static_cast<int>(cords[0])-65][static_cast<int>(cords[1])-49]=mark;
}

char board::get_area(char cords[2]){
    // Get mark from the specified area
    return areas[static_cast<int>(cords[0])-65][static_cast<int>(cords[1])-49];
}

int board::game_result()const{
    // Check for game result (win/loss/draw)
    int pl_counter, ai_counter;

    // Vertical lines
    for (int x = 0; x < size; x++) {
        pl_counter = ai_counter = 1;
        for (int y = 0; y < size - 1; y++) {
            if (areas[x][y] == areas[x][y + 1]) {
                if (areas[x][y] == p1_symbol)
                    pl_counter++;
                else if (areas[x][y] == p2_symbol)
                    ai_counter++;
                if (pl_counter == win)
                    return 1;
                if (ai_counter == win)
                    return -1;
            }
        }
    }
    // Horizontal lines
    for (int y = 0; y < size; y++) {
        pl_counter = ai_counter = 1;
        for (int x = 0; x < size - 1; x++) {
            if (areas[x][y] == areas[x + 1][y]) {
                if (areas[x][y] == p1_symbol)
                    pl_counter++;
                else if (areas[x][y] == p2_symbol)
                    ai_counter++;
                if (pl_counter == win)
                    return 1;
                if (ai_counter == win)
                    return -1;
            }
        }
    }
    // Diagonals (top-left to bottom-right)
    for(int y=0;y<size-win+1;y++){
        pl_counter=ai_counter=1;
        for(int x=0;x<(size-y-1);x++){
            if(areas[x][x+y]==areas[x+1][y+x+1]){
                if(areas[x][x+y]==p1_symbol)
                    pl_counter++;
                else if(areas[x][x+y]==p2_symbol)
                    ai_counter++;
                if(pl_counter==win)
                    return 1;
                if(ai_counter==win)
                    return -1;
            }
        }
    }
    // Diagonals (top-right to bottom-left)
    for(int y=1;y<size-win+1;y++){
        pl_counter=ai_counter=1;
        for(int x=0;x<(size-y-1);x++){
            if(areas[x+y][x]==areas[x+y+1][x+1]){
                if(areas[x+y][x]==p1_symbol)
                    pl_counter++;
                else if(areas[x+y][x]==p2_symbol)
                    ai_counter++;
                if(pl_counter==win)
                    return 1;
                if(ai_counter==win)
                    return -1;
            }
        }
    }
    for(int y=0;y<size-win+1;y++){
        pl_counter=ai_counter=1;
        for(int x=0;x<size-y-1;x++){
            if(areas[size-x-1][x+y]==areas[size-x-2][x+y+1]){
                if(areas[size-x-1][x+y]==p1_symbol)
                    pl_counter++;
                else if(areas[size-x-1][x+y]==p2_symbol)
                    ai_counter++;
                if(pl_counter==win)
                    return 1;
                if(ai_counter==win)
                    return -1;
            }
        }
    }
    for(int y=1;y<size-win+1;y++){
        pl_counter=ai_counter=1;
        for(int x=0;x<size-y-1;x++){
            if(areas[size-x-y-1][x]==areas[size-x-y-2][x+1]){
                if(areas[size-x-y-1][x]==p1_symbol)
                    pl_counter++;
                else if(areas[size-x-y-1][x]==p2_symbol)
                    ai_counter++;
                if(pl_counter==win)
                    return 1;
                if(ai_counter==win)
                    return -1;
            }
        }
    }
    return 0;
}

bool board::full_board(){
    // Check if the board is full
    for(int x=0;x<size;x++){
        for(int y=0;y<size;y++){
            if(areas[x][y]==0){
                return false;
            }
        }
    }
    return true;
}

bool board::occupied(int x, int y){
    // Check if the specified area is occupied
    if(areas[x-1][y-1]==0){
        return false;
    }
    return true;
}

void board::set(int x, int y) {
    // Set mark in the specified area if it's within bounds
    if (x >= 1 && x <= size && y >= 1 && y <= size) {
        if (player_turn())
            areas[x - 1][y - 1] = p1_symbol;
        else
            areas[x - 1][y - 1] = p2_symbol;
    }
}

void board::remove(int x, int y){
    // Remove mark from the specified area if it's within bounds
    if (x >= 1 && x <= size && y >= 1 && y <= size)
            areas[x - 1][y - 1] = 0;
}