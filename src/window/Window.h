#ifndef WINDOW_WINDOW_H_
#define WINDOW_WINDOW_H_

#include "../typedefs.h"
#include "../settings.h"

#include <stack>
#include <vector>

#include <glm/glm.hpp>

class GLFWwindow;

class Window {
	static GLFWwindow* window;
	static std::stack<glm::vec4> scissorStack;
	static glm::vec4 scissorArea;
public:
	static uint width;
	static uint height;
	static int initialize(DisplaySettings& settings);
	static void terminate();

	static void viewport(int x, int y, int width, int height);
	static void setCursorMode(int mode);
	static bool isShouldClose();
	static void setShouldClose(bool flag);
	static void swapBuffers();
	static void swapInterval(int interval);

	static void pushScissor(glm::vec4 area);
	static void popScissor();
	static void resetScissor();

	static void clear();

	static double time();
};

#endif /* WINDOW_WINDOW_H_ */
