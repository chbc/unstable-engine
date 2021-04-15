#include <application/SampleApplication.h>

#ifdef __ANDROID__
#include <SDL_log.h>

extern "C" __attribute__((visibility("default"))) int SDL_main(int argc, char** argv);

int SDL_main(int argc, char** argv)
{
	int result = 0;

	/* Enable standard application logging */
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

	try
	{
		SampleApplication().run();
	}
	catch (const char* message)
	{
		SDL_Log("XXX Error: %s", message);
		result = 1;
	}
	catch (std::exception& ex)
	{
		SDL_Log("XXX Error: %s", ex.what());
		result = 2;
	}
	catch (std::basic_string<char, std::char_traits<char>, std::allocator<char> >& message)
	{
		SDL_Log("XXX AQUELE Erro:");
		result = 3;
	}
	catch (std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, std::__ndk1::allocator<char> >& message)
	{
		SDL_Log("XXX AQUELE Erro 2");
	}

	SDL_Log("XXX result = %d", result);

	return result;
}

#else

#include <iostream>

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
	
	if (result != 0)
		system("pause");

	return result;
}
#endif
