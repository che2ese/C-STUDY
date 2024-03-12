using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KeyBoard
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("아무 키나 눌러보세요");
            
            // 키보드 키 값 입력
            ConsoleKeyInfo key = Console.ReadKey();
            Console.WriteLine("{0}", key.Key);
            if(key.Key == ConsoleKey.Enter) 
            { 
                Console.WriteLine("엔터");
            }
            Console.ReadLine();
        }
    }
}
