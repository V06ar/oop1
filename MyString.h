
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstring> // Разрешено по условию 2 (функции работы с Си-строками)
class MyString {
private:
	char* data;
	size_t length;	
	size_t capacity1;
	void new_capacity(size_t new_capacity);
public:
	MyString();
	MyString(const char* str);
	MyString(const std::string& str);
	MyString(const MyString& str);
	MyString(const char* str, int count);
	MyString(const std::string& str,int count);
	MyString(const MyString& str,int count);
	MyString(int count, char ch);
	~MyString();


	const char* c_str() const;
	void clear();
	void shrink_to_fit();
	MyString& operator =(const char* str);
	MyString& operator=(const std::string& str);
	MyString& operator=(const MyString& str);
	MyString& operator=(char ch);
	size_t size() const;
	size_t capacity() const;
	bool empty() const;
	void insert(int index, int count, char ch);
	void insert(int index, const char* str);
	void insert(int index, const std::string& str) { insert(index, str.c_str()); }
	void insert(int index, const MyString& str) { insert(index, str.c_str()); }
	void insert(int index, const char* str, int count);
	void insert(int index, const std::string& str, int count) { insert(index, str.c_str(), count); }
	void insert(int index, const MyString& str, int count) { insert(index, str.c_str(), count); }
	void insert(int index, const char* str, int s_index, int count);
	void insert(int index, const std::string& str, int s_index, int count) { insert(index, str.c_str(), s_index, count); }
	void insert(int index, const MyString& str, int s_index, int count) { insert(index, str.c_str(), s_index, count); }
	void append(const char* str);
	void append(const std::string& str);
	void append(const MyString& str);

	// --- Группа 2: append(str, count) ---
	void append(const char* str, int count);
	void append(const std::string& str, int count);
	void append(const MyString& str, int count);

	// --- Группа 3: append(str, s_index, count) ---
	void append(const char* str, int s_index, int count);
	void append(const std::string& str, int s_index, int count);
	void append(const MyString& str, int s_index, int count);

	// --- Отдельная перегрузка: append(char) и append(count, char) ---
	void append(char ch) { insert(length, 1, ch); } // или через operator+=
	void append(int count, char ch);
	void erase(int index, int count);
	void replace(int index, int count, const char* str);
	void replace(int index, int count, const std::string& str);
	void replace(int index, int count, const MyString& str);

	void replace(int index, int count, const char* str, int s_count);
	void replace(int index, int count, const std::string& str, int s_count);
	void replace(int index, int count, const MyString& str, int s_count);

	void replace(int index, int count, const char* str, int s_index, int s_count);
	void replace(int index, int count, const std::string& str, int s_index, int s_count);
	void replace(int index, int count, const MyString& str, int s_index, int s_count);
	MyString substr(int index) const;
	MyString substr(int index, int count) const;
	MyString operator+(const char* str) const;
	MyString operator+(const std::string& str) const;
	MyString operator+(const MyString& str) const;

	MyString& operator+=(const char* str);
	MyString& operator+=(const std::string& str);
	MyString& operator+=(const MyString& str);
	char& operator[](int index);
	const char& operator[](int index) const;
	int compare(const MyString& str) const;
	bool operator>(const MyString& str) const;
	bool operator<(const MyString& str) const;
	bool operator>=(const MyString& str) const;
	bool operator<=(const MyString& str) const;
	bool operator==(const MyString& str) const;
	bool operator!=(const MyString& str) const;
	int find(const char* str, int index = 0) const;
	int find(const std::string& str, int index = 0) const;
	int find(const MyString& str, int index = 0) const;
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);

// Функция pstr для форматированного вывода (как в примере задания)
void pstr(const MyString& str);

#endif
};