#include <SFML/Graphics.hpp>
#include "Engine/EngineCore.h"
#include <cstdlib>
int main() 
{
	EngineCore* core = (EngineCore*)malloc(sizeof(EngineCore));
	core = new EngineCore();
    return 0;
}