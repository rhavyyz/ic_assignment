#pragma once

#include <iostream>
#include <fstream> 
#include <vector>


#if !defined(_WIN32) && !defined(_WIN64)

#include <unistd.h>

const char separator = '/';

#else

#include "processthreadsapi.h"

const char separator = '\\';

int getpid()
{
    return (int)GetCurrentProcessId(); 
}

#endif

#include <filesystem>


class Logger
{
    private:
        Logger();
        Logger(Logger& l);
        ~Logger();

    public:

        static void save(std::string name, std::string content, bool concat = false)
        {
            std::string folder_name = std::to_string((int)getpid());

            // std::cout << std::filesystem::current_path() << std::endl;

            if(true)
                std::filesystem::create_directory(folder_name);
            
            std::string file_path = folder_name + separator + name;

            std::ofstream file;

            if(concat)
                file.open(file_path, std::ios_base::app); // append instead of overwrite
            else
                file.open(file_path); // append instead of overwrite

            file << content;

            file.close();
        }


        static void save(std::vector<std::string> name, std::string content, bool concat = false)
        {
            if(name.size() == 0)
                throw "U just cant save without name";

            std::string folder_name = std::to_string((int)getpid());

            // std::cout << std::filesystem::current_path() << std::endl;

            std::filesystem::create_directory(folder_name);

            std::string file_path = "";
            for(int i = 0; i < name.size() -1; i++)
            {
                if(i)
                    file_path += separator;
                file_path += name[i];

                std::filesystem::create_directory(folder_name + separator + file_path);
            }

            if (name.size() > 1)
                file_path += separator;

            file_path += name.back();            

            save(file_path, content, concat);
        }

};