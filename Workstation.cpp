

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Workstation.h"
#include <algorithm>
#include <sstream>
using namespace std;

void Workstation::runProcess(std::ostream& os) {

	if (!m_orders.empty()) {
		m_orders.front().fillItem(*this, os);
	}
};

bool Workstation::moveOrder() {

	bool check = false;
	if (!m_orders.empty()) {
		if (m_orders.front().isItemFilled(this->getItemName()) && m_pNextStation) {
			*m_pNextStation += std::move(m_orders.front());
			m_orders.pop_front();
			check = true;
		}
	}
	return check;
}

bool Workstation::getIfCompleted(CustomerOrder& order) {
	bool check = false;
	if (!m_orders.empty()) {
		if (m_orders.back().isOrderFilled()) {
			order = std::move(m_orders.front());
			m_orders.pop_front();
			check = true;
		}
	}
	return check;
}
void Workstation::display(std::ostream& os) const{
	if (getNextStation() != nullptr) {
		os << getItemName() << " --> " << getNextStation()->getItemName() << std::endl;
	}
	else {
		os << getItemName() << " --> END OF LINE" << std::endl;
	}
	
}