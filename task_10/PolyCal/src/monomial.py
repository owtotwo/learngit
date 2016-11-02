#!/usr/bin/env python
#-*- coding:utf-8 -*-

"""Monomial Expression Class"""

import unittest


__author__ = 'sysu_AT'


class Monomial(object):
    """Base monomial class.
    
    The main class in this module.
    """

    def __init__(self):
        raise NotImplementedError


class SimpleTest(unittest.TestCase):
    """A small unit test for this module."""

    def test_normal(self):
        raise NotImplementedError

    def test_float(self):
        raise NotImplementedError


if __name__ == '__main__':
    unittest.main()
