#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include "loading.cpp"
#include "points.cpp"

using namespace std;

void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Showcursor()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = TRUE;  // Hi?n th? con tr? chu?t
    Info.dwSize = 20;      // Kích thu?c con tr? chu?t (tùy ch?nh theo nhu c?u)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void SetBackgroundColor(int color) {
    // L?y handle c?a console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // L?y thông tin hi?n t?i c?a console screen buffer
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    // Thi?t l?p màu n?n m?i
    SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0x0F) | (color << 4));
}
void box(int x, int y, int w, int h, int t_color, int b_color, const string& nd) {
    int ix, iy;
    SetColor(7);
    gotoXY(x+w/2 - 5, y + 3);
    SetBackgroundColor(t_color,0);
    cout << nd << endl;
    SetBackgroundColor(b_color,0);

    if (h <= 1 || w <= 1) {
        return;
    }

    for (ix = x; ix <= x + w; ix++) {
        gotoXY(ix, y);
        cout << (char)196;
        gotoXY(ix, y + h);
        cout << (char)196;
    }

    for (iy = y; iy <= y + h; iy++) {
        gotoXY(x, iy);
        cout << (char)179;
        gotoXY(x + w, iy);
        cout << (char)179;
    }

    gotoXY(x, y);
    cout << (char)218;
    gotoXY(x + w, y);
    cout << (char)191;
    gotoXY(x, y + h);
    cout << (char)192;
    gotoXY(x + w, y + h);
    cout << (char)217;
    SetBackgroundColor(0,0);
}

void clearinfo(int x, int y, int z)
{
	gotoXY(x + 3, y + 2);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 3);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 4);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 5);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 6);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 7);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 8);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 9);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 10);
	cout << left << setw(z) << " ";
}
void clearpoint(int x, int y, int z) {
	gotoXY(x + 3, y + 2);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 3);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 4);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 5);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 6);
	cout << left << setw(z) << " ";
	gotoXY(x + 3, y + 7);
	cout << left << setw(z) << " ";
	gotoXY(x+3, y+9);
	cout <<left<<setw(z)<<" ";
}

class Sinhvien
{
	string ten,gioitinh,ngaysinh,diachi,khoa,lop,hoanthanh;
	int masv,sdt;
	double gpa;
	Points point;
public:
	Sinhvien() : ten(""), gioitinh(""), ngaysinh(""),diachi(""), khoa(""),lop(""),hoanthanh("0/0"), masv(0), sdt(0),gpa(0) {}
	string getName()
	{
		return ten;
	}
	Points getPoint() {
		return point;
	}
	int getid()
	{
		return masv;
	}
	void setname()
	{
		cout<<"Nhap ten: "; getline(cin,ten);
	}
	void setgioitinh()
	{
		cout<<"Nhap gioi tinh: "; cin>>gioitinh;
	}
	void setbirth()
	{
		cout<<"Nhap ngay sinh: "; cin>>ngaysinh;
	}
	void setphone()
	{
		cout<<"Nhap so dien thoai: "; cin>>sdt;
	}
	void setaddress()
	{
		cout<<"Nhap dia chi: "; getline(cin,diachi);
	}
	void getinfo(ifstream& fin, ifstream& fin2)
	{
		string str, info;
        getline(fin, str);
        stringstream ss(str);
        getline(ss, info, ',');
        stringstream a(info);
        a >> masv;
        getline(ss, ten, ',');
        getline(ss, gioitinh, ',');
        getline(ss, ngaysinh, ',');
        getline(ss, lop, ',');
        getline(ss, khoa, ',');
        getline(ss, info, ',');
        stringstream b(info);
        b >> sdt;
        getline(ss, diachi, ',');
        getline(ss, info, ',');
        stringstream c(info);
        c >> gpa;
        getline(ss,hoanthanh,',');
        point.getFull(fin2);
	}
	
