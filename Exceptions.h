#include <iostream>
#include <exception>
using namespace std;

namespace Stormcloud {
	class GLFWFailedToInitializeException : exception {
		virtual const char* what() const throw()
		{
			return "GLFW Failed to Initialize!";
		}

	} GLFWFailedToInitializeException;
}
