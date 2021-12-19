#include "pch.h"
#include "Game.h"

#include <iostream>
#pragma comment(lib, "Winmm.lib")
#include <mmsystem.h>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	PrintConsole();

	StartMusic();

	// initialize game resources here
	InitTextures();

	InitColors();
	InitGrid();
}

void Draw()
{
	ClearBackground();
	DrawBackground();

	// Put your own draw statements here
	switch (g_GameState)
	{
	case GameState::TITLE_SCREEN:
		DrawTitleScreen();
		break;
	case GameState::MAIN_MENU:
		DrawMainMenu();
		break;
	case GameState::GAME:
		DrawGrid();
		DrawPlayers();
		DrawPlayerColor(0);
		DrawPlayerColor(1);
		break;
	case GameState::GAME_OVER:
		DrawGrid();
		DrawGameOver();
		break;
	}
}

void Update(float elapsedSec)
{
	const float introLength{ 5.0f };

	g_MusicTime += elapsedSec;
	if (g_MusicTime > introLength && g_MusicTime - elapsedSec <= introLength)
	{
		StartMusic();
	}
	// process input, do physics 

	// e.g. Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void End()
{
	// free game resources here
	FreeResources();
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{
	
}

void OnKeyUpEvent(SDL_Keycode key)
{
	if (g_GameState == GameState::TITLE_SCREEN)
	{
		g_GameState = GameState::MAIN_MENU;
		return;
	}

	Point2i directionP1{};
	Point2i directionP2{};
	switch (key)
	{
	case SDLK_w:
	case SDLK_z:
		directionP1.y = 1;
		break;
	case SDLK_s:
		directionP1.y = -1;
		break;
	case SDLK_a:
	case SDLK_q:
		directionP1.x = -1;
		break;
	case SDLK_d:
		directionP1.x = 1;
		break;
	case SDLK_SPACE:
		SelectTile(0);
		break;
	case SDLK_UP:
		directionP2.y = 1;
		break;
	case SDLK_DOWN:
		directionP2.y = -1;
		break;
	case SDLK_LEFT:
		directionP2.x = -1;
		break;
	case SDLK_RIGHT:
		directionP2.x = 1;
		break;
	case SDLK_RETURN:
		SelectTile(1);
		break;
	case SDLK_r:
		if (g_GameState == GameState::GAME || g_GameState == GameState::GAME_OVER)
		{
			StartGame();
		}
		break;
	case SDLK_ESCAPE:
		if (g_GameState == GameState::MAIN_MENU)
		{
			g_GameState = GameState::TITLE_SCREEN;
		}
		else
		{
			g_GameState = GameState::MAIN_MENU;
		}
		break;
	case SDLK_i:
		PrintConsole();
		break;
	}

	MovePlayer(0, directionP1);
	MovePlayer(1, directionP2);
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{

}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	const Point2f mousePos{ float(e.x), float(g_WindowHeight - e.y) };
	if (g_GameState == GameState::MAIN_MENU)
	{
		CheckGridSizeButtons(mousePos);
		CheckNrColorsButtons(mousePos);
		CheckStartButton(mousePos);
	}
	////std::cout << "  [" << e.x << ", " << e.y << "]\n";
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//{
	//	//std::cout << "Left mouse button released\n";
	//	//Point2f mousePos{ float( e.x ), float( g_WindowHeight - e.y ) };
	//	break;
	//}
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here
void InitColors()
{
	for (int i{ 0 }; i < g_NrColors; ++i)
	{
		switch (Color(i))
		{
		case Color::GREEN:
			g_Colors[i] = Color4f{ 0.0f, 1.0f, 0.0f, 1.0f };
			break;
		case Color::ORANGE:
			g_Colors[i] = Color4f{ 1.0f, 0.5f, 0.0f, 1.0f };
			break;
		case Color::PURPLE:
			g_Colors[i] = Color4f{ 0.5f, 0.0f, 1.0f, 1.0f };
			break;
		case Color::YELLOW:
			g_Colors[i] = Color4f{ 1.0f, 1.0f, 0.0f, 1.0f };
			break;
		case Color::DISABLED:
			g_Colors[i] = Color4f{ 0.5f, 0.5f, 0.5f, 1.0f };
			break;
		case Color::RED:
			g_Colors[i] = Color4f{ 1.0f, 0.0f, 0.0f, 1.0f };
			break;
		case Color::BLUE:
			g_Colors[i] = Color4f{ 0.0f, 0.0f, 1.0f, 1.0f };
			break;
		case Color::MAGENTA:
			g_Colors[i] = Color4f{ 1.0f, 0.0f, 1.0f, 1.0f };
			break;
		case Color::CYAN:
			g_Colors[i] = Color4f{ 0.0f, 1.0f, 1.0f, 1.0f };
			break;
		case Color::DARK_GREEN:
			g_Colors[i] = Color4f{ 0.0f, 0.6f, 0.0f, 1.0f };
			break;
		case Color::BROWN:
			g_Colors[i] = Color4f{ 0.5f, 0.25f, 0.0f, 1.0f };
			break;
		case Color::TURQUOISE:
			g_Colors[i] = Color4f{ 0.0f, 1.0f, 0.6f, 1.0f };
			break;
		case Color::DARK_PINK:
			g_Colors[i] = Color4f{ 0.4f, 0.0f, 0.4f, 1.0f };
			break;
		}
	}
}

void InitPlayers()
{
	const std::string musicPath{ "Resources/Music/Game_Start.wav" };
	PlaySound(s2ws(musicPath).c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	g_MusicTime = 0 ;

	const Point2i spawnPoint1{ 0,0 };
	const Point2i spawnPoint2{ g_GridSize - 1, g_GridSize - 1 };

	g_Players[0].points = 0;
	g_Players[0].previousSelection.clear();
	g_Players[0].activated = true;
	g_Players[0].areaColor = Color::RED;
	g_Players[0].position = spawnPoint1;
	g_Players[0].currentColor = Color(rand() % g_NrColorsInField);
	g_Players[0].currentNrClicks = 0;
	RandomizeClicksBeforeClaim(0);

	g_Players[1].points = 0;
	g_Players[1].previousSelection.clear();
	g_Players[1].activated = true;
	g_Players[1].areaColor = Color::BLUE;
	g_Players[1].position = spawnPoint2;
	g_Players[1].currentColor = Color(rand() % g_NrColorsInField);
	g_Players[1].currentNrClicks = 0;
	RandomizeClicksBeforeClaim(1);
}

void InitGrid()
{
	if (g_pGrid != nullptr)
	{
		delete[] g_pGrid;
		g_pGrid = nullptr;
	}

	g_pGrid = new Color[g_GridSize * g_GridSize];

	for (int x{ 0 }; x < g_GridSize; ++x)
	{
		for (int y{ 0 }; y < g_GridSize; ++y)
		{
			const int gridIndex{ GetGridIndex(x,y) };
			g_pGrid[gridIndex] = Color(rand() % g_NrColorsInField);
		}
	}

	const float offset{ 20 };

	g_GridTileSize = (g_WindowHeight - offset * 2) / g_GridSize;
}

void InitTextures()
{
	const int fontSize{ 36 };

	TextureFromString("Player 1", "Resources/Fonts/Font.ttf", fontSize, Color4f{ 1.0f, 1.0f, 1.0f, 1.0f }, g_Players[0].nametexture);
	TextureFromString("Player 2", "Resources/Fonts/Font.ttf", fontSize, Color4f{ 1.0f, 1.0f, 1.0f, 1.0f }, g_Players[1].nametexture);
	TextureFromFile("Resources/Textures/player1_wins.png", g_Players[0].winTexture);
	TextureFromFile("Resources/Textures/player2_wins.png", g_Players[1].winTexture);
	TextureFromFile("Resources/Textures/player1.png", g_Players[0].gridTexture);
	TextureFromFile("Resources/Textures/player2.png", g_Players[1].gridTexture);
	TextureFromFile("Resources/Textures/player1controls.png", g_Players[0].controlsTexture);
	TextureFromFile("Resources/Textures/player2controls.png", g_Players[1].controlsTexture);
	TextureFromFile("Resources/Textures/titlescreen.png", g_TitleScreenTexture);
	TextureFromFile("Resources/Textures/draw.png", g_DrawTexture);
	TextureFromFile("Resources/Textures/mainmenu.png", g_MainMenuTexture);
	TextureFromFile("Resources/Textures/plus.png", g_PlusSignTexture);
	TextureFromFile("Resources/Textures/minus.png", g_MinusSignTexture);
	TextureFromFile("Resources/Textures/startbutton.png", g_StartButtonTexture);
	TextureFromFile("Resources/Textures/gameovercontrols.png", g_GameOverTexture);
	TextureFromString(std::to_string(g_GridSize) + "x" + std::to_string(g_GridSize), "Resources/Fonts/Font.ttf", fontSize, Color4f{ 1.0f, 1.0f, 1.0F, 1.0f }, g_GridSizeTexture);
	TextureFromString(std::to_string(g_NrColorsInField), "Resources/Fonts/Font.ttf", fontSize, Color4f{ 1.0f, 1.0f, 1.0F, 1.0f }, g_NrColorsTexture);
}

void RandomizeClicksBeforeClaim(int playerIndex)
{
	const int minClicks{ 3 };
	const int maxClicks{ 6 };

	g_Players[playerIndex].clicksBeforeClaim = rand() % (maxClicks - minClicks + 1) + minClicks;
}

int GetGridIndex(int column, int row)
{
	return row * g_GridSize + column;
}

void DrawGrid()
{
	const float startX{ g_WindowWidth / 2.0f - g_GridSize / 2.0f * g_GridTileSize };
	const float startY{ g_WindowHeight / 2.0f - g_GridSize / 2.0f * g_GridTileSize };
	const float borderWidth{ 5.0f };

	for (int x{ 0 }; x < g_GridSize; ++x)
	{
		for (int y{ 0 }; y < g_GridSize; ++y)
		{
			const float currentX{ startX + x * g_GridTileSize };
			const float currentY{ startY + y * g_GridTileSize };
			const Color currentColor{ g_pGrid[GetGridIndex(x,y)] };
			const Color4f currentColorValue{ g_Colors[int(currentColor)] };

			SetColor(currentColorValue);
			FillRect(currentX, currentY, g_GridTileSize, g_GridTileSize);

			const float blackMultiplier{ 0.75f };

			SetColor(currentColorValue.r * blackMultiplier, currentColorValue.g * blackMultiplier, currentColorValue.b * blackMultiplier, 1.0f);
			DrawRect(currentX, currentY, g_GridTileSize, g_GridTileSize);
		}
	}

	SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	DrawRect(startX, startY, g_GridSize * g_GridTileSize, g_GridSize * g_GridTileSize, borderWidth);
}

void DrawPlayers()
{
	const float startX{ g_WindowWidth / 2.0f - g_GridSize / 2.0f * g_GridTileSize };
	const float startY{ g_WindowHeight / 2.0f - g_GridSize / 2.0f * g_GridTileSize };

	for (int i{ 0 }; i < g_NrPlayers; ++i)
	{
		Player& player{ g_Players[i] };

		if (!player.activated)
		{
			continue;
		}

		Rectf rect{ startX + player.position.x * g_GridTileSize - 1, startY + player.position.y * g_GridTileSize, g_GridTileSize + 1, g_GridTileSize };

		DrawTexture(player.gridTexture, rect);
	}
}

void DrawPlayerColor(int playerIndex)
{
	const float width{ 75.0f };
	const float height{ 50.0f };
	const float borderWidth{ 3.0f };

	const float offsetMid{ g_WindowWidth / 4.0f + g_GridSize * g_GridTileSize / 4.0f - width / 2.0f };
	float xPos{};
	float yPos{ g_WindowHeight / 5.0f * 4.0f };

	const float gridY{ g_WindowHeight / 2.0f - g_GridSize / 2.0f * g_GridTileSize };

	if (playerIndex == 1)
	{
		xPos = g_WindowWidth / 2.0f + offsetMid;
	}
	else
	{
		xPos = g_WindowWidth / 2.0f - offsetMid - width;
		yPos = g_WindowHeight - yPos - height;
	}

	SetColor(g_Colors[int(g_Players[playerIndex].currentColor)]);
	FillRect(xPos, yPos, width, height);
	SetColor(1.0f, 1.0f, 1.0f);
	DrawRect(xPos, yPos, width, height , borderWidth);

	const float textOffset{ 30.0f };
	const Texture& texture{ g_Players[playerIndex].nametexture };

	float textY{};
	if (playerIndex == 0)
	{
		textY = gridY + textOffset;
	}
	else
	{
		textY =  g_WindowHeight - gridY - texture.height - textOffset;
	}
	const float textX{ xPos + width / 2.0f - texture.width / 2.0f };

	DrawTexture(texture, Point2f{ textX, textY });
	
	const float controlsOffset{ 250 };
	const Texture& controls{ g_Players[playerIndex].controlsTexture };

	float controlsY{};
	if (playerIndex == 0)
	{
		controlsY = gridY + controlsOffset;
	}
	else
	{
		controlsY = g_WindowHeight - gridY - controls.height - controlsOffset;
	}
	const float controlsX{ xPos + width / 2.0f - controls.width / 2.0f };

	DrawTexture(controls, Point2f{ controlsX, controlsY });
}

void DrawBackground()
{
	SetColor(g_Colors[int(Color::RED)]);
	FillRect(0, 0, g_WindowWidth / 2.0f, g_WindowHeight);
	SetColor(g_Colors[int(Color::BLUE)]);
	FillRect(g_WindowWidth / 2.0f, 0, g_WindowWidth / 2.0f, g_WindowHeight);
}

void DrawTitleScreen()
{
	DrawTexture(g_TitleScreenTexture, Point2f{ 0,0 });
}

void DrawMainMenu()
{
	DrawTexture(g_MainMenuTexture, Point2f{ 0,0 });
	const float textOffset{ 35 + g_GridSizeTexture.height };
	const float gridButtonOffset{ 160 + g_PlusSignTexture.width / 2.0f };
	const float colorsButtonOffset{ 135 + g_PlusSignTexture.width / 2.0f };
	const Point2f gridSizePosition{ g_WindowWidth / 4.0f, g_WindowHeight / 2.0f - textOffset };
	const Point2f colorsPosition{ g_WindowWidth / 4.0f * 3, g_WindowHeight / 2.0f - textOffset };
	const Point2f startPosition{ g_WindowWidth / 2.0f - g_StartButtonTexture.width / 2.0f, g_WindowHeight / 6.0f };

	if (g_GridSize > g_MinGridSize)
	{
		DrawTexture(g_MinusSignTexture, Point2f{ gridSizePosition.x - gridButtonOffset, gridSizePosition.y - (g_MinusSignTexture.height - g_GridSizeTexture.height) / 2.0f });
	}
	DrawTexture(g_GridSizeTexture, Point2f{ gridSizePosition.x - g_GridSizeTexture.width / 2.0f, gridSizePosition.y });
	DrawTexture(g_PlusSignTexture, Point2f{ gridSizePosition.x + gridButtonOffset - g_PlusSignTexture.width, gridSizePosition.y - (g_MinusSignTexture.height - g_GridSizeTexture.height) / 2.0f });

	if (g_NrColorsInField > g_MinColors)
	{
		DrawTexture(g_MinusSignTexture, Point2f{ colorsPosition.x - colorsButtonOffset, colorsPosition.y - (g_MinusSignTexture.height - g_NrColorsTexture.height) / 2.0f });
	}
	DrawTexture(g_NrColorsTexture, Point2f{ colorsPosition.x - g_NrColorsTexture.width / 2.0f, colorsPosition.y });
	if (g_NrColorsInField < g_MaxColors)
	{
		DrawTexture(g_PlusSignTexture, Point2f{ colorsPosition.x + colorsButtonOffset - g_PlusSignTexture.width, colorsPosition.y - (g_MinusSignTexture.height - g_NrColorsTexture.height) / 2.0f });
	}

	DrawTexture(g_StartButtonTexture, startPosition);
}

void DrawGameOver()
{
	const Point2f texturePosition{ 0.0f, g_WindowHeight / 3.0f * 2.0f - g_DrawTexture.height / 2.0f };
	const Point2f controlsPosition{ 0.0f, g_WindowHeight / 5.0f - g_GameOverTexture.height / 2.0f };

	DrawTexture(g_GameOverTexture, controlsPosition);

	if (g_Players[0].points > g_Players[1].points)
	{
		DrawTexture(g_Players[0].winTexture, texturePosition);
	}
	else if (g_Players[1].points > g_Players[0].points)
	{
		DrawTexture(g_Players[1].winTexture, texturePosition);
	}
	else
	{
		DrawTexture(g_DrawTexture, texturePosition);
	}
}

void MovePlayer(int playerIndex, const Point2i& direction)
{
	Player& player{ g_Players[playerIndex] };

	if (!player.activated)
	{
		return;
	}

	player.position.x += direction.x;
	player.position.y += direction.y;

	if (player.position.x < 0 || player.position.x == g_GridSize)
	{
		player.position.x -= direction.x;
	}
	if (player.position.y < 0 || player.position.y == g_GridSize)
	{
		player.position.y -= direction.y;
	}
}

void SelectTile(int playerIndex)
{
	Player& player{ g_Players[playerIndex] };

	if (TilesContainsPosition(player.previousSelection, player.position))
	{
		return;
	}

	Color currentColor{ g_pGrid[GetGridIndex(player.position.x, player.position.y)] };

	if (currentColor == Color::RED || currentColor == Color::BLUE || currentColor == Color::DISABLED || currentColor == player.currentColor)
	{
		return;
	}

	std::vector<Point2i> checkedTiles{};
	std::vector<Point2i> changedTiles{};
	SetTileColor(player.position, player.currentColor, currentColor, checkedTiles, changedTiles);

	player.previousSelection = changedTiles;

	++player.currentNrClicks;
	++g_NrTotalClicks;
	if (player.currentNrClicks == player.clicksBeforeClaim)
	{
		player.currentColor = player.areaColor;
		player.currentNrClicks = -1;
		RandomizeClicksBeforeClaim(playerIndex);
	}
	else
	{
		player.currentColor = Color(rand() % g_NrColorsInField);
	}

	const int NrClicksBeforeDisable{ 20 };

	if (g_NrTotalClicks % 15 == 0)
	{
		const int minDisabled{ 2 };
		const int maxDisabled{ 5 };
		int amountDisabled{ rand() % (maxDisabled - minDisabled + 1) + minDisabled };
		const int tilesLeft{ GetAmountRemainingTiles() };

		if (amountDisabled >= tilesLeft)
		{
			amountDisabled = tilesLeft - 1;
		}

		for (int i{ 0 }; i < amountDisabled; ++i)
		{
			Point2i disabledPosition{};
			int currentGridIndex{};
			Color tileColor{ };

			do {
				disabledPosition.x = rand() % g_GridSize;
				disabledPosition.y = rand() % g_GridSize;
				currentGridIndex = GetGridIndex(disabledPosition.x, disabledPosition.y);
				tileColor = g_pGrid[currentGridIndex];
			} while (tileColor == Color::BLUE || tileColor == Color::RED || tileColor == Color::DISABLED);

			g_pGrid[currentGridIndex] = Color::DISABLED;
		}
	}

	if (CheckEndGame())
	{
		g_GameState = GameState::GAME_OVER;
		g_Players[0].activated = false;
		g_Players[1].activated = false;
	}
}

void SetTileColor(const Point2i& tilePosition, const Color& newColor, const Color& previousColor, std::vector<Point2i>& checkedTiles, std::vector<Point2i>& changedTiles)
{
	if (TilesContainsPosition(checkedTiles, tilePosition))
	{
		return;
	}

	if (tilePosition.x < 0 ||
		tilePosition.x == g_GridSize ||
		tilePosition.y < 0 ||
		tilePosition.y == g_GridSize)
	{
		return;
	}

	checkedTiles.push_back(tilePosition);

	const Color& currentColor{ g_pGrid[GetGridIndex(tilePosition.x, tilePosition.y)] };

	if (currentColor == previousColor)
	{
		g_pGrid[GetGridIndex(tilePosition.x, tilePosition.y)] = newColor;

		changedTiles.push_back(tilePosition);

		if (currentColor == Color::RED)
		{
			++g_Players[0].points;
		}
		else if (currentColor == Color::BLUE)
		{
			++g_Players[1].points;
		}

		SetTileColor(Point2i{ tilePosition.x, tilePosition.y + 1 }, newColor, previousColor, checkedTiles, changedTiles);
		SetTileColor(Point2i{ tilePosition.x, tilePosition.y - 1 }, newColor, previousColor, checkedTiles, changedTiles);
		SetTileColor(Point2i{ tilePosition.x + 1, tilePosition.y }, newColor, previousColor, checkedTiles, changedTiles);
		SetTileColor(Point2i{ tilePosition.x - 1, tilePosition.y }, newColor, previousColor, checkedTiles, changedTiles);
	}
}

bool TilesContainsPosition(const std::vector<Point2i>& checkedTiles, Point2i position)
{
	for (const Point2i& tile : checkedTiles)
	{
		if (tile.x == position.x && tile.y == position.y)
		{
			return true;
		}
	}
	return false;
}

bool CheckEndGame()
{
	if (CanPlayerSelect(g_Players[0]) || CanPlayerSelect(g_Players[1]))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CanPlayerSelect(const Player& player)
{
	for (int x{ 0 }; x < g_GridSize; ++x)
	{
		for (int y{ 0 }; y < g_GridSize; ++y)
		{
			const int i{ y * g_GridSize + x };
			const Color& color{ g_pGrid[i] };
			if (color == Color::BLUE || color == Color::RED || color == Color::DISABLED)
			{
				continue;
			}
			if (color == player.currentColor)
			{
				continue;
			}
			if (TilesContainsPosition(player.previousSelection, Point2i{ x,y }))
			{
				continue;
			}
			return true;
		}
	}
	return false;
}

void StartMusic()
{
	const std::string musicPath{ "Resources/Music/Color_Royale.wav" };
	PlaySound(s2ws(musicPath).c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void GetTileOfColor(const Point2i& tilePosition, Color color, std::vector<Point2i>& checkedTiles, std::vector<Point2i>& colorTiles)
{
	if (tilePosition.x < 0 ||
		tilePosition.x == g_GridSize ||
		tilePosition.y < 0 ||
		tilePosition.y == g_GridSize)
	{
		return;
	}

	if (TilesContainsPosition(checkedTiles, tilePosition))
	{
		return;
	}

	checkedTiles.push_back(tilePosition);

	Color currentColor{ g_pGrid[GetGridIndex(tilePosition.x,tilePosition.y)] };

	if (currentColor == color)
	{
		colorTiles.push_back(tilePosition);

		GetTileOfColor(Point2i{ tilePosition.x, tilePosition.y + 1 }, color, checkedTiles, colorTiles);
		GetTileOfColor(Point2i{ tilePosition.x, tilePosition.y - 1 }, color, checkedTiles, colorTiles);
		GetTileOfColor(Point2i{ tilePosition.x + 1, tilePosition.y }, color, checkedTiles, colorTiles);
		GetTileOfColor(Point2i{ tilePosition.x - 1, tilePosition.y }, color, checkedTiles, colorTiles);
	}
}

int GetAmountRemainingTiles()
{
	int amount{};
	for (int x{ 0 }; x < g_GridSize; ++x)
	{
		for (int y{ 0 }; y < g_GridSize; ++y)
		{
			const Color& currentColor{ g_pGrid[GetGridIndex(x,y)] };

			if (currentColor == Color::RED || currentColor == Color::BLUE || currentColor == Color::DISABLED)
			{
				continue;
			}

			++amount;
		}
	}
	return amount;
}

void FreeResources()
{
	delete[] g_pGrid;

	g_pGrid = nullptr;

	DeleteTexture(g_Players[0].nametexture);
	DeleteTexture(g_Players[0].winTexture);
	DeleteTexture(g_Players[0].gridTexture);
	DeleteTexture(g_Players[0].controlsTexture);
	DeleteTexture(g_Players[1].nametexture);
	DeleteTexture(g_Players[1].winTexture);
	DeleteTexture(g_Players[1].gridTexture);
	DeleteTexture(g_Players[1].controlsTexture);
	DeleteTexture(g_TitleScreenTexture);
	DeleteTexture(g_DrawTexture);
	DeleteTexture(g_MainMenuTexture);
	DeleteTexture(g_PlusSignTexture);
	DeleteTexture(g_MinusSignTexture);
	DeleteTexture(g_StartButtonTexture);
	DeleteTexture(g_GridSizeTexture);
	DeleteTexture(g_NrColorsTexture);
	DeleteTexture(g_GameOverTexture);
}

void CheckGridSizeButtons(const Point2f& mousePos)
{
	const float textOffset{ 35 + g_GridSizeTexture.height };
	const float gridButtonOffset{ 160 + g_PlusSignTexture.width / 2.0f };
	const Point2f gridSizePosition{ g_WindowWidth / 4.0f, g_WindowHeight / 2.0f - textOffset };
	const Point2f minusPosition{ gridSizePosition.x - gridButtonOffset, gridSizePosition.y - (g_MinusSignTexture.height - g_GridSizeTexture.height) / 2.0f };
	const Point2f plusPosition{ gridSizePosition.x + gridButtonOffset - g_PlusSignTexture.width, gridSizePosition.y - (g_MinusSignTexture.height - g_GridSizeTexture.height) / 2.0f };
	
	if (g_GridSize > g_MinGridSize)
	{
		if (mousePos.x > minusPosition.x && mousePos.x < minusPosition.x + g_MinusSignTexture.width)
		{
			if (mousePos.y > minusPosition.y && mousePos.y < minusPosition.y + g_MinusSignTexture.height)
			{
				--g_GridSize;
				DeleteTexture(g_GridSizeTexture);
				TextureFromString(std::to_string(g_GridSize) + "x" + std::to_string(g_GridSize), "Resources/Fonts/Font.ttf", 36, Color4f{ 1.0f, 1.0f, 1.0F, 1.0f }, g_GridSizeTexture);
			}
		}
	}

	if (mousePos.x > plusPosition.x && mousePos.x < plusPosition.x + g_PlusSignTexture.width)
	{
		if (mousePos.y > plusPosition.y && mousePos.y < plusPosition.y + g_PlusSignTexture.height)
		{
			++g_GridSize;
			DeleteTexture(g_GridSizeTexture);
			TextureFromString(std::to_string(g_GridSize) + "x" + std::to_string(g_GridSize), "Resources/Fonts/Font.ttf", 36, Color4f{ 1.0f, 1.0f, 1.0F, 1.0f }, g_GridSizeTexture);
		}
	}
}

void CheckNrColorsButtons(const Point2f& mousePos)
{
	const float textOffset{ 35 + g_GridSizeTexture.height };
	const float colorsButtonOffset{ 135 + g_PlusSignTexture.width / 2.0f };
	const Point2f colorsPosition{ g_WindowWidth / 4.0f * 3, g_WindowHeight / 2.0f - textOffset };
	const Point2f minusPosition{ colorsPosition.x - colorsButtonOffset, colorsPosition.y - (g_MinusSignTexture.height - g_NrColorsTexture.height) / 2.0f };
	const Point2f plusPosition{ colorsPosition.x + colorsButtonOffset - g_PlusSignTexture.width, colorsPosition.y - (g_MinusSignTexture.height - g_NrColorsTexture.height) / 2.0f };

	if (g_NrColorsInField > g_MinColors)
	{
		if (mousePos.x > minusPosition.x && mousePos.x < minusPosition.x + g_MinusSignTexture.width)
		{
			if (mousePos.y > minusPosition.y && mousePos.y < minusPosition.y + g_MinusSignTexture.height)
			{
				--g_NrColorsInField;
				DeleteTexture(g_NrColorsTexture);
				TextureFromString(std::to_string(g_NrColorsInField), "Resources/Fonts/Font.ttf", 36, Color4f{ 1.0f, 1.0f, 1.0F, 1.0f }, g_NrColorsTexture);
			}
		}
	}

	if (g_NrColorsInField < g_MaxColors)
	{
		if (mousePos.x > plusPosition.x && mousePos.x < plusPosition.x + g_PlusSignTexture.width)
		{
			if (mousePos.y > plusPosition.y && mousePos.y < plusPosition.y + g_PlusSignTexture.height)
			{
				++g_NrColorsInField;
				DeleteTexture(g_NrColorsTexture);
				TextureFromString(std::to_string(g_NrColorsInField), "Resources/Fonts/Font.ttf", 36, Color4f{ 1.0f, 1.0f, 1.0F, 1.0f }, g_NrColorsTexture);
			}
		}
	}
}

void CheckStartButton(const Point2f& mousePos)
{
	const Point2f startPosition{ g_WindowWidth / 2.0f - g_StartButtonTexture.width / 2.0f, g_WindowHeight / 6.0f };

	if (mousePos.x > startPosition.x && mousePos.x < startPosition.x + g_StartButtonTexture.width)
	{
		if (mousePos.y > startPosition.y && mousePos.y < startPosition.y + g_StartButtonTexture.height)
		{
			StartGame();
		}
	}
}

void StartGame()
{
	InitGrid();
	InitPlayers();
	g_GameState = GameState::GAME;
}

void PrintConsole()
{
	std::cout << "-=-= Welcome to COLOR RUSH! =-=-" << std::endl;
	std::cout << std::endl;
	std::cout << "--= Goal of the game =--" << std::endl;
	std::cout << "Change as many colored blocks into your own color!" << std::endl;
	std::cout << "Keep up the pace! The other player is trying to do the same thing!" << std::endl;
	std::cout << "Keep moving! You can't click the same area twice in a row!" << std::endl;
	std::cout << "Don't forget, you can't click on blocks with the same color as you!" << std::endl;
	std::cout << std::endl;
	std::cout << "--= In main menu: =--" << std::endl;
	std::cout << "ESC : Return to title screen" << std::endl;
	std::cout << "Mouse controls : Click the buttons" << std::endl;
	std::cout << std::endl;
	std::cout << "--= In game: =--" << std::endl;
	std::cout << "ESC : Return to main menu" << std::endl;
	std::cout << "R : Restart the game" << std::endl;
	std::cout << "WASD : Move as player 1" << std::endl;
	std::cout << "SPACE : Select as player 1" << std::endl;
	std::cout << "ARROW KEYS : Move as player 2" << std::endl;
	std::cout << "ENTER : Select as player 2" << std::endl;
	std::cout << std::endl;
	std::cout << "--= In game over screen: =--" << std::endl;
	std::cout << "ESC : Return to main menu" << std::endl;
	std::cout << "R : Restart the game" << std::endl;
}
#pragma endregion ownDefinitions