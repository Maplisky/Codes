#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

namespace GB {
	//检测按键、左键、右键 
	//上38 下40 左37 右39 
	#define keydown(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
	#define downL ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1:0)
	#define downR ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 1:0)
	//不需要用到的 
	#define Get GetStdHandle(STD_OUTPUT_HANDLE)
	//颜色 
	#define color(a) SetConsoleTextAttribute(Get,a)
	#define pgrey 7
	#define pblue 9
	#define pgreen 10
	#define pred 12
	#define pyellow 14
	#define pwhite 15
	//我自己用的 
	#define iv inline void
	#define ib inline bool
	#define ii inline int
	#define rep(i, a, b) for(int i=(a), i##up=(b); i<=i##up; ++i)
	#define repd(i, a, b, c) for(int i=(a), i##up=(b), i##de=(c); i<=i##up; i+=i##de)
	#define repf(i, a) for(int i=1, i##up=(a); i<=i##up; ++i)
	#define rrep(i, a, b) for(int i=(a), i##dn=(b); i>=i##dn; --i)
	#define repe(e, u) for(int e=head[u]; e; e=nxt[e])
	//键盘对应编码
	const string in_key[232]={
		"", "", "", "", "", "", "", "", "backspace", "tap", 
		"", "", "", "回车", "", "", "", "", "", "break", 
		"caps_lock", "", "", "", "", "", "", "", "", "", 
		"", "", "空格", "page_up", "page_down", "end", "home", "左", "上", "右", 
		"下", "", "", "", "print_screen", "insert", "delete", "", "", "1", 
		"2", "3", "4", "5", "6", "7", "8", "9", "0", "", 
		"", "", "", "", "", "A", "B", "C", "D", "E", 
		"F", "G", "H", "I", "J", "K", "L", "M", "N", "O", 
		"P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", 
		"Z", "", "", "", "", "", "小键盘0", "小键盘1", "小键盘2", "小键盘3", 
		"小键盘4", "小键盘5", "小键盘6", "小键盘7", "小键盘8", "小键盘9", "小键盘*", "小键盘+", "", "小键盘-", 
		"小键盘.", "小键盘/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", 
		"F9", "F10", "F11", "F12", "", "", "", "", "", "", 
		"", "", "", "", "", "", "", "", "", "", 
		"", "", "", "", "num_lock", "soroll_lock", "", "", "", "", 
		"", "", "", "", "", "", "", "", "", "", 
		"", "", "", "", "", "", "", "", "", "", 
		"", "", "", "", "", "", "", "", "", "", 
		"", "", "", "", "", "", ";", "=", ",", "-", 
		".", "/", "`", "", "", "", "", "", "", "", 
		"", "", "", "", "", "", "", "", "", "", 
		"", "", "", "", "", "", "", "", "", "[", 
		"\\", "]", "'"};
	//得到鼠标的位置(x,y)   左上角是(0,0), x上下, y左右 
	iv getxy(int &x, int &y) {
		POINT pt;
		HWND hwnd=GetForegroundWindow();
		GetCursorPos(&pt), ScreenToClient(hwnd,&pt);
		x=pt.y/16, y=pt.x/8;
	}
	//开/关光标显示(0关闭显示, 1开启显示) 
	iv mouse(int a) {
		HANDLE handle=Get;
		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(handle,&CursorInfo);
		CursorInfo.bVisible=a;
		SetConsoleCursorInfo(handle,&CursorInfo);
	}
	//移动光标到(x,y)
	iv goxy(int x, int y) {
		COORD position={y-1<<1, x-1};
		HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOut, position);
	}
	
	//文件的读取, 可以不管 
	inline string freads(FILE *in) {
		string res=""; char c;
		while(!isalpha(c=fgetc(in))) ;
		while(isalpha(c)) res+=c, c=fgetc(in);
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
	//输出字符串, print(颜色, 要输出的字符串) 
	iv writes(string s) {
		for(int i=0; s[i]; ++i) putchar(s[i]);
	}
	iv print(int c, string s) {
		color(c), writes(s), color(15);
	}
	//数字转字符串, 长度不满len填充' ' 
	inline string turns(int x, int len=0, char ad=' ') {
		string res="";
		if(x==0) res="0";
		while(x) res=char(x%10+48)+res, x/=10;
		while(res.size()<len) res+=ad;
		return res;
	}
	
	//按钮, 一个按钮有上下左右四个值, 上<=下, 左<=右 
	struct button {
		int u, d, l, r;
		button() {
			l=r=u=d=0;
		}
		button(int u, int d, int l, int r):
			u(u), d(d), l(l), r(r) {}
	};
	//需要开一个数组存储你开了的按钮, 然后在一个循环里不断引用getxy和button_check
	//上传: 你的按钮数组, 按钮数组的大小(我这个写的是从1开始存的), 鼠标的x轴位置, 鼠标的y轴位置
	//返回: 被按下的按钮在数组中的下标 
	ii button_check(button q[], int siz, int px, int py) {
		for(int i=1; i<=siz; ++i) if(px>=q[i].u&&px<=q[i].d&&py>=q[i].l&&py<=q[i].r) return i;
		return -1;
	}
	//记事本读入中文 
	inline string read_str(const char* str) {
		string s;
		WCHAR *strSrc;
		LPSTR szRes;
		int i=MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
		strSrc=new WCHAR[i+1];
		MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);
		i=WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
		szRes=new CHAR[i+1];
		WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
		s=szRes;
		delete[]strSrc;
		delete[]szRes;
		return s;
	}
	//可按空格跳过的sleep 
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
	//16进制: 0123456789:;<=>?
}
using namespace GB;

