#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

class Logger {
private:
    std::ofstream logFile;

public:
    Logger(const std::string &filename) {
        logFile.open(filename.c_str(), std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "Cannot open log file: " << filename << std::endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(const std::string &message) {
        logMessage("LOG", message);
    }

    void debug(const std::string &message) {
        logMessage("DEBUG", message);
    }

private:
    void logMessage(const std::string &level, const std::string &message) {
        if (logFile.is_open()) {
            time_t currentTime = std::time(nullptr);
            tm *timeInfo = std::localtime(&currentTime);

            char timeString[20];
            strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeInfo);

            logFile << "[" << level << "][" << timeString << "] " << message << std::endl;

            std::cout << "[" << level << "][" << timeString << "] " << message << std::endl;
        }
    }
};

class Matrix {
public:
    int rows;
    int cols;
    std::vector<std::vector<int>> data;

    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, std::vector<int>(cols, 0)) {}

    Matrix operator+(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::runtime_error("Matrix dimensions do not match for addition.");
        }

        Matrix result(rows, cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    Matrix operator-(const Matrix &other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::runtime_error("Matrix dimensions do not match for subtraction.");
        }

        Matrix result(rows, cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }

        return result;
    }

    Matrix operator*(const Matrix &other) const {
        if (cols != other.rows) {
            throw std::runtime_error("Matrix dimensions do not match for multiplication.");
        }

        Matrix result(rows, other.cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    Matrix operator/(int divisor) const {
        if (divisor == 0) {
            throw std::runtime_error("Matrix division by zero.");
        }

        Matrix result(rows, cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] / divisor;
            }
        }

        return result;
    }
};

int main() {
    Logger logger("log.txt");

    try {
        Matrix a(2, 3);
        Matrix b(2, 3);

        a.data = {{1, 2, 3}, {4, 5, 6}};
        b.data = {{7, 8, 9}, {10, 11, 12}};

        Matrix c = a + b;
        logger.log("Matrix Addition Result:");


        Matrix d = a - b;
        logger.log("Matrix Subtraction Result:");

        Matrix e = a * b;
        logger.log("Matrix Multiplication Result:");


        Matrix f = a / 2;  // Division by a scalar (2)
        logger.log("Matrix Division Result:");


    } catch (const std::exception &e) {
        logger.log("Exception caught: " + std::string(e.what()));
    }

    return 0;
}
