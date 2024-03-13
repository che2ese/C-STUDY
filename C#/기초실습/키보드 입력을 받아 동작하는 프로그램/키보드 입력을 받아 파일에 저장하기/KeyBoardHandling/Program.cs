using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KeyBoardHandling
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string KeyData = "";
            Console.WriteLine("파일에 저장할 내용 입력 : ");
            KeyData = Console.ReadLine();
            Console.WriteLine("입력한 값 : {0}", KeyData);
            StreamWriter Mw1 = new StreamWriter(new FileStream("KeyBoardHandling.txt", FileMode.Create));
            Mw1.WriteLine(KeyData);
            Mw1.Close();

            StreamReader Mr1 = new StreamReader(new FileStream("KeyBoardHandling.txt", FileMode.Open));
            while (Mr1.EndOfStream == false)
            {
                Console.WriteLine(Mr1.ReadLine());
            }
            Mr1.Close();
            Console.ReadLine();
        }
    }
}
