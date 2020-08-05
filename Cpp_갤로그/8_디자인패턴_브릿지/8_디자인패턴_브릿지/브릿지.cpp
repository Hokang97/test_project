// 브릿지패턴이란?
// 추상화 부분과 구현 부분을 분리하는 패턴
// 기능들과 구현을 별도로 정의해 분리하는 방법으로 두 클래스를 서로 다른 계층구조에 넣어
// 변경 가능하게 만드는 디자인 패턴

#include <iostream>
#include <iomanip>
#pragma warning(disable:4996)
using namespace std;

__interface GetAreaMethod
{
public:

	virtual const char* GetInfo() = 0;
	virtual double GetArea(int, int) = 0;
};

class GetAreaTriangleMethod : public GetAreaMethod
{
public:

	virtual const char* GetInfo()							{ return "이 도형은 삼각형입니다."; }
	virtual double GetArea(int width, int height) { return static_cast<double>(width) * height / 2; }
};

class GetAreaRectangleMethod : public GetAreaMethod
{
public:

	virtual const char* GetInfo() { return "이 도형은 사각형입니다."; }
	virtual double GetArea(int width, int height) { return static_cast<double>(width)* height; }
};

class Shape
{
protected:
	GetAreaMethod* m_pMethod = nullptr;

protected:
	int width;
	int height;

public:
	
	~Shape() { if (m_pMethod != nullptr) delete m_pMethod; }

	double GetArea() { return m_pMethod->GetArea(width,height); }
	const char* GetInfo() { return m_pMethod->GetInfo(); }

	void SetWidth(int value) { width = value; }
	void SetHeight(int value) { height = value; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
};

class Triangle : public Shape
{
public:
	Triangle(GetAreaMethod* pMethod) { m_pMethod = pMethod; }
};

class Rectangle : public Shape
{
public:
	Rectangle(GetAreaMethod* pMethod) { m_pMethod = pMethod; }
};

int main()
{
	Triangle tri(new GetAreaTriangleMethod);
	Rectangle rect(new GetAreaRectangleMethod);

	tri.SetWidth(5);
	tri.SetHeight(10);

	rect.SetWidth(5);
	rect.SetHeight(10);

	cout << "삼각형의 넓이? " << tri.GetArea() << endl;
	cout << "사각형의 넓이? " << rect.GetArea() << endl;
}