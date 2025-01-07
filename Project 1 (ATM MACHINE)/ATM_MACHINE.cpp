#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#include <limits>
#include <map>

using namespace std;

// Structure to hold account information
struct Account {
    string cardNumber;
    string pin;
    double balance;
    string bankName;
    string holderName;
    vector<string> transactionHistory;
    int failedAttempts;
    bool isLocked;
    chrono::system_clock::time_point lockTime;
};

class ATM {
private:
    map<char, Account> accounts;
    const int MAX_FAILED_ATTEMPTS = 3;
    const int LOCK_DURATION_MINUTES = 60;

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void addTransaction(Account& account, const string& transaction) {
        time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        string timestamp = ctime(&now);
        timestamp = timestamp.substr(0, timestamp.length()-1);  // Remove newline
        account.transactionHistory.push_back(timestamp + " - " + transaction);
    }

    bool isAccountLocked(Account& account) {
        if (account.isLocked) {
            auto now = chrono::system_clock::now();
            auto duration = chrono::duration_cast<chrono::minutes>(now - account.lockTime).count();
            
            if (duration >= LOCK_DURATION_MINUTES) {
                account.isLocked = false;
                account.failedAttempts = 0;
                return false;
            }
            return true;
        }
        return false;
    }

    void lockAccount(Account& account) {
        account.isLocked = true;
        account.lockTime = chrono::system_clock::now();
        cout << "\n⚠️ Your account has been locked for " << LOCK_DURATION_MINUTES << " minutes due to multiple failed attempts." << endl;
    }

    bool validatePin(Account& account, const string& enteredPin) {
        if (isAccountLocked(account)) {
            cout << "\n🔒 Account is locked. Please try again later." << endl;
            return false;
        }

        if (enteredPin == account.pin) {
            account.failedAttempts = 0;
            return true;
        }

        account.failedAttempts++;
        if (account.failedAttempts >= MAX_FAILED_ATTEMPTS) {
            lockAccount(account);
        }
        return false;
    }

public:
    ATM() {
        // Initialize sample accounts
        accounts['k'] = {"1234-5678-9012-3456", "1234", 50000, "SBI", "Nayaj", {}, 0, false};
        accounts['s'] = {"2345-6789-0123-4567", "5678", 100000, "HDFC", "Nayaj", {}, 0, false};
        accounts['l'] = {"3456-7890-1234-5678", "9123", 600000, "ICICI", "Nayaj", {}, 0, false};
        accounts['i'] = {"4567-8901-2345-6789", "4567", 900000, "AXIS", "Nayaj", {}, 0, false};
        accounts['n'] = {"5678-9012-3456-7890", "8912", 30000, "PNB", "Nayaj", {}, 0, false};
    }

    void displayWelcomeScreen() {
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║      WELCOME TO MODERN ATM         ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
        cout << "\nPlease insert your card (k,s,l,i,n): ";
    }

    void displayMenu() {
        cout << "\n╔════════════════════════════════════╗" << endl;
        cout << "║             MAIN MENU              ║" << endl;
        cout << "╠════════════════════════════════════╣" << endl;
        cout << "║ 1. Withdraw Money                  ║" << endl;
        cout << "║ 2. Check Balance                   ║" << endl;
        cout << "║ 3. View Transaction History        ║" << endl;
        cout << "║ 4. Fast Cash                       ║" << endl;
        cout << "║ 5. Change PIN                      ║" << endl;
        cout << "║ 6. Exit                           ║" << endl;
        cout << "╚════════════════════════════════════╝" << endl;
    }