	void getin4keyboard(int x, int y)
	{
		gotoXY(x + 3, y + 8);
		cout<<left<<setw(1)<<" ";
		gotoXY(x + 3, y + 2);
		cout<<left<<setw(1)<<" ";
		gotoXY(x + 3, y + 2);
		while (true) {
			cin>>masv;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				gotoXY(x + 3, y + 2);
				cout<<"Khong hop le!Vui long nhap lai!";
				Sleep(1500);
				gotoXY(x+3,y+2);
				cout<<setw(32)<<" ";
				gotoXY(x+3,y+2);
			} else {
				break;
			}
		}
	
	    gotoXY(x + 3, y + 3);
	    cin.ignore();
	    getline(cin,ten);
	
	    gotoXY(x + 3, y + 4);
	    getline(cin,gioitinh);
	
	    gotoXY(x + 3, y + 5);
		getline(cin,ngaysinh);
	
	    gotoXY(x + 3, y + 6);
	    getline(cin,lop);
	
	    gotoXY(x + 3, y + 7);
	    getline(cin,khoa);
	
	    gotoXY(x + 3, y + 8);
	    while (true) {
			cin>>sdt;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				gotoXY(x + 3, y + 8);
				cout<<"Khong hop le!Vui long nhap lai!";
				Sleep(1500);
				gotoXY(x+3,y+8);
				cout<<setw(32)<<" ";
				gotoXY(x+3,y+8);
			} else {
				break;
			}
		}
	
	    gotoXY(x + 3, y + 9);
	    cin.ignore();
	    getline(cin,diachi);
	
	    gotoXY(x + 3, y + 10);
	    while (true) {
			cin>>gpa;
			if (cin.fail() || gpa>4.0 || gpa<0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				gotoXY(x + 3, y + 10);
				cout<<"Khong hop le!Vui long nhap lai!";
				Sleep(1500);
				gotoXY(x+3,y+10);
				cout<<setw(32)<<" ";
				gotoXY(x+3,y+10);
			} else {
				break;
			}
		}
	}
	
	void displaytuition(int x, int y) {
		gotoXY(x + 3, y + 2);
	    cout << left << setw(20) << "MaSV" << "| " << masv << endl;
	
	    gotoXY(x + 3, y + 3);
	    cout << left << setw(20) << "TenSV" << "| " << ten << endl;
	
	    gotoXY(x + 3, y + 4);
	    cout << left << setw(20) << "Lop " << "| " << lop << endl;
	
	    gotoXY(x + 3, y + 5);
	    cout << left << setw(20) << "Khoa " << "| " << khoa << endl;
	}
	
	void displayinfo(int x, int y)
	{  
	    gotoXY(x + 3, y + 2);
	    cout << left << setw(20) << "MaSV" << "| " << masv << endl;
	
	    gotoXY(x + 3, y + 3);
	    cout << left << setw(20) << "TenSV" << "| " << ten << endl;
	
	    gotoXY(x + 3, y + 4);
	    cout << left << setw(20) << "Gioi tinh " << "| " << gioitinh<< endl;
	
	    gotoXY(x + 3, y + 5);
	    cout << left << setw(20) << "Ngay sinh " << "| " << ngaysinh << endl;
	
	    gotoXY(x + 3, y + 6);
	    cout << left << setw(20) << "Lop " << "| " << lop << endl;
	
	    gotoXY(x + 3, y + 7);
	    cout << left << setw(20) << "Khoa " << "| " << khoa << endl;
	
	    gotoXY(x + 3, y + 8);
	    cout << left << setw(20) << "SDT " << "| " << sdt << endl;
	
	    gotoXY(x + 3, y + 9);
	    cout << left << setw(20) << "Dia chi " << "| " << endl;
	
	    gotoXY(x + 3, y + 10);
	    cout << left << setw(20) << "GPA " << "| " << endl;
	}
	void displayPoint(int x, int y)
	{  
	    gotoXY(x + 3, y + 2);
	    cout << left << setprecision(2) << setw(20) << "Giai tich 2 " << "| " << point.getGt() << endl;
	
	    gotoXY(x + 3, y + 3);
	    cout << left << setprecision(2) << setw(20) << "Anh van A2.2 " << "| " << point.getAv() << endl;
	
	    gotoXY(x + 3, y + 4);
	    cout << left << setprecision(2) << setw(20) << "Vat li ban dan " << "| " << point.getVlbd() << endl;
	
	    gotoXY(x + 3, y + 5);
	    cout << left << setprecision(2) << setw(20) << "Lap trinh OOP " << "| " << point.getoop() << endl;
	
	    gotoXY(x + 3, y + 6);
	    cout << left << setprecision(2) << setw(20) << "Vat li 2 " << "| " << point.getVl2() << endl;
	
	    gotoXY(x + 3, y + 7);
	    cout << left << setprecision(2) << setw(20) << "PBL1: Lap trinh " << "| " << point.getPbl() << endl;

	    gotoXY(x + 3, y + 9);
	    cout << left << setprecision(3) << setw(20) << "GPA(t10) " << "| " << point.getgpa() << endl;
	}
};

