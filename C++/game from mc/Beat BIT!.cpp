#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

namespace GB {
	#define keydown(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
	#define downL ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1:0)
	#define downR ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 1:0)
	#define Get GetStdHandle(STD_OUTPUT_HANDLE)
	#define color(a) SetConsoleTextAttribute(Get,a)
	#define pgrey 7
	#define pblue 9
	#define pgreen 10
	#define pred 12
	#define pyellow 14
	#define pwhite 15
	#define iv inline void
	#define ib inline bool
	#define ii inline int
	#define rep(i,a,b) for(int i=(a); i<=(b); ++i)
	#define rrep(i,a,b) for(int i=(a); i>=(b); --i)
	inline char DtoHsu(int x) {return x<10?x^48:(x-9)^96;}	//dec to hex (single and unsigned)
	inline string DtoHu(int x) {string ret="00"; ret[0]=DtoHsu(x>>4), ret[1]=DtoHsu(x&15); return ret;}
	inline string DtoH(int x) {return x<0?DtoHu(x+256):DtoHu(x);}
	iv getxy(int &x, int &y) {
		POINT pt;
		HWND hwnd=GetForegroundWindow();
		GetCursorPos(&pt), ScreenToClient(hwnd,&pt);
		x=pt.y/16+1, y=pt.x/8+1;
	}
	iv mouse(int a) {
		HANDLE handle=Get;
		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(handle,&CursorInfo);
		CursorInfo.bVisible=a;
		SetConsoleCursorInfo(handle,&CursorInfo);
	}
	iv goxy(int x, int y) {
		COORD position = { y-1, x-1 };
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOut, position);
	}
	
	inline string freads(FILE *in) {
		string res=""; char c;
		while(!isalnum(c=fgetc(in))) ;
		while(isalnum(c)) res+=c, c=fgetc(in);
		return res;
	}
	ii fread(FILE *in) {
		int t=0, f=1; char c;
		while(!isdigit(c=fgetc(in))) f=c^45;
		while(isdigit(c)) t=t*10+(c^48), c=fgetc(in);
		return t;
	}
	iv fwrites(string s, FILE *in) {
		for(int i=0; s[i]; ++i) fputc(s[i], in);
	}
	iv writes(string s) {
		for(int i=0; s[i]; ++i) putchar(s[i]);
	}
	iv print(int c, string s) {
		color(c), writes(s), color(15);
	}
	inline string iturns(int x, int len) {
		string res="";
		if(x==0) res="0";
		while(x) res=char(x%10+48)+res, x/=10;
		while(res.size()<len) res+=' ';
		return res;
	}
	inline string cturns(char c, int len) {
		string res="";
		while(res.size()<len) res+=c;
		return res;
	}
	inline string sdown(string s) {
		for(int i=0; s[i]; ++i) if(isupper(s[i])) s[i]=tolower(s[i]);
		return s;
	}
	
	struct button {
		int u, d, l, r;
		button() {
			l=r=u=d=0;
		}
		button(int u, int d, int l, int r):
			u(u), d(d), l(l), r(r) {}
	};
	ii button_check(button q[], int siz, int px, int py) {
		for(int i=1; i<=siz; ++i) if(px>=q[i].u&&px<=q[i].d&&py>=q[i].l&&py<=q[i].r) return i;
		return -1;
	}
	iv sleep(int t) {
		t/=100;
		while(t--) {
			if(keydown(32)) {
				while(keydown(32)) ;
				return;
			}
			Sleep(90);
		}
	}
}
using namespace GB;

namespace BT {
	
	const int col[8]={0, pblue, pred, 13, pgreen, 11, 14, 15};
	const int MNLEN=28, typsiz=20;
	int LEN;
	
	int type[20];
	int retik;
	int nxttyp;
	int px=19, py=10;
	
	string bat;
	int pbat=0;
	
	ii back(int a) {
		return a%LEN;
	}
	
	iv show() {
		goxy(px, py-2);
		for(int p=pbat-2, c=-2; c<=MNLEN; c++, p++) {
			p=back(p);
			print(col[c<retik? 0: (bat[p]^48)]*16, " ");
		}
		goxy(px-1, py), print(pyellow, "||");
		goxy(px, py), print(pyellow+col[0<retik? 0: (bat[pbat]^48)]*16, "|");
		print(pyellow+col[1<retik? 0: (bat[pbat+1]^48)]*16, "|");
		goxy(px+1, py), print(pyellow, "||");
	}
	
	iv update_nxt(int tapd) {
		retik=0;
		for(int p=pbat, c=0; ; ++c, ++p) {
			p=back(p);
			if(c>tapd+1&&bat[p]!=48) {
				nxttyp=bat[p]^48;
				break;
			}
			retik++;
		}
	}
	
	iv init(string baat) {
		string add="";
		bat="";
		for(int i=0; baat[i]; ++i) add+=baat[i], add+=baat[i];
		do bat+=add, LEN=bat.size(); while(LEN<MNLEN);
		pbat=0, update_nxt(-2);
	}
	
	bool music=0;
	ii tap(int typ) {	//此处，上传按下的键 
		typ=type[typ];
		if(music) cout<<(char)7;
		int res=666;
		if((typ&nxttyp)!=0 && retik>=-2 && retik<=2) {
			res=retik;
//			goxy(px, py+retik), print(col[0], "  ");
			update_nxt(res);
		}
		goxy(px-1, py-2);
		if(res==666) {
			print(pred, "F"), sleep(1000);
			return -1;
		} else if(res==0) {
			print(pyellow, "P");
			return 0;
		} else {
			print(pblue, "G");
			return res>=-1&&res<=1? 1:2;
		}
	}
	
	ii drop() {
		retik--, pbat++, pbat=back(pbat);
		if(retik<-3) {
			goxy(px-1, py-2), print(pred, "F"), sleep(1000);
			return -1;
		}
		return 0;
	}
	
	iv test() {
		init("000100100200");
		
		px=19, py=10;
		type[0]=type[1]=type[3]=1, type[2]=2;
		int now=0, t=clock(), th=clock()-160;
		while(1) {
			if(clock()-t>=160) {
				t=clock(), show();
				if(drop()==-1) break;
			}
			if(clock()-th>=160) {
				if(keydown('W')) now=tap(0), th=clock();
				if(keydown('D')) now=tap(1), th=clock();
				if(keydown('S')) now=tap(2), th=clock();
				if(keydown('A')) now=tap(3), th=clock();
				if(now==-1) break;
			}
		}
	}
	
}

namespace MP {
	const int dx[]= {0, 1, 0, -1}, dy[]= {1, 0, -1, 0}, maxkind=3, maxmap=10, nowtype=7;
	const int ty_xy[BT::typsiz][2]= {{8, 38}, {9, 39}, {9, 38}, {9, 37}, {8, 37}, {8, 39}, {10, 38}};
	string prt[]= {"", "  ", "==", "[]", "LL", "RR", "  "};
	const string jump[]= {"/\\", ">>", "\\/", "<<"};
	const int bl_col[]= {0, 8*16, 8*16+7, 8*16+6, 8*16, 8*16, 8*16};
	const char ty_char[BT::typsiz]= {'W', 'D', 'S', 'A', 'Q', 'E', 'X'};
	int px=0, py=0, pdir=0, num_mp=1, deduct=5, nowj=1, score=50;
	double gamespeed=2;
	string cycle;

