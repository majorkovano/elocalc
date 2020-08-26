#include "common.h"

using namespace std;

void deltrailspace(string& str){
	int i = 0;
	string nstr;
	while (i != str.size() && !isspace(str[i])){
		nstr+=str[i];
		i++;
	}
	str = nstr;
 }