class DSSV
{
	vector<Sinhvien> list;
	int n = 0;
public:
	void getFullInfo(ifstream& fin,ifstream& fin2)
	{
		string line;
		getline(fin,line);
		while(!fin.eof())
		{
			Sinhvien sv;
			sv.getinfo(fin,fin2);
			list.push_back(sv);
			n++;
		}
	}
	
	void editInfo();
	void clearInfo();
	void addInfo();
	void displayPoints();
	void editPoints();
	void tuition();
	
	void display() {
		Nocursortype();
		Sinhvien sv;
		box(28, 1, 65, 15, 2, 8, "");
		SetBackgroundColor(5,0);
		gotoXY(47, 1);
		cout << "==== Thong tin sinh vien ====" << endl;
		SetBackgroundColor(0,0);
		
		int i = 0;
		while (true) {
			SetColor(2);
		    gotoXY(28 + 3, 3 + 1);
		    cout << left << setw(20) << "STT" << "| " << i + 1 << endl;
		    clearinfo(50,3,20);
		    list[i].displayinfo(28,3);
		    box(75, 4, 13, 8, 5, 2, "");
		    SetColor(3);
		    gotoXY(75 + 4,8);
		    cout<<"Image";
		    gotoXY(28 + 2, 15);
		    cout<< i + 1 << "\\" << n - 1 << ", chua dang nhap, dang nhap de xem toan bo thong tin!";
		    char phim = getch();
		    
		    if (phim==8)
		    {
		    	system("cls");
		    	while(true)
		    	{
		    		SetColor(4);
		    		cout<<"Ban chac cham muon xoa!Thong tin da xoa khong the phuc hoi!Nhan Enter de xac nhan hoac 'q' de huy!!\n";
		    		char phim1 = getch();
		    		if (phim1=='q')
		    		{
		    			system("cls");
		    			box(28, 1, 65, 15, 2, 8, "");
						SetBackgroundColor(5,0);
						gotoXY(47, 1);
						cout << "==== Thong tin sinh vien ====" << endl;
						SetBackgroundColor(0,0);
		    			break;
					}
		    		if (phim1==13)
		    		{
		    			system("cls");
		    			list.erase(list.begin()+i);
		    			n--;
		    			box(28, 1, 65, 15, 2, 8, "");
						SetBackgroundColor(5,0);
						gotoXY(47, 1);
						cout << "==== Thong tin sinh vien ====" << endl;
						SetBackgroundColor(0,0);
		    			break;
					}
				}
			}
		
		    switch (phim) {
		      case 75:
		      	gotoXY(28+3,3+1);
		        i--;
		        if (i < 0) {
		          i = n - 2;
		        }
		        break;
		      case 77:
		        i++;
		        if (i >= n - 1) {
		          i = 0;
		        }
		        break;
		      case 'q':
		      	system("cls");
		        return;
		    }
		  }
		}
	
};

