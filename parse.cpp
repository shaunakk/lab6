/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>
/* helper to strip out quotes from a string */
string stripQuotes(std::string temp)
{
    temp.erase(
        remove(temp.begin(), temp.end(), '\"'),
        temp.end());
    return temp;
}

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss)
{
    string data, junk;
    //ignore the first quotes
    std::getline(ss, junk, '\"');
    //read the data (not to comma as some data includes comma (Hospital names))
    std::getline(ss, data, '\"');
    //read to comma final comma (to consume and prep for next)
    std::getline(ss, junk, ',');
    //data includes final quote (see note line 18)
    return stripQuotes(data);
}

string getFieldNQ(std::stringstream &ss)
{
    string temp;
    std::getline(ss, temp, ',');
    //std::cout << temp << std:: endl;
    return temp;
}

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile)
{
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while (std::getline(ss, colname, ','))
    {
        //    std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<regionData> readCSVLineDemog(std::string theLine)
{
    std::stringstream ss(theLine);

    string name = getField(ss);
    string state = getField(ss);
    //turn into mathematical percent
    double popOver65 = stod(getField(ss));
    double popUnder18 = stod(getField(ss));
    double popUnder5 = stod(getField(ss));
    double bachelorDegreeUp = stod(getField(ss));
    double highSchoolUp = stod(getField(ss));

    //now skip over some data
    for (int i = 0; i < 4; i++)
        getField(ss);

    //store initial data as percent (then convert to count)
    double FirstNation = stod(getField(ss)) / 100.0;
    double Asian = stod(getField(ss)) / 100.0;
    double Black = stod(getField(ss)) / 100.0;
    double Latinx = stod(getField(ss)) / 100.0;
    double HIPacificIsle = stod(getField(ss)) / 100.0;
    double MultiRace = stod(getField(ss)) / 100.0;
    double White = stod(getField(ss)) / 100.0;
    double WhiteNH = stod(getField(ss)) / 100.0;
    //now skip over some data
    for (int i = 0; i < 6; i++)
        getField(ss);

    int medHouseIncome = stoi(getField(ss)); //dont use
    //skip per capita
    getField(ss);
    double belowPoverty = stod(getField(ss));
    //now skip over some data
    for (int i = 0; i < 10; i++)
        getField(ss);

    int totalPop2014 = stoi(getField(ss));
    raceDemogData r = raceDemogData(round(FirstNation * totalPop2014), round(Asian * totalPop2014), round(Black * totalPop2014), round(Latinx * totalPop2014), round(HIPacificIsle * totalPop2014), round(MultiRace * totalPop2014), round(White * totalPop2014), round(WhiteNH * totalPop2014), round(totalPop2014));

    //update as needed this is lab3 version
    return make_shared<demogData>(name, state, popOver65, popUnder18,
                                  popUnder5, bachelorDegreeUp, highSchoolUp, totalPop2014, belowPoverty, r);
}

//read one line of police data
shared_ptr<regionData> readCSVLinePolice(std::string theLine)
{
    std::stringstream ss(theLine);

    getFieldNQ(ss); //ignore id
    string name = getFieldNQ(ss);
    for (int i = 0; i < 3; i++)
    {
        getFieldNQ(ss);
    }
    int age = 0;
    string tmp = getFieldNQ(ss);
    if (tmp != "")
    {
        age = stoi(tmp);
    }
    else
    {
        age = -1;
    }
    bool gender = getFieldNQ(ss) == "M";
    string race = getFieldNQ(ss);
    string city = getFieldNQ(ss);
    string state = getFieldNQ(ss);
    bool illness = (getFieldNQ(ss) == "True");
    getFieldNQ(ss);
    string fleeString = getFieldNQ(ss);
    bool flee = !(fleeString == "Not fleeing" || fleeString == "");
    //finish reading other data fields and initialize police data

    return make_shared<psData>(state, name, age, gender, race, city, illness, flee);
}

//read from a CSV file (for a given data type) return a vector of the data
void read_csv(vector<shared_ptr<regionData>> &pileOfData, std::string filename, typeFlag fileType)
{
    //the actual data

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    if (myFile.good())
    {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create demographic dataobject
        while (std::getline(myFile, line))
        {
            if (fileType == DEMOG)
            {
                pileOfData.push_back(readCSVLineDemog(line));
            }
            else if (fileType == POLICE)
            {

                pileOfData.push_back(readCSVLinePolice(line));
            }
            else
            {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }

    //return theData;
}

// Reads a CSV file
