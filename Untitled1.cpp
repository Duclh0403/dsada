#include<iostream>
#include<string>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
using namespace std;

//T� m�u ch?
void textcolor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

//X�c ??nh v? tr�
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class User
{
protected:
    string Username;
    string Password;

    string Name;
    string Address;
    string Phone;
    string Email;
public:
    string getUsername(){return Username;}
    string getPassword(){return Password;}
    string getName(){return Name;}
    string getAddress(){return Address;}
    string getPhone(){return Phone;}
    string getEmail(){return Email;}
    
    void setUsername(string _Username){Username = _Username;}
    void setPassword(string _Password){Password = _Password;}
    void setName(string _Name){Name = _Name;}
    void setAddress(string _Address){Address = _Address;}
    void setPhone(string _Phone){Name = _Phone;}
    void setEmail(string _Email){Name = _Email;}

    User(string _Username = "", string _Password = "111111", string _Name = "", string _Address = "", string _Phone = "", string _Email = "")
    {
        Username = _Username;
        Password = _Password;
        Name = _Name;
        Address = _Address;
        Phone =_Phone;
        Email = _Email;
    }

    User(const User &u)
    {
        Username = u.Username;
        Password = u.Password;
        Name = u.Name;
        Address = u.Address;
        Phone = u.Phone;
        Email = u.Email;
    }
    ~User(){}

    virtual void ReadFile(ifstream &FileIn)
    {
        getline(FileIn, Username, ',');
        getline(FileIn, Password);
    }

    virtual void CreateFile(ofstream &FileOut, char* &FileName)
    {
        string str = (string)FileName;
        string FilePath = str + ".TXT";
        FileName = new char [FilePath.length()+1];
        strcpy (FileName, FilePath.c_str());
        if (FileName != NULL)
        {
            FileOut.open(FileName, ios_base::out);
        }
        delete[] FileName;
    }

    virtual void OpenFile(ifstream &FileIn, char* &FileName)
    {
        string str = (string)FileName;
        string FilePath = str + ".TXT";
        FileName = new char [FilePath.length()+1];
        strcpy (FileName, FilePath.c_str());
        if (FileName != NULL)
        {
            FileIn.open(FileName, ios_base::in);
        }
        delete[] FileName;
    }

    virtual void ReadInfomation(ifstream &FileIn)
    {
        getline(FileIn, Name);
        getline(FileIn, Address);
        getline(FileIn, Phone);
        getline(FileIn, Email);
    }

    virtual void DeleteFile(string FileName)
    {
        string FilePath = "\"del " + FileName + ".txt\"";
        char* strDelete = new char[FilePath.length() + 1];
        strcpy(strDelete, FilePath.c_str()); //chuy?n ki?u string th�nh char*
        system(strDelete);
    }

    virtual void Input()
    {
        cin.ignore();
        textcolor(3);
        cout << "Nhap thong tin ca nhan " << endl;
        cout << "Ho ten : ";
        textcolor(15);
        getline(cin, Name);
        textcolor(3);
        cout <<"Dia chi: ";
        textcolor(15);
        getline(cin, Address);
        textcolor(3);
        cout <<"So dien thoai: ";
        textcolor(15);
        getline(cin, Phone);
        textcolor(3);
        cout <<"Email: ";
        textcolor(15);
        getline(cin, Email);
    }
};

class Administrators : public User
{
public:
    void ReadFile(ifstream &FileIn)
    {
        User::ReadFile(FileIn);
    }
    void CreateFile(ofstream &FileOut, char *FileName)
    {
        User::CreateFile(FileOut, FileName);
    }
    bool operator == (Administrators a)
    {
        return a.getUsername() + a.getPassword() == getUsername() + getPassword();
    }
    Administrators(string _Username = "", string _Password = "111111", string _Name = "", string _Address = "", string _Phone = "", string _Email = "")
    :User(_Username, _Password, _Name, _Address, _Phone, _Password){}
};

