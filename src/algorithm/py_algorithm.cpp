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
#include "py_data.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/chrono.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

namespace py = pybind11;

using namespace std;
using namespace std::chrono;

/*
int py_count(const vector<Record<int>>& records, int value)
{
    return count_if(records.begin(), records.end(), [&] (const Record<int>& record) {
        auto values = record.get_values();
        return value == get<0>(values);
    });
}
*/

int py_read_tuples(const vector<py::tuple>& tuples)
{
    int count = 0;
    for (const py::tuple& tuple : tuples)
    {
        Row row;
        size_t index = 0;
        for (auto const& value : tuple)
        {
            auto value_type = py::type::of(value);
            stringstream type_name;
            type_name << value_type;
            if (0 == type_name.str().compare("<class 'int'>"))
            {
                row.set_int(index, value.cast<int64_t>());
            }
            else if (0 == type_name.str().compare("<class 'float'>"))
            {
                row.set_double(index, value.cast<double>());
            }
            else if (0 == type_name.str().compare("<class 'str'>"))
            {
                row.set_string(index, value.cast<string>());
            }
            else
            {
                cout << type_name.str() << endl;
            }

            index++;
        }
        count++;
    }

    return count;
}

template<typename T>
int py_count(const vector<T>& values, T value)
{
    return count(values.begin(), values.end(), value);
}

template<typename T>
int py_count_arr(const py::array_t<T>& values, T value)
{
    auto buffer_info = values.request();
    if (buffer_info.ndim != 1)
        throw runtime_error("Only one dimensional arrays are supported!");

    T* raw_values = static_cast<T*>(buffer_info.ptr);

    // Raw style
    /*
    int count = 0;
    for (int index = 0, size = buffer_info.size; index < size; index++)
    {
        if (value == raw_values[index])
        {
            count++;
        }
    }

    return count;
    */

    // STL style
    vector<T> vec_values;
    vec_values.reserve(buffer_info.size);
    vec_values.insert(vec_values.end(), &raw_values[0], &raw_values[buffer_info.size]);

    return count(vec_values.begin(), vec_values.end(), value);
}

template<typename T>
int py_count_if_lt(const vector<T>& values, T value)
{
    return count_if(values.begin(), values.end(), [&] (const T& entry) {
        return entry < value;
    });
}

template<typename T>
int py_count_if_lteq(const vector<T>& values, T value)
{
    return count_if(values.begin(), values.end(), [&] (const T& entry) {
        return entry <= value;
    });
}

template<typename T>
int py_count_if_gt(const vector<T>& values, T value)
{
    return count_if(values.begin(), values.end(), [&] (const T& entry) {
        return entry > value;
    });
}

template<typename T>
int py_count_if_gteq(const vector<T>& values, T value)
{
    return count_if(values.begin(), values.end(), [&] (const T& entry) {
        return entry >= value;
    });
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
    m.def("count_arr", &py_count_arr<int>, "Returns the number of integers satisfying the specific integer.", 
        py::arg("values"), py::arg("value"));
    m.def("count_lt", &py_count_if_lt<int>, "Returns the number of integers being less than the specific integer.", 
        py::arg("values"), py::arg("value"));
    m.def("count_lt", &py_count_if_lt<float>, "Returns the number of floats being less than the specific float.", 
        py::arg("values"), py::arg("value"));
    m.def("count_lt", &py_count_if_lt<string>, "Returns the number of strings being less than the specific string.", 
        py::arg("values"), py::arg("value"));
    m.def("count_lt", &py_count_if_lt<system_clock::time_point>, "Returns the number of dates being less than the specific date.", 
        py::arg("values"), py::arg("value"));

    m.def("read_tuples", &py_read_tuples, "Reads tuples into a row structure.",
        py::arg("tuples"));
}