const int key_f[3][6]={
	{38, 39, 40, 37, 13, 0},
	{87, 68, 83, 65, 70, 71},
	{38, 39, 40, 37, 191, 190}};
int key[3][6]={
	{38, 39, 40, 37, 13, 0},
	{87, 68, 83, 65, 70, 71},
	{38, 39, 40, 37, 191, 190}};
ii choose(int user, int xtot, int ytot, int co, int stx, int sty, int dx=1, int dy=5) {
	int posx=1, posy=1, tx=stx, fpx=stx, ty=sty, fpy=sty, tik=clock();
	int edx=stx+(xtot-1)*dx, edy=sty+(ytot-1)*dy;
	while(1) if(clock()-tik>=80) {
//		goxy(11, 10), printf("%d", posx);
		tik=clock();
		goxy(fpx, fpy), print(0, " ");
		goxy(fpx=tx, fpy=ty), print(co, "*");
		if(keydown(key[user][0])) {
			while(keydown(key[user][0]));
			if(posx>1) tx-=dx, posx--;
			else tx=edx, posx=xtot;
		}
		if(keydown(key[user][2])) {
			while(keydown(key[user][2]));
			if(posx<xtot) tx+=dx, posx++;
			else tx=stx, posx=1;
		}
		if(keydown(key[user][1])) {
			while(keydown(key[user][1]));
			if(posy<ytot) ty+=dy, posy++;
			else ty=sty, posy=1;
		}
		if(keydown(key[user][3])) {
			while(keydown(key[user][1]));
			if(posy>1) ty-=dy, posy--;
			else ty=edy, posy=ytot;
		}
		if(keydown(key[user][4])) {
			while(keydown(key[user][4]));
			return (posx-1)*ytot+posy;
		}
	}
}

namespace MP_PY {
	const int MAX_X=256, MAX_Y=256;
	const string typ[16]={"xx", "  ", "[]"};
	int siz_x, siz_y, minix, maxix, miniy, maxiy;
	int col[MAX_X+10][MAX_Y+10];
	int flor[MAX_X+10][MAX_Y+10];
	int tox[MAX_X+10][MAX_Y+10], toy[MAX_X+10][MAX_Y+10], tof[MAX_X+10][MAX_Y+10];
	
