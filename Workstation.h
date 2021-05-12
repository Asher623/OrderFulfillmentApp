

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "CustomerOrder.h"
#include <deque>

class Workstation: public Station {
	std::deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation;
public:
	Workstation(std::string& strRecord) : Station(strRecord) {
		m_pNextStation = nullptr;
	};
	Workstation(Workstation&) = delete;
	Workstation& operator=(Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator=(Workstation&&) = delete;

	void runProcess(std::ostream& os);
	bool moveOrder();
	void setNextStation(Workstation& station) {
		m_pNextStation = &station;
	};
	const Workstation* getNextStation() const {
		return m_pNextStation;
	};
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream& os) const;

	Workstation& operator+=(CustomerOrder&& order) {
		m_orders.push_back(std::move(order));
		return *this;
	};

};

#endif