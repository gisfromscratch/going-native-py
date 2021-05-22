from datetime import datetime
import numpy as np
import unittest

# pip install memory_profiler
#from memory_profiler import profile

from algorithm import count, count_arr, count_lt, read_tuples

class TestAlgorithmMethods(unittest.TestCase):

    def test_count(self):
        integers = [1, 2, 3, 4, 5, 1, 7]
        self.assertEqual(2, count(integers, 1), 'The list contains two elements being 1!')
        floats = [1.1, 2.2, 3.3, 1.1, 2.3]
        self.assertEqual(2, count(floats, 1.1), 'The list contains two elements being 1.1!')
        strings = ['Dessau', 'Durchwehna', 'Leipzig', 'Bonn', 'Dessau']
        self.assertEqual(2, count(strings, 'Dessau'), 'The list contains two elements being \'Dessau\'!')
        dates = [datetime(1981, 5, 23), datetime(2013, 7, 17), datetime(1981, 5, 23)]
        self.assertEqual(2, count(dates, datetime(1981, 5, 23)), 'The list contains two elements being the 23th of May in the year 1981!')

    def test_count_lt(self):
        integers = [1, 2, 3, 4, 5, 1, 7]
        self.assertEqual(2, count_lt(integers, 2), 'The list contains two elements being less than 2!')
        floats = [1.1, 2.2, 3.3, 1.1, 2.3]
        self.assertEqual(2, count_lt(floats, 2.2), 'The list contains two elements being less than 2.2!')
        strings = ['Dessau', 'Durchwehna', 'Leipzig', 'Bonn', 'Dessau']
        self.assertEqual(1, count_lt(strings, 'Dessau'), 'The list contains one element being less than \'Dessau\'!')
        dates = [datetime(1981, 5, 23), datetime(2013, 7, 17), datetime(1981, 5, 23)]
        self.assertEqual(0, count_lt(dates, datetime(1981, 5, 23)), 'The list contains no element being less than the 23th of May in the year 1981!')

    def test_read_tuples(self):
        row = (1, 51.83864, 12.24555, 'Dessau', datetime(1981, 5, 23))
        rows = [row]
        count = len(rows)
        self.assertEqual(count, read_tuples(rows), 'Not all rows were read!')


    #@profile
    @unittest.skip('Six million dollar skip!')
    def test_count_lee_majors(self):
        size = int(6e7)
        integers = [dollar for dollar in range(size)]
        self.assertEqual(1, count(integers, 0), 'The count is wrong!')
        #self.assertEqual(1, count_arr(integers, 0), 'The count is wrong!')

if __name__ == '__main__':
    unittest.main()
