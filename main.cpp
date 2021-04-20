#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>


using namespace std;


stack<char> ops;
vector<string> tokens;
map<string, bool> isThereAVariable;
string type = "";
int lastRand = 0;

int preced(char c) {
	switch(c) {

		case'+':
		case'-':
			return 0;
		case'*':
		case'/':
			return 1;
		default:	return -1;

	}
}


bool isOperator(string token) {
	if(token.length() != 1) {
		return false;
	}

	char c = token[0];
	switch(c) {
		case'+':
		case'-':
		case'*':
		case'/':
			return true;
			break;
		default: 
			return false;
			break;

	}
}

string randomVarGen() {
	string temp = "randomVar";
	bool isThere = true;
	while(isThere) {
		string str = temp + to_string(lastRand);
		if(isThereAVariable[str]) {
			lastRand++;
		} else {
			temp = str;
			isThereAVariable[temp] = true;
			cout << "Define " << temp << " as 0" << endl;
			isThere = false;

		}
	}

	return temp;

}

bool isOperand(const string& token) {
	 for (char const &c : token) {
        if (isdigit(c) == 0) {
        	return false;
    	}
    }
    return true;
}

bool isOp(char c) {
	switch(c) {
		case'(':
			return true;
		case')':
			return true;
		case'+':
			return true;
		case'-':
			return true;
		case'*':
			return true;
		case'/':
			return true;
		case'=':
			type = "expression";
			return true;
		default:
			return false;
	}
}

int result(int a, int b, char c) {
	switch(c) {
		case'+':
			return a+b;
		case'-':
			return a-b;
		case'*':
			return a*b;
		case'/':
			return a/b;
	}
}

void compute(vector<string>& operation, string var) {
	queue<string> proceed;
	stack<string> keep;

	for(int i=0; i<operation.size(); i++) {
		proceed.push(operation[i]);
	}


	while(!proceed.empty()) {
		string s = proceed.front();
		proceed.pop();

		if(isOperator(s)) {
			string v1 = keep.top();
			keep.pop();
			string v2 = keep.top();
			keep.pop();
			
			string opr = randomVarGen();
			cout << opr << " = " << v2 << " " << s << " " << v1 << endl;
			keep.push(opr);
		}	else {
			keep.push(s);
		}
	}


	cout << var << " = " << keep.top() << endl;

}

void to_postfix(vector<string>& tokens) {
	vector<string> operation;

	char op;
	string str;

	for(int i=2; i<tokens.size(); i++) {
		if(isOperand(tokens[i])) {
			operation.push_back(tokens[i]);
		} else if(tokens[i] == "(") {
			ops.push('(');
		} else if(tokens[i] == ")") {

			while(!ops.empty() && ops.top() != '(') {

				op = ops.top();
				ops.pop();

				str += " ";
				str[str.length()-1] = op;
				operation.push_back(str);
				str="";

			}
			
			if(!ops.empty()) {
				ops.pop();
			}
		} else if(isOperator(tokens[i])) {

			if(ops.empty() || ops.top() == '(') {
				ops.push(tokens[i][0]);
			} else {

				while(!ops.empty() && ops.top() != '(' && preced(tokens[i][0]) <= 
															preced(ops.top())) {

					op = ops.top();
					ops.pop();

					str += " ";
					str[str.length()-1] = op;
					operation.push_back(str);
					str="";

				}

				ops.push(tokens[i][0]);
			}
		}

	}


	while(!ops.empty()) {

		op = ops.top();
		ops.pop();

		str += " ";
		str[str.length()-1] = op;
		operation.push_back(str);
		str = "";

	}
	compute(operation, tokens[0]);
}

void tokenize(string line) {
	string str;

	for(int i=0; i<line.length(); i++) {

		if(line[i] == '#') {

			break;
		}
		switch(line[i]) {
			case'\t':
			case'\n':
				continue;

		}

		if(line[i] == ' ') {

			if(str == "") {
			} else {
				tokens.push_back(str);
				str = "";
			}
			continue;
		} else if(isOp(line[i])) {

			if(str != "") {
				tokens.push_back(str);
			}

			str = " ";
			str[0] = line[i];
			tokens.push_back(str);

			str = "";
			continue;
		} else {
			str += " ";
			str[str.length()-1] = line[i];
		}


	}

	if(str != "") {
		tokens.push_back(str);
	}
}

bool checkVar(string var_name) {
	if(!isThereAVariable[var_name]) {
		cout << "Define " << var_name << " as 0" << endl;
		isThereAVariable[var_name] = true;
		return false;
	} else {
		cout << "Error!" << endl;
		return true;
	}
}


void assign(vector<string>& tokens) {
	bool check;
	if(tokens.size() == 1) {
		check = checkVar(tokens[0]);
		if(check) {
			return;
		} 
	} else if(tokens.size() == 2) {
		cout << "Error!" << endl;
		return;
	} else {
		if(tokens[1] != "=") {
			cout << "Error!" << endl;
			return;
		} else {
			check = checkVar(tokens[0]);
			if(check) {
				return;
			}

			to_postfix(tokens);


		}
	}
}


int main(int argc, char const *argv[])
{


	string line = "a = 12  -  10  * (1-3) ";
	cout << "line is : " << line << endl;

	for (int i = 0; i < 1; ++i)	{
		tokenize(line);

		if(type == "expression" || type == "") {
			assign(tokens);
		}


	}


	return 0;
}