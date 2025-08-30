#include <bits/stdc++.h>
using namespace std;

// ========== Safe Input Helpers ==========
bool safeReadInt(const string& prompt, int& out) {
    while (true) {
        cout << prompt;
        if (cin >> out) return true;
        if (cin.eof()) return false;              // allow Ctrl+D/Ctrl+Z to exit cleanly
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number. Please try again.\n";
    }
}

bool safeReadDouble(const string& prompt, double& out) {
    while (true) {
        cout << prompt;
        if (cin >> out) return true;
        if (cin.eof()) return false;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount. Please enter a valid number.\n";
    }
}

bool safeReadToken(const string& prompt, string& out) {
    while (true) {
        cout << prompt;
        if (cin >> out) return true;
        if (cin.eof()) return false;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again.\n";
    }
}

bool validateDate(const string& date) {
    int y, m, d;
    if (sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d) != 3) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > 31) return false; // simple day check (not month-length aware)
    return true;
}

// --------------------- Transaction Class ---------------------
class Transaction {
private:
    double amount;
    string category;
    string type; // "Income" or "Expense"
    string date; // YYYY-MM-DD
public:
    Transaction(double amt, string cat, string t, string d)
        : amount(amt), category(cat), type(t), date(d) {}
    
    double getAmount() const { return amount; }
    string getCategory() const { return category; }
    string getType() const { return type; }
    string getDate() const { return date; }

    void display() const {
        cout << date << " | " << type << " | " << category << " | " << amount << endl;
    }
};

// --------------------- User Class ---------------------
class User {
private:
    string name;
    double balance;
    vector<Transaction> transactions;

public:
    User(string n) : name(std::move(n)), balance(0.0) {}

    string getName() const { return name; }
    double getBalance() const { return balance; }

    void addTransaction(const Transaction& t) {
        transactions.push_back(t);
        if (t.getType() == "Income") balance += t.getAmount();
        else if (t.getType() == "Expense") balance -= t.getAmount();
        // any other type is ignored for balance update
    }

    const vector<Transaction>& getTransactions() const { return transactions; }

    double getMonthlyExpense(int year, int month) const {
        double total = 0.0;
        for (const auto &t : transactions) {
            if (t.getType() == "Expense") {
                int y, m, d;
                sscanf(t.getDate().c_str(), "%d-%d-%d", &y, &m, &d);
                if (y == year && m == month) total += t.getAmount();
            }
        }
        return total;
    }

    map<string, double> getCategoryWiseExpense(int year, int month) const {
        map<string, double> categoryMap;
        for (const auto &t : transactions) {
            if (t.getType() == "Expense") {
                int y, m, d;
                sscanf(t.getDate().c_str(), "%d-%d-%d", &y, &m, &d);
                if (y == year && m == month)
                    categoryMap[t.getCategory()] += t.getAmount();
            }
        }
        return categoryMap;
    }

    void displayTransactions(int year, int month) const {
        cout << "Transactions for " << name << " in " << year << "-" << month << ":\n";
        for (const auto &t : transactions) {
            int y, m, d;
            sscanf(t.getDate().c_str(), "%d-%d-%d", &y, &m, &d);
            if (y == year && m == month) t.display();
        }
        cout << "Balance: " << balance << endl;
    }
};

// --------------------- Analytics Class ---------------------
class Analytics {
public:
    void detectAnomalies(const User &u, int year, int month) {
        auto categoryMap = u.getCategoryWiseExpense(year, month);
        cout << "\n-- Anomaly Detection --\n";
        for (auto &p : categoryMap) {
            double spent = p.second;
            if (spent > 1000) {
                cout << "High spending detected in " << p.first << ": " << spent << endl;
            }
        }
    }

    void suggestBudget(const User &u, int year, int month) {
        auto categoryMap = u.getCategoryWiseExpense(year, month);
        double totalExpense = 0.0;
        for (auto &p : categoryMap) totalExpense += p.second;

        cout << "\n-- Budget Suggestion --\n";
        double availableBalance = u.getBalance();

        if (totalExpense <= 0.0 || availableBalance <= 0.0) {
            cout << "Not enough data (or balance) to suggest a budget.\n";
            return;
        }

        for (auto &p : categoryMap) {
            double suggested = (p.second / totalExpense) * availableBalance;
            cout << setw(15) << p.first << ": Suggested Budget = " << suggested << endl;
        }
    }