class Employees : public User
{
public:
    void ReadFile(ifstream &FileIn)
    {
        User::ReadFile(FileIn);
    }
    void Input()
    {
        User::Input();
    }
    void CreateFile(ofstream &FileOut, char *FileName)
    {
        User::CreateFile(FileOut, FileName);
    }
    void ReadInformation(ifstream &FileIn)
    {
        User::ReadInfomation(FileIn);
    }
    bool operator ==(Employees a)
    {
        return a.getUsername() + a.getPassword() == getUsername() + getPassword();
    }
    Employees(string _Username = "", string _Password = "111111", string _Name = "", string _Address = "", string _Phone = "", string _Email = "")
    :User(_Username, _Password, _Name, _Address, _Phone, _Password){}
};

void DangNhapAdmin()
{
    textcolor(14);
    cout << "\t\t\t\t\t****************************"<< endl;
    cout << "\t\t\t\t\t*    ";
    textcolor(10);
    cout << "DANG NHAP ADMIN       ";
    textcolor(14);
    cout << "*" << endl;
    cout << "\t\t\t\t\t****************************" << endl;
}

void DangNhapEmployees()
{
    textcolor(14);
    cout << "\t\t\t\t\t****************************" << endl;
    cout << "\t\t\t\t\t*    ";
    textcolor(10);
    cout << "DANG NHAP EMPLOYEES   ";
    textcolor(14);
    cout << "*" << endl;
    cout << "\t\t\t\t\t****************************" << endl;
}

void MenuAdmin()
{
    textcolor(14);
    cout << "\t\t\t\t\t****************MENU****************" << endl;
    cout << "\t\t\t\t\t    1. Them Employee                " << endl;
    cout << "\t\t\t\t\t    2. Xoa Employee                 " << endl;
    cout << "\t\t\t\t\t    3. Tim Employee                 " << endl;
    cout << "\t\t\t\t\t    4. Cap nhat Employee            " << endl;
    cout << "\t\t\t\t\t    5. Hien thi thong tin Employee  " << endl;
    cout << "\t\t\t\t\t    6. Thoat                        " << endl;
    cout << "\t\t\t\t\t************************************" << endl;
}

void MenuEmployee()
{
    textcolor(14);
    cout << "\t\t\t\t\t***********MENU EMPLOYEE***********" << endl;
    cout << "\t\t\t\t\t     1. Xem thong tin tai khoan    " << endl;
    cout << "\t\t\t\t\t     2. Doi password               " << endl;
    cout << "\t\t\t\t\t     3. Thoat                      " << endl;
    cout << "\t\t\t\t\t***********************************" << endl;

}

//M� h�a m?t kh?u th�nh d?u *
void MaHoaPassword(char* &MatKhau, char x, int size)
{
    x = 'a';
    size = 0;
    while(x != 13) //13: ph�m Enter
    {
        x = getch(); //s? d?ng getch() ?? nh?p v� getch() b?t ph�m ngay sau khi nh?p
                    //thay v� d�ng cin th� m?i l?n nh?p 1 k� t? ph?i nh?n Enter s? kh�ng ph� h?p
        if(x == 13)
        {
            break;
        }
        if(MatKhau[0] == '\0')
        {
            while(true)
            {
                x = getch();
                if(x != 8) { break; }
            }
        }
        if(x == 8) //8: ph�m Backspace
        {
            if(size != 0) //n?u size m� kh�c 0 th� ta m?i ti?n h�nh x�a k� t?
            {
                MatKhau[size] = '\0';
                size--;
                cout << "\b \b";
            }
        }
        else
        {
            cout << x;
            MatKhau[size] = x;
            size++;
            Sleep(100);
            cout << "\b \b*";
        }
    }
    MatKhau[size] = '\0';
}

//??ng nh?p v�o h? th?ng
void Login(string &TaiKhoan, char* &MatKhau)
{
    textcolor(3);
    cout << "\t\t\t\t\tUser:     " << endl;
    cout << "\t\t\t\t\tPin:     ";
    textcolor(15);
    gotoxy(46, 3);
    cin >> TaiKhoan;   
    char x = 'l';
    int size = 0;
    cout << endl;
    textcolor(3);
    gotoxy(46, 4);
    textcolor(15);
    MaHoaPassword(MatKhau, x, size);
    cout << endl;
}

//Ki?m tra Username ng??i d�ng nh?p v�o c� t?n t?i trong file hay kh�ng, n?u n� ?� t?n t?i th� tr? v? false
bool KiemTraUsernameEmployee(User* x, string Username)
{
    ifstream FileIn;
    FileIn.open("Employees.txt", ios_base::in);
    while (!FileIn.eof())
    {
        x = new Employees();
        x->ReadFile(FileIn);  
        if(Username == x->getUsername())
            return false;
    }
    FileIn.close();
    return true; 
}

