#pragma once

#include <string>
#include <vector>

namespace graphemesplitter {

int32_t utf8_codepoint(const char *str, size_t length, size_t pos);
std::string codepoint_to_utf8(int32_t codepoint);

size_t next_grapheme(const char *str, size_t length, size_t pos);


}
