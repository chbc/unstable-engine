#include <iostream>
#include <application/SampleApplication.h>

int main(int argc, char *argv[])
{
	try
	{
		SampleApplication().run();
		return 0;
	}
	catch (const std::string &message)
	{
		std::cout << "Error: " << message << std::endl;
		return 1;
	}
	catch (std::exception &ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
		return 1;
	}
}
