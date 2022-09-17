#!/usr/bin/python3

'''Testing module for add.py'''


import unittest
'''importing python builtin module'''

class TestingAdd(unittest.TestCase):
    '''Creating subclass to unittest'''

    def test_add(self):
        '''Testing test_add method'''
        self.assertEqual(sum([2, 3, 5]), 10, "Shoult be 10")
    def test_add_tuple(self):
        '''testing test_add_tuple'''
        self.assertEqual(sum((1, 3, 5)), 10, "It should be 10")


if __name__ == "__main__":
    '''The main method'''
    unittest.main()