    void generateReport(const User &u, int year, int month) {
        cout << "\n-- Monthly Report --\n";
        u.displayTransactions(year, month);
        auto categoryMap = u.getCategoryWiseExpense(year, month);

        if (categoryMap.empty()) {
            cout << "\nNo expenses recorded for this month.\n";
            return;
        }

        cout << "\nCategory-wise Expenses (ASCII Chart):\n";
        double maxVal = 0;
        for (auto &p : categoryMap) maxVal = max(maxVal, p.second);
        if (maxVal <= 0) {
            cout << "All category spends are zero.\n";
            return;
        }

        for (auto &p : categoryMap) {
            int barLength = static_cast<int>((p.second / maxVal) * 50.0);
            cout << setw(15) << p.first << " | ";
            for (int i = 0; i < barLength; i++) cout << "#";
            cout << " " << p.second << endl;
        }
    }

    void predictNextMonth(const User &u, int currentYear, int currentMonth) {
        cout << "\n-- Predicted Spending for Next Month --\n";
        map<string, double> predictions;
        map<string, vector<double>> historical;

        for (int m = currentMonth - 2; m <= currentMonth; m++) {
            if (m <= 0) continue;
            auto monthData = u.getCategoryWiseExpense(currentYear, m);
            for (auto &p : monthData) {
                historical[p.first].push_back(p.second);
            }
        }

        if (historical.empty()) {
            cout << "Not enough historical data to predict.\n";
            return;
        }

        for (auto &p : historical) {
            if (!p.second.empty()) {
                double sum = 0;
                for (double val : p.second) sum += val;
                predictions[p.first] = sum / p.second.size();
            }
        }

        for (auto &p : predictions) {
            cout << setw(15) << p.first << " : " << p.second << endl;
        }
    }
};

// --------------------- FinanceManager Class ---------------------
class FinanceManager {
private:
    vector<User> users;
    Analytics analytics;

public:
    void addUser(const string& name) {
        users.emplace_back(name);
        cout << "User " << name << " added successfully!\n";
    }

    User* findUser(const string& name) {
        for (auto &u : users) {
            if (u.getName() == name) return &u;
        }
        return nullptr;
    }

    void addTransactionToUser(const string& name, const Transaction& t) {
        User* u = findUser(name);
        if (u) {
            u->addTransaction(t);
            saveData(); // auto-save after each transaction
        }
        else cout << "User not found!\n";
    }

    void runAnalytics(const string& name, int year, int month) {
        User* u = findUser(name);
        if (u) {
            analytics.generateReport(*u, year, month);
            analytics.suggestBudget(*u, year, month);
            analytics.detectAnomalies(*u, year, month);
        } else cout << "User not found!\n";
    }

    void predictNextMonthSpending(const string& name, int year, int month) {
        User* u = findUser(name);
        if (u) analytics.predictNextMonth(*u, year, month);
        else cout << "User not found!\n";
    }

    // --------------------- File Persistence ---------------------
    void saveData() {
        ofstream outFile("data.txt");
        if (!outFile) {
            cout << "Error opening file for saving.\n";
            return;
        }
        for (auto &u : users) {
            outFile << "USER|" << u.getName() << "|" << u.getBalance() << "\n";
            for (auto &t : u.getTransactions()) {
                outFile << "TRANS|" << t.getDate() << "|" << t.getType()
                        << "|" << t.getCategory() << "|" << t.getAmount() << "\n";
            }
        }
        outFile.close();
    }

