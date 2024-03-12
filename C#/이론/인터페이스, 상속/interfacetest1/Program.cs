using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Channels;
using System.Text;
using System.Threading.Tasks;

// 느슨한 결합으로 수정하기 비교적 쉬움
namespace interfacetest1
{
    class Program
    {
        static void Main(string[] args)
        {
            Move move = new Move();
            // Car와 Train은 ITrans를 상속하기 때문에 인스턴스화 가능
            ITrans trans = new Car();
            ITrans trans1 = new Train();
            move.Run(trans);
        }
    }
    interface ITrans // Interface의 약자 I를 앞에 붙여 사용
    {
        void Run();
    }
    class Car : ITrans // 상속
    {
        public void Run()
        {
            Console.WriteLine("Car Run!!");
            Console.ReadLine();
        }
    }
    class Train : ITrans
    {
        public void Run()
        {
            Console.WriteLine("Train Run!!");
            Console.ReadLine();
        }
    }
    class Move : Move1 // Move1이 부모클래스가 돼서 자식클래스에서 호출 가능
    {
        // 교통 범주를 매겨변수로 받게 함.
        // 따라서 Move 클래스는 변경 안해도 됨.
        public void Run(ITrans trans) 
        {
            trans.Run();
            Run1();
        }
    }
    class Move1
    {
        public void Run1()
        {
            Console.WriteLine("Run!!");
            Console.ReadLine();
        }
    }
}