	struct Block {	//方块
		int kind, col;
		vector <int> data;
		Block (int kind, int col=pwhite): kind(kind), col(col) {}
		Block () {}
	};
	map <pair<int, int>, Block> pre_floor[maxmap], floor[maxmap];
	map <pair<int, int>, int> pre_door[maxmap][2], door[maxmap][2];

	iv PrintFloor(int cnt, int x, int y) {	//打印单个方块
		#define pcol(cl) ((cl>>4<<4)+BT::col[cl&15])
		goxy(cnt/7*2+4, cnt%7*4+8);
		if(floor[nowj].find(make_pair(x, y))==floor[nowj].end()) putchar(32), putchar(32);
		else {
			Block b2=floor[nowj][make_pair(x, y)];
			if(b2.kind==6) prt[6]=jump[(b2.data[0]-pdir+4)&3];
//			if(x==2 && y==5) goxy(22, 1), printf("%d\n", b2.data[0]), system("pause");
			if(x==px && y==py) color(b2.col | pwhite), putchar(1), color(pcol(b2.col)), putchar(prt[b2.kind][1]), color(pwhite);
			else print(pcol(b2.col), prt[b2.kind]);
		}
	}
	iv PrintDoor(int opt, int cnt, int kind, int x, int y) {
//		if(opt==1) goxy(22, 1), printf("%d %d %d  \n", cnt, x, y), system("pause");
		opt==0 ? goxy(cnt/7*2+5, cnt%7*4+8) : goxy(cnt/6*2+4, cnt%6*4+10);
//		if(x==0 && y==0 && opt==1 && door[nowj][kind].find(make_pair(x, y))==door[nowj][kind].end()) cout<<cnt<<endl, system("pause");
		if(door[nowj][kind].find(make_pair(x, y))==door[nowj][kind].end()) putchar(32), putchar(32);
		else {
			int c2=door[nowj][kind][make_pair(x, y)];
			print(BT::col[7-c2]|8, opt==0 ? "==" : "||");
		}
	}
	iv PrintType(int typ) {	//打印按键
		goxy(ty_xy[typ][0], ty_xy[typ][1]), color((BT::col[BT::type[typ]])^(keydown(ty_char[typ])<<3)), putchar(ty_char[typ]), color(15);
	}
	iv PrintScore() {	//打印分数
		goxy(5, 37), printf("%d ", score);
	}
	iv PrintMap() {	//打印地图
		int cnt=0;
		switch (pdir) {
			case 0: {
				rrep(j, 3, -3) rep(i, -3, 3) PrintFloor(cnt++, px+i, py+j); cnt=0;
				rrep(j, 2, -3) rep(i, -3, 3) PrintDoor(0, cnt++, 0, px+i, py+j); cnt=0;
				rrep(j, 3, -3) rep(i, -3, 2) PrintDoor(1, cnt++, 1, px+i, py+j);
				break;
			}
			case 1: {
				rrep(i, 3, -3) rrep(j, 3, -3) PrintFloor(cnt++, px+i, py+j); cnt=0;
				rrep(i, 2, -3) rrep(j, 3, -3) PrintDoor(0, cnt++, 1, px+i, py+j); cnt=0;
				rrep(i, 3, -3) rrep(j, 2, -3) PrintDoor(1, cnt++, 0, px+i, py+j);
				break;
			}
			case 2: {
				rep(j, -3, 3) rrep(i, 3, -3) PrintFloor(cnt++, px+i, py+j); cnt=0;
				rep(j, -3, 2) rrep(i, 3, -3) PrintDoor(0, cnt++, 0, px+i, py+j); cnt=0;
				rep(j, -3, 3) rrep(i, 2, -3) PrintDoor(1, cnt++, 1, px+i, py+j);
				break;
			}
			case 3: {
				rep(i, -3, 3) rep(j, -3, 3) PrintFloor(cnt++, px+i, py+j); cnt=0;
				rep(i, -3, 2) rep(j, -3, 3) PrintDoor(0, cnt++, 1, px+i, py+j); cnt=0;
				rep(i, -3, 3) rep(j, -3, 2) PrintDoor(1, cnt++, 0, px+i, py+j);
				break;
			}
		}
	}
	iv InitMap() {	//初始化地图
		system("cls");
		goxy(1, 1);
		puts("");
		puts("  o======================================o");
		puts("  |   ---------------------------        |");
		puts("  |  | X   X   X   X   X   X   X | score |");
		puts("  |  |                           |  ???  |");
		puts("  |  | X   O   O   O   O   O   X |       |");
		puts("  |  |                           |       |");
		puts("  |  | X   O   O   O   O   O   X |  QWE  |");
		puts("  |  |                           |  ASD  |");
		puts("  |  | X   O   O   @   O   O   X |   X   |");
		puts("  |  |                           |       |");
		puts("  |  | X   O   O   O   O   O   X |       |");
		puts("  |  |                           |       |");
      printf("  |  | X   O   O   O   O   O   X |   %c   |\n", 2);
		puts("  |  |                           |       |");
		puts("  |  | X   X   X   X   X   X   X |       |");
		puts("  |   ---------------------------        |");
		puts("  |                                      |");
		puts("  |       mcgc                           |");
		puts("  |                                      |");
		puts("  o======================================o");
		PrintMap();
		PrintScore();
		rep(i, 0, 6) PrintType(i);
	}
	ib load(string s) {	//加载地图种子
		#define Lchecks(i) (i+1<=len && isdigit(s[i])||s[i]>='a'&&s[i]<='f')
		#define Lcheck(i) (Lchecks(i)&&Lchecks(i+1))
		#define Lgetsu(i) (isdigit(s[i])?s[i]^48:(s[i]^96)+9)
		#define Lgetu(i) ((Lgetsu(i)<<4)+Lgetsu(i+1))
		#define Lget(i) (Lgetu(i)-(Lgetu(i)<128?0:256))
		goxy(21, 1), puts("loading...");
		int len=s.size(), i=0;
		if(!Lcheck(i)) return 0;	//地图速度，循环节长度，循环节 
		gamespeed=Lgetu(i)/16.0, i+=2;
		if(!Lcheck(i)) return 0;
		int lenc=Lgetu(i); i+=2;
		if(i+lenc>s.size()) return 0;
		rep(di, 0, lenc-1) if(!Lchecks(i)) return 0;
		cycle.assign(s, i, lenc), i+=lenc;

		if(!Lcheck(i)) return 0;	//扣分值
		deduct=Lgetu(i), i+=2;

		rep(j, 0, 7) {	//按键种类
			if(!Lchecks(i)) return 0;
			BT::type[j]=Lgetsu(i), ++i;
		}

		if(!Lcheck(i)) return 0;	//地图数量，地图 
		num_mp=Lgetu(i), i+=2;
		rep(j, 1, num_mp) pre_floor[j].clear(), pre_door[j][0].clear(), pre_door[j][1].clear();
//		puts("1");
		rep(j, 1, num_mp) {
			if(!Lcheck(i) || !Lcheck(i+2) || !Lcheck(i+4) || !Lcheck(i+6)) return 0;
			int n=Lgetu(i), m=Lgetu(i+2), sx=Lget(i+4), sy=Lget(i+6), tmp=0;
			i+=8;
			while(tmp<n*m) {
				if(!Lchecks(i)) return 0;
				int opt=Lgetsu(i); ++i;
				if(opt==0) {if(!Lcheck(i)) return 0; int cnt=Lgetu(i); i+=2, tmp+=cnt;}
				else {
					int nx=tmp%m, ny=tmp/m;
					pair <int, int> pxy=make_pair(nx-sx, ny-sy);
					if(opt>=1 && opt<=3) {
						Block b2(opt, bl_col[opt]);
						pre_floor[j][pxy]=b2;
					} else if(opt==4 || opt==5) {
						if(!Lchecks(i)) return 0;
						int col=Lgetsu(i); ++i;
						if(col>7) return 0;
						Block b2(opt, bl_col[opt]+col);
						pre_floor[j][pxy]=b2;
					} else if(opt==6) {
						if(!Lchecks(i) && !Lchecks(i+1)) return 0;
						int col=Lgetsu(i), dir=Lgetsu(i+1); i+=2;
						if(col>7 || dir>3) return 0;
//						if(nx==2 && ny==5) printf("%d %d\n", col, dir), system("pause");
						Block b2(6, bl_col[5]+col);
						b2.data.push_back(dir);
						pre_floor[j][pxy]=b2;
					} else return 0;
					++tmp;
				}
			}
//			printf("%d\n", n*m);
//			puts("3");
			tmp=0;
			while(tmp<(n-1)*m) {
//				puts("while 1");
				if(!Lchecks(i)) return 0;
				int opt=Lgetsu(i); ++i;
				if(opt==0) {if(!Lcheck(i)) return 0; int cnt=Lgetu(i); i+=2, tmp+=cnt;}
				else {
					int nx=tmp%m, ny=tmp/m;
					if(opt>=1 && opt<=7) pre_door[j][0][make_pair(nx-sx, ny-sy)]=opt;
					++tmp;
				}
			}
			tmp=0;
//			puts("4");
			while(tmp<n*(m-1)) {
				if(!Lchecks(i)) return 0;
				int opt=Lgetsu(i);
				++i;
				if(opt==0) {if(!Lcheck(i)) return 0; int cnt=Lgetu(i); i+=2, tmp+=cnt;}
				else {
					int nx=tmp%(m-1), ny=tmp/(m-1);
					if(opt>=1 && opt<=7) pre_door[j][1][make_pair(nx-sx, ny-sy)]=opt;
					++tmp;
				}
			}
		}
//		puts("5");
		if(i!=len) return 0;
		BT::init(cycle);
		return 1;
	}
	ii leave(int x, int y) {	//离开..时的交互
		pair <int, int> pxy=make_pair(x, y);
		if(floor[nowj].find(pxy)==floor[nowj].end()) return 0;
		int kind=floor[nowj][pxy].kind;
		if(kind==2) {
			floor[nowj].erase(pxy);
		} else if(kind==4 || kind==5 || kind==6) {
			Block b2=floor[nowj][pxy];
			BT::type[kind]-=b2.data.back(), b2.data.pop_back(), floor[nowj][pxy]=b2;
		}
		return 0;
	}
	ii from_to(int xf, int yf, int xt, int yt, int thistik) {	//从..移动到..时的交互
		int xft=xf+xt>>1, yft=yf+yt>>1, kind=(xf==xt?0:1), typ=BT::type[thistik];
		if(door[nowj][kind].find(make_pair(xft, yft))!=door[nowj][kind].end()) {
			int c2=door[nowj][kind][make_pair(xft, yft)];
			goxy(22, 1);
			if((typ&c2)==typ) return -1;
		}
		return 0;//...
	}
	ii reach(int x, int y) {	//到达..时的交互
		pair <int, int> pxy=make_pair(x, y);
		if(floor[nowj].find(pxy)==floor[nowj].end()) return -1;
		int kind=floor[nowj][pxy].kind;
		if(kind==3) {
			score+=100;
			return -1;
		} else if(kind==4 || kind==5 || kind==6) {
			Block b2=floor[nowj][pxy];
			int typk=BT::type[kind], dtyp=(BT::type[kind]|b2.col-bl_col[kind])-BT::type[kind];
			BT::type[kind]+=dtyp, b2.data.push_back(dtyp), floor[nowj][pxy]=b2;
		} else return 0;
	}
	ii move(int kind) {	//移动
		if(kind>=0 && kind<=3) {
			int Mdir=pdir+kind&3;
			if(from_to(px, py, px+dx[Mdir], py+dy[Mdir], kind)==-1) return -1;
			if(leave(px, py)==-1) return -1;
			px+=dx[Mdir], py+=dy[Mdir];
			if(reach(px, py)==-1) return -1;
			PrintMap();
		} else if(kind>=4 && kind<=5) {
			kind==4?--pdir:++pdir;
			pdir=pdir+4&3;
			PrintMap();
		} else if(kind==6) {
//			goxy(22, 1), puts("1");
			if(floor[nowj].find(make_pair(px, py))==floor[nowj].end()) return -1;
			Block b2=floor[nowj][make_pair(px, py)];
//			puts("1.5");
			if(b2.kind==6) {
//				puts("2");
				int dir=b2.data[0];
//				puts("3");
				rep(t, 0, 1) if(from_to(px+t*dx[dir], py+t*dy[dir], px+(t+1)*dx[dir], py+(t+1)*dy[dir], kind)==-1) return -1;
//				puts("4");
				if(leave(px, py)==-1) return -1;
				px+=2*dx[dir], py+=2*dy[dir];
//				puts("5");
				if(reach(px, py)==-1) return -1;
				PrintMap();
			} else return -1;
		}
//		if(kind==6) goxy(22, 1), system("pause");
		return 0;
	}
	iv init() {	//初始化
		rep(j, 1, num_mp) floor[j]=pre_floor[j], door[j][0]=pre_door[j][0], door[j][1]=pre_door[j][1];
		px=py=0, pdir=0, nowj=1;
	}
	iv talk(int p) {
		switch(p) {
			case 0: {
				goxy(11, 36), print(pyellow, "跟节拍"); 
				goxy(12, 36), print(pyellow, "按adws");
				goxy(13, 36), print(pyellow, "移动到"); 
				goxy(14, 36), print(pyellow, "终点[]");
				break;
			}
			case 1: {
				goxy(11, 36), print(pyellow, "加油!");
				break;
			}
		}
	}
	ii main(int p) {
		int stik=1000/gamespeed;
		score=100;
		InitMap();
		talk(p);
		goxy(19, 10), print(pyellow, "输入S以开始");
		while(1) if(keydown('S')) break;
		BT::show();
		sleep(200);
		reach(0, 0);
		clock_t tim=clock();
		int b=-1;
		while(1) {
			if(BT::drop()==-1) break;
			BT::show();
			PrintScore();
			int thistik=-1;
			while(clock()-tim<=stik) {	//循环到过了一个 tik
				if(b!=-1 && !keydown(ty_char[b])) b=-1;
				if(b==-1)
					rep(typ, 0, nowtype-1) if(keydown(ty_char[typ])) b=thistik=typ;
				rep(typ, 0, nowtype-1) PrintType(typ);
				if(keydown('P')) {
					system("mode con cols=60 lines=22");
					InitMap(), talk(p), BT::show();
					goxy(3, 47), print(pyellow, "已暂停");
					goxy(6, 47), print(pwhite, "1:继续");
					goxy(8, 47), print(pwhite, "2:退出");
					goxy(10, 47), print(pwhite, "3:重来");
					int ret=-1;
					while(1) {
						if(keydown('1')) break;
						if(keydown('2')) {ret=233; break;}
						if(keydown('3')) {ret=666; break;}
					}
					system("mode con cols=44 lines=22");
					InitMap(), talk(p), BT::show();
					if(ret!=-1) return ret;
				}
			}
			tim=clock();
			if(thistik!=-1) {
				int ret=BT::tap(thistik);
				if(ret==-1) break;	//炸掉了
				score-=ret*deduct;
				if(score<=0) break;	//分数太少
				if(move(thistik)==-1) break;
			}
		}
//		goxy(22, 1);
//		printf("%d", b);
//		system("pause");
//		PrintScore();
		PrintMap();
		tim=clock();
		while(clock()-tim>=2500) if(keydown('P')) break;
		score-=100;
		return score;
	}
	iv test() {
		string seed;
		cin>>seed;
		while(!load(seed)) puts("error!"), cin>>seed;
		init();
		system("cls");
		for(map <pair<int, int>, Block> :: iterator it=floor[1].begin(); it!=floor[1].end(); ++it) {
			printf("(%d, %d): %d\n", it->first.first, it->first.second, it->second.kind);
		}
		rep(t, 0, 1) {
			puts("");
			for(map <pair<int, int>, int> :: iterator it=door[1][t].begin(); it!=door[1][t].end(); ++it) {
				printf("(%d, %d): %d\n", it->first.first, it->first.second, it->second);
			}
		}
		system("pause");
		main(-1);
	}
}

