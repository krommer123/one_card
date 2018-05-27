#ifndef KRBUS_H
#define KRBUS_H
#include<iostream>
#include<string>
using namespace std;

class KrTime{
private:
	int hour,minute,second;
public:
	KrTime(int h=0,int m=0,int s=0):hour(h),minute(m),second(s){};
	
	double operator- (KrTime k){
		int h=0,m=0,s=0;
		if(second-k.second<0){s=60+second-k.second; m=-1;} 
			else s=second-k.second;
		if(minute-k.minute<0){m=60+minute-k.minute+m; h=-1; }
			else m=minute-k.minute+m;
		h=hour-k.hour+h;
		
		double hours; hours=h+(double)m/60+(double)s/3600;
		return hours;
	};	
	
	KrTime& operator=(const KrTime k){
		hour=k.hour; minute=k.minute; second=k.second;
		return *this;
	};
	
	bool operator<=(const KrTime k){
		if(hour<k.hour) return true;
		else if(hour==k.hour){
			if(minute<k.minute) return true;
			else if(minute==k.minute){
				if(second<=k.second) return true;
				else return false;
			}
			else return false;
		}
		else return false;
	};
	
	bool operator>=(const KrTime k){
		if(hour>k.hour) return true;
		else if(hour==k.hour){
			if(minute>k.minute) return true;
			else if(minute==k.minute){
				if(second>=k.second) return true;
				else return false;
			}
			else return false;
		}
		else return false;};
};

class KrShift{
public:	
	KrTime runtime,offtime;  //班车运行时段的开始与结束时间
	KrTime fromtime,arritime;  //班车应该离开和到达停车点的时间
	KrTime arrive;  //班车实际到达停车点的时间
	KrTime from;  //班车实际离开停车点的时间
	double hours; // 全程运行时间
	KrShift(int rh,int rm,int rs,int oh,int om,int os,int fh,int fm,int fs,int ah,int am,int as):runtime(rh,rm,rs),offtime(oh,om,os),fromtime(fh,fm,fs),arritime(ah,am,as){
		hours=offtime-runtime;
	};
	 
};

class KrBus{
	
private:
	string plate,model,dname;//车牌号,车型号，驾驶员姓名
	KrShift shift;//该班车的班次表
	int numbus; //班车总数，方便计算准时到达率
	static int ontime[2]; //准时到达与准时发车车数 
public:
	int people;//最大承载人数
	int numpeople;// 实际承载人数
	
	KrBus(int nb,string p,int n,int rh,int rm,int rs,int oh,int om,int os,int fh,int fm,int fs,int ah,int am,int as):shift(rh,rm,rs,oh,om,os,fh,fm,fs,ah,am,as){
		numbus=nb;plate=p; people=n; numpeople=0;
	}; 
	
	void running1(KrTime a,KrTime f){
		shift.arrive=a; shift.from=f;
		cout<<"----------------------------\n";
		cout<<plate<<" real:max : "<<((double)numpeople/people)*100<<"%\n";
		if(a<=shift.arritime) ontime[0]++;
		if(f<=shift.fromtime) ontime[1]++;
	}
	
	void running2(){
		cout<<"arrive on time: "<<((double)ontime[0]/numbus)*100<<"%\n";
		cout<<"from on time: "<<((double)ontime[1]/numbus)*100<<"%\n";
		cout<<"-----------------------------\n"; 
	}
};

#endif