	//PY
	const int fx[4]={-1, 0, 1, 0}, fy[4]={0, 1, 0, -1};
	const string fs[5]={"^", ">", "v", "<", "x"};
	void nxt_point(int &x, int &y, int f) {
		x+=fx[f], y+=fy[f];
	}
	ib inmap(int x, int  y) {
		return x>=minix&&x<=maxix&&y>=miniy&&y<=maxiy;
	}
	struct bul {
		int nx, ny, co, reco, f, speed, wait;
		bul() { nx=ny=-1, co=0, f=4; }
		bul(int a, int b, int c, int d, int sp, int sc=21): nx(a), ny(b), co(c), f(d), speed(sp), reco(sc-c) { wait=0; }
		iv hide() {
			goxy(nx, ny), print(col[nx][ny]*16, typ[flor[nx][ny]]);
		}
		iv show() {
			goxy(nx, ny), print(col[nx][ny]*16+co, "++");
		}
		inline bul nxt() {
			if(wait>0) return *this;
			bul tmp=*this;
			int now=flor[nx][ny];
			if(now==2&&tof[nx][ny]==f) tmp.nx=tox[nx][ny], tmp.ny=toy[nx][ny];
			else tmp.nx+=fx[f], tmp.ny+=fy[f];
			return tmp;
		}
		ib move() {
//			goxy(15, 15), printf("%d", wait);
			bul tmp=nxt();
			hide();
			if(inmap(tmp.nx, tmp.ny)) {
				*this=tmp;
				if(col[nx][ny]==co) col[nx][ny]=reco;
				return 1;
			}
			return 0;
		}
	};
	vector<bul> lin;
	ib atsam(bul a, bul b) { return a.nx==b.nx&&a.ny==b.ny; }
	ib alsam(bul a, bul b) { return atsam(a, b)&&a.f==b.f&&a.co==b.co; }
	ib check_hd(bul a, bul b) {
		if((a.f==0&&b.f==2||a.f==2&&b.f==0)&&abs(a.nx-b.nx)<=2&&a.ny==b.ny||
		   (a.f==1&&b.f==3||a.f==3&&b.f==1)&&abs(a.ny-b.ny)<=2&&a.nx==b.nx||
		   atsam(a.nxt(), b.nxt())) return 1;
	}
	iv move_bul() {
		int del[100], pos=0;
		rep(i, 0, lin.size()-1) rep(j, i+1, iup) {
			if(alsam(lin[i], lin[j])) del[pos++]=j;
			if(lin[i].co!=lin[j].co&&lin[i].f!=lin[j].f) {
				if(check_hd(lin[i], lin[j])) del[pos++]=i, del[pos++]=j;
			}
		}
		//move
		rep(i, 0, lin.size()-1) {
//			goxy(15+i, 15), printf("   ");
//			goxy(15+i, 15), printf("%d", lin[i].wait);
			lin[i].wait--;
			lin[i].hide();
			if(!inmap(lin[i].nx, lin[i].ny)) del[pos++]=i;
			if(lin[i].wait<=0) {
				if(!lin[i].move()) del[pos++]=i;
				lin[i].wait=lin[i].speed;
			}
		}
		sort(del, del+pos), pos=unique(del, del+pos)-del;
//		goxy(21, 20), printf("%d", pos);
		while(pos-->0) lin.erase(lin.begin()+del[pos]);
		rep(i, 0, lin.size()-1) lin[i].show();
	}
	const int totskill=8;
	const string skill_name[100]={"", "多排子弹", "大跳", "激光炮", "加特林机枪", "无畏冲撞", "强力子弹", "色彩力场", "艾草钻刺!"};
	const int str_tot_time[100]={0, 10, 8, 20, 20, 8, 8, 20, 3};
	const int skill_cost[100]={0, 3, 4, 4, 1, 4, 2, 1, 1};
	struct player {
		int id;
		int nx, ny, co, reco, state;
		int nf, sf;
		int walk_speed, walk_wait;// 移速为 1/w_s 每秒
		bool can_turn_sf, can_turn_nf, can_cover;
		int hav, maxi_hav, get_speed, pst;
		
