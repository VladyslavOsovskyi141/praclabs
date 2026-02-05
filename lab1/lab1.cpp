#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

class MathException {
public:
    virtual void message() const {
        cout << "Math exception occurred\n";
    }
};

class FileException : public MathException {
    string file;
public:
    FileException(string f) : file(f) {}
    void message() const override {
        cout << "File error: cannot open " << file << endl;
    }
};

class DomainException : public MathException {
public:
    void message() const override {
        cout << "Domain error: invalid expression under root\n";
    }
};


struct Row {
    double x, t, u;
};


double parseDouble(string s) {
    replace(s.begin(), s.end(), ',', '.');
    return stod(s);
}

vector<Row> loadTable(const string& filename) {
    ifstream in(filename);
    if (!in) throw FileException(filename);

    vector<Row> table;
    string xs, ts, us;

    while (in >> xs >> ts >> us) {
        table.push_back({
            parseDouble(xs),
            parseDouble(ts),
            parseDouble(us)
            });
    }
    return table;
}

double interpolate(const vector<Row>& tab, double x, bool isT) {
    for (size_t i = 0; i + 1 < tab.size(); ++i) {
        if (tab[i].x <= x && x <= tab[i + 1].x) {
            double y1 = isT ? tab[i].t : tab[i].u;
            double y2 = isT ? tab[i + 1].t : tab[i + 1].u;
            return y1 + (y2 - y1) * (x - tab[i].x) / (tab[i + 1].x - tab[i].x);
        }
    }
    return isT ? tab.back().t : tab.back().u;
}


double T(double x) {
    string file;
    if (fabs(x) < 1) file = "dat_X_1_1.dat";
    else if (x < -1) { x = 1 / x; file = "dat_X00_1.dat"; }
    else { x = 1 / x; file = "dat_X1_00.dat"; }

    auto tab = loadTable(file);
    return interpolate(tab, x, true);
}

double U(double x) {
    string file;
    if (fabs(x) < 1) file = "dat_X_1_1.dat";
    else if (x < -1) { x = 1 / x; file = "dat_X00_1.dat"; }
    else { x = 1 / x; file = "dat_X1_00.dat"; }

    auto tab = loadTable(file);
    return interpolate(tab, x, false);
}


double Srz(double x, double y, double z) {
    return (x > y) ? T(x) + U(z) - T(y)
        : T(y) + U(y) - U(z);
}


double Rrz_alg2(double x, double y, double z) {
    return (x > y) ? x * y * (x * Srz(y, z, y))
        : x * z * (y * Srz(x, y, x));
}

double Rrz_alg3(double x, double y, double z) {
    return (x > y) ? x * y * (x * Srz(y, z, y))
        : y * z * (y * Srz(x, y, x));
}


double Srs(double x, double y, double z) {
    if (z > y && z * z + x * y > 0)
        return Srz(x, y, z) + y * sqrt(z * z + x * y);

    if (z <= y && x * x + z * y > 0)
        return y + Srz(z, x, y) * sqrt(x * x + z * y);

    throw DomainException();
}

double Qrz(double x, double y) {
    return (fabs(x) < 1) ? x * Srs(x, y, x)
        : y * Srs(y, x, y);
}

double Rrz(double x, double y, double z) {
    try {
        return (x > y) ? x * z * Qrz(y, z)
            : y * x * Qrz(x, y);
    }
    catch (DomainException&) {
        if (z * z + x * y < 0)
            return Rrz_alg2(x, y, z);
        return Rrz_alg3(x, y, z);
    }
}

double Grs(double x, double y, double z) {
    return 0.1389 * Rrz(x, y, y)
        + 1.8389 * Rrz(x - y, z, y);
}

double fun(double x, double y, double z) {
    try {
        return x * Grs(x, y, z) + y * Grs(x, z, y);
    }
    catch (FileException& e) {
        e.message();
        return 1.3498 * x + 2.2362 * y * z - 2.348 * x * y;
    }
}

// main

int main() {
    double x, y, z;
    cout << "Input x y z: ";
    cin >> x >> y >> z;

    try {
        double f = fun(x, y, z);
        cout << "fun = " << f << endl;
    }
    catch (MathException& e) {
        e.message();
    }
    catch (...) {
        cout << "Unknown error\n";
    }

    return 0;
}