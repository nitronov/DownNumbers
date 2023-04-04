#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    // Открываем первый бинарный файл для чтения
    ifstream file1("file1.dat", ios::binary);
    if (!file1.is_open()) {
        cout << "Error opening file1" << endl;
        return 1;
    }

    // Открываем второй бинарный файл для чтения
    ifstream file2("file2.dat", ios::binary);
    if (!file2.is_open()) {
        cout << "Error opening file2" << endl;
        return 1;
    }

    // Создаем третий текстовый файл для записи
    ofstream output("output.txt");
    if (!output.is_open()) {
        cout << "Error creating output file" << endl;
        return 1;
    }

    int num1, num2;

    // Считываем первое число из первого бинарного файла
    if (file1.read((char*)&num1, sizeof(int))) {
        // Считываем первое число из второго бинарного файла
        if (file2.read((char*)&num2, sizeof(int))) {
            // Сравниваем числа и записываем их в третий файл в порядке возрастания
            while (true) {
                if (num1 < num2) {
                    output << num1 << endl;
                    if (file1.read((char*)&num1, sizeof(int))) {
                        continue;
                    }
                    else {
                        // Достигли конца первого бинарного файла, записываем оставшиеся числа из второго файла
                        output << num2 << endl;
                        while (file2.read((char*)&num2, sizeof(int))) {
                            output << num2 << endl;
                        }
                        break;
                    }
                }
                else {
                    output << num2 << endl;
                    if (file2.read((char*)&num2, sizeof(int))) {
                        continue;
                    }
                    else {
                        // Достигли конца второго бинарного файла, записываем оставшиеся числа из первого файла
                        output << num1 << endl;
                        while (file1.read((char*)&num1, sizeof(int))) {
                            output << num1 << endl;
                        }
                        break;
                    }
                }
            }
        }
        else {
            // Ошибка чтения из второго бинарного файла
            cout << "Error reading from file2" << endl;
            return 1;
        }
    }
    else {
        // Ошибка чтения из первого бинарного файла
        cout << "Error reading from file1" << endl;
        return 1;
    }

    // Закрываем все файлы
    file1.close();
    file2.close();
    output.close();

    return 0;
}