#include <iostream>
#include <algorithm>

class DynamicArray {
private:
    int* arr;
    int size;
    int capacity;

public:
    // Constructor - khởi tạo mảng với dung lượng cho trước
    DynamicArray(int cap = 10) {
        capacity = cap;
        size = 0;
        arr = new int[capacity];
        std::cout << "Mảng được khởi tạo với dung lượng: " << capacity << std::endl;
    }

    // Destructor - giải phóng bộ nhớ
    ~DynamicArray() {
        delete[] arr;
        arr = nullptr;
        std::cout << "Mảng đã được hủy và giải phóng bộ nhớ." << std::endl;
    }

    // Nhập mảng từ bàn phím
    void input() {
        std::cout << "Nhập số phần tử: ";
        std::cin >> size;
        
        if (size > capacity) {
            std::cout << "Kích thước vượt quá dung lượng!" << std::endl;
            size = capacity;
        }

        std::cout << "Nhập " << size << " phần tử: ";
        for (int i = 0; i < size; i++) {
            std::cin >> arr[i];
        }
    }

    // Xuất mảng ra màn hình
    void output() const {
        if (size == 0) {
            std::cout << "Mảng rỗng." << std::endl;
            return;
        }
        
        std::cout << "Mảng: ";
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    // Tìm giá trị lớn nhất
    int findMax() const {
        if (size == 0) return INT_MIN;
        
        int max = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;
    }

    // Tìm giá trị nhỏ nhất
    int findMin() const {
        if (size == 0) return INT_MAX;
        
        int min = arr[0];
        for (int i = 1; i < size; i++) {
            if (arr[i] < min) {
                min = arr[i];
            }
        }
        return min;
    }

    // Tìm kiếm phần tử có giá trị x
    int search(int x) const {
        for (int i = 0; i < size; i++) {
            if (arr[i] == x) {
                return i;
            }
        }
        return -1; // Không tìm thấy
    }

    // Xóa phần tử đầu tiên có giá trị x
    bool remove(int x) {
        int pos = search(x);
        if (pos == -1) return false;

        // Dịch chuyển các phần tử sau vị trí pos lên trước
        for (int i = pos; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
        return true;
    }

    // Sắp xếp mảng tăng dần (Bubble Sort)
    void sortAsc() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // Chèn phần tử vào mảng đã sắp xếp tăng
    bool insertSorted(int x) {
        if (size >= capacity) {
            std::cout << "Mảng đã đầy, không thể chèn!" << std::endl;
            return false;
        }

        // Tìm vị trí chèn
        int pos = 0;
        while (pos < size && arr[pos] < x) {
            pos++;
        }

        // Dịch chuyển các phần tử để tạo chỗ trống
        for (int i = size; i > pos; i--) {
            arr[i] = arr[i - 1];
        }

        // Chèn phần tử mới
        arr[pos] = x;
        size++;
        return true;
    }

    // Đảo mảng mà không dùng mảng phụ
    void reverse() {
        int left = 0;
        int right = size - 1;
        
        while (left < right) {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    // Getter cho size
    int getSize() const {
        return size;
    }
};

int main() {
    // Tạo đối tượng mảng động với dung lượng 20
    DynamicArray myArray(20);

    // Demo các chức năng
    std::cout << "\n=== DEMO MẢNG ĐỘNG ===" << std::endl;

    // Nhập mảng
    myArray.input();

    // Xuất mảng ban đầu
    std::cout << "\nMảng ban đầu:" << std::endl;
    myArray.output();

    // Tìm max, min
    if (myArray.getSize() > 0) {
        std::cout << "\nGiá trị lớn nhất: " << myArray.findMax() << std::endl;
        std::cout << "Giá trị nhỏ nhất: " << myArray.findMin() << std::endl;

        // Tìm kiếm
        int searchValue;
        std::cout << "\nNhập giá trị cần tìm: ";
        std::cin >> searchValue;
        
        int pos = myArray.search(searchValue);
        if (pos != -1) {
            std::cout << "Tìm thấy " << searchValue << " tại vị trí: " << pos << std::endl;
        } else {
            std::cout << "Không tìm thấy " << searchValue << std::endl;
        }

        // Sắp xếp
        std::cout << "\nSắp xếp mảng tăng dần:" << std::endl;
        myArray.sortAsc();
        myArray.output();

        // Chèn phần tử
        int insertValue;
        std::cout << "\nNhập giá trị cần chèn vào mảng đã sắp xếp: ";
        std::cin >> insertValue;
        
        if (myArray.insertSorted(insertValue)) {
            std::cout << "Mảng sau khi chèn " << insertValue << ":" << std::endl;
            myArray.output();
        }

        // Đảo mảng
        std::cout << "\nĐảo mảng:" << std::endl;
        myArray.reverse();
        myArray.output();

        // Xóa phần tử
        int removeValue;
        std::cout << "\nNhập giá trị cần xóa: ";
        std::cin >> removeValue;
        
        if (myArray.remove(removeValue)) {
            std::cout << "Đã xóa " << removeValue << ". Mảng sau khi xóa:" << std::endl;
            myArray.output();
        } else {
            std::cout << "Không tìm thấy " << removeValue << " để xóa." << std::endl;
        }
    }

    return 0;
} // Destructor được gọi tự động khi kết thúc chương trình