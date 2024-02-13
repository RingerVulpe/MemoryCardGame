#pragma once

#include <raylib.h>
#include "CardState.h"

#include <string>

#ifndef CARD_H
#define CARD_H

class Card
{
public:

	Card(Rectangle r, int n)
	{
		rect = r; num = n;
		
		cardCen = Vector2{
						rect.x + rect.width / 2,
						rect.y + rect.height / 2
		};
	}


	Rectangle rect;
	int num; // in our checks (comparison) we can use this

	CardState cardState = CardState::Hidden;


	void DrawCard();


private:
	int fontSize = 96;

	Vector2 cardCen;
	float txtHeight;
};

#endif
