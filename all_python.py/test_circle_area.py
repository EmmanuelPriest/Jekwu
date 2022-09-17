#!/usr/bin/python3

'''Module to test circle_area.py'''


import unittest
'''importing python builtin test module'''
from circle_area import circle_area
'''importing circle_area method from circle_area.py'''
from math import pi
'''importing math module'''

class TestCircleArea(unittest.TestCase):
    '''Creating subclass from unittest'''
    def test_area(self):
        # Test area when radius >= 0
        self.assertAlmostEqual(circle_area(1), pi)
        self.assertAlmostEqual(circle_area(0), 0)
        self.assertAlmostEqual(circle_area(2.1), (pi * (2.1 ** 2)))

    def test_values(self):
        # Make sure value errors are raised when necessary
        self.assertRaises(valueError, circle_area, -2)

    def test_types(self):
        # Make sure type errors are raised when necessary
        self.assertRaises(TypeError, circle_area, 2 + 5j)
        self.assertRaises(TypeError, circle_area, True)
        self.assertRaises(TypeError, circle_area, "radius")
