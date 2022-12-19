#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <optional>
using namespace std;
//const int process_count = 2;
//volatile double result = 0;
//pthread_t array[process_count];
//const int count = 1200'000;
//char buf[count];

//задание 0
//void write_data_to_file() {
//    int fd = open("data.bin", O_CREAT | O_TRUNC | O_RDWR);
//    string data = "";
//    for (int i = 0; i < 8'000'000; i++) {
//        data += "1";
//    }
//    write(fd, data.c_str(), strlen(data.c_str()));
//    close(fd);
//}

//void *processing_data_parallel(void* arg) {
//    pthread_t id = pthread_self();
//    int number = 0;
//    for (int i = 0; i < process_count; i++) {
//        if (id == array[i]) {
//            number = i;
//            break;
//        }
//    }
//    double tmp_sum = 0;
//    for (int i = number; i < strlen(buf); i += process_count) {
//        tmp_sum += buf[i] - '0';
//    }
//    result += tmp_sum;
//}
//
//int main() {
//    chdir("/home/artem/CLionProjects/SYSLAB3");
//    //write_data_to_file();
//    int fd = open("data.bin", O_CREAT | O_RDWR);
//    read(fd, &buf, count);
//    cout << "Последовательное выполнение: \n";
//    double sum = 0;
//    clock_t time1 = clock();
//    for (int i = 0; i < strlen(buf); i++) {
//        sum += buf[i] - '0';
//    }
//    clock_t time2 = clock();
//    clock_t time_ = time2 - time1;
//    cout << "Результат: " << sum << "\nЗатраченное время: " << (double)time_ / CLOCKS_PER_SEC << "\n";
//    cout << "Параллельное вычисление\n";
//    clock_t time3 = clock();
//    for (int i = 0; i < process_count; i++) {
//        pthread_create(&array[i], NULL, &processing_data_parallel, NULL);
//    }
//    for (int i = 0; i < process_count; i++) {
//        pthread_join(array[i], NULL);
//    }
//    clock_t time4 = clock();
//    clock_t time__ = time4 - time3;
//    cout << "Результат: " << result << "\nЗатраченное время: " << (double)time__ / CLOCKS_PER_SEC << "\n";
//
//    return 0;
//}




