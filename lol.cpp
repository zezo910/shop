// السلام عليكم ورحمة الله وبركاته
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>
#include <iomanip>
using namespace std;
// 1341 ewqre
// edit
// super ayman

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"


static int id_item = 11;
static int id_user = 1;
const string ADMIN_PASSWORD = "Prof_Elshf3y";

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void displayHeader( string title) {
    cout << CYAN << BOLD << "\n========================================\n";
    cout << "          " << title << "\n";
    cout << "========================================\n" << RESET;
}

void pressAnyKeyToContinue() {
    cout << YELLOW << "\nPress any key to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
}

int getValidNumber( string prompt = "Enter a number: ") {
    int num;
    while (true) {
        cout << prompt;
        if (cin >> num) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return num;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "Invalid input. Please enter a number.\n" << RESET;
    }
}

int getPositiveNumber( string prompt = "Enter a positive number: ") {
    int num;
    do {
        num = getValidNumber(prompt);
        if (num < 0) {
            cout << RED << "Please enter a positive number.\n" << RESET;
        }
    } while (num < 0);
    return num;
}

string getValidEmail() {
    string email;
    while (true) {
        cout << "Enter email: ";
        getline(cin, email);

        bool hasAt = false;
        bool hasSpace = false;
        for (char c : email) {
            if (c == '@') hasAt = true;
            if (isspace(c)) hasSpace = true;
        }

        if (email.empty()) {
            cout << RED << "Error: Email cannot be empty.\n" << RESET;
        } 
        else if (hasSpace) {
            cout << RED << "Error: Email cannot contain spaces.\n" << RESET;
        } 
        else if (!hasAt) {
            cout << RED << "Error: Email must contain @.\n" << RESET;
        } 
        else {
            return email;
        }
    }
}

string getValidPhone() {
    string phone;
    while (true) {
        cout << "Enter phone (11 digits starting with 0): ";
        getline(cin, phone);

        bool isValid = true;
        
        if (phone.length() != 11) {
            cout << RED << "Error: Phone number must be exactly 11 digits.\n" << RESET;
            isValid = false;
        }
        
        for (char c : phone) {
            if (!isdigit(c)) {
                cout << RED << "Error: Phone number must contain digits only.\n" << RESET;
                isValid = false;
                break;
            }
        }

        if (phone[0] != '0') {
            cout << RED << "Error: Phone number must start with 0.\n" << RESET;
            isValid = false;
        }

        if (isValid) {
            return phone;
        }
    }
}


class InventoryItem {
private:
    int item_id;
    string item_name;
    int quantity;
    double price;
    
public:
    InventoryItem() : item_id(0), quantity(0), price(0.0) {

    }
    
    InventoryItem(int id, string name, int qty, double pr) : 
        item_id(id), item_name(name), quantity(qty), price(pr) {
            
        }

    void displayItem() const {
        cout << BLUE << left << setw(5) << item_id << RESET << "| "
             << WHITE << setw(15) << item_name << RESET << "| "
             << GREEN << setw(8) << quantity << RESET << "| $"
             << YELLOW << setw(8) << fixed << setprecision(2) << price << RESET << endl;
    }

    string getItemName() const {
         return item_name; 
        }
    int getItemId() const { 
        return item_id; 
        }
    double getPrice() const {
         return price; 
        }
    int getQuantity() const {
         return quantity; 
        }

    void setQuantity(int q) {
         quantity = q;
        }
    void setPrice(double p) {
         price = p;
        }
    void setItemName(const string& name) { 
        item_name = name;
        }
    void setItemId(int id) { 
        item_id = id; 
    }
    
    void reduceQuantity(int q) {
         quantity -= q; 
        }
};


class User {
private:
    int user_id;
    string name;
    string email;
    string phone;
    string password;
    double balance;
    vector<pair<string, int>> purchasedItems; 
    
public:
    User() : user_id(0), balance(0.0) {}
    
    User(int id, const string& n, const string& e, const string& ph, const string& pwd) :
        user_id(id), name(n), email(e), phone(ph), password(pwd), balance(0.0) {}

    void display() const {
        cout << "ID: " << BLUE << user_id << RESET 
        << " | Name: " << WHITE << name << RESET
        << " | Email: " << email << " | Phone: " << phone << endl;
    }

    string getName() const { 
        return name; 
    }
    string getEmail() const { 
        return email; 
    }
    string getPhone() const { 
        return phone; 
    }
    string getPassword() const { 
        return password; 
    }
    double getBalance() const { 
        return balance; 
    }
    
