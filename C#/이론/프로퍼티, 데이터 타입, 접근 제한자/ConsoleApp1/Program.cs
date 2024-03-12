using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// public 클래스 내 외부의 모든 곳에서 접근
// internal 동일 프로젝트에서 public 접근
// Protected 클래스 외부 불가 / 파생 클래스에서 가능
// private 클래스의 내부에서만 접근

namespace ConsoleApp1
{
    internal class Program
    {
        static void Main(string[] args)
        {
        }
    }
    public class Print // class는 기본적으로 internal
    {
        public void PrintHello()
        {
            string text = "hello world";
            Console.WriteLine(text);
            Console.ReadLine();
        }
    }
    class Car 
    {
        // 캡슐화 원칙을 준수하기 위해
        // 필드는 private, 접근할 수 있는 프로퍼티를 public으로 설정
        // 프로퍼티를 통해 필드에 접근

        // 일반적인 필드 예
        int field = 1;          // 4 바이트 정수
        long field1 = 11;       // 8 바이트 정수
        char field2 = 'a';      // 2 바이트 유니코드 문자
        float field3 = 1.1f;    // 4 바이트 실수
        double field4 = 1.1;    // 8 바이트 실수
        string field5 = "aaaa"; // 가변 사이즈 문자열
        bool field6 = true;

        // 일반적인 프로퍼티 예

        private string name;
        public string Name
        {
            get { return name; } // 자료를 가져오기 (name 필드를 가져오기)
            set { name = value; } // 가져온 name 필드에 value 값을 담음
        }

        /* ex
        Name = 5라고 하면 value에 5가 저장되고 get을 통해 그 5를 가져옴.
         */ 

        // public 프로퍼티 / 자동 구현 프로퍼티 예 1
        public int Speed { get; set; }

        // 자동 구현 프로퍼티 예 2 ( get만 허용, 외부에서 값 설정은 불가능 )
        public int Speed1 { get; private set; }
    }
}
