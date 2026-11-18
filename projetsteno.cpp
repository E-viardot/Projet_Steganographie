#include"message.h"
#include"image.h"
#include <iostream>
#include <string>
#include <vector>
#include<filesystem>

int main(int argc, char* argv[])
{
    {  
        std::cout
            << "Working Directory :  "
            << std::filesystem::current_path()
            << '\n';
    }
 
    {
        Message::displayTestBits();

        return 0;


        if (argc < 2)
        {
            std::cerr << "Missing command\n";
            return 0;
        }

        std::string command = argv[1];

        if (command == "encode")
        {
            if (argc != 5)
            {
                std::cerr << "Invalid encode arguments\n";
                return 1;
            }

        }
        else if (command == "decode")
        {
            if (argc != 3)
            {
                std::cerr << "Invalid decode arguments\n";
                return 1;
            }
        }
        else
        {
            std::cerr << "unknown command\n";
            return 1;
        }
    }
}