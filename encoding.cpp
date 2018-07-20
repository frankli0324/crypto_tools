#include "encoding.h"
namespace Base64 {
	bool is_base64(unsigned char c) {
		return (isalnum(c) || (c == '+') || (c == '/'));
	}
	std::string encode(std::string raw_string) {
		std::string ret;
		int i = 0;
		int j = 0;
		unsigned char char_array_3[3];
		unsigned char char_array_4[4];
		unsigned int in_len = raw_string.size();
		const char *bytes_to_encode = raw_string.c_str();

		while (in_len--) {
			char_array_3[i++] = *(bytes_to_encode++);
			if (i == 3) {
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (i = 0; (i <4); i++)
					ret += base64_chars[char_array_4[i]];
				i = 0;
			}
		}

		if (i) {
			for (j = i; j < 3; j++)
				char_array_3[j] = '\0';
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;
			for (j = 0; (j < i + 1); j++)
				ret += base64_chars[char_array_4[j]];
			while ((i++ < 3))
				ret += '=';
		}
		return ret;
	}
	std::string decode(std::string encoded_string) {
		int in_len = encoded_string.size();
		int i = 0;
		int j = 0;
		int in_ = 0;
		unsigned char char_array_4[4], char_array_3[3];
		std::string ret;

		while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
			char_array_4[i++] = encoded_string[in_]; in_++;
			if (i == 4) {
				for (i = 0; i <4; i++)
					char_array_4[i] = base64_chars.find(char_array_4[i]);

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (i = 0; (i < 3); i++)
					ret += char_array_3[i];
				i = 0;
			}
		}

		if (i) {
			for (j = i; j <4; j++)
				char_array_4[j] = 0;

			for (j = 0; j <4; j++)
				char_array_4[j] = base64_chars.find(char_array_4[j]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
		}

		return ret;
	}
	
}

namespace UrlEncode {
	unsigned char ToHex(unsigned char x) {
		return  x > 9 ? x + 55 : x + 48;
	}

	unsigned char FromHex(unsigned char x) {
		unsigned char y;
		if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
		else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
		else if (x >= '0' && x <= '9') y = x - '0';
		return y;
	}

	std::string encode(const std::string & str) {
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++) {
			if (isalnum((unsigned char)str[i]) ||
				(str[i] == '-') || (str[i] == '_') || (str[i] == '.') || (str[i] == '~'))
				strTemp += str[i];
			else if (str[i] == ' ')
				strTemp += "+";
			else {
				strTemp += '%';
				strTemp += ToHex((unsigned char)str[i] >> 4);
				strTemp += ToHex((unsigned char)str[i] % 16);
			}
		}
		return strTemp;
	}
	std::string decode(const std::string & str) {
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++) {
			if (str[i] == '+') strTemp += ' ';
			else if (str[i] == '%') {
				unsigned char high = FromHex((unsigned char)str[++i]);
				unsigned char low = FromHex((unsigned char)str[++i]);
				strTemp += high * 16 + low;
			}
			else strTemp += str[i];
		}
		return strTemp;
	}
}

namespace Fence {
	int prime[100];
	bool check[501];
	int prime_cnt = 0;
	void gen_prime() {
		memset(check, 0, sizeof(check));
		for (int i = 2; i < 500; i++) {
			if (!check[i])
				prime[prime_cnt++] = i;
			
			for (int j = 0; j < prime_cnt; j++) {
				if ((i * prime[j]) > 500)
					break;

				check[i*prime[j]] = 1;
				if (i % prime[j] == 0)
					break;
			}
		}
	}
	
	std::string encode(std::string word, int unit, bool force = false) {
		if (force == false && word.size() % unit)return "check unit size";
		std::string ret; int parts = word.size() / unit;
		for (int i = 0; i < parts; i++) {
			for (int j = 0; j < unit; j++)
				if (i + j * parts < word.size())ret += word[i + j * parts];
		}
		return ret;
	}
	std::string decode(std::string word, int unit, bool force = false) {
		if (force == false && word.size() % unit)return "check unit size";
		std::string ret;
		int parts = word.size() / unit;
		if (word.size() % unit)unit++;
		for (int i = 0; i < unit; i++) {
			for (int j = 0; j < parts; j++)
				if (j*unit + i < word.size())ret += word[j*unit + i];
		}
		return ret;
	}
	std::vector<std::string> auto_decode(std::string word) {
		std::vector<std::string>ret;
		//if (prime_cnt == 0)gen_prime();
		for (int i = 1; i < word.size(); i++) {
			if (word.size() % i == 0)ret.push_back(decode(word, i) + "    with chars per unit:\"" + std::to_string(i) + "\"");
		}
		return ret;
	}
}

namespace Caesar {
	std::string decode(std::string word, int r_padding) {
		std::string ret;
		for (int i = 0; i < word.size(); i++) {
			if (isalpha(word[i]) == false)continue;
			word[i] = tolower(word[i]);
			word[i] = ((int)word[i] - 'a' + r_padding) % 26 + 'a';
		}
		return word;
	}
	std::vector<std::string> decode_listall(std::string word) {
		std::vector<std::string>ret;
		for (int i = 1; i <= 26; i++)
			ret.push_back(decode(word, i));
		return ret;
	}
}

namespace ASCII {
	int mark; std::string sentence;
	int next_int() {
		int mark2 = 0;
		while (mark < sentence.size() && !isdigit(sentence[mark]))mark++;
		if (mark == sentence.size())return 0;
		mark2 = mark;
		while (isdigit(sentence[mark2]))mark2++;
		int ret = atoi(sentence.substr(mark, mark2 - (mark)).c_str());
		mark = mark2;
		return ret;
	}
	std::string decode(std::string word) {
		std::string ret; int temp;
		sentence = word; mark = 0;
		while (temp = next_int())
			ret += char(temp);
		return ret;
	}
}