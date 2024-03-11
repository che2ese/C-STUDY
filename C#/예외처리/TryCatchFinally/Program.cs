using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TryCatchFinally
{
    internal class Program
    {
        static void Main(string[] args)
        {
            try
            {
                int[] array = new int[3] { 1, 2, 3, };
                for (int i = 0; i < 5; i++)
                {
                    Console.WriteLine(array[i]);
                }
            }
            catch (DivideByZeroException e) // 0으로 나눌 수 없음.
            {
                Console.WriteLine("예외 1\n");
                Console.WriteLine(e.Message);
            }
            catch (Exception e)
            {
                Console.WriteLine("예외 2\n");
                Console.WriteLine(e.Message);
            }
            finally // finally 구문 안의 코드는 예외가 발생하든 안하든 무조건 실행
            {
                Console.WriteLine("예외가 발생하였습니다.\n");
            }
            Console.ReadLine();
        }
    }
}
