

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "CustomerOrder.h"
#include <algorithm>
#include <sstream>
using namespace std;

size_t CustomerOrder::m_widthField;

CustomerOrder::CustomerOrder(const std::string& strFile) {
	Utilities utils;
	bool more = false;
	size_t commaArray[11] = { 0 };
	int delimeterCount = 0;
	for (size_t i = 0; i < strFile.length(); i++) {
		if (strFile[i] != '\0') {

			if (strFile[i] == utils.getDelimiter()) {
				commaArray[delimeterCount] = i;
				delimeterCount++;
			}

		}
	}

	if (strFile.empty()) {
		m_lstItem = nullptr;
		m_name = "";
		m_cntItem = 0;
		m_product = "";
	}
	else {

		m_name = utils.extractToken(strFile, commaArray[0], more);

		if (more) {
			m_product = utils.extractToken(strFile, commaArray[1], more);
		}
		m_cntItem = delimeterCount - 1;
		m_lstItem = new Item * [m_cntItem];
		int currentDelim = 2;
		for (size_t i = 0u; i < m_cntItem && more; i++) {
			if (commaArray[currentDelim] == 0) {
				size_t cmSize = strFile.size();
				m_lstItem[i] = new Item(utils.extractToken(strFile, cmSize, more));
			}
			else {
				m_lstItem[i] = new Item(utils.extractToken(strFile, commaArray[currentDelim], more));
			}
			
			currentDelim++;
		}
		if (utils.getFieldWidth() > m_widthField)
			m_widthField = utils.getFieldWidth();
	}
	
}

void CustomerOrder::fillItem(Station& station, std::ostream& os) {
	for (size_t i = 0; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == station.getItemName()) {
			if (station.getQuantity() >= 1) {
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;
				station.updateQuantity();
				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
			else {
				os << "    Unable to fill  " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}

}