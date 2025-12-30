#include <iostream>

// Lớp Node đại diện cho một nút trong danh sách liên kết
class Node {
public:
    int data;
    Node* next;

    // Constructor
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Lớp SingleLinkedList quản lý danh sách liên kết đơn
class SingleLinkedList {
private:
    Node* head;

public:
    // Constructor - tạo danh sách rỗng
    SingleLinkedList() {
        head = nullptr;
        std::cout << "Danh sách liên kết đơn rỗng được tạo." << std::endl;
    }

    // Destructor - giải phóng bộ nhớ
    ~SingleLinkedList() {
        clear();
        std::cout << "Danh sách đã được hủy và giải phóng bộ nhớ." << std::endl;
    }

    // Kiểm tra danh sách có rỗng không
    bool isEmpty() const {
        return head == nullptr;
    }

    // Xóa toàn bộ danh sách
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    // Thêm phần tử vào đầu danh sách
    void addFirst(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        std::cout << "Đã thêm " << value << " vào đầu danh sách." << std::endl;
    }

    // Thêm phần tử vào cuối danh sách
    void addLast(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        std::cout << "Đã thêm " << value << " vào cuối danh sách." << std::endl;
    }

    // Xuất các phần tử của danh sách
    void display() const {
        if (isEmpty()) {
            std::cout << "Danh sách rỗng." << std::endl;
            return;
        }

        std::cout << "Danh sách: ";
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << " -> NULL" << std::endl;
    }

    // Tìm kiếm phần tử trong danh sách
    bool search(int value) const {
        Node* current = head;
        int position = 0;
        
        while (current != nullptr) {
            if (current->data == value) {
                std::cout << "Tìm thấy " << value << " tại vị trí " << position << std::endl;
                return true;
            }
            current = current->next;
            position++;
        }
        
        std::cout << "Không tìm thấy " << value << " trong danh sách." << std::endl;
        return false;
    }

    // Xóa phần tử đầu danh sách
    bool removeFirst() {
        if (isEmpty()) {
            std::cout << "Danh sách rỗng, không thể xóa." << std::endl;
            return false;
        }

        Node* temp = head;
        int removedValue = temp->data;
        head = head->next;
        delete temp;
        
        std::cout << "Đã xóa phần tử đầu: " << removedValue << std::endl;
        return true;
    }

    // Xóa phần tử cuối danh sách
    bool removeLast() {
        if (isEmpty()) {
            std::cout << "Danh sách rỗng, không thể xóa." << std::endl;
            return false;
        }

        // Trường hợp chỉ có một phần tử
        if (head->next == nullptr) {
            int removedValue = head->data;
            delete head;
            head = nullptr;
            std::cout << "Đã xóa phần tử cuối: " << removedValue << std::endl;
            return true;
        }

        // Tìm phần tử áp cuối
        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        
        int removedValue = current->next->data;
        delete current->next;
        current->next = nullptr;
        
        std::cout << "Đã xóa phần tử cuối: " << removedValue << std::endl;
        return true;
    }