		int skill, str_time;
		int machine_gun_time;
		int charge_time;
		int power_time;
		player() {
			skill=1;
			get_speed=10, maxi_hav=5;
		}
		iv hide() {
			goxy(nx, ny), print(col[nx][ny]*16, typ[flor[nx][ny]]);
		}
		ii show(bool die=0) {
			if(!die) {
				state=sf;
				goxy(nx, ny), print(co+col[nx][ny]*16, turns(hav, 1));
				print((str_time>=str_tot_time[skill]? 15: co)+col[nx][ny]*16, fs[state]);
			} else goxy(nx, ny), print(pwhite+col[nx][ny]*16, "X(");
		}
		iv init(int num, int a, int b, int c) {
			id=num;
			nx=a, ny=b, co=c, reco=21-co;
			hav=5, nf=sf=4, pst=0;
			state=4, str_time=0, walk_speed=1, can_turn_sf=can_turn_nf=1;
			machine_gun_time=charge_time=power_time=0;
		}
		ib move(int f, int cover=0) {
			int tx, ty, now=flor[nx][ny];
			if(now==2&&tof[nx][ny]==f) tx=tox[nx][ny], ty=toy[nx][ny];
			else tx=nx+fx[f], ty=ny+fy[f];
			if(cover&&col[tx][ty]==co) col[tx][ty]=reco;
			if(inmap(tx, ty)&&col[tx][ty]&&col[tx][ty]==reco) {
				hide(), nx=tx, ny=ty;
				return 1;
			}
			return 0;
		}
		ii walk(int f, int speed=1, int cover=0) {
			repf(i, speed) if(!move(f, cover)) return i-1;
			return speed;
		}
		iv shot(int f, int sx, int sy, int sp=2) {
			lin.push_back(bul(sx, sy, co, f, sp));
		}
		iv choose_skill() {
			system("cls");
			goxy(2, 4), print(co, "P"+turns(id)+"选择技能");
			repf(i, totskill) {
				goxy(2+i, 5), print(pwhite, skill_name[i]);
				goxy(2+i, 13), print(pwhite, "消耗"+turns(skill_cost[i]));
			}
//			goxy(10, 10), printf("acbc");
			skill=choose(id, totskill, 1, pwhite, 3, 4);
		}
		ib ask() {
			bool ed=0;
			rep(i, 0, 3) if(!ed&&keydown(key[id][i])) {
				if(can_turn_nf) nf=i, ed=1;
				if(can_turn_sf) sf=nf;
			}
			walk_wait--;
			if(charge_time) {
				charge_time=walk(nf, 2, 1);
				if(!charge_time) can_turn_nf=1;
			}
			if(ed) {
				bool fcan=can_cover;
				if(power_time) can_cover=1;
				if(walk_wait<=0) {
					if(walk_speed<0) walk(nf, 1, can_cover), walk_wait=-walk_speed;
					else walk(nf, walk_speed, can_cover), walk_wait=1;
				}
				can_cover=fcan;
			}
			
			if(keydown(key[id][5])) {
				str_time=0;
				switch(skill) {
					case 3: {
						walk_speed=1;
						break;
					}
					case 4: {
						walk_speed=1;
						can_turn_sf=1;
						machine_gun_time=0;
						break;
					}
				}
			}
			
			if(hav<maxi_hav) if(++pst==get_speed) hav++, pst=0;
			if(nf<4) {
				if(keydown(key[id][4])) {
					if(++str_time>=str_tot_time[skill]) {
						switch(skill) {
							case 3: {
								walk_speed=-2;
								break;
							}
							case 4: {
								if(hav>0) {
									walk_speed=-3;
									can_turn_sf=0;
									++machine_gun_time;
									if(machine_gun_time%2==0) shot(sf, nx, ny, 3);
									if(machine_gun_time%5==0) hav--;
								} else {
									walk_speed=1;
									can_turn_sf=1;
									machine_gun_time=0;
									str_time=0;
								}
								break;
							}
							case 7: {
								if(hav>0) {
									++power_time;
									if(power_time%3==0) hav--;
								} else {
									power_time=0;
								}
								break;
							}
						}
					}
				} else {
					if(str_time>=str_tot_time[skill]) {
						if(hav>=skill_cost[skill]) {
							hav-=skill_cost[skill];
							switch(skill) {
								case 1: {
									shot(sf, nx, ny);
									shot(sf, nx+fx[sf^1], ny+fy[sf^1]);
									shot(sf, nx+fx[sf^3], ny+fy[sf^3]);
									break;
								}
								case 2: {
									int tx=nx+fx[nf]*4, ty=ny+fy[nf]*4;
									while(col[tx][ty]==0||!inmap(tx, ty)) tx-=fx[nf], ty-=fy[nf];
									rep(x, max(tx-1, minix), min(tx+1, maxix)) rep(y, max(ty-1, miniy), min(ty+1, maxiy)) {
										if(col[x][y]==co) goxy(x, y), print((col[x][y]=reco)*16, typ[flor[x][y]]);
									}
									hide(), nx=tx, ny=ty;
									break;
								}
								case 3: {
									walk_speed=1;
									int x=nx, y=ny;
									while(inmap(x, y)) {
										if(col[x][y]==co) goxy(x, y), print((col[x][y]=reco)*16, typ[flor[x][y]]);
										x+=fx[nf], y+=fy[nf];
									}
									x=nx+fx[sf^1], y=ny+fy[sf^1];
									while(inmap(x, y)) {
										if(col[x][y]==co) goxy(x, y), print((col[x][y]=reco)*16, typ[flor[x][y]]);
										x+=fx[nf], y+=fy[nf];
									}
									x=nx+fx[sf^3], y=ny+fy[sf^3];
									while(inmap(x, y)) {
										if(col[x][y]==co) goxy(x, y), print((col[x][y]=reco)*16, typ[flor[x][y]]);
										x+=fx[nf], y+=fy[nf];
									}
									walk(sf^2, 1, 0);
									break;
								}
								case 4: {
									walk_speed=1;
									can_turn_sf=1;
									machine_gun_time=0;
									break;
								}
								case 5: {
									can_turn_nf=0;
									charge_time=1;
									break;
								}
								case 6: {
									shot(sf, nx, ny, 1);
									break;
								}
								case 7: {
									power_time=0;
									rep(x, max(nx-1, minix), min(nx+1, maxix)) rep(y, max(ny-1, miniy), min(ny+1, maxiy)) {
										if(col[x][y]==co) goxy(x, y), print((col[x][y]=reco)*16, typ[flor[x][y]]);
									}
									break;
								}
								case 8: {
									walk(nf, 3, 1);
									break;
								}
							}
						} else {
							switch(skill) {
								case 3: {
									walk_speed=1;
									break;
								}
								case 4: {
									walk_speed=1;
									can_turn_sf=1;
									break;
								}
							}
						}
					} else if(str_time>0&&hav) shot(sf, nx, ny), hav--;
					str_time=0;
				}
			}
			
			if(power_time) col[nx][ny]=reco;
			if(col[nx][ny]==reco) return 0;
			return 1;
		}
	}p[3];
	
