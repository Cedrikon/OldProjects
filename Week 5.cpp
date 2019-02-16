#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
//#include <cmath>
//#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iomanip>
using namespace std;

class Date {
private:
	int Year;
	int Month;
	int Day;

public:
	int GetYear() const {
		return Year;
	}
	int GetMonth() const {
		return Month;
	}
	int GetDay() const {
		return Day;
	}
	Date (const string& dateline) {

		stringstream stream(dateline);
// first char is number
		if ((stream.peek() >= '0') && (stream.peek() <= '9')) {
		} else {
			stringstream ins;
			ins << "Wrong date format: " << dateline;
			throw runtime_error(ins.str());
		}

		int tempy;
		stream >> tempy;
// year is right
		if ((tempy < 0) || (tempy > 9999)) {
			stringstream ins;
			ins << "Wrong date format: " << dateline;
			throw runtime_error(ins.str());
		}
		Year = tempy;
// next simbol is "-"
		if (stream.peek() != '-') {
			stringstream ins;
			ins << "Wrong date format: " << dateline;
			throw runtime_error(ins.str());
		}
		stream.ignore(1);
// next is number
		if ((stream.peek() >= '0') && (stream.peek() <= '9')) {
		} else {
			stringstream ins;
			ins << "Wrong date format: " << dateline;
			throw runtime_error(ins.str());
		}
// get month
		int tempm;
		stream >> tempm;
// next simbol is "-" and month is less 100
		if ((stream.peek() != '-') || (tempm > 99)) {
			stringstream ins;
			ins << "Wrong date format: " << dateline;
			throw runtime_error(ins.str());
		}
		stream.ignore(1);
// next is number
		if ((stream.peek() >= '0') && (stream.peek() <= '9')) {
		} else {
			stringstream ins;
			ins << "Wrong date format: " << dateline;
			throw runtime_error(ins.str());
		}

		int tempd;
		stream >> tempd;
// nothing after day
		if (stream.peek() > 0) {
			stringstream ins;
			ins << "Wrong date format: " << dateline;
			throw runtime_error(ins.str());
		}

		if ((tempm > 12) || (tempm < 1)) {
			stringstream ins;
			ins << "Month value is invalid: " << tempm;
			throw runtime_error(ins.str());
		} else {
			Month = tempm;
		}
		if ((tempd > 31) || (tempd < 1)) {
			stringstream ins;
			ins << "Day value is invalid: " << tempd;
			throw runtime_error(ins.str());
		} else {
			Day = tempd;
		}
	}

	void PrintDate() const {
		cout << setfill('0') << setw(4) << Year << "-" << setw(2) << Month << "-" << setw(2) << Day;
	}

};

bool operator < (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear()) {
		return true;
	} else {
		if (lhs.GetYear() > rhs.GetYear()) {
			return false;
		} else {
			if (lhs.GetMonth() < rhs.GetMonth()) {
				return true;
			} else {
				if (lhs.GetMonth() > rhs.GetMonth()) {
					return false;
				} else {
					if (lhs.GetDay() < rhs.GetDay()) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool operator == (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			if (lhs.GetDay() == rhs.GetDay()) {
				return true;
			}
		}
	}
	return false;
}

class Database {
private:
	map<Date, set<string>> Dates;
public:
	void AddEvent(const Date& date, const string& event) {
		set<string> vtemp;
		if (Dates.count(date) > 0) {
			vtemp = Dates[date];
			Dates.erase(date);
		}
		vtemp.insert(event);
		Dates[date] = vtemp;
//		date.PrintDate();
//		cout << " added event " << event << endl;
	}

	bool DeleteEvent(const Date& date, const string& event) {
		bool found = false;
		for (auto item : Dates) {
			if (item.first == date) {
				set<string> inner;
				for (auto inevent : item.second) {
					if (inevent != event) {
						inner.insert(inevent);
					} else {
						found = true;
					}
				}
				Dates.erase(date);
				if (inner.size() > 0) {
					Dates[date] = inner;
				}
				break;
			}
		}
		return found;
	}

	int DeleteDate(const Date& date) {
		int delcount = 0;
		for (auto item : Dates) {
			if (item.first == date) {
				delcount = item.second.size();
				Dates.erase(date);
				return delcount;
				break;
			}
		}
		return delcount;
	}

	void Find(const Date& date) const {
		for (auto& item : Dates) {
			if (item.first == date) {
				// item.first.PrintDate();
				for (auto& initem : item.second) {
					cout << initem << endl;
				}
//				cout << endl;
				return;
			}
		}
	}

	void Print() const {
		for (auto& item : Dates) {
//			item.first.PrintDate();
			for (auto& itemsec : item.second) {
				item.first.PrintDate();
				cout << " " << itemsec << endl;
			}
//			cout << endl;
		}
	}

};

int main() {
	Database db;

	string command;
	while (getline(cin, command)) {
//		cout << command << endl;
		stringstream instream(command);
		string fcomm, fdate, fevent;
		instream >> fcomm;

try {
	if (command.size() == 0) {
		throw runtime_error("");
	}
	if ((fcomm != "Del") && (fcomm != "Find") && (fcomm != "Print") && (fcomm != "Add")) {
		cout << "Unknown command: " << fcomm << endl;
		break;
	}
		if (fcomm == "Print") {
			db.Print();
		} else {
			instream.ignore(1);
			instream >> fdate;
			Date indate(fdate);
//			indate.PrintDate();
			instream.ignore(1);
			instream >> fevent;
			if (fcomm == "Del") {
				if (fdate == "") {
					stringstream ins;
					ins << "Wrong date format: " << fdate;
					throw runtime_error(ins.str());
				}
//				cout << "do delete command ";
				if (fevent.length() > 0) {
//					cout << "with event" << endl;
					bool trytodel = db.DeleteEvent(fdate, fevent);
					if (trytodel) {
						cout << "Deleted successfully" << endl;
					} else {
						cout << "Event not found" << endl;
					}
				} else {
//					cout << "NO event" << endl;
					int dcount = db.DeleteDate(fdate);
					cout << "Deleted " << dcount << " events" << endl;
				}
			} else {
				if (fcomm == "Add") {
					if ((fevent == "") || (fdate == "")) {
						stringstream ins;
						ins << "Wrong date format: " << fdate;
						throw runtime_error(ins.str());
					}
					db.AddEvent(fdate, fevent);
				} else {
					if (fcomm == "Find") {
						if (/*(fevent == "") || */(fdate == "")) {
							stringstream ins;
							ins << "Wrong date format: " << fdate;
							throw runtime_error(ins.str());
						}
//						cout << "Founded: ";
						db.Find(fdate);
					} else {
						cout << "Unknown command: " << fcomm << endl;
					}
				}
			}
		}


//		cout << " Recieved: 1. Command - " << fcomm << ", Date - " << fdate << ", Event - " << fevent << endl;
//db.Print();
} catch (exception& ex) {
		cout << ex.what();
		break;
}

	}

	return 0;
}