//Ki?m tra t�i kho?n v� m?t kh?u khi ??ng nh?p c� ch�nh x�c hay kh�ng, n?u ch�nh x�c tr? v? true
bool DangNhapThanhCong(User* x, char* FilePath, string &SaveUsername)
{
    ifstream FileIn;
    FileIn.open(FilePath, ios_base::in);
    string TaiKhoan;
    char* MatKhau;
    Login(TaiKhoan, MatKhau);
    while(!FileIn.eof())
    {
        x = new User();
        x->ReadFile(FileIn);
        if(x->getUsername() + x->getPassword() == TaiKhoan + " " + MatKhau)
        {
            SaveUsername = TaiKhoan;
            return true;
        }
    }
    FileIn.close();
    return false;
}

/****************************************
 * TH�M EMPLOYEES
 * B1: Cho ng??i d�ng nh?p v�o username c?n th�m
 * B2: Ki?m tra username nh?p v�o ?� t?n t?i hay ch?a, n?u ch?a th� th�m m?i username v�o file (Employees.txt),
 *     v?i password m?c ??nh l� "111111"
 * B3: T?o file [username.txt] t??ng ?ng v?i t�n username ng??i d�ng nh?p v�o
 * B4: Cho ng??i d�ng nh?p v�o file [username.txt] c�c th�ng tin bao g?m h? t�n, ??a ch?, s?t, email.
 **************************************/
void ThemEmployee(User* x)
{
    string Username;
    textcolor(3);
    cout << "Nhap Username muon them: ";
    textcolor(15);
    cin >> Username;
    if(KiemTraUsernameEmployee(x, Username))
    {
        textcolor(3);
        textcolor(15);
        char* FilePath = new char[Username.length() +1];
        strcpy(FilePath, Username.c_str());
        ofstream FileOut;
        Employees* Emp = new Employees();
        FileOut.open("Employees.TXT", ios_base::app);                          
        FileOut << endl << Username << ", " << "111111";
        FileOut.close();
        Emp->CreateFile(FileOut, FilePath);
        Emp->Input();
        FileOut << Emp->getName() << endl << Emp->getAddress() << endl << Emp->getPhone() << endl << Emp->getEmail();
        FileOut.close();
        textcolor(12);
        cout << "Them thanh cong !" << endl;
    }
    else
    {
        cout << "Username da ton tai !" << "\n";
    }
}

/*************************************************************************************************
 * X�A EMPLOYEES
 * B1: Kh?i t?o 1 file t?m (EmployeesCopy.txt);
 * B2: ??c to�n b? d? li?u t? file g?c (Employees.txt) v� ghi xu?ng file t?m nh?ng ko ??c Username c?n x�a
 * B3: X�a file g?c (Employees.txt) v� file [username.txt], sau ?� t?o l?i file g?c (Employees.txt)
 *     (m?c ?�ch c?a thao t�c n�y l� l� r?ng d? li?u trong file g?c)
 * B4: ??c ng??c d? li?u t? file t?m v� ghi v�o file g?c v� x�a file t?m
 * ***********************************************************************************************/
void XoaEmployee(User* x, string Username)
{
    ifstream FileIn;
    FileIn.open("Employees.txt", ios_base::in);
    ofstream FileOut;
    FileOut.open("EmployeesCopy.txt", ios_base::out);
    int count = 0; 
    while(!FileIn.eof())
    {
        x = new Employees();
        x->ReadFile(FileIn);
        if(x->getUsername() != Username)
        {
            FileOut << x->getUsername() << "," << x->getPassword() << endl;
        }
        count++;
    }
    FileIn.close();
    FileOut.close();
    system("del Employees.txt");
    char* c = (char *)"Employees";
    x->CreateFile(FileOut, c);
    FileOut.close();
    FileIn.open("EmployeesCopy.txt", ios_base::in);
    FileOut.open("Employees.txt", ios_base::out);
    while(count > 1){
        x = new Employees();
        x->ReadFile(FileIn);
        if(count == 2)
        {
            FileOut << x->getUsername() << "," << x->getPassword();
            break;
        }
        FileOut << x->getUsername() << "," << x->getPassword() << endl;
        count--;
    }
    FileIn.close();
    FileOut.close();
    x->DeleteFile(Username);
    textcolor(12);
    cout << "Xoa thanh cong !" << endl;
    system("del EmployeesCopy.txt");
}

