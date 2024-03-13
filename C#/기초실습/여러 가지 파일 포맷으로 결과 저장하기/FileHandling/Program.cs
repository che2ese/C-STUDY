using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileHandling
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // StreamWriter / StreamReader 클래스
            // Stream은 데이터를 쓰는 통로 역할
            Console.WriteLine("StreamWriter / StreamReader ----------------\r\n");
            Console.WriteLine("파일 쓰기");
            // 파일을 쓸 때 메모리에 있는 데이터를 바이트 단위로 하드디스크로 옮김
            // 경로를 지정하지 않으면 프로젝트 bin-debug 파일에 생김
            StreamWriter sw = new StreamWriter(new FileStream("a.txt", FileMode.Create)); // a.txt라는 제목의 파일을 생성모드로 만듦  
            sw.Write(10); // write는 줄바꿈 안됨
            sw.WriteLine("Hello!");
            sw.WriteLine(3.999);
            sw.Close(); // 통로를 열었으니 닫아줘야됨

            StreamReader sr = new StreamReader(new FileStream("a.txt", FileMode.Open));
            Console.WriteLine("파일 읽기");
            while(sr.EndOfStream == false) // 스트림 마지막이 비어있을 때까지 실행
            {
                Console.WriteLine(sr.ReadLine());
            }
            sr.Close();

            using (StreamWriter sw1 = new StreamWriter(new FileStream("b.txt", FileMode.Create)))
            {
                // using이라는 키워드를 통해 스트림을 자동으로 닫아줌
                // 그럼 굳이 close 안써도 됨
            }

            // File 클래스를 활용하여, 간단하게 파일로 출력하기 --------------------

            Console.WriteLine(Environment.NewLine + "File 클래스 사용 ----------------" + Environment.NewLine);
            // 모든 줄을 한 줄씩 쓰기
            string[] lines = { "aaaaa", "bbbbb", "ccccc" };
            File.WriteAllLines("c.txt", lines);
            // 모든 줄을 한 줄씩 읽기
            string[] lines1 = File.ReadAllLines("c.txt");
            foreach(string line in lines1)
            {
                Console.WriteLine(line);
            }

            string text = "Hello World!!";

            File.WriteAllText(@"C:\Users\김민성\OneDrive - dgu.ac.kr\바탕 화면\C-STUDY\C#\여러 가지 파일 포맷으로 결과 저장하기\FileHandling\HelloWorld.txt", text);
            Console.WriteLine(File.ReadAllText(@"C:\Users\김민성\OneDrive - dgu.ac.kr\바탕 화면\C-STUDY\C#\여러 가지 파일 포맷으로 결과 저장하기\FileHandling\HelloWorld.txt"));

            Console.ReadLine();
        }
    }
}
