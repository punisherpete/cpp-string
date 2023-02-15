#include "string.hpp"

String::String(std::size_t size, char character) {
  capacity_ = size_ = size;
  string_ = new char[size_ + 1];
  memset(string_, character, size);
  string_[capacity_] = 0;
}

String::String(const char* character) {
  capacity_ = size_ = strlen(character);
  string_ = new char[capacity_ + 1];
  memcpy(string_, character, size_);
  string_[capacity_] = 0;
}

String::String(const String& string) {
  capacity_ = string.capacity_;
  size_ = string.size_;
  string_ = new char[capacity_ + 1];
  memcpy(string_, string.string_, size_);
  string_[size_] = 0;
}

String::~String() { delete[] string_; }

String& String::operator=(String string) {
  Swap(string);
  return *this;
}

bool String::operator<(const String& string) const {
  int result = memcmp(string_, string.string_, std::min(size_, string.size_));
  return result < 0 || result == 0 && size_ < string.size_;
}

bool String::operator<=(const String& string) const {
  int result = memcmp(string_, string.string_, std::min(size_, string.size_));
  return result <= 0 && size_ <= string.size_;
}

bool String::operator==(const String& string) const {
  int result = memcmp(string_, string.string_, std::min(size_, string.size_));
  return result == 0 && size_ == string.size_;
}

bool String::operator>(const String&string) const { return !(*this <= string); }

bool String::operator>=(const String&string) const { return !(*this < string); }

bool String::operator!=(const String&string) const { return !(*this == string); }

String& String::operator+=(const String& string) {
  size_t prev_size = size_;
  Resize(size_ + string.size_);
  memcpy(string_ + prev_size, string.string_, string.size_);
  return *this;
}

String operator+(String string, const String& string_to_add) { return string += string_to_add; }

String operator*(String string, int multiplier) { return string *= multiplier; }

String& String::operator*=(int multiplier) {
  ChangeCapacity(size_ * multiplier);
  for (int i = 1; i < multiplier; ++i) {
    memcpy(string_ + size_ * i, string_, size_);
  }

  size_ *= multiplier;
  string_[size_] = 0;
  return *this;
}

char& String::operator[](std::size_t index) { return string_[index]; }

const char& String::operator[](std::size_t index) const { return string_[index]; }

void String::Clear() {
  size_ = 0;
  string_[0] = 0;
}

void String::PushBack(char character) {
  while (size_ >= capacity_) {
    ChangeCapacity();
  }

  string_[size_] = character;
  string_[++size_] = 0;
}

void String::PopBack() {
  if (size_ != 0) {
    string_[--size_] = 0;
  }
}

void String::Resize(std::size_t new_size) {
  char* tmp = string_;
  capacity_ = new_size;
  string_ = new char[capacity_ + 1];
  memcpy(string_, tmp, std::min(size_, capacity_));
  delete[] tmp;
  size_ = capacity_;
  string_[capacity_] = 0;
}

void String::Resize(std::size_t new_size, char character) {
  char* tmp = string_;
  capacity_ = new_size;
  string_ = new char[capacity_ + 1];
  memcpy(string_, tmp, std::min(size_, capacity_));
  delete[] tmp;
  memset(string_ + std::min(size_, capacity_), character,
         capacity_ - std::min(size_, capacity_));
  size_ = capacity_;
  string_[capacity_] = 0;
}

void String::Reserve(std::size_t new_cap) {
  if (capacity_ >= new_cap) {
    return;
  }

  std::size_t prev_size = size_;
  Resize(new_cap);
  size_ = prev_size;
  string_[size_] = 0;
}

void String::ShrinkToFit() {
  if (capacity_ == size_) {
    return;
  }

  Resize(size_);
}

void String::Swap(String& string) {
  std::swap(string_, string.string_);
  std::swap(capacity_, string.capacity_);
  std::swap(size_, string.size_);
}

char& String::Front() { return string_[0]; }

char String::Front() const { return string_[0]; }

char& String::Back() { return string_[size_ - 1]; }

char String::Back() const { return string_[size_ - 1]; }

bool String::Empty() const { return size_ == 0; }

std::size_t String::Size() const { return size_; }

std::size_t String::Capacity() const { return capacity_; }

const char* String::Data() { return string_; }

const char* String::Data() const { return string_; }

std::vector<String> String::Split(const String& delim) const {
  std::vector<std::size_t> split_positions = {0};

  for (std::size_t i = 0; i <= size_ - delim.size_ && size_ >= delim.size_;
       ++i) {
    bool eq = memcmp(string_ + i, delim.string_, delim.size_) == 0;
    if (eq) {
      split_positions.push_back(i);
      i += delim.size_;
      split_positions.push_back(i--);
    }
  }

  split_positions.push_back(size_);
  std::vector<String> split(split_positions.size() / 2);
  for (size_t i = 0; i < split_positions.size() - 1; i += 2) {
    split[i / 2] = String("");
    split[i / 2].Resize(split_positions[i + 1] - split_positions[i]);
    memcpy(split[i / 2].string_, string_ + split_positions[i],
           split[i / 2].size_);
  }
  return split;
}

String String::Join(const std::vector<String>& strings) const {
  String tmp;
  for (std::size_t i = 0; i < strings.size(); ++i) {
    tmp += strings[i];
    if (i != strings.size() - 1) {
      tmp += *this;
    }
  }

  return tmp;
}

std::istream& operator>>(std::istream&istream, String&string) {
  char tmp;
  string = String();
  while (istream.get(tmp)) {
    if (tmp == ' ' || tmp == '\n' || tmp == '\0') {
      break;
    }
    string.PushBack(tmp);
  }

  return istream;
}

std::ostream& operator<<(std::ostream&ostream, const String&string) {
  return ostream << string.Data();
}

void String::ChangeCapacity() {
  size_t prev_size = size_;
  Resize(std::max(capacity_ * 2, (size_t)1));
  size_ = prev_size;
}

void String::ChangeCapacity(std::size_t new_capacity) {
  std::size_t prev_size = size_;
  capacity_ = std::max(capacity_ * 2, (size_t)1);
  while (capacity_ <= new_capacity) {
    capacity_ <<= 1;
  }
  
  Resize(capacity_);
  size_ = prev_size;
}