//T�M EMPLOYEES
void TimEmployee(User* x, string Username)
{
    ifstream FileIn;
    char* FileName = new char[Username.length() + 1];
    strcpy(FileName, Username.c_str());
    x = new Employees();
    x->OpenFile(FileIn, FileName);
    x->ReadInfomation(FileIn);
    textcolor(12);
    cout << "Thong tin Employee can tim: " << endl;
    textcolor(11);
    cout << "Ho ten: " << x->getName() << endl;
    cout << "Dia chi: " << x->getAddress() << endl;
    cout << "So dien thoai: " << x->getPhone() << endl;
    cout << "Email: " << x->getEmail(); 
    FileIn.close();  
}

//XEM TH�NG TIN T�I KHO?N EMPLOYEES
void XemThongTinTaiKhoan(User* x, string Username)
{
    ifstream FileIn;
    char* FileName = new char[Username.length() + 1];
    strcpy(FileName, Username.c_str());
    x = new Employees();
    x->OpenFile(FileIn, FileName);
    x->ReadInfomation(FileIn);
    textcolor(12);
    cout << "Thong tin tai khoan" << endl;
    textcolor(11);
    cout << "Ho ten: " << x->getName() << endl;
    cout << "Dia chi: " << x->getAddress() << endl;
    cout << "So dien thoai: " << x->getPhone() << endl;
    cout << "Email: " << x->getEmail(); 
    FileIn.close();  
}

/****************************************************************************************************************************
 * C?P NH?T TH�NG TIN EMPLOYEES
 * B1: Cho ng??i d�ng nh?p v�o username c?n c?p nh?t th�ng tin, sau ?� ch?n thu?c t�nh c?n s?a
 * B2: Ti?p t?c nh?p th�ng tin thay ??i v�o bi?n Edit
 * B3: M? file [username.txt] ??c to�n b? d? li?u trong file nh?ng kh�ng ??c d�ng th�ng tin c?n s?a
 *     m� thay v�o ?� l� ??c th�ng tin t? bi?n Edit v?a nh?p v�o v? tr� c?n thay ??i v� ghi sang file t?m (NoName.txt)
 * B4: X�a file [username.txt] v� t?o l?i file v?a x�a, m?c ?�ch c?a thao t�c n�y l� l�m r?ng d? li?u trong file
 * B5: M? file (NoName.txt) ??c to�n b? d? li?u trong file n�y v� ghi xu?ng file [username.txt], sau ?� x�a file (NoName.txt)
 * **************************************************************************************************************************/
