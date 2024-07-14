#if !defined(SHIPPING)
#include "..\Content\ContentLoader.h"
#include "..\Components\Script.h"
#include <thread>

bool engine_initialize()
{
	bool result{ PotatoEngine::content::load_game() };
	return true;
}

void engine_update()
{
	PotatoEngine::script::update(10.f);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void engine_shutdown()
{
	PotatoEngine::content::unload_game();
}
#endif // !defined(SHIPPING)