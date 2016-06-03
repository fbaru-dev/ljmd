#ifndef _VEC3D_HPP
#define _VEC3D_HPP

#include <iostream>
#include <iomanip> 
#include <cmath>
#include <stdexcept>

typedef double real_type;

template <typename T> 
class Vec3D 
{
  private:
    T data[3];
  public:
    Vec3D();
    Vec3D(T value);
    Vec3D(T x, T y, T z);
    Vec3D(const Vec3D<T>& v);
    Vec3D(const T v[3]);

   
    // assignment is not the same as initialization
    Vec3D& operator=(const Vec3D<T>& v);
    
    T& operator[](int i);
    const T& operator[](int i) const;

    // unary operators
    Vec3D& operator+=(const Vec3D<T>& v);
    Vec3D& operator-=(const Vec3D<T>& v);
    Vec3D& operator*=(const T v);
    Vec3D& operator/=(const T v);

    // bool operators
    bool operator==(const Vec3D<T>& v) const;
    bool operator!=(const Vec3D<T>& v) const;

    // elementwise binary operators
    Vec3D operator+ (const Vec3D<T> &v) const;
    Vec3D operator- (const Vec3D<T> &v) const;
    Vec3D operator* (T v) const;
    Vec3D operator/ (T v) const;
    
    // Cross product of two Vec3D
    Vec3D cross(const Vec3D<T>& v) const;

    // binary dot product
    T operator* (const Vec3D<T>& v) const;

    T sqr() const;
    T abs() const;
    
    // set and get operators
    T& at(int i);
    const T& at(int i) const;

    void setItem(int i, T v);
    T getItem(int i) const;
    
    template<typename T2> Vec3D<T2> convert()
    {
       Vec3D<T2> ret;
       ret.at(0) =  static_cast<T2>(this->at(0));
       ret.at(1) =  static_cast<T2>(this->at(1));
       ret.at(2) =  static_cast<T2>(this->at(2));
    }
  
};

template<typename T>
inline Vec3D<T>::Vec3D(){data[0] = data[1] = data[2] = 0;}

template<typename T>
inline Vec3D<T>::Vec3D(T value) {data[0] = data[1] = data[2] = value;}

template<typename T>
inline Vec3D<T>::Vec3D(T x, T y, T z){data[0] = x; data[1] = y; data[2] = z;}

template<typename T>
inline Vec3D<T>::Vec3D(const Vec3D<T> &v){data[0] = v[0]; data[1] = v[1]; data[2] = v[2];}

template<typename T>
inline Vec3D<T>::Vec3D(const T v[3]) {data[0] = v[0]; data[1] = v[1]; data[2] = v[2];}

template<typename T>
inline T &Vec3D<T>::operator[](int i) {return data[i];}    

template<typename T>
inline const T &Vec3D<T>::operator[](int i) const {return data[i];}    

//assignment
template<typename T>
inline Vec3D<T> &Vec3D<T>::operator=(const Vec3D<T> &v) 
{
  data[0] = v[0];
  data[1] = v[1];
  data[2] = v[2];
  return *this;
}

// unary operators
template<typename T>
inline Vec3D<T> &Vec3D<T>::operator+=(const Vec3D<T> &v)
{ for (int i = 0; i < 3; i++) data[i] += v.data[i]; return *this;}

template<typename T>
inline Vec3D<T> &Vec3D<T>::operator-=(const Vec3D<T> &v)
{ for (int i = 0; i < 3; i++) data[i] -= v.data[i]; return *this;}

template<typename T>
inline Vec3D<T> &Vec3D<T>::operator*=(const T v)
{ for (int i = 0; i < 3; i++) data[i] *= v; return *this;}

template<typename T>
inline Vec3D<T> &Vec3D<T>::operator/=(const T v) { 
  T v_1 = 1.0/v;
  for (int i = 0; i < 3; i++) 
    data[i] *= v_1; 
  return *this;
}

// bool operators
template<typename T>
inline bool Vec3D<T>::operator==(const Vec3D<T> &v) const {
  return 
      (data[0] == v.data[0]) &&
      (data[1] == v.data[1]) &&
      (data[2] == v.data[2]);
}
  
