#include <iostream>
#include "Application.h"
#include "Windows.h"

int main() {
	Window window(" Engine Test");
	double lastTime = glfwGetTime();
	int frameCount = 0;
	float elapsedTime = 0.0;
	while (!window.closed())
	{
		window.clear();
		// Calculate delta time.
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		//Render
		elapsedTime += deltaTime;
		frameCount++;
		window.update(deltaTime);

		if (elapsedTime >= 1.0)
		{
			std::cout << frameCount / elapsedTime << " fps" << std::endl;
			elapsedTime = 0.0;
			frameCount = 0;
		}
	}

	glfwTerminate();
	return 0;
}