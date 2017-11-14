from heapq import heappush, heappop
def availabilities(bob, alice):
    h = []
    for b in bob:
        heappush(h, b)
    for a in alice:
        heappush(h, a)

    e = 0
    free = []
    while h:
        s, ne = heappop(h)
        if e < s:
            free.append((e,s))
        e = ne
    
    if e != 24:
        free.append((e, 24))
    return free

print(availabilities([(3,5), (6,9)], [(10,12)]))


    
