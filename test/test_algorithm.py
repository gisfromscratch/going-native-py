import unittest

from algorithm import count

class TestAlgorithmMethods(unittest.TestCase):

    def test_count(self):
        integers = [1, 2, 3, 4, 5, 1, 7]
        self.assertEqual(2, count(integers, 1), 'The list contains two elements being 1!')
        floats = [1.1, 2.2, 3.3, 1.1, 2.3]
        self.assertEqual(2, count(floats, 1.1), 'The list contains two elements being 1.1!')
        strings = ['Dessau', 'Duchwehna', 'Leipzig', 'Bonn', 'Dessau']
        self.assertEqual(2, count(strings, 'Dessau'), 'The list contains two elements being \'Dessau\'!')

if __name__ == '__main__':
    unittest.main()
