#include "Card.h"
#include <raylib.h>
#include <iostream>
#include <ostream>
#include <string>

void Card::DrawCard()
{
	std::string txtStr;
	Color color;

	switch (cardState)
	{
	case Hidden:
		color = GRAY;
		txtStr = "?";
		break;

	case Flipped:
		color = ORANGE;
		txtStr = std::to_string(num);
		break;

	case Found:
		color = GREEN;
		txtStr = ":)";
		break;

	default:
		break;
	}

	float txtWidth = MeasureText(txtStr.c_str(), fontSize);
	Vector2 txtOrigin = Vector2{
								cardCen.x - txtWidth / 2,
								cardCen.y - fontSize / 2 };

	DrawRectangleRounded(rect, 0.1, 5, color);


	DrawText(txtStr.c_str(), txtOrigin.x,
		txtOrigin.y, fontSize, WHITE);

}
