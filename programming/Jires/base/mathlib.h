#ifndef MATHLIB_H
#define MATHLIB_H
#include <stdio.h>//TODO remove this debug staff
#include <cstdint>
#include <cmath>
#ifndef MATH_PI
#define MATH_PI 3.1415926535897932384626433832795
#endif
#define ToRadians(x) (float)(((x) * MATH_PI / 180.0f))
#define ToDegrees(x) (float)(((x) * 180.0f / MATH_PI))

template<typename T, unsigned int D>
struct Vector{
public:
	inline T dot(const Vector<T, D>& r)const{
		unsigned int i;
		T res = T(0);
		for(i=0;i<D;++i)res+=values[i]*r[i];
		return res;
	}

	inline Vector<T, D> max(const Vector<T, D>& r)const{
		unsigned int i;
		Vector<T, D> res;
		for(i=0;i<D;++i)res[i]=values[i]>r[i]?values[i]:r[i];
		return res;
	}

	inline T max()const{
		T res(0);
		unsigned int i;
		for(i=0;i<D;++i)if(res<values[i])res=values[i];
		return res;
	}

	inline T lengthSq(){return this->dot(*this);}
	inline T length(){return sqrt(lengthSq());}
	inline Vector<T, D> normalized(){return (*this)/length();}
	inline void normalize(){(*this)/=length();}
	inline Vector<T,D> lerp(const Vector<T,D>& r, T lerpFactor)const{ return (r - *this) * lerpFactor + *this; }

	inline Vector<T, D> Reflect(const Vector<T,D>& normal)const{
		return *this - (normal * (this->Dot(normal) * 2));
	}

	inline Vector<T, D> operator+(const Vector<T, D>& r)const{
		Vector<T, D> res;
		unsigned int i;
		for(i=0;i<D;++i)res[i]=values[i]+r[i];
		return res;
	}

	inline Vector<T, D>& operator+=(const Vector<T, D>& r)const{
		unsigned int i;
		for(i=0;i<D;++i)values[i]+=r[i];
		return *this;
	}

	inline Vector<T, D> operator+(const T& r)const{
		Vector<T, D> res;
		unsigned int i;
		for(i=0;i<D;++i)res[i]=values[i]+r;
		return res;
	}

	inline Vector<T, D>& operator+=(const T& r)const{
		unsigned int i;
		for(i=0;i<D;++i)values[i]+=r;
		return *this;
	}

	inline Vector<T, D> operator-(const Vector<T, D>& r)const{
		Vector<T, D> res;
		unsigned int i;
		for(i=0;i<D;++i)res[i]=values[i]-r[i];
		return res;
	}

	inline Vector<T, D>& operator-=(const Vector<T, D>& r)const{
		unsigned int i;
		for(i=0;i<D;++i)values[i]-=r[i];
		return *this;
	}

	inline Vector<T, D> operator-(const T& r)const{
		Vector<T, D> res;
		unsigned int i;
		for(i=0;i<D;++i)res[i]=values[i]-r;
		return res;
	}

	inline Vector<T, D>& operator-=(const T& r)const{
		unsigned int i;
		for(i=0;i<D;++i)values[i]-=r;
		return *this;
	}

	inline Vector<T, D> operator*(const T& r)const{
		Vector<T, D> res;
		unsigned int i;
		for(i=0;i<D;++i)res[i]=values[i]*r;
		return res;
	}

	inline Vector<T, D>& operator*=(const T& r)const{
		unsigned int i;
		for(i=0;i<D;++i)values[i]*=r;
		return *this;
	}

	inline Vector<T, D> operator/(const T& r)const{
		Vector<T, D> res;
		unsigned int i;
		for(i=0;i<D;++i)res[i]=values[i]/r;
		return res;
	}

	inline Vector<T, D>& operator/=(const T& r)const{
		unsigned int i;
		for(i=0;i<D;++i)values[i]/=r;
		return *this;
	}

	T& operator [] (unsigned int i) { return values[i]; }
	T operator [] (unsigned int i)const { return values[i]; }
	
	inline uint8_t operator==(const Vector<T,D>& r)const{
		unsigned int i;
		for(i=0;i<D;++i)if(values[i] != r[i])return 0;
		return 1;
	}
	
	inline uint8_t operator!=(const Vector<T,D>& r)const{ return !operator==(r); }
private:
	T values[D];
};

template<typename T>
struct Vector2: public Vector<T, 2>{
public:
	Vector2(){}
	Vector2(const Vector<T, 2>& r){
		(*this)[0]=r[0];
		(*this)[1]=r[1];
	}
	Vector2(const Vector<T, 3>& r){
		(*this)[0]=r[0];
		(*this)[1]=r[1];
	}
	Vector2(const Vector<T, 4>& r){
		(*this)[0]=r[0];
		(*this)[1]=r[1];
	}
	Vector2(T x){
		(*this)[0]=x;
		(*this)[1]=x;
	}
	Vector2(T x, T y){
		(*this)[0]=x;
		(*this)[1]=y;
	}

	inline T getX()const{ return (*this)[0]; }
	inline T getY()const{ return (*this)[1]; }

