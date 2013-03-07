//
//  TextFileReader.h
//  Bump
//
//  Created by Joseph Holub on 2/1/13.
//  Copyright (c) 2012 Joseph Holub. All rights reserved.
//

// Bump Headers
#include <bump/FileSystem.h>
#include <bump/Log.h>
#include <bump/TextFileReader.h>

// C++ Headers
#include <fstream>

namespace bump {
	
namespace TextFileReader {
	
StringList readFileLines(String fileName, const int& beginningLine, const int& numLines)
{
	// Create StringList to store info
	StringList file_contents;
	
	// Check to see if the file is valid before opening
	bool is_valid = FileSystem::isFile(fileName);
	if(!is_valid)
	{
		bumpERROR_P("FileSystem: ", "File to open is not a valid file");
		return file_contents;
	}
	bumpINFO_P("FileReader: Reading File ", fileName);
	
	// Open File
	std::ifstream input_file;
	input_file.open(fileName.toStdString().data(), std::ios::in);
	if (!input_file.is_open())
	{
		bumpERROR_P("FileReader: Error opening ", fileName);
		return file_contents;
	}
	
	std::string line;
	input_file.seekg(0, std::ios::beg);
	for (unsigned int i = 1; i < beginningLine; i++)
	{
		std::getline(input_file, line);
		if (input_file.eof())
		{
			bumpERROR_P("FileReader: ", "The line requested is larger than the number of lines in the file");
			return file_contents;
		}
	}
	
	if (numLines == -1)
	{
		while (!input_file.eof())
		{
			std::getline(input_file, line);
			file_contents.push_back(line);
		}
	}
	else
	{
		// Read the specified lines from the file
		for (unsigned int i = 0; i < numLines; i++)
		{
			if (input_file.eof())
			{
				bumpINFO_P("FileReader: ", "More lines were requested than were in the file");
				return file_contents;
			}
			std::getline(input_file, line);
			file_contents.push_back(line);
		}
	}
	
	input_file.close();
	return file_contents;
}

StringList fileContents(const String& fileName)
{
	return readFileLines(fileName, 0, -1); // -1 for the whole file
}
	
StringList fileContents(const String& fileName, const int& beginningLine, const int& numLines)
{
	if (beginningLine < 1)
	{
		bumpINFO_P("FileReader: ", "The beginningLine can not be less than 1");
		StringList empty_string;
		return empty_string;
	}
	
	return readFileLines(fileName, beginningLine, numLines);
}

StringList fileContents(const String& fileName, const int& beginningLine)
{
	if (beginningLine < 1)
	{
		bumpINFO_P("FileReader: ", "The beginningLine can not be less than 1");
		StringList empty_string;
		return empty_string;
	}
	
	int number_of_lines = -1; // -1 specifies the rest of the file
	return readFileLines(fileName, beginningLine, number_of_lines);
}

String firstLine(const String& fileName)
{
	StringList file_contents = readFileLines(fileName, 0, 1);
	
	String header;
	if(!file_contents.empty())
	{
		header = file_contents.front();
	}
	
	return header;
}

StringList header(const String& fileName, const int& numLines)
{
	if (numLines < 1)
	{
		bumpINFO_P("FileReader: ", "The numLines can not be less than 1 for a header");
		StringList empty_string;
		return empty_string;
	}
	
	return readFileLines(fileName, 0, numLines);
}
	
StringList footer(const String& fileName, const int& numLines)
{
	int file_num_lines = numberOfLines(fileName);
	if (file_num_lines == -1)
	{
		StringList empty_string;
		return empty_string;
	}
	int beginning_line = file_num_lines - numLines + 1;
	if(beginning_line < 0)
	{
		beginning_line = 0;
	}

	return readFileLines(fileName, beginning_line, numLines);
}

int numberOfLines(const String& fileName)
{
	// Check to see if the file is valid before opening
	bool is_valid = FileSystem::isFile(fileName);
	if(!is_valid)
	{
		bumpERROR_P("FileSystem: ", "File to open is not a valid file");
		return -1;
	}
	bumpINFO_P("FileReader: Reading File ", fileName);
	
	// Open File
	std::ifstream input_file;
	input_file.open(fileName.toStdString().data(), std::ios::in);
	if (!input_file.is_open())
	{
		bumpERROR_P("FileReader: Error opening ", fileName);
		return -1;
	}
	
	std::string line;
	input_file.seekg(0, std::ios::beg);
	unsigned int num_lines = 0;
	while (!input_file.eof())
	{
		std::getline(input_file, line);
		num_lines++;
	}
	
	input_file.close();
	
	return num_lines;
}


}	// End of TextFileReader namespace
	
} 	// End of bump namespace
