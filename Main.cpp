#include "Arguments.h"
#include "Message.h"
#include "BMP.h"
#include "Encoder.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{

	{
		Message::displayTestBits();

		return 0;
		if (argc < 2)
		{
			std::cerr << "Missing command\n";
			return 1;
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
