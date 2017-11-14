def findWords(board, words):
    try:
        N, M = len(board), len(board[0])
    except: return 0
    words = set(words)
    sol = []

    # Let's build a trie!
    root = {}

    for word in words:
        node = root
        for c in word:
            if c not in node:
                node[c] = {}
            node = node[c]
            
    def dfs(coord, node, path, visited):
        if path in words:
            sol.append(path) 
            words.remove(path)
        x, y = coord
        for nx, ny in [(x+1,y), (x-1,y), (x,y+1), (x,y-1)]:
            if 0 <= nx < N and 0 <= ny < M and (nx, ny) not in visited:
                c = board[nx][ny]
                if c not in node: continue
                visited.add((nx, ny))
                dfs((nx, ny), node[c], path+c, visited)
                visited.remove((nx, ny)) 

    # Now we need to traverse our trie on top of this board:
    for x in range(N):
        for y in range(M):
            if board[x][y] in root:
                dfs((x,y), root[board[x][y]], board[x][y], set([(x,y)]))
    return sol