    // Sắp xếp danh sách tăng dần (Bubble Sort)
    void sortAscending() {
        if (isEmpty() || head->next == nullptr) {
            std::cout << "Danh sách đã được sắp xếp (rỗng hoặc có 1 phần tử)." << std::endl;
            return;
        }

        bool swapped;
        Node* current;
        Node* lastSorted = nullptr;

        do {
            swapped = false;
            current = head;

            while (current->next != lastSorted) {
                if (current->data > current->next->data) {
                    // Hoán đổi dữ liệu
                    int temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
            lastSorted = current;
        } while (swapped);

        std::cout << "Danh sách đã được sắp xếp tăng dần." << std::endl;
    }

    // Chèn phần tử vào danh sách tăng, giữ thứ tự
    void insertSorted(int value) {
        Node* newNode = new Node(value);

        // Nếu danh sách rỗng hoặc giá trị nhỏ hơn phần tử đầu
        if (isEmpty() || head->data > value) {
            newNode->next = head;
            head = newNode;
            std::cout << "Đã chèn " << value << " vào đầu danh sách." << std::endl;
            return;
        }

        // Tìm vị trí chèn phù hợp
        Node* current = head;
        while (current->next != nullptr && current->next->data < value) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
        std::cout << "Đã chèn " << value << " vào danh sách tại vị trí phù hợp." << std::endl;
    }

    // Đếm số phần tử trong danh sách
    int count() const {
        int counter = 0;
        Node* current = head;
        while (current != nullptr) {
            counter++;
            current = current->next;
        }
        return counter;
    }

    // Lấy phần tử tại vị trí index (bắt đầu từ 0)
    int getAt(int index) const {
        if (index < 0 || isEmpty()) {
            throw std::out_of_range("Index không hợp lệ");
        }

        Node* current = head;
        int currentIndex = 0;
        
        while (current != nullptr && currentIndex < index) {
            current = current->next;
            currentIndex++;
        }

        if (current == nullptr) {
            throw std::out_of_range("Index vượt quá kích thước danh sách");
        }

        return current->data;
    }
};

void showMenu() {
    std::cout << "\n=== MENU DANH SÁCH LIÊN KẾT ĐƠN ===" << std::endl;
    std::cout << "1. Thêm phần tử vào đầu" << std::endl;
    std::cout << "2. Thêm phần tử vào cuối" << std::endl;
    std::cout << "3. Xuất danh sách" << std::endl;
    std::cout << "4. Tìm kiếm phần tử" << std::endl;
    std::cout << "5. Xóa phần tử đầu" << std::endl;
    std::cout << "6. Xóa phần tử cuối" << std::endl;
    std::cout << "7. Sắp xếp danh sách tăng dần" << std::endl;
    std::cout << "8. Chèn phần tử vào danh sách tăng" << std::endl;
    std::cout << "9. Đếm số phần tử" << std::endl;
    std::cout << "10. Lấy phần tử tại vị trí" << std::endl;
    std::cout << "0. Thoát" << std::endl;
    std::cout << "Nhập lựa chọn: ";
}

int main() {
    SingleLinkedList list;
    int choice, value, index;

    std::cout << "=== CHƯƠNG TRÌNH QUẢN LÝ DANH SÁCH LIÊN KẾT ĐƠN ===" << std::endl;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Nhập giá trị cần thêm vào đầu: ";
                std::cin >> value;
                list.addFirst(value);
                break;

            case 2:
                std::cout << "Nhập giá trị cần thêm vào cuối: ";
                std::cin >> value;
                list.addLast(value);
                break;

            case 3:
                list.display();
                break;

            case 4:
                std::cout << "Nhập giá trị cần tìm: ";
                std::cin >> value;
                list.search(value);
                break;

            case 5:
                list.removeFirst();
                break;

            case 6:
                list.removeLast();
                break;

            case 7:
                list.sortAscending();
                break;

            case 8:
                std::cout << "Nhập giá trị cần chèn vào danh sách tăng: ";
                std::cin >> value;
                list.insertSorted(value);
                break;

            case 9:
                std::cout << "Số phần tử trong danh sách: " << list.count() << std::endl;
                break;

            case 10:
                std::cout << "Nhập vị trí cần lấy (bắt đầu từ 0): ";
                std::cin >> index;
                try {
                    value = list.getAt(index);
                    std::cout << "Phần tử tại vị trí " << index << " là: " << value << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Lỗi: " << e.what() << std::endl;
                }
                break;

            case 0:
                std::cout << "Thoát chương trình." << std::endl;
                break;

            default:
                std::cout << "Lựa chọn không hợp lệ!" << std::endl;
                break;
        }

        if (choice != 0) {
            std::cout << "\nNhấn Enter để tiếp tục...";
            std::cin.ignore();
            std::cin.get();
        }

    } while (choice != 0);

    return 0;
}