namespace BS {
	
	const int totL=6, MXL=250;
	string mp[MXL]={
		"",
		"a01000001000100020000211210000010302000012210013004003",
		"a00c00010010020001112100000105050200002100120021110022213121100211001014014",
		"a00c0001001002000111210000010607040100222300321001100120012100112121222111211212002210012001023024",
		"a00c00010010020002112100000106030002002200162021262200120021002622300f00c",
		"a00c0001001002000211210000010c0301000012001621222262026202001222226212200162262062020012222220013001021018",
		"a00c0001001002000111210000010606030300241141152151001100111002152001200110011001300111100352001101e01e"
	};
	map<string, string> spmp;
	int score[MXL];
	bool opn[MXL]={0, 1};
	
	string diymp[4]={"", "NuLl", "NuLl", "NuLl"};
	string diykey[4]={"", "NuLl", "NuLl", "NuLl"};
	
	int wich[30][50], px, py, p;
	
	const int tipsiz=17;
	string tips[tipsiz+2]={
		"acbc!!!",
		"mcgc!!!",
		"no tip",
		"也许这个游戏可以在今年内做完?",
		"ITA:为什么我被插队了",
		"Beeeeeeeeeeeeeeeeeat!!",
		"ac特别喜欢bc",
		"我觉得有必要扩充一下tips",
		"算上这条, tips一共有"+iturns(tipsiz, 0)+"条",
		"acbc是BBIT世界中的唯一真理。",
		"不会真有人觉得tips里会有提示吧?(",
		"一定要把快速编辑模式给关掉!",
		"不要在显示 按S以开始 的时候干一些奇奇怪怪的事啊!",
		"为什么这个游戏是在愚人节开始做的呢?",
		"我个人感觉, 这游戏挺简单的--ztue",
		"这真的是一条为了写tip而写的tip",
		"《关于我什么都没干bug却自己好了的这档事儿》",
		"本游戏没有任何彩蛋, 真的"
	};
	
