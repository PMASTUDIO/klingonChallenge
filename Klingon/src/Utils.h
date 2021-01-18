#pragma once

#include <string>
#include <vector>
#include <map>

class Utils {
public:
	static std::map<char, uint32_t> letterValues;

	struct Report {
		uint32_t numOfPrepositions = 0;
		uint32_t numOfVerbs = 0;
		uint32_t numOfFirstPersonVerbs = 0;
		uint32_t numOfBeautifulNumbers = 0;
		std::string textBVocab = std::string();
	};

	enum class TextColor {
		RED = 0,
		GREEN = 1,
		BLUE = 2,
		CYAN = 3,
		MAGENTA = 4,
		YELLOW = 5
	};

	// General use functions
	static std::string ReadTextFile(const std::string& filePath);
	static std::vector<std::string> SplitString(const std::string& text, char by);
	static std::string JoinStrings(std::vector<std::string> words);

	static std::string GetColored(const std::string text, TextColor color);

	// Challenge specific functions
	static void AnswerNicely(Report& answerReport);
	static unsigned long long WordToNumber(const std::string& word);
	static std::vector<std::string> GetVocabularyList(const std::vector<std::string> words);
};
