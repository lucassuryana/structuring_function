#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define functions
vector <double> sense(vector <double> p, string Z, vector <string> world, double pHit, double pMiss);
vector <double> move(vector <double> p, int U, double pExact, double pOvershoot, double pUndershoot);

int main() {
    // Declare and define all vectors and variables
    vector <double> p(5, 0.2);
    vector <string> world;
    vector <string> measurement;
    vector <int> motions(2,1);
    double pHit = 0.6;
    double pMiss = 0.2;
    double pExact = 0.8;
    double pOvershoot = 0.1;
    double pUndershoot = 0.1;

    // Fill in world and measurements vectors
    world.push_back("green");
    world.push_back("red");
    world.push_back("red");
    world.push_back("green");
    world.push_back("green");

    measurement.push_back("red");
    measurement.push_back("green");

    // Iterate through world and measurements vectors
    for (int i = 0; i < measurement.size(); i++) {

        p = sense(p, measurement[i], world, pHit, pMiss);
        p = move(p, motions[i], pExact, pOvershoot, pUndershoot);
    }

    for (int k = 0; k < p.size(); k ++) {
        cout << p[k] << " ";
    }

    cout << endl;

    return 0;
}

vector <double> sense(vector <double> p, string Z, vector <string> world, double pHit, double pMiss) {

    vector <double> q(p.size());
    bool hit;
    double s = 0;

    // Calculate new probabilities
    for (int i = 0; i < p.size(); i++) {
        hit = (Z == world[i]);
        q[i] = p[i] * (hit * pHit + (1-hit) * pMiss);
        s += q[i]; 
    }

    for (int i = 0; i < q.size(); i++) {
        q[i] = q[i] / s;
    }

    return q;
}


vector <double> move(vector <double> p, int U, double pExact, double pOvershoot, double pUndershoot) {
    vector <double> q(p.size());
    double s;

    for (int i = 0; i < p.size(); i++) {
    // Calculate new probabilities
    for (int i = 0; i < p.size(); i++) {
        // The modulo operator behaves a bit different in C++ with negatives
        // If we took it as -1 % p.size(), we'd get zero instead of four
        // -1 + p.size() will give us what we would get from -1 % p.size in Python
        if (i-U < 0) {
            s = pExact * p[(i-U) + p.size()];
        }
        else {
            s = pExact * p[(i-U) % p.size()];
        }
        if (i-U-1 < 0) {
            s = s + pOvershoot * p[(i-U-1) + p.size()];
        }
        else {
            s = s + pOvershoot * p[(i-U-1) % p.size()];
        }
        if (i-U+1 < 0) {
            s = s + pUndershoot * p[(i-U+1) + p.size()];
        }
        else {
            s = s + pUndershoot * p[(i-U+1) % p.size()];
        }

        q[i] = s;
    }

    }

    return q;
}