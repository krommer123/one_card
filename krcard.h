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
	string name;  //�ֿ������� 
	string id;    //һ��ͨ���
	string unit;  //������λ
	
	int balance;  //�������
	int num;  //�ۼƱ��³˳����� 
	
	KrDate firsttime;  //�쿨ʱ�䣬���ڱ�ʾ��Ч��
	KrDate endtime;  //��Ч�ڽ�ֹ���� 
	KrDate currtime;  //��ǰ���ڣ�Ĭ��ˢ��ʱ�Ӷ������õ� 
	KrDate starttime;  //������ʼ���ڣ����ڸ����·� 
	
	static int cardnum[3];  //�ֱ𴢴����ֿ�������
	
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
		cout<<"����";
		cout<<endtime;
		cout<<endl<<"----------------------------"<<endl;
	};
	
	virtual void KrByBus(KrDate c,KrBus& k)=0;
	
	void NumUpdate();
};

class stucard:public KrCard{  //ѧ���� 
public:
	stucard(string n,string i,int y,int m,int d,int b=0):KrCard(n,i,y,m,d,b){
		cardnum[0]++;
		if(!(cardnum[0]>cardnum[1]&&cardnum[1]>cardnum[2]))
			throw Bad_KrCard();
	};
	
	void KrByBus(KrDate c,KrBus& k);
};

class teacard:public KrCard{  //��ʦ�� 
public:
	teacard(string n,string i,int y,int m,int d,int b=0):KrCard(n,i,y,m,d,b){
		cardnum[1]++;
		if(!(cardnum[0]>cardnum[1]&&cardnum[1]>cardnum[2]))
			throw Bad_KrCard();
	};
	
	void KrByBus(KrDate c,KrBus& k);
};

class limcard:public KrCard{  //���ƿ� 
public:
	limcard(string n,string i,int y,int m,int d,int b=0):KrCard(n,i,y,m,d,b){
		cardnum[2]++;
		if(!(cardnum[0]>cardnum[1]&&cardnum[1]>cardnum[2]))
			throw Bad_KrCard();
	};
	
	void KrByBus(KrDate c,KrBus& k);
};


#endif
