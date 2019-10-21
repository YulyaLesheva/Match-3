#pragma once
#include "stdafx.h"
#include "Icons.h"
#include <random>

namespace Random {
	std::string archive[7] = { "milk", "orange", "apple", "flower", "cocos", "bread", "brokkoli" };

	std::string GetRandomTile() {

		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> uni(0, 6);

		auto random_integer = uni(rng);
		std::string icon = archive[random_integer];
		return icon;
	}
}

