int isParenthesisRight(char c);
int isParenthesisLeft(char c);
int isValid(char c);
char * intToString(int n);
void print_answer(double n);
int isDigit(int c);
int isOperator(char c);
void get_expression();
void calculator_main();
void calculate(double * resp);
void pushToOperatorStack(char op);
void pushToNumStack(double n);
char popOperatorStack();
void popNumStack(double * num);