	inline void setX(const T& x){ (*this)[0] = x; }
	inline void setY(const T& y){ (*this)[1] = y; }

	inline void set(const T& x, const T& y){ setX(x); setY(y); }
};

template<typename T>
struct Vector3: public Vector<T, 3>{
	Vector3(){}
	Vector3(const Vector<T, 2>& r, T z=0){
		(*this)[0]=r[0];
		(*this)[1]=r[1];
		(*this)[2]=z;
	}
	Vector3(const Vector<T, 3>& r){
		(*this)[0]=r[0];
		(*this)[1]=r[1];
		(*this)[2]=r[2];
	}
	Vector3(const Vector<T, 4>& r){
		(*this)[0]=r[0];
		(*this)[1]=r[1];
		(*this)[2]=r[2];
	}
	Vector3(T x){
		(*this)[0]=x;
		(*this)[1]=x;
		(*this)[2]=x;
	}
	Vector3(T x, T y, T z){
		(*this)[0]=x;
		(*this)[1]=y;
		(*this)[2]=z;
	}
	inline Vector3<T> cross(const Vector3<T>& r)const{
		T x = (*this)[1] * r[2] - (*this)[2] * r[1];
		T y = (*this)[2] * r[0] - (*this)[0] * r[2];
		T z = (*this)[0] * r[1] - (*this)[1] * r[0];

		return Vector3<T>(x, y, z);
	}

	inline Vector3<T> rotate(T angle, const Vector3<T>& axis)const{	
		const T sinAngle = sin(-angle);
		const T cosAngle = cos(-angle);
		
		return this->cross(axis * sinAngle) +        //Rotation on local X
			(*this * cosAngle) +                     //Rotation on local Z
		    axis * this->Dot(axis * (1 - cosAngle)); //Rotation on local Y
	}

	inline Vector2<T> getXY()const{ return Vector2<T>(getX(), getY()); }
	inline Vector2<T> getYZ()const{ return Vector2<T>(getY(), getZ()); }
	inline Vector2<T> getZX()const{ return Vector2<T>(getZ(), getX()); }
	
	inline Vector2<T> getYX()const{ return Vector2<T>(getY(), getX()); }
	inline Vector2<T> getZY()const{ return Vector2<T>(getZ(), getY()); }
	inline Vector2<T> getXZ()const{ return Vector2<T>(getX(), getZ()); }
	
	inline T getX()const{ return (*this)[0]; }
	inline T getY()const{ return (*this)[1]; }
	inline T getZ()const{ return (*this)[2]; }
	
	inline void setX(const T& x){ (*this)[0] = x; }
	inline void setY(const T& y){ (*this)[1] = y; }
	inline void setZ(const T& z){ (*this)[2] = z; }
	
	inline void set(const T& x, const T& y, const T& z){ setX(x); setY(y); setZ(z); }
};

template<typename T>
struct Vector4: public Vector<T, 4>{
public:
	Vector4(){}
	Vector4(const Vector<T, 4>& r){
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
		(*this)[3] = r[3];
	}

	Vector4(T x){
		(*this)[0] = x;
		(*this)[1] = x;
		(*this)[2] = x;
		(*this)[3] = x;
	}

	Vector4(const Vector2<T>& r, T z, T w){
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = z;
		(*this)[3] = w;
	}
	Vector4(const Vector3<T>& r, T w){
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
		(*this)[3] = w;
	}
	Vector4(T x, T y, T z, T w){
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = w;
	}
	
	inline T getX()const{ return (*this)[0]; }
	inline T getY()const{ return (*this)[1]; }
	inline T getZ()const{ return (*this)[2]; }
	inline T getW()const{ return (*this)[3]; }
	
	inline void setX(const T& x){(*this)[0] = x; }
	inline void setY(const T& y){(*this)[1] = y; }
	inline void setZ(const T& z){(*this)[2] = z; }
	inline void setW(const T& w){(*this)[3] = w; }
	
	inline void set(const T& x, const T& y, const T& z, const T& w){ setX(x); setY(y); setZ(z); setW(w); }
protected:
private:
};

template<typename T, unsigned int D>
struct Matrix{
	inline Matrix<T, D> initIdentity(){
		unsigned int i,j;
		for(i=0;i<D;++i)
			for(j=0;j<D;++j)
				m[i][j]=(i==j)?T(1):T(0);
		return *this;
	}
	inline Matrix<T, D> initScale(const Vector<T, D-1>& r){
		unsigned int i,j;

		for(i=0;i<D;++i)
			for(j=0;j<D;++j)
				m[i][j]=(i==j && i!=D-1)?r[i]:T(0);

		m[D-1][D-1]=1;
		return *this;
	}
	inline Matrix<T, D> initTranslation(const Vector<T, D-1>& r){
		unsigned int i,j;

		for(i=0;i<D;++i)
			for(j=0;j<D;++j)
				m[i][j]=(i==D-1&&j!=D-1)?r[j]:(i==j)?T(1):T(0);

		m[D-1][D-1]=1;
		return *this;
	}
	inline Matrix<T, D> transpose()const{
		unsigned int i,j;
		Matrix<T, D> t;
		for(i=0;i<D;++i)
			for(j=0;j<D;++j)
				t[i][j]=m[j][i];
		return t;
	}
	inline Matrix<T,D> operator*(const Matrix<T,D>& r)const{
		unsigned int i,j,k;
		Matrix<T,D> ret;
		for(i=0;i<D;i++){
			for(j=0;j<D;j++){
				ret[i][j] = T(0);
				for(k=0;k<D;k++)
					ret[i][j] += m[k][j] * r[i][k];
			}
		}
		return ret;
	}
	inline Vector<T,D> transform(const Vector<T,D>& r)const{
		unsigned int i,j;
		Vector<T,D> ret;
		for(i=0;i<D;i++){
			ret[i] = 0;
			for(j=0;j<D;j++)
				ret[i] += m[j][i] * r[j];
		}
		return ret;
	}
	
