#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

using namespace std;

namespace Simulator {

enum class Coaster { wooden, steel, suspended };
enum class Lift { cable, chain, lanuched };

unordered_map<string, Coaster> coasters {
  { "Wooden", Coaster::wooden },
  { "Steel", Coaster::steel },
  { "Suspended", Coaster::suspended },
};
unordered_map<string, Lift> lifts {
  { "Cable", Lift::cable },
  { "Chain", Lift::chain },
  { "lanuched", Lift::lanuched },
};

// Command interface
class CoasterCommand {
public:
  virtual double execute(const double max_speed, const double bumps_per_sec, const Lift lift_type) = 0;
  virtual ~CoasterCommand() = default;

protected:
  virtual double getComfortScore(const double max_speed, const double bumps_per_sec, const Lift lift_type) {
    return min(1., min(1 / bumps_per_sec, 1 / max_speed));
  }
  virtual double getOverallScore(const double max_speed, const double bumps_per_sec, const Lift lift_type, const double scale_facter) {
    return scale_facter * getComfortScore(max_speed, bumps_per_sec, lift_type) * max_speed;
  }
};

class WoodenCoasterCommand : public CoasterCommand {
public:
  double execute(const double max_speed, const double bumps_per_sec, const Lift lift_type) override {
    return getOverallScore(max_speed, bumps_per_sec, lift_type, scale_factor);
  }
private:
  const double scale_factor = 1;
};

class SteelCoasterCommand : public CoasterCommand {
public:
  double execute(const double max_speed, const double bumps_per_sec, Lift lift_type) override {
    return getOverallScore(max_speed, bumps_per_sec, lift_type, scale_factor);
  }
protected:
  double getComfortScore(const double max_speed, const double bumps_per_sec, Lift lift_type) override {
    return min(1., min(1 / bumps_per_sec, 5 / max_speed));
  }
private:
  const double scale_factor = 2;
};

class SuspendedCoasterCommand : public CoasterCommand {
public: 
  double execute(const double max_speed, const double bumps_per_sec, const Lift lift_type) override {
    return getOverallScore(max_speed, bumps_per_sec, lift_type, scale_factor);
  }
  double getComfortScore(const double max_speed, const double bumps_per_sec, const Lift lift_type) override {
    double additional_comfort = lift_type == Lift::cable ? 0.5 : 0;
    return min(1., min(1 / bumps_per_sec, 1 / max_speed)) + additional_comfort;
  }
private:
  const double scale_factor = 0.5;
};

// Invoker class
class ScoreCalculator {
public:
    void setCommand(Coaster coaster_type, unique_ptr<CoasterCommand> coaster_command) {
      commands[coaster_type] = move(coaster_command);
    }

    double calculateScore(const Coaster coaster_type, const double max_speed, const double bumps_per_sec, const Lift lift_type) {
        return commands[coaster_type]->execute(max_speed, bumps_per_sec, lift_type);
    }

private:
  unordered_map<Coaster, unique_ptr<CoasterCommand>> commands;
};

void processData(const vector<vector<string>>& rollers) {
  ScoreCalculator calculator;

  calculator.setCommand(Coaster::wooden, make_unique<WoodenCoasterCommand>());
  calculator.setCommand(Coaster::steel, make_unique<SteelCoasterCommand>());
  calculator.setCommand(Coaster::suspended, make_unique<SuspendedCoasterCommand>());

  for (const vector<string>& rolller : rollers) {
    if (rolller.size()  != 4) {
      cerr << "invalid input size" << endl;
      continue;
    }

    string coaster_type = rolller[0];
    string lift_type = rolller[3];

    double max_speed, bumps_per_sec;
    try {
      max_speed = stod(rolller[1]);
      bumps_per_sec = stod(rolller[2]);
    } catch (exception& e) {
      cerr << "invalid number string" << endl;
      continue; 
    }

    if (!coasters.count(coaster_type)) {
      cerr << "invalid coaster type" << endl;
      continue; 
    }
    if (!lifts.count(lift_type)) {
      cerr << "invalid lift type" << endl;
      continue; 
    }

    double cost = calculator.calculateScore(coasters[coaster_type], max_speed, bumps_per_sec, lifts[lift_type]);
    cout << coaster_type << ": " << cost << endl;
  }
}

} // namespace Simulator

int main() {
    vector<vector<string>> rollers = {
        {"Wooden", "4.0", "1.0", "Chain"},
        {"Steel", "20.0", "2.0", "Cable"},
        {"Suspended", "2.0", "1.5", "Cable"},
        {"Suspended", "2.0", "1.5", "Chain"}
    };

    Simulator::processData(rollers);

    return 0;
}
