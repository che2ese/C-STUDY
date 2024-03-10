using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int count = 3;

            int[] ints1 = new int[3] { 1, 2, 3 };

            List<int> intList = new List<int>();

            ints1[0] = 1;
            ints1[1] = 2;
            ints1[2] = 5;

            intList.Add(1);
            intList.Add(2);
            intList.Add(5);

            for (int i = 0; i < ints1.Length; i++)
            {   
                // else 문은 마지막 if문과 한 쌍

                /*
                if(i == 0)
                {
                    Console.WriteLine("count는 0입니다.");
                }
                if(i == 1)
                {
                    Console.WriteLine("count는 1입니다.");
                }
                else
                {
                    Console.WriteLine("count는 0이 아닙니다.");
                }
                */
                
                // 한 세트로 만들려면 else if 사용
                if (i == 0)
                {
                    Console.WriteLine("count는 0입니다.");
                }
                else if (i == 1)
                {
                    Console.WriteLine("count는 1입니다.");
                }
                else
                {
                    Console.WriteLine("count는 0이 아닙니다.");
                }
                Console.WriteLine(ints1[i]);
            }
            Console.WriteLine();

            foreach (int x in ints1)
            {
                Console.WriteLine(x);
            }
            Console.WriteLine();

            while (count != 0)
            {
                Console.WriteLine(count);
                count--;
            }
            
            // switch 문 - 특정 조건에 맞는 하나만 출력, break 꼭 사용
            count++;
            switch (count) 
            {
                case 0:
                    Console.WriteLine("count는 0입니다.");
                    break;
                case 1:
                    Console.WriteLine("count는 1입니다.");
                    break;
                case 2:
                    Console.WriteLine("count는 2입니다.");
                    break;
            }
            Console.ReadLine();
        }
    }
}

