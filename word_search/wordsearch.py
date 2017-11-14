"""
To find these words, we should go one by one
and perform a breadth first search on the board.
"""

def find_words(board, words):
    try:    
        N, M = len(board), len(board[0])
    except: return 0
    words = list(set(words))
    sol = [] 
    
    def dfs(word, coord, idx, visited):
        x, y = coord[0], coord[1]
        if idx == len(word)-1:
            return True
        for nx, ny in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
            if 0 <= nx < N and 0 <= ny < M and (nx, ny) not in visited and board[nx][ny] == word[idx+1]:
                visited.add((nx, ny))
                if dfs(word, (nx, ny), idx+1, visited):
                    return True
                visited.remove((nx, ny))
        return False

    def add(word):
        if not word:
            sol.append(word)
            return
        for x in range(N):
            for y in range(M):
                if board[x][y] == word[0] and dfs(word, [x,y], 0, set([(x,y)])):
                    sol.append(word)
                    return
    
    for word in words:
        add(word)
    return sol

