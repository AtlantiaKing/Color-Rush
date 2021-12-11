#pragma once

enum class Color
{
	GREEN,
	YELLOW,
	PURPLE,
	ORANGE,
	MAGENTA,
	CYAN,
	DARK_GREEN,
	BROWN,
	DARK_PINK,
	TURQUOISE,
	// Add new colors before this line
	DISABLED,
	RED,
	BLUE
};

enum class GameState
{
	TITLE_SCREEN,
	MAIN_MENU,
	GAME,
	GAME_OVER
};