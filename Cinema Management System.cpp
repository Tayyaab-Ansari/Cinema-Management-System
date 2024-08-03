#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

string to_string(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

struct SeatNode {
    char row;
    int seatnum;
    bool isReserved;
    SeatNode* left;
    SeatNode* right;

    SeatNode(char r, int s) : row(r), seatnum(s), isReserved(false), left(NULL), right(NULL) {}
};

struct MovieNode {
    string name;
    string genre;
    string director;
    string duration;
    string timing;
    MovieNode* left;
    MovieNode* right;

    MovieNode(string n, string g, string d, string dur, string t)
        : name(n), genre(g), director(d), duration(dur), timing(t), left(NULL), right(NULL) {}
};

struct BookingNode {
    string name;
    int phone;
    string movieName;
    string seatLocation;
    string ticketType;
    BookingNode* left;
    BookingNode* right;

    BookingNode(string n, int p, string m, string s, string t)
        : name(n), phone(p), movieName(m), seatLocation(s), ticketType(t), left(NULL), right(NULL) {}
};

class SeatTree {
public:
    SeatNode* root;

    SeatTree() : root(NULL) {}

    SeatNode* insert(SeatNode* node, char row, int seatnum) {
        if (node == NULL) {
            return new SeatNode(row, seatnum);
        }
        if (row < node->row || (row == node->row && seatnum < node->seatnum)) {
            node->left = insert(node->left, row, seatnum);
        } else if (row > node->row || (row == node->row && seatnum > node->seatnum)) {
            node->right = insert(node->right, row, seatnum);
        }
        return node;
    }

    SeatNode* search(char row, int seatnum) {
        return search(root, row, seatnum);
    }

    SeatNode* search(SeatNode* node, char row, int seatnum) {
        if (node == NULL || (node->row == row && node->seatnum == seatnum)) {
            return node;
        }
        if (row < node->row || (row == node->row && seatnum < node->seatnum)) {
            return search(node->left, row, seatnum);
        } else {
            return search(node->right, row, seatnum);
        }
    }

   void inorder(SeatNode* node, int rowLength) {
    if (node == NULL) return;
    inorder(node->left, rowLength);

    // Output formatting for each seat
    cout << node->row << node->seatnum 
         << (node->isReserved ? " X" : " -");

    if (node->seatnum % rowLength == 0) {
        cout << endl; // New line after each row
    } else {
        cout << " | "; // Separator between seats
    }

    inorder(node->right, rowLength);
}

    void display() {
    int rowLength = 10; // Assuming each row has 10 seats
    inorder(root, rowLength);
    cout << endl;
}
};

class MovieTree {
public:
    MovieNode* root;

    MovieTree() : root(NULL) {}

    MovieNode* insert(MovieNode* node, string name, string genre, string director, string duration, string timing) {
        if (node == NULL) {
            return new MovieNode(name, genre, director, duration, timing);
        }
        if (name < node->name) {
            node->left = insert(node->left, name, genre, director, duration, timing);
        } else {
            node->right = insert(node->right, name, genre, director, duration, timing);
        }
        return node;
    }

    MovieNode* search(string name) {
        return search(root, name);
    }

    MovieNode* search(MovieNode* node, string name) {
        if (node == NULL || node->name == name) {
            return node;
        }
        if (name < node->name) {
            return search(node->left, name);
        } else {
            return search(node->right, name);
        }
    }

    void inorder(MovieNode* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << "**********************************************" << endl;
        cout << "| Movie Name       : " << node->name << endl;
        cout << "| Movie Genre      : " << node->genre << endl;
        cout << "| Movie Director   : " << node->director << endl;
        cout << "| Movie Duration   : " << node->duration << endl;
        cout << "| Movie Timing     : " << node->timing << endl;
        inorder(node->right);
    }

    void display() {
        inorder(root);
        cout << "**********************************************" << endl;
    }
};

class BookingTree {
public:
    BookingNode* root;

    BookingTree() : root(NULL) {}

    BookingNode* insert(BookingNode* node, string name, int phone, string movieName, string seatLocation, string ticketType) {
        if (node == NULL) {
            return new BookingNode(name, phone, movieName, seatLocation, ticketType);
        }
        if (name < node->name || (name == node->name && phone < node->phone)) {
            node->left = insert(node->left, name, phone, movieName, seatLocation, ticketType);
        } else {
            node->right = insert(node->right, name, phone, movieName, seatLocation, ticketType);
        }
        return node;
    }

    void inorder(BookingNode* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << "Name           : " << node->name << endl;
        cout << "Phone Number   : " << node->phone << endl;
        cout << "Movie          : " << node->movieName << endl;
        cout << "Seat Location  : " << node->seatLocation << endl;
        cout << "Ticket Type    : " << node->ticketType << endl;
        cout << endl;
        inorder(node->right);
    }

    void display() {
        if (root == NULL) {
            cout << "No Booking right now" << endl;
        } else {
            inorder(root);
        }
    }
};

class Seats {
public:
    SeatTree seatTree;
    MovieTree movieTree;
    BookingTree bookingTree;
    int movie_count;

    Seats() : movie_count(0) {
        // Initialize with 3 movies
        add_movie("Avengers: Endgame", "Action/Sci-Fi", "Anthony and Joe Russo", "3 hours 2 mins", "09:00");
        add_movie("Batman Begins", "Action/Adventure", "Christopher Nolan", "2 hours 20 mins", "12:00");
        add_movie("Demon Slayer: Mugen Train", "Animation/Action", "Haruo Sotozaki", "1 hour 57 mins", "15:00");

        // Initialize seat tree with 5 rows and 10 seats each
        for (char row = 'A'; row <= 'E'; row++) {
            for (int seatnum = 1; seatnum <= 10; seatnum++) {
                seatTree.root = seatTree.insert(seatTree.root, row, seatnum);
            }
        }
    }

    void add_movie(string name, string genre, string director, string duration, string timing) {
        movieTree.root = movieTree.insert(movieTree.root, name, genre, director, duration, timing);
        movie_count++;
    }

    void display_seats() {
        seatTree.display();
    }

    void display_movies() {
        if (movie_count == 0) {
            cout << "No movies available" << endl;
        } else {
            movieTree.display();
        }
    }

    void reserve_seat() {
        char row;
        int seatnum;
        int numAdult, numStudent, numChildren;

        // Ask for the name and phone number only once
        string bookingName;
        int bookingPhone;
        cout << "Enter Your name :" << endl;
        cin.ignore();
        getline(cin, bookingName);
        cout << "Enter your Phone number" << endl;
        cin >> bookingPhone;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter a valid phone number." << endl;
            return;
        }

        cout << "Following are the available Movies :" << endl;
        display_movies();

        cout << "Enter the name of the movie you want to watch:" << endl;
        string movieName;
        cin.ignore();
        getline(cin, movieName);

        MovieNode* movie = movieTree.search(movieName);
        if (movie == NULL) {
            cout << "Invalid movie selection." << endl;
            return;
        }

        cout << "Enter the number of Adult tickets you want: ";
        cin >> numAdult;
        cout << "Enter the number of Student tickets you want: ";
        cin >> numStudent;
        cout << "Enter the number of Children tickets you want: ";
        cin >> numChildren;

        int totalSeats = numAdult + numStudent + numChildren;

        cout << "Following are the available seats" << endl;
        display_seats();

        for (int i = 0; i < totalSeats; i++) {
            cout << "Enter the Row (A-E) for seat " << i + 1 << ": ";
            cin >> row;
            cout << "Enter the seat number (1-10) for seat " << i + 1 << ": ";
            cin >> seatnum;

            SeatNode* seat = seatTree.search(row, seatnum);
            if (seat == NULL || seat->isReserved) {
                cout << "Invalid or already reserved seat selection." << endl;
                i--;
                continue;
            }
            seat->isReserved = true;
            cout << "Seat reserved successfully.(" << row << "," << seatnum << ")" << endl;

            string seatLocation = string(1, row) + to_string(seatnum);
            string ticketType;
            if (i < numAdult)
                ticketType = "Adult";
            else if (i < numAdult + numStudent)
                ticketType = "Student";
            else
                ticketType = "Children";

            bookingTree.root = bookingTree.insert(bookingTree.root, bookingName, bookingPhone, movieName, seatLocation, ticketType);
        }

        int totalPrice = (numAdult * 500) + (numStudent * 300) + (numChildren * 100);
        cout << "Total price for the tickets is: " << totalPrice << " rupees." << endl;
    }

    void display_bookings() {
        bookingTree.display();
    }

    void add_new_movies() {
        string m_name, genre, d_name, duration, timing;
        if (movie_count >= 10) {
            cout << "You have entered the maximum number of movies." << endl;
        } else {
            cout << "Enter the name of Movie: ";
            cin.ignore();
            getline(cin, m_name);

            cout << "Enter the genre of movie: ";
            getline(cin, genre);

            cout << "Enter the name of director: ";
            getline(cin, d_name);

            cout << "Enter the duration of movie (2 hours 37 mins): ";
            getline(cin, duration);

            cout << "Enter the timing of movie (HH:MM): ";
            getline(cin, timing);

            add_movie(m_name, genre, d_name, duration, timing);
            cout << "Your movie \"" << m_name << "\" has been added successfully." << endl;
        }
    }

    int get_movie_count() {
        return movie_count;
    }
};

