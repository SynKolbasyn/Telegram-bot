#pragma once
#ifndef _TYPES_HPP_
#define _TYPES_HPP_

#include <fstream>

using std::fstream;

namespace sk {

typedef short int i16;
typedef unsigned short int u16;
typedef int i32;
typedef unsigned int u32;
typedef long int i64;
typedef unsigned long int u64;

typedef fstream::openmode open_mode;

} // namespace sk

#endif