	//MP
	iv show() {
		rep(x, minix, maxix) rep(y, miniy, maxiy) goxy(x, y), print(col[x][y]*16, typ[flor[x][y]]);
		p[1].show(), p[2].show();
	}
	#define map_nxt (map_seed[map_pos++]^48)
	#define spc_nxt (spc_seed[spc_pos++]^48)
	#define map_nxt2 (map_nxt*16+map_nxt)
	#define spc_nxt2 (spc_nxt*16+spc_nxt)
	iv init(string map_seed, string spc_seed) {
		lin.clear();
		
		int map_pos=0;
		siz_x=map_nxt2, siz_y=map_nxt2;
		minix=1, maxix=minix+siz_x-1, miniy=1, maxiy=miniy+siz_y-1;
		
		int x=map_nxt2, y=map_nxt2;
		p[1].init(1, x, y, pblue);
		x=map_nxt2, y=map_nxt2;
		p[2].init(2, x, y, pred);
		
		rep(x, minix, maxix) rep(y, miniy, maxiy) {
			int num=map_nxt;
			col[x][y]=(num? ((num&1)? pred: pblue): 0);
			flor[x][y]=map_nxt;
		}
		
		int spc_pos=0, tot=spc_nxt2;
		repf(i, tot) {
			int kind=spc_nxt2;
			if(kind==1) {
				int x=spc_nxt2, y=spc_nxt2, tx=spc_nxt2, ty=spc_nxt2, tf=spc_nxt2;
				tox[x][y]=tx, toy[x][y]=ty, tof[x][y]=tf;
//				goxy(15+i, 30), printf("%d %d %d %d", x, y, tx, ty);
			}
		}
		
	}
	#undef map_nxt
	#undef spc_nxt
	#undef map_nxt2
	#undef spc_nxt2
	namespace TEST {
		void show__(bul a) {
			printf("%d %d %d %d", a.nx, a.ny, a.f, a.co);
		}
		void test__() {
			system("cls");
			cout<<lin.size()<<endl;
//			goxy(20, 1);
			rep(i, 0, lin.size()-1) rep(j, i+1, iup) if(lin[i].co!=lin[j].co&&lin[i].f!=lin[j].f) {
				show__(lin[i]), printf("  "), show__(lin[j]);
				if(alsam(lin[i], lin[j])) cout<<"!";
				puts("");
			}
		}
	}
}

