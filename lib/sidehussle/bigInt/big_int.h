//
// Created by Yaser Alkayale on 2017-08-13.
//
/*
 * Implementing bigIn using base 2^31
 * Assuming only positive integers, no decimals, no negative integers
 */
#ifndef KMEANSII_BIG_INT_H
#define KMEANSII_BIG_INT_H

#include <vector>
#include <iostream>
#include <ostream>
#include <cmath>
#include <sstream>

#define ull unsigned long long
#define ll long long
namespace bigint{
class BigInt{
public:
  inline explicit BigInt(const BigInt &b) : isPositive_(true), data_(std::vector<ull>(1, 0)) {
    (*this) += b;
  }

  template<typename T>
  inline explicit BigInt(T initialValue = 0) : isPositive_(true), data_(std::vector<ull>(1, 0)) {
    (*this) += initialValue;
  }

  template<typename T>
  inline BigInt &operator+=(const T &b2) {
    ull maxVal = std::numeric_limits<ull>::max() >> 33;
    ull carry = b2;
    size_t currPos = 0;
    for(; currPos < data_.size() && carry > 0; ++currPos) {
      data_[currPos] += carry;
      carry = data_[currPos] >> 31;
      data_[currPos] = data_[currPos] & maxVal;
    }
    if(carry > 0) {
      data_.push_back(carry);
    }
    return (*this);
  }

  inline BigInt &operator+=(const BigInt &b2) {
    if(isPositive_ && !b2.isPositive_) {
      BigInt k(b2);
      k.isPositive_ = true;
      (*this) -= k;
    } else if(!isPositive_ && b2.isPositive_) {

    } else {
      if(data_.size() < b2.data_.size() + 1) {
        data_.resize(b2.data_.size(), 0);
      }
      ull maxVal = std::numeric_limits<ull>::max() >> 33;
      std::size_t currPos = 0;
      ull carry = 0;
      while(currPos < b2.data_.size()) {
        data_[currPos] += b2.data_[currPos] + carry;
        carry = data_[currPos] >> 31;
        data_[currPos] = data_[currPos] & maxVal;
        ++currPos;
      }
      for(; currPos < data_.size() && carry > 0; ++currPos) {
        data_[currPos] += carry;
        carry = data_[currPos] >> 31;
        data_[currPos] = data_[currPos] & maxVal;
      }
      if(carry > 0) {
        data_.push_back(carry);
      }
      return (*this);
    }
  }

  inline BigInt &operator-=(const BigInt &b2) {
    if((*this) > b2) {

    } else {

    }
    return (*this);
  }


  bool operator<=(const BigInt &b2) {
    return (*this) == b2 || (*this) < b2;
  }

  bool operator>=(const BigInt &b2) {
    return (*this) == b2 || (*this) > b2;
  }

  bool operator>(const BigInt &b2) {
    return !((*this) <= b2);
  }

  inline bool operator==(const BigInt &b2) {
    this->cleanup();
    BigInt k(b2);
    k.cleanup();
    if(isPositive_ == k.isPositive_) { return false; }
    if(data_.size() != b2.data_.size()) { return false; }
    for(size_t i = 0; i < data_.size(); ++i) {
      if(data_[i] != k.data_[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator<(const BigInt &b2) {
    if(isPositive_ && !b2.isPositive_) { return false; }
    if(!isPositive_ && b2.isPositive_) { return true; }
    if(!isPositive_ && !b2.isPositive_) {
      this->cleanup();
      BigInt k(b2);
      k.cleanup();
      if(data_.size() > k.data_.size()) { return true; }
      if(data_.size() < k.data_.size()) { return false; }
      for(ll i = data_.size(); i >= 0; --i) {
        if(data_[i] < k.data_[i]) { return false; }
      }
      return true;
    }
    if(this->isPositive_ && b2.isPositive_) {
      this->cleanup();
      BigInt k(b2);
      k.cleanup();
      if(data_.size() < k.data_.size()) { return true; }
      if(data_.size() > k.data_.size()) { return false; }
      for(ll i = data_.size(); i >= 0; --i) {
        if(data_[i] > k.data_[i]) { return false; }
      }
      return true;
    }
  }


  friend std::ostream &operator<<(std::ostream &o, const BigInt &b);

  /*
   * remove all the trailing zero elements
   */
  inline void cleanup() {
    if(data_.empty())
      return;
    size_t i = data_.size() - 1;
    while(true) {
      if(data_[i] == 0) data_.pop_back();
      else return;

      if(i == 0) break;
      --i;
    }
  }

private:
  std::vector<ull> data_;
  bool isPositive_;

};

inline std::ostream &operator<<(std::ostream &o, const BigInt &b) {
  ull num;
  std::stringstream s;
  for(auto section : b.data_) {
    for(int i = 0; i < 31; ++i) {
      s << (section & 1);
      section = section >> 1;
    }
  }
  std::string temp = s.str();
  for(ll i = temp.size() - 1; i >= 0; --i) {
    o << temp[i];
  }
  return o;
}





/*
 * Assuming this is a value that is not a BigInt
 */
//    template<typename T>
//    BigInt &operator+=(BigInt &b, T toAdd) {
//        if (toAdd < maxVal) {
//
//        }
//    }
//
//    BigInt &operator++() {
//        return (*this) += 1;
//    }
//
//    BigInt &operator++(int) {
//        BigInt temp(*this);
//        (*this) += 1;
//        return temp;
//    }
//
//    BigInt operator+(const BigInt &i1, const BigInt &i2) {
//        BigInt result;
//        result = i1;
//        result += i2;
//        return result;
//    }

}//namespace bigint

#endif //KMEANSII_BIG_INT_H