	iv special_map() {
		spmp["EZ"]="500c0001001002000110210000010705030000320015252415142415141424152414142525241415142415252424100230020056001560016560026655500260070076565001600160026600255005";
	}
	
	iv data_save() {
		FILE *fout=fopen("BBITdata.txt", "w");
		rep(i, 1, MXL) fwrites(iturns(score[i], 0)+' ', fout);
		fputc('\n', fout);
		rep(i, 0, MXL) fwrites(iturns(opn[i], 0)+' ', fout);
		fputc('\n', fout);
		rep(i, 1, 3) fwrites(diymp[i]+'\n', fout);
		rep(i, 1, 3) fwrites(diykey[i]+' ', fout);
		fclose(fout);
	}
	iv data_read() {
		FILE *fin;
		if(!(fin=fopen("BBITdata.txt", "r"))) data_save();
		fin=fopen("BBITdata.txt", "r");
		rep(i, 1, MXL) score[i]=fread(fin);
		rep(i, 0, MXL) opn[i]=fread(fin);
		rep(i, 1, 3) diymp[i]=freads(fin);
		rep(i, 1, 3) {
			diykey[i]=freads(fin);
			if(diykey[i]!="NuLl") spmp[diykey[i]]=diymp[i];
		}
		fclose(fin);
	}
	
	namespace DIY {
		
