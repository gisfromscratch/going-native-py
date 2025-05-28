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
    Row recylced_row;
    for (const py::tuple& tuple : tuples)
    {
        size_t index = 0;
        for (auto const& value : tuple)
        {
            if (0 == count)
            {
                // Determine the value types
                auto value_type = py::type::of(value);
                stringstream type_name;
                type_name << value_type;
                if (0 == type_name.str().compare("<class 'int'>"))
                {
                    recylced_row.set_int(index, value.cast<int64_t>());
                }
                else if (0 == type_name.str().compare("<class 'float'>"))
                {
                    recylced_row.set_double(index, value.cast<double>());
                }
                else if (0 == type_name.str().compare("<class 'datetime'>"))
                {
                    recylced_row.set_date(index, value.cast<system_clock::time_point>());
                }
                else if (0 == type_name.str().compare("<class 'str'>"))
                {
                    recylced_row.set_string(index, value.cast<string>());
                }
                else
                {
                    //cout << type_name.str() << endl;
                }    
            }
            else
            {
                switch (recylced_row.get_value_type(index))
                {
                    case Row::ValueTypes::Integer:
                        recylced_row.set_int(index, value.cast<int64_t>());
                        break;

                    case Row::ValueTypes::Double:
                        recylced_row.set_double(index, value.cast<double>());
                        break;

                    case Row::ValueTypes::Date:
                        recylced_row.set_date(index, value.cast<system_clock::time_point>());
                        break;

                    case Row::ValueTypes::String:
                        recylced_row.set_string(index, value.cast<string>());
                        break;

                    case Row::ValueTypes::Unknown:
                        //cout << "Unknown type" << endl;
                        break;
                }
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

template<typename T>
vector<T> py_reverse(const vector<T>& values)
{
    vector<T> result = values;
    reverse(result.begin(), result.end());
    return result;
}

template<typename T>
vector<T> py_sort(const vector<T>& values)
{
    vector<T> result = values;
    sort(result.begin(), result.end());
    return result;
}

template<typename T>
T py_accumulate(const vector<T>& values, T init)
{
    return accumulate(values.begin(), values.end(), init);
}

template<typename T>
T py_min_element(const vector<T>& values)
{
    if (values.empty()) {
        throw runtime_error("Cannot find minimum of empty container");
    }
    return *min_element(values.begin(), values.end());
}

template<typename T>
T py_max_element(const vector<T>& values)
{
    if (values.empty()) {
        throw runtime_error("Cannot find maximum of empty container");
    }
    return *max_element(values.begin(), values.end());
}

// Transform functions with predefined operations
template<typename T>
vector<T> py_transform_square(const vector<T>& values)
{
    vector<T> result;
    result.reserve(values.size());
    transform(values.begin(), values.end(), back_inserter(result), [](const T& x) { return x * x; });
    return result;
}

template<typename T>
vector<T> py_transform_abs(const vector<T>& values)
{
    vector<T> result;
    result.reserve(values.size());
    transform(values.begin(), values.end(), back_inserter(result), [](const T& x) { return x < 0 ? -x : x; });
    return result;
}

vector<float> py_transform_sqrt(const vector<float>& values)
{
    vector<float> result;
    result.reserve(values.size());
    transform(values.begin(), values.end(), back_inserter(result), [](const float& x) { return sqrt(x); });
    return result;
}

vector<string> py_transform_toupper(const vector<string>& values)
{
    vector<string> result;
    result.reserve(values.size());
    transform(values.begin(), values.end(), back_inserter(result), [](const string& s) {
        string upper_s = s;
        transform(upper_s.begin(), upper_s.end(), upper_s.begin(), ::toupper);
        return upper_s;
    });
    return result;
}

vector<string> py_transform_tolower(const vector<string>& values)
{
    vector<string> result;
    result.reserve(values.size());
    transform(values.begin(), values.end(), back_inserter(result), [](const string& s) {
        string lower_s = s;
        transform(lower_s.begin(), lower_s.end(), lower_s.begin(), ::tolower);
        return lower_s;
    });
    return result;
}

template<typename T>
vector<T> py_unique(const vector<T>& values)
{
    vector<T> result = values;
    auto last = unique(result.begin(), result.end());
    result.erase(last, result.end());
    return result;
}

template<typename T>
bool py_binary_search(const vector<T>& values, T value)
{
    return binary_search(values.begin(), values.end(), value);
}

template<typename T>
T py_nth_element(const vector<T>& values, int n)
{
    if (values.empty()) {
        throw runtime_error("Cannot find nth element of empty container");
    }
    if (n < 0 || n >= values.size()) {
        throw runtime_error("Index out of bounds");
    }
    vector<T> result = values;
    nth_element(result.begin(), result.begin() + n, result.end());
    return result[n];
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

    m.def("reverse", &py_reverse<int>, "Returns a reversed copy of the integer list.", 
        py::arg("values"));
    m.def("reverse", &py_reverse<float>, "Returns a reversed copy of the float list.", 
        py::arg("values"));
    m.def("reverse", &py_reverse<string>, "Returns a reversed copy of the string list.", 
        py::arg("values"));
    m.def("reverse", &py_reverse<system_clock::time_point>, "Returns a reversed copy of the date list.", 
        py::arg("values"));

    m.def("sort", &py_sort<int>, "Returns a sorted copy of the integer list.", 
        py::arg("values"));
    m.def("sort", &py_sort<float>, "Returns a sorted copy of the float list.", 
        py::arg("values"));
    m.def("sort", &py_sort<string>, "Returns a sorted copy of the string list.", 
        py::arg("values"));
    m.def("sort", &py_sort<system_clock::time_point>, "Returns a sorted copy of the date list.", 
        py::arg("values"));

    m.def("accumulate", &py_accumulate<int>, "Returns the sum of integers starting with initial value.", 
        py::arg("values"), py::arg("init"));
    m.def("accumulate", &py_accumulate<float>, "Returns the sum of floats starting with initial value.", 
        py::arg("values"), py::arg("init"));

    m.def("min_element", &py_min_element<int>, "Returns the minimum integer value in the list.", 
        py::arg("values"));
    m.def("min_element", &py_min_element<float>, "Returns the minimum float value in the list.", 
        py::arg("values"));
    m.def("min_element", &py_min_element<string>, "Returns the minimum string value in the list.", 
        py::arg("values"));
    m.def("min_element", &py_min_element<system_clock::time_point>, "Returns the minimum date value in the list.", 
        py::arg("values"));

    m.def("max_element", &py_max_element<int>, "Returns the maximum integer value in the list.", 
        py::arg("values"));
    m.def("max_element", &py_max_element<float>, "Returns the maximum float value in the list.", 
        py::arg("values"));
    m.def("max_element", &py_max_element<string>, "Returns the maximum string value in the list.", 
        py::arg("values"));
    m.def("max_element", &py_max_element<system_clock::time_point>, "Returns the maximum date value in the list.", 
        py::arg("values"));

    m.def("transform_square", &py_transform_square<int>, "Returns a list with each integer squared.", 
        py::arg("values"));
    m.def("transform_square", &py_transform_square<float>, "Returns a list with each float squared.", 
        py::arg("values"));
    m.def("transform_abs", &py_transform_abs<int>, "Returns a list with absolute value of each integer.", 
        py::arg("values"));
    m.def("transform_abs", &py_transform_abs<float>, "Returns a list with absolute value of each float.", 
        py::arg("values"));
    m.def("transform_sqrt", &py_transform_sqrt, "Returns a list with square root of each float.", 
        py::arg("values"));
    m.def("transform_toupper", &py_transform_toupper, "Returns a list with each string converted to uppercase.", 
        py::arg("values"));
    m.def("transform_tolower", &py_transform_tolower, "Returns a list with each string converted to lowercase.", 
        py::arg("values"));

    m.def("unique", &py_unique<int>, "Returns a list with adjacent duplicate integers removed.", 
        py::arg("values"));
    m.def("unique", &py_unique<float>, "Returns a list with adjacent duplicate floats removed.", 
        py::arg("values"));
    m.def("unique", &py_unique<string>, "Returns a list with adjacent duplicate strings removed.", 
        py::arg("values"));
    m.def("unique", &py_unique<system_clock::time_point>, "Returns a list with adjacent duplicate dates removed.", 
        py::arg("values"));

    m.def("binary_search", &py_binary_search<int>, "Returns true if the integer value is found in the sorted list.", 
        py::arg("values"), py::arg("value"));
    m.def("binary_search", &py_binary_search<float>, "Returns true if the float value is found in the sorted list.", 
        py::arg("values"), py::arg("value"));
    m.def("binary_search", &py_binary_search<string>, "Returns true if the string value is found in the sorted list.", 
        py::arg("values"), py::arg("value"));
    m.def("binary_search", &py_binary_search<system_clock::time_point>, "Returns true if the date value is found in the sorted list.", 
        py::arg("values"), py::arg("value"));

    m.def("nth_element", &py_nth_element<int>, "Returns the nth smallest integer element (0-indexed).", 
        py::arg("values"), py::arg("n"));
    m.def("nth_element", &py_nth_element<float>, "Returns the nth smallest float element (0-indexed).", 
        py::arg("values"), py::arg("n"));
    m.def("nth_element", &py_nth_element<string>, "Returns the nth smallest string element (0-indexed).", 
        py::arg("values"), py::arg("n"));
    m.def("nth_element", &py_nth_element<system_clock::time_point>, "Returns the nth smallest date element (0-indexed).", 
        py::arg("values"), py::arg("n"));

    m.def("read_tuples", &py_read_tuples, "Reads tuples into a row structure.",
        py::arg("tuples"));
}