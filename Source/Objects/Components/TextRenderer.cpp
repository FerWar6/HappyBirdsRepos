#include "TextRenderer.h"
#include "Objects/Object.h"
#include "Managers/ServiceLocator.h"
#include "Engine/PreLoader.h"

TextRenderer::TextRenderer(std::string fName, std::string textContent)
	: Component(TEXT_RENDERER),
	fontName(fName)
{
	text.setFont(sl::GetPreLoader().GetFont(fName));
	text.setCharacterSize(30); // TODO - add size to this component
	text.setPosition(object.GetPos());
	text.setOrigin(object.GetSize() / 2.f); // TODO - improved centering of text
	text.setString(textContent);
}

void TextRenderer::Render(sf::RenderWindow& window)
{
	window.draw(text);
}

std::string TextRenderer::GetSaveData()
{
	std::string data;
	data += std::to_string(type) + " ";
	data += fontName + " ";
	return data;
}
