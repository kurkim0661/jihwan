#include<iostream>
#include<algorithm>
#include<vector>
 
using namespace std;
 
int clocks[12];

int pressButton(int buttonNum, int Time){

	//스위치의 효과들. 첫번째는 몇개의 시계를 움직이는가의 수
	int button[10][6] = 
	{
		{3,0,1,2},
		{4,3,7,9,11},
		{4,4,10,14,15},
		{5,0,4,5,6,7},
		{5,6,7,8,10,12},
		{4,0,2,14,15},
		{3,3,14,15},
		{5,4,5,7,14,15},
		{5,1,2,3,4,5},
		{5,3,4,5,9,13}
	};

	int pressTime = (4-Time)%4;//필요한 클릭수



	for(int i=1;i<=button[buttonNum][0];i++){

		clocks[button[buttonNum][i]] += pressTime;//누르는 횟수만큼 더하고
		clocks[button[buttonNum][i]]%=4;//4(12시)넘은건 버린다

	}

	//cout << "press " << buttonNum << " " <<  pressTime << " times" << endl;
	/*for(int i=0;i<16;i++){
		if(clocks[i] == 0)
		cout << 12 << " ";
		else
		cout << clocks[i]*3 << " ";
	}
	cout << endl;
	cout << endl;*/

	return pressTime;


}

int countPressButton(){

	int pressCnt=0;
	/*
	버튼		조건
4	n8	a8=a12
1	n11	
9	n13	n9=n13
2	n10	
3	n6	
7	n7	
8	n4	n4=n5
0	n1	
5	n2	n0=n2
6	n3	n3=n14=n15


	*/

	if(clocks[8] != clocks[12])
		return -1;

	pressCnt += pressButton(4, clocks[8]);
	pressCnt += pressButton(1, clocks[11]);
	
	if(clocks[9] != clocks[13])
		return -1;

	pressCnt += pressButton(9, clocks[13]);
	pressCnt += pressButton(2, clocks[10]);
	pressCnt += pressButton(3, clocks[6]);
	pressCnt += pressButton(7, clocks[7]);
	
	if(clocks[4] != clocks[5])
		return -1;

	pressCnt += pressButton(8, clocks[4]);
	pressCnt += pressButton(0, clocks[1]);

	if(clocks[0] != clocks[2])
		return -1;

	pressCnt += pressButton(5, clocks[2]);

	
	if((clocks[3] != clocks[14]) || (clocks[3] != clocks[15]) || (clocks[14] != clocks[15]) )
		return -1;

	pressCnt += pressButton(6, clocks[3]);



	return pressCnt;	
}

int main(){
    ios::sync_with_stdio(false);
 
    int TC;
 
    //테스트 케이스
    cin >> TC;
 
	int tmp;
	int clockNum;

    while(TC--){
		for(int clockNum = 0 ; clockNum < 16 ; clockNum++){
		
			cin >> tmp;
			switch(tmp){
			case 3:clocks[clockNum]=1;break;
			case 6:clocks[clockNum]=2;break;
			case 9:clocks[clockNum]=3;break;
			case 12:clocks[clockNum]=0;break;
			}
			
		}
	cout << countPressButton() << endl;
 
    }

 
    return 0;
}
