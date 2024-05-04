#pragma once
#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;
class SanPham {
protected:
    string maso, tieude;
    double giaban;
public:
    virtual ~SanPham(){};
    double getgiaban() const { return giaban; }
    virtual void nhapthongtinsanpham() {
        cout << "Nhap ma so san pham: ";
        cin >> maso;
        cout << "Nhap tieu de cua san pham: ";
        cin.ignore();
        getline(cin, tieude);
        cout << "Nhap vao gia ban cua san pham: ";
        cin >> giaban;
    }
    virtual void xuatthongtinsanpham() const {
        cout << "Ma so cua san pham: " << maso << endl;
        cout << "Tieu de cua san pham: " << tieude << endl;
        cout << "Gia ban cua san pham: " << fixed << setprecision(0)<< getgiaban() << endl;
    }
};

class TranhAnh : public SanPham {
protected:
    double chieucao, chieurong;
    string tenhoasi;
public:
    void nhapthongtinsanpham() override {
        SanPham::nhapthongtinsanpham();
        cout << "Nhap chieu cao va chieu rong cua tranh anh: ";
        cin >> chieucao >> chieurong;
        cout << "Nhap ten cua hoa si: ";
        cin.ignore();
        getline(cin, tenhoasi);
    }
    void xuatthongtinsanpham() const override {
        SanPham::xuatthongtinsanpham();
        cout << "Chieu cao va chieu rong cua tranh anh: " << chieucao << " " << chieurong << endl;
        cout << "Ten hoa si: " << tenhoasi << endl;
    }
};

class CD : public SanPham {
protected:
    string tencasi, tensanxuat;
public:
    void nhapthongtinsanpham() override {
        SanPham::nhapthongtinsanpham();
        cout << "Nhap ten ca si: ";
        cin.ignore();
        getline(cin, tencasi);
        cout << "Nhap ten nha san xuat: ";
        getline(cin, tensanxuat);
    }
    void xuatthongtinsanpham() const override {
        SanPham::xuatthongtinsanpham();
        cout << "Ten ca si: " << tencasi << endl;
        cout << "Ten nha san xuat: " << tensanxuat << endl;
    }
};

class KhachHang {
protected:
    string makhachhang, ten, sodienthoai;
public:
    void nhapthongtin() {
        cout << "Nhap ma khach hang: ";
        cin >> makhachhang;
        cout << "Nhap ho ten cua khach hang: ";
        cin.ignore();
        getline(cin, ten);
        cout << "Nhap so dien thoai khach hang: ";
        cin >> sodienthoai;
    }
    void xuatthongtin() const {
        cout << "Ma khach hang la: " << makhachhang << endl;
        cout << "Ho ten cua khach hang la: " << ten << endl;
        cout << "So dien thoai khach hang la: " << sodienthoai << endl;
    }
};

class HoaDon {
protected:
    string mahoadon, ngay;
    KhachHang Khachhang;
    double tonggia;
    vector<SanPham*> Danhsachsp;
public:

    void nhaphoadon() {
        cout << "Nhap ma cua hoa don: ";
        cin >> mahoadon;
        cout << "Ngay mua: ";
        cin >> ngay;
        cout << "Nhap thong tin cua khach hang: \n";
        Khachhang.nhapthongtin();
        cout << "Nhap so san pham trong hoa don nay: ";
        int sosanpham;
        cin >> sosanpham;
        for (int i = 0; i < sosanpham; i++) {
            cout << "Nhap thong tin san pham " << i+1 << ":" << endl;
            cout << "1. Tran hinh\n2. CD\n";
            int choice;
            cin >> choice;
            SanPham *sp;
            switch (choice) {
            case 1:
                sp = new TranhAnh();
                cout << "Nhap thong tin cua tranh anh: \n";
                sp->nhapthongtinsanpham();
                break;
            case 2:
                sp = new CD();
                cout << "Nhap thong tin cua dia CD: \n";
                sp->nhapthongtinsanpham();
                break;
            }
            Danhsachsp.push_back(sp);
            tonggia += sp->getgiaban();
        }
    }
    void xuathoadon() const {
        cout << "Ma cua hoa don la: " << mahoadon << endl;
        cout << "Ngay nhap hoa don la: " << ngay << endl;
        cout << "Thong tin cua khach hang: \n";
        Khachhang.xuatthongtin();
        for(const auto&sp : Danhsachsp){
            sp->xuatthongtinsanpham();
        }
    }
    
    void thongtinkhachhang() const {
        Khachhang.xuatthongtin();
    }
    double gettonggia() const {
        return tonggia;
    }

};

class CuaHang {
protected:
    vector<HoaDon*> Danhsachhd;
public:
    void nhapcachoadon() {
        cout << "Nhap vao so hoa don: ";
        int sohoadon;cin >> sohoadon;
        for (int i = 0; i < sohoadon; i++) {
            cout<<"Nhap thong tin hoa don thu "<<i+1<<" :\n";
            HoaDon *hd=new HoaDon();
            hd->nhaphoadon();
            Danhsachhd.push_back(hd);
        }
    }
    void xuatcachoadon() const {
        cout<<"Danh sach hoa don \n";
        for(const auto&hd: Danhsachhd){
            hd->xuathoadon();
        }
    }
    void khachhangmuanhieunhat() const {
        const HoaDon* hoadonnhieunhat = nullptr;
        double maxgia = 0;
        for(const auto&sp :Danhsachhd){
            if(sp->gettonggia()>maxgia){
                maxgia=sp->gettonggia();
                hoadonnhieunhat=sp;
            }
        }
        cout <<"THONG TIN KHACH HANG MUA NHIEU NHAT:\n";
        hoadonnhieunhat->thongtinkhachhang();
    }
};