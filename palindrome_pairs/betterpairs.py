def palindromePairs(words):
    words = {word: i for i, word in enumerate(words)}
    ans = set()
    for word in words:
        idx = words[word]
        # S = P + S
        for j in range(len(word)+1):
            prefix = word[:j]
            suffix = word[j:]
            # Palindrome = rev(S) + P + S if palindrome(P)
            if prefix == prefix[::-1]:
                revs = suffix[::-1]
                if revs in words and words[revs] != idx:
                    ans.add((words[revs],  idx))
            # Palindrome = P + S + rev(P) if palindrome(S)
            if suffix == suffix[::-1]:
                revp = prefix[::-1]
                if revp in words and words[revp] != idx:
                    ans.add((idx, words[revp]))
    return list(ans)
