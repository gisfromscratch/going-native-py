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

#ifndef DATA_H
#define DATA_H

#include <limits>
#include <map>
#include <tuple>
#include <string>
#include <vector>

template<typename... T>
class Record {

public:
    std::tuple<T...> get_values() const;
    void set_values(std::tuple<T...> values);

private:
    std::tuple<T...> _values;
};



class Row {

public:
    int64_t get_int(size_t index);
    void set_int(size_t index, int64_t value);

    double get_double(size_t index);
    void set_double(size_t index, double value);

    std::string get_string(size_t index);
    void set_string(size_t index, const std::string& value);

    enum class ValueTypes {
        Unknown,
        Integer,
        Double,
        String
    };

    ValueTypes get_value_type(size_t index) const;

    //static const int64_t none_int = std::numeric_limits<int64_t>::min();

private:
    void set_value_type(size_t index, ValueTypes value_type);

    std::vector<ValueTypes> _value_types;
    std::map<size_t, int64_t> _int_values;
    std::map<size_t, double> _double_values;
    std::map<size_t, std::string> _string_values;
};

#endif