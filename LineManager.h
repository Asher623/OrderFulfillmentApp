

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <iostream>
#include <iomanip>
#include <string>
#include "Workstation.h"
#include "CustomerOrder.h"
#include <vector>
#include <deque>

class LineManager {
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;

	Workstation* firstStation = nullptr;

public:
	LineManager(std::string fileName, std::vector<Workstation*>& stations, std::vector<CustomerOrder>& orders);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};

#endif