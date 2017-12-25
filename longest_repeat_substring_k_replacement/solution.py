from collections import deque, defaultdict

def char_replacement(s, k):
    """
    Check how many characters in total - greatest_frequency. If greater than k, need to retract back of deque
    """
    d = deque()
    f = defaultdict(int)
    maxlen = 0

    def scan_chars():
        total_freq, max_char, max_freq = 0, None, 0
        for l in f:
            if max_freq < f[l]:
                max_char = l
                max_freq = f[l]
            total_freq += f[l] 
        return (total_freq, max_char, max_freq)

    for c in s:
        f[c] += 1
        d.append(c) 
        total_freq, max_char, max_freq = scan_chars()
        while len(d) and total_freq - max_freq > k: 
            f[d.popleft()] -= 1
            total_freq, max_char, max_freq = scan_chars()
        maxlen = max(maxlen, len(d)) 
    return maxlen
    
print(char_replacement("ABABBBBD", 2))
