#include "ai.h"

#include <climits>

int ai::minimax(board board, int depth, int alpha, int beta, bool maximizingPlayer) {
     // Check if the game has reached a terminal state or the depth limit
    int game_state = board.game_result();
    int size = board.get_size();
    if(game_state!=0 || board.full_board() || depth==0){
	
		return game_state;
	}
    if (maximizingPlayer) {
        int maxScore = -INT_MAX;

        // Iterate over each possible move
        for (int i=1; i < size+1; i++) {
            for (int j = 1; j < size+1; j++) {
                if (!board.occupied(i,j)) {
                    board.change_turn(1);
					board.set(i,j);
                    int currentScore = minimax(board, depth - 1, alpha, beta, false);
                    board.remove(i,j);
                    maxScore = std::max(maxScore, currentScore);
                    alpha = std::max(alpha, maxScore);
                    if (beta <= alpha)
                        return alpha;
                }
            }
        }
        
        return maxScore;
    } else {
        int minScore = INT_MAX;

        // Iterate over each possible move
        for (int i = 1; i < size+1; i++) {
            for (int j = 0; j < size+1; j++) {
                if (!board.occupied(i,j)) {
                    board.change_turn(0);
					board.set(i,j);
                    int currentScore = minimax(board, depth - 1, alpha, beta, true);
                    board.remove(i,j);
                    minScore = std::min(minScore, currentScore);
                    beta = std::min(beta, minScore);
                    if (beta <= alpha)
                        return beta;
                }
            }
        }
        
        return minScore;
    }
}

void ai::move(board board) {
    int current, best = INT_MAX;
    // Iterate over each possible move
    for (int i = 1; i < board.get_size() + 1; i++) 
        for (int j = 1; j < board.get_size() + 1; j++) 
            if (!board.occupied(i, j)){
                board.change_turn(0);
                board.set(i, j);
                // Find the best move using minimax algorithm
                current = minimax(board, depth, -INT_MAX, INT_MAX, true);
                board.remove(i, j);
                if (current < best){
                    x = i;
                    y = j;
                    best = current;
                }
            }
}