	inline Vector<T,D-1> transform(const Vector<T,D-1>& r) const{
		unsigned int i;
		Vector<T,D> r2;

		for(i=0;i< D-1;i++)r2[i] = r[i];

		r2[D-1] = T(1);

		Vector<T,D> ret2 = transform(r2);
		Vector<T,D-1> ret;
		
		for(i=0;i<D-1;i++)ret[i] = ret2[i];
			
		return ret;
	}
	inline Vector<T,D> operator*(const Vector<T,D>& r)const{return transform(r);}
	inline Vector<T,D-1> operator*(const Vector<T,D-1>& r)const{return transform(r);}

	inline void set(unsigned int x, unsigned int y, T val){m[x][y]=val;}
	inline const T* operator[](int index)const{ return m[index]; }
	inline T* operator[](int index){ return m[index]; }
protected:
	T m[D][D];
private:
};

template<typename T>
struct Matrix4: public Matrix<T, 4>{
public:
	Matrix4(){}

	template<unsigned int D>
	Matrix4(const Matrix<T,D>& r){
		unsigned int i,j;
		if(D<4){
			this->initIdentity();
			for(i=0;i<D;++i)
				for(j=0;j<D;++j)
					(*this)[i][j]=r[i][j];
		}else{
			for(i=0;i<4;++i)
				for(j=0;j<4;++j)
					(*this)[i][j]=r[i][j];
		}
	}
	inline Matrix4<T> initRotationEuler(T rotateX, T rotateY, T rotateZ){
		Matrix4<T> rx, ry, rz;

		const T x = rotateX;
		const T y = rotateY;
		const T z = rotateZ;

		rx[0][0] = T(1);   rx[1][0] = T(0)  ;  rx[2][0] = T(0)   ; rx[3][0] = T(0);
		rx[0][1] = T(0);   rx[1][1] = cos(x);  rx[2][1] = -sin(x); rx[3][1] = T(0);
		rx[0][2] = T(0);   rx[1][2] = sin(x);  rx[2][2] = cos(x) ; rx[3][2] = T(0);
		rx[0][3] = T(0);   rx[1][3] = T(0)  ;  rx[2][3] = T(0)   ; rx[3][3] = T(1);
		
		ry[0][0] = cos(y); ry[1][0] = T(0);    ry[2][0] = -sin(y); ry[3][0] = T(0);
		ry[0][1] = T(0)  ; ry[1][1] = T(1);    ry[2][1] = T(0)   ; ry[3][1] = T(0);
		ry[0][2] = sin(y); ry[1][2] = T(0);    ry[2][2] = cos(y) ; ry[3][2] = T(0);
		ry[0][3] = T(0)  ; ry[1][3] = T(0);    ry[2][3] = T(0)   ; ry[3][3] = T(1);
		
		rz[0][0] = cos(z); rz[1][0] = -sin(z); rz[2][0] = T(0);    rz[3][0] = T(0);
		rz[0][1] = sin(z); rz[1][1] = cos(z) ; rz[2][1] = T(0);    rz[3][1] = T(0);
		rz[0][2] = T(0)  ; rz[1][2] = T(0)   ; rz[2][2] = T(1);    rz[3][2] = T(0);
		rz[0][3] = T(0)  ; rz[1][3] = T(0)   ; rz[2][3] = T(0);    rz[3][3] = T(1);

		*this = rz * ry * rx;
		
		return *this;
	}
	inline Matrix4<T> initRotationFromVectors(const Vector3<T>& n, const Vector3<T>& v, const Vector3<T>& u){
		(*this)[0][0] = u.getX();   (*this)[1][0] = u.getY();   (*this)[2][0] = u.getZ();   (*this)[3][0] = T(0);
		(*this)[0][1] = v.getX();   (*this)[1][1] = v.getY();   (*this)[2][1] = v.getZ();   (*this)[3][1] = T(0);
		(*this)[0][2] = n.getX();   (*this)[1][2] = n.getY();   (*this)[2][2] = n.getZ();   (*this)[3][2] = T(0);
		(*this)[0][3] = T(0);       (*this)[1][3] = T(0);       (*this)[2][3] = T(0);       (*this)[3][3] = T(1);  
		
		return *this;
	}
	inline Matrix4<T> initRotationFromDirection(const Vector3<T>& forward, const Vector3<T>& up){
		Vector3<T> n = (Vector3<T>(forward)).normalized();
		Vector3<T> u = Vector3<T>(Vector3<T>(up).normalized()).cross(n);
		Vector3<T> v = n.cross(u);
		
		return initRotationFromVectors(n,v,u);
	}
	inline Matrix4<T> initPerspective(T fov, T aspectRatio, T zNear, T zFar){
		const T zRange     = zNear - zFar;
		const T tanHalfFOV = tanf(fov / T(2));

		(*this)[0][0] = T(1)/(tanHalfFOV * aspectRatio); (*this)[1][0] = T(0); (*this)[2][0] = T(0); (*this)[3][0] = T(0);
		(*this)[0][1] = T(0);	(*this)[1][1] = T(1)/tanHalfFOV; (*this)[2][1] = T(0); (*this)[3][1] = T(0);
		(*this)[0][2] = T(0);	(*this)[1][2] = T(0);	(*this)[2][2] = -(-zNear - zFar)/zRange ; (*this)[3][2] = T(2)*zFar*zNear/zRange;
		(*this)[0][3] = T(0);	(*this)[1][3] = T(0); (*this)[2][3] = T(-1); (*this)[3][3] = T(0); 
		
		return *this;
	}
	inline Matrix4<T> initOrthographic(T left, T right, T bottom, T top, T near, T far){
		const T width = (right - left);
		const T height = (top - bottom);
		const T depth = (far - near);

		(*this)[0][0] = T(2)/width; (*this)[1][0] = T(0);        (*this)[2][0] = T(0);        (*this)[3][0] = -(right + left)/width;
		(*this)[0][1] = T(0);       (*this)[1][1] = T(2)/height; (*this)[2][1] = T(0);        (*this)[3][1] = -(top + bottom)/height;
		(*this)[0][2] = T(0);       (*this)[1][2] = T(0);        (*this)[2][2] = T(-2)/depth; (*this)[3][2] = -(far + near)/depth;
		(*this)[0][3] = T(0);       (*this)[1][3] = T(0);        (*this)[2][3] = T(0);        (*this)[3][3] = T(1); 
		
		return *this;
	}

