Documentation:

What is this program?
---------------------------
    This is a simulation of some of the actions a slot machine can perform, as well as some imaginary features, such as 
    possibly changing a number in a roll. The program is split into 6 tasks, each performing different operations on a matrix.

    Note: The code contains Romanian notations (variable names and comments).

Tasks:
---------------------------
1.    Pick a column and decide how many times you want to roll it.

2.    Calculate the score for a matrix.

        Score breakdown:
        a. The score is counted only in a 3x3 submatrix from the top-left corner.
  
        b. ‘n’ matching symbols award ‘n’ points; valid when n ≥ 3.
  
        c. A diagonal is worth 7 points.
  
        d. Two diagonals forming an 'X' shape are worth 21 points.

4.    This task combines tasks 1 and 2 by making multiple column rolls and calculating all the winnings.

5.    This task calculates the best possible score by changing one specific symbol in the matrix.

6.    In this task, the program swaps any two columns to obtain the highest score.

7.    This task steps away from gambling. It finds the minimum-cost path from the top-left to the bottom-right of the matrix.
    The cost is determined by the absolute difference between the current cell and the next.

Input:
---------------------------
    The task number
    The number of rows and columns
    The matrix itself
    (Only for tasks 1 and 3): the column number and how many times to rotate it