void select(int i) {
    switch (i) {
        case 1:
            cout << "In thong thong tin sinh vien." << endl;
            break;
        case 2:
            cout << "Chinh sua thong tin sinh vien." << endl;
            break;
        case 3:
            cout << "Them thong tin sinh vien." << endl;
            break;
        case 4:
            cout << "Ket qua hoc tap sinh vien(danh cho sinh vien)." << endl;
            break;
        case 5:
            cout << "ket qua hoc tap sinh vien(danh cho giang vien)." << endl;
            break;
        case 6:
            cout << "Loc thong tin sinh vien theo yeu cau." << endl;
            break;
        case 7:
            cout << "Dang ki hoc(danh cho sinh vien)." << endl;
            break;
        case 8:
            cout << "Hoc phi." << endl;
            break;
        case 9:
            cout << "Thoat." << endl;
            break;
    }
}

int menu(int luachon, int soluongluachon) {

    Nocursortype();

    int start_x = 29 + (65 - 20) / 2;
    int start_y = 3 + (20 - soluongluachon - 4) / 2;
    
    while (true) {
        box(28, 1, 65, 20, 4, 1, "");
        box(29,2,63,18,4,1,"====OPTION====");

        for (int i = 1; i <= soluongluachon; ++i) {
            gotoXY(start_x - 14, start_y + i + 1);
            if (i == luachon) {
            	SetColor(0x07);
                cout << "> ";
                SetBackgroundColor(1,0);
            } else {
                SetColor(0x07);
                cout << "  ";
            }
            cout << i << ". ";
            select(i);
        }
        SetColor(0x07);
        gotoXY(start_x, start_y + soluongluachon + 3);
        char phim = getch();
        switch (phim) {
            case 72: // Phím mui tên lên
                luachon--;
                if (luachon < 1) {
                    luachon = soluongluachon;
                }
                break;
            case 80: // Phím mui tên xu?ng
                luachon++;
                if (luachon > soluongluachon) {
                    luachon = 1;
                }
                break;
            case 13:
                system("cls"); 
                return luachon;
            default:
                break;
        }
    }
}

void dk() {
	while (true) {
		box(28, 1, 65, 11, 2, 8, "");
		gotoXY(42,3);
		SetColor(2);
		cout<<"Dang ki hoc cho sinh vien nam nhat(k23)";
		gotoXY(36,4);
		cout<<"Nam hoc: 2023-2024 \t\t LopSH: chua dang nhap";
		gotoXY(40,7);
		cout<<"Hien khong phai thoi gian dang ki hoc";
		gotoXY(31,10);
		cout<<"Nhan 'q' de tro lai! Ban co the truy cap nhung chuc nang khac!";
		char c = _getch();
		if (c == 'q') {
			break;
		}
	}
	system("cls");
}

void option(DSSV sv)
{
	while (true)
	{
		int select = menu(1,9);
		switch (select)
		{
			case 1:
				sv.display();
				break;
			case 2:
				sv.editInfo();
				break;
			case 3:
				sv.addInfo();
				break;
			case 4:
				sv.displayPoints();
				break;
			case 7:
				dk();
				break;
			case 8:
				sv.tuition();
				break;
			case 9:
				return;
		}
	}
}
string convert(int x) {
	string s = to_string(x);
	string results = "";
	int j = 0;
	for (int i=s.length()-1;i>=0;i--) {
		if (j%3==0 && j>0) {
			results = '.' + results;
		}
		j++;
		results = s[i] + results;
	}
	return results;
}

int main() {
    int luachon = 1, soluongluachon = 9;
    ifstream fin("info.csv");
//    sv.editInfo();
    ifstream fin2("points.csv");
    loading();
    DSSV sv;
    sv.getFullInfo(fin, fin2);
//    sv.displayPoints();
//    sv.check();
    option(sv);
    closing();
}

