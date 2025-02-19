#include "Grid.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"
#include <SFML/Window/Cursor.hpp>
Grid::Grid(sf::RenderWindow& w, InputManager& im)
	: Object(),
	window(w),
	inputMan(im)
{
	//grid texture should be 25x25
	sf::Texture& gridTxr = sl::GetPreLoader().GetTexture("GridSquare");
	gridTxr.setRepeated(true);
	sf::Vector2u winSize = window.getSize();
	gridSprite.setTexture(gridTxr);
	sf::IntRect rect(0, 0, winSize.x, winSize.y);
	gridSprite.setTextureRect(rect);

	sf::Texture& gridCursorTxr = sl::GetPreLoader().GetTexture("GridHighlight");
	gridCursorSprite.setTexture(gridCursorTxr);

	sf::Cursor cursor;
	sf::Texture& txr = sl::GetPreLoader().GetTexture("GridCursor");
	sf::Image img = txr.copyToImage();
	cursor.loadFromPixels(img.getPixelsPtr(), txr.getSize(), sf::Vector2u(txr.getSize().x/2, txr.getSize().y/2));
	window.setMouseCursor(cursor);
}

void Grid::Update()
{
	posOnGrid = CalculatePosOnGrid(inputMan.GetMousePos());
	if (gridCursorSprite.getPosition() != (sf::Vector2f)posOnGrid)
		gridCursorSprite.setPosition((sf::Vector2f)posOnGrid);
}

void Grid::Render(sf::RenderWindow& window)
{
	//window.setMouseCursorVisible(false);
	window.draw(gridSprite);

	window.draw(gridCursorSprite);
}

sf::Vector2i Grid::GetPosOnGrid()
{
	return posOnGrid;
}

sf::Vector2i Grid::CalculatePosOnGrid(sf::Vector2i cursorPos)
{
	sf::Vector2i gridPos = sf::Vector2i();
	float xpos = cursorPos.x / 25;
	gridPos.x = std::floor(xpos) * 25;
	float ypos = cursorPos.y / 25;
	gridPos.y = std::floor(ypos) * 25;
	return gridPos;
}