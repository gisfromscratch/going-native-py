// 
// Copyright (C) 2021 Jan Tschada (gisfromscratch@live.de)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

using namespace std;

int py_count(const vector<int>& integers, int value)
{
    return count(integers.begin(), integers.end(), value);
}

PYBIND11_MODULE(algorithm, m) {
    m.doc() = "Offers access to the STL algorithms."; // optional module docstring
    m.def("count_int", &py_count, "Returns the number of integers satisfying the specific integer.", 
        py::arg("integers"), py::arg("value"));
}