	inline Matrix4<T>lookAt(Vector3<T> const & eye, Vector3<T> const & center,Vector3<T> const & up){
		uint32_t i,j;
		Vector3<T> f((center - eye).normalized());

		Vector3<T> s(f.cross(up).normalized());

		Vector3<T> u(s.cross(f));


		for(i=0;i<3;++i)(*this)[i][3]=T(0);
		(*this)[3][3]=T(1);

		(*this)[0][0] = s.getX();
		(*this)[1][0] = s.getY();
		(*this)[2][0] = s.getZ();
		(*this)[0][1] = u.getX();
		(*this)[1][1] = u.getY();
		(*this)[2][1] = u.getZ();
		(*this)[0][2] =-f.getX();
		(*this)[1][2] =-f.getY();
		(*this)[2][2] =-f.getZ();
		(*this)[3][0] =-s.dot(eye);
		(*this)[3][1] =-u.dot(eye);
		(*this)[3][2] = f.dot(eye);
		return (*this);
	}
	/*Matrix4<T> invert(){
		Matrix4<T> inv;

    inv[0][0] = (*this)[1][1]  * (*this)[2][2] * (*this)[3][3] - 
             (*this)[1][1]  * (*this)[3][2] * (*this)[2][3] - 
             (*this)[1][2]  * (*this)[2][1]  * (*this)[3][3] + 
             (*this)[1][2]  * (*this)[3][1]  * (*this)[2][3] +
             (*this)[1][3] * (*this)[2][1]  * (*this)[3][2] - 
             (*this)[1][3] * (*this)[3][1]  * (*this)[2][2];

    inv[0][1] = -(*this)[0][1]  * (*this)[2][2] * (*this)[3][3] + 
              (*this)[0][1]  * (*this)[3][2] * (*this)[2][3] + 
              (*this)[0][2]  * (*this)[2][1]  * (*this)[3][3] - 
              (*this)[0][2]  * (*this)[3][1]  * (*this)[2][3] - 
              (*this)[0][3] * (*this)[2][1]  * (*this)[3][2] + 
              (*this)[0][3] * (*this)[3][1]  * (*this)[2][2];

    inv[0][2] = (*this)[0][1]  * (*this)[1][2] * (*this)[3][3] - 
             (*this)[0][1]  * (*this)[3][2] * (*this)[1][3] - 
             (*this)[0][2]  * (*this)[1][1] * (*this)[3][3] + 
             (*this)[0][2]  * (*this)[3][1] * (*this)[1][3] + 
             (*this)[0][3] * (*this)[1][1] * (*this)[3][2] - 
             (*this)[0][3] * (*this)[3][1] * (*this)[1][2];

    inv[0][3] = -(*this)[0][1]  * (*this)[1][2] * (*this)[2][3] + 
               (*this)[0][1]  * (*this)[2][2] * (*this)[1][3] +
               (*this)[0][2]  * (*this)[1][1] * (*this)[2][3] - 
               (*this)[0][2]  * (*this)[2][1] * (*this)[1][3] - 
               (*this)[0][3] * (*this)[1][1] * (*this)[2][2] + 
               (*this)[0][3] * (*this)[2][1] * (*this)[1][2];

    inv[1][0] = -(*this)[1][0]  * (*this)[2][2] * (*this)[3][3] + 
              (*this)[1][0]  * (*this)[3][2] * (*this)[2][3] + 
              (*this)[1][2]  * (*this)[2][0] * (*this)[3][3] - 
              (*this)[1][2]  * (*this)[3][0] * (*this)[2][3] - 
              (*this)[1][3] * (*this)[2][0] * (*this)[3][2] + 
              (*this)[1][3] * (*this)[3][0] * (*this)[2][2];

    inv[1][1] = (*this)[0][0]  * (*this)[2][2] * (*this)[3][3] - 
             (*this)[0][0]  * (*this)[3][2] * (*this)[2][3] - 
             (*this)[0][2]  * (*this)[2][0] * (*this)[3][3] + 
             (*this)[0][2]  * (*this)[3][0] * (*this)[2][3] + 
             (*this)[0][3] * (*this)[2][0] * (*this)[3][2] - 
             (*this)[0][3] * (*this)[3][0] * (*this)[2][2];

    inv[1][2] = -(*this)[0][0]  * (*this)[1][2] * (*this)[3][3] + 
              (*this)[0][0]  * (*this)[3][2] * (*this)[1][3] + 
              (*this)[0][2]  * (*this)[1][0] * (*this)[3][3] - 
              (*this)[0][2]  * (*this)[3][0] * (*this)[1][3] - 
              (*this)[0][3] * (*this)[1][0] * (*this)[3][2] + 
              (*this)[0][3] * (*this)[3][0] * (*this)[1][2];

    inv[1][3] = (*this)[0][0]  * (*this)[1][2] * (*this)[2][3] - 
              (*this)[0][0]  * (*this)[2][2] * (*this)[1][3] - 
              (*this)[0][2]  * (*this)[1][0] * (*this)[2][3] + 
              (*this)[0][2]  * (*this)[2][0] * (*this)[1][3] + 
              (*this)[0][3] * (*this)[1][0] * (*this)[2][2] - 
              (*this)[0][3] * (*this)[2][0] * (*this)[1][2];

    inv[2][0] = (*this)[1][0]  * (*this)[2][1] * (*this)[3][3] - 
             (*this)[1][0]  * (*this)[3][1] * (*this)[2][3] - 
             (*this)[1][1]  * (*this)[2][0] * (*this)[3][3] + 
             (*this)[1][1]  * (*this)[3][0] * (*this)[2][3] + 
             (*this)[1][3] * (*this)[2][0] * (*this)[3][1] - 
             (*this)[1][3] * (*this)[3][0] * (*this)[2][1];

    inv[2][1] = -(*this)[0][0]  * (*this)[2][1] * (*this)[3][3] + 
              (*this)[0][0]  * (*this)[3][1] * (*this)[2][3] + 
              (*this)[0][1]  * (*this)[2][0] * (*this)[3][3] - 
              (*this)[0][1]  * (*this)[3][0] * (*this)[2][3] - 
              (*this)[0][3] * (*this)[2][0] * (*this)[3][1] + 
              (*this)[0][3] * (*this)[3][0] * (*this)[2][1];

    inv[2][2] = (*this)[0][0]  * (*this)[1][1] * (*this)[3][3] - 
              (*this)[0][0]  * (*this)[3][1] * (*this)[1][3] - 
              (*this)[0][1]  * (*this)[1][0] * (*this)[3][3] + 
              (*this)[0][1]  * (*this)[3][0] * (*this)[1][3] + 
              (*this)[0][3] * (*this)[1][0] * (*this)[3][1] - 
              (*this)[0][3] * (*this)[3][0] * (*this)[1][1];

    inv[2][3] = -(*this)[0][0]  * (*this)[1][1] * (*this)[2][3] + 
               (*this)[0][0]  * (*this)[2][1] * (*this)[1][3] + 
               (*this)[0][1]  * (*this)[1][0] * (*this)[2][3] - 
               (*this)[0][1]  * (*this)[2][0] * (*this)[1][3] - 
               (*this)[0][3] * (*this)[1][0] * (*this)[2][1] + 
               (*this)[0][3] * (*this)[2][0] * (*this)[1][1];

    inv[3][0] = -(*this)[1][0] * (*this)[2][1] * (*this)[3][2] + 
              (*this)[1][0] * (*this)[3][1] * (*this)[2][2] + 
              (*this)[1][1] * (*this)[2][0] * (*this)[3][2] - 
              (*this)[1][1] * (*this)[3][0] * (*this)[2][2] - 
              (*this)[1][2] * (*this)[2][0] * (*this)[3][1] + 
              (*this)[1][2] * (*this)[3][0] * (*this)[2][1];

    inv[3][1] = (*this)[0][0] * (*this)[2][1] * (*this)[3][2] - 
             (*this)[0][0] * (*this)[3][1] * (*this)[2][2] - 
             (*this)[0][1] * (*this)[2][0] * (*this)[3][2] + 
             (*this)[0][1] * (*this)[3][0] * (*this)[2][2] + 
             (*this)[0][2] * (*this)[2][0] * (*this)[3][1] - 
             (*this)[0][2] * (*this)[3][0] * (*this)[2][1];

    inv[3][2] = -(*this)[0][0] * (*this)[1][1] * (*this)[3][2] + 
               (*this)[0][0] * (*this)[3][1] * (*this)[1][2] + 
               (*this)[0][1] * (*this)[1][0] * (*this)[3][2] - 
               (*this)[0][1] * (*this)[3][0] * (*this)[1][2] - 
               (*this)[0][2] * (*this)[1][0] * (*this)[3][1] + 
               (*this)[0][2] * (*this)[3][0] * (*this)[1][1];

    inv[3][3] = (*this)[0][0] * (*this)[1][1] * (*this)[2][2] - 
              (*this)[0][0] * (*this)[2][1] * (*this)[1][2] - 
              (*this)[0][1] * (*this)[1][0] * (*this)[2][2] + 
              (*this)[0][1] * (*this)[2][0] * (*this)[1][2] + 
              (*this)[0][2] * (*this)[1][0] * (*this)[2][1] - 
              (*this)[0][2] * (*this)[2][0] * (*this)[1][1];
	return inv;
}*/
protected:
private:
};

