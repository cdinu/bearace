#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream file("data.csv");

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    // Read the header
    std::string line;
    getline(file, line);

    // Data structure to store clientID as key and average sum as value
    std::unordered_map<std::string, double> averageSum;

    // Skip the first line
    getline(file, line);

    // Read data, line by line
	while (getline(file, line)) {
	    std::stringstream linestream(line);
	    std::string cell;
	    std::vector<std::string> parsedRow;

	    // Parse the line into cells
	    while (getline(linestream, cell, ',')) {
		parsedRow.push_back(cell);
	    }

	    // Make sure there are enough columns in the row
	    if (parsedRow.size() > 3) {
		std::string puprn = parsedRow[0];
		try {
		    // Try to convert to double and catch any invalid_argument exception
		    double consumptionValue = std::stod(parsedRow[3]); // Assuming the 4th column is 'elec_active_import_profile_hh_wh'
		    consumption[puprn] += consumptionValue;
		} catch (const std::invalid_argument& ia) {
		    // Handle the case where the string could not be converted
		    // std::cerr << "Invalid argument: " << ia.what() << " for PUPRN " << puprn << " arg " << parsedRow[3] << std::endl;
		    // std::cerr << line << std::endl;
		    // break;
		    // You could also decide to continue with the next line or handle the error as needed
		}
	    } else {
		// Handle the case where the row does not have enough columns
		std::cerr << "Invalid row: " << line << std::endl;
	    }
	}

    file.close();

    // Convert the map into a vector of pairs for sorting
    std::vector<std::pair<std::string, double>> sortedConsumption(consumption.begin(), consumption.end());

    // Sort the vector by consumption in descending order
    std::sort(sortedConsumption.begin(), sortedConsumption.end(),
              [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
                  return a.second > b.second;
              });

    // Display the top 10 consumers
    for (int i = 0; i < 10 && i < sortedConsumption.size(); ++i) {
        std::cout << "PUPRN: " << sortedConsumption[i].first << ", Consumption: " << sortedConsumption[i].second << std::endl;
    }

    return 0;
}