#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>


using namespace std;


stack<char> ops;

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

bool isOperand(const string& token) {
	 for (char const &c : token) {
        if (isdigit(c) == 0) {
        	return false;
    	}
    }
    return true;
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



void compute(vector<string>& tokens, string& postfix) {

	char op;
	for(int i=0; i<tokens.size(); i++) {
		if(isOperand(tokens[i])) {
			postfix += tokens[i];
		} else if(tokens[i] == "(") {
			ops.push('(');
		} else if(tokens[i] == ")") {

			while(!ops.empty() && ops.top() != '(') {

				op = ops.top();
				ops.pop();

				postfix += " ";
				postfix[postfix.length()-1] = op;

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

					postfix += " ";
					postfix[postfix.length()-1] = op;

				}

				ops.push(tokens[i][0]);
			}
		}

	}


	while(!ops.empty()) {

		op = ops.top();
		ops.pop();

		postfix += " ";
		postfix[postfix.length()-1] = op;

	}
}




int main(int argc, char const *argv[])
{

	string post = "";

	vector<string> line = { "(", "12", "-", "10", ")", "*", "(", "1", "-" , "3", ")"};
	compute(line, post);
	cout << post << endl;
	return 0;
}