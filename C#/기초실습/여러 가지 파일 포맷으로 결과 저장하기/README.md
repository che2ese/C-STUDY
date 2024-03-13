# 스트림
**스트림** : 데이터가 흐르는 통로 

*메모리에서 하드 디스크로 파일을 쓰기 전에, 스트림을 먼저 생성*


|파일읽기|파일쓰기|
|:---:|:---:|
|StreamWriter sw = new StreamWrtier(new FileStream("a.txt", FileMode.Create))|StreamReader sw = new StreamReader(new FileStream("a.txt", FileMode.Open))|