template<typename T>
struct Matrix3: public Matrix<T, 3>{
public:
	Matrix3(){}

	template<unsigned int D>
	Matrix3(const Matrix<T,D>& r){
		unsigned int i,j;
		if(D<3){
			this->initIdentity();
			for(i=0;i<D;++i)
				for(j=0;j<D;++j)
					(*this)[i][j]=r[i][j];
		}else{
			for(i=0;i<3;++i)
				for(j=0;j<3;++j)
					(*this)[i][j]=r[i][j];
		}
	}
protected:
private:
};

struct Quaternion;

struct Vector3f: public Vector3<float>{
public:
	Vector3f(){}
	Vector3f(float x){
		(*this)[0] = x;
		(*this)[1] = x;
		(*this)[2] = x;
	}
	Vector3f(float x, float y, float z){
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}
	Vector3f(const Vector<float,2>& r, float z=0){
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = z;
	}
	Vector3f(const Vector<float,3>& r){
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
	}
	Vector3f(const Vector<float,4>& r){
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
	}

	inline float length() const { return sqrtf(getX() * getX() + getY() * getY() + getZ() * getZ()); }
	inline float dot(const Vector3f& v) const { return getX() * v.getX() + getY() * v.getY() + getZ() * v.getZ(); }

	inline Vector3f cross(const Vector3f& v) const
	{
		const float _x = getY() * v.getZ() - getZ() * v.getY();
		const float _y = getZ() * v.getX() - getX() * v.getZ();
		const float _z = getX() * v.getY() - getY() * v.getX();

		return Vector3f(_x, _y, _z);
	}

