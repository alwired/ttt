# Tic-Tac-Toe
Single player Tic-Tac-Toe in C

Recurrence defining the upper bound for the number of times find_move() is called, where n is the number of empty squares. This is equal to the total number of moves in every remaining sequence of moves (+1 for initial function call). The actual number is lower because the game can end early if either player wins, and also because the function returns after finding a guaranteed win. <br><br>
T(0) = 1 <br>
T(n) = n*T(n-1) + 1