template<typename T>
inline bool Vec3D<T>::operator!=(const Vec3D<T> &v) const { return ! (*this == v);}

// elementwise binary operators
template<typename T>
inline Vec3D<T> Vec3D<T>::operator+(const Vec3D<T> &v) const { return Vec3D<T>(*this) += v;}

template<typename T>
inline Vec3D<T> Vec3D<T>::operator-(const Vec3D<T> &v) const{ return Vec3D<T>(*this) -= v;}

template<typename T>  
inline Vec3D<T> Vec3D<T>::operator*(T v) const { return Vec3D<T>(*this) *= v;}

template<typename T>
inline Vec3D<T> Vec3D<T>::operator/(T v) const { return Vec3D<T>(*this) /= v;}  

// Cross product of two Vec3D
template<typename T>
inline Vec3D<T> Vec3D<T>::cross(const Vec3D<T> &v) const {
  return Vec3D<T>(data[1]*v[2] - data[2]*v[1],
		  data[2]*v[0] - data[0]*v[2],
		  data[0]*v[1] - data[1]*v[0]);
}

// binary dot product
template<typename T>
inline T Vec3D<T> ::operator* (const Vec3D<T> &v) const
{ return data[0]*v.data[0] + data[1]*v.data[1] + data[2]*v.data[2];}

template<typename T>
inline T Vec3D<T>::sqr() const
{ return data[0]*data[0] + data[1]*data[1] + data[2]*data[2]; }

template<typename T>
inline T Vec3D<T>::abs() const
{ return sqrt(sqr()); }

// set and ger operators
template<typename T>
inline T &Vec3D<T>::at(int i) {
  if (i < 0 || i > 2)
    throw std::out_of_range("Vec3D::at");
  return (*this)[i];
}

template<typename T>
inline const T &Vec3D<T>::at(int i) const {
  if (i < 0 || i > 2)
    throw std::out_of_range("Vec3D::at");
   return (*this)[i];
}

template<typename T>
inline void Vec3D<T>::setItem(int i, T v)
{ this->at(i) = v; }

template<typename T> 
inline T Vec3D<T>::getItem(int i) const
{ return this->at(i); }

//outstream for '<<' operator
template<typename T>
inline std::ostream &operator<<(std::ostream &out, const Vec3D<T> &v) 
{
  return out << std::left << std::setprecision(9) << std::setw(10)
  << v[0] << ' ' << v[1] << ' ' << v[2];
}

#ifdef TEST
int main(int argc, char** argv )
{
	cout << "Test Case" << endl;
	Vec3D<double> v1;
	Vec3D<double> v2(2);
	Vec3D<double> v3(1,2,3);
 	Vec3D<double> v4(v2);
	float a[3];
	a[0] = 4; a[1] = 5;a[2] = 6;
	Vec3D<float> v5(a);
	
	cout << v1 << endl;
	cout << v2 << endl;
	cout << v3 << endl;
	cout << v4 << endl;
	cout << v5 << endl;
	cout << endl;
	//assignment
	v1 = v3;
	cout << v1 << endl;
	cout << endl;
	// unary operators
	v1 += v2;
	v2 -= v4;
	v3 *= 3.1;
	v5 /= 10;
	cout << v1 << endl;
	cout << v2 << endl;
	cout << v3 << endl;
	cout << v4 << endl;
	cout << v5 << endl;
	cout << endl;
	// bool operators
	bool b = (v1==v2)?(true):(false);
	cout << b << endl;
	b = (v1!=v2)?(true):(false);
	cout << b << endl;
	b = (v5==v5)?(true):(false);
	cout << b << endl;
	cout << endl;
	// elementwise binary operators

	v1 = v2 + v3; 
	v2 = v3 - v1; 
	v3 = v4 * 2;
	v4 = v1 / 2;
	cout << v1 << endl;
	cout << v2 << endl;
	cout << v3 << endl;
	cout << v4 << endl;
	cout << v5 << endl;
	cout << endl;
	cout << v1*v1 << endl;
	cout << v1.cross(v3) << endl;
	cout << endl;
	cout << v4.sqr() << endl;
	cout << v4.abs() << endl;
	
}
#endif

#endif