	inline Vector3f rotate(float angle, const Vector3f& axis) const
	{
		const float sin = sinf(-angle);
		const float cos = cosf(-angle);

		return this->cross(axis * sin) +        //Rotation on local X
			(*this * cos) +                     //Rotation on local Z
		    axis * this->dot(axis * (1 - cos)); //Rotation on local Y

	}

	Vector3f rotate(const Quaternion& rotation) const;

	inline Vector3f normalized()const{
		const float length = this->length();

		return Vector3f(getX() / length, getY() / length, getZ() / length);
	}
	inline Vector3f operator+(const Vector3f& r)const{ return Vector3f(getX() + r.getX(), getY() + r.getY(), getZ() + r.getZ()); }
	inline Vector3f operator-(const Vector3f& r)const{ return Vector3f(getX() - r.getX(), getY() - r.getY(), getZ() - r.getZ()); }
	inline Vector3f operator*(float f)const{ return Vector3f(getX() * f, getY() * f, getZ() * f); }
	inline Vector3f operator/(float f)const{ return Vector3f(getX() / f, getY() / f, getZ() / f); }

	inline bool operator==(const Vector3f& r)const{ return getX() == r.getX() && getY() == r.getY() && getZ() == r.getZ(); }
	inline bool operator!=(const Vector3f& r)const{ return !operator==(r); }

	inline Vector3f& operator+=(const Vector3f& r){
		(*this)[0] += r.getX();
		(*this)[1] += r.getY();
		(*this)[2] += r.getZ();

		return *this;
	}
	inline Vector3f& operator-=(const Vector3f& r){
		(*this)[0] -= r.getX();
		(*this)[1] -= r.getY();
		(*this)[2] -= r.getZ();

		return *this;
	}
		inline Vector3f& operator*=(float f){
		(*this)[0] *= f;
		(*this)[1] *= f;
		(*this)[2] *= f;

		return *this;
	}
	inline Vector3f& operator/=(float f){
		(*this)[0] /= f;
		(*this)[1] /= f;
		(*this)[2] /= f;

		return *this;
	}

	inline float getX()const{ return (*this)[0]; }
	inline float getY()const{ return (*this)[1]; }
	inline float getZ()const{ return (*this)[2]; }

	inline void setX(float x){ (*this)[0] = x; }
	inline void setY(float y){ (*this)[1] = y; }
	inline void setZ(float z){ (*this)[2] = z; }

