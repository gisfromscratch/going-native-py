from datetime import datetime
#import numpy as np
import unittest

# pip install memory_profiler
#from memory_profiler import profile

from algorithm import count, count_arr, count_lt, read_tuples, reverse, sort, accumulate, min_element, max_element, transform_square, transform_abs, transform_sqrt, transform_toupper, transform_tolower, unique, binary_search, nth_element, set_union, set_intersection, set_difference, includes, partition_less_than, rotate_left

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

    def test_transform_functions(self):
        # Test transform_square
        integers = [1, -2, 3, -4, 5]
        self.assertEqual([1, 4, 9, 16, 25], transform_square(integers), 'Transform square should work for integers!')
        floats = [1.0, -2.0, 3.0]
        expected_floats = [1.0, 4.0, 9.0]
        result_floats = transform_square(floats)
        for i, (expected, actual) in enumerate(zip(expected_floats, result_floats)):
            self.assertAlmostEqual(expected, actual, places=5, msg=f'Float square mismatch at index {i}')
        
        # Test transform_abs
        negative_ints = [1, -2, 3, -4, 5]
        self.assertEqual([1, 2, 3, 4, 5], transform_abs(negative_ints), 'Transform abs should work for integers!')
        negative_floats = [1.5, -2.5, 3.5, -4.5]
        expected_abs_floats = [1.5, 2.5, 3.5, 4.5]
        result_abs_floats = transform_abs(negative_floats)
        for i, (expected, actual) in enumerate(zip(expected_abs_floats, result_abs_floats)):
            self.assertAlmostEqual(expected, actual, places=5, msg=f'Float abs mismatch at index {i}')
        
        # Test transform_sqrt
        sqrt_input = [1.0, 4.0, 9.0, 16.0, 25.0]
        expected_sqrt = [1.0, 2.0, 3.0, 4.0, 5.0]
        result_sqrt = transform_sqrt(sqrt_input)
        for i, (expected, actual) in enumerate(zip(expected_sqrt, result_sqrt)):
            self.assertAlmostEqual(expected, actual, places=5, msg=f'Sqrt mismatch at index {i}')
        
        # Test string transforms
        mixed_case = ['Hello', 'WORLD', 'PyThOn']
        self.assertEqual(['HELLO', 'WORLD', 'PYTHON'], transform_toupper(mixed_case), 'Transform toupper should work!')
        self.assertEqual(['hello', 'world', 'python'], transform_tolower(mixed_case), 'Transform tolower should work!')

    def test_unique(self):
        # Test with integers (adjacent duplicates)
        integers = [1, 1, 2, 2, 3, 1, 2]  # Note: unique only removes adjacent duplicates
        self.assertEqual([1, 2, 3, 1, 2], unique(integers), 'Unique should remove only adjacent duplicates!')
        
        # Test with sorted integers
        sorted_integers = [1, 1, 1, 2, 2, 3, 3, 3]
        self.assertEqual([1, 2, 3], unique(sorted_integers), 'Unique should work well with sorted data!')
        
        # Test with strings
        strings = ['a', 'a', 'b', 'b', 'c', 'c']
        self.assertEqual(['a', 'b', 'c'], unique(strings), 'Unique should work with strings!')
        
        # Test with no duplicates
        no_duplicates = [1, 2, 3, 4, 5]
        self.assertEqual([1, 2, 3, 4, 5], unique(no_duplicates), 'Unique should not change list without adjacent duplicates!')

    def test_binary_search(self):
        # Test with sorted integers
        sorted_integers = [1, 3, 5, 7, 9, 11, 13]
        self.assertTrue(binary_search(sorted_integers, 5), 'Binary search should find existing element!')
        self.assertTrue(binary_search(sorted_integers, 1), 'Binary search should find first element!')
        self.assertTrue(binary_search(sorted_integers, 13), 'Binary search should find last element!')
        self.assertFalse(binary_search(sorted_integers, 6), 'Binary search should not find non-existing element!')
        self.assertFalse(binary_search(sorted_integers, 0), 'Binary search should not find element smaller than minimum!')
        self.assertFalse(binary_search(sorted_integers, 15), 'Binary search should not find element larger than maximum!')
        
        # Test with sorted strings
        sorted_strings = ['apple', 'banana', 'cherry', 'date']
        self.assertTrue(binary_search(sorted_strings, 'banana'), 'Binary search should work with strings!')
        self.assertFalse(binary_search(sorted_strings, 'grape'), 'Binary search should not find non-existing string!')
        
        # Test with empty list
        self.assertFalse(binary_search([], 5), 'Binary search on empty list should return False!')

    def test_nth_element(self):
        values = [9, 2, 5, 1, 8, 3, 7, 4, 6]
        
        # Test finding minimum (0th element)
        self.assertEqual(1, nth_element(values, 0), 'nth_element should find minimum (0th element)!')
        
        # Test finding median (middle element)
        self.assertEqual(5, nth_element(values, 4), 'nth_element should find median (4th element in 0-indexed)!')
        
        # Test finding maximum (last element)
        self.assertEqual(9, nth_element(values, 8), 'nth_element should find maximum (8th element in 0-indexed)!')
        
        # Test with floats
        float_values = [3.3, 1.1, 4.4, 2.2]
        result = nth_element(float_values, 1)  # Should be 2.2 (2nd smallest)
        self.assertAlmostEqual(2.2, result, places=5, msg='nth_element should work with floats!')
        
        # Test exceptions
        with self.assertRaises(RuntimeError):
            nth_element([], 0)  # Empty list
        with self.assertRaises(RuntimeError):
            nth_element([1, 2, 3], -1)  # Negative index
        with self.assertRaises(RuntimeError):
            nth_element([1, 2, 3], 3)  # Index out of bounds

    def test_set_operations(self):
        # Test with sorted integer sets
        set1 = [1, 3, 5, 7, 9]
        set2 = [2, 3, 6, 7, 8]
        
        # Test set_union
        union_result = set_union(set1, set2)
        self.assertEqual([1, 2, 3, 5, 6, 7, 8, 9], union_result, 'Set union should contain all unique elements!')
        
        # Test set_intersection
        intersection_result = set_intersection(set1, set2)
        self.assertEqual([3, 7], intersection_result, 'Set intersection should contain common elements!')
        
        # Test set_difference
        difference_result = set_difference(set1, set2)
        self.assertEqual([1, 5, 9], difference_result, 'Set difference should contain elements in first but not second!')
        
        # Test includes
        subset = [3, 7]
        self.assertTrue(includes(set1, subset), 'Set1 should include subset [3, 7]!')
        self.assertFalse(includes(set1, [2, 4]), 'Set1 should not include [2, 4]!')
        
        # Test with strings
        str_set1 = ['apple', 'banana', 'cherry']
        str_set2 = ['banana', 'date', 'elderberry']
        str_union = set_union(str_set1, str_set2)
        self.assertEqual(['apple', 'banana', 'cherry', 'date', 'elderberry'], str_union, 'String set union should work!')
        
        # Test empty sets
        self.assertEqual(set1, set_union(set1, []), 'Union with empty set should return original set!')
        self.assertEqual([], set_intersection(set1, []), 'Intersection with empty set should return empty set!')

    def test_partition_and_rotate(self):
        # Test partition_less_than
        values = [9, 2, 5, 1, 8, 3, 7, 4, 6]
        partitioned = partition_less_than(values, 5)
        # Check that all elements < 5 are before all elements >= 5
        less_than_five = [x for x in partitioned if x < 5]
        greater_equal_five = [x for x in partitioned if x >= 5]
        
        # Find the partition point
        partition_point = 0
        for i, val in enumerate(partitioned):
            if val >= 5:
                partition_point = i
                break
        
        # All elements before partition point should be < 5
        for i in range(partition_point):
            self.assertLess(partitioned[i], 5, f'Element at index {i} should be less than 5!')
        
        # All elements from partition point should be >= 5
        for i in range(partition_point, len(partitioned)):
            self.assertGreaterEqual(partitioned[i], 5, f'Element at index {i} should be >= 5!')
        
        # Test rotate_left
        sequence = [1, 2, 3, 4, 5]
        
        # Rotate left by 2 positions
        rotated_left_2 = rotate_left(sequence, 2)
        self.assertEqual([3, 4, 5, 1, 2], rotated_left_2, 'Rotate left by 2 should work!')
        
        # Rotate left by 0 (no change)
        rotated_left_0 = rotate_left(sequence, 0)
        self.assertEqual([1, 2, 3, 4, 5], rotated_left_0, 'Rotate left by 0 should not change sequence!')
        
        # Rotate left by negative amount (right rotation)
        rotated_left_neg1 = rotate_left(sequence, -1)
        self.assertEqual([5, 1, 2, 3, 4], rotated_left_neg1, 'Rotate left by -1 should rotate right!')
        
        # Rotate by more than length (should wrap around)
        rotated_left_7 = rotate_left(sequence, 7)  # 7 % 5 = 2
        self.assertEqual([3, 4, 5, 1, 2], rotated_left_7, 'Rotate should wrap around for large values!')
        
        # Test with empty list
        self.assertEqual([], rotate_left([], 5), 'Rotate of empty list should return empty list!')
        
        # Test with floats
        float_seq = [1.1, 2.2, 3.3]
        rotated_float = rotate_left(float_seq, 1)
        expected = [2.2, 3.3, 1.1]
        for i, (exp, act) in enumerate(zip(expected, rotated_float)):
            self.assertAlmostEqual(exp, act, places=5, msg=f'Float rotate mismatch at index {i}')

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
