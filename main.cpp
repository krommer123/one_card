#include"krcard.h"
int main(){
	stucard xs1("LiMing","001",2018,5,14,100);
	stucard xs2("WangMei","002",2017,5,14);
	stucard xs3("FanTianning","003",2018,5,13,3);
	
	teacard ls1("Mr.li","004",2016,5,13,100);
	teacard ls2("Mr.wang","005",2016,5,13);
	
	limcard xz1("Arch0n","006",2018,4,22,5);
	
	KrDate now(2018,5,21);//当前时间
	
	KrBus kr1(3,"1000",3,8,0,0,18,0,0,8,0,0,18,0,0) ; 
	//一共有三辆车，其中1000号车能坐3个人 
	//车运行时段从早上八点到下午六点，应在八点出发，下午六点到达
	KrBus kr2(3,"2000",2,6,0,0,15,0,0,6,0,0,15,0,0) ;
	KrBus kr3(3,"3000",100,6,0,0,17,0,0,6,0,0,17,0,0) ;
	
	KrTime a1(15,10,6); KrTime a2(16,20,36);
	KrTime f1(6,0,0); KrTime f2(8,0,0);
	
	xs1.KrByBus(now,kr1);
	xs2.KrByBus(now,kr1);
	xs3.KrByBus(now,kr1);
	ls1.KrByBus(now,kr1);
	ls2.KrByBus(now,kr1);
	xz1.KrByBus(now,kr2);
	
	kr1.running1(a1,f1); kr1.running2();
	kr2.running1(a2,f2); kr2.running2();
	
	for(int i=1;i<=21;i++) xz1.KrByBus(now,kr3);
	kr3.running1(a2,f2); kr3.running2();
	
	KrDate now2(2018,6,21);
	ls1.KrByBus(now2,kr3);
	ls1.KrByBus(now2,kr3);
	
	return 0;
}
