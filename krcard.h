#ifndef KRCARD_H
#define KRCARD_H
#include"krbus.h"

class KrDate{
private:	
	int year;
	int month;
	int day;
	static int Yue[12];
public:
	KrDate(int y,int m,int d):year(y),month(m),day(d) {};
	KrDate& operator=(const KrDate& c){
		year=c.year; month=c.month; day=c.day;
		return *this;
	};
	friend ostream& operator<<(ostream& os,KrDate& kr){
		os<<kr.year<<"."<<kr.month<<"."<<kr.day;
		return os;
	};
	int Month(KrDate s){
		if(month==s.month&&year==s.year) return 1;
		return 0;
	};
	int Day(KrDate s){
		if(day==Yue[s.month]) return 1;
		return 0;
	}
	KrDate& update(){
		month++;
		day=1;
		return *this;
	}
};

class KrCard{
protected:	
	string name;  //持卡人姓名 
	string id;    //一卡通编号
	string unit;  //所属单位
	
	int balance;  //卡内余额
	int num;  //累计本月乘车次数 
	
	KrDate firsttime;  //办卡时间，用于表示有效期
	KrDate endtime;  //有效期截止日期 
	KrDate currtime;  //当前日期，默认刷卡时从读卡机得到 
	KrDate starttime;  //本月起始日期，用于更新月份 
	
	static int cardnum[3];  //分别储存三种卡的数量
	
public:
	class Bad_KrCard{};
	
	KrCard(string n,string i,int y,int m,int d,int b=0):firsttime(y,m,d),currtime(y,m,d),starttime(y,m,d),endtime(y+4,m,d){
		name=n; id=i; unit="XDU"; balance=b; num=0;
	};
	
	bool KrPrint1(){
		if(balance<2){
			cout<<endl<<"Insufficient balance, not allowed to ride\n";
			KrPrint2();
			return false;
		}
		if(balance>=2&&balance<=5){
			cout<<"The balance is too low, please recharge in time\n";
			return true;
		}
		if(balance>5) return true;
	}
	
	void KrPrint2(){
		cout<<endl;
		cout<<"Name: "<<name<<endl<<"ID: "<<id<<endl<<"Unit: "<<unit<<endl;
		cout<<"Your Balance: "<<balance<<endl<<"Your number of rides: "<<num<<endl;
		cout<<"Your card is valid for ";
		cout<<firsttime;
		cout<<"——";
		cout<<endtime;
		cout<<endl<<"----------------------------"<<endl;
	};
	
	virtual void KrByBus(KrDate c,KrBus& k)=0;
	
	void NumUpdate();
};

class stucard:public KrCard{  //学生卡 
public:
	stucard(string n,string i,int y,int m,int d,int b=0):KrCard(n,i,y,m,d,b){
		cardnum[0]++;
		if(!(cardnum[0]>cardnum[1]&&cardnum[1]>cardnum[2]))
			throw Bad_KrCard();
	};
	
	void KrByBus(KrDate c,KrBus& k);
};

class teacard:public KrCard{  //教师卡 
public:
	teacard(string n,string i,int y,int m,int d,int b=0):KrCard(n,i,y,m,d,b){
		cardnum[1]++;
		if(!(cardnum[0]>cardnum[1]&&cardnum[1]>cardnum[2]))
			throw Bad_KrCard();
	};
	
	void KrByBus(KrDate c,KrBus& k);
};

class limcard:public KrCard{  //限制卡 
public:
	limcard(string n,string i,int y,int m,int d,int b=0):KrCard(n,i,y,m,d,b){
		cardnum[2]++;
		if(!(cardnum[0]>cardnum[1]&&cardnum[1]>cardnum[2]))
			throw Bad_KrCard();
	};
	
	void KrByBus(KrDate c,KrBus& k);
};


#endif
