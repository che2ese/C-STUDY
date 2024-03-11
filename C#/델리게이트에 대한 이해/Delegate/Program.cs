using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Delegate
{   
    // 델리게이트 (대리자) 정의
    // 이 메서드는 항상 정수형 2개 매개변수를 받게 됨.
    delegate int Dele(int a, int b);

    class Program
    {   
        static void Main(string[] args)
        {
            // 델리게이트 인스턴스 생성
            Dele plus = new Dele(Plus);
            Dele minus = new Dele(Minus);
            Dele multy = new Dele(Multy);

            // 델리게이트를 매개변수로 하는 메서드를 호출
            Calc(1, 2, Plus);
            Calc(4, 3, Minus);
            Calc(5, 6, Multy);

            Console.ReadLine();
        }

        // 델리게이트를 매개변수로 받는 메서드
        static void Calc(int a, int b, Dele dele)
        {
            Console.WriteLine(dele(a, b));
        }

        // 델리게이트로 다른 메서드에 넘겨줄 메서드
        // 델리게이트와 동일한 형태면 델리게이트로 넘겨줄 수 있음
        static int Plus(int a, int b)
        {
            return a + b;
        }
        static int Minus(int a, int b)
        {
            return a - b;
        }
        static int Multy(int a, int b)
        {
            return a * b;
        }
    }
}
