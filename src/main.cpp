#include <iostream>

#include "board.h"
#include "ai.h"

// Function to create an AI object with a specified maximum recursion depth
ai make_ai(){
	int max_depth;
	do{
		std::cout << "Maximum recursion depth: \n";
		std::cin >> max_depth;
		if(max_depth <= 0)
			std::cout << "Minimum recursion depth is 1. Please enter again. \n";
	}while(max_depth <= 0);
	ai Ai(max_depth);
	return Ai;
}

// Function to create a board object with user input for size, winning condition, and player symbol
board make_board(){
	int size, to_win;
	char p1 = 0;

	std::cout << "Enter the desired size of the tic-tac-toe board: \n";
	do{
		std::cin >> size;
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		if(size < 3)
			std::cout << "Minimum board size for tic-tac-toe is 3x3! Please enter a larger size: \n";
		if(size > 9)
			std::cout << "Maximum board size for tic-tac-toe is 9x9! Please enter a smaller size: \n";
	} while (size < 3 || size > 9);

	std::cout << "Enter the desired number of marks required to win: \n";
	do{
		std::cin >> to_win;
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		if(to_win > size)
			std::cout << "The number of marks required to win cannot be greater than the board size! Please enter a smaller number: \n";
		else if(to_win < 2)
			std::cout << "The number of marks required to win cannot be less than 2! Please enter a larger number: \n";
	} while (to_win > size || to_win < 2);

	std::cout << "Enter the desired symbol (x|o): \n";
	do{
		std::cin >> p1;
		std::cin.clear();
		std::cin.ignore(1024, '\n');
		if(!(p1 == 'o' || p1 == 'x'))
			std::cout << "Invalid symbol! Please choose a valid symbol (x|o):\n";
	}while(!(p1 == 'o' || p1 == 'x'));

	board table(size, to_win, p1);
	return table;
}

// Function to display the winner or a draw
void win_condition(board table){
	if (table.full_board() && table.game_result() == 0)
		std::cout << "Draw!\n";
	else if (table.game_result() != 0) {
		std::cout << "Game over! The winner is ";
		if (!table.player_turn())
			std::cout << "Player (" << table.get_p1_symbol() << ")\n";
		else
			std::cout << "Computer (" << table.get_p2_symbol() << ")\n";
	}
	std::cout << '\n';
}

// Function for player's choice of coordinates
std::vector<int> pl_choise(board table){
	int x, y;
    char chosen[2];
    int size = table.get_size();
	do{
		do{
            std::cin >> chosen ;
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            if(!(static_cast<int>(chosen[0]) > 64 && static_cast<int>(chosen[0]) < (65 + size))){
                std::cout << "Invalid column! Please choose a column within the range A-" << static_cast<char>(64 + size) << '!' << std::endl;
            }
            if(!(static_cast<int>(chosen[1]) > 48 && static_cast<int>(chosen[1]) < (49 + size))){
                std::cout << "Invalid row! Please choose a row within the range 1-" << static_cast<char>(48 + size) << '!' << std::endl;
            }
            if((!(static_cast<int>(chosen[1]) > 48 && static_cast<int>(chosen[1]) < (49 + size))) || (!(static_cast<int>(chosen[0]) > 64 && static_cast<int>(chosen[0]) < (65 + size)))){
                std::cout << "Choose a field to place your mark: \n";
            }
        } while(!((static_cast<int>(chosen[0]) > 64 && static_cast<int>(chosen[0]) < (65 + size))) && (static_cast<int>(chosen[1]) > 48 && static_cast<int>(chosen[1]) < (49 + size)));
		if(table.taken(chosen)){
			std::cout <<"The chosen field " << chosen << " is already taken. Choose another field!\n";
		}
	}while (table.taken(chosen));
    x = static_cast<int>(chosen[0]) - 64;
    y = static_cast<int>(chosen[1]) - 48;
	std::vector<int> coords;
	coords.push_back(x);
	coords.push_back(y);
	return coords;
}

// Function to handle the game between player and AI
void game_ai(board table){
	ai AI = make_ai();
	std::vector<int> coords;
	int chosen_turn;
	do{
		std::cout << "Who starts? 1 - player / 2 - computer. \n";
		std::cin >> chosen_turn;
		if(chosen_turn == 1)
			table.set_turn(1);
		else if(chosen_turn == 2)
			table.set_turn(0);
		else
			std::cout << "Invalid choice. Please enter 1 or 2.\n";
	}while(!(chosen_turn == 1) || !(chosen_turn == 2));

	table.reset();
	table.print();

	while(table.game_result() == 0 && !table.full_board()){
		if(table.player_turn()){
			std::cout << "Your turn.\n";
        	std::cout << "Choose a field using uppercase letters and numbers without spaces. \n";
			coords = pl_choise(table);
			table.set(coords[0], coords[1]);
        	table.change_turn(0);
		}else{
			std::cout << "Computer is making a move... \n";
			AI.move(table);
			table.set(AI.getx(), AI.gety());
			table.change_turn(1);
		}
		table.print();
		win_condition(table);
	}
}

int main(){
	board table = make_board();
	game_ai(table);
}
