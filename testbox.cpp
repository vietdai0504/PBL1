#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

void Nocursortype() {
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Showcursor()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&Info); 
}

void SetBackgroundColor(int colorIndex) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD color = (colorIndex << 4) | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    SetConsoleTextAttribute(hConsole, color);
}

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void box(int x, int y, int w, int h, int t_color, int b_color, const string& nd) {
    int ix, iy;
    SetColor(7);
    gotoXY(x+w/2 - 5, y + 3);
    SetBackgroundColor(t_color);
    cout << nd << endl;
    SetBackgroundColor(b_color);

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
    SetBackgroundColor(0);
}

void clearinfo()
{
	gotoXY(28 + 3, 3 + 2);
	cout << left << setw(60) << " ";
	gotoXY(28 + 3, 3 + 3);
	cout << left << setw(60) << " ";
	gotoXY(28 + 3, 3 + 4);
	cout << left << setw(60) << " ";
	gotoXY(28 + 3, 3 + 5);
	cout << left << setw(60) << " ";
	gotoXY(28 + 3, 3 + 6);
	cout << left << setw(60) << " ";
	gotoXY(28 + 3, 3 + 7);
	cout << left << setw(60) << " ";
	gotoXY(28 + 3, 3 + 8);
	cout << left << setw(60) << " ";
	gotoXY(28 + 3, 3 + 9);
	cout << left << setw(60) << " ";
	gotoXY(28 + 3, 3 + 10);
	cout << left << setw(60) << " ";
}


class Sinhvien
{
	string ten,gioitinh,ngaysinh,diachi,khoa,lop,hoanthanh;
	int masv,sdt;
	double gpa;
public:
	Sinhvien() : ten(""), gioitinh(""), ngaysinh(""),diachi(""), khoa(""),lop(""),hoanthanh("0/0"), masv(0), sdt(0),gpa(0) {}
	string getName()
	{
		return ten;
	}
	int getid()
	{
		return masv;
	}
	void getinfo(ifstream& fin)
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
	}
	
	void displayinfo()
	{  
	    gotoXY(28 + 3, 3 + 2);
	    cout << left << setw(20) << "MaSV" << "| " << masv << endl;
	
	    gotoXY(28 + 3, 3 + 3);
	    cout << left << setw(20) << "TenSV" << "| " << ten << endl;
	
	    gotoXY(28 + 3, 3 + 4);
	    cout << left << setw(20) << "Gioi tinh " << "| " << gioitinh<< endl;
	
	    gotoXY(28 + 3, 3 + 5);
	    cout << left << setw(20) << "Ngay sinh " << "| " << ngaysinh << endl;
	
	    gotoXY(28 + 3, 3 + 6);
	    cout << left << setw(20) << "Lop " << "| " << lop << endl;
	
	    gotoXY(28 + 3, 3 + 7);
	    cout << left << setw(20) << "Khoa " << "| " << khoa << endl;
	
	    gotoXY(28 + 3, 3 + 8);
	    cout << left << setw(20) << "SDT " << "| " << endl;
	
	    gotoXY(28 + 3, 3 + 9);
	    cout << left << setw(20) << "Dia chi " << "| " << endl;
	
	    gotoXY(28 + 3, 3 + 10);
	    cout << left << setw(20) << "GPA " << "| " << endl;
	}
};

class DSSV
{
	vector<Sinhvien> list;
	int n = 0;
public:
	void getFullInfo(ifstream& fin)
	{
		string line;
		getline(fin,line);
		while(!fin.eof())
		{
			Sinhvien sv;
			sv.getinfo(fin);
			list.push_back(sv);
			n++;
		}
	}
	
	void display() {
		Nocursortype();
		Sinhvien sv;
		box(28, 1, 65, 15, 2, 8, "");
		SetBackgroundColor(5);
		gotoXY(47, 1);
		cout << "==== Thong tin sinh vien ====" << endl;
		SetBackgroundColor(0);
		
		int i = 0;
		while (true) {
			SetColor(2);
		    gotoXY(28 + 3, 3 + 1);
		    cout << left << setw(20) << "STT" << "| " << i + 1 << endl;
		    clearinfo();
		    list[i].displayinfo();
		    box(75, 4, 13, 8, 5, 2, "");
		    SetColor(3);
		    gotoXY(75 + 4,8);
		    cout<<"Image";
		    gotoXY(28 + 1, 15);
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
        box(29,2,63,18,4,1,"====MENU====");

        for (int i = 1; i <= soluongluachon; ++i) {
            gotoXY(start_x - 14, start_y + i + 1);
            if (i == luachon) {
            	SetColor(0x07);
                cout << "> ";
                SetBackgroundColor(1);
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
			case 9:
				return;
		}
	}
}

int main() {
    int luachon = 1, soluongluachon = 9;
    ifstream fin("info.csv");
    DSSV sv;
    sv.getFullInfo(fin);
    ifstream logout("banner.txt");
    string str;
    while (logout >> str)
    	cout<<str << endl;
//    option(sv);
    return 0;
}
