import time
import re


def empty_loop(d, sum):
    """
        Вираховуєм час  певної кількості циклів.
    """

    starttime = time.time()
    for i in range(d):
        c = sum
        c = sum
        c = sum
        c = sum
        c = sum
        c = sum
        c = sum
        c = sum
        c = sum
        c = sum
    endtime = time.time()
    return endtime - starttime


def addition(a, b, d):
    """
        Вираховуєм кількість операцій додавання за секунду.
        Повертає список з двох елементів ["+", кількість_операцій_за_секунду].
    """

    sum = a + b
    starttime = time.time()
    for i in range(d):
        a + b
        a + b
        a + b
        a + b
        a + b
        a + b
        a + b
        a + b
        a + b
        a + b

    endtime = time.time()
    difference1 = endtime - starttime
    difference2 = empty_loop(d, sum)
    difference = difference1 - difference2
    number_operations_second = (d * 10) / difference  # вираховуєм кількість операцій за секунду.
    return int(number_operations_second)


def subtraction(a, b, d):
    """
        Вираховуєм кількість операцій віднімання за секунду.
        Повертає список з двох елементів ["-", кількість_операцій_за_секунду ]
    """

    sum = a - b
    starttime = time.time()
    for i in range(d):
        c = a - b
        c = a - b
        c = a - b
        c = a - b
        c = a - b
        c = a - b
        c = a - b
        c = a - b
        c = a - b
        c = a - b

    endtime = time.time()
    difference1 = endtime - starttime
    difference2 = empty_loop(d, sum)
    difference = difference1 - difference2
    number_operations_second = (d * 10) / difference  # вираховуєм кількість операцій за секунду.
    return number_operations_second


def multiplication(a, b, d):
    """
        Вираховуєм кількість операцій множення за секунду.
        Повертає список з двох елементів ["*", кількість_операцій_за_секунду ]
    """

    sum = a * b
    starttime = time.time()
    for i in range(d):
        c = a * b
        c = a * b
        c = a * b
        c = a * b
        c = a * b
        c = a * b
        c = a * b
        c = a * b
        c = a * b
        c = a * b

    endtime = time.time()
    difference1 = endtime - starttime
    difference2 = empty_loop(d, sum)
    difference = difference1 - difference2
    number_operations_second = (d * 10) / difference  # вираховуєм кількість операцій за секунду.
    return number_operations_second


def division(a, b, d):
    """
        Вираховуєм кількість операцій ділення за секунду
        Повертає список з двох елементів ["/", кількість_операцій_за_секунду ]
    """

    sum = a / b
    starttime = time.time()
    for i in range(d):
        c = a / b
        c = a / b
        c = a / b
        c = a / b
        c = a / b
        c = a / b
        c = a / b
        c = a / b
        c = a / b
        c = a / b

    endtime = time.time()
    difference1 = endtime - starttime
    difference2 = empty_loop(d, sum)
    difference = difference1 - difference2
    number_operations_second = (d * 10) / difference  # вираховуєм кількість операцій за секунду.
    return number_operations_second


def maximum(arr):
    """
        Вираховуєм максимальну кількість операцій з усіх операцій для певного операнда.
    """
    max1 = max(arr)
    return max1


def interest(max_number, number):
    """
        Вираховуєм відсоток кількості операцій від -->
        --> максимальної кількісті операцій з усіх операцій для будь-якого типу.
    """
    return int((number * 100) / max_number)


def int_number(a, b, stop, types_arr, arr):
    """
        Додавання, віднімання, множення, ділення для int
    """
    if type(a) == type(b) == int:
        types_arr.append("int    ")
        number = addition(a, b, stop)
        arr.append(number)
        number = subtraction(a, b, stop)
        arr.append(number)
        number = multiplication(a, b, stop)
        arr.append(number)
        number = division(a, b, stop)
        arr.append(number)
    else:
        print("Кількість операцій для типу int НЕ можливо обчислити!!!",
              "Параметри a, b мають мати тип int!!!", "", sep="\n", )
    return arr, types_arr


def float_number(a, b, stop, types_arr, arr):
    """
        Додавання, віднімання, множення, ділення для float
    """
    if type(a) == type(b) == float:
        types_arr.append("float  ")
        number = addition(a, b, stop)
        arr.append(number)
        number = subtraction(a, b, stop)
        arr.append(number)
        number = multiplication(a, b, stop)
        arr.append(number)
        number = division(a, b, stop)
        arr.append(number)
    else:
        print("Кількість операцій для типу float НЕ можливо обчислити!!!",
              "Параметри a, b мають мати тип float!!!", "", sep="\n")
    return arr, types_arr


def complex_number(a, b, stop, types_arr, arr):
    """
        Додавання, віднімання, множення, ділення для complex
    """
    if type(a) == type(b) == complex:
        types_arr.append("complex")
        number = addition(a, b, stop)
        arr.append(number)
        number = subtraction(a, b, stop)
        arr.append(number)
        number = multiplication(a, b, stop)
        arr.append(number)
        number = division(a, b, stop)
        arr.append(number)
    else:
        print("Кількість операцій для типу complex НЕ можливо обчислити!!!",
              "Параметри a, b мають мати тип complex!!!", "", sep="\n")
    return arr, types_arr


