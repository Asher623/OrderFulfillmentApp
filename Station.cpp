

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Station.h"
#include <algorithm>
#include <sstream>
using namespace std;

size_t Station::m_widthField = 0;
int Station::id_generator = 0;

Station::Station(const std::string strStation) {

	Utilities utils;
	bool more = false;
	size_t commaArray[10] = { 0 };
	int a = 0;
	for (size_t i = 0; i < strStation.length(); i++) {
		if (strStation[i] != '\0') {

			if (strStation[i] == utils.getDelimiter()) {
				commaArray[a] = i;
				a++;
			}

		}
	}
	id_generator++;
	stationId = id_generator;
	size_t lastOne = strStation.length();
	itemName = utils.extractToken(strStation, commaArray[0], more);
	nextSerialNumber = std::stoi(utils.extractToken(strStation, commaArray[1], more));
	if (utils.getFieldWidth() > m_widthField) {
		m_widthField = utils.getFieldWidth();
	}
	
	numItems = std::stoi(utils.extractToken(strStation, commaArray[2], more));
	stationDescription = utils.extractToken(strStation, lastOne, more);

	


}
void Station::display(std::ostream& os, bool full) const {
	
	if (full == false) {
		os << "[" << std::setw(3) << std::setfill('0') << std::right  << stationId << "] Item: "  <<std::setw(m_widthField) << std::left  << std::setfill(' ') <<  itemName << " [" <<std::setw(6) << std::setfill('0') << std::right<< nextSerialNumber << "]";
	}
	else {
		os << "[" << std::setw(3) << std::setfill('0') << std::right << stationId << "] Item: " << std::setw(m_widthField) << std::left << std::setfill(' ') << itemName << " [" << std::setw(6) << std::setfill('0') << std::right << nextSerialNumber << "]" << " Quantity: " << std::setw(m_widthField) << std::left << std::setfill(' ') << numItems << " Description: " << stationDescription;
	}
	os << std::endl;
}
