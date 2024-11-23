#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"
#include <algorithm>
using namespace std;
using namespace q2;
using namespace q4;
std::vector<Patient> q2::read_file(std::string filename)
{
    ifstream file(filename); // Open the CSV file
    string line;
    vector<Patient> ret;
    if (!file.is_open())
    {
        std::cerr << "Failed to open file\n";
        return ret;
    }

    bool header = false;
    // Read the file line by line
    while (std::getline(file, line))
    {
        std::stringstream ss(line); // Use stringstream to split the line into tokens
        std::string cell;
        std::vector<std::string> row;

        // Read comma-separated values
        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell); // Add each cell to a vector (each row will be a vector of cells)
        }
        if (row.size() != 6)
        {
            continue;
        }
        if (!header)
        {
            header = true;
            continue;
        }
        Patient p;
        p.name = row[0] + (row[0][row[0].size() - 1] == ' ' ? "" : " ") + row[1];
        p.age = stoi(row[2]);
        p.smokes = stoi(row[3]);
        p.area_q = stoi(row[4]);
        p.alkhol = stoi(row[5]);

        ret.push_back(p);
    }

    file.close(); // Close the file
    return ret;
}
int weight(Patient p) {
    return 3*p.age + 5*p.smokes + 2*p.area_q + 4*p.alkhol;
}
bool compare(Patient p1, Patient p2) {
   return weight(p1) > weight(p2);
}
void q2::sort(std::vector<Patient> &patients)
{
    sort(patients.begin(), patients.end(), compare);
}

Vector2D q4::kalman_filter(std::vector<Sensor> sensors) {
    Vector2D ret;
    double totalAcc = 0;
    for_each(sensors.begin(), sensors.end(), [&](Sensor sensor){
        totalAcc += sensor.accuracy;
    });
    for_each(sensors.begin(), sensors.end(), [&](Sensor sensor){
        ret.x += sensor.accuracy / totalAcc * sensor.pos.x;
        ret.y += sensor.accuracy / totalAcc * sensor.pos.y;
    });
    return ret;
}