def str_number(a, b, stop, types_arr, arr):
    """
        Додавання, віднімання, множення, ділення для str
    """
    z1 = 0
    if type(a) == type(b) == str:
        types_arr.append("str    ")
        number = addition(a, b, stop)
        z1 = 1
    elif (type(a) == str and type(b) == int) or (type(b) == str and type(a) == int):
        types_arr.append("str    ")
        number = multiplication(a, b, stop)
        z1 = 2
    else:
        print("Кількість операцій для типу str НЕ можливо обчислити!!!",
              "Параметри a, b повинні мати тип str, хоча б один!!!", "", sep="\n", )
    if z1 == 1:
        arr.append(number)
        arr.append(0)
        arr.append(0)
        arr.append(0)
    elif z1 == 2:
        arr.append(0)
        arr.append(0)
        arr.append(number)
        arr.append(0)
    else:
        pass
    return arr, types_arr


def histogram(interest):
    """
        Будуєм гістограму по відсотках. ( 1% = X )
    """
    string = "X" * int(interest)
    return string


def output1(max, arr, types_arr):
    """
        Виводить дані тіщо не обхідні для лабораторної
    """
    operants = ["+", "-", "*", "/"]
    for i in range(0, len(arr)):
        if arr[i]:
            vidsotok = interest(max, arr[i])
            print(f"{operants[i % 4]}  {types_arr[i // 4]}   {arr[i]:.7e}      {histogram(vidsotok)}", end="")
            print(int(100 - vidsotok) * " ", "  ", str(vidsotok), "%", sep="")
    print("\n")


def test_in_file1(arr):
    """
        Процес запису в file.
        index --> номер елементів, які мають один і той самий тип.
    """
    with open("macOS1.txt", "w") as file: # qwe1.txt --> файл у який записуєм результат 
        for index in range(20):
            op = [ "+", "-", "*", "/", ]                       # операції які присутні в даній задачі
            wo = [ "int", "float", "complex", "str", "str"]    # тип кожного визова для певної операції(при кожному визові додаєм тип)
            arr1 = list()
            file.write(f"\nкількість операцій за 1 секунду для  {op[index % 4]} {wo[index // 4]}\n")
            for i in arr:
                file.write(f"{int(i[index])} --> ")
                arr1.append(i[index])
            average_duration = sum(arr1) / len(arr)
            file.write(f"\n\nДля ({op[index % 4]} {wo[index // 4]}):")
            maximum = max(arr1)
            minimum = min(arr1)
            difference = maximum - minimum
            file.write(f"\n     Середня кількість операції = {average_duration:.7e}")
            print(f"\n\nДля ({op[index % 4]} {wo[index // 4]}):")
            print(average_duration)
            file.write(f"\n     max     = {maximum:.7e}")
            file.write(f"\n     min     = {minimum:.7e}")
            file.write(f"\n     Різниця = {difference:.7e}")
            file.write("\n----------------------------------------------------------------------------------------------"
                       "------------------------------------------------------------------------------------------------\n")


def test_in_file2(max, arr, types_arr):   # файл у який записуєм гістограму кожного цикла
    operants = ["+", "-", "*", "/"]
    with open("qwe2.txt", "a") as file:
        for i in range(0, len(arr)):
            if arr[i]:
                vidsotok = interest(max, arr[i])
                file.write(f"{operants[i % 4]}  {types_arr[i // 4]}   {arr[i]:.7e}      {histogram(vidsotok)}")
                file.write(f"{int(100 - vidsotok) * ' '} {str(vidsotok)}%\n")


def generation_process(stop):
    """
        Процес генерації
    """
    arr = list()
    types_arr = list()
    a, b = 2, 3
    arr, types_arr = int_number(a, b, stop, types_arr, arr)

    a, b = 6.67, 32.98
    arr, types_arr = float_number(a, b, stop, types_arr, arr)

    a, b = 6 + 8j, 3 + 4j
    arr, types_arr = complex_number(a, b, stop, types_arr, arr)

    a, b = "1", "6"
    arr, types_arr = str_number(a, b, stop, types_arr, arr)

    a, b = 10, "1"
    arr, types_arr = str_number(a, b, stop, types_arr, arr)
    return arr, types_arr




def output2(number_generations, stop):
    """
        Виводить гістоограму з лабки для кількості операцій
        і записує тест в файл окремо для кожної операції та типу
    """
    try:
        arr1 = []
        arr2 = []

        with open("macOS2.txt", "tw"):           # створюєм пустий файл
            pass
        for i in range(number_generations):
            start = time.time()
            arr, types_arr = generation_process(stop)
            end = time.time()
            arr2.append(end - start)
            arr1.append(arr)
            max = maximum(arr)
            test_in_file2(max, arr, types_arr)  # запис гістограми з умов задачі
            with open("qwe2.txt", "a") as file:
                file.write("\n\n")
            output1(max, arr, types_arr)
        test_in_file1(arr1)  # запис тесту кількості операцій за 1с певної операції та типу
        print("\n\n Час виконання генерації кількості операцій за 1 секунду для", number_generations,
              "генераторів:", sum(arr2))
    except ZeroDivisionError:
        print("Ділення на нуль, збільши stop!!!")


stop = 1_000_000
number_generations = 1
output2(number_generations, stop)

