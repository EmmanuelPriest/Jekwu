#!/usr/bin/python3

'''Module to test add2.py'''


import unittest
'''Importing python builtin module'''

from add2 import add
'''Importing add method from add2.py'''

class CheckAdd(unittest.TestCase):
    '''Creating subclass of unittest'''

    def test_list_int(self):
        '''Method to test int in a list'''

        data = [1, 2, 3]
        result = add(data)
        self.assertEqual(result, 6)


if __name__ == "__main__":
    '''The main module'''
    unittest.main()
