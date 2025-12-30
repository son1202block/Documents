#include <iostream>
#include <algorithm>
using namespace std;

// Nhap Mang
void nhapMang(int a[], int&n) {
 cout << "Nhap so phan tu n: ";
 cin >> n;
 for (int i = 0; i < n; i++) {
  cout << "a[" << i << "] = ";
  cin >> a[i];
 }
}

// Xuat mang
void xuatMang(int a[], int n) {
 int dem = 0;
 for (int i = 0; i < n; i++) {
 cout << a[i] << " ";
  }
  cout << endl;    
}

// Dem so chan
int demChan(int a[], int n) {
 int dem = 0;
 for (int i = 0; i < n; i++)
 if (a[i] % 2 == 0) dem++;
 return dem;
}

// Dem so phan tu bang x
int demBangX(int a[], int n, int x) {
 int dem = 0;
 for (int i = 0; i < n; i++)
 if (a[i] == x) dem++;
 return dem;
}

// Tim min
int timMin(int a[], int n) {
 int minVal = a[0];
 for (int i = 1; i < n; i++)
 if (a[i] < minVal) minVal = a[i];
 return minVal;
}

// Tim max
int timMax(int a[], int n) {
 int maxVal = a[0];
 for (int i = 1; i < n; i++)
 if (a[i] > maxVal) maxVal = a[i];
 return maxVal;
}

// Tim phan tu bang x
int timX(int a[], int n, int x) {
 for (int i = 0; i < n; i++)
 if (a[i] == x) return i;
 return -1; 
}

// Xoa phan tu bang x
void xoaX(int a[], int &n, int x) {
 int k = 0;
 for (int i = 0; i < n; i++)
 if (a[i] != x) a[k++] = a[i];
 n = k;
}

// Sap xep tang dan
void sapXepTang(int a[], int n) {
 for (int i = 0; i < n - 1; i++)
 for (int j = i + 1; j < n; j++)
 if (a[i] > a[j]) swap(a[i], a[j]);
}

// Chen x vao mang da tang
void chenX(int a[], int &n, int x) {
 int i = n - 1;
 while (i >= 0 && a[i] > x) {
  a[i+1] = a[i];
  i--;
 }
 a[i+1] = x;
 n++;
}

// Tron 2 mang tang thanh mang tang
void tronMang(int a[], int n, int b[], int m, int c[], int &k) {
 int i = 0, j = 0;
 k = 0;
 while (i < n && j < m) {
  if (a[i] < b[j]) c[k++] = a[i++];
  else c[k++] = b[j++];
 }
 while (i < n) c[k++] = a[i++];
 while (j < m) c[k++] = b[j++];
}

// Dao mang khong dung mang phu
void daoMang(int a[], int n) {
 for (int i = 0; i < n/2; i++)
 swap(a[i], a[n-1-i]);
}

// Kiem tra doi xung
bool doiXung(int a[], int n) {
 for (int i = 0; i < n/2; i++)
 if (a[i] != a[n-1-i]) return false;
 return true;
}

// Tim phan tu lon thu 2
int lonThu2(int a[], int n) {
 int max1 = timMax(a,n), max2 = -1e9;
 for (int i = 0; i <n; i++)
 if (a[i] < max1 && a[i] > max2) max2 = a[i];
 return max2;
}

// Tim phan tu nho thu 2
int nhoThu2(int a[], int n) {
 int min1 = timMin(a,n), min2 = 1e9;
 for (int i = 0; i < n; i++)
 if (a[i] > min1 && a[i] < min2) min2 = a[i];
 return min2;
}

int main() {
 int a[100], n;
 nhapMang(a, n);
 cout << "Mang vua nhap: "; xuatMang(a, n);
 cout << "So chan: " << demChan(a, n) << endl;
 int x;
 cout << "Nhap x: "; cin >> x;
 cout << "So phan tu bang x: " << demBangX(a, n, x) << endl;
 cout << "Min = " << timMin(a, n) << endl;
 cout << "Max = " << timMax(a, n) << endl;
 int pos = timX(a, n, x);
 if (pos != -1) cout << "Tim thay x tai vi tri " << pos << endl;
 else cout << "Khong tim thay x\n";
 xoaX(a, n, x);
 cout << "Mang sau khi xoa x: "; xuatMang(a, n);
 sapXepTang(a, n);
 cout << "Mang sap xep tang: "; xuatMang(a, n);
 cout << "Chen x vao mang tang: ";
 chenX(a, n, x);
 xuatMang(a, n);
 cout << "Mang doi xung? " << (doiXung(a, n) ? "Co" : "Khong") << endl;
 cout << "Phan tu lon thu 2: " << lonThu2(a, n) << endl;
 cout << "Phan tu nho thu 2: " << nhoThu2(a, n) << endl;
 return 0;
 
}
