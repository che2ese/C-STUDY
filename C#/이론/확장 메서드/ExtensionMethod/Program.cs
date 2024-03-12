using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ExtensionMethod
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // 확장 메서드는 정적 메서드이기 때문에, 인스턴스 없이 string.Print()로 바로 호출 가능
            string result = "hello";
            result.Print();

            int result1 = 3;
            int result2 = 0;
            result2 = result1.Plus(3);

            Console.WriteLine(result2);


            StaticClass.Print(); // 정적 클래스는 클래스 원형에 함수 호출

            StaticClass class1 = new StaticClass();
            class1.Print1();

            Console.ReadLine();
        }
    }
    class StaticClass
    {
        public static void Print()
        {
            Console.WriteLine("Hello!");
            Console.ReadLine();
        }
        public void Print1()
        {
            Console.WriteLine("Hello!");
            Console.ReadLine();
        }
    }
}
