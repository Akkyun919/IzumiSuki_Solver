#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

#define NW 5000

int Oishi;
int Izumi[7]={0,0,1,4,1,2,3};
int Suki[10002][7][7];

string OishiIzumiShuki[10002][7][7];

bool slv(int tar,int left,int right){
	if(tar<-3000 || 3000<tar)return(false);
	if(Suki[tar+NW][left][right]!=-1)return(Suki[tar+NW][left][right]);

	if(left==right){
		if(tar == Izumi[left]){
			return(Suki[tar+NW][left][right] = true);
		}
		else{
			return(Suki[tar+NW][left][right] = false);
		}
	}

	bool ret = false;
	for(int i=left;i<right && !ret;i++){
		// +
		for(int t=-tar;t<=tar && !ret;t++){
			if(slv(t,left,i) & slv(tar-t,i+1,right)){
				OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[t+NW][left][i] + '+' + OishiIzumiShuki[tar-t+NW][i+1][right] + ')';
				ret = true;
			}
		}
		// -
		// need check
		for(int t=0;t<=50 && !ret;t++){
			if(slv(tar+t,left,i) & slv(t,i+1,right)){
				OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[tar+t+NW][left][i] + '-' + OishiIzumiShuki[t+NW][i+1][right] + ')';
				ret = true;
			}
		}
		// *
		if(tar==0){
			for(int t=0;t<=100 && !ret;t++){
				if(slv(0,left,i) & slv(t,i+1,right)){
					OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[0+NW][left][i] + '*' + OishiIzumiShuki[t+NW][i+1][right] + ')';
					ret = true;
				}
				if(slv(t,left,i) & slv(0,i+1,right)){
					OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[t+NW][left][i] + '*' + OishiIzumiShuki[0+NW][i+1][right] + ')';
					ret = true;
				}
			}
		}
		else{
			for(int t=1;t<=tar && !ret;t++){
				if(tar%t==0){
					if(slv(t,left,i) & slv(tar/t,i+1,right)){
						OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[t+NW][left][i] + '*' + OishiIzumiShuki[tar/t+NW][i+1][right] + ')';
						ret = true;
					}
				}
			}
		}
		// /
		if(tar!=0){
			for(int t=1;t<=10 && !ret;t++){
				if(slv(tar*t,left,i) & slv(t,i+1,right)){
					OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[tar*t+NW][left][i] + '/' + OishiIzumiShuki[t+NW][i+1][right] + ')';
					ret = true;
				}
			}
		}
		// ^
		if(tar==0){
			for(int t=1;t<=1000;t++){
				if(slv(0,left,i) & slv(t,i+1,right)){
					OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[0+NW][left][i] + '^' + OishiIzumiShuki[t+NW][i+1][right] + ')';
					ret = true;
				}
			}
		}
		else if(tar==1){
			for(int t=0;t<=1000;t++){
				if(slv(t,left,i) & slv(0,i+1,right)){
					OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[t+NW][left][i] + '^' + OishiIzumiShuki[0+NW][i+1][right] + ')';
					ret = true;
				}
				if(slv(1,left,i) & slv(t,i+1,right)){
					OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[1+NW][left][i] + '^' + OishiIzumiShuki[t+NW][i+1][right] + ')';
					ret = true;
				}
			}
		}
		else{
			for(int t=2;t<=tar;t++){
				int p=tar,f=0;
				while(p%t==0){
					p/=t;f++;
				}
				if(p==1){
					if(slv(t,left,i) & slv(f,i+1,right)){
						OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[t+NW][left][i] + '^' + OishiIzumiShuki[f+NW][i+1][right] + ')';
						ret = true;
					}
				}
			}
		}
		// !
		if(2<tar){
			int kai=1,mat;
			for(mat=2;kai<tar;mat++){
				kai*=mat;
			}
			mat--;
			if(kai==tar){
				if(slv(mat,left,right)){
					OishiIzumiShuki[tar+NW][left][right] = '(' + OishiIzumiShuki[mat+NW][left][right] + '!' + ')';
				}
			}
		}
	}

	Suki[tar+NW][left][right] = ret ? 1 : 0;
	return(ret);
}

int main(){

	// Init
	for(int nm=0;nm<=10000;nm++){
		for(int i=0;i<7;i++){
			for(int j=0;j<7;j++){
				Suki[nm][i][j] = -1;
				OishiIzumiShuki[nm][i][j]="";
			}
		}
	}
	for(int i=0;i<7;i++){OishiIzumiShuki[Izumi[i]+NW][i][i] = Izumi[i]+'0';}

	for(Oishi=0;Oishi<=10000;Oishi++){
		// Solve
		if(slv(Oishi,0,6)){
			cout<<Oishi<<" : "<<OishiIzumiShuki[Oishi+NW][0][6]<<endl;
		}
		else{
			//cout<<"OishiIzumiShuki"<<endl;
		}
	}

	return(0);
}

/*
大石泉算のレギュレーション…？
並び替えなし、桁合成なし、四則演算と()、べき乗と階乗を使用可
0!=1,0^0=1と定義　でいいんじゃないですかね
*/