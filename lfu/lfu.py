"""

The least frequently used cache will evict any element that has been accessed the least so far.

If there are multiple keys that have the same frequency, then the least recently used key would be evicted.

For example:

p(1,1) 1:1
p(2,2) 1:1, 2:1
g(1)   1:2, 2:1
p(3,3) 1:2, 3:1 <- 2:1 gets evicted
g(2) <- -1 not found
g(3) <- 3:2, 1:2
p(4,4) <- evicts 1:2
...

The approach would be to implement a doubly linked list for the recent-ness of the cache,
and additionally, we want to evict the least frequently used, which means we need some kind of
sorted book-keeping.

When we put(k,v), we need to associate the key with a frequency. When we put an element its frequency is always 1.
There could be elements of frequency > 1, thus we have to insert the frequencies in their own buckets.

To do this, we have a dictionary that maps:

{ frequency : linkedlist roots }

We can keep track of a minfreq = 0 initialized.
"""

from collections import deque, OrderedDict as odict, defaultdict as ddict
import sys

class LFUCache(object):
    def __init__(self, capacity):
        """
        We will instantiate the following:
        self.deques : {frequency -> deque}
        self.nodedict : {key -> (value, frequency)}
        :type capacity: int
        """
        self.deques = ddict(odict)
        self.nodedict = {}
        self.capacity = capacity
        self.size = 0
        self.minfreq = sys.maxsize
   
    def updatefreq(self):
        """
        Checks to see if minfreq should be updated based on
        state of the minimum frequency dictionary.

        :rtype: void
        """
        if len(self.deques[self.minfreq]) == 0:
            self.minfreq += 1 # The frequency can change by at most 1.

    def evictmin(self):
        """
        Evicts the lowest frequency.
        If unsuccessful, then don't do anything and return False.

        :rtype: bool
        """
        ldict = self.deques[self.minfreq]
        if not len(ldict):
            return False
        remove = next(iter(ldict))
        ldict.pop(remove)
        self.nodedict.pop(remove)
        self.updatefreq()
        return True

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        # If key is not in nodedict, then we just return -1.
        if key not in self.nodedict: return -1

        value, freq = self.nodedict[key] 
        self.deques[freq].pop(key)
        self.deques[freq + 1][key] = value
        self.nodedict[key] = (value, freq + 1)
        self.updatefreq() 
        return value

    def put(self, key, value):
        """
        When we want to insert a node, we will set minfreq ALWAYS to 1.
        And then, we will add the new node into the back of deques[1].

        :type key: int
        :type value: int
        :rtype: void
        """
        # Case 1: Key is already inside nodedict.
        # We have to set the value since key is present
        # and increment the frequency.
        if key in self.nodedict:
            self.nodedict[key] = (value, self.nodedict[key][1]) # preserve prev freq
            self.get(key)
        # Case 2: Key is new.
        # We have to, by default, insert a new record into frequency 1's bin.
        else:
            # Now, we need to evict 1 value if we create a new
            # record and the capacity is reached.
            self.size += 1
            if self.size > self.capacity:
                if not self.evictmin(): return
            self.deques[1][key] = value 
            self.nodedict[key] = (value, 1)
            self.minfreq = 1
        
if __name__ == "__main__":
    cache = LFUCache(3)
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);       # returns 1
    cache.put(3, 3);    # evicts key 2
    cache.get(2);       # returns -1 (not found)
    cache.get(3);       # returns 3.
    cache.put(4, 4);    # evicts key 1.
    cache.get(1);       # returns -1 (not found)
    cache.get(3);       # returns 3
    cache.get(4);       # returns 4
