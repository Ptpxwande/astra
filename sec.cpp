#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


struct Contact {
    std::string phoneNumber;
    std::string name;
};

std::string findNameByPhoneNumber(const std::string& phoneNumber) {
    std::ifstream inFile("contacts.txt");
    std::string name;
    std::string line;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string token;
            std::getline(iss, token, ','); // Read phone number
            if (token == phoneNumber) {
                std::getline(iss, name); // Read name
                inFile.close();
                return name;
            }
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }

    return "unregistered";
}

int main() {
    bool continueTransaction = true;
    while (continueTransaction) {
        std::string phoneNumber;
        double amountToSend;
        int pin;
        double accountBalance = 40000.0; // Predefined account balance

        // Input phone number and amount to send
        std::cout << "Enter recipient's phone number: ";
        std::cin >> phoneNumber;

        std::cout << "Enter amount of money to send: ";
        std::cin >> amountToSend;
        std::cout << "\n";

        // Verify PIN
        std::cout << "Enter PIN: ";
        std::cin >> pin;
        std::cout << "\n";

        if (pin != 2156) {
            std::cout << "Incorrect PIN. Transaction aborted." << std::endl;
        } else if (amountToSend > accountBalance) {
            std::cout << "Insufficient funds. Transaction aborted." << std::endl;
        } else {
            // Lookup recipient's name
            std::string recipientName = findNameByPhoneNumber(phoneNumber);

            if (recipientName == "unregistered") {
                std::cout << "Recipient is unregistered." << std::endl;
            } else {
                // Confirm transaction
                std::cout << "Send Ksh " << amountToSend << " to " << recipientName << " (" << phoneNumber << ") ? (y/n): ";
                char confirm;
                std::cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    // Perform transaction
                    accountBalance -= amountToSend;
                    std::cout << "\n";
                    std::cout << "Transaction successful. Updated balance: Ksh " << accountBalance << std::endl;
                } else {
                    std::cout << "Transaction cancelled." << std::endl;
                }
            }
        }

        // Ask user if they want to continue
        char choice;
        std::cout << "\n";
        std::cout << "Do you want to perform another transaction? (y/n): ";
        std::cin >> choice;
        std::cout << "\n";
        
        if (choice != 'y' && choice != 'Y') {
            continueTransaction = false; // Exit the loop if user does not want to continue
        }
    }

    return 0;
}
