#ifndef EXCEPTII_H_
#define EXCEPTII_H_
#include <string>

using std::string;

class RepoExceptii {
private:

	string msg;

public:

	RepoExceptii(const string& m) : msg{ m } {

	}

	string getMesage() const {
		return msg;
	}

	~RepoExceptii() = default;

};

class ValidatorExceptii {
private:

	string msg;

public:
	ValidatorExceptii(const string& m) : msg{ m } {

	}
	string getMesage() const {
		return msg;
	}

	~ValidatorExceptii() = default;
};

class RetetaExceptii {
private:

	string msg;

public:

	RetetaExceptii(const string& ot) : msg{ ot } {

	}

	string getMesage() const {
		return msg;
	}

	~RetetaExceptii() = default;
};

#endif // !EXCEPTII_H_