	inline void set(float x, float y, float z){ (*this)[0] = x; (*this)[1] = y; (*this)[2] = z; }
protected:
private:
};

typedef Vector2<int> Vector2i;
typedef Vector3<int> Vector3i;
typedef Vector4<int> Vector4i;

typedef Vector2<float> Vector2f;
//typedef Vector3<float> Vector3f;
typedef Vector4<float> Vector4f;

typedef Vector2<double> Vector2d;
typedef Vector3<double> Vector3d;
typedef Vector4<double> Vector4d;

typedef Matrix<int, 2> Matrix2i;
typedef Matrix3<int> Matrix3i;
typedef Matrix4<int> Matrix4i;

typedef Matrix<float, 2> Matrix2f;
typedef Matrix3<float> Matrix3f;
typedef Matrix4<float> Matrix4f;

typedef Matrix<double, 2> Matrix2d;
typedef Matrix3<double> Matrix3d;
typedef Matrix4<double> Matrix4d;

struct Quaternion : public Vector4<float>{
public:
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f){
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
		(*this)[3] = w;
	}
	
	Quaternion(const Vector<float,4>& r){
		(*this)[0] = r[0];
		(*this)[1] = r[1];
		(*this)[2] = r[2];
		(*this)[3] = r[3];
	}
	
	Quaternion(const Vector3f& axis, float angle){
		float sinHalfAngle = sinf(angle/2);
		float cosHalfAngle = cosf(angle/2);
		
		(*this)[0] = axis.getX() * sinHalfAngle;
		(*this)[1] = axis.getY() * sinHalfAngle;
		(*this)[2] = axis.getZ() * sinHalfAngle;
		(*this)[3] = cosHalfAngle;
	}
	
	Quaternion(const Matrix4f& m){
		float trace = m[0][0] + m[1][1] + m[2][2];
		
		if(trace > 0){
			float s = 0.5f / sqrtf(trace + 1.0f);
			(*this)[0] = 0.25f / s;
			(*this)[1] = (m[1][2] - m[2][1]) * s;
			(*this)[2] = (m[2][0] - m[0][2]) * s;
			(*this)[3] = (m[0][1] - m[1][0]) * s;
		}
		else if(m[0][0] > m[1][1] && m[0][0] > m[2][2]){
			float s = 2.0f * sqrtf(1.0f + m[0][0] - m[1][1] - m[2][2]);
			(*this)[0] = (m[1][2] - m[2][1]) / s;
			(*this)[1] = 0.25f * s;
			(*this)[2] = (m[1][0] + m[0][1]) / s;
			(*this)[3] = (m[2][0] + m[0][2]) / s;
		}
		else if(m[1][1] > m[2][2]){
			float s = 2.0f * sqrtf(1.0f + m[1][1] - m[0][0] - m[2][2]);
			(*this)[0] = (m[2][0] - m[0][2]) / s;
			(*this)[1] = (m[1][0] + m[0][1]) / s;
			(*this)[2] = 0.25f * s;
			(*this)[3] = (m[2][1] + m[1][2]) / s;
		}
		else{
			float s = 2.0f * sqrtf(1.0f + m[2][2] - m[1][1] - m[0][0]);
			(*this)[0] = (m[0][1] - m[1][0]) / s;
			(*this)[1] = (m[2][0] + m[0][2]) / s;
			(*this)[2] = (m[1][2] + m[2][1]) / s;
			(*this)[3] = 0.25f * s;
		}
		
		float length = this->length();
		(*this)[3] = (*this)[3] / length;
		(*this)[0] = (*this)[0] / length;
		(*this)[1] = (*this)[1] / length;
		(*this)[2] = (*this)[2] / length;
	}

	Quaternion(const Vector3f& euler){
		setX(cos(euler.getX()/2)*cos(euler.getY()/2)*cos(euler.getZ()/2)+sin(euler.getX()/2)*sin(euler.getY()/2)*sin(euler.getZ()/2));
		setY(sin(euler.getX()/2)*cos(euler.getY()/2)*cos(euler.getZ()/2)-cos(euler.getX()/2)*sin(euler.getY()/2)*sin(euler.getZ()/2));
		setZ(cos(euler.getX()/2)*sin(euler.getY()/2)*cos(euler.getZ()/2)+sin(euler.getX()/2)*cos(euler.getY()/2)*sin(euler.getZ()/2));
		setW(cos(euler.getX()/2)*cos(euler.getY()/2)*sin(euler.getZ()/2)-sin(euler.getX()/2)*sin(euler.getY()/2)*cos(euler.getZ()/2));

		float length = this->length();
		(*this)[3] = (*this)[3] / length;
		(*this)[0] = (*this)[0] / length;
		(*this)[1] = (*this)[1] / length;
		(*this)[2] = (*this)[2] / length;
	}

	inline Quaternion NLerp(const Quaternion& r, float lerpFactor, bool shortestPath) const{
		Quaternion correctedDest;
		
		if(shortestPath && this->dot(r) < 0)
			correctedDest = r * -1;
		else
			correctedDest = r;
	
		return Quaternion(lerp(correctedDest, lerpFactor).normalized());
	}
	
	inline Quaternion SLerp(const Quaternion& r, float lerpFactor, bool shortestPath) const{
		static const float EPSILON = 1e3;
	
		float cos = this->dot(r);
		Quaternion correctedDest;
		
		if(shortestPath && cos < 0){
			cos *= -1;
			correctedDest = r * -1;
		}
		else
			correctedDest = r;
			
		if(fabs(cos) > (1 - EPSILON))
			return NLerp(correctedDest, lerpFactor, false);
		
		float sin = (float)sqrtf(1.0f - cos * cos);
		float angle = atan2(sin, cos);
		float invSin = 1.0f/sin;
		
		float srcFactor = sinf((1.0f - lerpFactor) * angle) * invSin;
		float destFactor = sinf((lerpFactor) * angle) * invSin;
		
		return Quaternion((*this) * srcFactor + correctedDest * destFactor);
	}
	
	inline Matrix4f toRotMatrix()const{
	
		//printf("%g %g %g %g\n", getX(), getY(), getZ(), getW());

		Vector3f forward = Vector3f(-2.0f * (getX() * getZ() - getW() * getY()), 2.0f * (getY() * getX() + getW() * getZ()), 1.0f - 2.0f * (getY() * getY() + getZ() * getZ()));
		Vector3f up = Vector3f(2.0f * (getZ()*getY() + getW()*getX()), -1.0f + 2.0f * (getX()*getX() + getZ()*getZ()), -2.0f * (getX()*getY() - getW()*getZ()));
		Vector3f right = Vector3f(-1.0f + 2.0f * (getX()*getX() + getY()*getY()), 2.0f * (getY()*getZ() - getW()*getX()), 2.0f * (getX()*getZ() + getW()*getY()));
	
		return Matrix4f().initRotationFromVectors(forward,up,right);

		/*Vector3f euler = getEuler();
		printf("euler: %g %g %g\n\n", euler.getX(), euler.getY(), euler.getZ());
		return Matrix4f().initRotationEuler(euler.getX(), euler.getY(), euler.getZ());*/
	}

	inline Vector3f getEuler()const{
		float a = 2*(getX()*getY()+getZ()*getW());
		float b = 1-2*(getY()*getY()+getZ()*getZ());
		float c = 2*(getX()*getZ()-getY()*getW());
		if(c>1)c=1;
		float d = 2*(getX()*getW()+getY()*getZ());
		float e = 1-2*(getZ()*getZ()+getW()*getW());
		return Vector3f(atan2(a,b), asin(c), atan2(d,e));
	}

	inline Vector3f getForward()const{ 
		return Vector3f(0,0,1).rotate(*this); 
	}
	
	inline Vector3f getBack()const{ 
		return Vector3f(0,0,-1).rotate(*this); 
	}
	
	inline Vector3f getUp()const{ 
		return Vector3f(0,1,0).rotate(*this); 
	}
	
	inline Vector3f getDown()const{ 
		return Vector3f(0,-1,0).rotate(*this); 
	}
	
	inline Vector3f getRight()const{ 
		return Vector3f(1,0,0).rotate(*this); 
	}
	
	inline Vector3f getLeft()const{ 
		return Vector3f(-1,0,0).rotate(*this);  
	}

	inline Quaternion conjugate()const{ return Quaternion(-getX(), -getY(), -getZ(), getW()); }

	inline Quaternion operator*(const float r)const{
		return Quaternion(getX()*r, getY()*r, getZ()*r, getW()*r);
	}
	inline Quaternion operator*(const Quaternion& r)const{
		const float _x = (getX() * r.getX()) - (getY() * r.getY()) - (getZ() * r.getZ()) - (getW() * r.getW());
		const float _y = (getX() * r.getY()) + (getY() * r.getX()) - (getZ() * r.getW()) + (getW() * r.getZ());
		const float _z = (getX() * r.getZ()) + (getY() * r.getW()) + (getZ() * r.getX()) - (getW() * r.getY());
		const float _w = (getX() * r.getW()) - (getY() * r.getZ()) + (getZ() * r.getY()) + (getW() * r.getX());

		/*const float _w = (getW() * r.getW()) - (getX() * r.getX()) - (getY() * r.getY()) - (getZ() * r.getZ());
		const float _x = (getX() * r.getW()) + (getW() * r.getX()) + (getY() * r.getZ()) - (getZ() * r.getY());
		const float _y = (getY() * r.getW()) + (getW() * r.getY()) + (getZ() * r.getX()) - (getX() * r.getZ());
		const float _z = (getZ() * r.getW()) + (getW() * r.getZ()) + (getX() * r.getY()) - (getY() * r.getX());
*/
		return Quaternion(_x, _y, _z, _w);
	}
	inline Quaternion operator*(const Vector3<float>& v)const{
		const float _w = - (getX() * v.getX()) - (getY() * v.getY()) - (getZ() * v.getZ());
		const float _x =   (getW() * v.getX()) + (getY() * v.getZ()) - (getZ() * v.getY());
		const float _y =   (getW() * v.getY()) + (getZ() * v.getX()) - (getX() * v.getZ());
		const float _z =   (getW() * v.getZ()) + (getX() * v.getY()) - (getY() * v.getX());

		return Quaternion(_x, _y, _z, _w);
	}
};
#endif
