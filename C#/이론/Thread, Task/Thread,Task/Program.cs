using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Thread_Task
{
    // 프로그램을 실행 시, 메인 스레드가 프로그램을 실행
    // 메인 스레드 외 다른 스레드를 사용하기 위해 Task, Thread를 사용
    // 여러 개의 스레드를 사용하는 방법을 멀티 스레딩이라고 함
    // 멀티 스레딩으로 동작을 시키면 추가된 스레드들은 비동기로 실행
    // 순차적인 실행을 보장하는 형태의 실행 형태를 동기 방식이라고 함
    // 비동기 방식은 순서 상관 없음

    internal class Program
    {
        static void Main(string[] args)
        {
            ThreadPool.QueueUserWorkItem(TestThread0);

            // 새로운 스레드 (비동기로 실행)
            Task t1 = new Task(new Action(TestThread1));
            t1.Start();
            Thread t2 = new Thread(TestThread2);
            t2.Start();
            var t3 = Task.Run(TestThread3);

            Console.WriteLine("main입니다.");

            // 호출이 완료될 때까지 대기
            t1.Wait();
            t2.Join();
            t3.Wait();

            // 스레드의 현재 상태 확인(메인 스레드에서 실행)--------------
            Console.WriteLine("--- 스레드 상태 확인(메인 스레드에서 실행) ---");
            Console.WriteLine("Thread1 : " + t1.Status);
            Console.WriteLine("Thread2 : " + t2.ThreadState);
            Console.WriteLine("Thread3 : " + t3.Status);
            Console.WriteLine("-------------------------");

            Console.ReadLine();
        }

        static void TestThread0(object obj)
        {
            Console.WriteLine("--- (별도 스레드에서 실행) ---");
            Console.WriteLine("Thread 0입니다");
        }
        static void TestThread1()
        {
            Console.WriteLine("--- (별도 스레드에서 실행) ---");
            Console.WriteLine("Thread 1입니다");
        }
        static void TestThread2()
        {
            Console.WriteLine("--- (별도 스레드에서 실행) ---");
            Console.WriteLine("Thread 2입니다");
        }
        static void TestThread3()
        {
            Console.WriteLine("--- (별도 스레드에서 실행) ---");
            Console.WriteLine("Thread 3입니다");
        }
    }
}
