#pragma once

#include <iostream>
#include <string>

namespace application::util
{
	auto inline clear_console() -> void
	{
#if defined _WIN32
		system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
		system("clear");
#endif
	}

	auto inline pause_console(std::string message = "") -> void
	{
		if (message.length() <= 0)
		{
			message = "Press enter key to continue...";
		}

		std::cout << "\n" + message + "\n";

		// Grab next line character after pause message
		auto _ = getchar();

		// Wait for next input
		std::cin.get();
	}
}
