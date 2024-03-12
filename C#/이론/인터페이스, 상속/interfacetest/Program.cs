using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// 강한 결합으로 수정하기 힘듦
namespace interfacetest
{
    class Car // Car가 아니라 Train으로 바뀌면, 호출하는 클래스도 바뀌어야 한다.
    {
        public void Run()
        {
            Console.WriteLine("Run!");
        }
    }
    class Move 
    { 
        public void Run(Car car)
        {
            car.Run();
        }    
    }
}
