

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"

struct Item
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;

	Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	Item** m_lstItem;
	static size_t m_widthField;
public:
	CustomerOrder() { m_name = ""; m_product = ""; m_cntItem = 0; m_lstItem = nullptr; };
	CustomerOrder(const std::string& strFile);
	CustomerOrder(CustomerOrder&) { throw "ERROR: Copy is not allowed!"; }
	CustomerOrder(CustomerOrder&& order) noexcept {
		m_lstItem = nullptr;
		m_cntItem = 0;
		*this = std::move(order);
	}
	CustomerOrder& operator=(CustomerOrder&& order) noexcept {
		if (this != &order) {
			for (size_t i = 0u; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_name = order.m_name;
			m_product = order.m_product;
			m_cntItem = order.m_cntItem;
			m_lstItem = order.m_lstItem;

			order.m_lstItem = nullptr;
			order.m_cntItem = 0;
		}
		return *this;
	}
	~CustomerOrder() {
		for (size_t i = 0u; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool isOrderFilled() const {
		bool fill = true;

		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				fill = false;
			}
		}
		return fill;
	}
	bool isItemFilled(const std::string& itemName) const {
		
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				return m_lstItem[i]->m_isFilled;
			}
		}
		return true;
	}
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] " << std::setw(m_widthField - 1) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) {
				 os << "FILLED" << std::endl;
			}
			else {
				os << "MISSING" << std::endl;
			}
		}
	}
};

#endif