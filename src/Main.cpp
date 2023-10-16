#include <vk_engine.h>

#include "Input/Event.h"
#include <iostream>

void Test1()
{
	std::cout << 1 << std::endl;
}

void Test2()
{
	std::cout << 2 << std::endl;
}

int main(int argc, char* argv[])
{
	VulkanEngine engine;

	engine.init();
	
    auto event = HarvestHavoc::Input::Event();
	size_t id = event.AddListener(Test1);
	event.AddListener(Test2);
	event.Invoke();
	event.Invoke();
	event.RemoveListener(id);
	event.Invoke();
	event.Invoke();
	event.Invoke();

	engine.run();

	engine.cleanup();

	return 0;
}
