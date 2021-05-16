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
#include "py_algorithm.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/chrono.h>
#include <pybind11/stl.h>

namespace py = pybind11;

using namespace std;
using namespace std::chrono;

template<typename T>
int py_count(const vector<T>& values, T value)
{
    return count(values.begin(), values.end(), value);
}

PYBIND11_MODULE(algorithm, m) {
    m.doc() = "Offers access to the STL algorithms."; // optional module docstring
    m.def("count", &py_count<int>, "Returns the number of integers satisfying the specific integer.", 
        py::arg("values"), py::arg("value"));
    m.def("count", &py_count<float>, "Returns the number of floats satisfying the specific float.", 
        py::arg("values"), py::arg("value"));
    m.def("count", &py_count<string>, "Returns the number of strings satisfying the specific string.", 
        py::arg("values"), py::arg("value"));
    m.def("count", &py_count<system_clock::time_point>, "Returns the number of dates satisfying the specific date.", 
        py::arg("values"), py::arg("value"));
}