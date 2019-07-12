#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Data
{
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

double StdDev(double c1, double c2, double c3, double c4, double c5, double mean)
{
  double sumSquares = pow(c1-mean,2) + pow(c2-mean,2) + pow(c3-mean,2) + pow(c4-mean,2) + pow(c5-mean,2);
  return pow(sumSquares/4.,0.5); 
}

Data ReadFile(std::string filePath)
{
  ifstream inFile;  
  inFile.open(filePath);
  Data data;
  std::vector<double> Voltage;
  std::vector<double> Current;
  std::vector<double> Capacitance;
  double capacitanceMean{0};
  double ecapacitanceMean{0};
  double currentMean{0};
  double ecurrentMean{0};
  std::size_t CV = filePath.find("CV");
  std::size_t IV = filePath.find("IV");
  	  std::string line{""};
	  std::string timeStamp{""};
	  double voltage{}, current{}, resistance{}, capacitance{};
	  int linecount{1};
	  
  if(!inFile.good())
	{
	  std::cout << "Error Opening Input File..." << std::endl;
	  return data;
	}
	  
  if(CV != std::string::npos && IV == std::string::npos)
    {   
	  while(!inFile.eof())
	    {
	      getline(inFile,line);
	      if(linecount == 5)
		{
		  //std::cout << line << std::endl;
		  std::string tmpVac;
		  stringstream ssline(line);
		  std::size_t mVac = line.find("mVac");
		  if(mVac != std::string::npos)
		    {
		      tmpVac = "0.5";
		    }
		  else if(mVac ==std::string::npos)
		    {
		      tmpVac = "1";
		    }
		  std::size_t degree = line.find("C");
		  std::string tmpdegree = line.substr(degree - 4, 4);
		  //std::cout<<tmpdegree<<std::endl;
		  //line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		  data.temp = std::stod(tmpdegree);
		  data.Vac = std::stod(tmpVac);
		}
	      else if(linecount > 29)
		{
		  //std::cout << line << std::endl;
		  stringstream ssdata(line);
		  ssdata >> timeStamp >> voltage >> current >> resistance >> capacitance;
		  //std ::cout << timeStamp << "\t" << voltage << "\t" << current << "\t" << resistance << "\t" << capacitance << std::endl;
		  Voltage.push_back(voltage);
		  Current.push_back(current);
		  Capacitance.push_back(capacitance);
		}  
	      ++linecount;
	    }
  
  
      int n{0};
      for(int i{0}; i<=Voltage.size(); ++i)
    	{
    	  if(n != 5){++n;}
    	  else if(n == 5)
    	    {
    	      n = 1;
    	      double voltageav{(Voltage[i-1] + Voltage[i-2] + Voltage[i-3] + Voltage[i-4] +Voltage[i-5])/5.};
    	      data.voltage.push_back(voltageav);
    	      data.evoltage.push_back(0.05);

	      capacitanceMean = (Capacitance[i-1] + Capacitance[i-2] + Capacitance[i-3] + Capacitance[i-4] +Capacitance[i-5])/5.;
    	      data.capacitance.push_back(capacitanceMean);
    	      ecapacitanceMean = StdDev(Capacitance[i-1],Capacitance[i-2],Capacitance[i-3],Capacitance[i-4],Capacitance[i-5],capacitanceMean);
	      data.ecapacitance.push_back(ecapacitanceMean);
	      
	      currentMean = (Current[i-1] + Current[i-2] + Current[i-3] + Current[i-4] +Current[i-5])/5.;
    	      data.current.push_back(currentMean);
    	      ecurrentMean = StdDev(Current[i-1],Current[i-2],Current[i-3],Current[i-4],Current[i-5],currentMean);
	      data.ecurrent.push_back(ecurrentMean);

	      data.inversecapacitance2.push_back(1/pow(capacitanceMean,2));
	      data.einversecapacitance2.push_back(ecapacitanceMean/pow(capacitanceMean,3));
	      
	      if(voltageav != 0)
		{
		  data.logcapacitance.push_back(log(abs(capacitanceMean)));
		  data.logvoltage.push_back(log(abs(voltageav)));
		  data.elogcapacitance.push_back(abs(ecapacitanceMean/capacitanceMean));
		  data.elogvoltage.push_back(abs(0.05/voltageav));
		}
    	    }      
    	}
      return data;
      inFile.close();
  }
  else if (CV == std::string::npos && IV != std::string::npos)
    {
      //std::string line{""};
      std::string timeStamp{""};
      double voltage{}, current{};
      int linecount{1};
      while(!inFile.eof())
	{
	  getline(inFile,line);
	  if(linecount == 5)
	    {
	      stringstream ssline(line);
	      //std::cout<<line<<std::endl;
	      line.erase(std::remove(line.begin(), line.end(), 'C'), line.end());
	      std::string tmpdegree = line.substr(line.size() - 5, 4);
	      //std::cout<<tmpdegree<<std::endl;
	    }
	  else if(linecount > 18)
	    {
	      //std::cout << line << std::endl;
	      stringstream ssdata(line);
	      ssdata >> timeStamp >> voltage >> current;
	      //std ::cout << timeStamp << "\t" << voltage << "\t" << current << std::endl;
	      Voltage.push_back(voltage);
	      Current.push_back(current);
	    }
	  ++linecount;
	}
      int n{0};
      for(int i{0}; i<=Voltage.size(); ++i)
    	{
    	  if(n != 5){++n;}
    	  else if(n == 5)
    	    {
    	      n = 1;
    	      double voltageav{(Voltage[i-1] + Voltage[i-2] + Voltage[i-3] + Voltage[i-4] +Voltage[i-5])/5.};
    	      data.voltage.push_back(voltageav);
    	      data.evoltage.push_back(0.05);
	      
	      currentMean = (Current[i-1] + Current[i-2] + Current[i-3] + Current[i-4] +Current[i-5])/5.;
    	      data.current.push_back(currentMean);
    	      ecurrentMean = StdDev(Current[i-1],Current[i-2],Current[i-3],Current[i-4],Current[i-5],currentMean);
	      data.ecurrent.push_back(ecurrentMean);
    	    }      
    	}
      return data;
      inFile.close();
    }
  else
    std::cout << "Error Reading Input File..." << std::endl;
  return data;
  inFile.close();
}
