//#include <iostream>
//#include <nana/gui.hpp>
//#include <nana/gui/widgets/label.hpp>
//#include <nana/gui/widgets/textbox.hpp>
//#include <nana/gui/widgets/button.hpp>
//#include <nana/gui/widgets/combox.hpp>
//#include <nana/gui/widgets/form.hpp>
//#include <nana/gui/drawing.hpp>
//#include <sstream>  
//#include <vector>
//#include <string>
//#include "BlackScholes.h"
//#include "date.h"
//#include "TermStructure.h"
//
//
//
//int main() {
//	using namespace nana;
//	using namespace financial_math;
//
//
//	// Create the form
//	form fm;
//	fm.size(size(700, 400));  // Ensure enough space for graph and controls
//	fm.caption("Option Price Calculator");
//
//	// Create a dropdown list for option type (Call or Put)
//	label lblType(fm, rectangle(10, 10, 200, 20));
//	lblType.caption("Option Type:");
//	combox cmbOptionType(fm, rectangle(220, 10, 100, 20));
//	cmbOptionType.push_back("Call");
//	cmbOptionType.push_back("Put");
//	cmbOptionType.option(0); // Set default selection to "Call"
//
//	label lblS(fm, rectangle(10, 40, 200, 20));
//	lblS.caption("Underlying stock price (S):");
//	textbox txtS(fm, rectangle(220, 40, 100, 20));
//	txtS.caption("100");  // Default stock price
//	txtS.multi_lines(false);
//
//	label lblK(fm, rectangle(10, 70, 200, 20));
//	lblK.caption("Strike price (K):");
//	textbox txtK(fm, rectangle(220, 70, 100, 20));
//	txtK.caption("100");  // Default strike price
//	txtK.multi_lines(false);
//
//	label lblDividend(fm, rectangle(10, 100, 200, 20));
//	lblDividend.caption("Dividend Yield:");
//	textbox txtDividend(fm, rectangle(220, 100, 100, 20));
//	txtDividend.caption("0");  // Default dividend yield (0%)
//	txtDividend.multi_lines(false);
//
//	label lblSigma(fm, rectangle(10, 130, 200, 20));
//	lblSigma.caption("Volatility (sigma):");
//	textbox txtSigma(fm, rectangle(220, 130, 100, 20));
//	txtSigma.caption("0.2");  // Default volatility (20%)
//	txtSigma.multi_lines(false);
//
//	label lblTimeS(fm, rectangle(10, 160, 200, 20));
//	lblTimeS.caption("Starting Date(YYYY/MM/DD):");
//	textbox txtTimeS(fm, rectangle(220, 160, 100, 20));
//	txtTimeS.caption("2024/01/01");  // Default starting date
//	txtTimeS.multi_lines(false);
//
//	label lblTimeE(fm, rectangle(10, 190, 200, 20));
//	lblTimeE.caption("Expiration Date(YYYY/MM/DD):");
//	textbox txtTimeE(fm, rectangle(220, 190, 100, 20));
//	txtTimeE.caption("2024/12/31");  // Default expiration date
//	txtTimeE.multi_lines(false);
//
//	// Day count convention label 
//	label lblDayCount(fm, rectangle(10, 220, 200, 20));
//	lblDayCount.caption("Day Count Convention:");
//	std::vector<std::string> dayCountConventions = { "Thirty360", "Thirty365", "Actual360", "Actual365", "ActualActual" };
//	combox cmbDayCount(fm, rectangle(220, 220, 100, 20));
//	for (const auto& dayCount : dayCountConventions) {
//		cmbDayCount.push_back(dayCount);
//	}
//	cmbDayCount.option(0);
//
//	// Create button
//	button btnCalculate(fm, rectangle(10, 280, 230, 30));
//	btnCalculate.caption("Calculate Prices");
//
//
//	// NelsonSiegelParams Title
//	label lblNelsonSiegelParams(fm, rectangle(340, 10, 400, 20));
//	lblNelsonSiegelParams.caption("NelsonSiegelParams for Constructing risk-free terms structure:");
//
//	// Labels and textboxes for NelsonSiegel parameters
//	label lblBeta0(fm, rectangle(340, 40, 200, 20));
//	lblBeta0.caption("Beta0 (Level):");
//	textbox txtBeta0(fm, rectangle(550, 40, 100, 20));
//	txtBeta0.caption("0.05");  // Default value for Beta0
//	txtBeta0.multi_lines(false);
//
//	label lblBeta1(fm, rectangle(340, 70, 200, 20));
//	lblBeta1.caption("Beta1 (Slop):");
//	textbox txtBeta1(fm, rectangle(550, 70, 100, 20));
//	txtBeta1.caption("-0.02");  // Default value for Beta1
//	txtBeta1.multi_lines(false);
//
//	label lblBeta2(fm, rectangle(340, 100, 200, 20));
//	lblBeta2.caption("Beta2 (Curvature):");
//	textbox txtBeta2(fm, rectangle(550, 100, 100, 20));
//	txtBeta2.caption("0.03");  // Default value for Beta2
//	txtBeta2.multi_lines(false);
//
//	label lblTau(fm, rectangle(340, 130, 200, 20));
//	lblTau.caption("Tau :");
//	textbox txtTau(fm, rectangle(550, 130, 100, 20));
//	txtTau.caption("1.5");  // Default value for Tau
//	txtTau.multi_lines(false);
//
//	label lblNelsonSiegelNote(fm, rectangle(340, 160, 400, 20));
//	lblNelsonSiegelNote.caption("*Note: set Beta1 = Beta2 = 0 for Constant Rate");
//
//	// Event handler for the button
//	btnCalculate.events().click([&] {
//		double S = std::stod(txtS.caption());
//		double K = std::stod(txtK.caption());
//		double sigma = std::stod(txtSigma.caption());
//		double b0 = std::stod(txtBeta0.caption());
//		double b1 = std::stod(txtBeta1.caption());
//		double b2 = std::stod(txtBeta2.caption());
//		double tau = std::stod(txtTau.caption());
//
//		// Parse starting date
//		std::istringstream startStream(txtTimeS.caption());
//		int sYear, sMonth, sDay;
//		char delim;
//		startStream >> sYear >> delim >> sMonth >> delim >> sDay;
//		date startingDate(sDay, sMonth, sYear);
//
//		// Parse expiration date
//		std::istringstream endStream(txtTimeE.caption());
//		int eYear, eMonth, eDay;
//		endStream >> eYear >> delim >> eMonth >> delim >> eDay;
//		date expirationDate(eDay, eMonth, eYear);
//
//		if (!startingDate.valid() || !expirationDate.valid()) {
//			msgbox mb(fm, "Error");
//			mb << "Invalid date(s) entered.";
//			mb.show();
//			return;
//		}
//
//		// Determine the day count convention based on combox selection
//		DayCountConvention dcc;
//		switch (cmbDayCount.option()) {
//		case 0: dcc = DayCountConvention::Thirty360; break;
//		case 1: dcc = DayCountConvention::Thirty365; break;
//		case 2: dcc = DayCountConvention::Actual360; break;
//		case 3: dcc = DayCountConvention::Actual365; break;
//		case 4: dcc = DayCountConvention::ActualActual; break;
//		default:
//			msgbox mb_error(fm, "Invalid day count convention selected");
//			mb_error.show();
//			return;
//		}
//
//		// Calculate the time to maturity using years_until method
//		double timeToMaturity = startingDate.years_until(expirationDate, dcc);
//		TermStructure::NelsonSiegelParams params(b0, b1, b2, tau);
//		double r = TermStructure::nelsonSiegelSpotRate(timeToMaturity, params);
//
//		// Calculate and display the prices and Greeks
//		msgbox mbPrice(fm, "Option Prices and Greeks");
//		if (cmbOptionType.option() == 0) { // Call option selected
//			CallOption call(S, K, r, sigma, timeToMaturity);
//			mbPrice << "Call Option Price: " << call.option_price() << "\n";
//			mbPrice << "Delta: " << call.delta() << "\n";
//			mbPrice << "Gamma: " << call.gamma() << "\n";
//			mbPrice << "Vega: " << call.vega() << "\n";
//			mbPrice << "Theta: " << call.theta() << "\n";
//			mbPrice << "Rho: " << call.rho();
//		}
//		else { // Put option selected
//			PutOption put(S, K, r, sigma, timeToMaturity);
//			mbPrice << "Put Option Price: " << put.option_price() << "\n";
//			mbPrice << "Delta: " << put.delta() << "\n";
//			mbPrice << "Gamma: " << put.gamma() << "\n";
//			mbPrice << "Vega: " << put.vega() << "\n";
//			mbPrice << "Theta: " << put.theta() << "\n";
//			mbPrice << "Rho: " << put.rho();
//		}
//		mbPrice.show();
//		});
//
//	// Show the form
//	fm.show();
//
//	// Start the event loop
//	exec();
//}



