// VinGameInventory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<string>
#include<vector>

using namespace std;

// Forward declarations
class Item;
class Inventory;

// Item class definition
class Item
{
public:
    Item()
    {
        name = "";
        float price;
        float quantity;
    }
    void add_or_edit_data(bool is_add);
    void display_data();
    void set_price(float new_price); // added function
    float get_price();
    void set_quantity(int);
    int get_quantity();
    int is_match(string);
    string get_name() { return name; }

private:
    string name;
    float price;
    int quantity;
};

// Inventory class definition
class Inventory
{
public:
    void add_item();
    void sell_item(string item_name);
    void sell_item(int);
    void find_item();
    void edit_item();
    void list_items();

private:
    vector<Item*> items;
    float total_money = 0.0f;
};

// Item class member functions

// Prompt the user to enter data for a new item or edit data of an item and store it in the object
void Item::add_or_edit_data(bool is_add)
{
    string action = is_add ? "add" : "edit";
    cin.ignore();
    cout << "\nEnter item name to " << action << ": ";
    getline(cin, name);
    cout << "Enter quantity: ";
    cin >> quantity;
    cout << "Enter price: ";
    cin >> price;
}

// Display the data stored in the object
void Item::display_data()
{
    cout << "\nItem name: " << name;
    cout << "\nQuantity: " << quantity;
    cout << "\nPrice: " << price;
}

// Set the price of the item
void Item::set_price(float new_price)
{
    price = new_price;
}

// Return the price of the item
float Item::get_price()
{
    return price;
}

// Set the quantity of the item to a new value
void Item::set_quantity(int new_quantity)
{
    quantity = new_quantity;
}

// Return the quantity of the item
int Item::get_quantity()
{
    return quantity;
}

int Item::is_match(string item_name)
{
    return name == item_name;
}

// Invent class member functions

// Add a new item to the inventory
void Inventory::add_item()
{
    Item* new_item = new Item;
    new_item->add_or_edit_data(true);

    // check for existing item with the same name
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->is_match(new_item->get_name()))
        {
            cout << "An item with the same name is already in the inventory.\n";
            cout << "What do you want to do?\n";
            cout << "1. Update Quantity\n";
            cout << "2. Update Price\n";
            cout << "3. Cancel\n";
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter new quantity: ";
                int new_quantity;
                cin >> new_quantity;
                items[i]->set_quantity(new_quantity);
                break;
            case 2:
                cout << "Enter new price: ";
                float new_price;
                cin >> new_price;
                items[i]->set_price(new_price);
                break;
            case 3:
                break;
            default:
                cout << "Invalid choice. Operation cancelled.\n";
                break;
            }
            return;
        }
    }
    items.push_back(new_item);
    cout << "Item added successfully" << endl;

}


// Sell an item from the inventory
void Inventory::sell_item(string item_name)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->is_match(item_name))
        {
            sell_item(i);
            cout << "\nNumber of items left in stock: " << items[i]->get_quantity();
            return;
        }
    }
    throw std::invalid_argument("Item not found in inventory");
}

// Sell a specific item from the inventory
void Inventory::sell_item(int item_index)
{
    int input_quantity;
    Item* item = items[item_index];
    cout << "\nEnter number of items to sell: ";
    cin >> input_quantity;

    int quantity = item->get_quantity();
    if (input_quantity <= quantity)
    {
        float price = item->get_price();
        float money_earned = price * input_quantity;
        item->set_quantity(quantity - input_quantity);
        cout << "\nItems sold sucessfully";
        cout << "\nMoney received: " << money_earned;
        total_money += money_earned;
    }
    else
    {
        throw std::invalid_argument("Not enough items in stock");
    }
}

// Find an item in the inventory
void Inventory::find_item()
{
    string item_name;
    cin.ignore();
    cout << "\nEnter item name to find: ";
    getline(cin, item_name);

    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->is_match(item_name))
        {
            items[i]->display_data();
            return;
        }
    }

    cout << "Item not found in inventory." << endl;
}

// Edit an item in the inventory
void Inventory::edit_item()
{
    string item_name;
    cin.ignore();
    cout << "\nEnter item name to edit: ";
    getline(cin, item_name);

    for (int i = 0; i < items.size(); i++)
    {
        if (items[i]->is_match(item_name))
        {
            items[i]->add_or_edit_data(false);
            cout << "Item edited successfully" << endl;
            return;
        }
    }
    cout << "Item not found in inventory." << endl;
}

// List all items in the inventory
void Inventory::list_items()
{
    if (items.size() == 0)
    {
        cout << "No items in inventory" << endl;
        return;
    }
    cout << "\nInventory: " << endl;
    for (int i = 0; i < items.size(); i++)
    {
        cout << i + 1 << ". ";
        items[i]->display_data();
        cout << endl;
    }
    cout << "\nTotal money: " << total_money << endl;
}

int main()
{
    Inventory inv;
    int choice;

    do
    {
        cout << "\n\nMENU" << endl;
        cout << "1. Add item" << endl;
        cout << "2. Sell item" << endl;
        cout << "3. Find item" << endl;
        cout << "4. Edit item" << endl;
        cout << "5. List items" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            inv.add_item();
            break;
        case 2:
            try
        {
            string item_name;
            cin.ignore();
            cout << "Enter item name to sell: ";
            cin >> item_name;
            inv.sell_item(item_name);
        }
        catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
        }
        break;
        case 3:
            inv.find_item();
            break;
        case 4:
            inv.edit_item();
            break;
        case 5:
            inv.list_items();
            break;
        case 6:
            exit(0);
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }
    } while (choice != 6);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file