namespace BS {
	int totmap=4;
	bool first_play=1;
	string map_seed[100]= {
		"",
		"080901010809111111111111111111112121211111212121112100211111002121112121001111112121111121212100111121111100212111001121111111212111111121212121212121212121",
		"050;0101050;11212121210011111111112121212121001111111111212121212100111111111121212121210011111111112121212121001111111121",
		"07070202060600001200000000001111111111000011111111111200111100212100222121212121000021212121210000000000220000",
//		"070602010606020202020200111100000002021111000002020011210002020000212102020000002121000202020202",
		"0?0?03030=0=111111111111111100111111111111111111111111111111111111111111111111000011111121210000111111212100001111111121212121001111212100111111111121212121001111212211111111111121222121211111212111111111110021212121211111212111111111000000212121211111212111111111110021212121211111212111111112112121212121211211212100111111112121212121001111212100111111112121212100001111212121000011112121210000212121212121212121212121212121212121212121212121002121212121212121"
	};
	/*
	传送门 01 x y tx ty f
	*/
	string spc_seed[100]= {
		"",
		"00",
		"00",
		"04010103070500010705010302010501030703010307050101",
//		"12010101070200010102070300010103070400010104070500010105070600010702010102010703010202010704010302010705010402010706010502010301020603010401030603010501040603010601050603010206030101010306040101010406050101010506060101",
		"040106020:0>00010:0>06020201060:0:0601010:06060:03"
	};
	
	int key_use[3][232];
	iv data_save() {
		FILE *fout=fopen("INVdata.txt", "w");
		fwrites(turns(first_play)+' ', fout);
		rep(i, 0, 2) rep(j, 0, 5) fwrites(turns(key[i][j])+' ', fout);
		repf(i, 2) fwrites(turns(MP_PY::p[i].skill)+' ', fout);
		fclose(fout);
	}
	iv data_read() {
		FILE *fin;
		if(!(fin=fopen("INVdata.txt", "r"))) data_save();
		fin=fopen("INVdata.txt", "r");
		first_play=fread(fin);
		rep(i, 0, 2) rep(j, 0, 5) key_use[i][key[i][j]=fread(fin)]=1;
		repf(i, 2) MP_PY::p[i].skill=fread(fin);
		fclose(fin);
	}
	
