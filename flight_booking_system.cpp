/*
 * ============================================================
 *  Flight Booking System
 *  Language : C++17
 *  File     : flight_booking_system.cpp
 *  Features : Book/cancel flights, view available flights,
 *             manage passengers – classes, vectors, file I/O
 * ============================================================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <ctime>
#include <string>

using namespace std;

// ─────────────────────────────────────────────
//  Utilities
// ─────────────────────────────────────────────
static string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    return (a == string::npos) ? "" : s.substr(a, b - a + 1);
}

static string timestamp() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", localtime(&now));
    return buf;
}

// ─────────────────────────────────────────────
//  Class: Passenger
// ─────────────────────────────────────────────
class Passenger {
public:
    string name;
    int    age;
    string passport;   // passport / CNIC number
    string gender;     // M / F / O

    Passenger() : age(0) {}
    Passenger(const string& n, int a, const string& pp, const string& g)
        : name(n), age(a), passport(pp), gender(g) {}

    string toCSV() const {
        return name + "~" + to_string(age) + "~" + passport + "~" + gender;
    }

    static Passenger fromCSV(const string& s) {
        istringstream ss(s);
        string tok;
        Passenger p;
        getline(ss, tok, '~'); p.name     = trim(tok);
        getline(ss, tok, '~'); p.age      = stoi(tok);
        getline(ss, tok, '~'); p.passport = trim(tok);
        getline(ss, tok, '~'); p.gender   = trim(tok);
        return p;
    }

    void print() const {
        cout << left
             << setw(22) << name
             << setw(6)  << age
             << setw(18) << passport
             << gender   << "\n";
    }
};

// ─────────────────────────────────────────────
//  Class: Flight
// ─────────────────────────────────────────────
class Flight {
public:
    string flightNo;
    string airline;
    string origin;
    string destination;
    string departDate;    // YYYY-MM-DD
    string departTime;
    string arrivalTime;
    int    totalSeats;
    double economyFare;
    double businessFare;
    vector<Passenger> economy;    // booked passengers
    vector<Passenger> business;

    Flight() : totalSeats(0), economyFare(0), businessFare(0) {}

    Flight(const string& no, const string& air, const string& orig,
           const string& dest, const string& date, const string& dep,
           const string& arr, int seats, double eco, double biz)
        : flightNo(no), airline(air), origin(orig), destination(dest),
          departDate(date), departTime(dep), arrivalTime(arr),
          totalSeats(seats), economyFare(eco), businessFare(biz) {}

    int economyAvail()  const { return totalSeats     - (int)economy.size();  }
    int businessAvail() const { return totalSeats / 5 - (int)business.size(); } // biz = 20%

    // ── Short listing ──
    void display() const {
        cout << left
             << setw(9)  << flightNo
             << setw(16) << airline
             << setw(14) << origin
             << setw(14) << destination
             << setw(12) << departDate
             << setw(7)  << departTime
             << right
             << setw(10) << economyFare
             << setw(10) << businessFare
             << setw(6)  << economyAvail()
             << setw(6)  << businessAvail()
             << "\n";
    }

    // Serialise flight header (no passengers)
    string headerCSV() const {
        return flightNo + "|" + airline + "|" + origin + "|" + destination + "|"
             + departDate + "|" + departTime + "|" + arrivalTime + "|"
             + to_string(totalSeats) + "|"
             + to_string(economyFare)  + "|"
             + to_string(businessFare);
    }
};

// ─────────────────────────────────────────────
//  Class: Booking
// ─────────────────────────────────────────────
class Booking {
public:
    string bookingRef;
    string flightNo;
    string cabin;         // Economy / Business
    string passengerName;
    string passport;
    double fare;
    string bookedAt;

    Booking() : fare(0) {}

    Booking(const string& ref, const string& fno, const string& cab,
            const string& name, const string& pp, double fare)
        : bookingRef(ref), flightNo(fno), cabin(cab),
          passengerName(name), passport(pp), fare(fare) {
        bookedAt = timestamp();
    }

    string toCSV() const {
        return bookingRef + "|" + flightNo  + "|" + cabin + "|"
             + passengerName + "|" + passport + "|"
             + to_string(fare) + "|" + bookedAt;
    }

    static Booking fromCSV(const string& line) {
        istringstream ss(line);
        string tok;
        Booking b;
        getline(ss, tok, '|'); b.bookingRef    = trim(tok);
        getline(ss, tok, '|'); b.flightNo      = trim(tok);
        getline(ss, tok, '|'); b.cabin         = trim(tok);
        getline(ss, tok, '|'); b.passengerName = trim(tok);
        getline(ss, tok, '|'); b.passport      = trim(tok);
        getline(ss, tok, '|'); b.fare          = stod(tok);
        getline(ss, tok, '|'); b.bookedAt      = trim(tok);
        return b;
    }

    void printTicket(const Flight& f) const {
        cout << "\n" << string(56, '=') << "\n";
        cout << "          BOARDING PASS / E-TICKET\n";
        cout << string(56, '=') << "\n";
        cout << " Booking Ref  : " << bookingRef    << "\n";
        cout << " Flight       : " << flightNo  << "  (" << f.airline << ")\n";
        cout << " Route        : " << f.origin   << " → " << f.destination << "\n";
        cout << " Date         : " << f.departDate << "  Dep: " << f.departTime
             << "  Arr: " << f.arrivalTime << "\n";
        cout << " Cabin        : " << cabin          << "\n";
        cout << " Passenger    : " << passengerName  << "\n";
        cout << " Passport/ID  : " << passport       << "\n";
        cout << " Fare         : Rs. " << fixed << setprecision(2) << fare << "\n";
        cout << " Booked At    : " << bookedAt       << "\n";
        cout << string(56, '=') << "\n\n";
    }
};

// ─────────────────────────────────────────────
//  Class: FlightBookingSystem  –  main app
// ─────────────────────────────────────────────
class FlightBookingSystem {
private:
    vector<Flight>  flights;
    vector<Booking> bookings;
    int             refSeed = 2000;

    const string flightFile  = "flights.dat";
    const string bookingFile = "bookings.dat";

    // ── Generate unique booking ref ──
    string genRef() { return "BK" + to_string(++refSeed); }

    // ── Load bookings from file ──
    void loadBookings() {
        ifstream f(bookingFile);
        if (!f.is_open()) return;
        string line;
        getline(f, line);  // header
        while (getline(f, line)) {
            if (trim(line).empty()) continue;
            try {
                Booking b = Booking::fromCSV(line);
                bookings.push_back(b);
                if (b.bookingRef.size() > 2) {
                    int seed = stoi(b.bookingRef.substr(2));
                    if (seed >= refSeed) refSeed = seed + 1;
                }
            } catch (...) {}
        }

        // Rebuild passenger lists in flights from bookings
        for (const auto& b : bookings) {
            for (auto& fl : flights) {
                if (fl.flightNo == b.flightNo) {
                    Passenger p(b.passengerName, 0, b.passport, "");
                    if (b.cabin == "Business") fl.business.push_back(p);
                    else                       fl.economy.push_back(p);
                    break;
                }
            }
        }
    }

    // ── Save bookings to file ──
    void saveBookings() const {
        ofstream f(bookingFile);
        f << "BookingRef|FlightNo|Cabin|Passenger|Passport|Fare|BookedAt\n";
        for (const auto& b : bookings) f << b.toCSV() << "\n";
    }

    // ── Seed default flights ──
    void initFlights() {
        flights.emplace_back("PK301", "PIA",          "Karachi",   "Lahore",    "2026-07-10", "08:00", "09:30", 150,  9500,  25000);
        flights.emplace_back("PK302", "PIA",          "Lahore",    "Karachi",   "2026-07-10", "12:00", "13:30", 150,  9500,  25000);
        flights.emplace_back("AP501", "AirBlue",      "Islamabad", "Karachi",   "2026-07-11", "07:30", "09:10", 120,  8800,  22000);
        flights.emplace_back("AP502", "AirBlue",      "Karachi",   "Islamabad", "2026-07-11", "14:00", "15:40", 120,  8800,  22000);
        flights.emplace_back("SV101", "SereneAir",    "Lahore",    "Peshawar",  "2026-07-12", "09:15", "10:05", 100,  6500,  18000);
        flights.emplace_back("PK401", "PIA",          "Karachi",   "Quetta",    "2026-07-13", "06:00", "07:20", 80,   7200,  19000);
        flights.emplace_back("EK901", "Emirates",     "Karachi",   "Dubai",     "2026-07-14", "02:00", "04:20", 300, 35000, 110000);
        flights.emplace_back("TK501", "Turkish Air",  "Islamabad", "Istanbul",  "2026-07-15", "23:00", "05:30", 250, 55000, 160000);
    }

    // ── Find flight by number ──
    Flight* findFlight(const string& no) {
        for (auto& f : flights)
            if (f.flightNo == no) return &f;
        return nullptr;
    }

    // ── Print flight table header ──
    void printFlightHeader() const {
        cout << "\n" << string(98, '-') << "\n";
        cout << left
             << setw(9)  << "Flight"
             << setw(16) << "Airline"
             << setw(14) << "From"
             << setw(14) << "To"
             << setw(12) << "Date"
             << setw(7)  << "Dep"
             << right
             << setw(10) << "EcoFare"
             << setw(10) << "BizFare"
             << setw(6)  << "Eco"
             << setw(6)  << "Biz"
             << "\n";
        cout << string(98, '-') << "\n";
    }

    // ── Search flights by route ──
    void searchFlights() {
        cout << "\nFrom (city): "; string from; getline(cin, from);
        cout << "To   (city): "; string to;   getline(cin, to);

        transform(from.begin(), from.end(), from.begin(), ::tolower);
        transform(to.begin(),   to.end(),   to.begin(),   ::tolower);

        bool found = false;
        printFlightHeader();
        for (const auto& f : flights) {
            string orig = f.origin,  dest = f.destination;
            transform(orig.begin(), orig.end(), orig.begin(), ::tolower);
            transform(dest.begin(), dest.end(), dest.begin(), ::tolower);
            if (orig.find(from) != string::npos && dest.find(to) != string::npos) {
                f.display(); found = true;
            }
        }
        if (!found) cout << "No flights found for that route.\n";
        cout << string(98, '-') << "\n";
    }

    // ── View all flights ──
    void viewAllFlights() {
        printFlightHeader();
        for (const auto& f : flights) f.display();
        cout << string(98, '-') << "\n";
    }

    // ── Book a ticket ──
    void bookTicket() {
        viewAllFlights();
        cout << "\nEnter Flight Number: "; string fno; getline(cin, fno);
        Flight* fl = findFlight(trim(fno));
        if (!fl) { cout << "Flight not found.\n"; return; }

        // Choose cabin
        cout << "Cabin (1=Economy Rs." << fl->economyFare
             << " / 2=Business Rs." << fl->businessFare << "): ";
        int cabin; cin >> cabin;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (cabin != 1 && cabin != 2) { cout << "Invalid cabin.\n"; return; }

        bool isEco = (cabin == 1);
        if (isEco  && fl->economyAvail()  <= 0) { cout << "Economy full.\n";  return; }
        if (!isEco && fl->businessAvail() <= 0) { cout << "Business full.\n"; return; }

        // Passenger details
        string name, pp, gender;
        int age = 0;
        cout << "Passenger name      : "; getline(cin, name);
        cout << "Age                 : ";
        while (!(cin >> age) || age <= 0) { cin.clear(); cin.ignore(1000,'\n'); }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Passport/CNIC       : "; getline(cin, pp);
        cout << "Gender (M/F/O)      : "; getline(cin, gender);

        Passenger p(trim(name), age, trim(pp), trim(gender));
        if (isEco) fl->economy.push_back(p);
        else       fl->business.push_back(p);

        double fare = isEco ? fl->economyFare : fl->businessFare;
        string ref  = genRef();
        Booking b(ref, fl->flightNo, isEco ? "Economy" : "Business",
                  p.name, p.passport, fare);
        bookings.push_back(b);
        saveBookings();
        b.printTicket(*fl);
    }

    // ── Cancel booking ──
    void cancelBooking() {
        cout << "\nEnter Booking Reference: "; string ref; getline(cin, ref);
        ref = trim(ref);

        auto it = find_if(bookings.begin(), bookings.end(),
                          [&ref](const Booking& b){ return b.bookingRef == ref; });
        if (it == bookings.end()) { cout << "Booking not found.\n"; return; }

        // Remove from flight passenger list
        Flight* fl = findFlight(it->flightNo);
        if (fl) {
            auto removeP = [&](vector<Passenger>& v) {
                v.erase(remove_if(v.begin(), v.end(),
                    [&](const Passenger& p){ return p.passport == it->passport; }), v.end());
            };
            if (it->cabin == "Business") removeP(fl->business);
            else                         removeP(fl->economy);
        }

        cout << "Cancel booking " << ref << " for " << it->passengerName << "? (y/n): ";
        char c; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (tolower(c) != 'y') { cout << "Cancelled.\n"; return; }

        bookings.erase(it);
        saveBookings();
        cout << "✓ Booking " << ref << " cancelled. Refund will be processed.\n";
    }

    // ── View passenger manifest for a flight ──
    void viewManifest() {
        cout << "\nEnter Flight Number: "; string fno; getline(cin, fno);
        Flight* fl = findFlight(trim(fno));
        if (!fl) { cout << "Flight not found.\n"; return; }

        cout << "\n=== Passenger Manifest: " << fl->flightNo
             << " (" << fl->origin << " → " << fl->destination << ") ===\n";

        auto printPassList = [](const string& label, const vector<Passenger>& v) {
            cout << "\n[ " << label << " ]\n";
            cout << string(60, '-') << "\n";
            cout << left << setw(22) << "Name" << setw(6) << "Age"
                 << setw(18) << "Passport/ID" << "Gender\n";
            cout << string(60, '-') << "\n";
            if (v.empty()) { cout << "  (no passengers)\n"; return; }
            for (const auto& p : v) p.print();
        };

        printPassList("Business Class", fl->business);
        printPassList("Economy Class",  fl->economy);
        cout << "\nTotal on board: " << fl->economy.size() + fl->business.size() << "\n";
    }

    // ── View my bookings by passenger name ──
    void viewMyBookings() {
        cout << "\nEnter passenger name to search: "; string name; getline(cin, name);
        string kw = name;
        transform(kw.begin(), kw.end(), kw.begin(), ::tolower);

        bool found = false;
        cout << "\n" << string(70, '-') << "\n";
        cout << left << setw(12) << "Ref" << setw(10) << "Flight"
             << setw(22) << "Passenger" << setw(12) << "Cabin"
             << right << setw(10) << "Fare" << "\n";
        cout << string(70, '-') << "\n";
        for (const auto& b : bookings) {
            string n = b.passengerName;
            transform(n.begin(), n.end(), n.begin(), ::tolower);
            if (n.find(kw) != string::npos) {
                cout << left << setw(12) << b.bookingRef
                     << setw(10) << b.flightNo
                     << setw(22) << b.passengerName
                     << setw(12) << b.cabin
                     << right << setw(10) << fixed << setprecision(2) << b.fare << "\n";
                found = true;
            }
        }
        if (!found) cout << "No bookings found.\n";
        cout << string(70, '-') << "\n";
    }

    // ── Revenue report ──
    void revenueReport() const {
        map<string, double> rev;
        double grand = 0;
        for (const auto& b : bookings) { rev[b.flightNo] += b.fare; grand += b.fare; }

        cout << "\n--- Revenue Report ---\n";
        cout << left << setw(12) << "Flight" << right << setw(14) << "Revenue(Rs)\n";
        cout << string(26, '-') << "\n";
        for (const auto& [fno, r] : rev)
            cout << left << setw(12) << fno << right << setw(14)
                 << fixed << setprecision(2) << r << "\n";
        cout << string(26, '-') << "\n";
        cout << left << setw(12) << "Total" << right << setw(14)
             << fixed << setprecision(2) << grand << "\n\n";
    }

public:
    FlightBookingSystem() {
        initFlights();
        loadBookings();
    }

    void run() {
        int choice;
        do {
            cout << "\n╔══════════════════════════════════╗\n";
            cout <<   "║    Flight Booking System         ║\n";
            cout <<   "╠══════════════════════════════════╣\n";
            cout <<   "║  1. View All Flights             ║\n";
            cout <<   "║  2. Search Flights (by Route)    ║\n";
            cout <<   "║  3. Book a Ticket                ║\n";
            cout <<   "║  4. Cancel a Booking             ║\n";
            cout <<   "║  5. View Passenger Manifest      ║\n";
            cout <<   "║  6. My Bookings (by Name)        ║\n";
            cout <<   "║  7. Revenue Report               ║\n";
            cout <<   "║  8. Exit                         ║\n";
            cout <<   "╚══════════════════════════════════╝\n";
            cout << "Choose: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = 0;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            switch (choice) {
                case 1: viewAllFlights();  break;
                case 2: searchFlights();   break;
                case 3: bookTicket();      break;
                case 4: cancelBooking();   break;
                case 5: viewManifest();    break;
                case 6: viewMyBookings();  break;
                case 7: revenueReport();   break;
                case 8: cout << "Thank you for using Flight Booking System!\n"; break;
                default: cout << "Invalid option.\n";
            }
        } while (choice != 8);
    }
};

// ─────────────────────────────────────────────
//  Entry point
// ─────────────────────────────────────────────
int main() {
    FlightBookingSystem app;
    app.run();
    return 0;
}
