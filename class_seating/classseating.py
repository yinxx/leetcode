"""
We want to seat people in the seats 0,...,N.

We want to support:
1. adding a person to the seats
2. removing a person

To do this, we will use a priority queue type data structure.

To add a person to the seats, we'll take the biggest interval : [L,R]
and then remove it, breaking up into 2 smaller intervals : [L,M], [M,R],
and inserting the two smaller intervals into the priority queue.

When we want to merge 2 smaller intervals, we need to remove the elements from
the priority queue(list underneath) that ends at M and starts at M.
"""

from heapq import heappush, heappop
import sys

class Scheduler():
    def __init__(self, N):
        self.N = N
        self.seating = [(-N,0,N)] # We will compare with (N,0,N).
        self.students = {}

    def largestInterval(self):
        """
        returns the largest interval empty seating.
        """
        return -(self.seating[0][0])

    def addStudent(self, student_idx):
        """
        Adds a single student.
        Remove the largest interval.
        """
        _, start, end = heappop(self.seating)
        middle = int((start+end)/2)
        heappush( self.seating, (start-middle, start, middle))
        heappush( self.seating, (middle-end, middle, end))
        self.students[student_idx] = middle

    def removeStudent(self, student_idx):
        """
        Removes a single student.
        """
        middle = self.students[student_idx]
        for i in range(len(self.seating)):
            if self.seating[i][2] == middle:
                start = self.seating[i][1]
                self.seating[i] = (-sys.maxsize, start, middle)
            if self.seating[i][1] == middle:
                end = self.seating[i][2]
                self.seating[i] = (-sys.maxsize, middle, end)
        self.students.pop(student_idx)
        heappop(self.seating)
        heappop(self.seating)
        heappush( self.seating, (start-end, start, end))

if __name__ == "__main__":
    s = Scheduler(10)
    s.addStudent(5)
    print(s.seating)
    s.addStudent(1)
    print(s.seating)
    s.removeStudent(5)
    print(s.seating)
    s.addStudent(2)
    print(s.seating)
    print(s.largestInterval())
