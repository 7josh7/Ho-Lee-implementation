// term_structure.cpp
#include "term_structure.h"
#include <cmath>

namespace financial_math {

    double TermStructure::yieldFromDiscountFactor(const double& d_t, const double& t) {
        return (-std::log(d_t) / t);
    }

    double TermStructure::discountFactorFromYield(const double& r, const double& t) {
        return std::exp(-r * t);
    }

    double TermStructure::forwardRateFromDiscountFactors(const double& d_t1, const double& d_t2, const double& time) {
        return (std::log(d_t1 / d_t2)) / time;
    }

    double TermStructure::forwardRateFromYields(const double& r_t1, const double& r_t2, const double& t1, const double& t2) {
        return (r_t2 * t2 - r_t1 * t1) / (t2 - t1);
    }

    double TermStructure::nelsonSiegelSpotRate(double t, const NelsonSiegelParams& params) {
        double term1 = params.beta0;
        double term2 = params.beta1 * (1 - exp(-t / params.tau)) / (t / params.tau);
        double term3 = params.beta2 * ((1 - exp(-t / params.tau)) / (t / params.tau) - exp(-t / params.tau));
        return term1 + term2 + term3;
    }

    double TermStructure::nelsonSiegelDiscountFactor(double t, const NelsonSiegelParams& params) {
        double spotRate = nelsonSiegelSpotRate(t, params);
        return exp(-spotRate * t);
    }
    std::vector<double> TermStructure::bootstrapYieldCurve(const std::vector<Bond>& bonds) {
        std::vector<double> spotRates(bonds.size(), 0.0);
        for (size_t i = 0; i < bonds.size(); ++i) {
            const auto& bond = bonds[i];
            double cashFlowSum = 0.0;
            double coupon = bond.couponRate * bond.faceValue / bond.frequency;
            for (int j = 1; j <= bond.maturity * bond.frequency; ++j) {
                double time = j / static_cast<double>(bond.frequency);
                double df = j - 1 < i ? discountFactorFromYield(spotRates[j - 1], time) : 1.0;  // Use previously bootstrapped rates
                cashFlowSum += coupon * df;
            }
            // Add the face value payment
            double lastDF = discountFactorFromYield(spotRates[i], bond.maturity);
            double totalValue = cashFlowSum + bond.faceValue * lastDF;
            double targetPrice = bond.price;

            // Simple solver: Adjust the spot rate until the bond is correctly priced
            double error = totalValue - targetPrice;
            while (std::abs(error) > 0.0001) {
                spotRates[i] += (targetPrice - totalValue) / 100000.0;  // Adjust rate
                lastDF = discountFactorFromYield(spotRates[i], bond.maturity);
                totalValue = cashFlowSum + bond.faceValue * lastDF;
                error = totalValue - targetPrice;
            }
        }
        return spotRates;
    }

} // namespace financial_math
