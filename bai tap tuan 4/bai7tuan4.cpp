#include <iostream>
#include <algorithm>

class DynamicSquareMatrix {
private:
    int** matrix;
    int size;

public:
    // Constructor - khởi tạo ma trận vuông với kích thước n×n
    DynamicSquareMatrix(int n) {
        size = n;
        matrix = new int*[size];
        for (int i = 0; i < size; i++) {
            matrix[i] = new int[size];
        }
        std::cout << "Ma trận vuông " << size << "×" << size << " được khởi tạo." << std::endl;
    }

    // Destructor - giải phóng bộ nhớ
    ~DynamicSquareMatrix() {
        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
        std::cout << "Ma trận đã được hủy và giải phóng bộ nhớ." << std::endl;
    }

    // Nhập các giá trị cho ma trận
    void input() {
        std::cout << "Nhập " << size * size << " phần tử cho ma trận " << size << "×" << size << ":" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << "Dòng " << i + 1 << ": ";
            for (int j = 0; j < size; j++) {
                std::cin >> matrix[i][j];
            }
        }
    }

    // Xuất ma trận ra màn hình
    void output() const {
        std::cout << "Ma trận:" << std::endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }

    // Tìm phần tử lớn nhất trong ma trận
    int findMax() const {
        int max = matrix[0][0];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] > max) {
                    max = matrix[i][j];
                }
            }
        }
        return max;
    }

    // Tính tổng các phần tử trên đường chéo chính
    int sumMainDiagonal() const {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += matrix[i][i];
        }
        return sum;
    }

    // Sắp xếp các phần tử trên từng dòng tăng dần
    void sortRowsAsc() {
        for (int i = 0; i < size; i++) {
            // Sắp xếp dòng thứ i bằng bubble sort
            for (int j = 0; j < size - 1; j++) {
                for (int k = 0; k < size - 1 - j; k++) {
                    if (matrix[i][k] > matrix[i][k + 1]) {
                        std::swap(matrix[i][k], matrix[i][k + 1]);
                    }
                }
            }
        }
    }

    // Phương thức bổ sung: xuất đường chéo chính
    void outputMainDiagonal() const {
        std::cout << "Đường chéo chính: ";
        for (int i = 0; i < size; i++) {
            std::cout << matrix[i][i] << " ";
        }
        std::cout << std::endl;
    }

    // Phương thức bổ sung: tính tổng đường chéo phụ
    int sumSecondaryDiagonal() const {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += matrix[i][size - 1 - i];
        }
        return sum;
    }

    // Getter cho size
    int getSize() const {
        return size;
    }

    // Kiểm tra ma trận có phải ma trận đối xứng không
    bool isSymmetric() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] != matrix[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    int n;
    
    std::cout << "=== CHƯƠNG TRÌNH QUẢN LÝ MA TRẬN VUÔNG ĐỘNG ===" << std::endl;
    std::cout << "Nhập kích thước ma trận vuông (n×n): ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Kích thước không hợp lệ!" << std::endl;
        return 1;
    }

    // Tạo đối tượng ma trận vuông động
    DynamicSquareMatrix matrix(n);

    // Nhập ma trận
    std::cout << "\n1. NHẬP MA TRẬN:" << std::endl;
    matrix.input();

    // Xuất ma trận ban đầu
    std::cout << "\n2. MA TRẬN BAN ĐẦU:" << std::endl;
    matrix.output();

    // Tìm phần tử lớn nhất
    std::cout << "\n3. PHẦN TỬ LỚN NHẤT:" << std::endl;
    int maxElement = matrix.findMax();
    std::cout << "Phần tử lớn nhất trong ma trận: " << maxElement << std::endl;

    // Tính tổng đường chéo chính
    std::cout << "\n4. ĐƯỜNG CHÉO CHÍNH:" << std::endl;
    matrix.outputMainDiagonal();
    int diagSum = matrix.sumMainDiagonal();
    std::cout << "Tổng các phần tử trên đường chéo chính: " << diagSum << std::endl;

    // Thông tin bổ sung về đường chéo phụ
    std::cout << "\n5. THÔNG TIN BỔ SUNG:" << std::endl;
    int secDiagSum = matrix.sumSecondaryDiagonal();
    std::cout << "Tổng các phần tử trên đường chéo phụ: " << secDiagSum << std::endl;
    
    bool symmetric = matrix.isSymmetric();
    std::cout << "Ma trận có đối xứng không? " << (symmetric ? "Có" : "Không") << std::endl;

    // Sắp xếp từng dòng tăng dần
    std::cout << "\n6. SẮP XẾP TỪNG DÒNG TĂNG DẦN:" << std::endl;
    matrix.sortRowsAsc();
    std::cout << "Ma trận sau khi sắp xếp từng dòng tăng dần:" << std::endl;
    matrix.output();

    // So sánh trước và sau
    std::cout << "\n7. TỔNG KẾT:" << std::endl;
    std::cout << "Kích thước ma trận: " << matrix.getSize() << "×" << matrix.getSize() << std::endl;
    std::cout << "Phần tử lớn nhất: " << maxElement << std::endl;
    std::cout << "Tổng đường chéo chính ban đầu: " << diagSum << std::endl;
    std::cout << "Tổng đường chéo chính sau sắp xếp: " << matrix.sumMainDiagonal() << std::endl;

    return 0;
} // Destructor được gọi tự động khi kết thúc chương trình