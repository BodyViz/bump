/**
 *  FileReader.cpp
 *  SOMViz
 *
 *  Created by Joseph Holub on 2/1/13.
 *  Copyright 2013 Iowa State University. All rights reserved.
 */

// Local headers
#include <bump/TextFileReader.h>
#include <bump/FileSystem.h>
#include <bump/Log.h>
#include <fstream>

namespace bump {
	
namespace TextFileReader{
	
boost::shared_ptr<StringList> readFileLines(String fileName, int beginningLine, int numLines){
	
	// Create StringList to store info
	boost::shared_ptr<StringList> fileContents(new StringList);
	
	// Check to see if the file is valid before opening
	bool isValid = FileSystem::isFile(fileName);
	if(!isValid){
		bumpALWAYS_P("FileSystem: ", "File to open is not a valid file");
		return fileContents;
	}
	bumpINFO_P("FileReader: Reading File ", fileName);
	
	// Open File
	std::ifstream inputFile;
	inputFile.open(fileName.toStdString().data(), std::ios::in);
	if (!inputFile.is_open()) {
		bumpALWAYS_P("FileReader: Error opening ", fileName);
		return fileContents;
	}
	
	std::string line;
	inputFile.seekg(0, std::ios::beg);
	for (unsigned int i = 1; i < beginningLine; i++) {
		std::getline(inputFile, line);
		if (inputFile.eof()) {
			bumpALWAYS_P("FileReader: ", "The line requested is larger than the number of lines in the file");
			return fileContents;
		}
	}
	
	if (numLines == -1) {
		while (!inputFile.eof()) {
			std::getline(inputFile, line);
			fileContents->push_back(line);
		}
	}else{
		// Read the specified lines from the file
		for (unsigned int i = 0; i < numLines; i++) {
			if (inputFile.eof()) {
				bumpINFO_P("FileReader: ", "More lines were requested than were in the file");
				return fileContents;
			}
			std::getline(inputFile, line);
			fileContents->push_back(line);
		}
	}
	
	
	inputFile.close();
	
	return fileContents;
	
}

boost::shared_ptr<StringList> returnFileContents(String fileName){
	
	boost::shared_ptr<StringList> fileContents(new StringList);
	fileContents = readFileLines(fileName, 0, -1); // -1 for the whole file
	
	return fileContents;
}

String returnFirstLine(String fileName){
	
	boost::shared_ptr<StringList> fileContents(new StringList);
	fileContents = readFileLines(fileName, 0, 1);
	
	if(fileContents->empty()){
		bump::String emptyString;
		return emptyString;
	}
	
	return fileContents->front();
}

boost::shared_ptr<StringList> returnFirstNLines(String fileName, int numLines){
	
	boost::shared_ptr<StringList> fileContents(new StringList);
	fileContents = readFileLines(fileName, 0, numLines);
	
	return fileContents;
}

boost::shared_ptr<StringList> returnNLinesStartingAtM(String fileName, int beginningLine, int numLines){
	
	boost::shared_ptr<StringList> fileContents(new StringList);
	fileContents = readFileLines(fileName, beginningLine, numLines);
	
	return fileContents;
}

boost::shared_ptr<StringList> returnLineNThroughEnd(String fileName, int beginningLine){
	
	int numberOfLines = -1; // -1 for the whole file
	
	boost::shared_ptr<StringList> fileContents(new StringList);
	fileContents = readFileLines(fileName, beginningLine, numberOfLines);
	
	return fileContents;
}

int numberOfLines(String fileName){
	
	// Check to see if the file is valid before opening
	bool isValid = FileSystem::isFile(fileName);
	if(!isValid){
		bumpALWAYS_P("FileSystem: ", "File to open is not a valid file");
		return -1;
	}
	bumpINFO_P("FileReader: Reading File ", fileName);
	
	// Open File
	std::ifstream inputFile;
	inputFile.open(fileName.toStdString().data(), std::ios::in);
	if (!inputFile.is_open()) {
		bumpALWAYS_P("FileReader: Error opening ", fileName);
		return -1;
	}
	
	std::string line;
	inputFile.seekg(0, std::ios::beg);
	unsigned int numLines = 0;
	while (!inputFile.eof()) {
		std::getline(inputFile, line);
		numLines++;
	}
	
	inputFile.close();
	
	return numLines;
}


}	// End of TextFileReader namespace
	
} 	// End of bump namespace
