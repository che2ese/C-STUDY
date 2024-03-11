# 확장 메서드
int 타입에는 Method가 없지만, int 타입에 메서드를 추가해 이 클래스(구조체)를 확장 가능

**static void Method(this int a)** 형태로 정의하며, int 클래스형 변수.Method() 형태로 호출
### 예시
```
public static void Print(this string s) // string 클래스 타입에 Print라는 확장 메서드를 추가
{                                       // 따라서 string a 라는 변수가 있으면 a.Print()로 호출 가능
    Console.WriteLine(s);
}
public static int Plus(this int a, int b) // int 클래스로 Plus() 확장 메서드를 사용할 수 있게 할거고 그 때 매개변수 b를 받겠다.
{
    return a + b;
}
```

# static

**static class** : 인스턴스 클래스와 다르게 new 키워드를 사용해 인스턴스를 생성할 수 없으며, 

class 내에 변수나 메서드가 호출될 때 생성되어, 프로그램 종료시까지 동작함.

전역으로 어디에서든 접근할 수 있는 전역 클래스/클래스 내부에는 static 요소만 존재.



**static method** : 인스턴스.Method() 형태로 호출하는 일반메서드와는 달리 

정적 메서드는 클래스.Method() 형태로 호출함.

### 예시

```
// 정적 메서드
string result = "hello";
result.Print();

// 기존 메서드
StaticClass.Print();

StaticClass class1 = new StaticClass();
class1.Print1();
```
