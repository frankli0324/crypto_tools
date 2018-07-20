#pragma once
#include<string>
#include<vector>
namespace Base64 {
	static inline bool is_base64(unsigned char c);
	static const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	std::string encode(std::string raw_string);
	std::string decode(std::string encoded_string);
}

namespace UrlEncode {
	unsigned char ToHex(unsigned char x);
	unsigned char FromHex(unsigned char x);

	std::string encode(const std::string& str);
	std::string decode(const std::string& str);
}

namespace Fence {
	std::string encode(std::string word, int unit, bool force);
	std::string decode(std::string word, int unit, bool force);
	std::vector<std::string>auto_decode(std::string word);
}

namespace Caesar {
	std::vector<std::string> decode_listall(std::string word);
}

namespace ASCII {
	std::string decode(std::string word);
}