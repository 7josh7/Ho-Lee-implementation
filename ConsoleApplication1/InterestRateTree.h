// InterestRateTree.h
#ifndef INTEREST_RATE_TREE_H
#define INTEREST_RATE_TREE_H

#include <vector>
#include <cmath>

using namespace std;

class InterestRateTree {
public:
    InterestRateTree(double r0, double u, double d, int n);
    vector<vector<double>> build() const;
    double valueOfCashflows(const vector<double>& cflow, const vector<vector<double>>& r_tree, double q) const;
    double valueOfCallableBond(const vector<double>& cflows, const vector<vector<double>>& r_tree, double q, int first_call_time, double call_price) const;

protected:
    double r0;
    double u;
    double d;
    int n;
};

#endif // InterestRateTree.h