		const int prtsiz=12;
		const int front_col[prtsiz+2]= {0, 15, 0, 15, 14, 15, 15, 15, 15, 15, 15, 15, 15};
		const int back_col[prtsiz+2]= {0, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0};
		const bool hav_col[prtsiz+2]= {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
		const bool out_map[prtsiz+2]= {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0};
		const string prt[prtsiz+2]= {"", "c ", "  ", "==", "[]", "LL", "RR", "==", "||", "<<", ">>", "/\\", "\\/"};
		
		const int col[8]={0, pblue, pred, 13, pgreen, 11, 14, 15};
		int pagesiz=ceil(1.0*prtsiz/5);
		int block[6];
		
		button bq[1000];
		int bqsiz;
		
		int wich[50][50];
		int tx[55], ty[55];
		int type_block[55];	//1 起点，2 普通，3 塌陷，4 终点，56 左右转，78 \，9abc 左右上下跳 
		int col_block[55];
		//1 2 3 4 5 6 7
		//8 9 a b c d e
		//...
		
		int owich[50][50];
		int otx[110], oty[110], outf[110];
		int type_o[110];	//123456 \，78 横竖门 
		int col_o[110];
		
		int de_score;
		double speed;
		int bat_len;	//速度；循环节长度
		int bat_col[20];	//循环节颜色，如 000100200100 从 1 开始 
		int key_col[20];	//以 qweasdx 的顺序的颜色 
		
		iv epty_map_show() {
			system("cls");
			puts("");
			puts("  o======================================o");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  o======================================o");
		} 
		
		iv block_show(int page, int chos) {
			goxy(19, 4), print(pyellow, page>1? "<-": "  ");
			goxy(19, 40), print(pyellow, page<pagesiz? "->": "  ");
			rep(i, 6, 10) bq[i]=button(0, 0, 0, 0);
			int bg=(page-1)*5, up=min(5, prtsiz-bg);
			bqsiz=5;
			rep(i, up+1, 5) goxy(19, i*8-2), print(0, "  ");
			rep(i, 1, 5) goxy(18, i*8-2), print(0, "  ");
			rep(i, 1, up) {
				goxy(19, i*8-2), print(front_col[bg+i]+back_col[bg+i]*16, prt[bg+i]);
				bq[++bqsiz]=button(19, 19, i*8-2, i*8-1), block[i]=bg+i;
				if(block[i]==chos) goxy(18, i*8-2), print(pgreen, "\\/");
			}
		}
		inline string seed_produce() {	//mcbc
//			goxy(22, 1);
//			rep(i, 1, 20) cout<<col_o[i]<<' ';
//			system("pause");
			string seed="";
			seed+=DtoHu((int) ceil(speed*16));
			seed+=DtoHu(bat_len);
//			rep(i, 1, 16) cout<<DtoHsu(bat_col[i])<<' ';
//			system("pause");
			rep(i, 1, bat_len) seed+=DtoHsu(bat_col[i]);
			seed+=DtoH(de_score);
			seed+=DtoHsu(key_col[2]); seed+=DtoHsu(key_col[6]); seed+=DtoHsu(key_col[5]); seed+=DtoHsu(key_col[4]);
			seed+=DtoHsu(key_col[1]); seed+=DtoHsu(key_col[3]); seed+=DtoHsu(key_col[7]); seed+='0';
			seed+="010707";
			int cnt=0;
			rep(tmp, 0, 48) if(type_block[tmp+1]==1) ++cnt, seed+=DtoHu(tmp%7), seed+=DtoHu(6-tmp/7);
			if(cnt!=1) return seed="error";
			#define checkcnt if(cnt!=0) seed+="0", seed+=DtoHu(cnt), cnt=0
			cnt=0;
			rep(tmp, 0, 48) {
				int tb=type_block[(6-tmp/7)*7+tmp%7+1], cb=col_block[(6-tmp/7)*7+tmp%7+1];
				if(tb==0) ++cnt;
				else {
//					cout<<seed;
					checkcnt;
//					cout<<endl<<seed<<endl;
//					system("pause");
					if(tb==1) seed+="1";
					else if(tb>=2 && tb<=4) seed+=DtoHsu(tb-1);
					else if(tb>=5 && tb<=6) seed+=DtoHsu(tb-1), seed+=DtoHsu(cb);
					else if(tb>=9 && tb<=12) {
						seed+="6", seed+=DtoHsu(cb);
						if(tb==9) seed+="3";
						if(tb==10) seed+="1";
						if(tb==11) seed+="0";
						if(tb==12) seed+="2";
					} else return seed="error and mcbc";
				}
			}
			checkcnt;
			rep(tmp, 0, 41) {
				int tmp2=tmp%7==6?(6-tmp/7)*13:(5-tmp/7)*13+tmp%7*2+2, to=type_o[tmp2], co=col_o[tmp2]^(to==0?0:7);
				if(to==0) ++cnt;
				else {
					checkcnt;
					if(to==7) seed+=DtoHsu(co);
					else return seed="error and mcbc too";
				}
			}
			checkcnt;
			rep(tmp, 0, 41) {
				int tmp2=tmp<6?6*13+tmp+1:(6-tmp/6)*13+tmp%6*2+1, to=type_o[tmp2], co=col_o[tmp2]^(to==0?0:7);
				if(to==0) ++cnt;
				else {
					checkcnt;
					if(to==8) seed+=DtoHsu(co);
					else return seed="error and mcbc three";
				}
			}
			checkcnt;
			return seed;
			#undef checkcnt
		}
		iv map_show() {
			system("cls");
			puts("");
			puts("  o======================================o");
			puts("  |   ---------------------------        |");
			puts("  |  |                           |       |");
			puts("  |  |                           | 选择  |");
			puts("  |  |                           |颜色和 |");
			puts("  |  |                           |方块,  |");
			puts("  |  |                           |用左键 |");
			puts("  |  |                           |添加右 |");
			puts("  |  |                           |键删除 |");
			puts("  |  |                           |       |");
			puts("  |  |                           |       |");
			puts("  |  |                           |       |");
			puts("  |  |                           |       |");
			puts("  |  |                           |       |");
			puts("  |  |                           |       |");
			puts("  |   ---------------------------        |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  |                                      |");
			puts("  o======================================o");
			
		}
		ib map_draw() {
			map_show();
			/*
			1-chos_red 2-chos_blue 3-chos-green
			4-last_page 5-next_page
			6~10 block
			*/
			memset(wich, 0, sizeof(wich));
			goxy(1, 1), print(pred, "exit"), wich[1][1]=wich[1][2]=wich[1][3]=wich[1][4]=-1;
			goxy(1, 41), print(pgreen, "next"), wich[1][41]=wich[1][42]=wich[1][43]=wich[1][44]=-2;
			
			goxy(12, 37), print(pred*16, "   "), bq[1]=button(12, 12, 37, 39);
			goxy(14, 37), print(pblue*16, "   "), bq[2]=button(14, 14, 37, 39);
			goxy(16, 37), print(pgreen*16, "   "), bq[3]=button(16, 16, 37, 39);
			bq[4]=button(19, 19, 4, 5), bq[5]=button(19, 19, 40, 41);
			
			for(int x=4, cnt=0, ocnt=0; x<=16; x+=2) for(int y=8; y<=32; y+=4) {
				wich[x][y]=wich[x][y+1]=(++cnt), tx[cnt]=x, ty[cnt]=y, goxy(x, y), print(7*16, "  ");
				if(y!=32) owich[x][y+2]=owich[x][y+3]=++ocnt, otx[ocnt]=x, oty[ocnt]=y+2, outf[ocnt]=1;
				if(x!=16) owich[x+1][y]=owich[x+1][y+1]=++ocnt, otx[ocnt]=x+1, oty[ocnt]=y, outf[ocnt]=2;
			}
			
			int px, py, chos_block=1;
			int chos_col=0;
			int page=1, click;
			block_show(1, chos_block);
			
			int now=clock();
			while(1) if(clock()-now>100) {
				now=clock();
				if(downL) {
					getxy(px, py);
//					goxy(1, 5), print(pwhite, iturns(px, 2)+" "+iturns(py, 2));
					click=button_check(bq, bqsiz, px, py);
//					goxy(1, 20), print(pred, iturns(click, 0));
					switch(click) {
						case -1: {
							break;
						}
						case 1: {
							chos_col^=2, goxy(12, 37), print(((chos_col&2)? pgrey: pred)*16, "   ");
							break;
						}
						case 2: {
							chos_col^=1, goxy(14, 37), print(((chos_col&1)? pgrey: pblue)*16, "   ");
							break;
						}
						case 3: {
							chos_col^=4, goxy(16, 37), print(((chos_col&4)? pgrey: pgreen)*16, "   ");
							break;
						}
						case 4: {
							if(page>1) block_show(--page, chos_block);
							break;
						}
						case 5: {
							if(page<pagesiz) block_show(++page, chos_block);
							break;
						}
						default: {
							block_show(page, chos_block=block[click-5]);
							break;
						}
					}
					click=wich[px][py];
					if(click==-1) return 0;
					if(click==-2) return 1;
					if(!out_map[chos_block]&&click>0) {
						goxy(tx[click], ty[click]);
						print((hav_col[chos_block]? front_col[chos_block]: (col[chos_col]? col[chos_col]: pgrey))+back_col[chos_block]*16, prt[chos_block]);
						type_block[click]=chos_block, col_block[click]=chos_col;
					}
					click=owich[px][py];
					if(out_map[chos_block]&&click>0) {
						goxy(otx[click], oty[click]);
						print((hav_col[chos_block]? front_col[chos_block]: (col[chos_col]? col[chos_col]: pgrey))+back_col[chos_block]*16, prt[chos_block]);
						type_o[click]=chos_block, col_o[click]=chos_col;
					}
				}
				if(downR) {
					getxy(px, py);
					click=wich[px][py];
					if(click>0) {
						goxy(tx[click], ty[click]), print(pgrey*16, "  ");
						type_block[click]=0;
					}
					click=owich[px][py];
					if(click>0) {
						goxy(otx[click], oty[click]), print(0, "  ");
						type_o[click]=0;
					}
				}
			}
		}
	/*
---------------------------------------------
										    |	---	1
  o======================================o  |
  |                                      |  |
  |     QWE                              |  |	---	4
  |     ASD       red   blu   gre        |  |
  |      X                               |  |
  |                                      |  |	---	7
  |                                      |  |
  |                                      |  |
  |                                      |  |	---	10
  |   [      1       2       3       ]   |  |
  |                                      |  |
  |                                      |  |	---	13
  |                                      |  |
  |                                      |  |
  |                                      |  |	---	16
  |                                      |  |
  |                                      |  |
  |                                      |  |	---	19
  |                                      |  |
  o======================================o  |
										    |	---	22
---------------------------------------------
| |  |   |   |   |   |   |   |   |   |   |
1 3  6   10  14  18  22  26  30  34  38  42
     []      []      []      []      []	
		
		page 1
			block
	*/
		ib beat_draw() {
			int px, py;
			memset(wich, 0, sizeof(wich));
			
			bat_back:;
			epty_map_show();
			goxy(1, 1), print(pred, "exit"), wich[1][1]=wich[1][2]=wich[1][3]=wich[1][4]=-1;
			goxy(4, 12), print(pgreen, "请输入节拍循环的总长度");
			goxy(5, 12), print(pred, "范围4~16!");
			mouse(1), goxy(6, 12), cin>>bat_len, mouse(0);
			if(bat_len>16||bat_len<4) goto bat_back;
			
			speed_back:;
			epty_map_show();
			goxy(1, 1), print(pred, "exit"), wich[1][1]=wich[1][2]=wich[1][3]=wich[1][4]=-1;
			goxy(4, 12), print(pgreen, "请输入节拍的速度(一秒几个块)");
			goxy(5, 12), print(pred, "范围4~14");
			mouse(1), goxy(6, 12), cin>>speed, mouse(0);
			if(speed>14||speed<4) goto speed_back;
			
			scor_back:;
			epty_map_show();
			goxy(1, 1), print(pred, "exit"), wich[1][1]=wich[1][2]=wich[1][3]=wich[1][4]=-1;
			goxy(4, 12), print(pgreen, "请输入扣分值");
			goxy(5, 12), print(pred, "范围1~100");
			mouse(1), goxy(6, 12), cin>>de_score, mouse(0); 
			if(de_score<1||de_score>100) goto speed_back;
			
			epty_map_show();
			goxy(1, 1), print(pred, "exit"), wich[1][1]=wich[1][2]=wich[1][3]=wich[1][4]=-1;
			goxy(1, 41), print(pgreen, "next"), wich[1][41]=wich[1][42]=wich[1][43]=wich[1][44]=-2;
			
			int bat_cnt=0;
			goxy(11, 7);
			rep(i, 1, bat_len) print(pgrey*16, "  "), wich[11][5+i*2]=wich[11][6+i*2]=++bat_cnt;
			
			int chos_col=0, ktx[20], kty[20];
			string kc[20];
			goxy(5, 19), print(pred*16, "   "), bq[1]=button(5, 5, 19, 21);
			goxy(5, 25), print(pblue*16, "   "), bq[2]=button(5, 5, 25, 27);
			goxy(5, 31), print(pgreen*16, "   "), bq[3]=button(5, 5, 31, 33);
			goxy(4, 9), print(pgrey, kc[4]="Q"), bq[4]=button(ktx[4]=4, 4, kty[4]=9, 9);
			print(pgrey, kc[5]="W"), bq[5]=button(ktx[5]=4, 4, kty[5]=10, 10);
			print(pgrey, kc[6]="E"), bq[6]=button(ktx[6]=4, 4, kty[6]=11, 11);
			goxy(5, 9), print(pgrey, kc[7]="A"), bq[7]=button(ktx[7]=5, 5, kty[7]=9, 9);
			print(pgrey, kc[8]="S"), bq[8]=button(ktx[8]=5, 5, kty[8]=10, 10);
			print(pgrey, kc[9]="D"), bq[9]=button(ktx[9]=5, 5, kty[9]=11, 11);
			goxy(6, 10), print(pgrey, kc[10]="X"), bq[10]=button(ktx[10]=6, 6, kty[10]=10, 10);
			
			int now=clock(), click;
			while(1) if(clock()-now>100) {
				now=clock();
				if(downL) {
					getxy(px, py);
					click=button_check(bq, 10, px, py);
					switch(click) {
						case -1: {
							break;
						}
						case 1: {
							chos_col^=2, goxy(5, 19), print(((chos_col&2)? pgrey: pred)*16, "   ");
							break;
						}
						case 2: {
							chos_col^=1, goxy(5, 25), print(((chos_col&1)? pgrey: pblue)*16, "   ");
							break;
						}
						case 3: {
							chos_col^=4, goxy(5, 31), print(((chos_col&4)? pgrey: pgreen)*16, "   ");
							break;
						}
						default: {
							key_col[click-3]=chos_col;
							goxy(ktx[click], kty[click]), print(col[chos_col]? col[chos_col]: pgrey, kc[click]);
							break;
						}
					}
					click=wich[px][py];
//					goxy(22, 1), cout<<click;
					if(click==-1) return 0;
					if(click==-2) return 1;
					if(click>0) {
						bat_col[click]=chos_col;
						goxy(11, 5+click*2), print((col[chos_col]? col[chos_col]: pgrey)*16, "  ");
					}
				}
			}
		}
		
		iv DIY_clear() {
			bqsiz=0;
			memset(bat_col, 0, sizeof(bat_col)), memset(key_col, 0, sizeof(key_col));
			memset(type_o, 0, sizeof(type_o)), memset(col_o, 0, sizeof(col_o));
			memset(owich, 0, sizeof(owich)), memset(otx, 0, sizeof(otx)), memset(oty, 0, sizeof(oty));
			memset(type_block, 0, sizeof(type_block)), memset(col_block, 0, sizeof(col_block));
			memset(wich, 0, sizeof(wich)), memset(tx, 0, sizeof(tx)), memset(ty, 0, sizeof(ty));
		}
		inline string DIY_draw() {
			DIY_clear();
			if(!map_draw()) return "exit";
			if(!beat_draw()) return "exit";
			return seed_produce();
		}
	}
	
