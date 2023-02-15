#pragma once

#include <cstring>
#include <iostream>
#include <vector>

class String {
public:
  String() = default;
  explicit String(std::size_t size, char character);
  String(const char* character);
  String(const String& string);
  ~String();

  String& operator=(String string);
  bool operator<(const String& string) const;
  bool operator<=(const String& string) const;
  bool operator==(const String& string) const;
  bool operator>(const String& string) const;
  bool operator>=(const String& string) const;
  bool operator!=(const String& string) const;
  String& operator+=(const String& string);
  String& operator*=(int multiplier);
  friend String operator*(String string, int multiplier);
  friend String operator+(String string, const String& string_to_add);

  char& operator[](std::size_t index);
  const char& operator[](std::size_t index) const;

  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(std::size_t new_size);
  void Resize(std::size_t new_size, char character);
  void Reserve(std::size_t new_cap);
  void ShrinkToFit();
  void Swap(String& string);

  char& Front();
  char Front() const;
  char& Back();
  char Back() const;
  bool Empty() const;
  std::size_t Size() const;
  std::size_t Capacity() const;
  const char* Data();
  const char* Data() const;

  std::vector<String> Split(const String& delim = " ") const;
  String Join(const std::vector<String>& strings) const;

  friend std::istream& operator>>(std::istream& istream, String& string);
  friend std::ostream& operator<<(std::ostream& ostream, const String& string);

private:
  char* string_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;

  void ChangeCapacity();
  void ChangeCapacity(std::size_t new_capacity);
};
