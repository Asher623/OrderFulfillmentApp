

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utilities.h"
#include "LineManager.h"
#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

LineManager::LineManager(std::string fileName, std::vector<Workstation*>& stations, std::vector<CustomerOrder>& orders) {

	Utilities utils;
	
	std::ifstream fileOpen(fileName);
	if (!fileOpen)
		throw string("Unable to open [") + fileName + "] file.";



	std::string strStation;

	while (!fileOpen.eof()) {
		std::getline(fileOpen, strStation);
		
		
		bool more = false;
		int a = 0;
		size_t commaArray[10] = { 0 };
		for (size_t i = 0; i < strStation.length(); i++) {
			if (strStation[i] != '\0') {

				if (strStation[i] == utils.getDelimiter()) {
					commaArray[a] = i;
					a++;
				}

			}
		}

		std::string currentStation = utils.extractToken(strStation, commaArray[0], more);
		std::string nextStation = utils.extractToken(strStation, commaArray[1], more);

		for (size_t i = 0; i < stations.size(); i++) {
			if (stations[i]->getItemName() == currentStation) {
				for (size_t j = 0; i < stations.size(); j++) {
					if (stations[j]->getItemName() == nextStation) {
						stations[i]->setNextStation(*stations[j]);
						break;
					}
				}
				if (firstStation == nullptr) {
					firstStation = stations[i];
				}
			}
		}
	}
	fileOpen.close();
	AssemblyLine = stations;
	for (size_t i = 0; i < orders.size(); i++) {
		ToBeFilled.push_back(std::move(orders[i]));
	}
	m_cntCustomerOrder = ToBeFilled.size();

	

}

bool LineManager::run(std::ostream& os) {
	static size_t count;
	std::cout << "Line Manager Iteration: " << ++count << std::endl;

	if (!ToBeFilled.empty()) {
		*firstStation += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->runProcess(os);
	}
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->moveOrder();

		CustomerOrder order;
		if (AssemblyLine[i]->getIfCompleted(order)) {
			Completed.push_back(std::move(order));
		}
	}

	bool check = false;

	if (Completed.size() == m_cntCustomerOrder) {
		check = true;
	}
	return check;
}

void LineManager::displayCompletedOrders(std::ostream& os) const {

	for (auto i = Completed.begin(); i != Completed.end(); i++) {
		(*i).display(os);
	}
};
void LineManager::displayStations() const {
	for (auto i = AssemblyLine.begin(); i != AssemblyLine.end(); i++) {
		(*i)->display(std::cout);
	}
};
void LineManager::displayStationsSorted() const {
	const Workstation* station = firstStation;
	while (station != nullptr) {
		station->display(std::cout);
		station = station->getNextStation();
	}

};