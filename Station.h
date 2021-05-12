

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <iomanip>
#include <string>
#include "Utilities.h"

	class Station {

		int stationId = 0;
		std::string itemName = "";
		std::string stationDescription = "";
		int nextSerialNumber = 0;
		int numItems = 0;

		static size_t m_widthField;
		static int id_generator;

	public:
		Station() { m_widthField = 0; id_generator = 0; }
		Station(const std::string strStation);
		const std::string& getItemName() const { return itemName; }
		unsigned int getNextSerialNumber() { return nextSerialNumber++; }
		unsigned int getQuantity() const { return numItems; }
		void updateQuantity() { numItems -= 1; }
		void display(std::ostream& os, bool full) const;

	};
	


#endif