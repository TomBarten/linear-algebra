#define SDL_MAIN_HANDLED

#include <iostream>

#include "console_helpers.h"
#include "program.h"

using namespace application::util;

constexpr auto WIDTH = 640;
constexpr auto HEIGHT = WIDTH;

constexpr float FOV_DEGREES = 90.f;
constexpr float Z_NEAR = 0.1f;
constexpr float Z_FAR = 100.f;

static auto handle_exception(const std::exception_ptr& exception_ptr) -> void
{
    try
    {
        if (exception_ptr)
        {
            std::rethrow_exception(exception_ptr);
        }
    }
    catch (const std::exception& exception)
    {
	    clear_console();

        std::cerr << "Exception thrown:\n\"" << exception.what() << "\"\n";

	    pause_console();
    }
}

static auto run_program() -> void
{
    const auto program = std::make_unique<application::program>(WIDTH, HEIGHT, FOV_DEGREES, Z_NEAR, Z_FAR, false);

    try
    {
        program->run();
    }
    catch (...)
    {
        const auto& exception = std::current_exception();

        handle_exception(exception);
    }
}

auto main() -> int
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

    run_program();
	
    _CrtDumpMemoryLeaks();

    return 0;
}
