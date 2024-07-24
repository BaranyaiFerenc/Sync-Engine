#include "string.hpp"
#include "list.hpp"
#include "dictionary.hpp"
#include "matrix.hpp"
#include "logger.hpp"

#include <iostream>
#include <fstream>

bool bigger(int a, int b)
{
    return a < b;
}

void run()
{
    std::ofstream file("output.txt", std::ios_base::app);
    Logger logger = Logger(file, "main.cpp");


    logger.ConsoleLog("Hello World!", Logger::Error);
    file.close();
}

int main()
{
    run();

    return 0;
}

