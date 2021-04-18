#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>


using namespace std;


stack<int> operands;
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
		case'(':
		case')':
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

	int count = 0;
	for(int i=0; i<tokens.size(); i++) {
		cout << i << endl;
		if(isOperand(tokens[i])) {
			cout << i << " in isOperand" << endl;
			operands.push(stoi(tokens[i]));
			cout << i << " in isOperand2" << endl;
		} else if(tokens[i] == "(") {
			ops.push('(');
		} else if(tokens[i] == ")") {

			while(!ops.empty() && ops.top() != '(') {
				int v1, v2;
				char op;

				v1 = operands.top();
				operands.pop();
				v2 = operands.top();
				operands.pop();
				op = ops.top();
				ops.pop();

				if(count == 0) {
					postfix += to_string(v2);
				}

				postfix += to_string(v1);
				postfix += " ";
				// cout << postfix << endl;
				postfix[postfix.length()-1] = op;

				int res = result(v2, v1, op);
				cout << res << endl;
				operands.push(res);
				count++;
			}
			
			if(!ops.empty()) {
				ops.pop();
			}
		} else if(isOperator(tokens[i])) {
			// cout << i << endl;
			if(ops.empty() || ops.top() == '(') {
				ops.push(tokens[i][0]);
			} else {

				while(!ops.empty() && ops.top() != '(' && preced(tokens[i][0]) <= 
															preced(ops.top())) {
					int v1, v2;
					char op;

					v1 = operands.top();
					operands.pop();
					v2 = operands.top();
					operands.pop();
					op = ops.top();
					ops.pop();

					if(count == 0) {
						postfix += to_string(v2);
					}

					postfix += to_string(v1);
					postfix += " ";
					postfix[postfix.length()-1] = op;

					int res = result(v2, v1, op);
					operands.push(res);
					count++;
					// cout << res << endl;
				}

				ops.push(tokens[i][0]);
			}
		}

	}

	cout << "last step" << endl;

	while(!ops.empty()) {
		cout << "opssize : " << ops.size() << endl;
		int v1, v2;
		char op;

		cout << "opersize:" << operands.size() << endl;
		v1 = operands.top();
		operands.pop();
		cout << v1 << endl;
		v2 = operands.top();
		operands.pop();
		cout << v2 << endl;
		op = ops.top();
		ops.pop();
		cout << "op:" << op << endl;

		if(count == 0) {
			postfix += to_string(v2);
		}

		postfix += to_string(v1);
		postfix += " ";
		postfix[postfix.length()-1] = op;

		int res = result(v2, v1, op);
		// cout << res << endl;
		operands.push(res);
		count++;
	}
}




int main(int argc, char const *argv[])
{

	string post = "";
	// post += 5;
	// // post += 3;
	// // post += " ";
	// // post[post.length()-1] = '*';
	vector<string> line = { "12", "+", "3", "*", "5"};
	compute(line, post);
	cout << operands.top() << endl;
	cout << post << endl;
	return 0;
}