#!/usr/bin/python3
'''Addition of numbers'''


def test_add():
    '''Finding sum of numbers'''
    assert sum([2, 3, 5]) == 10, "Should be 10"

def test_add_tuple():
    '''Finding sum of tupple'''
    if sum((1, 3, 5)) != 10:
        raise AssertionError("Must not be equal")
    assert sum((1, 3, 5)) == 10, "It should be 10"

if __name__ == "__main__":
    '''The main function'''
    test_add()
    test_add_tuple()
    print("Everything is correct")
