using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TryCatch
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int a = 10;
            Console.WriteLine(a / 0);
        }

        /*
        static void Main(string[] args)
        {
            try 문 안에 코드를 작성하고 그 안에서 발생한 예외는 catch 문에서 처리
            try
            {
                int[] array = new int[3] { 1, 2, 3, };
                for (int i = 0; i < 5; i++)
                {
                    console.writeline(array[i]);
                }

                int a = 10;
                console.writeline(a / 0);

                int a = 10;
                string b = "aaa";
                console.writeline(a * b);
            }
            catch (dividebyzeroexception e) // 0으로 나눌 수 없음.
            {
                console.writeline("예외 1");
                console.writeline(e.Message);
                console.readline();
            }
            catch (exception e)
            {
                console.writeline("예외 2");
                console.writeline(e.Message);
                // throw new myexception();
                console.readline();
            }
        }
        */
    }
}
