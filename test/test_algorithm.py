import unittest

from algorithm import count_int

class TestAlgorithmMethods(unittest.TestCase):

    def test_help(self):
        integers = [1, 2, 3, 4, 5, 1, 7]
        self.assertEqual(2, count_int(integers, 1), 'The list contain two elements being 1!')

if __name__ == '__main__':
    unittest.main()
