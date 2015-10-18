#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

enum TYPE{BOOKS,FOOD,MEDICAL,OTHERS}; //the type of the sales.

map<string,TYPE> goods_map;

class Goods{
private:
	TYPE type;
	bool imported;
	float price;
	string str_o;
	float taxes;
	int number;
public:
	Goods(string str){
		taxes = 0.0;
		/* find the number of the goods */
		sscanf(str.c_str(),"%d",&number);

		/* judge whether imported or not */
		if(str.find(" imported ") != string::npos)
			imported = true;
		else
			imported = false;

		/* find the price of the sales */
		int found_at = str.find(" at ");
		int n = str.size() - found_at - 3;
		sscanf(str.substr(found_at+3,n).c_str(),"%f",&price);

		/*  the additional sales of imported goods */
		if(imported)
			taxes += price * 0.05;

		/* find the name of sales */
		int found_s = 0;
		if(imported){
			int found_1 = 0,found_2 = 0;
			found_1 = str.find(" of ") + 3;
			found_2 = str.find(" imported ") + 9;
			found_s = found_1>found_2?found_1:found_2;
		}
		else{
			int found = 0;
			found_s = str.find(" ");
			if((found=str.find(" of ")) != string::npos)
				found_s = found + 3;
		}
		string name = str.substr(found_s+1,found_at-found_s-1);

		/* the basic sales tax */
		map<string,TYPE>::iterator it;
		it = goods_map.find(name);
		if(it != goods_map.end()){
			if((*it).second == OTHERS)
				taxes += price * 0.1;
		}
		
		/* assemble the output string */
		price += taxes;
		str_o = str.substr(0,found_at) + ":";
		ostringstream buffer;
		buffer<<setiosflags(ios::fixed)<<setprecision(2)<<price;
		str_o += buffer.str();
	}
	float get_price(){
		return price;
	}
	float get_taxes(){
		return taxes;
	}
	string get_str_o(){
		return str_o;
	}
};

/*
 * init the map of goods_map.
 * 用来查询物品的类型
 */
void init(){
	goods_map.insert(make_pair("book",BOOKS));
	goods_map.insert(make_pair("music CD",OTHERS));
	goods_map.insert(make_pair("chocolate bar",FOOD));
	goods_map.insert(make_pair("chocolates",FOOD));
	goods_map.insert(make_pair("perfume",OTHERS));
	goods_map.insert(make_pair("headache pills",MEDICAL));
}

int main(){
	init();
	string str;
	vector<Goods> gds;
	/* input the string for stdin */
	while(getline(cin,str)){
		gds.push_back(Goods(str));
	}

	float taxes = 0.0;
	float total = 0.0;
	int size = gds.size();
	/* output the last price of every piece of goods */
	for(int i=0; i<size; i++){
		cout<<gds[i].get_str_o()<<endl;
		taxes += gds[i].get_taxes();
		total += gds[i].get_price();
	}
	
	/* output the taxes and total */
	cout<<setiosflags(ios::fixed)<<setprecision(2);
	cout << "Sales Taxes:" << taxes << endl;
	cout << "Total:" << total << endl;

	return 0;
}