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
            // 초기화
            int count = 3;

            // 배열 선언 - 크기 지정
            int[] ints1 = new int[3] { 1, 2, 3 };

            //리스트 선언
            List<int> intList = new List<int>();

            // 배열에 값 저장
            ints1[0] = 1;
            ints1[1] = 2;
            ints1[2] = 5;

            // 리스트에 값 저장
            intList.Add(1);
            intList.Add(2);
            intList.Add(5);

            // 배열의 값 반복 출력
            for (int i = 0; i < ints1.Length; i++)
            {
                Console.WriteLine(ints1[i]);
            }
            Console.WriteLine();

            // 리스트의 값 반복 출력
            // foreach 리스트 안에 남은 요소가 없을 때까지 요소를 하나씩 꺼내옴.
            foreach (int x in ints1) 
            { 
                Console.WriteLine(x);
            }
            Console.WriteLine() ;

            // while문을 통한 반복 출력
            while (count != 0)
            {
                Console.WriteLine(count);
                count--;
            }
            Console.ReadLine();
        }
    }
}
