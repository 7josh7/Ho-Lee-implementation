// InterestRateTree.cpp
#include "InterestRateTree.h"

InterestRateTree::InterestRateTree(double r0, double u, double d, int n)
    : r0(r0), u(u), d(d), n(n) {}

vector<vector<double>> InterestRateTree::build() const {
    vector<vector<double>> tree;
    vector<double> r(1);
    r[0] = r0;
    tree.push_back(r);
    for (int i = 1; i <= n; ++i) {
        double rtop = r[r.size() - 1] * u;
        for (int j = 0; j < i; ++j) {
            r[j] = d * r[j];
        }
        r.push_back(rtop);
        tree.push_back(r);
    }
    return tree;
}


double InterestRateTree::valueOfCashflows(const vector<double>& cflow, const vector<vector<double>>& r_tree, double q) const {
    int n = int(cflow.size());
    vector<vector<double>> values(n);
    vector<double> value(n);

    // Initialize values with the final cashflows
    for (int i = 0; i < n; ++i) {
        value[i] = cflow[n - 1];
    }
    values[n - 1] = value;

    // Backward induction through the tree
    for (int t = n - 1; t > 0; --t) { // t represent time step
        vector<double> value(t, 0.0);
        for (int i = 0; i < t; ++i) { // i represent statue
            value[i] = cflow[t - 1] + exp(-r_tree[t - 1][i]) * (q * values[t][i] + (1 - q) * values[t][i + 1]);
        }
        values[t - 1] = value;
    }

    return values[0][0];
}

double InterestRateTree::valueOfCallableBond(const vector<double>& cflows, const vector<vector<double>>& r_tree, double q, int first_call_time, double call_price) const {
    int n = int(cflows.size());
    vector<vector<double>> values(n);
    vector<double> value(n);

    // Initialize values with the final cashflows
    for (int i = 0; i < n; ++i) {
        value[i] = cflows[n - 1];
    }
    values[n - 1] = value;

    // Backward induction through the tree
    for (int t = n - 1; t > 0; --t) {
        vector<double> value(t, 0.0);
        for (int i = 0; i < t; ++i) {
            value[i] = cflows[t - 1] + exp(-r_tree[t - 1][i]) * (q * values[t][i] + (1 - q) * values[t][i + 1]);
            if (t >= first_call_time) {
                value[i] = min(value[i], call_price);
            }
        }
        values[t - 1] = value;
    }

    return values[0][0];
}
// InterestRateTree.cpp
