#ifndef ITABLE_H
#define ITABLE_H


#include <iomanip>
#include <string>

class ITable {

public:

	virtual ~ITable() {}
	
	virtual void addHeader(const std::string& header) = 0;
	virtual void addRow(const std::string& header, const std::string& data) = 0;
	virtual void print() const = 0;
	


};


#endif // !ITABLE_H

/*
#include <iostream>
#include <iomanip>  // For std::setw, std::left, std::right

int main() {
    // Header of the table
    std::cout << std::setw(10) << std::left << "Name"
              << std::setw(10) << std::left << "Age"
              << std::setw(15) << std::left << "Occupation"
              << std::setw(10) << std::right << "Salary" << std::endl;

    // Separator line
    std::cout << std::setw(45) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ');  // Reset fill character to space

    // Rows of the table
    std::cout << std::setw(10) << std::left << "Alice"
              << std::setw(10) << std::left << "30"
              << std::setw(15) << std::left << "Engineer"
              << std::setw(10) << std::right << "$5000" << std::endl;

    std::cout << std::setw(10) << std::left << "Bob"
              << std::setw(10) << std::left << "25"
              << std::setw(15) << std::left << "Designer"
              << std::setw(10) << std::right << "$4000" << std::endl;

    std::cout << std::setw(10) << std::left << "Charlie"
              << std::setw(10) << std::left << "28"
              << std::setw(15) << std::left << "Manager"
              << std::setw(10) << std::right << "$6000" << std::endl;

    return 0;
}



*/