void ticketprice() {
    int n;
    cout << "Which Ticket Do you want? \n 1-Adult\n 2-Student\n 3-Children\n";
    cin >> n;
    if (n == 1) {
        cout << "The price of Adult ticket is 500" << endl;
    } else if (n == 2) {
        cout << "The price of Student ticket is 300" << endl;
    } else if (n == 3) {
        cout << "The price of Children ticket is 100" << endl;
    }
}
void show_timings_recursive(MovieNode* node);
void show_timings(Seats &s) {
    cout << setw(30) << left << "Movie Name" << setw(15) << left << "Timings" << endl;
    show_timings_recursive(s.movieTree.root);
}

void show_timings_recursive(MovieNode* node) {
    if (node == NULL) {
        return;
    }

    // In-order traversal to display movies in sorted order
    show_timings_recursive(node->left);
    cout << setw(30) << left << node->name << setw(15) << left << node->timing << endl;
    show_timings_recursive(node->right);
}



int main() {
    Seats s;
    int ch, t = 1;
    while (t != 0) {
        cout << "\n1-For Booking Tickets" << endl;
        cout << "\n2-For Adding New Movies" << endl;
        cout << "\n3-Showing All Available movies" << endl;
        cout << "\n4-Showing Your Bookings" << endl;
        cout << "\n5-Showing Price of tickets" << endl;
        cout << "\n6-Showing Movies Timings" << endl;
        cout << "\n7-Available Seats" << endl;
        cout << "\n8-Exit" << endl;
        cin >> ch;
        if (ch == 1) {
            system("cls");
            s.reserve_seat();
        } else if (ch == 2) {
            system("cls");
            s.add_new_movies();
        } else if (ch == 3) {
            system("cls");
            s.display_movies();
        } else if (ch == 4) {
            system("cls");
            s.display_bookings();
        } else if (ch == 5) {
            system("cls");
            ticketprice();
        } else if (ch == 6) {
            system("cls");
            show_timings(s);
        } else if (ch == 7) {
            system("cls");
            s.display_seats();
            cout << endl;
        } else if (ch == 8) {
            t = 0;
        } else {
            system("cls");
            cout << "Invalid Input (1-8)" << endl;
        }
    }
    return 0;
}

