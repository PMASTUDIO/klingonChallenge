/*
Data: 17/01/2021
Autor: Pedro Klingelfus Ganme
Desafio: https://github.com/jonathan-santos/klingon-test/blob/main/README.md
*/

#include <regex>

#include "Utils.h"

int main() {

	std::string textA = Utils::ReadTextFile("Resources/Texts/A.txt");
	std::vector<std::string> textAWords = Utils::SplitString(textA, ' ');

	std::string textB = Utils::ReadTextFile("Resources/Texts/B.txt");
	std::vector<std::string> textBWords = Utils::SplitString(textB, ' ');

	Utils::Report textBReport{};

	std::regex prepositionRegex("..[^slfwk]$");
	std::regex verbRegex("[a-z]*[slfwk]$");
	std::regex firstPersonRegex("^[^slfwk][a-z]*");

	for (auto word : textBWords) {
		// Preposition (Has size 3 - Matches preposition regex - Doesn't have d)
		if (word.size() == 3 && std::regex_match(word, prepositionRegex) && word.find("d") == std::string::npos) {
			textBReport.numOfPrepositions++;
		}

		// Verbs (Has size >= 8 - Matches verb regex)
		if (word.size() >= 8 && std::regex_match(word, verbRegex)) {
			textBReport.numOfVerbs++;
			if (std::regex_match(word, firstPersonRegex))
				textBReport.numOfFirstPersonVerbs++;
		}

		// Is a beautiful number (Value >= 440566 - Is dividable by 3 - Distinct)
		auto wordValue = Utils::WordToNumber(word);
		std::vector<unsigned long long> existingBeautifulNumbers{};
		if (wordValue >= 440566 && wordValue % 3 == 0 && std::find(existingBeautifulNumbers.begin(), existingBeautifulNumbers.end(), wordValue) == existingBeautifulNumbers.end()) {
			textBReport.numOfBeautifulNumbers++;
			existingBeautifulNumbers.push_back(wordValue);
		}
	}

	textBReport.textBVocab = Utils::JoinStrings(Utils::GetVocabularyList(textBWords));

	Utils::AnswerNicely(textBReport);
}