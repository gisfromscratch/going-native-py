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

#include "py_data.hpp"

using namespace std;

template<typename... T>
tuple<T...> Record<T...>::get_values() const
{
    return _values;
}

template<typename... T>
void Record<T...>::set_values(tuple<T...> values)
{
    _values = values;
}



int64_t Row::get_int(size_t index)
{    
    return _int_values.at(index);
}

void Row::set_int(size_t index, int64_t value)
{
    set_value_type(index, ValueTypes::Integer);
    _int_values[index] = value;
}

double Row::get_double(size_t index)
{
    return _double_values.at(index);
}

void Row::set_double(size_t index, double value)
{
    set_value_type(index, ValueTypes::Double);
    _double_values[index] = value;
}

string Row::get_string(size_t index)
{
    return _string_values.at(index);
}

void Row::set_string(size_t index, const string& value)
{
    set_value_type(index, ValueTypes::String);
    _string_values[index] = value;
}

Row::ValueTypes Row::get_value_type(size_t index) const
{
    if (_value_types.size() <= index)
    {
        return ValueTypes::Unknown;
    }

    return _value_types[index];
}

void Row::set_value_type(size_t index, ValueTypes value_type)
{
    if (index < _value_types.size())
    {
        _value_types[index] = value_type;
    }
    else
    {
        _value_types.push_back(value_type);
    }
}