    void processTransaction(char cardChoice) {
        if (accounts.find(cardChoice) == accounts.end()) {
            cout << "\n❌ Invalid card!" << endl;
            return;
        }

        Account& currentAccount = accounts[cardChoice];
        clearScreen();
        
        cout << "\n👋 Hello " << currentAccount.holderName << "!" << endl;
        cout << "💳 You are using " << currentAccount.bankName << " DEBIT CARD" << endl;
        cout << "Card Number: XXXX-XXXX-XXXX-" << currentAccount.cardNumber.substr(15) << endl;

        while (true) {
            displayMenu();
            int choice;
            cout << "\nEnter your choice (1-6): ";
            cin >> choice;
            clearScreen();

            string pin;
            double amount;

            switch (choice) {
                case 1: // Withdraw
                    cout << "\n💰 WITHDRAW MONEY" << endl;
                    cout << "Enter PIN: ";
                    cin >> pin;
                    
                    if (validatePin(currentAccount, pin)) {
                        cout << "Enter amount to withdraw: $";
                        cin >> amount;
                        
                        if (amount > currentAccount.balance) {
                            cout << "\n❌ Insufficient funds!" << endl;
                            addTransaction(currentAccount, "Failed withdrawal attempt: $" + to_string(amount));
                        } else if (amount <= 0) {
                            cout << "\n❌ Invalid amount!" << endl;
                        } else {
                            currentAccount.balance -= amount;
                            cout << "\n✅ Please collect your money: $" << amount << endl;
                            cout << "Remaining balance: $" << currentAccount.balance << endl;
                            addTransaction(currentAccount, "Withdrawn: $" + to_string(amount));
                        }
                    } else {
                        cout << "\n❌ Incorrect PIN!" << endl;
                    }
                    break;

                case 2: // Check Balance
                    cout << "\n💵 CHECK BALANCE" << endl;
                    cout << "Enter PIN: ";
                    cin >> pin;
                    
                    if (validatePin(currentAccount, pin)) {
                        cout << "\nCurrent Balance: $" << fixed << setprecision(2) << currentAccount.balance << endl;
                        addTransaction(currentAccount, "Balance checked");
                    } else {
                        cout << "\n❌ Incorrect PIN!" << endl;
                    }
                    break;

                case 3: // Transaction History
                    cout << "\n📝 TRANSACTION HISTORY" << endl;
                    cout << "Enter PIN: ";
                    cin >> pin;
                    
                    if (validatePin(currentAccount, pin)) {
                        if (currentAccount.transactionHistory.empty()) {
                            cout << "\nNo transactions found." << endl;
                        } else {
                            cout << "\nRecent Transactions:" << endl;
                            cout << "══════════════════════════════════════" << endl;
                            for (const auto& transaction : currentAccount.transactionHistory) {
                                cout << transaction << endl;
                            }
                        }
                    } else {
                        cout << "\n❌ Incorrect PIN!" << endl;
                    }
                    break;

                case 4: // Fast Cash
                    cout << "\n⚡ FAST CASH" << endl;
                    cout << "Enter PIN: ";
                    cin >> pin;
                    
                    if (validatePin(currentAccount, pin)) {
                        vector<int> fastCashOptions = {20, 40, 60, 80, 100, 200};
                        cout << "\nSelect amount:" << endl;
                        for (size_t i = 0; i < fastCashOptions.size(); i++) {
                            cout << i + 1 << ". $" << fastCashOptions[i] << endl;
                        }
                        
                        int fastChoice;
                        cout << "\nEnter choice (1-6): ";
                        cin >> fastChoice;
                        
                        if (fastChoice >= 1 && fastChoice <= 6) {
                            amount = fastCashOptions[fastChoice - 1];
                            if (amount > currentAccount.balance) {
                                cout << "\n❌ Insufficient funds!" << endl;
                                addTransaction(currentAccount, "Failed fast cash attempt: $" + to_string(amount));
                            } else {
                                currentAccount.balance -= amount;
                                cout << "\n✅ Please collect your money: $" << amount << endl;
                                cout << "Remaining balance: $" << currentAccount.balance << endl;
                                addTransaction(currentAccount, "Fast cash withdrawn: $" + to_string(amount));
                            }
                        } else {
                            cout << "\n❌ Invalid choice!" << endl;
                        }
                    } else {
                        cout << "\n❌ Incorrect PIN!" << endl;
                    }
                    break;

                case 5: // Change PIN
                    cout << "\n🔐 CHANGE PIN" << endl;
                    cout << "Enter current PIN: ";
                    cin >> pin;
                    
                    if (validatePin(currentAccount, pin)) {
                        string newPin, confirmPin;
                        cout << "Enter new PIN: ";
                        cin >> newPin;
                        cout << "Confirm new PIN: ";
                        cin >> confirmPin;
                        
                        if (newPin == confirmPin && newPin.length() == 4) {
                            currentAccount.pin = newPin;
                            cout << "\n✅ PIN successfully changed!" << endl;
                            addTransaction(currentAccount, "PIN changed");
                        } else {
                            cout << "\n❌ PIN change failed! PINs don't match or invalid length." << endl;
                        }
                    } else {
                        cout << "\n❌ Incorrect PIN!" << endl;
                    }
                    break;

                case 6: // Exit
                    cout << "\n👋 Thank you for using our ATM. Goodbye!" << endl;
                    return;

                default:
                    cout << "\n❌ Invalid choice! Please try again." << endl;
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            clearScreen();
        }
    }
};

int main() {
    ATM atm;
    char cardChoice;

    while (true) {
        atm.displayWelcomeScreen();
        cin >> cardChoice;
        atm.processTransaction(cardChoice);

        cout << "\nWould you like to perform another transaction? (y/n): ";
        char continueChoice;
        cin >> continueChoice;
        if (tolower(continueChoice) != 'y') {
            cout << "\nThank you for using our ATM. Have a great day!" << endl;
            break;
        }
    }

    return 0;
}