//задание 1
//volatile int** parallel_result = new volatile int*[0];
//int **result = new int*[0];
//int** matrix = new int*[0];
//const int process_count = 4;
//pthread_t array[process_count];
//int matrix_size = 0;
//
//void get_matrix_to_file(const string& filename, int size_) {
//    int fd = open(filename.c_str(), O_CREAT | O_TRUNC | O_RDWR);
//    string data = "";
//    for (int i = 0; i < size_; i++) {
//        for (int j = 0; j < size_; j++) {
//            data += to_string(rand() % 10);
//            if (j < size_ - 1) data += " ";
//        }
//        if (i < size_ - 1) data += "\n";
//    }
//    write(fd, data.c_str(), strlen(data.c_str()));
//    close(fd);
//}
//
//void free_memory() {
//    for (int i = 0; i < matrix_size; i++) {
//        delete[] matrix[i];
//        delete[] result[i];
//        delete[] parallel_result[i];
//    }
//    delete[] matrix;
//    delete[] result;
//    delete[] parallel_result;
//}
//
//void get_memory(int count) {
//    free_memory();
//    matrix_size = count;
//    matrix = new int*[count];
//    result = new int*[count];
//    parallel_result = new volatile int*[count];
//    for (int i = 0; i < count; i++) {
//        matrix[i] = new int[count];
//        result[i] = new int[count];
//        parallel_result[i] = new int[count];
//    }
//}
//
//void get_matrix_from_file(const string& filename) {
//    int fd = open(filename.c_str(),O_RDWR);
//    struct stat st;
//    stat(filename.c_str(), &st);
//    char buffer[st.st_size];
//    read(fd, &buffer, st.st_size);
//    int count = 0;
//    for (int i = 0; i < strlen(buffer); i++) {
//        if (buffer[i] == '\n') count++;
//    }
//    get_memory(count + 1);
//    for (int i = 0, x = 0, y = 0; i < strlen(buffer); i++) {
//        if (buffer[i] != ' ' && buffer[i] != '\n') {
//            matrix[x][y] = buffer[i] - '0';
//            y++;
//        }
//        if (buffer[i] == '\n') {
//            x++;
//            y = 0;
//        }
//    }
//}
//
//void print_result(bool is_sequential_matrix) {
//    for (int i = 0; i < matrix_size; i++) {
//        for (int j = 0; j < matrix_size; j++) {
//            if (is_sequential_matrix) cout << result[i][j];
//            else cout << parallel_result[i][j];
//            if (j < matrix_size - 1) cout << " ";
//        }
//        if (i < matrix_size - 1) cout << "\n";
//    }
//}
//
//void sequential_matrix_multiplication() {
//    for (int i = 0; i < matrix_size; i++) {
//        for (int k = 0; k < matrix_size; k++) {
//            for (int j = 0; j < matrix_size; j++) {
//                result[i][k] += matrix[i][j] * matrix[j][k];
//            }
//        }
//    }
//}
//
//void* parallel_matrix_multiplication(void* arg) {
//    pthread_t id = pthread_self();
//    int number = 0;
//    for (int i = 0; i < process_count; i++) {
//        if (id == array[i]) {
//            number = i;
//            break;
//        }
//    }
//    for (int i = number; i < matrix_size; i += process_count) {
//        for (int k = 0; k < matrix_size; k++) {
//            for (int j = 0; j < matrix_size; j++) {
//                parallel_result[i][k] += matrix[i][j] * matrix[j][k];
//            }
//        }
//    }
//}
//
//void work(const string& filename, bool is_test_flag) {
//    clock_t time1, time2, time;
//    if (is_test_flag) cout << "Проверка корректности: \n";
//    else cout << "\nТеперь замерим время умножения больших матриц\n";
//    get_matrix_from_file(filename.c_str());
//    cout << "Последовательное умножение: \n";
//    time1 = clock();
//    sequential_matrix_multiplication();
//    time2 = clock();
//    time = time2 - time1;
//    if (is_test_flag) {
//        cout << "Результат последовательного умножения: \n";
//        print_result(true);
//    }
//    else cout << "\nЗатраченное время: " << (double)time / CLOCKS_PER_SEC << "\n";
//    cout << "\nПараллельное умножение: \n";
//    time1 = clock();
//    for (int i = 0; i < process_count; i++) {
//        pthread_create(&array[i], NULL, &parallel_matrix_multiplication, NULL);
//    }
//    for (int i = 0; i < process_count; i++) {
//        pthread_join(array[i], NULL);
//    }
//    time2 = clock();
//    time = time2 - time1;
//    if (is_test_flag) {
//        cout << "Результат параллельного умножения: \n";
//        print_result(false);
//    }
//    else cout << "\nЗатраченное время: " << (double)time / CLOCKS_PER_SEC << "\n";
//}






//int main() {
//    chdir("/home/artem/CLionProjects/SYSLAB3/");
//    //get_matrix_to_file("test_matrix.bin", 10);
//    get_matrix_to_file("matrix.bin", 1000);
//    work("test_matrix.bin", true);
//    work("matrix.bin", false);
//    free_memory();
//}



//задание 2

const int size_ = 20;
int* matrix = new int[size_];
bool* indexes_array = new bool[size_];
const int process_count = 4;
pthread_t array[process_count];
int indexes[size_];
int indexes_count = 0;
int max_value = 2;
int min_value = 1;
pthread_mutex_t mutex;
pthread_spinlock_t lock;
//pthread_barrier_t barrier;


void input_correctly_number(int& aa)
{
    while (!(cin >> aa) || cin.peek() != '\n')
    {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        while (cin.get() != '\n') {};
        cout << "Введено неверное значение. Повторите попытку: ";
    }
}

void Limitations(int min, int max, int& value)
{
    while (value < min || value > max)
    {
        cout << "Введенное число не соответствует промежутку. Повторите ввод: ";
        input_correctly_number(value);
    }
}

