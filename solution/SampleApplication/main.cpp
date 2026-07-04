#include <iostream>

#include "application/SampleApplication.h"

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
