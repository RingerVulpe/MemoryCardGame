#include "Memory.h"
#include <raylib.h>

#include "Card.h"

#include <time.h>

void Memory::Main()
{
	Start();

	InitWindow(screenWidth, screenHeight, "memory Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		Update();
		EndDrawing();
	}
	CloseWindow();
}

void Memory::Start()
{
	srand(time(NULL));

	float heightMinusGaps = screenHeight - (GAP + (GAP * gridSize));
	float tileSize = heightMinusGaps / gridSize;

	// populating the numbers
	for (int i = 0; i < gridSize * gridSize / 2; i++)
	{
		numbers.push_back(i + 1);
		numbers.push_back(i + 1);
	}

	// generate all of our numbers in an array <vector>
	// we gonna go through our cards in order
	// but through our numbers in random
	// and assign
	// 1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8
	for (int row = 0; row < gridSize; row++)
		for (int col = 0; col < gridSize; col++)
		{
			float x = GAP + (tileSize + GAP) * col;
			float y = GAP + (tileSize + GAP) * row;
			Rectangle rect = Rectangle{ x, y, tileSize, tileSize };

			int randomIndex = rand() % numbers.size();
			int num = numbers[randomIndex];
			Card card = Card { rect, num };

			numbers.erase(numbers.begin() + randomIndex);
			cards.push_back(card);
		}
}

void Memory::Update()
{
	EvalCurFrame();
	DrawCurFrame();
}

void Memory::EvalCurFrame()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !startTimer) // Prevent flipping more cards when timer is running
	{
		Vector2 mousePoint = GetMousePosition();

		for (int i = 0; i < cards.size(); i++)
		{
			if (CheckCollisionPointRec(mousePoint, cards[i].rect) && cards[i].cardState == Hidden)
			{
				if (flippedCount == 0)
				{
					firstFlipped = &cards[i];
				}
				else if (flippedCount == 1)
				{
					secondFlipped = &cards[i];
				}
				cards[i].cardState = Flipped;
				flippedCount++;
			}
		}
	}

	// Update part
	if (flippedCount == 2 && !startTimer) // Check if two cards are flipped and start timer if not already started
	{
		// Set the startTimer flag to true to begin the delay
		startTimer = true;
		flipTimer = 0; // Reset the timer
	}

	if (startTimer)
	{
		flipTimer += GetFrameTime(); // Increment the timer by the time taken for the last frame

		if (flipTimer >= 1.0f) // Check if 1 second has passed
		{
			
			// Code to flip cards back if they don't match
			if (firstFlipped && secondFlipped) // Ensure these are not null
			{
				if (firstFlipped->num != secondFlipped->num) // If cards do not match
				{
					firstFlipped->cardState = Hidden;
					secondFlipped->cardState = Hidden;
				}
				else // If they match
				{
					firstFlipped->cardState = Found;
					secondFlipped->cardState = Found;
				}
			}

			flippedCount = 0;
			startTimer = false; // Reset the timer flag
		}
	}
	
	//check if all the cards have been found if so, display a message
	allFound = true;
	for (int i = 0; i < cards.size(); i++)
	{
		if (cards[i].cardState != Found)
		{
			allFound = false;
			break;
		}
	}

	
	
}

void Memory::DrawCurFrame()
{
	for (Card card : cards)
		card.DrawCard();

	if (allFound)
	{
		DrawText("You Win!", 400, 250, 40, RED);
	}
}
