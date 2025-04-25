## 📌 C++에서 Iterator를 사용하는 이유

C++에서 `iterator`는 다양한 컨테이너의 요소를 **일관된 방식으로 순회하거나 조작**할 수 있게 해주는 도구입니다.  
각 컨테이너의 내부 구조에 상관없이 동일한 코드로 데이터를 처리할 수 있어, **범용적이고 효율적인 프로그래밍**이 가능합니다.

---

### ✅ 주요 이유 정리

1. **컨테이너에 독립적인 범용 코드 작성**  
   컨테이너 종류(`vector`, `list`, `map` 등)에 관계없이 동일한 방식으로 요소를 순회할 수 있습니다.

2. **포인터처럼 동작하지만 더 안전하고 유연함**  
   `iterator`는 포인터처럼 사용할 수 있지만, 각 컨테이너에 맞춰 추상화되어 있어 안정성과 호환성이 높습니다.

3. **삽입/삭제/검색 등의 연산을 쉽게 처리**  
   특히 `list`, `map` 등 인덱스를 지원하지 않는 컨테이너에서 유용하게 사용됩니다.

4. **STL 알고리즘과의 호환성**  
   `std::sort`, `std::find` 등 대부분의 표준 알고리즘이 iterator 기반으로 설계되어 있습니다.

5. **범위 기반 for문에서 내부적으로 iterator 사용**  
   C++11 이후 등장한 `range-based for loop`도 내부적으로 iterator를 사용합니다.

---

## 📂 컨테이너별 Iterator 사용 예시

### 📌 `std::vector` 와 Iterator

- `vector`는 메모리에 연속적으로 저장되는 배열 기반 컨테이너입니다.
- Random Access Iterator를 지원하여 인덱스 접근이 빠릅니다.

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, 3, 4};

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    // 출력: 1 2 3 4
}
```

- 정렬 예시:

```cpp
#include <algorithm>

std::sort(vec.begin(), vec.end());
```

---

### 📌 `std::list` 와 Iterator

- `list`는 이중 연결 리스트로 구현된 컨테이너입니다.
- 인덱스 접근 불가 → iterator 사용 필수
- 삽입/삭제에 매우 유리합니다.

```cpp
#include <list>
#include <iostream>

int main() {
    std::list<int> myList = {10, 20, 30};

    auto it = myList.begin();
    ++it; // 두 번째 요소
    myList.insert(it, 15); // 20 앞에 15 삽입

    for (auto val : myList) {
        std::cout << val << " ";
    }
    // 출력: 10 15 20 30
}
```

---

### 📌 `std::map` 와 Iterator

- `map`은 키-값 쌍을 저장하는 연관 배열입니다.
- 키에 대한 빠른 검색을 지원하고, iterator를 통해 키와 값에 접근할 수 있습니다.

```cpp
#include <map>
#include <iostream>

int main() {
    std::map<int, std::string> myMap = {{1, "apple"}, {2, "banana"}, {3, "cherry"}};

    for (auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    // 출력:
    // 1: apple
    // 2: banana
    // 3: cherry
}
```

- 값 삽입 예시:

```cpp
myMap[4] = "date";  // 새로운 키-값 삽입
```

---
