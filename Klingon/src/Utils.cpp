#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

std::map<char, uint32_t> Utils::letterValues{
	{'k',  0},
	{'b',  1},
	{'w',  2},
	{'r',  3},
	{'q',  4},
	{'d',  5},
	{'n',  6},
	{'f',  7},
	{'x',  8},
	{'j',  9},
	{'m',  10},
	{'l',  11},
	{'v',  12},
	{'h',  13},
	{'t',  14},
	{'c',  15},
	{'g',  16},
	{'z',  17},
	{'p',  18},
	{'s',  19}
};

void Utils::AnswerNicely(Report& answerReport)
{
	std::cout << GetColored(
		"// ----------------------\n//\n// - Data: 17/01/2021\n// - Autor: Pedro Klingelfus Ganme\n// - Desafio: https://github.com/jonathan-santos/klingon-test/blob/main/README.md \n//\n// ----------------------\n",
		TextColor::GREEN);

	std::cout << GetColored("\nProgram Report...\n", TextColor::CYAN);

	std::cout << "There are " << GetColored(std::to_string(answerReport.numOfPrepositions), TextColor::MAGENTA) << " PREPOSITIONS in text B." << std::endl;
	std::cout << "There are " << GetColored(std::to_string(answerReport.numOfVerbs), TextColor::MAGENTA) << " VERBS in text B." << std::endl;
	std::cout << "There are " << GetColored(std::to_string(answerReport.numOfFirstPersonVerbs), TextColor::MAGENTA) << " FIRST PERSON VERBS in text B." << std::endl;
	std::cout << "There are " << GetColored(std::to_string(answerReport.numOfBeautifulNumbers), TextColor::MAGENTA) << " unique BEAUTIFUL NUMBERS in text B." << std::endl;
	std::cout << "This is the vocabulary list for text B: \n" << GetColored(answerReport.textBVocab, TextColor::YELLOW) << std::endl;
}

std::string Utils::ReadTextFile(const std::string& filePath)
{
	std::ifstream inFile;

	inFile.open(filePath);

	if (!inFile) {
		std::cerr << "Unable to open file " << filePath << std::endl;
		return std::string();
	}

	std::ostringstream ss;
	ss << inFile.rdbuf(); // Read all data

	return ss.str();
}

std::vector<std::string> Utils::SplitString(const std::string& text, char by)
{
	std::string tmp;
	std::stringstream ss(text);
	std::vector<std::string> words;

	while (std::getline(ss, tmp, by))
	{
		words.push_back(tmp);
	}

	return words;
}

std::string Utils::JoinStrings(const std::vector<std::string> words)
{
	const char* const delim = " ";

	std::ostringstream imploded;
	std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(imploded, delim));

	return imploded.str();
}

std::string Utils::GetColored(const std::string text, TextColor color)
{
	std::stringstream ss;
	
	switch (color)
	{
	case Utils::TextColor::RED:
		ss << "\x1B[31m";
		break;
	case Utils::TextColor::GREEN:
		ss << "\x1B[32m";
		break;
	case Utils::TextColor::BLUE:
		ss << "\x1B[34m";
		break;
	case Utils::TextColor::CYAN:
		ss << "\x1B[36m";
		break;
	case Utils::TextColor::MAGENTA:
		ss << "\x1B[35m";
		break;
	case Utils::TextColor::YELLOW:
		ss << "\x1B[33m";
		break;
	default:
		break;
	}

	ss << text;
	ss << "\033[0m";

	return ss.str();
}

unsigned long long Utils::WordToNumber(const std::string& word)
{
	unsigned long long value = 0;

	for (size_t i = 0; i < word.size(); i++) {
		unsigned long long add = letterValues[word[i]] * pow(20, i);
		value += add;
	}

	return value;
}

std::vector<std::string> Utils::GetVocabularyList(std::vector<std::string> words)
{
	std::sort(words.begin(), words.end(), [](std::string a, std::string b) {
		for (size_t i = 0; i < std::min(a.size(), b.size()); i++) {
			if (a[i] == b[i])
				continue;

			return letterValues[a[i]] < letterValues[b[i]];
		}
	});

	return words;
}
