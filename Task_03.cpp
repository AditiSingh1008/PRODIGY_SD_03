// Implement a Simple Contact Management System

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

void addContact(vector<Contact>& contacts);
void viewContacts(const vector<Contact>& contacts);
void editContact(vector<Contact>& contacts);
void deleteContact(vector<Contact>& contacts);
void loadContacts(vector<Contact>& contacts, const string& filename);
void saveContacts(const vector<Contact>& contacts, const string& filename);

int main() {
    vector<Contact> contacts;
    const string filename = "contacts.txt";

    // Load contacts from file
    loadContacts(contacts, filename);

    int choice;
    do {
        // Display the menu
        cout << "Contact Manager\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle user choice
        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                editContact(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                // Save contacts to file before exiting
                saveContacts(contacts, filename);
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}

void addContact(vector<Contact>& contacts) {
    Contact newContact;

    cout << "Enter name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newContact.name);
    cout << "Enter phone number: ";
    getline(cin, newContact.phone);
    cout << "Enter email address: ";
    getline(cin, newContact.email);

    contacts.push_back(newContact);
    cout << "Contact added successfully.\n";
}

void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to display.\n";
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << "Contact " << i + 1 << ":\n";
        cout << "Name: " << contacts[i].name << "\n";
        cout << "Phone: " << contacts[i].phone << "\n";
        cout << "Email: " << contacts[i].email << "\n";
        cout << "-----------------------\n";
    }
}

void editContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to edit.\n";
        return;
    }

    int index;
    cout << "Enter the contact number to edit: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    Contact& contact = contacts[index - 1];
    cout << "Editing contact " << index << ":\n";
    cout << "Enter new name (or press Enter to keep current): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        contact.name = newName;
    }
    cout << "Enter new phone number (or press Enter to keep current): ";
    string newPhone;
    getline(cin, newPhone);
    if (!newPhone.empty()) {
        contact.phone = newPhone;
    }
    cout << "Enter new email address (or press Enter to keep current): ";
    string newEmail;
    getline(cin, newEmail);
    if (!newEmail.empty()) {
        contact.email = newEmail;
    }

    cout << "Contact updated successfully.\n";
}

void deleteContact(vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to delete.\n";
        return;
    }

    int index;
    cout << "Enter the contact number to delete: ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    cout << "Contact deleted successfully.\n";
}

void loadContacts(vector<Contact>& contacts, const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        // File does not exist, no contacts to load
        return;
    }

    Contact contact;
    while (getline(infile, contact.name)) {
        getline(infile, contact.phone);
        getline(infile, contact.email);
        contacts.push_back(contact);
    }

    infile.close();
}

void saveContacts(const vector<Contact>& contacts, const string& filename) {
    ofstream outfile(filename);
    for (const auto& contact : contacts) {
        outfile << contact.name << "\n";
        outfile << contact.phone << "\n";
        outfile << contact.email << "\n";
    }
    outfile.close();
}