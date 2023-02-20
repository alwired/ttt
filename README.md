# Tic-Tac-Toe
Single player Tic-Tac-Toe in C

# How to play: 
Download tictactoe.exe and run it in your command line.

# How it works:

Game board states are implemented with bitboards. A string of 9 bits can represent the presence of moves on the board. This means that determining if the board is full or if a player has won is as simple as checking if it's equal to a value. For example, a full board is 0b111111111 = 511. After the player enters a move, the computer will do a brute force search to find the best move.

# Move search
The function find_move() is an implementation of the negamax algorithm. A recurrence defining the upper bound for the number of times find_move() is called, where n is the number of empty squares is given by

$$T(0) = 1$$  
$$T(n) = n*T(n-1) + 1$$  

This is equal to the total number of moves in every remaining sequence of moves (+1 for initial function call). The actual number is lower because the game will end early if either player wins, and also because the function returns after finding a guaranteed win. This is equivalent to the sum  

$$\sum_{i=0}^{n} = \frac{n!}{(n-i)!}$$

So this algorithm has $O(n!)$ time complexity, which is very slow, but inconsequential for this game's speed. 