	iv DIY_map() {
		bool flag=1;
		int bqsiz;
		button bq[1000]={};
		string seed;
		while(flag) {
			system("cls");
			goxy(2, 12), print(pgreen, "输入种子(可输入钥匙码)"); 
			goxy(3, 12), print(pgreen, "输入draw进入地图编辑器");
			goxy(4, 12), print(pred, "输入exit以离开");
			goxy(5, 12), mouse(1), cin>>seed, mouse(0);
			if(seed=="draw") seed=DIY::DIY_draw();
			if(seed=="exit") return;
			if(spmp[seed].size()) seed=spmp[seed];
			if(MP::load(seed)) flag=0;
			else system("cls"), goxy(2, 16), print(pred, "输错了 :-("), sleep(1000);
		}
		start:;
		int scor;
		MP::load(seed), MP::init();
		system("cls"), print(pwhite, "tip:"+tips[rand()%tipsiz]), sleep(1000);
		system("cls"), scor=MP::main(-1), sleep(1000);
		system("cls");
		if(scor==233) return;
		if(scor==666) goto start;
		if(scor>=60) {
			goxy(2, 16), print(pyellow, "过关啦!"), sleep(1000);
			goxy(3, 16), print(pyellow, "分数 "+iturns(scor, 0));
			if(p>0)  score[p]=max(score[p], scor);
			goxy(4, 16), print(pgreen, "重来  返回  保存");
			bqsiz=0, bq[++bqsiz]=button(4, 4, 16, 19), bq[++bqsiz]=button(4, 4, 22, 25), bq[++bqsiz]=button(4, 4, 28, 31);
		} else {
			goxy(2, 16), print(pyellow, "失败了!"), sleep(1000);
			goxy(3, 16), print(pgreen, "重来  返回  保存");
			bqsiz=0, bq[++bqsiz]=button(3, 3, 16, 19), bq[++bqsiz]=button(3, 3, 22, 25), bq[++bqsiz]=button(3, 3, 28, 31);
		}
		int now=clock();
		while(1) if(clock()-now>=100) {
			now=clock();
			if(downL) {
				int click;
				getxy(px, py), click=button_check(bq, bqsiz, px, py);
				if(click==1) goto start;
				if(click==2) return;
				if(click==3) {
					rep(x, 1, 3) {
						goxy(10, 6+8*x);
						if(diymp[x]=="NuLl") print(pgreen, iturns(x, 0)), bq[++bqsiz]=button(10, 10, 6+8*x, 6+8*x);
						else print(pred, iturns(x, 0)), bq[++bqsiz]=button(0, 0, 0, 0);
					}
					click=-1;
				}
				if(click>3) {
					click-=3, diymp[click]=seed, diykey[click]=iturns(click, 0);
					goxy(12, 10), print(pyellow, "设置对应钥匙码(不区分大小写)");
					goxy(13, 10), mouse(1), cin>>diykey[click], diykey[click]=sdown(diykey[click]), mouse(0);
					while(spmp[diykey[click]].size()) {
						goxy(12, 10), print(1, "                            ");
						goxy(12, 10), print(pred, "重复! 请重新设置");
						goxy(13, 10), print(1, "                                                                                          ");
						goxy(13, 10), mouse(1), cin>>diykey[click], diykey[click]=sdown(diykey[click]), mouse(0); 
					}
					spmp[diykey[click]]=diymp[click], data_save();
					system("cls"), print(pyellow, "已保存!"), sleep(2000);
					return;
				}
			}
		}
	}
	
