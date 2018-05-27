#include"krcard.h"
void KrCard::NumUpdate (){
	if(currtime.Month(starttime)){
		if(currtime.Day(starttime)){ 
			num=1;//月末重置num
			starttime.update();//更新月份 
			}
		else num++; 
	}
	else{
		starttime=currtime;
		num=1;
	}
}

void stucard::KrByBus(KrDate c,KrBus& k){
	currtime=c;
	if(!KrPrint1()) return;
	NumUpdate ();
	if(k.numpeople>=k.people){
		cout<<"The number of people is full,you can't ride\n";
		cout<<"--------------------------\n";return;
	}
	else k.numpeople++;
	
	balance-=2;
	
	KrPrint2();
}

void teacard::KrByBus(KrDate c,KrBus& k){
	currtime=c;
	NumUpdate ();
	if(k.numpeople>=k.people){
		cout<<"The number of people is full,you can't ride\n";
		cout<<"--------------------------\n";
		return;
	}
	else k.numpeople++;
	
	KrPrint2();
}

void limcard::KrByBus(KrDate c,KrBus& k){
	currtime=c;
	if(k.numpeople>=k.people){
		cout<<"The number of people is full,you can't ride\n";
		cout<<"--------------------------\n";return;
	}
	else k.numpeople++;
	
	if(num>20) if(!KrPrint1()) return ;
	NumUpdate ();
	
	if(num<20) ;
	else if(num==20) cout<<"This is your last free ride\n";
	else if(num>20) balance-=2;
	
	KrPrint2();
}

int KrCard::cardnum[3]={2,1,0};
int KrDate::Yue[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int KrBus::ontime[2]={0,0};