#include "TimeContingentCashFlows.h"
#include "TermStructureHoLee.h"
#include "TermStructure.h"
#include <iostream>
#include <vector>

int main() {
    double delta = 0.98;
    double pi = 0.5;
    double r = 0.1;

    // Flat term structure
    TermStructure* initial = new TermStructureFlat(r);
    std::vector<double> times;
    times.push_back(5.0);
    std::vector<double> cflows;
    cflows.push_back(100);
    double K = 80;
    double time_to_maturity = 3;
    std::cout << "Flat term structure" << std::endl;
    std::cout << "c = " << price_european_call_option_on_bond_using_ho_lee(initial, delta, pi, times, cflows, K, time_to_maturity) << std::endl;
    std::cout << std::endl;

    delete initial;
    // Nelson-Siegel term structure
    double beta0 = 0.09;
    double beta1 = 0.01;
    double beta2 = 0.01;
    double lambda = 5.0;
    TermStructure::NelsonSiegelParams ns_params(beta0, beta1, beta2, lambda);
    initial = new TermStructureInterpolated();

    // Setting up the Nelson-Siegel term structure with interpolated observations
    std::vector<double> ns_times = { 1.0, 2.0, 3.0, 4.0, 5.0 }; // Example times
    std::vector<double> ns_yields;
    for (double t : ns_times) {
        ns_yields.push_back(TermStructure::nelsonSiegelSpotRate(t, ns_params));
    }
    dynamic_cast<TermStructureInterpolated*>(initial)->setInterpolatedObservations(ns_times, ns_yields);

    std::cout << "Nelson Siegel term structure" << std::endl;
    std::cout << "c = " << price_european_call_option_on_bond_using_ho_lee(initial, delta, pi, times, cflows, K, time_to_maturity) << std::endl;
    std::cout << std::endl;

    delete initial;

    return 0;
}