void CapNhatEmployee(User *x)
{
    ifstream FileIn;
    ofstream FileOut;
    textcolor(3);
    cout << "Nhap Username muon cap nhat: ";
    string Username;
    textcolor(15);
    cin >> Username;
    if(!KiemTraUsernameEmployee(x, Username))
    {
        while (true)
        {
            textcolor(10);
            cout << "Chon muc ban muon cap nhat: " << endl;
            cout << "1. Ho ten " << endl;
            cout << "2. Dia chi " << endl;
            cout << "3. So dien thoai " << endl;
            cout << "4. Email " << endl;
            int LuaChon;
            textcolor(15);
            cin >> LuaChon;  
            char* FileName = new char[Username.length() + 1];
            strcpy(FileName, Username.c_str());
            x = new Employees();
            string Edit;
            if(LuaChon == 1)
            {
                textcolor(3);
                cout << "Nhap ho ten thay doi: ";
                cin.ignore();
                textcolor(15);
                getline(cin, Edit);
                x->OpenFile(FileIn, FileName);
                x->ReadInfomation(FileIn);   
                FileOut.open("NoName.txt", ios_base::out);
                FileOut << Edit << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                x->DeleteFile(Username);

                char* fileName = new char[Username.length() + 1];
                strcpy(fileName, Username.c_str());
                FileIn.open("NoName.txt", ios_base::in);
                x = new Employees();
                x->ReadInfomation(FileIn);
                x->CreateFile(FileOut, fileName);
                FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                textcolor(12);
                cout << "Cap nhat ho ten Employee thanh cong !" << endl;
                x->DeleteFile("NoName");
            }
            else if(LuaChon == 2)
            {
                textcolor(13);
                cout << "Nhap dia chi thay doi: ";
                cin.ignore();
                textcolor(15);
                getline(cin, Edit);
                x->OpenFile(FileIn, FileName);
                x->ReadInfomation(FileIn);   
                FileOut.open("NoName.txt", ios_base::out);
                FileOut << x->getName() << endl << Edit << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                x->DeleteFile(Username);

                char *fileName = new char[Username.length() + 1];
                strcpy(fileName, Username.c_str());
                FileIn.open("NoName.txt", ios_base::in);
                x = new Employees();
                x->ReadInfomation(FileIn);
                x->CreateFile(FileOut, fileName);
                FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                textcolor(12);
                cout << "Cap nhat dia chi Employee thanh cong !" << endl;
                x->DeleteFile("NoName");
            }
            else if(LuaChon == 3)
            {
                textcolor(3);
                cout << "Nhap so dien thoai thay doi: ";
                cin.ignore();
                textcolor(15);
                getline(cin, Edit);
                x->OpenFile(FileIn, FileName);
                x->ReadInfomation(FileIn);   
                FileOut.open("NoName.txt", ios_base::out);
                FileOut << x->getName() << endl << x->getAddress() << endl << Edit << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                x->DeleteFile(Username);

                char* fileName = new char[Username.length() + 1];
                strcpy(fileName, Username.c_str());
                FileIn.open("NoName.txt", ios_base::in);
                x = new Employees();
                x->ReadInfomation(FileIn);
                x->CreateFile(FileOut, fileName);
                FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                textcolor(12);
                cout << "Cap nhat so dien thoai Employee thanh cong !" << endl;
                x->DeleteFile("NoName");
            }
            else if(LuaChon == 4)
            {
                textcolor(3);
                cout << "Nhap email thay doi: ";
                cin.ignore();
                textcolor(15);
                getline(cin, Edit);
                x->OpenFile(FileIn, FileName);
                x->ReadInfomation(FileIn);  
                FileOut.open("NoName.txt", ios_base::out);
                FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << Edit;
                FileIn.close();
                FileOut.close();
                x->DeleteFile(Username);

                char* fileName = new char[Username.length() + 1];
                strcpy(fileName, Username.c_str());
                FileIn.open("NoName.txt", ios_base::in);
                x = new Employees();
                x->ReadInfomation(FileIn);
                x->CreateFile(FileOut, fileName);
                FileOut << x->getName() << endl << x->getAddress() << endl << x->getPhone() << endl << x->getEmail();
                FileIn.close();
                FileOut.close();
                textcolor(12);
                cout << "Cap nhat email Employee thanh cong !" << endl;
                x->DeleteFile("NoName");
            }
            textcolor(12);
            cout << "Ban co muon tiep tuc cap nhat khong ? (c/k)" << endl;
            char c;
            textcolor(15);
            cin >> c;
            if(c == 'k') 
                break;
            else
                system("cls");
        
        }
    }
    else
    {
        textcolor(12);
        cout << "Username khong ton tai! " << endl;
    }
}


/**************************************************************************************************************
 * HI?N TH? TH�NG TIN TO�N B? EMPLOYEES
 * B1: Kh?i t?o m?ng strUser[100]
 * B2: ??c to�n b? d? li?u t? file (Employees.txt) v� g�n cho t?ng ph?n t? trong m?ng strUser[]
 * B3: Duy?t m?ng strUser[] ?? l?y t?ng ph?n t? trong m?ng t??ng ?ng v?i t?ng username v� m? file [username.txt]
 *     ??c to�n b? th�ng tin trong file [username.txt] v� xu?t ra m�n h�nh
 **************************************************************************************************************/
