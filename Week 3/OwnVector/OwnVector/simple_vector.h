#pragma once

#include <cstdlib>
#include <iostream>

template <typename T>
class SimpleVector {
public:
    SimpleVector() {
        data = nullptr;
        end_ = nullptr;
        capacity = 0;
        size_ = 0;
    }
    explicit SimpleVector(size_t size) {
        capacity = size;
        size_ = size;
        data = new T[size];
        end_ = data + size;
    }
    ~SimpleVector() {
        delete[] data;
    }

    T& operator[](size_t index) {
        return *(data + index);
    }

    T* begin() {
        return data;
    }
    T* end() {
        return end_;
    }

    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return capacity;
    }
    void PushBack(const T& value) {
        if (data == nullptr) {
            data = new T[1];
            capacity = 1;
            size_ = 1;
            *data = value;
            end_ = data + 1;
        } else if (size_ == capacity) {
            T* temp = new T[capacity * 2];
            int counter = 0;
            //std::cout << *data << std::endl;
            while (counter < capacity) {
                //std::cout << *(data + counter) << std::endl;
                *(temp + counter) = *(data + counter);
                counter++;
            }
            capacity *= 2;
            size_++;
            delete[] data;
            data = temp;
            end_ = (data + size_);
            *(data + size_ - 1) = value;
        } else {
            size_++;
            *(data + size_ - 1) = value;
            end_ = data + size_;
        }
    }

private:
    T* data;
    T* end_;
    size_t capacity;
    size_t size_;
};