void DSSV::editInfo()
{
	system("cls");
	Nocursortype();
//	Showcursor();
	int current = 0, select, luachon = 1, soluongluachon = 6;
	bool check = false;
	box(5, 1, 40, 20, 4, 1, "");
	box(50, 3, 65, 15, 2, 8, "");
	box(97, 7, 13, 8, 5, 2, "");
	SetColor(3);
	gotoXY(97 + 4,11);
	cout<<"Image";
	//list[0].displayinfo(50,5);
	gotoXY(13,3);
	cout<<"Thong tin muon chinh sua";
	string a[7] = {"","Ten","Ngay sinh", "Gioi tinh","SDT", "Dia chi","Tro lai"};
	int i = 0;
	bool running = true;
	while (running)
	{
		system("cls");
		Nocursortype();
	//	Showcursor();
		int current = 0, select, luachon = 1, soluongluachon = 6;
		bool check = false;
		box(5, 1, 40, 20, 4, 1, "");
		box(50, 3, 65, 15, 2, 8, "");
		box(97, 7, 13, 8, 5, 2, "");
		SetColor(3);
		gotoXY(97 + 4,11);
		cout<<"Image";
		//list[0].displayinfo(50,5);
		gotoXY(13,3);
		cout<<"Thong tin muon chinh sua";
		string a[7] = {"","Ten","Ngay sinh", "Gioi tinh","SDT", "Dia chi","Tro lai"};
		check = false;
		while (!check) {
			SetColor(2);
			clearinfo(72,3,20);
			gotoXY(50 + 3, 5 + 1);
			cout << left << setw(20) << "STT" << "| " << i + 1 << endl;
			list[i].displayinfo(50,5);
			gotoXY(53+ 1, 17);
			cout<< i + 1 << "\\" << n - 1 << ", chua dang nhap, dang nhap de xem toan bo thong tin!";
			char phim = getch();
			if (phim == 'q')
			{
				running = false;
				break;
			}
			switch (phim) {
			    case 75:
			      	gotoXY(50+3,5+1);
			        i--;
			        if (i < 0) {
			          i = n - 2;
			        }
			        break;
			    case 77: 
			        i++;
			        if (i >= n - 1) {
			          i = 0;
			        }
			        break;
				case 13:
			    	current = i;
			    	check = true;
			}
		}
		
		while (check) {
			SetColor(2);
			list[current].displayinfo(50,5);
			gotoXY(7,20);
			cout<<"Mot so thong tin khong the chinh sua!!";
			int start_x = 30, start_y = 6; 
	        for (int i = 1; i <= soluongluachon; ++i) {
	            gotoXY(start_x - 14, start_y + i + 1);
	            if (i == luachon) {
	            	SetColor(2);
	                cout << "> ";
	                SetBackgroundColor(1,0);
	            } else {
	                SetColor(2);
	                cout << "  ";
	            }
	            cout << i << ". " <<a[i];
	        }
	        SetColor(2);
	        gotoXY(start_x, start_y + soluongluachon + 3);
	        char phim = getch();
	        switch (phim) {
	            case 72:
	                luachon--;
	                if (luachon < 1) {
	                    luachon = soluongluachon;
	                }
	                break;
	            case 80:
	                luachon++;
	                if (luachon > soluongluachon) {
	                    luachon = 1;
	                }
	                break;
	            case 13:
	                select = luachon;
	                gotoXY(8,16);
					switch(luachon)
					{
						case 1:
							list[current].setname();
							clearinfo(72,5,20);
							gotoXY(8,16);
							cout<<left<<setw(36)<<" ";
							luachon = 1;
							break;
						case 2:
							list[current].setbirth();
							clearinfo(72,5,20);
							gotoXY(8,16);
							cout<<left<<setw(36)<<" ";
							luachon = 1;
							break;
						case 3:
							list[current].setgioitinh();
							clearinfo(72,5,20);
							gotoXY(8,16);
							cout<<left<<setw(36)<<" ";
							luachon = 1;
							break;
						case 4:
							list[current].setphone();
							clearinfo(72,5,20);
							gotoXY(8,16);
							cout<<left<<setw(36)<<" ";
							luachon = 1;
							break;
						case 5:
							list[current].setaddress();
							clearinfo(72,5,20);
							gotoXY(8,16);
							cout<<left<<setw(36)<<" ";
							luachon = 1;
							break;
						case 6:
							system("cls");
							check = false;
							break;
					}
	            default:
	                break;
	        }
		}
	}
	system("cls");	
}
void DSSV::addInfo()
{
	box(28, 1, 65, 15, 2, 8, "");
	Sinhvien sv;
	SetBackgroundColor(5,0);
	gotoXY(47, 1);
	cout << "==== Thong tin sinh vien ====" << endl;
	SetBackgroundColor(0);
	SetColor(2);
	gotoXY(28 + 3, 3 + 1);
	cout << left << setw(20) << "STT" << "| " << n << endl;
	sv.displayinfo(28,3);
	Showcursor();
	sv.getin4keyboard(50,3);
	list.insert(list.begin() + n - 1,sv);
	n++;
	box(75, 4, 13, 8, 5, 2, "");
	SetColor(3);
	gotoXY(75 + 4,8);
	cout<<"Image";
	gotoXY(28 + 2, 15);
	system("cls");
}

