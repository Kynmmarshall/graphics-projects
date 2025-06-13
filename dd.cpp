#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <graphics.h>
using namespace std;

class Book {
private:
    int bookID;
    string title;
    string author;
    bool isIssued;
    time_t issueTime;
    string borrowerName;
    string borrowerAddress;
    vector<string> borrowerHistory;

public:
    Book(int id, string title, string author)
        : bookID(id), title(title), author(author), isIssued(false), issueTime(0) {}

    Book() : bookID(0), isIssued(false), issueTime(0) {}

    int getID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isBookIssued() const { return isIssued; }

    void displayInfo(bool isManager = false) const {
        outtextxy(100, 100, ("Book ID   : " + to_string(bookID)).c_str());
        outtextxy(100, 120, ("Title     : " + title).c_str());
        outtextxy(100, 140, ("Author    : " + author).c_str());
        outtextxy(100, 160, ("Status    : " + string(isIssued ? "Issued" : "Available")).c_str());
        if (isManager && isIssued) {
            outtextxy(100, 180, ("Issued To : " + borrowerName + ", " + borrowerAddress).c_str());
            char timeStr[26];
            ctime_s(timeStr, sizeof(timeStr), &issueTime);
            outtextxy(100, 200, ("Issue Time: " + string(timeStr)).c_str());
        }
        if (isManager && !borrowerHistory.empty()) {
            outtextxy(100, 220, "Borrower History:");
            int y = 240;
            for (const auto& entry : borrowerHistory) {
                outtextxy(120, y, ("- " + entry).c_str());
                y += 20;
            }
        }
    }

    bool issue(string name, string address) {
        if (isIssued || name.empty() || address.empty()) return false;
        borrowerName = name;
        borrowerAddress = address;
        isIssued = true;
        issueTime = time(nullptr);
        char timeStr[26];
        ctime_s(timeStr, sizeof(timeStr), &issueTime);
        borrowerHistory.push_back("Issued to " + name + " (" + address + ") at " + string(timeStr));
        return true;
    }

    bool returnBook() {
        if (!isIssued) return false;
        time_t returnTime = time(nullptr);
        char timeStr[26];
        ctime_s(timeStr, sizeof(timeStr), &returnTime);
        borrowerHistory.push_back("Returned at " + string(timeStr));
        isIssued = false;
        issueTime = 0;
        borrowerName = "";
        borrowerAddress = "";
        return true;
    }

    bool isOverdue() const {
        if (!isIssued) return false;
        return difftime(time(nullptr), issueTime) > 7 * 24 * 60 * 60;
    }

    void save(ofstream& out) const {
        out << bookID << "|" << title << "|" << author << "|" << isIssued << "|"
            << issueTime << "|" << borrowerName << "|" << borrowerAddress << "|";
        out << borrowerHistory.size();
        for (const auto& history : borrowerHistory) {
            out << "|" << history;
        }
        out << "\n";
    }

    void load(const string& line) {
        istringstream iss(line);
        string token;
        getline(iss, token, '|'); bookID = stoi(token);
        getline(iss, title, '|');
        getline(iss, author, '|');
        getline(iss, token, '|'); isIssued = stoi(token);
        getline(iss, token, '|'); issueTime = stol(token);
        getline(iss, borrowerName, '|');
        getline(iss, borrowerAddress, '|');
        getline(iss, token, '|');
        int histSize = stoi(token);
        borrowerHistory.clear();
        for (int i = 0; i < histSize; ++i) {
            string entry;
            getline(iss, entry, '|');
            borrowerHistory.push_back(entry);
        }
    }
};

class Library {
private:
    vector<Book> books;

    bool isDuplicateID(int id) {
        for (auto& b : books) if (b.getID() == id) return true;
        return false;
    }

    bool isDuplicateTitle(const string& title) {
        for (auto& b : books) if (b.getTitle() == title) return true;
        return false;
    }

    void drawButton(int x, int y, int width, int height, const string& text) {
        setcolor(WHITE);
        rectangle(x, y, x + width, y + height);
        outtextxy(x + 10, y + height/2 - 5, text.c_str());
    }