	iv key_setter(int user) {
		setting:;
		MP_PY::p[1].init(1, 0, 0, pblue);
		MP_PY::p[2].init(2, 0, 0, pred);
		while(keydown(key[user][4]));
		system("cls");
		goxy(1, 4), print(pwhite, "页面按键设置");
		goxy(4, 5), print(pwhite, "上          "+in_key[key[user][0]]);
		goxy(5, 5), print(pwhite, "右          "+in_key[key[user][1]]);
		goxy(6, 5), print(pwhite, "下          "+in_key[key[user][2]]);
		goxy(7, 5), print(pwhite, "左          "+in_key[key[user][3]]);
		goxy(8, 5), print(pwhite, "选中/攻击   "+in_key[key[user][4]]);
		if(user) goxy(9, 5), print(pwhite, "取消/用道具 "+in_key[key[user][5]]);
		if(user) goxy(10, 5), print(pwhite, "技能        "+MP_PY::skill_name[MP_PY::p[user].skill]);
		goxy(9+2*(user>0), 5), print(pwhite, "保存并退出");
		goxy(10+2*(user>0), 5), print(pwhite, "重置");
		goxy(12+2*(user>0), 4), print(pwhite, "注意: esc, shift, ctrl, alt, win, fn, \
		右键菜单键, 鼠标, 以及部分小键盘按键 无法使用");
		int chos_=choose(user, 7+2*(user>0), 1, pwhite, 4, 4);
		if(user&&chos_==7) {
			goxy(10, 10), printf("%d", user);
			MP_PY::p[user].choose_skill();
			goto setting;
		}
		if(chos_==6+2*(user>0)) {
			data_save();
			return;
		}
		if(chos_==7+2*(user>0)) {
			rep(i, 0, 4) key[user][i]=key_f[user][i];
			goto setting;
		}
		goxy(3+chos_, 4), print(pred, "*");
		while(keydown(key[user][4]));
		while(1) {
			repf(i, 222) if(keydown(i)) {
				if(i==27) goto setting;
				if(in_key[i]!=""&&!key_use[0][i]) {
					key_use[user][key[user][chos_-1]]=0;
					key_use[user][key[user][chos_-1]=i]=0;
					goto setting;
				}
			}
		}
	}
	
