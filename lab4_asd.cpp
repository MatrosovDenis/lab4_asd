#include <iostream>
#include <fstream>
#include <fstream>
#include <cstdlib>

std::ifstream fin("input.txt");
std::ofstream fout;
typedef char base;

struct node {
	base info;
	node* lt;
	node* rt;
	node() {
		lt = NULL;
		rt = NULL;
	}
};

typedef node* binTree;

bool isNull(binTree);
base RootBT(binTree);
binTree Create(void);
binTree Left(binTree);
binTree Right(binTree);
binTree ConsBT(const base& x, binTree& lst, binTree& rst);
unsigned int sizeBT(binTree b);
void destroy(binTree&);
void outBT(binTree b);
void displayBT(binTree b, int n);

binTree EnterBinTreeFormula(std::string strBinTree, int position) {
	binTree left, right;
	int buf = 0;
	int counter = 0;
	while (!((strBinTree[position] == '*' || strBinTree[position] == '-' || strBinTree[position] == '+') && counter == 0)) {
		position++;
		if (strBinTree[position] == '(')
			counter++;
		else if ((strBinTree[position] == '*' || strBinTree[position] == '+' || strBinTree[position] == '-') && counter > 0) {
			counter--;
			position++;
			if (strBinTree[position] == '(') {
				counter++;
			}
		}
	}
	buf = position;
	int buf1 = buf;
	counter = 0;
	if (strBinTree[buf1 - 1] == ')') {
		buf1--;
		while (!((strBinTree[buf1] == '(') && counter == 0)) {
			buf1--;
			if (strBinTree[buf1] == ')') {
				counter++;
			}
			else if ((strBinTree[buf1] == '(') && counter > 0) {
				counter--;
				buf1--;
				if (strBinTree[buf1] == ')') {
					counter++;
				}
			}
		}
		left = EnterBinTreeFormula(strBinTree, buf1);
	}
	else {
		binTree p1;
		p1 = new node;
		p1->info = strBinTree[buf - 1];
		p1->lt = NULL;
		p1->rt = NULL;
		left = p1;
	}
	if (strBinTree[buf + 1] == '(') {
		right = EnterBinTreeFormula(strBinTree, buf + 1);
	}
	else {
		binTree p2;
		p2 = new node;
		p2->info = strBinTree[buf + 1];
		p2->lt = NULL;
		p2->rt = NULL;
		right = p2;
	}
	return ConsBT(strBinTree[position], left, right);
}

binTree ConsBT(const base& x, binTree& lst, binTree& rst) {
	binTree p;
	p = new node;
	if (p != NULL) {
		p->info = x;
		p->lt = lst;
		p->rt = rst;
		return p;
	}
	else {
		std::cerr << "Memory not enough\n";
		exit(1);
	}
}

void outBT(binTree b) {
	if (b != NULL) {
		fout << RootBT(b);
		outBT(Left(b));
		outBT(Right(b));
	}
	else
		fout << '/';
}

void displayBT(binTree b, int n) {
	if (b != NULL) {
		fout << ' ' << RootBT(b);
		if (!isNull(Right(b))) {
			displayBT(Right(b), n + 1);
		}
		else
			fout << std::endl;
		if (!isNull(Left(b))) {
			for (int i = 1; i <= n; i++)
				fout << "  ";
			displayBT(Left(b), n + 1);
		}
	}
}

unsigned int sizeBT(binTree b)
{
	if (isNull(b)) return 0;
	else return sizeBT(Left(b)) + sizeBT(Right(b)) + 1;
}

binTree Create() {
	return NULL;
}

bool isNull(binTree b) {
	return (b == NULL);
}

base RootBT(binTree b)
{
	if (b == NULL) { std::cerr << "Error: RootBT(null) \n"; exit(1); }
	else return b->info;
}

binTree Left(binTree b)
{
	if (b == NULL) { std::cerr << "Error: Left(null) \n"; exit(1); }
	else return b->lt;
}

binTree Right(binTree b)
{
	if (b == NULL) { std::cerr << "Error: Right(null) \n"; exit(1); }
	else return b->rt;
}

void destroy(binTree& b) {
	if (b != NULL) {
		destroy(b->lt);
		destroy(b->rt);
		delete b;
		b = NULL;
	}
}

bool isOperator(char op) {
	return (op == '+' ||
		op == '-' ||
		op == '*');
}

bool isNum(binTree bt) {
	bool result = true;
	if (isOperator(bt->info)) {
		bool tmp1 = isNum(bt->lt);
		bool tmp2 = isNum(bt->lt);
		if (tmp1 == false || tmp2 == false) result = false;
		return result;
	}
	else if (isalpha(bt->info)) return false;
	else return true;
}

int Operation(char oper, int op1, int op2) {
	if (oper == '+') return op1 + op2;
	if (oper == '-') return op1 - op2;
	if (oper == '*') return op1 * op2;
}

int calculate(binTree bt) {
	if (isNum(bt)) {
		if (isOperator(bt->info)) {
			return Operation(bt->info, calculate(bt->lt), calculate(bt->rt));
		}
		else {
			return bt->info - 48;
		}
	}
	else {
		std::cout << "Can't be calculated!";
	}
}

int main() {
	setlocale(LC_CTYPE, "rus");
	fout.open("result.txt");
	binTree binaryTree;
	std::string formula;
	fin >> formula;
	binaryTree = EnterBinTreeFormula(formula, 0);
	if (isNum(binaryTree)) {
		int res = calculate(binaryTree);
		std::cout << "Result of calculatin" << res;
	}
	else std::cout << "Can't be calculated!";
	return 0;
}