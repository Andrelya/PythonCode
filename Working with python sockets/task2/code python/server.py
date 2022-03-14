import socket, time, re


def who(client, s):
    """
        Інформація про виконавця та варіант
    """

    s.sendto((
              '/nКонтексний пошук у файлі.\n'
              'На сервері зберігається файл (достатньо лише текстовий).\n'
              'Користувач  в  клієнті задає  контекст  (лише із символів  клавіатури),\n'
              'клієнт відсилає  до сервера для виконання  контекстного пошуку  рядків. \n'
              'Результати пошуку порядково відсилаються до клієнта. Якщо пошук пустий,\n'
              'то сервер все одно відсилає відповідне попередження.\n').encode("utf-8"), client)


def search(a):
    """
        Знаходимо text в команді --> search(text); --> яку прислав клієнт
    """

    q = a.split(' :: ') # розбиваємо в список без елемента ' :: '

    if len(q) > 1:
        result = re.match(r'(search){1,1}(\(){1,1}([a-zA-Z]+|[0-9]+)(\)){1,1}(;){1,1}', q[-1])
        if result != None:
            if (len(result[0]) == len(q[-1])):
                w = result[3]
    return w


def help(client, s):
    """
        Уточнення для вводу команди
    """

    s.sendto(('\nwho();            --->    інформація про власника і варіант задачі.\n'
              'search(text);     --->    кількість пошуку збігів "text" у файлі по абзацу\n').encode("utf-8"), client)


def command_who(a):
    """
        Перевіряєм чи те, що написав клієнт є командою  -->  who();
    """

    q = a.split(' :: ')  # розбиваємо в список без елемента ' :: '

    if (len(q) > 1):
        result = re.match(r'(who){1,1}(\(){1,1}(\)){1,1}(;){1,1}', q[-1])
        if result != None:
            if (len(result[0]) == len(q[-1])):
                return 1
    return 0


def command_help(a):
    """
        Перевіряєм чи те, що написав клієнт є командою  -->  help();
    """

    q = a.split(' :: ')  # розбиваємо в список без елемента ' :: '

    if (len(q) > 1):
        result = re.match(r'(help){1,1}(\(){1,1}(\)){1,1}(;){1,1}', q[-1])
        if result != None:
            if (len(result[0]) == len(q[-1])):
                return 1
    return 0


def command_search(a):
    """
        Перевіряєм чи те, що написав клієнт є командою  -->  search(text);
    """

    q = a.split(' :: ') # розбиваємо в список без елемента ' :: '

    if (len(q) > 1):
        result = re.match(r'(search){1,1}(\(){1,1}([a-zA-Z]+|[0-9]+)(\)){1,1}(;){1,1}', q[-1])
        if result != None:
            if (len(result[0]) == len(q[-1])):
                return 1
    return 0


def server():

    with open('шлях_файлу_в_який_записуєм_команди_від_клієнта', 'w') as file:  # очищаєм файл(для запису) в який записуєм всі команди клієнтів
        pass

    host = '127.0.0.1'
    port = 1035   # будя-який(найефективніше брати більше 1025)

    clients = []  # добавляєм в список зєднення клієнтів

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)   # створення сокета --- підтримка технології TCP, IP
    s.bind((host, port))  # зв'язує сокет з локальним адресним протоколом

    quit = False  # додаткова змінна для виключення сервера
    print("Server Started")

    while not quit:  # поки сервер не відключився
        try:
            message, addr = s.recvfrom(1024)  # принімає повідомлення message від клієнта за адресою клієнта addr; 1024 -- по стандарту задається

            if addr not in clients:  # якщо адреси клієнта немає в списку добавляєм в список
                clients.append(addr)

            itsatime = time.strftime("%Y-%m-%d-%H.%M.%S", time.localtime())  # зберігає в змінну 'рік-місяць-день-год-мин-сек'

            print("[" + addr[0] + "]=[" + str(addr[1]) + "]=[" + itsatime + "]", end="")  # записуєм на сервер адресу клієнта і час команди клієнта
            print(message.decode("utf-8"))  # записуєм на сервер команду яку прислав клієнт

            with open('шлях_файлу_в_який_записуєм_команди_від_клієнта', 'a+', encoding='utf-8') as file:  #  відкриваєм файл для запису
                file.write("[" + addr[0] + "]=[" + str(addr[1]) + "]=[" + itsatime + "]/")
                file.write(message.decode("utf-8") + "\n")

            for client in clients:

                if addr == client: # якщо адреса дорівнює адресі клієнта який прислав повідомлення

                    booll1 = command_who(message.decode("utf-8"))     # наша функція зверху розташована
                    booll2 = command_search(message.decode("utf-8"))  # наша функція зверху розташована
                    booll3 = command_help(message.decode("utf-8"))    # наша функція зверху розташована

                    if booll2:  # якщо кілєнт вводить команду для пошуку текста
                        number1 = 0
                        str_1 = search(message.decode("utf-8"))  # текст який клієн хоче знайти

                        with open('файл_в_якому_відбувається_пошук_збігів', 'r', encoding='utf-8') as file:  # відкриваєм файл для читання
                            arr_lines = file.readlines()

                            for line in arr_lines:
                                number1 += 1
                                number2 = line.count(str_1)   # пошук кількості збігів str_1 в кожному абзаці
                                str_2 = 'Кількість збігів в ' + str(number1) + ' абзаці: ' + str(number2)
                                s.sendto(str_2.encode("utf-8"), client)  # надсилаєм на клієнт текст
                    elif booll3:
                        help(client, s)
                    elif booll1:
                        who(client, s)
                    else:
                        str_3 = 'Введіте правильну команду ( для уточнення введіте help(); )!!!'
                        s.sendto(str_3.encode("utf-8"), client)  # надсилаєм на клієнт текст
        except KeyboardInterrupt:
            print("Server Stopped")
            quit = True  # тоді сервер закриється
    s.close()  # закриття сокету


server()