void HienThiThongTinEmployee(User* x)
{
    ifstream FileIn;
    x = new Employees();
    FileIn.open("Employees.txt", ios_base::in);
    string strUser[100];
    int n = 0;
    while (!FileIn.eof())
    {
        x->ReadFile(FileIn);
        strUser[n] = x->getUsername();
        n++;
    }
    FileIn.close();
    for(int i = 0; i < n; i++){
        textcolor(12);
        cout << "Thong tin " << strUser[i] << ": "<< endl;
        string s = strUser[i];
        char* FileName = new char[s.length() + 1];
        strcpy(FileName, s.c_str());
        x->OpenFile(FileIn, FileName);
        x->ReadInfomation(FileIn);
        textcolor(11);
        cout << "Ho ten: " << x->getName() << endl;
        cout << "Dia chi: " << x->getAddress() << endl;
        cout << "So dien thoai: " << x->getPhone() << endl;
        cout << "Email: " << x->getEmail() << endl;
        cout << endl;
        FileIn.close();
    }
}

/****************************************************************1***************************************************************
 * TH?C HI?N THAO T�C ??I M?T KH?U
 * B1: Kh?i t?o c�c chu?i bao g?m CurrentPass l� m?t kh?u c? hi?n t?i, NewPass l� m?t kh?u m?i,
 *     SaveUsername d�ng ?? x�c nh?n t�i kho?n c?n ??i m?t kh?u
 * B2: T?o file t?m (NoName.txt), sau ?� m? file (Employees.txt) ??c to�n b? th�ng tin t? file n�y v� ghi v�o file t?m (NoName.txt)
 * B3: X�a file (Employees.txt) v� t?o l?i file v?a x�a, m?c ?�ch c?a thao t�c n�y l� l�m r?ng d? li?u trong file
 * B4: M? file t?m (NoName.txt) ?? ??c v� ki?m c�c th�ng tin bao g?m username, password hi?n t?i
 *     c� kh?p v?i username, password ng??i d�ng nh?p v�o hay kh�ng, n?u ?�ng th� ghi c?p nh?t v�o file (Employees.txt)
 *******************************************************************************************************************************/
void ThucHienDoiMatKhau(User* x, string CurrentPass, string NewPass, string SaveUsername)
{
    ifstream FileIn;
    ofstream FileOut;
    string s = "NoName";
    char* fileName = new char[s.length() + 1];
    strcpy(fileName, s.c_str());
    x->CreateFile(FileOut, fileName);
    FileIn.open("Employees.txt", ios_base::in);
    int count = 0;
    while (!FileIn.eof())
    {
        x->ReadFile(FileIn);
        count++;
    }
    FileIn.close();
    int tmp = count;
    FileIn.open("Employees.txt", ios_base::in);
    while(count > 0)
    {
        x->ReadFile(FileIn);
        if(count == 1)
        {
            FileOut << x->getUsername() << "," << x->getPassword();
            break;
        }
        FileOut << x->getUsername() << "," << x->getPassword() << endl;
        count--;
    }
    FileIn.close();
    FileOut.close();
    x->DeleteFile("Employees");
    string s2 = "NoName";
    char *fileName2 = new char[s2.length() + 1];
    strcpy(fileName2, s2.c_str());
    x->OpenFile(FileIn, fileName2);
    FileOut.open("Employees.txt", ios_base::out);
    while(tmp > 0)
    {
        x->ReadFile(FileIn); 
        if(SaveUsername == x->getUsername() && " " + CurrentPass == x->getPassword() && tmp == 1)
        {
            FileOut << x->getUsername() << ", " << NewPass;
            break;
        }
        else if(SaveUsername == x->getUsername() && " " + CurrentPass == x->getPassword())
        {
            FileOut << x->getUsername() << ", " << NewPass << endl;
        }
        else
        {
            if(tmp == 1)
            {
                FileOut << x->getUsername() << "," << x->getPassword();
                break;
            }
            else if(tmp != 1)
            {
                FileOut << x->getUsername() << "," << x->getPassword() << endl;
            }
            else
            {
                break;
            }
        }
        tmp--;
    }
    textcolor(12);
    cout << "\nDoi mat khau thanh cong !";
    FileIn.close();
    FileOut.close();
    x->DeleteFile("NoName");
}

