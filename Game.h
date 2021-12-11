#pragma once
using namespace utils;
#include "enums.h"
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Color Rush - De Keukelaere Sander & Dumoulin Glenn - 1DAE21N" };

// Change the window dimensions here
float g_WindowWidth{ 1280 };
float g_WindowHeight{ 720 };
#pragma endregion gameInformation

struct Player
{
	Texture gridTexture{};
	Texture nametexture{};
	Texture winTexture{};
	Texture controlsTexture{};

	bool activated{};

	Color areaColor{};
	Point2i position{};
	Color currentColor{};

	std::vector<Point2i> previousSelection{};

	int clicksBeforeClaim{};
	int currentNrClicks{};
	int points{};
};

#pragma region ownDeclarations
// Declare your own global variables here
const int g_NrColors{ int(Color::BLUE)+1 };
const int g_NrPlayers{ 2 };
const int g_MinColors{ 4 };
const int g_MaxColors{ 10 };
const int g_MinGridSize{ 5 };
Color4f g_Colors[g_NrColors]{};
Player g_Players[g_NrPlayers]{};

int g_NrColorsInField{ 4 };
int g_GridSize{ 10 };
float g_GridTileSize{ 30 };

Color* g_pGrid{ nullptr };

int g_NrTotalClicks{ 0 };
float g_MusicTime{ 100000 };

GameState g_GameState{ GameState::TITLE_SCREEN };

Texture g_TitleScreenTexture{};
Texture g_DrawTexture{};
Texture g_MainMenuTexture{};
Texture g_PlusSignTexture{};
Texture g_MinusSignTexture{};
Texture g_StartButtonTexture{};
Texture g_GridSizeTexture{};
Texture g_NrColorsTexture{};
Texture g_GameOverTexture{};
// Declare your own functions here
void InitColors();
void InitPlayers();
void InitGrid();
void InitTextures();
void RandomizeClicksBeforeClaim(int playerIndex);

void DrawBackground();
void DrawGrid();
void DrawPlayers();
void DrawPlayerColor(int playerIndex);
void DrawTitleScreen();
void DrawMainMenu();
void DrawGameOver();

void MovePlayer(int index, const Point2i& direction);
void SetTileColor(const Point2i& tilePosition, const Color& newColor, const Color& previousColor, std::vector<Point2i>& checkedTiles, std::vector<Point2i>& changedTiles);
bool TilesContainsPosition(const std::vector<Point2i>& checkedTiles, Point2i position);
void SelectTile(int playerIndex);
void GetTileOfColor(const Point2i& tilePosition, Color color, std::vector<Point2i>& checkedTiles, std::vector<Point2i>& colorTiles);
int GetAmountRemainingTiles();
bool CheckEndGame();
bool CanPlayerSelect(const Player& player);
void StartMusic();
void StartGame();
void PrintConsole();

void CheckGridSizeButtons(const Point2f& mousePos);
void CheckNrColorsButtons(const Point2f& mousePos);
void CheckStartButton(const Point2f& mousePos);

int GetGridIndex(int column, int row);

void FreeResources();
#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
