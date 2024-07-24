#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <time.h>
#include <chrono>

class Logger
{

    std::ostream& output;
    char* source;

public:

    
    enum Level
    {
        Log, Warning, Error
    };

private:

    const char* ParseLevel(Level lvl) const
    {
        switch (lvl)
        {
            case Log:
                return "Log";
                break;
            case Warning:
                return "Warning";
                break;
            case Error:
                return "Error";
                break;
            
            default:
                return "Log";
                break;
        }
    }

    const char* getCurrentLocalTime() 
    {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        struct tm* localTime = std::localtime(&currentTime);

        static char formattedTime[20];
        strftime(formattedTime, sizeof(formattedTime), "%Y.%m.%d-%H:%M", localTime);

        return formattedTime;
    }

public:

    Logger(std::ostream& os = std::cout, char* src = ""):output(os), source(src){}


    void ConsoleLog(char* msg, Level lvl = Log)
    {
        const char* t = getCurrentLocalTime();
        output<<"["<< ParseLevel(lvl) <<"]"<< "["<<t <<"] "<<source<<" - "<<msg<<std::endl;
    }

};


#endif