void DSSV::displayPoints()
{
	system("cls");
	Nocursortype();
//	Showcursor();
	int current = 0, select, luachon = 1, soluongluachon = 6;
	bool check = false;
	box(5, 1, 40, 20, 4, 1, "");
	box(50, 3, 65, 15, 2, 8, "");
	box(97, 7, 13, 8, 5, 2, "");
	SetColor(3);
	gotoXY(97 + 4,11);
	cout<<"Image";
	//list[0].displayinfo(50,5);
	string a[7] = {"","Ten","Ngay sinh", "Gioi tinh","SDT", "Dia chi","Tro lai"};
	int i = 0;
	bool running = true;
	while (running)
	{
		system("cls");
		Nocursortype();
	//	Showcursor();
		int current = 0, select, luachon = 1, soluongluachon = 6;
		bool check = false;
		box(5, 1, 40, 20, 4, 1, "");
		box(50, 3, 65, 15, 2, 8, "");
		box(97, 7, 13, 8, 5, 2, "");
		SetColor(3);
		gotoXY(97 + 4,11);
		cout<<"Image";
		//list[0].displayinfo(50,5);
		gotoXY(15,3);
		cout<<"Bang diem ki gan nhat";
		string a[7] = {"","Ten","Ngay sinh", "Gioi tinh","SDT", "Dia chi","Tro lai"};
		check = false;
		while (!check) {
			SetColor(2);
			clearinfo(72,3,20);
			clearpoint(32,5,6);
			gotoXY(50 + 3, 5 + 1);
			cout << left << setw(20) << "STT" << "| " << i + 1 << endl;
			list[i].displayinfo(50,5);
			list[i].displayPoint(10,5);
			gotoXY(53+ 1, 17);
			cout<< i + 1 << "\\" << n - 1 << ", chua dang nhap, dang nhap de xem toan bo thong tin!";
			char phim = getch();
			if (phim == 'q')
			{
				running = false;
				break;
			}
			switch (phim) {
			    case 75:
			      	gotoXY(50+3,5+1);
			        i--;
			        if (i < 0) {
			          i = n - 2;
			        }
			        break;
			    case 77: 
			        i++;
			        if (i >= n - 1) {
			          i = 0;
			        }
			        break;
				case 13: //enter
			    	current = i;
			    	check = true;
			}
		}
	}
	system("cls");	
}

