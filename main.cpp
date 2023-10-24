
/*template <typename T>
ComplexConcept<T>
hash()
toString()
1.Наличие у типа T метода hash(), который возвращает тип, конвертируемый в long;
2.Наличие у типа T метода toString(), который возвращает std::string;
3.Отсутствие у типа T виртуального деструктора.
Для проверки наличия у типа метода перечислите ограничения, используя ключевое слово requires
Для проверки конвертируемости возвращаемого типа воспользуетесь трейтом std::convertible_to
Для проверки возвращаемого типа воспользуетесь трейтом std::same_as
Для проверки отсутствия у типа виртуального деструктора воспользуетесь трейтом std::has_virtual_destructor
*/

#include <iostream>
#include <string>

//--------------------------------------------------------------
//g++ -std=c++2a -fconcepts-diagnostics-depth=2 -o a main.cpp
//-------------------------------------------------------------
template <typename T>
concept ComplexConcept = requires(T t)
 {
    { t.hash() } -> std::convertible_to<long>;//Проверяем, что возврат функции может быть сконвертирован к long
    { t.toString()}  -> std::same_as<std::string>;//Проверяем, что возврат функции в точности равен string
        requires !std::has_virtual_destructor_v<T>;//Проверяем на валидность
};
struct RightTest
{
  int a{100};
  long hash() const
  {
    return a;
  }
  std::string toString() const
  {
    return std::to_string(a);
  }
};
struct InvalidTest
{
    const char* toString() const
    {
      return "InvalidTest";
    }
 virtual ~InvalidTest(){};

};
void testPrint(ComplexConcept auto &value)
{
  std::cout<<value.hash()<<"\n";
  std::cout<<value.toString()<<"\n";
}
int main()
{
RightTest rt;
InvalidTest it;
testPrint(rt);
//testPrint(it);//не компилируется
return 0;
}
