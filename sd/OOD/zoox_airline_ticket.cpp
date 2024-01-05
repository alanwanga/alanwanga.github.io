// #include <sstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

using namespace std;

namespace Airfare {

enum class Seat { economy, premium, business };
enum class Airline { delta, united, southwest, luigiair };

unordered_map<string, Seat> seats {
  {"Economy", Seat::economy},
  {"Premium", Seat::premium},
  {"Business", Seat::business}
};
unordered_map<string, Airline> airlines {
  {"Delta", Airline::delta},
  {"United", Airline::united},
  {"Southwest", Airline::southwest},
  {"LuigiAir", Airline::luigiair}
};

// Command interface
class TicketCommand {
public:
    virtual double execute(const double miles, const Seat seat_class) = 0;
    virtual ~TicketCommand() = default;

protected:
    virtual double getOpCost(const double miles, const Seat seat_class) {
      switch (seat_class)
      {
        case Seat::economy:
          return getEconomyOpCost(miles);
        case Seat::premium:
          return getPremiumOpCost(miles);
        case Seat::business:
          return getBusinessOpCost(miles);
        default:
          return 0; // or handle other cases as needed
      }
    }
    virtual double getEconomyOpCost (double miles) {
      return 0;
    }
    virtual double getPremiumOpCost (double miles) {
      return 25;
    }
    virtual double getBusinessOpCost (double miles) {
      return 50 + 0.25 * miles;
    }
};

// Command classes
class DeltaCommand : public TicketCommand {
public:
    double execute(const double miles, Seat seating_class) override {
        return 0.5 * miles + getOpCost(miles, seating_class);
    }
};

class UnitedCommand : public TicketCommand {
public:
    double execute(const double miles, Seat seating_class) override {
        return 0.75 * miles + getOpCost(miles, seating_class);
    }
protected:
    double getPremiumOpCost (double miles) override {
      return 25 + 0.1 * miles;
    }
};

class SouthwestCommand : public TicketCommand {
public:
    double execute(const double miles, const Seat seating_class) override {
        return 1 * miles;
    }
};

class LuigiAirCommand : public TicketCommand {
public:
    double execute(const double miles, const Seat seat_class) override {
        return max(100., 2 * getOpCost(miles, seat_class));
    }
};

// Invoker class
class TicketCalculator {
public:
    void setCommand(const Airline airline, unique_ptr<TicketCommand> command) {
        commands[airline] = move(command);
    }

    double calculateTicketCost(const Airline airline, const double miles, const Seat seat_class) {
      return commands[airline]->execute(miles, seat_class);
    }

private:
    unordered_map<const Airline, unique_ptr<TicketCommand>> commands;
};

void processData(vector<vector<string>>& tickets) {
    TicketCalculator calculator;

    calculator.setCommand(Airline::delta, make_unique<Airfare::DeltaCommand>());
    calculator.setCommand(Airline::united, make_unique<Airfare::UnitedCommand>());
    calculator.setCommand(Airline::southwest, make_unique<Airfare::SouthwestCommand>());
    calculator.setCommand(Airline::luigiair, make_unique<Airfare::LuigiAirCommand>());

    for (const vector<string>& ticket : tickets) {
        // istringstream iss(ticket);
        // string airline, seat_class;
        // double miles;

        // iss >> airline >> miles >> seat_class;

        // if (!airlines.count(airline) || !miles || !seats.count(seat_class)) {
        //   cerr <<  "invalid" << endl;
        //   continue;
        // }
        if (ticket.size() != 3) {
          cerr << "invalid input format" << endl;
          continue;
        }

        string airline = ticket[0];
        string seat_class = ticket[2];
        double miles;
        try {
          miles = stod(ticket[1]);
        } catch(const exception& e) {
          cerr << "invalid distance" << endl;
          continue;
        }
        if (!seats.count(seat_class)) {
          cerr << "invalid seat class" << endl;
          continue;
        }
        if (!airlines.count(airline)) {
          cerr << "invalid airline" << endl;
          continue;
        }
        double cost = calculator.calculateTicketCost(airlines[airline], miles, seats[seat_class]);
        cout << airline << ": $" << cost << endl;
    }
}

}

int main() {
    vector<vector<string>> tickets = {
      {"United", "150", "Premium"},
      {"Delta", "60", "Business"},
      {"Southwest", "1000", "Economy"},
      {"LuigiAir", "50", "Business"},
      // invalid input
      {"United", "", "Premium"},
      {"Deltaa", "60", "Business"},
      {"Southwest", "1000", "Economyy"},
      {"LuigiAir", "xx", "Business"},
    };

    Airfare::processData(tickets);

    return 0;
}
