#pragma once
#include <vector>


class board{
    int size;
    int win;
    bool turn;
    char p1_symbol, p2_symbol;
    std::vector<std::vector<char>> areas;
     


    public:
    board(){};  
    board(int size, int win, char player);
    void print() const;  
    void reset();
    bool taken(char cords[2]) const;
    void set_mark(char cords[2], char mark);
    char get_area(char cords[2]);
    int game_result()const;
    bool full_board();
    bool occupied(int x, int y);
    int get_size(){return size;};
    bool player_turn(){return turn;}	
    void set(int x, int y);
	void remove(int x, int y);
    void change_turn(bool player){player ? turn =1 : turn=0;}
    void set_turn(bool whose_turn){turn = whose_turn;}
    char get_p1_symbol(){return p1_symbol;}
	char get_p2_symbol(){return p2_symbol;}

};