//Ch?c n?ng ??i m?t kh?u k?t h?p v?i h�m [ThucHienDoiMatKhau] ?? x? l�
void DoiMatKhau(User *x)
{
    ifstream FileIn;
    ofstream FileOut;
    char* CurrentPass = new char[50]; //m?t kh?u c?
    char* NewPass = new char[50];     //m?t kh?u m?i
    char* ConfirmPass = new char[50]; //x�c nh?n m?t kh?u m?i
    char c;
    int size = 0;
    string Username;
    textcolor(3);
    cout << "Nhap username hien tai: ";
    textcolor(15);
    cin >> Username;
    textcolor(3);
    cout << "Nhap password hien tai: ";
    textcolor(15);
    MaHoaPassword(CurrentPass, c, size);
    textcolor(3);
    cout << "\nNhap password moi: ";
    textcolor(15);
    MaHoaPassword(NewPass, c, size);
    textcolor(3);
    cout << "\nNhap lai password moi: ";
    textcolor(15);
    MaHoaPassword(ConfirmPass, c, size);
    FileIn.open("Employees.txt", ios_base::in);
    bool XacNhan = false; //ki?m tra c�c ?i?u ki?n password c� h?p l? hay kh�ng, n?u h?p l? th� th?c hi?n ??i m?t kh?u
    while(!FileIn.eof())
    {
        x = new Employees();
        x->ReadFile(FileIn);
        if(" " + (string)CurrentPass == x->getPassword() && (string)NewPass == (string)ConfirmPass)
        {   
            XacNhan = true;
            break;
        }
    }
    FileIn.close();
    if(XacNhan == false)
    {
        textcolor(12);
        cout << "\nThong tin ban nhap khong chinh xac, ban vui long kiem tra lai !" << endl;
    }
    else
    {
        ThucHienDoiMatKhau(x, CurrentPass, NewPass, Username);
    }
}

