#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "raceDemogData.h"
#include "psData.h"
#include "regionData.h"
#include <memory>
#include <cassert>
#include <map>
#include "visitor.h"

using namespace std;

class psCombo : public enable_shared_from_this<psCombo>, public regionData
{
public:
    psCombo(string inS)
    {
        states[inS] = true;
        numMentalI = 0;
        fleeingCount = 0;
        over65 = 0;
        under18 = 0;
        racialData = raceDemogData();
        males = 0;
        females = 0;
        cases = 0;
    } //add
    //complete these
    int getNumMentalI() const { return numMentalI; }
    int getFleeingCount() const { return fleeingCount; }
    int getCasesOver65() const { return over65; }
    int getCasesUnder18() const { return under18; }
    raceDemogData getRacialData() const { return racialData; }
    int getnumMales() const { return males; }
    int getnumFemales() const { return females; }
    int getNumberOfCases() const { return cases; }
    void accept(class Visitor &v);

    //add any others needed
    void addIncident(psData p)
    {
        cases++;
        states[p.getState()] = true;
        numMentalI += p.getMental_Illness();
        if (p.getAge() >= 65)
            over65++;
        else if (p.getAge() <= 18)
            under18++;
        p.getGender() ? males++ : females++;
        fleeingCount += p.getFlee();
        if (p.getRace() == "A")
        {
            racialData.addAsianCount(1);
        }
        if (p.getRace() == "B")
        {
            racialData.addBlackCount(1);
        }
        if (p.getRace() == "N")
        {
            racialData.addFirstNationCount(1);
        }
        if (p.getRace() == "H")
        {
            racialData.addLatinxCount(1);
        }
        if (p.getRace() == "O")
        {
            racialData.addOtherCount(1);
        }
        if (p.getRace() == "W")
        {
            racialData.addWhiteCount(1);
            racialData.addWhiteNHCount(1);
        }
        else
            racialData.addCommunityCount(1); //blank entry in csv data
    }
    virtual void toString(std::ostream &out) const
    {
        out << "State Info: ";

        for (auto s : this->states)
        {
            out << s.first << endl;
        }
        out << "total states: " << this->states.size();
        out << "\nNumber of incidents: " << this->getNumberOfCases();
        out << std::setprecision(2) << std::fixed;
        out << "\nIncidents with age \n(over 65): " << double(this->getCasesOver65()) / this->getNumberOfCases() << " \%: " << this->getCasesOver65();
        out << "\n(19 to 64): " << double((this->getNumberOfCases() - (this->getCasesOver65() + this->getCasesUnder18()))) / this->getNumberOfCases() << " \%: " << this->getNumberOfCases() - (this->getCasesOver65() + this->getCasesUnder18());
        out << "\n(under 18): " << double(this->getCasesUnder18() / this->getNumberOfCases()) << " \%: " << this->getCasesUnder18();
        out << "\nIncidents involving fleeing: " << this->getFleeingCount() << " \%: " << double(this->getFleeingCount() * 100) / this->getNumberOfCases();
        out << "\nIncidents involving mental illness: " << this->getNumMentalI() << " \%: " << double(this->getNumMentalI() * 100) / this->getNumberOfCases();
        out << "\nMale incidents: " << this->getnumMales() << " female incidents: " << this->getnumFemales();
        out << "\nRacial demographics of state incidents: " << this->getRacialData();
    }

private:
    std::map<string, bool> states; //add others
    int numMentalI;
    int fleeingCount;
    int over65;
    int under18;
    raceDemogData racialData;
    int males;
    int females;
    int cases;
};

#endif