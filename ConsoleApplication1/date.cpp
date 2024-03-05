#include "date.h"
date::date() { year_ = 0; month_ = 0; day_ = 0; };
date::date(const int& day, const int& month, const int& year) {
	day_ = day;
	month_ = month;
	year_ = year;
};
int date::day() const { return day_; };
int date::month() const { return month_; };
int date::year() const { return year_; };
void date::set_day(const int& day) { date::day_ = day; };
void date::set_month(const int& month) { date::month_ = month; };
void date::set_year(const int& year) { date::year_ = year; };
bool date::valid() const {
	// Basic checks
	if (year_ < 0) return false;
	if (month_ < 1 || month_ > 12) return false;
	if (day_ < 1 || day_ > 31) return false;

	// Check for months with 30 days
	if ((month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11) && day_ > 30) {
		return false;
	}

	// Check for February (month 2)
	if (month_ == 2) {
		// Check if it's a leap year
		bool isLeapYear = (year_ % 4 == 0 && (year_ % 100 != 0 || year_ % 400 == 0));
		if (day_ > 29 || (day_ == 29 && !isLeapYear)) {
			return false;
		}
	}

	return true; // Passed all checks
}

bool operator == (const date& d1, const date& d2) {//check forequality
	if (!(d1.valid() && (d2.valid()))) { return false; }; /*ifdatesnotvalid,not clearwhat todo.
	alternative: throwexception*/
	return((d1.day() == d2.day()) && (d1.month() == d2.month()) && (d1.year() == d2.year()));
};
bool operator < (const date& d1, const date& d2) {
	if (!(d1.valid() && (d2.valid()))) { return false; }; //seeaboveremark
	if (d1.year() == d2.year()) {//sameyear
		if (d1.month() == d2.month()) {//samemonth
			return(d1.day() < d2.day());
		}
		else {
			return(d1.month() < d2.month());
		};
	}
	else {//differentyear
		return(d1.year() < d2.year());
	};
};
//remainingoperatorsdefinedintermsof theabove
bool operator<=(const date& d1, const date& d2) {
	if (d1 == d2) { return true; }
	return(d1 < d2);
}
bool operator>=(const date& d1, const date& d2) {
	if (d1 == d2) { return true; };
	return(d1 > d2);
};
bool operator>(const date& d1, const date& d2) { return !(d1 <= d2); };
bool operator !=(const date& d1, const date& d2) { return !(d1 == d2); }

date next_date(const date& d) {
	if (!d.valid()) { return date(); }; //
	date ndat = date((d.day() + 1), d.month(), d.year()); //first tryaddingaday
	if (ndat.valid()) return ndat;
	ndat = date(1, (d.month() + 1), d.year()); //thentryaddingamonth
	if (ndat.valid()) return ndat;
	ndat = date(1, 1, (d.year() + 1)); //must benextyear
	return ndat;
}
date previous_date(const date& d) {
	if (!d.valid()) { return date(); }; //returnthedefaultdate
	date pdat = date((d.day()-1), d.month(), d.year()); if (pdat.valid()) return pdat; //trysamemonth
	pdat = date(31, (d.month()-1), d.year()); if (pdat.valid()) return pdat; //trypreviousmonth
	pdat = date(30, (d.month()-1), d.year()); if (pdat.valid()) return pdat;
	pdat = date(29, (d.month()-1), d.year()); if (pdat.valid()) return pdat;
	pdat = date(28, (d.month()-1), d.year()); if (pdat.valid()) return pdat;
	pdat = date(31, 12, (d.year()-1)); //trypreviousyear
	return pdat;
};
date date::operator++(int) {//postfixoperator
	date d = *this;
	*this = next_date(d);
	return d;
}
date date::operator ++() {//prefixoperator
	*this = next_date(*this);
	return*this;
}
date date::operator --(int) {//postfixoperator, returncurrent value
	date d = *this;
	*this = previous_date(*this);
	return d;
}
date date::operator --() {//prefixoperator, returnnewvalue
	*this = previous_date(*this);
	return*this;
};
