# Tic Tac Toe
Single player Tic-Tac-Toe in C

Recurrence defining the number of function calls for find_move(), where n is the number of empty squares. Ignores the fact that the function returns from winning configurations, and also returns if guaranteed win is found. This is the total number of moves in every possible remaining sequence of moves (+1 for initial function call). <br>
T(0) = 1 <br>
T(n) = n*T(n-1) + 1
