#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
//#include <cmath>
//#include <algorithm>
#include <vector>
//#include <string>
#include <map>
#include <set>
//#include <iomanip>
using namespace std;

class Rational {
public:
    Rational() {
    	numer = 0;
    	denom = 1;
    }

    Rational(int numerator, int denominator) {
    	if (denominator == 0) {
/*    		stringstream errorstr;
    		errorstr << "invalid_argument";*/
    		throw 1;
//    		throw invalid_argument("invalid_argument");
    	}
    	if (numerator == 0) {
    		numer = 0;
    		denom = 1;
    	} else {
    		if (denominator < 0) {
    			numerator *= -1;
    			denominator *= -1;
    		}
		int i = abs(numerator);
		int j = abs(denominator);
			while (i > 0 && j > 0) {
				if (i > j) {
					i %= j;
				} else {
					j %= i;
				}
			}
		i += j;
		numer = numerator / i;
		denom = denominator /i;
    	}
    }

    int Numerator() const {
    	return numer;
    }

    int Denominator() const {
    	return denom;
    }

private:
   int numer;
   int denom;
};

bool operator == (const Rational& lhs, const Rational& rhs) {
	if ((lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator())) {
		return true;
	}
	return false;
}

bool operator > (const Rational& lhs, const Rational& rhs) {
	if (lhs.Numerator() * rhs.Denominator() > rhs.Numerator() * lhs.Denominator()) {
		return true;
	}
	return false;
}

bool operator < (const Rational& lhs, const Rational& rhs) {
	if (lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator()) {
		return true;
	}
	return false;
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
	int i = lhs.Numerator();
	int k = lhs.Denominator();
	int j = rhs.Numerator();
	int l = rhs.Denominator();
	return Rational( i * l + k * j, l * k);
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
	int i = lhs.Numerator();
	int k = lhs.Denominator();
	int j = rhs.Numerator();
	int l = rhs.Denominator();
	return Rational( i * l - k * j, l * k);
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
	int i = lhs.Numerator() * rhs.Numerator();
	int j = lhs.Denominator() * rhs.Denominator();
	return Rational( i, j);
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
/*		stringstream errorstr;
		errorstr << "domain_error";*/
		throw 2;
//		throw domain_error("domain_error");
	}
	int i = lhs.Numerator() * rhs.Denominator();
	int j = lhs.Denominator() * rhs.Numerator();
	return Rational( i, j);
}

ostream& operator<<(ostream& stream, const Rational& rational) {
	if (stream) {
		stream << rational.Numerator() << '/' << rational.Denominator();
	}
	return stream;
}

istream& operator>>(istream& stream, Rational& rational) {
	int i, j;
	stream >> i;
	stream.ignore(1);
	stream >> j;
	if (stream) {
		Rational rat(i, j);
		rational = rat;
	}
	return stream;
}

int main() {
    try {
        Rational i, j, outrat;
        char k;
        cin >> i >> k >> j;
        if (k == '+') {
        	outrat = i + j;
        	cout << outrat;
        } else {
        	if (k == '-') {
        		outrat = i - j;
        		cout << outrat;
        	} else {
        		if (k == '*') {
        			outrat = i * j;
        			cout << outrat;
        		} else {
        			outrat = i / j;
        			cout << outrat;
        		}
        	}
        }
    } catch (int& excpt) {
    	if (excpt == 1) {
    		cout << "Invalid argument";
    	} else {
    		if (excpt == 2) {
    			cout << "Division by zero";
    		}
    	}
    }

//    cout << "OK" << endl;
    return 0;
}