    bool isButtonClicked(int x1, int y1, int x2, int y2) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            clearmouseclick(WM_LBUTTONDOWN);
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
        }
        return false;
    }

    void clearScreen() {
        cleardevice();
        setbkcolor(BLUE);
    }

    void showMessage(const string& msg) {
        clearScreen();
        outtextxy(100, 100, msg.c_str());
        delay(2000);
    }

    string getInput(int x, int y, int maxLen) {
        char* input = new char[maxLen + 1];
        int i = 0;
        while (true) {
            if (kbhit()) {
                char ch = getch();
                if (ch == 13) { // Enter key
                    input[i] = '\0';
                    break;
                } else if (ch == 8 && i > 0) { // Backspace
                    i--;
                    outtextxy(x + i * 8, y, " "); // Clear the character
                } else if (i < maxLen) {
                    input[i] = ch;
                    outtextxy(x + i * 8, y, &ch);
                    i++;
                }
            }
        }
        string result(input);
        delete[] input;
        return result;
    }

public:
    Library() {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, "");
        setbkcolor(BLUE);
        cleardevice();
    }

    ~Library() {
        closegraph();
    }

    void addBooks(int count) {
        clearScreen();
        for (int i = 0; i < count; ++i) {
            int id;
            string title, author;

            outtextxy(100, 100, ("Enter Book " + to_string(i + 1) + " details:").c_str());

            while (true) {
                outtextxy(100, 120, "Book ID: ");
                string idStr = getInput(180, 120, 20);
                id = stoi(idStr);
                if (isDuplicateID(id)) {
                    showMessage("Duplicate ID. Try again.");
                    continue;
                }
                break;
            }

            while (true) {
                outtextxy(100, 160, "Title: ");
                title = getInput(180, 160, 100);

                outtextxy(100, 200, "Author: ");
                author = getInput(180, 200, 100);

                if (isDuplicateTitle(title)) {
                    showMessage("Title exists. Try again.");
                    continue;
                }
                if (!title.empty() && !author.empty()) break;
                showMessage("Invalid input. Try again.");
            }

            books.emplace_back(id, title, author);
            showMessage("Book added successfully!");
        }
    }

    void deleteBook(int id) {
        clearScreen();
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getID() == id) {
                if (it->isBookIssued()) {
                    showMessage("Cannot delete. Book is currently issued.");
                    return;
                }
                books.erase(it);
                showMessage("Book deleted successfully.");
                return;
            }
        }
        showMessage("Book not found.");
    }

    void displayAllBooks(bool isManager = false) const {
        clearScreen();
        if (books.empty()) {
            showMessage("Library is empty.");
            return;
        }
        
        int y = 100;
        for (auto& book : books) {
            book.displayInfo(isManager);
            y += 250;
            if (y > getmaxy() - 100) {
                showMessage("Press any key to continue...");
                getch();
                y = 100;
                clearScreen();
            }
        }
        showMessage("Press any key to continue...");
        getch();
    }

    void issueBook(int id) {
        clearScreen();
        for (auto& book : books) {
            if (book.getID() == id) {
                if (book.isBookIssued()) {
                    showMessage("Book already issued.");
                    return;
                }
                
                outtextxy(100, 100, "Borrower's Name: ");
                string name = getInput(280, 100, 100);

                outtextxy(100, 140, "Borrower's Address: ");
                string address = getInput(280, 140, 200);

                if (book.issue(name, address)) {
                    showMessage("Book issued successfully!");
                } else {
                    showMessage("Issue failed.");
                }
                return;
            }
        }
        showMessage("Book not found.");
    }

    void returnBook(int id) {
        clearScreen();
        for (auto& book : books) {
            if (book.getID() == id) {
                if (book.returnBook()) {
                    showMessage("Book returned successfully!");
                } else {
                    showMessage("Book wasn't issued.");
                }
                return;
            }
        }
        showMessage("Book not found.");
    }

    void saveToFile() {
        ofstream out("library_data.txt");
        for (auto& book : books) book.save(out);
        out.close();
        showMessage("Library data saved.");
    }

    void loadFromFile() {
        ifstream in("library_data.txt");
        if (!in) {
            showMessage("No saved data found.");
            return;
        }
        string line;
        books.clear();
        while (getline(in, line)) {
            Book b;
            b.load(line);
            books.push_back(b);
        }
        in.close();
        showMessage("Library data loaded.");
    }

    void searchByTitle(const string& title) const {
        clearScreen();
        bool found = false;
        int y = 100;
        for (const auto& b : books) {
            if (b.getTitle().find(title) != string::npos) {
                b.displayInfo();
                y += 200;
                if (y > getmaxy() - 100) {
                    showMessage("Press any key to continue...");
                    getch();
                    y = 100;
                    clearScreen();
                }
                found = true;
            }
        }
        if (!found) showMessage("No matching title found.");
    }

    void searchByAuthor(const string& author) const {
        clearScreen();
        bool found = false;
        int y = 100;
        for (const auto& b : books) {
            if (b.getAuthor().find(author) != string::npos) {
                b.displayInfo();
                y += 200;
                if (y > getmaxy() - 100) {
                    showMessage("Press any key to continue...");
                    getch();
                    y = 100;
                    clearScreen();
                }
                found = true;
            }
        }
        if (!found) showMessage("No matching author found.");
    }

    void reportOverdueBooks() const {
        clearScreen();
        bool found = false;
        int y = 100;
        for (const auto& b : books) {
            if (b.isOverdue()) {
                b.displayInfo(true);
                y += 250;
                if (y > getmaxy() - 100) {
                    showMessage("Press any key to continue...");
                    getch();
                    y = 100;
                    clearScreen();
                }
                found = true;
            }
        }
        if (!found) showMessage("No overdue books.");
    }

    void managerAccess() {
        clearScreen();
        outtextxy(100, 100, "Enter manager code: ");
        string code = getInput(280, 100, 50);

        if (code == "Fahdil") {
            showMessage("Manager Access Granted.");
            displayAllBooks(true);
        } else {
            showMessage("Access Denied.");
        }
    }

    void mainMenu() {
        while (true) {
            clearScreen();
            outtextxy(100, 50, "--- Library Management System ---");
            
            // Draw buttons for each menu option
            drawButton(100, 100, 200, 40, "1. Add Books");
            drawButton(100, 150, 200, 40, "2. Display All Books");
            drawButton(100, 200, 200, 40, "3. Issue Book");
            drawButton(100, 250, 200, 40, "4. Return Book");
            drawButton(100, 300, 200, 40, "5. Save Library");
            drawButton(100, 350, 200, 40, "6. Load Library");
            drawButton(350, 100, 200, 40, "7. Search by Title");
            drawButton(350, 150, 200, 40, "8. Search by Author");
            drawButton(350, 200, 200, 40, "9. Report Overdue");
            drawButton(350, 250, 200, 40, "10. Delete Book");
            drawButton(350, 300, 200, 40, "11. Manager Access");
            drawButton(350, 350, 200, 40, "12. Exit");

            // Check for button clicks
            if (isButtonClicked(100, 100, 300, 140)) {
                clearScreen();
                outtextxy(100, 100, "Number of books to add: ");
                string countStr = getInput(300, 100, 10);
                addBooks(stoi(countStr));
            }
            else if (isButtonClicked(100, 150, 300, 190)) {
                displayAllBooks();
            }
            else if (isButtonClicked(100, 200, 300, 240)) {
                clearScreen();
                outtextxy(100, 100, "Enter Book ID to issue: ");
                string idStr = getInput(280, 100, 10);
                issueBook(stoi(idStr));
            }
            else if (isButtonClicked(100, 250, 300, 290)) {
                clearScreen();
                outtextxy(100, 100, "Enter Book ID to return: ");
                string idStr = getInput(280, 100, 10);
                returnBook(stoi(idStr));
            }
            else if (isButtonClicked(100, 300, 300, 340)) {
                saveToFile();
            }
            else if (isButtonClicked(100, 350, 300, 390)) {
                loadFromFile();
            }
            else if (isButtonClicked(350, 100, 550, 140)) {
                clearScreen();
                outtextxy(100, 100, "Enter title to search: ");
                string titleStr = getInput(280, 100, 100);
                searchByTitle(titleStr);
            }
            else if (isButtonClicked(350, 150, 550, 190)) {
                clearScreen();
                outtextxy(100, 100, "Enter author to search: ");
                string authorStr = getInput(280, 100, 100);
                searchByAuthor(authorStr);
            }
            else if (isButtonClicked(350, 200, 550, 240)) {
                reportOverdueBooks();
            }
            else if (isButtonClicked(350, 250, 550, 290)) {
                clearScreen();
                outtextxy(100, 100, "Enter Book ID to delete: ");
                string idStr = getInput(280, 100, 10);
                deleteBook(stoi(idStr));
            }
            else if (isButtonClicked(350, 300, 550, 340)) {
                managerAccess();
            }
            else if (isButtonClicked(350, 350, 550, 390)) {
                showMessage("Goodbye!");
                return;
            }
        }
    }
};

int main() {
    Library lib;
    lib.mainMenu();
    return 0;
}
