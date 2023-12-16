#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Book {
public:
    string title;
    string author;
    bool available;

    Book(const string& t, const string& a) : title(t), author(a), available(true) {}
};

class User {
public:
    string username;
    vector<Book*> borrowedBooks;

    User(const string& u) : username(u) {}
};

class Library {
private:
    vector<Book> books;
    vector<User> users;

public:
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title, author));
    }

    void addUser(const string& username) {
        users.push_back(User(username));
    }

    void displayBooks() const {
        cout << "Library Books:\n";
        for (const auto& book : books) {
            cout << "Title: " << book.title << ", Author: " << book.author
                 << ", Available: " << (book.available ? "Yes" : "No") << "\n";
        }
    }

    void displayUsers() const {
        cout << "Library Users:\n";
        for (const auto& user : users) {
            cout << "Username: " << user.username << "\n";
        }
    }

    Book* findBook(const string& title) {
        auto it = find_if(books.begin(), books.end(), [&title](const Book& b) {
            return b.title == title;
        });
        return (it != books.end()) ? &(*it) : nullptr;
    }

    User* findUser(const string& username) {
        auto it = find_if(users.begin(), users.end(), [&username](const User& u) {
            return u.username == username;
        });
        return (it != users.end()) ? &(*it) : nullptr;
    }

    void borrowBook(const string& username, const string& title) {
        User* user = findUser(username);
        Book* book = findBook(title);

        if (user && book && book->available) {
            user->borrowedBooks.push_back(book);
            book->available = false;
            cout << "Book '" << title << "' has been borrowed by " << username << ".\n";
        } else {
            cout << "Book not available or user not found.\n";
        }
    }

    void returnBook(const string& username, const string& title) {
        User* user = findUser(username);
        Book* book = findBook(title);

        if (user && book && !book->available) {
            auto it = find(user->borrowedBooks.begin(), user->borrowedBooks.end(), book);
            if (it != user->borrowedBooks.end()) {
                user->borrowedBooks.erase(it);
                book->available = true;
                cout << "Book '" << title << "' has been returned by " << username << ".\n";
            } else {
                cout << "User has not borrowed this book.\n";
            }
        } else {
            cout << "Book not found or already available.\n";
        }
    }
};

int main() {
    Library library;

    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Add User\n";
        cout << "3. Display Books\n";
        cout << "4. Display Users\n";
        cout << "5. Borrow Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author;
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                library.addBook(title, author);
                break;
            }
            case 2: {
                string username;
                cout << "Enter username: ";
                cin.ignore();
                getline(cin, username);
                library.addUser(username);
                break;
            }
            case 3:
                library.displayBooks();
                break;
            case 4:
                library.displayUsers();
                break;
            case 5: {
                string username, title;
                cout << "Enter username: ";
                cin.ignore();
                getline(cin, username);
                cout << "Enter book title: ";
                getline(cin, title);
                library.borrowBook(username, title);
                break;
            }
            case 6: {
                string username, title;
                cout << "Enter username: ";
                cin.ignore();
                getline(cin, username);
                cout << "Enter book title: ";
                getline(cin, title);
                library.returnBook(username, title);
                break;
            }
            case 7:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 7);

    return 0;
}
