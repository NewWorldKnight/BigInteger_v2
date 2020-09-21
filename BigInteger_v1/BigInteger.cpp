//William Becker
//Fall 2020
//Advanced C++
//BigInteger Version 1

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>


using namespace std;

//Prototypes
void help();
vector<int> toDigits(string);
int valueOf(char);
void displayDecimalDigits(vector<int>);
vector<int> trimLeadingZeros(vector<int>);
vector<int> addLeadingZeros(vector<int>, int);
vector<int> normalize(vector<int>, int = 10);
vector<int> add(vector<int>, vector<int>);

//Constants


//Full scope Variables
string bigInt_1s, bigInt_2s, opperand;
int baseNumber;

int main(int argc, char* argv[]) {
	cout << "Welcome to Big Integer version 1" << endl << endl;
	if (argc == 1) {
		cout << "Please Enter a bigInt String:" << endl;
		cin >> bigInt_1s;
		cout << "Please Enter a bigInt String:" << endl;
		cin >> bigInt_2s;
		cout << "Please Enter an opperator" << endl;
		cin >> opperand;
		cout << "Please Enter the base number:" << endl;
		cin >> baseNumber;
		//TODO USer input
	}
	if (argc >= 2) {
		bigInt_1s = argv[1];
		if (bigInt_1s == "help") {
			help();
			return EXIT_SUCCESS;
		}
	}
	if (argc >= 3) {
		if (argc == 3) {
			bigInt_2s = argv[2];
		}
	}
	if (argc >= 4) {
		opperand = argv[3];
	}
	if (argc >= 5) {
		baseNumber = stoi(argv[4]);
	}
	if (argc > 6) {
		cout << "Error! Too many Arguments given! Terminating program!" << endl;
		cout << "Uses argument \"help\" for a list of Usable Arguments" << endl;
		return EXIT_FAILURE;
	}
	vector<int> bigInt_1 = toDigits(bigInt_1s);
	bigInt_1 = trimLeadingZeros(bigInt_1);
	displayDecimalDigits(bigInt_1);
	cout << "+" << endl;
	vector<int> bigInt_2 = toDigits(bigInt_2s);
	bigInt_2 = trimLeadingZeros(bigInt_2);
	displayDecimalDigits(bigInt_2);
	cout << "=" << endl;
	vector<int> result = add(bigInt_1, bigInt_2);
	displayDecimalDigits(result);

	return EXIT_SUCCESS;
}

void help() {
	cout << "The following Arguments are avaliable for this program:" << endl << endl;
	cout << "BigIntNumber_1 \t BigIntNumber_2 \t MathOperand \t BaseNumber" << endl;
	cout << "BigIntNumber_1 \t BigIntNumber_2 \t MathOperand" << endl;
	cout << "BigIntNumber_1 \t BaseNumber" << endl;
	cout << "BigIntNumber_1" << endl;
	cout << "help" << endl << endl;
	cout << "BaseNumber_1 and BaseNumber_2 are any number in a continuous string, possitive or negative." << endl;
	cout << "MathOperand is any ONE of the following: +, -, /, *, or %" << endl;
	cout << "BaseNumber is any base number 2 to 36, inclusively." << endl;
	cout << "help displays this message." << endl << endl;
}

vector<int> toDigits(string s) {
	vector<int> result(s.length());
	for (unsigned int i = 0; i < result.size(); i++) {
		result[i] = valueOf(s[i]);
	}
	return result;
}

int valueOf(char c) {
	if (isdigit(c)) {
		return c - '0';
	}
	if (isalpha(c)) {
		c = toupper(c);
		return 10 + (c - 'A');
	}
	else {
		cout << "ERROR! Attempted to convert " << c << " to a digit!" << endl;
		cout << c << " is out of this programs scope" << endl;
		return NAN;
	}
}

void displayDecimalDigits(vector<int> a) {
	for (unsigned int i = 0; i < a.size(); ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
}

vector<int> trimLeadingZeros(vector<int> v) {
	int count = 0;
	for (unsigned int i = 0; i < v.size(); i++) {
		if (v[i] == 0) {
			++count;
		}
		else {
			break;
		}
	}
	vector<int> result(v.size() - count);
	for (unsigned int i = count, r = 0; i < v.size(); r++, i++) {
		result[r] = v[i];
	}
	return result;
}

vector<int> addLeadingZeros(vector<int> v, int count = 1) {
	vector<int> result(v.size() + count);
	for (int i = 0; i < count; i++)
	{
		result[i] = 0;
	}
	for (int i = 0; i < v.size(); i++)
	{
		result[i + count] = v[i];
	}
	return	result;
}

vector<int> normalize(vector<int> v, int b) {
	vector<int> result = v;
	result = addLeadingZeros(result, 1);
	for (int i = result.size() - 1; i >= 0; --i) {
		while (result[i] >= b) {
			result[i] -= b;
			result[i - 1] += 1;
		}
	}
	trimLeadingZeros(v);
	return result;
}

vector<int> add(vector<int> v1, vector<int> v2) {
	vector<int> result;
	if (v1.size() >= v2.size()) {
		result = v1;
		v2 = addLeadingZeros(v2, (v1.size() - v2.size()));
	}
	else {
		result = v1;
		v1 = addLeadingZeros(v1, (v2.size() - v1.size()));
	}
	for (int i = 0; i < v1.size(); i++) {
		result[i] = v1[i] + v2[i];
	}
	if (baseNumber != NAN) {
		result = normalize(result, baseNumber);
	}
	else {
		result = normalize(result);
	}
	result = trimLeadingZeros(result);
	return result;
}