	iv play(int p) {
		if(p==1&&opn[0]==0) p=0;
		int scor, bqsiz;
		button bq[1000]={};
		string seed;
		switch(p) {
			case 0: {
				int diecnt=0;
				system("cls"), print(pyellow, "你好!\n"), sleep(1500);
				print(pyellow, "我是ITue, 你在这个世界里的向导!"), sleep(2500);
				retry:;
				MP::load("a01000001000100010000211110000010302000012210013004003"), MP::init();
				system("cls"), scor=MP::main(0);
				system("cls");
				if(scor>=80) {
					print(pyellow, "如你所见, 这是一个非常简单的游戏!\n"), sleep(1700);
					print(pyellow, "......"), sleep(800);
					print(pyellow, "......"), sleep(900);
					rep(i, 1, 6) print(pyellow, "."), sleep(i*50);
					system("cls"), print(pyellow, "我好像把你的s键搞丢了......"), sleep(2000);
					system("cls"), print(pyellow, "没事的! 我还有一个s键!......可能, 有点, 不太适配?"), sleep(600);
					print(pred, "s"), sleep(2000);
					system("cls"), print(pyellow, "......"), sleep(1000);
					print(pyellow, "我刚才..."), sleep(800), print(pyellow, "去看了一下代码, \n"), sleep(1300);
					print(pyellow, "好像这个按钮不能在"), print(pblue, "蓝色方块"), print(pyellow, "下落的时候点......"), sleep(3000);
					system("cls"), print(pyellow, "你不会怪我吧? QAQ"), sleep(4000);
					system("cls"), print(pyellow, "其实, 还是有补救方案的, 可是那对于你来说, 有点...困难..."), sleep(1500);
					system("cls"), print(pyellow, "我帮你换上了"), print(pred, "红色方块"), print(pyellow, "这样你就能按s键了!"), sleep(3000);
					p=opn[0]=1, scor=0, data_save();
					goto start;
				} else {
					diecnt++;
					if(diecnt==1) print(pyellow, "是我的不对! 我忘记告诉你, 像==这样的方块是只能踩一次的!");
					if(diecnt>=2&&diecnt<=5) print(pyellow, "怎么这么不小心呢? 再试一次!");
					if(diecnt>=6&&diecnt<=12) print(pyellow, "为什么又回来了?");
					if(diecnt==13) {
						print(pyellow, "你是不是玩不起?");
						memset(opn, 0, sizeof(opn)), memset(score, 0, sizeof(score));
						exit(0);
					}
					
					sleep(1500);
					goto retry;
				}
				break;
			}
			case 4: {
				if(!opn[5]) {
					system("cls"), print(pyellow, "哈喽哈, 又见面了~\n"), sleep(1800);
					print(pyellow, "我这次给你带来了一个好玩的东西!"), sleep(1000);
					print(pyellow, "那就是跳板!"), sleep(2000);
					system("cls"), print(pred, "<< "), sleep(300), print(pred, ">> "), sleep(300), print(pred, "/\\ "), sleep(300), print(pred, "\\/\n"), sleep(1000);
					print(pyellow, "这四个分别是往左、右、上、下跳的跳板!\n"), sleep(2000);
					print(pyellow, "在踩到跳板的时候, 你可以用"), print(pred, "x"), print(pyellow, "键来触发!"), sleep(2500);
					system("cls"), print(pyellow, "跳板会让你快速地前进两格, 祝你玩得愉快!"), sleep(3500);
				}
				goto start;
				break;
			}
			case 6: {
				if(!opn[7]) {
					system("cls"), print(pyellow, "通关速度还挺快, 不愧是你\n"), sleep(2000);
					print(pyellow, "看来我要给你点更加 有趣 的小东西了呢~"), sleep(3000);
					system("cls"), print(pred, "LL RR\n"), sleep(1000);
					print(pyellow, "这是两个旋转方块, 左旋和右旋\n"), sleep(2500);
					print(pyellow, "站在上面的时候, 分别使用"), print(pred, " Q "), print(pyellow, "和"), print(pred, " E "), print(pyellow, "来使用它们!\n"), sleep(4000); 
					system("cls"), print(pyellow, "玩得愉快!"), sleep(2000); 
				}
				goto start;
				break;
			}
			default: {
				start:;
				MP::load(mp[p]), MP::init();
				system("cls"), print(pwhite, "tip:"+tips[rand()%tipsiz]), sleep(1000);
				system("cls"), scor=MP::main(p), sleep(1000);
				system("cls");
				if(scor==233) return;
				if(scor==666) goto start;
				if(scor>=60) {
					opn[p+1]=1;
					goxy(2, 16), print(pyellow, "过关啦!"), sleep(1000);
					goxy(3, 16), print(pyellow, "分数 "+iturns(scor, 0));
					if(p>0)  score[p]=max(score[p], scor), print(pyellow, " 最高 "+iturns(score[p], 0)), data_save();
					goxy(4, 16), print(pgreen, "重来  返回");
					bqsiz=0, bq[++bqsiz]=button(4, 4, 16, 19), bq[++bqsiz]=button(4, 4, 22, 25);
					while(1) if(downL) {
						int chos;
						getxy(px, py), chos=button_check(bq, bqsiz, px, py);
						if(chos==1) goto start;
						if(chos==2) return;
					}
				} else {
					goxy(2, 16), print(pyellow, "失败了!"), sleep(1000);
					goxy(3, 16), print(pgreen, "重来  返回");
					bqsiz=0, bq[++bqsiz]=button(3, 3, 16, 19), bq[++bqsiz]=button(3, 3, 22, 25);
					while(1) if(downL) {
						int chos;
						getxy(px, py), chos=button_check(bq, bqsiz, px, py);
						if(chos==1) goto start;
						if(chos==2) return;
					}
				}
				break;
			}
		}
		
	}
	
