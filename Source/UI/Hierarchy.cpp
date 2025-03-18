#include "Hierarchy.h"
#include "Engine/Scenes/SceneEditor.h"
#include "Objects/Object.h"
#include "Managers/ServiceLocator.h"
#include "Managers/InputManager.h"
#include "Engine/PreLoader.h"
Hierarchy::Hierarchy(std::vector<Object*>& objs)
	: UIElement(),
	inputMan(sl::GetInputManager()),
	objects(objs)
{
	titleTxt.setFont(sl::GetPreLoader().GetFont("goofy"));
	titleTxt.setPosition(sf::Vector2f(100, 100));
	titleTxt.setString("goffy\ngoofy\ngoooy");
}

void Hierarchy::Update()
{
	if (objects.size() != objectsTxts.size()) UpdateObjTxtVec();
	UpdateObjTxt();
	for (int i = 0; i < objectsTxts.size(); i++) {
		sf::Rect rect = objectsTxts[i].getGlobalBounds();
		if (inputMan.GetKeyDown(MOUSE_L) && HoveringOver((sf::Vector2i)rect.getSize(), (sf::Vector2i)rect.getPosition())) {
			sl::GetSceneEditor().SetSelectedObj(objects[i]);
		}
	}
}

void Hierarchy::Render(sf::RenderWindow& window)
{
	for (auto txt : objectsTxts) {
		window.draw(txt);
		sf::Rect rect = txt.getGlobalBounds();
		if (HoveringOver((sf::Vector2i)rect.getSize(), (sf::Vector2i)rect.getPosition())) {

			sf::RectangleShape highlight(sf::Vector2f(rect.width, rect.height));

			highlight.setPosition(rect.left, rect.top);
			highlight.setFillColor(sf::Color(100));
			window.draw(highlight);
		}
	}
	//sf::FloatRect textBounds = titleTxt.getGlobalBounds();
	//int border = 7;
	//int grayness = 50;
	//sf::Color color = sf::Color(grayness, grayness, grayness);
	//// Create a rectangle with the same size
	//sf::RectangleShape outline(sf::Vector2f(textBounds.width, textBounds.height));

	//// Position it at the text’s position
	//outline.setPosition(textBounds.left, textBounds.top);
	//
	//outline.setFillColor(color);
	//outline.setOutlineColor(color);
	//outline.setOutlineThickness(border);
	//
	//window.draw(outline);
	//window.draw(titleTxt);
}

void Hierarchy::UpdateObjTxt()
{
	sf::Vector2f pos(100, 100);
	int margin = 35;
	for (int i = 0; i < objectsTxts.size(); i++) {
		objectsTxts[i].setString("object");
		objectsTxts[i].setPosition(pos.x, pos.y + (margin * i));
	}
}

void Hierarchy::UpdateObjTxtVec()
{
	if (objects.size() > objectsTxts.size()) {
		for (int i = 0; i < objects.size() - objectsTxts.size(); i++) {
			sf::Text txt;
			txt.setFont(sl::GetPreLoader().GetFont("goofy"));
			objectsTxts.push_back(txt);
		}
	}
	else {
		int amountToRemove = objectsTxts.size() - objects.size();
		objectsTxts.erase(objectsTxts.end() - amountToRemove, objectsTxts.end());
	}
}

bool Hierarchy::HoveringOver(sf::Vector2i s, sf::Vector2i p)
{
	sf::Vector2i mP = inputMan.GetMousePos();
	return mP.x > p.x && mP.x < p.x + s.x && mP.y > p.y && mP.y < p.y + s.y;
}

int Hierarchy::GetHoverPos()
{
	sf::Rect textBounds = titleTxt.getGlobalBounds();
	sf::Vector2i s = (sf::Vector2i)textBounds.getSize();
	sf::Vector2i p = (sf::Vector2i)textBounds.getPosition();
	sf::Vector2i mP = inputMan.GetMousePos();

	return ceil(mP.y / (s.y / objects.size()));
}