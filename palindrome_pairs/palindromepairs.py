"""
Palindrome Pairs

The naive brute force:
    check whether each pair is a palindrome, takes O(S) for each pair,
    and we do this O(N^2) times, so total is O(N^2*S).

The better way: tries
    Take each word, construct a trie with the word, and then try to traverse the trie
    with the opposite of its word. If it completely consumes, then check if there's any subtree below
    that is also a palindrome of itself.
    This takes O(S) time to traverse, and then we will check the rest of the subtree to see if
    any one of them are palindromes.

    Traverse down rev(S), then we have rev(S) + s'.

    rev(S) + s' + S = palindrome iff s' is a palindrome.
    
    Time complexity: ???
"""


def palindrome_pairs(words):
    """
    :type words: List[str]
    :rtype: List[List[int]]
    """
    sorted_words = sorted(words)
    words = {word:k for k, word in enumerate(words)}
    root = {} 
    ans = []
    def fill_trie(word):
        node = root
        for c in word:
            if c not in node:
                node[c] = {}
            node = node[c]
        return node
    # First, we traverse to the word, 
    # and then we return the node.
    # If there is none, then we return None.
    def traverse_trie(word):
        node = root
        for c in word:
            if c not in node:
                return None
            node = node[c]
        return node

    def palindromic_postfix(node, prefix, postfix, res):
        if prefix+postfix in words and postfix == postfix[::-1]:
            res.add(prefix+postfix)
        for c in node:  
            palindromic_postfix(node[c], prefix, postfix+c, res)

    for i, word in enumerate(sorted_words):
        node = fill_trie(word)
        revword = word[::-1]
        revnode = traverse_trie(revword)
        if revnode is None: continue
        curres = set()
        palindromic_postfix(revnode, revword, "", curres)
        for p in curres:
            ans.append([i, words[p]])
    return ans
