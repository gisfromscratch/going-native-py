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

#include "py_io.hpp"

using namespace std;
using namespace io;

GeonamesCursor::GeonamesCursor(const string& file_path) : _reader(new io::LineReader(file_path))
{
    _current_line = _reader->next_line();
}

bool GeonamesCursor::has_next()
{
    return 0 == _current_line;
}

const Row& GeonamesCursor::next()
{
    _current_line = _reader->next_line();
    return _row;
}