int main(){
    while (true)
    {
        system("cls");
        textcolor(12);
        cout << "\t\t\t--------------------------" << "\t\t" << "--------------------------" << endl;
        cout << "\t\t\t| 1. Dang Nhap ADMIN     |" << "\t\t" << "| 2. Dang Nhap EMPLOYEES |" << endl;
        cout << "\t\t\t--------------------------" << "\t\t" << "--------------------------" << endl;
        textcolor(9);
        cout << "Nhap lua chon cua ban: " << endl;
        int LuaChon;
        textcolor(15);
        cin >> LuaChon;
        int ChucNang;
        string SaveUsername;
        if(LuaChon == 1)
        {
            while (true)
            {
                system("cls");
                DangNhapAdmin();
                ifstream FileIn;
                ofstream FileOut;
                User* x = NULL;
                bool Exit = false;
                if(DangNhapThanhCong(x, (char *)"Administrators.txt", SaveUsername))
                {
                    while (true)
                    {
                        system("cls");
                        MenuAdmin();
                        textcolor(3);
                        cout << "Moi ban chon chuc nang: ";
                        textcolor(15);
                        cin >> ChucNang;
                        if(ChucNang == 1)
                        {
                            ThemEmployee(x);
                            getch();
                        }
                        else if(ChucNang== 2)
                        {
                            string Username;
                            textcolor(3);
                            cout << "Nhap Username muon xoa: ";
                            textcolor(15);
                            cin >> Username;
                            FileIn.open("Employees.txt", ios_base::in);
                            bool TimThay = false; //ki?m tra username ng??i d�ng nh?p v�o c� t?n t?i trong file hay ch?a
                            while (!FileIn.eof())
                            {
                                x = new Employees();
                                x->ReadFile(FileIn);
                                if(x->getUsername() == Username)
                                {
                                    TimThay = true;
                                    break;
                                }               
                            }
                            FileIn.close();
                            if(TimThay == false)
                            {
                                textcolor(12);
                                cout << "Khong tim thay " << Username << " de xoa !" << endl;
                                getch();
                            }
                            else
                            {
                                XoaEmployee(x, Username);
                                getch();
                            }
                            FileOut.close();
                        }
                        else if(ChucNang == 3)
                        {
                            string Username;
                            textcolor(3);
                            cout << "Nhap Username muon tim: ";
                            textcolor(15);
                            cin >> Username;
                            FileIn.open("Employees.txt", ios_base::in);
                            bool TimThay = false;
                            while (!FileIn.eof())
                            {
                                x = new Employees();
                                x->ReadFile(FileIn);
                                if(x->getUsername() == Username)
                                {
                                    TimThay = true;
                                    break;
                                }               
                            }
                            FileIn.close();
                            if(TimThay == false)
                            {
                                textcolor(12);
                                cout << "Khong tim thay Employee !"<< endl;
                                getch();
                            }
                            else
                            {
                                TimEmployee(x, Username);
                                getch();
                            }
                        }
                        else if(ChucNang == 4)
                        {
                            CapNhatEmployee(x);
                            getch();
                        }
                        else if(ChucNang == 5)
                        {
                            HienThiThongTinEmployee(x);
                            getch();
                        }
                        else if(ChucNang == 6)
                        {
                            Exit = true;
                            break;
                        }
                        else
                        {
                            textcolor(12);
                            cout << "Lua chon khong hop le ! Ban vui long chon lai !!!" << endl;
                            getch();
                        }
                    }
                    if(Exit == true) break;
                }
                else
                {
                    textcolor(12);
                    cout << "Sai tai khoan hoac mat khau!" << endl;
                    getch();
                }
            }        
        }
        else if(LuaChon == 2)
        {
            int count = 0; //??m s? l?n nh?p sai m?t kh?u, n?u sai qu� 3 l?n th� tho�t ch??ng tr�nh
            bool Exit = false;
            while(true)
            {
                system("cls");
                DangNhapEmployees();
                ifstream FileIn;
                User* x = NULL;
                int n = 0;
                if(DangNhapThanhCong(x, (char *)"Employees.txt", SaveUsername))
                {
                    textcolor(12);
                    cout << "Dang nhap thanh cong !" << endl;
                    char* CurrentPass = new char[50];
                    char* NewPass = new char[50];
                    char c = 'a';
                    int size = 0;
                    bool XacNhan = false; //ki?m tra m?t kh?u nh?p v�o c� h?p l? hay kh�ng
                    ifstream FileIn;
                    ofstream FileOut;
                    textcolor(3);
                    cout << "Ban vui long doi mat khau truoc khi su dung chuong trinh !" << endl;
                    getch();
                    while(true)
                    {
                        system("cls");
                        textcolor(3);
                        cout << "Nhap mat khau hien tai: ";
                        textcolor(15);
                        MaHoaPassword(CurrentPass, c, size);
                        
                        FileIn.open("Employees.txt", ios_base::in);
                        while(!FileIn.eof())
                        {
                            x = new Employees();
                            x->ReadFile(FileIn);
                            if(" " + (string)CurrentPass == x->getPassword())
                            {   
                                XacNhan = true;
                                break;
                            }
                        }
                        FileIn.close();
                        if(XacNhan == false)
                        {
                            textcolor(12);
                            cout << "\nMat khau hien tai khong chinh xac! " << endl;
                            getch();
                        }
                        else if(XacNhan == true)
                        {
                            textcolor(3);
                            cout << "\nNhap mat khau moi: ";
                            textcolor(15);
                            MaHoaPassword(NewPass, c, size);
                            if((string)CurrentPass == (string)NewPass)
                            {
                                textcolor(12);
                                cout << "\nTrung mat khau roi ! Ban vui long nhap l?i !!!" << endl;
                                getch();
                            }
                            else
                            {
                                ThucHienDoiMatKhau(x, (string)CurrentPass, (string)NewPass, SaveUsername);
                                getch();
                                break;
                            }
                        }          
                    }
                    while (true)
                    {
                        system("cls");
                        MenuEmployee();
                        textcolor(3);
                        cout << "Moi ban chon chuc nang: ";
                        textcolor(15);
                        cin >> ChucNang;   
                        if(ChucNang == 1)
                        {
                            XemThongTinTaiKhoan(x, SaveUsername);
                            getch();
                        }
                        else if(ChucNang == 2)
                        {
                            DoiMatKhau(x);
                            getch();
                        }
                        else if(ChucNang == 3)
                        {
                            Exit = true;
                            break;
                        }
                        else
                        {
                            textcolor(12);
                            cout << "Lua chon khong hop le ! Ban vui long chon lai !!!" << endl;
                            getch();
                        }
                    }
                }
                else
                {
                    count++;
                    textcolor(12);
                    cout << "Sai tai khoan hoac mat khau!" << endl;
                }
                if(count == 3) exit(0);
                if(Exit == true) break;
                getch();
            }
        }
        else
        {
            textcolor(12);
            cout << "Lua chon khong hop le!" << endl;
            getch();
        }
    }   
    system("pause");
}
