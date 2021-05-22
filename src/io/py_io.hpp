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

#ifndef IO_H
#define IO_H

#include <memory>
#include <string>

#include <csv.h>

#include "../algorithm/py_data.hpp"

class Cursor {

public:
    virtual ~Cursor() {}

    virtual bool has_next() = 0;

    virtual const Row& next() = 0;
};



class GeonamesCursor : public Cursor {

public:
    GeonamesCursor(const std::string& file_path);

    virtual bool has_next() override;

    virtual const Row& next() override;

private:
    std::shared_ptr<io::LineReader> _reader;
    char* _current_line;
    Row _row;
};

#endif