    void addBalance(double amount) { 
        balance += amount; 
        cout << GREEN << "$" << fixed << setprecision(2) << amount 
             << " added successfully. New balance: $" << balance << RESET << endl;
    }

    bool deductBalance(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    void addPurchasedItem(const string& itemName, int quantity) {
        purchasedItems.emplace_back(itemName, quantity);
    }

    void displayPurchasedItems() const {
        for (const auto& item : purchasedItems) {
            cout << "- " << WHITE << item.first << RESET << " (Qty: " 
                 << GREEN << item.second << RESET << ")\n";
        }
    }
    
    double processPurchase(vector<InventoryItem>& inventory) {
        double total = 0.0;
        char choice;
        
        do {
            clearScreen();
            displayHeader("AVAILABLE ITEMS");
            displayInventory(inventory);
            
            int itemId = getPositiveNumber("Enter item ID to purchase (0 to finish): ");
            if (itemId == 0)
             break;
            
            int quantity = getPositiveNumber("Enter quantity: ");
            
            bool found = false;
            for (auto& item : inventory) {
                if (item.getItemId() == itemId) {
                    found = true;
                    if (item.getQuantity() < quantity) {
                        cout << RED << "Insufficient quantity. Available: " 
                             << item.getQuantity() << RESET << endl;
                        break;
                    }
                    
                    double itemTotal = item.getPrice() * quantity;
                    if (!deductBalance(itemTotal)) {
                        cout << RED << "Insufficient balance. You need $" 
                             << (itemTotal - balance) << " more." << RESET << endl;
                        break;
                    }
                    
                    item.reduceQuantity(quantity);
                    total += itemTotal;
                    addPurchasedItem(item.getItemName(), quantity);
                    cout << GREEN << "Added " << quantity << " x " << item.getItemName() 
                         << " ($" << itemTotal << ") to your cart." << RESET << endl;
                    break;
                }
            }
            
            if (!found) {
                cout << RED << "Item not found with ID: " << itemId << RESET << endl;
            }
            
            cout << "Continue shopping? (y/n): ";
            cin >> choice;
            cin.ignore();
        } 
        while (choice == 'y' || choice == 'Y');
        
        return total;
    }
    
    static void displayInventory(const vector<InventoryItem>& inventory) {
        cout << YELLOW << BOLD << left << setw(5) << "ID" << RESET << "| "
             << YELLOW << BOLD << setw(15) << "Item Name" << RESET << "| "
             << YELLOW << BOLD << setw(8) << "Qty" << RESET << "| "
             << YELLOW << BOLD << setw(8) << "Price" << RESET << endl;
        cout << GREEN << "----------------------------------------\n" << RESET;
        
        for (const auto& item : inventory) {
            item.displayItem();
        }
    }
};


class InventorySystem {
private:
    vector<InventoryItem> inventory;
    
public:
    InventorySystem() {
        inventory = {
            {1, "milk", 10, 50.0},
            {2, "bread", 20, 20.0},
            {3, "egg", 30, 10.0},
            {4, "juice", 40, 30.0},
            {5, "sugar", 50, 15.0},
            {6, "salt", 60, 5.0},
            {7, "tomato", 70, 25.0},
            {8, "potato", 80, 12.0},
            {9, "onion", 90, 18.0},
            {10, "carrot", 100, 22.0}
        };
        id_item = 11;
    }
    
    void addItem() {
        clearScreen();
        displayHeader("ADD NEW ITEM");
        
        InventoryItem item;
        item.setItemId(id_item++);
        
        cout << "Enter item name: ";
        string name;
        cin >> name;
        item.setItemName(name);
        
        item.setQuantity(getPositiveNumber("Enter quantity: "));
        item.setPrice(getPositiveNumber("Enter price: "));
        
        inventory.push_back(item);
        cout << GREEN << "\nItem added successfully!\n" << RESET;
        pressAnyKeyToContinue();
    }
    
    void deleteItem() {
        clearScreen();
        displayHeader("DELETE ITEM");
        displayAllItems();
        
        int id = getPositiveNumber("Enter item ID to delete: ");
        
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if (it->getItemId() == id) {
                inventory.erase(it);
                cout << GREEN << "\nItem deleted successfully!\n" << RESET;
                pressAnyKeyToContinue();
                return;
            }
        }
        
