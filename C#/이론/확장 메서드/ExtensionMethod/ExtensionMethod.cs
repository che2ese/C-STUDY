using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

// 확장 메서드는 전부 정적 메서드 형태, 매개변수 앞에 this 추가
namespace ExtensionMethod
{
    // static 키워드가 붙은 정적 클래스는 new 키워드로 인스턴스를 생성할 수 없음
    // 정적 클래스 내부의 변수나, 메서드가 호출될 때 인스턴스가 생성되어
    // 프로그램 종료 시까지 동작하게 되며, 전역으로 접근 가능
    // 정적 클래스 내부 요소들은 전부 정적으로 생성해야함

    // 정적 메서드는 기존 메서드와 호출 방식이 다름

    public static class ExtensionMethod
    {
        public static void Print(this string s) // string 클래스 타입에 Print라는 확장 메서드를 추가
        {                                       // 따라서 string a 라는 변수가 있으면 a.Print()로 호출 가능
            Console.WriteLine(s);
        }
        public static int Plus(this int a, int b) // int 클래스로 Plus() 확장 메서드를 사용할 수 있게 할거고 그 때 매개변수 b를 받겠다.
        {
            return a + b;
        }
        public static void Print1(this int a, int b)
        {
            int result = a + b;
            Console.WriteLine(result);
        }
    }
}
