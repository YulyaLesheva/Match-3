#pragma once
#include "stdafx.h"

namespace UseTextWork {
	int GetBestScore() {
		auto stream1 = Core::fileSystem.OpenRead("bestScore.txt");
		IO::TextReader reader(stream1.get());
		std::string line;
		line = reader.ReadAsciiLine();

		return std::stoi(line);
	}

	void WriteNewBestScore(int currentScore) {
		auto currentBestScore = GetBestScore();
		if (currentScore > currentBestScore) {
			auto stream1 = Core::fileSystem.OpenWrite("bestScore.txt");
			IO::OutputStream* write(stream1.get());
			char str[5];
			auto done = itoa(currentScore, str, 10);
			size_t length = strlen(done);
			write->Write(done, length);
		}
	}

	char* ReturnBestScoreForPrint() {
		auto bs = GetBestScore();
		char str[10];
		auto done1 = itoa(bs, str, 10);
		return done1;
	}
}