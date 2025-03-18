#include "EditorMoveTool.h"
#include "Managers/ServiceLocator.h"
#include "Managers/InputManager.h"
#include "Engine/Scenes/SceneEditor.h"
#include "Engine/PreLoader.h"
#include "Objects/Object.h"
EditorMoveTool::EditorMoveTool(Object*& selObj)
	: UIElement(),
	selectedObj(selObj),
	inputMan(sl::GetInputManager())
{
	sf::Texture& txrRef = sl::GetPreLoader().GetTexture("EditorMove");
	moveSprite.setTexture(txrRef);
	moveSprite.setOrigin(sf::Vector2f(8, 92));
	//	this needs a sprite and three very specific buttons, 
	//	if any of the buttons are pressed itll give controll to move the object in spefific ways
}

void EditorMoveTool::Update()
{
	int increment = 50;
	if (inputMan.GetKeyDownRepeat(ARROW_UP) && selectedObj) {
		sf::Vector2f newPos = selectedObj->GetPos();
		newPos.y -= increment;
		selectedObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDownRepeat(ARROW_DOWN) && selectedObj) {
		sf::Vector2f newPos = selectedObj->GetPos();
		newPos.y += increment;
		selectedObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDownRepeat(ARROW_LEFT) && selectedObj) {
		sf::Vector2f newPos = selectedObj->GetPos();
		newPos.x -= increment;
		selectedObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDownRepeat(ARROW_RIGHT) && selectedObj) {
		sf::Vector2f newPos = selectedObj->GetPos();
		newPos.x += increment;
		selectedObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDown(MOUSE_L) && HoveringOver()) {
		std::cout << "clicked on movetool \n";
	}
}

void EditorMoveTool::Render(sf::RenderWindow& window)
{
	if (selectedObj) {
		moveSprite.setPosition(selectedObj->GetPos());
		if (HoveringOver()) moveSprite.setColor(sf::Color(200, 200, 200));
		else moveSprite.setColor(sf::Color(255, 255, 255));
		window.draw(moveSprite);
	}
}

void EditorMoveTool::HandleClick()
{

}

bool EditorMoveTool::HoveringOver()
{
	sf::Vector2i mP = inputMan.GetMousePos();
	sf::Vector2i p = (sf::Vector2i)moveSprite.getGlobalBounds().getPosition();
	sf::Vector2i s = (sf::Vector2i)moveSprite.getGlobalBounds().getSize();
	return mP.x > p.x && mP.x < p.x + s.x && mP.y > p.y && mP.y < p.y + s.y;
}
