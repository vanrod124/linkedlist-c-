

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <stack>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <queue>
#include <iterator>

#include <string>

using namespace std;




struct node
{
    int idnum;
    string Name;
    int NumberofQuantity;
};


struct node2
{
    int idnum;
    string name;
    string address;
    int payment;
};


struct node3
{
    int idnum;
    int idproduct;
    int idcustomer;
};

class Product
{



private:
    list<node> product;

public:
    stack<node3> rv;
    Product();

    // void addproduct
    void addproduct(int idnum, string Name, int NumberofQuantity);
    void newProduct();
    // buy product
    void buyProduct(int customerid);
    void showAllProductDetails();
    // show product
    void showProduct(int id);
    // check product availability
    void checkProductAvailability();
    // save product
    void save();
    // load product
    void load(ifstream &my_file);
    bool t;
};

class Customer
{

private:
public:
    queue<node2> customers;
    Customer();

    void addCustomer();
    void showCustomerDetails();
    void showAll();
    void showList();
    // delete a customer
    void deleteCustomer();
    void save();
    void load(ifstream &my_file);
    bool t;
};

Product::Product()
{
    ifstream inFile("products.txt", ios::in);
    if (inFile.is_open())
    {
        load(inFile);
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for loading products." << endl;
    }
}

Customer::Customer()
{
    ifstream inFile("customers.txt", ios::in);
    if (inFile.is_open())
    {
        load(inFile);
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for loading customers." << endl;
    }
}



void Product::addproduct(int idnum, string Name, int NumberofQuantity)
{
    node newnode;
    newnode.idnum = idnum;
    newnode.Name = Name;
    newnode.NumberofQuantity = NumberofQuantity;
    product.push_back(newnode);
}



void Product::newProduct()
{
    int idnum;
    string Name;
    int NumberofQuantity;

    cout << "Enter Product ID: ";
    cin >> idnum;
    cin.ignore();
    cout << "Enter Product Name: ";
    getline(cin, Name);
    cout << "Enter Product Quantity: ";
    cin >> NumberofQuantity;

    addproduct(idnum, Name, NumberofQuantity);
}

void Product::buyProduct(int customerid)
{
    int id;
    cout << "Enter Product ID to buy: ";
    cin >> id;

    for (auto &p : product)
    {
        if (p.idnum == id)
        {
            if (p.NumberofQuantity > 0)
            {
                p.NumberofQuantity--;
                node3 rentedVideo;
                rentedVideo.idcustomer = customerid;
                rentedVideo.idproduct = id;
                rv.push(rentedVideo);
                cout << "Product successfully bought." << endl;
            }
            else
            {
                cout << "Product not available." << endl;
            }
            return;
        }
    }
    cout << "Product not found." << endl;
}

void Product::showAllProductDetails()
{
    for (const auto &p : product)
    {
        cout << "Product ID: " << p.idnum << endl;
        cout << "Product Name: " << p.Name << endl;
        cout << "Product Quantity: " << p.NumberofQuantity << endl;
        cout << "----------------------" << endl;
    }
}

