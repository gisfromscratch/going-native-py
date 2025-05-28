from datetime import datetime
import numpy as np
import unittest

# pip install memory_profiler
#from memory_profiler import profile

from algorithm import count, count_arr, count_lt, read_tuples, reverse, sort, accumulate, min_element, max_element

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

    def test_reverse(self):
        integers = [1, 2, 3, 4, 5]
        self.assertEqual([5, 4, 3, 2, 1], reverse(integers), 'The reversed integer list should be [5, 4, 3, 2, 1]!')
        floats = [1.1, 2.2, 3.3]
        expected_floats = [3.3, 2.2, 1.1]
        result_floats = reverse(floats)
        # Check each element with tolerance for floating point comparison
        for i, (expected, actual) in enumerate(zip(expected_floats, result_floats)):
            self.assertAlmostEqual(expected, actual, places=5, msg=f'Float reverse mismatch at index {i}')
        strings = ['Dessau', 'Berlin', 'Leipzig']
        self.assertEqual(['Leipzig', 'Berlin', 'Dessau'], reverse(strings), 'The reversed string list should be [\"Leipzig\", \"Berlin\", \"Dessau\"]!')
        dates = [datetime(1981, 5, 23), datetime(2013, 7, 17), datetime(2023, 1, 1)]
        expected_dates = [datetime(2023, 1, 1), datetime(2013, 7, 17), datetime(1981, 5, 23)]
        self.assertEqual(expected_dates, reverse(dates), 'The reversed date list should be properly reversed!')

    def test_sort(self):
        integers = [5, 2, 8, 1, 9, 3]
        self.assertEqual([1, 2, 3, 5, 8, 9], sort(integers), 'The sorted integer list should be [1, 2, 3, 5, 8, 9]!')
        floats = [3.3, 1.1, 2.2, 4.4]
        expected_floats = [1.1, 2.2, 3.3, 4.4]
        result_floats = sort(floats)
        # Check each element with tolerance for floating point comparison
        for i, (expected, actual) in enumerate(zip(expected_floats, result_floats)):
            self.assertAlmostEqual(expected, actual, places=5, msg=f'Float sort mismatch at index {i}')
        strings = ['zebra', 'apple', 'banana', 'cherry']
        self.assertEqual(['apple', 'banana', 'cherry', 'zebra'], sort(strings), 'The sorted string list should be alphabetical!')
        dates = [datetime(2023, 1, 1), datetime(1981, 5, 23), datetime(2013, 7, 17)]
        expected_dates = [datetime(1981, 5, 23), datetime(2013, 7, 17), datetime(2023, 1, 1)]
        self.assertEqual(expected_dates, sort(dates), 'The sorted date list should be chronological!')

    def test_accumulate(self):
        integers = [1, 2, 3, 4, 5]
        self.assertEqual(15, accumulate(integers, 0), 'The sum of [1, 2, 3, 4, 5] starting from 0 should be 15!')
        self.assertEqual(25, accumulate(integers, 10), 'The sum of [1, 2, 3, 4, 5] starting from 10 should be 25!')
        floats = [1.1, 2.2, 3.3]
        expected_sum = 6.6
        result_sum = accumulate(floats, 0.0)
        self.assertAlmostEqual(expected_sum, result_sum, places=5, msg='Float accumulate should work correctly')
        # Test empty list
        self.assertEqual(42, accumulate([], 42), 'Accumulate of empty list should return initial value!')

    def test_min_max_element(self):
        integers = [5, 2, 8, 1, 9, 3]
        self.assertEqual(1, min_element(integers), 'The minimum of [5, 2, 8, 1, 9, 3] should be 1!')
        self.assertEqual(9, max_element(integers), 'The maximum of [5, 2, 8, 1, 9, 3] should be 9!')
        
        floats = [3.3, 1.1, 2.2, 4.4]
        self.assertAlmostEqual(1.1, min_element(floats), places=5, msg='Float min_element should work correctly')
        self.assertAlmostEqual(4.4, max_element(floats), places=5, msg='Float max_element should work correctly')
        
        strings = ['zebra', 'apple', 'banana', 'cherry']
        self.assertEqual('apple', min_element(strings), 'The minimum string should be "apple"!')
        self.assertEqual('zebra', max_element(strings), 'The maximum string should be "zebra"!')
        
        dates = [datetime(2023, 1, 1), datetime(1981, 5, 23), datetime(2013, 7, 17)]
        self.assertEqual(datetime(1981, 5, 23), min_element(dates), 'The minimum date should be 1981-05-23!')
        self.assertEqual(datetime(2023, 1, 1), max_element(dates), 'The maximum date should be 2023-01-01!')
        
        # Test exception for empty list
        with self.assertRaises(RuntimeError):
            min_element([])
        with self.assertRaises(RuntimeError):
            max_element([])

    def test_read_tuple(self):
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

    @unittest.skip('Six million dollar skip!')
    def test_read_tuples_lee_majors(self):
        row = (1, 51.83864, 12.24555, 'Dessau', datetime(1981, 5, 23))
        size = int(6e7)
        rows = [row for _ in range(size)]
        count = len(rows)
        self.assertEqual(count, read_tuples(rows), 'Not all rows were read!')

if __name__ == '__main__':
    unittest.main()
