#pragma once
#include <vector>
#include "Card.h"

#ifndef MEMORY_H
#define MEMORY_H

class Memory
{
public:

#define GAP 5 // gap between every two tiles

	const int screenWidth = 800;
	const int screenHeight = 500;
	int flippedCount = 0;
	bool allFound = false;
	float flipTimer = 0.0f; // Time in seconds since the second card was flipped.
	bool startTimer = false; // Flag to start the timer.

	Card* firstFlipped = nullptr;
	Card* secondFlipped = nullptr;

	int gridSize = 4; // this can switch to 6 or 8 as well

	std::vector<Card> cards;
	std::vector<int> numbers;


	void Main();
	void Start();
	void EvalCurFrame();
	void DrawCurFrame();
	void Update();


};







#endif