        cout << RED << "\nItem not found with ID: " << id << RESET << endl; 
        pressAnyKeyToContinue();
    }
    
    void displayAllItems() const {
        cout << YELLOW << BOLD << left << setw(5) << "ID" << RESET << "| "
             << YELLOW << BOLD << setw(15) << "Item Name" << RESET << "| "
             << YELLOW << BOLD << setw(8) << "Qty" << RESET << "| "
             << YELLOW << BOLD << setw(8) << "Price" << RESET << endl;
        cout << GREEN << "----------------------------------------\n" << RESET;
        
        for (const auto& item : inventory) {
            item.displayItem();
        }
    }
    
    void updatePrice() {
        clearScreen();
        displayHeader("UPDATE PRICE");
        displayAllItems();
        
        int id = getPositiveNumber("Enter item ID to update price: ");
        
        for (auto& item : inventory) {
            if (item.getItemId() == id) {
                double newPrice = getPositiveNumber("Enter new price: ");
                item.setPrice(newPrice);
                cout << GREEN << "\nPrice updated successfully!\n" << RESET;
                pressAnyKeyToContinue();
                return;
            }
        }
        
        cout << RED << "\nItem not found with ID: " << id << RESET << endl;
        pressAnyKeyToContinue();
    }
    
    void updateQuantity() {
        clearScreen();
        displayHeader("UPDATE QUANTITY");
        displayAllItems();
        
        int id = getPositiveNumber("Enter item ID to update quantity: ");
        
        for (auto& item : inventory) {
            if (item.getItemId() == id) {
                int newQty = getPositiveNumber("Enter new quantity: ");
                item.setQuantity(newQty);
                cout << GREEN << "\nQuantity updated successfully!\n" << RESET;
                pressAnyKeyToContinue();
                return;
            }
        }
        
        cout << RED << "\nItem not found with ID: " << id << RESET << endl;
        pressAnyKeyToContinue();
    }
    
    vector<InventoryItem>& getInventory() { 
        return inventory; 
    }
};


class UserManager {
private:
    vector<User> users;
    
public:
    UserManager() : users() {}
    
    void registerUser() {
        clearScreen();
        displayHeader("USER REGISTRATION");
        
        User user;
        user = User(id_user++, "", "", "", "");
        
        cout << "Enter your name: ";
        string name;
        cin >> name;
        
        cin.ignore();
        string email = getValidEmail();
        string phone = getValidPhone();
        
        cout << "Enter your password: ";
        string password;
        cin >> password;
        
        users.emplace_back(id_user - 1, name, email, phone, password);
        cout << GREEN << "\nRegistration successful! Your user ID is: " 
             << (id_user - 1) << RESET << endl;
        pressAnyKeyToContinue();
    }
    
    User* loginUser() {
        clearScreen();
        displayHeader("USER LOGIN");
        
        cout << "Enter your name or email: ";
        string identifier;
        cin >> identifier;
        
        cout << "Enter your password: ";
        string password;
        cin >> password;
        
        for (auto& user : users) {
            if ((user.getName() == identifier || user.getEmail() == identifier) && 
                user.getPassword() == password) {
                cout << GREEN << "\nLogin successful!\n" << RESET;
                pressAnyKeyToContinue();
                return &user;
            }
        }
        
        cout << RED << "\nInvalid credentials. Please try again.\n" << RESET;
        pressAnyKeyToContinue();
        return nullptr;
    }
};


