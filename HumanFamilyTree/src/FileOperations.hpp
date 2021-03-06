/*
 * FileOperations.hpp
 *
 *  Created on: Jul 27, 2016
 *      Author: gopalmenon
 */
#ifndef FILEOPERATIONS_HPP_
#define FILEOPERATIONS_HPP_

#include "MitochondrialDnaSample.hpp"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <vector>

static std::string MTDNA_FILE_LISTING_TEXT_FILE = "../fileListing.txt";
static std::string DATA_FILES_DIRECTORY = "../Data/";

// trim string from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim string from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim string from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

std::string stripExtension(std::string fileName) {

	return fileName.substr(0, fileName.find(".txt"));

}

//Given a file name return the contents as a string
std::string getFileContents(std::string fileName) {

	std::string fileLine, fileContents;
	std::ifstream textFile(DATA_FILES_DIRECTORY + fileName);
	if (textFile.is_open()) {
		while (getline(textFile, fileLine)) {
			fileContents.append(trim(fileLine));
		}
	}
	textFile.close();
	return fileContents;
}

//Return a list of files contained in a text file that has the directory listing. Each line is expected to have one file name.
std::vector<std::string> getDirectoryListing(std::string directoryListingFileName) {

	std::string fileLine, fileContents;
	std::vector<std::string> mtDnaFiles;
	std::ifstream textFile(directoryListingFileName);
	if (textFile.is_open()) {
		while (getline(textFile, fileLine)) {
			mtDnaFiles.push_back(trim(fileLine));
		}
	}
	textFile.close();
	return mtDnaFiles;

}

//Return a container with the list of file contents
std::vector<MitochondrialDnaSample> getAllFileContents() {

	int counter = 0;
	std::vector<MitochondrialDnaSample> dnaSamples;
	for (std::string& fileName : getDirectoryListing(MTDNA_FILE_LISTING_TEXT_FILE)) {
		if (trim(fileName).length() > 0) {
			dnaSamples.push_back(MitochondrialDnaSample(getFileContents(fileName), stripExtension(fileName), counter++));
		}

	}

	return dnaSamples;
}

#endif /* FILEOPERATIONS_HPP_ */
