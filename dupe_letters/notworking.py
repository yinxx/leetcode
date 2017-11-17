"""
The idea of the problem is we want the lowest lexicographical ordering
of letters after we remove duplicates.

The core of the algorithm is the idea of **promoting**.

Promoting is when we can move an index of a specific letter to a new index.

In the below scenario, we have:

    ... ci, ..., cj, ...

Suppose c1 == c2, then we can move from the choice of c1 to c2 **greedily** if
there are no letters ck, k in (i,j) such that ci < ck.

If we have:

    ci > ck for all k, then we can definitely put ci over to cj and get a lower lex ordering.
    We would also preserve the invariant of a single ci letter.


"""
from string import ascii_lowercase
def remove_dupe(s):
    m = {}

    def promote(c, end):
        """
        To promote, we will take the max shift we can possibly make til end.
        A shift is where ci == cj, i < j <= end, and m[c] = ci, then we assign
        m[c] = cj instead.
        """
        cur = maxshift = m[c]
        valid = False
        while cur <= end:
            if s[cur] == c and valid:
                maxshift = cur
                valid = False
            elif m[s[cur]] == cur:
                if s[cur] < c:
                    valid = True   
                if s[cur] > c and not valid:
                    return maxshift
            cur += 1
        return maxshift
   
    for i, c in enumerate(s):
        if c not in m:
            m[c] = i
            continue
        end = promote(c, i)
        if end == i:
            m[c] = end
            for nc in ascii_lowercase:
               if nc >= c: break
               if nc not in m: continue
               m[nc] = promote(nc, i)
    s = sorted(list([(k,m[k]) for k in m]), key = lambda x : x[1])
    return "".join([v[0] for v in s])
        

if __name__ == "__main__":
    s = "eywdgenmcnzhztolafcfnirfpuxmfcenlppegrcalgxjlajxmphwidqqtrqnmmbssotoywfrtylm"
    print(s)
    print(remove_dupe(s))

