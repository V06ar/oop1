#include "MyString.h"
void MyString::new_capacity(size_t new_capacity) {
	if (new_capacity <= capacity1) {
		return;
	}
	char* new_data = new char[new_capacity];
	if (data) {
		std::memcpy(new_data, data, length + 1);
		delete[] data;
	}
	else {
		new_data[0] = '\0';
	}
	data = new_data;
	capacity1 = new_capacity;
}
//constructors
MyString::MyString():data(nullptr),length(0),capacity1(0) {
	new_capacity(1);
	data[0] = '\0';
}
MyString::MyString(const char* str): data(nullptr),length(0),capacity1(0) {
	if (!str) {
		throw std::invalid_argument("Null string pointer");
	}
	length = std::strlen(str);
	new_capacity(length + 1);
	std::memcpy(data, str, length + 1);
}
MyString::MyString(const std::string& str) : data(nullptr), length(0), capacity1(0) {
	length = str.size();
	new_capacity(length + 1);
	std::memcpy(data, str.data(), length);
	data[length] = '\0';
}

MyString::MyString(const MyString& str) : data(nullptr), length(0), capacity1(0) {
	length = str.length;
	new_capacity(length+1);
	if(str.data){
		std::memcpy(data, str.data, length + 1);
	}
	else{
		data[0] = '\0';
	}
}
MyString::MyString(const char* str, int count): data(nullptr),length(0),capacity1(0) {
	if (!str) throw std::invalid_argument("Null string pointer");
	if (count < 0) throw std::out_of_range("Count cannot be negative");
	size_t length_str = std::strlen(str);
	if (static_cast<size_t>(count) > length_str) {
		length = length_str;
	}
	else {
		length = count;	
	}
	new_capacity(length + 1); 
	std::memcpy(data, str, length);
	data[length] = '\0';
}
MyString::MyString(const std::string& str, int count) :MyString(str.c_str(), count) {}
MyString::MyString(const MyString& str, int count) :MyString(str.c_str(), count) {}
MyString::MyString(int count, char ch) : data(nullptr), length(0), capacity1(0) {
	if (count < 0) throw std::out_of_range("Count cannot be negative");
	length = count;
	new_capacity(length + 1);
	std::memset(data, ch, length);
	data[length] = '\0';
}
MyString::~MyString() {
	delete[]data;
}
void MyString::clear() {
	length = 0;
	if (data) {
		data[0] = '\0';
	}
}
void MyString::shrink_to_fit() {
	if (capacity1 > length + 1) {
		size_t new_cap = length + 1;
		char* new_data = new char[new_cap];
		if (data) {
			std::memcpy(new_data, data, length + 1);
			delete[] data;
		}
		data = new_data;
		capacity1 = new_cap;
	}
}
MyString& MyString::operator=(const char* str) {
	if (!str) {
		throw std::invalid_argument("Null string pointer");
	}
	size_t new_length = std::strlen(str);
	if (new_length + 1 > capacity1) {
		new_capacity(new_length + 1);
	}
	length = new_length;
	std::memcpy(data, str, new_length + 1);
	return *this;
}
MyString& MyString::operator=(const std::string& str) {
	return operator=(str.c_str());
}
MyString& MyString::operator=(const MyString& str) {
	if (this != &str) {
		operator=(str.c_str());
	}
	return *this;
}
MyString& MyString::operator=(char ch)
{
	if (capacity1 < 2) {
		new_capacity(2);
	}
	data[0] = ch;
	data[1] = '\0';
	length = 1;
	return *this;
}
const char* MyString::c_str() const {
	if (data) {
		return data;
	}
	else {
		return "";
	}
}
size_t MyString::size() const {
	return length;
}
size_t MyString::capacity() const {
	return capacity1;
}
bool MyString::empty() const {
	return length == 0;
}
void MyString::insert(int index, int count, char ch) {
	if (index < 0 || static_cast<size_t>(index) > length) throw std::out_of_range("Index out of range");
	if (count <= 0) return;
	size_t u_index = static_cast<size_t>(index);
	size_t u_count = static_cast<size_t>(count);
	size_t new_size = length + u_count;
	if (new_size + 1 > capacity1) {
		new_capacity(new_size + 1);
	}
	std::memmove(data + u_index + u_count, data + u_index, length - u_index + 1);
	std::memset(data + u_index, ch, u_count);
	length = new_size;
}
void MyString::insert(int index, const char* str) {
	if (!str) throw std::invalid_argument("Null string pointer");
	insert(index, str, 0, std::strlen(str));
}
void MyString::insert(int index, const char* str, int count) {
	insert(index, str, 0, count);
}
void MyString::insert(int index, const char* str, int s_index, int count){
	if (!str) throw std::invalid_argument("Null string pointer");
	if (index < 0 || static_cast<size_t>(index) > length) throw std::out_of_range("Index out of range");
	if (s_index < 0 || static_cast<size_t>(s_index) > std::strlen(str)) throw std::out_of_range("Source index out of range");
	if (count <= 0) return;
	size_t u_index = static_cast<size_t>(index);
	size_t u_sindex = static_cast<size_t>(s_index);
	size_t u_count = static_cast<size_t>(count);
	size_t new_length = std::strlen(str + u_index);
	if (u_count > new_length) {
		u_count = new_length;
	}
	size_t new_size = length + u_count;
	if(new_size+1> capacity1) {
		new_capacity(new_size + 1);
	}
	std::memmove(data + u_index + u_count, data + u_index, length - u_index + 1);
	std::memcpy(data + u_index, str + u_sindex, u_count);
	length = new_size;
}
void MyString::append(int count, char ch) {
	insert(length, count, ch);
}
void MyString::append(const char* str) {
	if (!str) throw std::invalid_argument("Null string pointer");
	insert(length, str, 0, std::strlen(str));
}
void MyString::append(const std::string& str) { 
	append(str.c_str()); 
}
void MyString::append(const MyString& str) { 
	append(str.c_str());
}
void MyString::append(const char* str, int count) {
	insert(length, str, 0, count);
}
void MyString::append(const std::string& str, int count) { 
	append(str.c_str(), count); 
}
void MyString::append(const MyString& str, int count) { 
	append(str.c_str(), count);
}
void MyString::append(const char* str, int s_index, int count) {
	insert(length, str, s_index, count);
}
void MyString::append(const std::string& str, int s_index,int count) {
	append(str.c_str(),s_index, count);
}
void MyString::append(const MyString& str, int s_index, int count) {
	append(str.c_str(), s_index, count);
}
void MyString::erase(int index, int count) {
	if (index < 0 || static_cast<size_t>(index) > length) throw std::out_of_range("Index out of range");
	if (count <= 0) return;

	size_t u_index = static_cast<size_t>(index);
	size_t u_count = static_cast<size_t>(count);

	if (u_index + u_count > length) {
		u_count = length - u_index;
	}

	std::memmove(data + u_index, data + u_index + u_count, length - u_index - u_count + 1);
	length -= u_count;
}
void MyString::replace(int index, int count, const char* str) {
	if (!str) throw std::invalid_argument("Null string pointer");
	replace(index, count, str, 0, std::strlen(str));
}
void MyString::replace(int index, int count, const std::string& str) {
	replace(index, count, str.c_str());
}
void MyString::replace(int index, int count, const MyString& str) { 
	replace(index, count, str.c_str());
}
void MyString::replace(int index, int count, const char* str, int s_count) {
	replace(index, count, str, 0, s_count);
}
void MyString::replace(int index, int count, const std::string& str, int s_count) {
	replace(index, count, str.c_str(), s_count); 
}
void MyString::replace(int index, int count, const MyString& str, int s_count) {
	replace(index, count, str.c_str(), s_count);
}
void MyString::replace(int index, int count, const char* str, int s_index, int s_count) {
	erase(index, count);
	insert(index, str, s_index, s_count);
}
void MyString::replace(int index, int count, const std::string& str, int s_index, int s_count) { 
	replace(index, count, str.c_str(), s_index, s_count); 
}
void MyString::replace(int index, int count, const MyString& str, int s_index, int s_count) {
	replace(index, count, str.c_str(), s_index, s_count);
}
MyString MyString::substr(int index) const {
	if (index < 0 || static_cast<size_t>(index) > length) throw std::out_of_range("Index out of range");
	return MyString(data + index);
}
MyString MyString::substr(int index, int count) const {
	if (index < 0 || static_cast<size_t>(index) > length) throw std::out_of_range("Index out of range");
	return MyString(data + index, count);
}
MyString MyString::operator+(const char* str) const {
	MyString res(*this);
	res.append(str);
	return res;
}
MyString MyString::operator+(const std::string& str) const { 
	return *this + str.c_str(); 
}
MyString MyString::operator+(const MyString& str) const { 
	return *this + str.c_str();
}
MyString& MyString::operator+=(const char* str) {
	append(str);
	return *this;
}
MyString& MyString::operator+=(const std::string& str) { 
	return *this += str.c_str(); 
}
MyString& MyString::operator+=(const MyString& str) {
	return *this += str.c_str(); 
}
char& MyString::operator[](int index) {
	if (index < 0 || static_cast<size_t>(index) >= length) throw std::out_of_range("Index out of range");
	return data[index];
}
const char& MyString::operator[](int index) const {
	if (index < 0 || static_cast<size_t>(index) >= length) throw std::out_of_range("Index out of range");
	return data[index];
}
int MyString::compare(const MyString& str) const {
	int cmp = std::strcmp(c_str(), str.c_str());
	if (cmp < 0) return -1;
	if (cmp > 0) return 1;
	return 0;
}
bool MyString::operator>(const MyString& str) const { 
	return compare(str) > 0; 
}
bool MyString::operator<(const MyString& str) const { 
	return compare(str) < 0; 
}
bool MyString::operator>=(const MyString& str) const { 
	return compare(str) >= 0; 
}
bool MyString::operator<=(const MyString& str) const { 
	return compare(str) <= 0;
}
bool MyString::operator==(const MyString& str) const { 
	return compare(str) == 0;
}
bool MyString::operator!=(const MyString& str) const { 
	return compare(str) != 0; 
}
int MyString::find(const char* str, int index) const {
	if (!str) throw std::invalid_argument("Null string pointer");
	if (index < 0 || static_cast<size_t>(index) > length) return -1;

	const char* pos = std::strstr(data + index, str);
	if (!pos) return -1;
	return static_cast<int>(pos - data);
}
int MyString::find(const std::string& str, int index) const { 
	return find(str.c_str(), index); 
}
int MyString::find(const MyString& str, int index) const { 
	return find(str.c_str(), index);
}
// Вывод в поток
std::ostream& operator<<(std::ostream& os, const MyString& str) {
	os << str.c_str();
	return os;
}

// Служебная функция pstr по условию лабораторной работы
void pstr(const MyString& str) {
	std::cout << "\"" << str.c_str() << "\" (" << str.size() << ", " << str.capacity() << ")" << std::endl;
}