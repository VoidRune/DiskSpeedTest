#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

double read_file(const std::string& filename)
{
	double timeTaken = 0.0;

	std::ifstream file;
	file.open(filename.c_str());

	if (file.is_open())
	{
		std::string text;
		text.resize(1024);

		auto startTime = std::chrono::system_clock::now();
		while (file.read(text.data(), text.size()))
		{
			// We don't do anything with the data
		}
		auto endTime = std::chrono::system_clock::now();

		timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() * 0.001;
	}
	else
	{
		std::cout << "[ERROR] Could not open file: " << filename << std::endl;
	}

	file.close();
	return timeTaken;
}

double write_file(const std::string& filename, uint32_t sizeInKilobytes)
{
	double timeTaken = 0.0;

	std::ofstream file;
	file.open(filename.c_str());

	if (file.is_open())
	{
		std::string text;
		for (size_t i = 0; i < 1024; i++)
		{
			text += 'a';
		}

		auto startTime = std::chrono::system_clock::now();
		for (size_t i = 0; i < sizeInKilobytes; i++)
		{
			file << text;
		}
		file.flush();
		auto endTime = std::chrono::system_clock::now();

		timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() * 0.001;
	}
	else
	{
		std::cout << "[ERROR] Could not open file: " << filename << std::endl;
	}

	file.close();
	return timeTaken;
}

int main(int argc, char* argv[])
{
	// Megabyte 1024
	// Gigabyte 1024 * 1024 = 1048576
	if (argc >= 2 && argv[1][0] == 'w')
	{
		std::cout << "Time taken to write 1 Megabyte: " << write_file("OutputTest1Megabyte.txt", 1024) << " seconds" << std::endl;
		std::cout << "Time taken to write 10 Megabyte: " << write_file("OutputTest10Megabytes.txt", 1024 * 10) << " seconds" << std::endl;
		std::cout << "Time taken to write 100 Megabyte: " << write_file("OutputTest100Megabytes.txt", 1024 * 100) << " seconds" << std::endl;
		std::cout << "Time taken to write 1 Gigabyte: " << write_file("OutputTest1Gigabyte.txt", 1024 * 1024) << " seconds" << std::endl;
	}
	else if (argc >= 2 && argv[1][0] == 'r')
	{
		std::cout << "Time taken to read 1 Megabyte: " << read_file("OutputTest1Megabyte.txt") << " seconds" << std::endl;
		std::cout << "Time taken to read 10 Megabytes: " << read_file("OutputTest10Megabytes.txt") << " seconds" << std::endl;
		std::cout << "Time taken to read 100 Megabytes: " << read_file("OutputTest100Megabytes.txt") << " seconds" << std::endl;
		std::cout << "Time taken to read 1 Gigabyte: " << read_file("OutputTest1Gigabyte.txt") << " seconds" << std::endl;
	}
	else
	{
		std::cout << "Execution arguments are incorrect, options are 'r' for read or 'w' for write";
	}
	std::cin;
	return 0;
}