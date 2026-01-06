#ifdef CONSOLE_APP
#include <iostream>
#else
#include <windows.h>
#endif

#include "application/SampleApplication.h"

#ifdef CONSOLE_APP
int main(int argc, char* argv[])
{
	int result = 0;
	try
	{
		SampleApplication().run();
	}
	catch (const std::string& message)
	{
		std::cout << "Error: " << message << std::endl;
		result = 1;
	}

	if (result != 0)
		system("pause");

	return result;
}

#else

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int result = 0;
	try
	{
		SampleApplication().run();
	}
	catch (const std::string& message)
	{
		result = 1;
	}

	return result;
}
#endif