	iv lock() {
		goxy(20, 12), print(pred, "该关卡尚未解锁!"), sleep(1000), print(pwhite, "               ");
	}
	
	iv map_choser() {
		chosing:;
		memset(wich, 0, sizeof(wich));
		px=4, py=7;
		int p=1;
		//7 15 23 31
		string seed;
		system("cls");
		
		goxy(2, 10), print(pred, "exit");
		wich[2][10]=wich[2][11]=wich[2][12]=wich[2][13]=-1;
		goxy(2, 16), print(pwhite, "Choose Map");
		
		while(p<=totL) {
			goxy(px, py), print(pred+(opn[p]? pyellow*16: pgrey*16), iturns(p, 3));
			wich[px][py]=wich[px][py+1]=wich[px][py+2]=(opn[p]? p: -2);
			py+=6, p++;
			if(py>31) py=7, px+=2;
		}
		goxy(px, py), print(pred+pyellow*16, "DIY");
		wich[px][py]=wich[px][py+1]=wich[px][py+2]=totL+1;
		
		bool flag=1, sptip=0;
		while(flag) if(downL) {
			getxy(px, py), p=wich[px][py];
			if(p>0&&p<=totL) play(p), flag=0;
			else if(p==totL+1) DIY_map(), flag=0;
			else if(p==-1) return;
			else if(p==-2) lock();
		}
		goto chosing;
	}
	iv about() {
		system("cls");
		print(pwhite, "游戏名称       Beat BIT!\n");
		sleep(1000);
		print(pwhite, "作者           atue, ztue\n");
		sleep(1000);
		print(pwhite, "开始制作时间   2021/4/1\n\n");
		sleep(1000);
		print(pyellow, "一些提示:\n");
		sleep(1000);
		print(pyellow, "按P以暂停\n");
		sleep(1000);
		print(pyellow, "事实上, aczbc\n");
		sleep(1000);
		print(pyellow, "几乎所有的等待时间都可以用空格跳过哦~\n");
		sleep(1000);
		
		print(pred, "\n\n按s以返回");
		while(1) if(keydown('S')) return;
	}
	iv test_main() {
		special_map();
		begin:;
		data_read();
		system("cls"), sleep(200), goxy(2, 16);
		string out[9]={"B", "E", "A", "T", " ", "B", "I", "T", "!"};
		rep(i, 0, 8) print(rand()%2? pred: pblue, out[i]), Sleep(20);
		goxy(1, 1), print(pred, "exit");
		goxy(1, 41), print(pgreen, "关于"); 
		int t=clock(), scren=0;
		if(opn[0]==0) goxy(12, 6), print(pred, "请先确保你的快速编辑模式已关闭!");
		while(1) {
			if(downL) {
				getxy(px, py);
				if(px==1&&py>=1&&py<=4) return;
				if(px==1&&py>=41&&py<=44) {
					about();
					goto begin;
				}
			}
			if(clock()-t>=700) {
				goxy(4, 16), print(rand()%8+8, scren? "         ": "按S以开始");
				scren^=1, t=clock();
			}
			if(keydown('S')) break;
		}
		map_choser();
		goto begin;
	}
	iv main() {
		//没的很, 甚至比story还要没得很 
	}
}

int main() {
	system("mode con cols=44 lines=22");
	color(pwhite), mouse(0), srand(time(NULL));
	BS::test_main();
	system("mode con cols=82 lines=25");
	color(7), mouse(1);
}