	iv test_major() {
		data_read();
		if(first_play) {
			goxy(1, 1), print(pwhite, "如果你是第一次玩, 请认真阅读以下内容:"), sleep(1000);
			goxy(2, 1), print(pwhite, "  按空格可以跳过大部分等待时间"), sleep(1000);
			goxy(3, 1), print(pwhite, "  主页按键为 ");
			rep(i, 0, 3) print(pwhite, in_key[key[0][i]]);
			print(pwhite, " 移动光标, ");
			print(pwhite, in_key[key[0][4]]);
			print(pwhite, " 确定"), sleep(1000);
			goxy(4, 1), print(pwhite, "  蓝色为P1, 红色为P2"), sleep(1000);
			goxy(5, 1), print(pblue, "  P1 按键为 ");
			rep(i, 0, 3) print(pblue, in_key[key[1][i]]);
			print(pblue, " 移动、移动光标, ");
			print(pblue, in_key[key[1][4]]);
			print(pblue, " 攻击、确定 ");
			print(pblue, in_key[key[1][5]]);
			print(pblue, " 取消攻击、使用道具"), sleep(1000); 
			goxy(6, 1), print(pred, "  P2 按键为 ");
			rep(i, 0, 3) print(pred, in_key[key[2][i]]);
			print(pred, " 移动、移动光标, ");
			print(pred, in_key[key[2][4]]);
			print(pred, " 攻击、确定 ");
			print(pred, in_key[key[2][5]]);
			print(pred, " 取消攻击、使用道具"), sleep(1000); 
			goxy(7, 1), print(pwhite, "  你只能在和自己相反颜色的方块上行动"), sleep(1000);
			goxy(8, 1), print(pwhite, "  子弹会让和你同色的方块改变颜色"), sleep(1000);
			goxy(9, 1), print(pwhite, "  击杀敌人就可以获得胜利"), sleep(1000);
			goxy(10, 1), print(pwhite, "  作者 子丑(ztue)"), sleep(1000);
			goxy(11, 1), print(pwhite, "以后可以在 帮助 中重新查看这段话\n"), sleep(1000);
			system("PAUSE");
			first_play=0;
			data_save();
		}
		while(1) {
			system("cls");
			goxy(1, 1), print(pwhite, "欢迎来到 INVERSUS (DEMO)");
			goxy(2, 1), print(pwhite, "本游戏非原创, 可以去 steam 搜索同名游戏购买游玩");
			goxy(4, 5), print(pwhite, "开始游戏");
			goxy(5, 5), print(pwhite, "设置");
			goxy(6, 5), print(pwhite, "帮助");
			goxy(7, 5), print(pwhite, "退出");
			int chos=choose(0, 4, 1, pwhite, 4, 4);
			switch(chos) {
				case 1: {
					system("cls");
					goxy(1, 4), print(pwhite, "选择地图");
					repf(i, totmap) goxy(2+i, 5), print(pwhite, turns(i));
					goxy(3+totmap, 5), print(pwhite, "返回主菜单");
					int chos_map=choose(0, totmap+1, 1, pwhite, 3, 4);
					if(chos_map>totmap) break;
					play:;
					MP_PY::init(map_seed[chos_map], spc_seed[chos_map]);
					system("cls");
					MP_PY::show();
					int game_tik=40;
					int tik=clock(), tik_cnt=0;
					bool die1=0, die2=0;
					while(1) if(clock()-tik>=game_tik) {
						tik=clock();
						MP_PY::move_bul();
						if(++tik_cnt==2) {
							tik_cnt=0;
							if(MP_PY::p[1].ask()) die1=1;
							if(MP_PY::p[2].ask()) die2=1;
						}
						MP_PY::p[1].show(die1);
						MP_PY::p[2].show(die2);
						if(die1||die2) break;
					}
					Sleep(1000);
					system("cls");
					goxy(1, 4);
					if(!die1) print(pwhite, "player 1 win!");
					else if(!die2) print(pwhite, "player 2 win!");
					else print(pwhite, "平局!");
					goxy(3, 5), print(pwhite, "重新开始");
					goxy(4, 5), print(pwhite, "返回主菜单");
					int chos_=choose(0, 2, 1, pwhite, 3, 4);
					if(chos_==1) goto play;
					break;
				}
				case 2: {
					setting:;
					system("cls");
					goxy(1, 4), print(pwhite, "设置列表");
					goxy(3, 5), print(pwhite, "页面按键");
					goxy(4, 5), print(pwhite, "玩家1");
					goxy(5, 5), print(pwhite, "玩家2");
					goxy(6, 5), print(pwhite, "返回主菜单");
					int chos_=choose(0, 4, 1, pwhite, 3, 4);
					if(chos_==1) key_setter(0);
					if(chos_==2) key_setter(1);
					if(chos_==3) key_setter(2);
					if(chos_==4) break;
					goto setting;
				}
				case 3: {
					system("cls");
					goxy(1, 1), print(pwhite, "按空格可以跳过大部分等待时间"), sleep(1000);
					goxy(2, 1), print(pwhite, "主页按键为 ");
					rep(i, 0, 3) print(pwhite, in_key[key[0][i]]);
					print(pwhite, " 移动光标, ");
					print(pwhite, in_key[key[0][4]]);
					print(pwhite, " 确定"), sleep(1000);
					goxy(3, 1), print(pwhite, "蓝色为P1, 红色为P2"), sleep(1000);
					goxy(4, 1), print(pblue, "P1 按键为 ");
					rep(i, 0, 3) print(pblue, in_key[key[1][i]]);
					print(pblue, " 移动、移动光标, ");
					print(pblue, in_key[key[1][4]]);
					print(pblue, " 攻击、确定 "), sleep(1000);
					print(pblue, in_key[key[1][5]]);
					print(pblue, " 取消攻击、使用道具");
					goxy(5, 1), print(pred, "P2 按键为 ");
					rep(i, 0, 3) print(pred, in_key[key[2][i]]);
					print(pred, " 移动、移动光标, ");
					print(pred, in_key[key[2][4]]);
					print(pred, " 攻击、确定 ");
					print(pred, in_key[key[2][5]]);
					print(pred, " 取消攻击、使用道具"), sleep(1000); 
					goxy(6, 1), print(pwhite, "你只能在和自己相反颜色的方块上行动"), sleep(1000);
					goxy(7, 1), print(pwhite, "子弹会让和你同色的方块改变颜色"), sleep(1000);
					goxy(8, 1), print(pwhite, "击杀敌人就可以获得胜利"), sleep(1000);
					goxy(9, 1), print(pwhite, "作者 子丑(ztue)\n"), sleep(1000);
					system("PAUSE");
					break;
				}
				case 4: {
					return;
					break;
				}
			}
		}
	}
}

int main() {
//	while(1) repf(i, 250) if(keydown(i)) printf("%d ", i), cout<<(char)i<<endl;
	mouse(0);
	BS::test_major();
	system("cls");
	print(pwhite, "INVERSUS");
	mouse(1);
	return 0;
}
