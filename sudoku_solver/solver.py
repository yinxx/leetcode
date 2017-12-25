"""
Oh god why am I doing these annoying questions

Sudoku has 2 restrictions: Only 1 unique number in each row, column, and cube.

This is just brute force recursion, but the recursion scheme is a little difficult by itself.
"""
import copy
import numpy as np
N = 9
BLOCKS = N//3
def sudokusolver(board):
    """
    board is 9x9 always, and has character '.' for empty, fill-able cells.
    We can keep a 3 lists of hashsets:
    rows[i] = hashset of numbers in i-th row
    columns[j] = hashset of numbers in j-th column
    block[i][j] = hashset of numbers in i,j-th block
    """
    rows = [set() for _ in range(N)]
    cols = [set() for _ in range(N)]
    blocks = [[set() for _ in range(BLOCKS)] for _ in range(BLOCKS)]
    
    for i in range(N):
        for j in range(N):
            if board[i][j] != '.':
                rows[i].add(board[i][j])
                cols[j].add(board[i][j])
                blocks[i//BLOCKS][j//BLOCKS].add(board[i][j])
    b = copy.deepcopy(board)
    def f(n):
        """
        We keep a recursive formulation:
        f(n) means we already solved up to n/N-th row, and we're on the n%N-th column.
        """
        if n == N*N: 
            return b
        i, j = n//N, n%N
        if board[i][j] != '.':
            return f(n+1)
        for c in range(1,10):
            c = str(c)
            if c in (rows[i] | cols[j] | blocks[i//BLOCKS][j//BLOCKS]): 
                continue
            b[i][j] = c
            rows[i].add(c)
            cols[j].add(c)
            blocks[i//BLOCKS][j//BLOCKS].add(c)
            cur = f(n+1)
            if cur:
                return cur
            rows[i].remove(c)
            cols[j].remove(c)
            blocks[i//BLOCKS][j//BLOCKS].remove(c)
        b[i][j] = board[i][j]
        return None
    return f(0) 

board = [[".",".","9","7","4","8",".",".","."],["7",".",".",".",".",".",".",".","."],[".","2",".","1",".","9",".",".","."],[".",".","7",".",".",".","2","4","."],[".","6","4",".","1",".","5","9","."],[".","9","8",".",".",".","3",".","."],[".",".",".","8",".","3",".","2","."],[".",".",".",".",".",".",".",".","6"],[".",".",".","2","7","5","9",".","."]]

res = sudokusolver(board)

print(np.array(res))