    void loadData() {
        ifstream inFile("data.txt");
        if (!inFile) return;

        users.clear();
        string line;
        User* currentUser = nullptr;

        while (getline(inFile, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, '|');

            if (token == "USER") {
                string name, balanceStr;
                getline(ss, name, '|');
                getline(ss, balanceStr, '|');
                users.emplace_back(name);
                currentUser = &users.back();
            } else if (token == "TRANS") {
                string date, type, category, amtStr;
                getline(ss, date, '|');
                getline(ss, type, '|');
                getline(ss, category, '|');
                getline(ss, amtStr, '|');
                try {
                    double amt = stod(amtStr);
                    if (currentUser) currentUser->addTransaction(Transaction(amt, category, type, date));
                } catch (...) {
                    // skip bad line
                }
            }
        }
        inFile.close();
    }

    // --------------------- CLI ---------------------
    void displayMenu() {
        while (true) {
            cout << "\n--- SmartFi Menu ---\n"
                 << "1. Add User\n2. Add Transaction\n3. View Monthly Report & Analytics\n"
                 << "4. Predict Next Month Spending\n5. Exit\n";

            int choice;
            if (!safeReadInt("Choice: ", choice)) { // handles EOF and non-numeric safely
                cout << "\nInput stream closed. Exiting...\n";
                saveData();
                break;
            }

            switch (choice) {
                case 1: {
                    string uname;
                    if (!safeReadToken("Enter user name: ", uname)) { cout << "\nExiting...\n"; saveData(); return; }
                    addUser(uname);
                    saveData();
                } break;

                case 2: {
                    string uname;
                    if (!safeReadToken("Enter user name: ", uname)) { cout << "\nExiting...\n"; saveData(); return; }

                    User* u = findUser(uname);
                    if (!u) {
                        cout << "User not found! Please add the user first.\n";
                        break; // do not ask for the rest; prevents confusing loops
                    }

                    string type;
                    while (true) {
                        if (!safeReadToken("Enter transaction type (Income/Expense): ", type)) { cout << "\nExiting...\n"; saveData(); return; }
                        if (type == "Income" || type == "Expense") break;
                        cout << "Type must be exactly 'Income' or 'Expense'.\n";
                    }

                    string category;
                    if (!safeReadToken("Enter category: ", category)) { cout << "\nExiting...\n"; saveData(); return; }

                    double amt;
                    if (!safeReadDouble("Enter amount: ", amt)) { cout << "\nExiting...\n"; saveData(); return; }

                    string date;
                    while (true) {
                        if (!safeReadToken("Enter date (YYYY-MM-DD): ", date)) { cout << "\nExiting...\n"; saveData(); return; }
                        if (validateDate(date)) break;
                        cout << "Invalid date format. Please use YYYY-MM-DD.\n";
                    }

                    addTransactionToUser(uname, Transaction(amt, category, type, date));
                } break;

                case 3: {
                    string uname;
                    if (!safeReadToken("Enter user name: ", uname)) { cout << "\nExiting...\n"; saveData(); return; }
                    int year, month;
                    if (!safeReadInt("Enter year: ", year)) { cout << "\nExiting...\n"; saveData(); return; }
                    while (true) {
                        if (!safeReadInt("Enter month (1-12): ", month)) { cout << "\nExiting...\n"; saveData(); return; }
                        if (month >= 1 && month <= 12) break;
                        cout << "Month must be between 1 and 12.\n";
                    }
                    runAnalytics(uname, year, month);
                } break;

                case 4: {
                    string uname;
                    if (!safeReadToken("Enter user name: ", uname)) { cout << "\nExiting...\n"; saveData(); return; }
                    int year, month;
                    if (!safeReadInt("Enter current year: ", year)) { cout << "\nExiting...\n"; saveData(); return; }
                    while (true) {
                        if (!safeReadInt("Enter current month (1-12): ", month)) { cout << "\nExiting...\n"; saveData(); return; }
                        if (month >= 1 && month <= 12) break;
                        cout << "Month must be between 1 and 12.\n";
                    }
                    predictNextMonthSpending(uname, year, month);
                } break;

                case 5:
                    saveData();
                    return;

                default:
                    cout << "Invalid choice! Please select 1-5.\n";
            }
        }
    }
};

// --------------------- Main ---------------------
int main() {
    FinanceManager manager;
    manager.loadData();
    manager.displayMenu();
    return 0;
}
