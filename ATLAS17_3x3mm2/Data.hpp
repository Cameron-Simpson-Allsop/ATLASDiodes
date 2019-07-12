#include <vector>

class Data
{
public:
  std::vector<double> voltage; //V
  std::vector<double> current; //A
  std::vector<double> capacitance; //F
  std::vector<double> logvoltage;
  std::vector<double> logcapacitance;
  std::vector<double> inversecapacitance2; //1/F2
  std::vector<double> evoltage; 
  std::vector<double> ecurrent;
  std::vector<double> ecapacitance;
  std::vector<double> elogvoltage;
  std::vector<double> elogcapacitance;
  std::vector<double> einversecapacitance2;

  double Vac; //V
  double temp; //K
};