void* find_element(void* arg) {
    pthread_mutex_lock(&mutex);
    int value = *(int*)arg;
    pthread_t id = pthread_self();
    int number = 0;
    for (int i = 0; i < process_count; i++) {
        if (id == array[i]) {
            number = i;
            break;
        }
    }
    //pthread_spin_lock(&lock);
    //возрастание
    for (int i = number * (size_ / process_count); i < number * (size_ / process_count) + (size_ / process_count); i++) {
        if (matrix[i] == value) {
            indexes[indexes_count] = i;
            indexes_count++;
            indexes_array[i] = true;
        }
    }
    //убывание

//    for (int i = size_ - 1 - number * (size_ / process_count); i >= size_ - number * (size_ / process_count) - (size_ / process_count); i--) {
//        if (matrix[i] == value) {
//            indexes[indexes_count] = i;
//            indexes_count++;
//            indexes_array[i] = true;
//        }
//    }
    pthread_mutex_unlock(&mutex);
    //pthread_spin_unlock(&lock);
}

int main(int argc, char* argv[]) {
    int value = 2;
    cout << "Введите число от 0 до " << max_value << " для поиска в массиве: ";
    //input_correctly_number(value);
    //Limitations(0, max_value, value);
    cout << "Сгенерированный массив: \n";
    for (int i = 0; i < size_; i++) {
        matrix[i] = i % 2 == 0 ? 2 : 1;
        indexes_array[i] = false;
        cout << matrix[i] << " ";
    }
    cout << "\n";
    pthread_mutex_init(&mutex, NULL);
    //pthread_spin_init(&lock, 0);
    //pthread_barrier_init(&barrier, NULL, 4);
    for (int i = 0; i < process_count; i++) {
        pthread_create(&array[i], NULL, &find_element, &value);
    }
    for (int i = 0; i < process_count; i++) {
        pthread_join(array[i], NULL);
    }
    cout << "Введенное значение найдено в сгенерированном массиве по следующим индексам: \n";
    for (int i = 0; i < size_; i++) {
        if (indexes_array[i]) cout << i << " ";
    }
    pthread_mutex_destroy(&mutex);
    //pthread_spin_destroy(&lock);
    //pthread_barrier_destroy(&barrier);
}


//задание 3
//template<typename T>
//class threadsafe_queue {
//private:
//    int max_size;
//    int size = 0;
//    int* array;
//    pthread_mutex_t mutex;

//public:
//
//    threadsafe_queue(int max_size) {
//        if (max_size <= 0) {
//            throw "Максимальный размер очереди должен быть больше 0";
//        }
//        this->max_size = max_size;
//        array = new int[max_size];
//        pthread_mutex_init(&mutex, NULL);
//    }
//
//    threadsafe_queue(const threadsafe_queue& ) = delete;
//    threadsafe_queue(threadsafe_queue&&) = delete;
//
//    ~threadsafe_queue() {
//        delete[] array;
//        max_size = 0;
//        size = 0;
//        pthread_mutex_destroy(&mutex);
//    }
//
//    void enqueue(const T& v) {
//        try_enqueue(v);
//    }
//
//    T dequeue() {
//        return try_dequeue();
//    }
//
//    bool full() const {
//        return size == max_size;
//    }
//
//    bool empty() const {
//        return size == 0;
//    }
//
//    optional<T> try_dequeue() {
//        pthread_mutex_lock(&mutex);
//        if (empty()) {
//            throw "Очередь итак пуста!";
//        }
//        T tmp = array[0];
//        for (int i = 0; i < size - 1; i++) {
//            array[i] = array[i+1];
//        }
//        size--;
//        pthread_mutex_unlock(&mutex);
//        return tmp;
//    }
//
//    bool try_enqueue(const T& v) {
//        pthread_mutex_lock(&mutex);
//        if (full()) {
//            return false;
//        }
//        v[size] = v;
//        size++;
//        pthread_mutex_unlock(&mutex);
//        return true;
//    }
//
//
//};
//
//int main() {
//    threadsafe_queue<string> queue(10);
//}