void Product::showProduct(int id)
{
    for (const auto &p : product)
    {
        if (p.idnum == id)
        {
            cout << "Product ID: " << p.idnum << endl;
            cout << "Product Name: " << p.Name << endl;
            cout << "Product Quantity: " << p.NumberofQuantity << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

void Product::checkProductAvailability()
{
    int id;
    cout << "Enter Product ID to check availability: ";
    cin >> id;

    for (const auto &p : product)
    {
        if (p.idnum == id)
        {
            if (p.NumberofQuantity > 0)
            {
                cout << "Product is available." << endl;
            }
            else
            {
                cout << "Product is not available." << endl;
            }
            return;
        }
    }
    cout << "Product not found." << endl;
}


void Product::save()
{
    ofstream outFile("products.txt", ios::out);
    if (outFile.is_open())
    {
        for (const auto &p : product)
        {
            outFile << p.idnum << "," << p.Name << "," << p.NumberofQuantity << endl;
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for saving products." << endl;
    }
}


void Product::load(ifstream &my_file)
{
    product.clear();
    node temp;
    while (my_file >> temp.idnum)
    {
        my_file.ignore(); // To ignore the newline character after reading idnum
        getline(my_file, temp.Name);
        my_file >> temp.NumberofQuantity;
        my_file.ignore(); // To ignore the newline character after reading NumberofQuantity
        product.push_back(temp);
    }
}



// Customer class methods

void Customer::addCustomer()
{
    node2 newCustomer;
    cout << "Enter Customer ID: ";
    cin >> newCustomer.idnum;
    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, newCustomer.name);
    cout << "Enter Customer Address: ";
    getline(cin, newCustomer.address);
    cout << "Enter Payment: ";
    cin >> newCustomer.payment;

    customers.push(newCustomer);
}

void Customer::showCustomerDetails()
{
    int id;
    cout << "Enter Customer ID: ";
    cin >> id;

    queue<node2> tempQueue;
    bool found = false;
    while (!customers.empty())
    {
        node2 c = customers.front();
        if (c.idnum == id)
        {
            found = true;
            cout << "Customer ID: " << c.idnum << endl;
            cout << "Customer Name: " << c.name << endl;
            cout << "Customer Address: " << c.address << endl;
            cout << "Payment: " << c.payment << endl;
        }
        tempQueue.push(c);
        customers.pop();
    }
    customers = tempQueue;

    if (!found)
    {
        cout << "Customer not found." << endl;
    }
}


void Customer::showAll()
{
    queue<node2> tempQueue;
    while (!customers.empty())
    {
        node2 c = customers.front();
        cout << "Customer ID: " << c.idnum << endl;
        cout << "Customer Name: " << c.name << endl;
        cout << "Customer Address: " << c.address << endl;
        cout << "Payment: " << c.payment << endl;
        cout << "----------------------" << endl;
        tempQueue.push(c);
        customers.pop();
    }
    customers = tempQueue;
}

void Customer::showList()
{
    int count = 1;
    queue<node2> tempQueue;
    while (!customers.empty())
    {
        node2 c = customers.front();
        cout << count << ". " << c.name << " (ID: " << c.idnum << ")" << endl;
        tempQueue.push(c);
        customers.pop();
        count++;
    }
    customers = tempQueue;
}


void Customer::deleteCustomer()
{
    int id;
    cout << "Enter Customer ID to delete: ";
    cin >> id;

    queue<node2> tempQueue;
    bool found = false;
    while (!customers.empty())
    {
        node2 c = customers.front();
        if (c.idnum == id)
        {
            found = true;
            cout << "Customer successfully deleted." << endl;
        }
        else
        {
            tempQueue.push(c);
        }
        customers.pop();
    }
    customers = tempQueue;

    if (!found)
    {
        cout << "Customer not found." << endl;
    }
}


void Customer::save()
{
    ofstream outFile("customers.txt", ios::out);
    if (outFile.is_open())
    {
        while (!customers.empty())
        {
            node2 c = customers.front();
            outFile << c.idnum << "," << c.name << "," << c.address << "," << c.payment << endl;
            customers.pop();
            customers.push(c);
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for saving customers." << endl;
    }
}


void Customer::load(ifstream &my_file)
{
    while (!customers.empty())
    {
        customers.pop();
    }

    node2 temp;
    while (my_file >> temp.idnum)
    {
        my_file.ignore(); // To ignore the newline character after reading idnum
        getline(my_file, temp.name);
        getline(my_file, temp.address);
        my_file >> temp.payment;
        my_file.ignore(); // To ignore the newline character after reading payment
        customers.push(temp);
    }
}

// Add this struct at the beginning, after the existing structs
struct PurchaseNode {
    int purchaseId;
    int customerId;
    int productId;
    int quantity;
};

// Create a new class called Purchase
class Purchase {
private:
    list<PurchaseNode> purchases;
    int nextPurchaseId;

public:
    Purchase();

    void addPurchase(int customerId, int productId, int quantity);
    void showPurchaseHistory(int customerId);
    void save();
    void load(ifstream &my_file);
};

// Implement the Purchase class methods

Purchase::Purchase() : nextPurchaseId(1) {
    ifstream inFile("purchases.txt", ios::in);
    if (inFile.is_open()) {
        load(inFile);
        inFile.close();
    } else {
        cout << "Unable to open file for loading purchases." << endl;
    }
}

void Purchase::addPurchase(int customerId, int productId, int quantity) {
    PurchaseNode newPurchase;
    newPurchase.purchaseId = nextPurchaseId++;
    newPurchase.customerId = customerId;
    newPurchase.productId = productId;
    newPurchase.quantity = quantity;
    purchases.push_back(newPurchase);
    cout << "Purchase added successfully." << endl;
}

void Purchase::showPurchaseHistory(int customerId) {
    cout << "Purchase history for customer ID " << customerId << ":" << endl;
    for (const auto &p : purchases) {
        if (p.customerId == customerId) {
            cout << "Purchase ID: " << p.purchaseId << endl;
            cout << "Product ID: " << p.productId << endl;
            cout << "Quantity: " << p.quantity << endl;
            cout << "----------------------" << endl;
        }
    }
}

void Purchase::save() {
    ofstream outFile("purchases.txt", ios::out);
    if (outFile.is_open()) {
        for (const auto &p : purchases) {
            outFile << p.purchaseId << "," << p.customerId << "," << p.productId << "," << p.quantity << endl;
        }
        outFile.close();
    } else {
        cout << "Unable to open file for saving purchases." << endl;
    }
}

void Purchase::load(ifstream &my_file) {
    purchases.clear();
    PurchaseNode temp;
    while (my_file >> temp.purchaseId) {
        my_file.ignore(); // To ignore the newline character after reading purchaseId
        my_file >> temp.customerId;
        my_file.ignore(); // To ignore the newline character after reading customerId
        my_file >> temp.productId;
        my_file.ignore(); // To ignore the newline character after reading productId
        my_file >> temp.quantity;
        my_file.ignore(); // To ignore the newline character after reading quantity
        purchases.push_back(temp);
    }
    if (!purchases.empty()) {
        nextPurchaseId = purchases.back().purchaseId + 1;
    }
}


int main()
{
    Product product;
    Purchase purchase;
    Customer customer;

    // Load data from files (if available)
    ifstream productFile("products.txt");
    if (productFile.is_open())
    {
        product.load(productFile);
        productFile.close();
    }
    ifstream customerFile("customers.txt");
    if (customerFile.is_open())
    {
        customer.load(customerFile);
        customerFile.close();
    }
        ifstream purchaseFile("purchases.txt");
    if (purchaseFile.is_open()) {
        purchase.load(purchaseFile);
        purchaseFile.close();
    }

    int choice = 0;
    while (choice != 9) {
        cout << "Welcome to the Product/Customer Management System" << endl;
cout << "Please choose an option:" << endl;
cout << "1. Add a new product" << endl;
cout << "2. Buy a product" << endl;
cout << "3. Check product availability" << endl;
cout << "4. Add a new customer" << endl;
cout << "5. Show customer details" << endl;
cout << "6. Add a purchase" << endl;
cout << "7. Show purchase history" << endl;
cout << "8. Save all data" << endl;
cout << "9. Exit" << endl;
cout << "Choice: ";
cin >> choice;

        switch (choice)
        {
            case 1:
                product.newProduct();
                break;
            case 2:
                int customerid;
                cout << "Enter Customer ID: ";
                cin >> customerid;
                product.buyProduct(customerid);
                break;
            case 3:
                product.checkProductAvailability();
                break;
            case 4:
                customer.addCustomer();
                break;
            case 5:
                customer.showCustomerDetails();
                break;
           case 6:
        {
            int customerId, productId, quantity;
            cout << "Enter Customer ID: ";
            cin >> customerId;
            cout << "Enter Product ID: ";
            cin >> productId;
            cout << "Enter Quantity: ";
            cin >> quantity;
            purchase.addPurchase(customerId, productId, quantity);
            break;
        }
        case 7:
        {
            int customerId;
            cout << "Enter Customer ID: ";
            cin >> customerId;
            purchase.showPurchaseHistory(customerId);
            break;
        }
        case 8:
        {
            product.save();
            customer.save();
            purchase.save();
            cout << "Data saved successfully." << endl;
            break;
        }
        case 9:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}


product.save();
customer.save();
purchase.save();

    

    return 0;
}




