#include <iostream>
#include <set>

using namespace std;


template <class T> class Set {
	set <T> symbols;
public:
	Set(set<T> s) : symbols(s) {}
	Set() {}

	Set getSet() { return symbols; }

	void addToSet(T c) { symbols.insert(c); }

	void removeFromSet(T c) { symbols.erase(c); }

	Set operator +(const Set& s) const {
		Set res(symbols);
		for (typename set<T>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
			res.addToSet(*it);
		return res;
	}

	Set operator -(const Set& s) const {
		Set res(symbols);
		for (typename set<T>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
			if (res.symbols.find(*it) != res.symbols.end())
				res.removeFromSet(*it);
		return res;
	}

	Set& operator +=(const Set& s) {
		for (typename set<T>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
			this->addToSet(*it);
		return *this;
	}

	Set& operator -=(const Set& s) {
		for (typename set<T>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
			if (symbols.find(*it) != symbols.end())
				this->removeFromSet(*it);
		return *this;
	}

	bool operator >(const Set& s) const { return symbols.size() > s.symbols.size(); }
	bool operator <(const Set& s) const { return symbols.size() < s.symbols.size(); }
	bool operator >=(const Set& s) const { return symbols.size() >= s.symbols.size(); }
	bool operator <=(const Set& s) const { return symbols.size() <= s.symbols.size(); }
	bool operator ==(const Set& s) const { return symbols == s.symbols; }
	bool operator !=(const Set& s) const { return symbols != s.symbols; }

	Set overlap(const Set& s) const {
		Set res;
		for (typename set<T>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
			if (symbols.find(*it) != symbols.end())
				res.addToSet(*it);
		return res;
	}

	friend istream& operator >>(istream& in, Set& s) {
		T c;
		in >> c;
		s.symbols.insert(c);
		return in;
	}
	friend ostream& operator <<(ostream& out, const Set& s) {
		for (typename set<T>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
			out << *it<<"|";
		return out;
	}
};