void DSSV::editPoints()
{
	system("cls");
	Nocursortype();
//	Showcursor();
	int current = 0, select, luachon = 1, soluongluachon = 6;
	bool check = false;
	box(5, 1, 40, 20, 4, 1, "");
	box(50, 3, 65, 15, 2, 8, "");
	box(97, 7, 13, 8, 5, 2, "");
	SetColor(3);
	gotoXY(97 + 4,11);
	cout<<"Image";
	//list[0].displayinfo(50,5);
	string a[7] = {"","Ten","Ngay sinh", "Gioi tinh","SDT", "Dia chi","Tro lai"};
	int i = 0;
	bool running = true;
	while (running)
	{
		system("cls");
		Nocursortype();
	//	Showcursor();
		int current = 0, select, luachon = 1, soluongluachon = 6;
		bool check = false;
		box(5, 1, 40, 20, 4, 1, "");
		box(50, 3, 65, 15, 2, 8, "");
		box(97, 7, 13, 8, 5, 2, "");
		SetColor(3);
		gotoXY(97 + 4,11);
		cout<<"Image";
		//list[0].displayinfo(50,5);
		gotoXY(15,3);
		cout<<"Bang diem ki gan nhat";
		string a[7] = {"","Ten","Ngay sinh", "Gioi tinh","SDT", "Dia chi","Tro lai"};
		check = false;
		while (!check) {
			SetColor(2);
			clearinfo(72,3,20);
			clearpoint(32,5,6);
			gotoXY(50 + 3, 5 + 1);
			cout << left << setw(20) << "STT" << "| " << i + 1 << endl;
			list[i].displayinfo(50,5);
			list[i].displayPoint(10,5);
			gotoXY(53+ 1, 17);
			cout<< i + 1 << "\\" << n - 1 << ", chua dang nhap, dang nhap de xem toan bo thong tin!";
			char phim = getch();
			if (phim == 'q')
			{
				running = false;
				break;
			}
			switch (phim) {
			    case 75:
			      	gotoXY(50+3,5+1);
			        i--;
			        if (i < 0) {
			          i = n - 2;
			        }
			        break;
			    case 77: 
			        i++;
			        if (i >= n - 1) {
			          i = 0;
			        }
			        break;
				case 13: //enter
			    	current = i;
			    	check = true;
			}
		}
	}
	system("cls");	
}
void DSSV::tuition() {
	const int tc = 732;
	Nocursortype();
	Sinhvien sv;
	box(28, 1, 65, 15, 2, 8, "");
	SetBackgroundColor(5);
	gotoXY(47, 1);
	cout << "==== Hoc phi sinh vien ====" << endl;
	SetBackgroundColor(0);
		
	int i = 0;
	while (true) {
		SetColor(2);
		gotoXY(28 + 3, 3 + 1);
		cout << left << setw(20) << "STT" << "| " << i + 1 << endl;
		clearinfo(50,3,20);
		list[i].displaytuition(28,3);
		gotoXY(31,10);
		cout<<left<<setw(20)<<"So tin chi dang ki"<<"| "<<list[i].getPoint().gettc();
		gotoXY(31,11);
		string s = convert(tc*1000);
		cout<<left<<setw(20)<<"Hoc phi/tin chi"<<"| "<<s<<"vnd";
		gotoXY(31,12);
		s = convert((int)list[i].getPoint().gettc()*tc*1000);
		cout<<left<<setw(20)<<"Hoc phi can dong"<<"| "<<s<<"vnd";
		gotoXY(28 + 2, 15);
		cout<< i + 1 << "\\" << n - 1 << ", chua dang nhap, dang nhap de xem toan bo thong tin!";
		char phim = getch();
		
		switch (phim) {
		    case 75:
			    gotoXY(28+3,3+1);
			    i--;
			    if (i < 0) {
			        i = n - 2;
			    }
			    break;
		    case 77:
		        i++;
		        if (i >= n - 1) {
		          i = 0;
		        }
		        break;
		    case 'q':
		      	system("cls");
		        return;
		}
	}
}
