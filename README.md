## Grapheme Splitter

This is the C++ equivalent of the JS library here: https://github.com/orling/grapheme-splitter.

Usage is simple, there is a single function:

```cpp
size_t next_grapheme(const char *str, size_t length, size_t pos);
```

This returns the position of the next grapheme in a UTF-8 string, after the position "pos". This can be used to iterate over graphemes or count the number of graphemes in a string. For example, the following function can be used to get a vector of all the graphemes that occur in a string:

```cpp
std::vector<std::string> split_graphemes(const char *str, size_t length) {
	std::vector<std::string> result;
	size_t pos = 0;
	while(pos < length) {
		size_t next_pos = next_grapheme(str, length, pos);
		result.push_back(std::string(str + pos, next_pos - pos));
		pos = next_pos;
	}
	return result;
}

// input: 🌷🎁💩😜👍🏳️‍🌈
// output: [🌷, 🎁, 💩, 😜, 👍, 🏳️‍🌈]
```