class ShoppingSystem {
private:
    InventorySystem inventorySystem;
    UserManager userManager;
    User* currentUser = nullptr;
    
public:
    void run() {
        while (true) {
            clearScreen();
            displayHeader("MAIN MENU");
            
            cout << "1. Management System\n";
            cout << "2. User System\n";
            cout << "3. Exit\n";
            
            int choice = getPositiveNumber("Enter your choice: ");
            
            switch (choice) {
                case 1:
                managementSystem(); 
                break;
                case 2: 
                userSystem(); 
                break;
                case 3: 
                    cout << MAGENTA << "\nThank you for using our system. Goodbye!\n" << RESET;
                    return;
                default:
                    cout << RED << "\nInvalid choice. Please try again.\n" << RESET;
                    pressAnyKeyToContinue();
            }
        }
    }
    
private:
    void managementSystem() {
        while (true) {
            clearScreen();
            displayHeader("MANAGEMENT SYSTEM");
            
            cout << "Enter admin password (or 'back' to return): ";
            string password;
            cin >> password;
            
            if (password == "back") return;
            
            if (password != ADMIN_PASSWORD) {
                cout << RED << "\nIncorrect password. Access denied.\n" << RESET;
                pressAnyKeyToContinue();
                continue;
            }
            
            while (true) {
                clearScreen();
                displayHeader("ADMIN DASHBOARD");
                
                cout << "1. Add Item\n";
                cout << "2. Delete Item\n";
                cout << "3. View All Items\n";
                cout << "4. Update Item Price\n";
                cout << "5. Update Item Quantity\n";
                cout << "6. Return to Main Menu\n";
                
                int choice = getPositiveNumber("Enter your choice: ");
                
                switch (choice) {
                    case 1: 
                    inventorySystem.addItem(); break;
                    case 2: 
                    inventorySystem.deleteItem(); break;
                    case 3: 
                        clearScreen();
                        displayHeader("INVENTORY ITEMS");
                        inventorySystem.displayAllItems();
                        pressAnyKeyToContinue();
                        break;
                    case 4: 
                    inventorySystem.updatePrice(); 
                    break;
                    case 5: 
                    inventorySystem.updateQuantity(); 
                    break;
                    case 6: 
                    return;
                    default:
                        cout << RED << "\nInvalid choice. Please try again.\n" << RESET;
                        pressAnyKeyToContinue();
                }
            }
        }
    }
    
    void userSystem() {
        while (true) {
            clearScreen();
            displayHeader("USER SYSTEM");
            
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. Return to Main Menu\n";
            
            int choice = getPositiveNumber("Enter your choice: ");
            
            switch (choice) {
                case 1: 
                    userManager.registerUser();
                    break;
                case 2: 
                    currentUser = userManager.loginUser();
                    if (currentUser) userMenu();
                    break;
                case 3: 
                    return;
                default:
                    cout << RED << "\nInvalid choice. Please try again.\n" << RESET;
                    pressAnyKeyToContinue();
            }
        }
    }
    
    void userMenu() {
        while (currentUser) {
            clearScreen();
            displayHeader("USER DASHBOARD");
            cout << "Welcome, " << MAGENTA << currentUser->getName() << RESET << "!\n";
            cout << "Current balance: " << BOLD << BLUE << "$" << fixed << setprecision(2) 
                 << currentUser->getBalance() << RESET << "\n\n";
            
            cout << "1. Shop\n";
            cout << "2. Add Funds\n";
            cout << "3. View Items\n";
            cout << "4. Logout\n";
            
            int choice = getPositiveNumber("Enter your choice: ");
            
            switch (choice) {
                case 1: {
                    double total = currentUser->processPurchase(inventorySystem.getInventory());
                    if (total > 0) {
                        displayReceipt(*currentUser, total);
                    }
                    break;
                }
                case 2: {
                    double amount = getPositiveNumber("Enter amount to add: $");
                    currentUser->addBalance(amount);
                    pressAnyKeyToContinue();
                    break;
                }
                case 3: {
                    clearScreen();
                    displayHeader("AVAILABLE ITEMS");
                    User::displayInventory(inventorySystem.getInventory());
                    pressAnyKeyToContinue();
                    break;
                }
                case 4: 
                    currentUser = nullptr;
                    cout << GREEN << "\nLogged out successfully.\n" << RESET;
                    pressAnyKeyToContinue();
                    return;
                default:
                    cout << RED << "\nInvalid choice. Please try again.\n" << RESET;
                    pressAnyKeyToContinue();
            }
        }
    }
    
    void displayReceipt(const User& user, double total) {
        clearScreen();
        displayHeader("PURCHASE RECEIPT");
        
        cout << MAGENTA << "Customer: " << user.getName() << "\n";
        cout << "Email: " << user.getEmail() << "\n";
        cout << "Phone: " << user.getPhone() << "\n";
        cout << "----------------------------------------\n";
        
        cout << BOLD << "Purchased Items:\n" << RESET;
        user.displayPurchasedItems();
        
        cout << "----------------------------------------\n";
        cout << YELLOW << "Total: $" << fixed << setprecision(2) << total << "\n";
        cout << GREEN << "Remaining Balance: $" << user.getBalance() << "\n";
        cout << "----------------------------------------\n";
        cout << BOLD << "Thank you for your purchase!\n" << RESET;
        pressAnyKeyToContinue();
    }
};


int main() {
    ShoppingSystem system;
    system.run();
    return 0;
}
