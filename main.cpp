#include "build_config.h"
#include <iostream>
#include "hlCore/hlLogger.h"

Logger lo;

int main(int argc, const char* argv[])
{

    lo.Log(Logger::LogLevel::Error, "Run");

    return 0;
}