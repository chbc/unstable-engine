#include <iostream>
#include <application/SampleApplication.h>

int main(int argc, char *argv[])
{
	int result = 0;
	try
	{
		SampleApplication().run();
	}
	catch (const char *message)
	{
		std::cout << "Error: " << message << std::endl;
		result = 1;
	}
	catch (std::exception &ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
		result = 2;
	}
	catch (std::basic_string<char, std::char_traits<char>, std::allocator<char> > &message)
	{
		std::cout << "Error: " << message << std::endl;
		result = 1;
	}
	
	system("pause");
	return result;
}
