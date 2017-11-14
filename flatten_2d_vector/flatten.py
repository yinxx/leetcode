from itertools import tee

class Vector2D(object):

    def __init__(self, vec2d):
        """
        Initialize your data structure here.
        :type vec2d: List[List[int]]
        """
        self.list = vec2d
        self.cur = 0
        self.iter = iter(vec2d[0]) if len(vec2d) else iter(vec2d)

    def next(self):
        """
        :rtype: int
        """
        while True:
            try:
                return next(self.iter)
            except StopIteration as e: # No more elements.
                self.cur += 1
                if self.cur >= len(self.list):
                    raise StopIteration()
                self.iter = iter(self.list[self.cur])

    def hasNext(self):
        """
        :rtype: bool
        """
        # Save the states to revert
        origiter, self.iter = tee(self.iter)
        cur = self.cur
        try:
            self.next()
            self.iter = origiter
            self.cur = cur
            return True
        except StopIteration as e:
            self.iter = origiter
            self.cur = cur
            return False
