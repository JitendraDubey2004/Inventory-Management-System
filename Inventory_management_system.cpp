#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Product class representing individual products
class Product {
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    // Constructors
    Product() : id(0), name(""), price(0.0), quantity(0) {}
    Product(int id, const string& name, double price, int quantity) 
        : id(id), name(name), price(price), quantity(quantity) {}

    // Getters and Setters
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

 void setId(int id) { this->id = id; }
    void setName(const string& name) { this->name = name; }
    void setPrice(double price) { this->price = price; }
    void setQuantity(int quantity) { this->quantity = quantity; }

    // Display Product information
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Price: " << price << ", Quantity: " << quantity << endl;
    }

    // Overloading << operator for file output
    friend ofstream& operator<<(ofstream& ofs, const Product& product) {
        ofs << product.id << " " << product.name << " " << product.price << " " << product.quantity << endl;
        return ofs;
    }

    // Overloading >> operator for file input
    friend ifstream& operator>>(ifstream& ifs, Product& product) {
        ifs >> product.id >> product.name >> product.price >> product.quantity;
        return ifs;
    }
};

// Inventory class for managing products
class Inventory {
private:
    vector<Product> products;

public:
    // Add a new product
    void addProduct(const Product& product) {
        products.push_back(product);
    }
    // Remove a product by ID
    void removeProduct(int id) {
        products.erase(remove_if(products.begin(), products.end(), 
                                 [id](const Product& product) { return product.getId() == id; }), products.end());
    }

    // Update a product's details by ID
    void updateProduct(int id, const string& name, double price, int quantity) {
        for (auto& product : products) {
            if (product.getId() == id) {
                product.setName(name);
                product.setPrice(price);
                product.setQuantity(quantity);
                break;
            }
        }
    }

    // Display all products
    void displayProducts() const {
        for (const auto& product : products) {
            product.display();
        }
    }

    // Save products to a file
    void saveToFile(const string& filename) const {
        ofstream ofs(filename);
        for (const auto& product : products) {
            ofs << product;
        }
        ofs.close();
    }

    // Load products from a file
    void loadFromFile(const string& filename) {
        ifstream ifs(filename);
  Product product;
        while (ifs >> product) {
            products.push_back(product);
        }
        ifs.close();
    }
};

// Function prototypes
void displayMenu();
void handleUserInput(Inventory& inventory);

int main() {
    Inventory inventory;
    inventory.loadFromFile("inventory.txt");

    handleUserInput(inventory);

    inventory.saveToFile("inventory.txt");

    return 0;
}

// Function to display the menu
void displayMenu() {
    cout << "Inventory Management System" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Remove Product" << endl;
    cout << "3. Update Product" << endl;
    cout << "4. Display Products" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to handle user input and interact with Inventory
void handleUserInput(Inventory& inventory) {
    int choice;
do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, quantity;
                string name;
                double price;
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Product Name: ";
                cin >> name;
                cout << "Enter Product Price: ";
                cin >> price;
                cout << "Enter Product Quantity: ";
                cin >> quantity;
                inventory.addProduct(Product(id, name, price, quantity));
                break;
            }
            case 2: {
                int id;
                cout << "Enter Product ID to Remove: ";
                cin >> id;
                inventory.removeProduct(id);
                break;
            }
            case 3: {
                int id, quantity;
                string name;
                double price;
                cout << "Enter Product ID to Update: ";
                cin >> id;
                cout << "Enter New Product Name: ";
                cin >> name;
                cout << "Enter New Product Price: ";
                cin >> price;
                cout << "Enter New Product Quantity: ";
cin >> quantity;
                inventory.updateProduct(id, name, price, quantity);
                break;
            }
            case 4: {
                inventory.displayProducts();
                break;
            }
            case 5: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice, please try again." << endl;
                break;
            }
        }
    } while (choice != 5);
}


