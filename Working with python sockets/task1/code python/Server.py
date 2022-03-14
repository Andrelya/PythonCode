import socket, time, re, pyglet
from threading import *
import pygame, time


def who(client, s):
    s.sendto((
              '/nПрограмуємий будильник.\n'
              'Користувач з клієнта задає інтервал в секундах відображення часу на сервер\n'
              'Сервер в зазначені інтервали передає до клієнта свій час, а клієнт його відображає.\n'
              '(Клієнт лише відображає дані сервера, але сам він ніякий час не рахує.)\n').encode("utf-8"), client)


def command_time(a):
    q = a.split(' :: ')
    if len(q) > 1:
        result = re.match(r'(time){1,1}(\(){1,1}([0-9]+)(\)){1,1}(;){1,1}', q[-1])
        if result != None:
            if (len(result[0]) == len(q[-1])) and (int(result[3]) > 0):
                return int(result[3])
    return 0


def command_who(a):
    q = a.split(' :: ')
    if (len(q) > 1):
        result = re.match(r'(who){1,1}(\(){1,1}(\)){1,1}(;){1,1}', q[-1])
        if result != None:
            if (len(result[0]) == len(q[-1])):
                return 1
    return 0


def command_stop(a):
    q = a.split(' :: ')
    if (len(q) > 1):
        result = re.match(r'(stop){1,1}(\(){1,1}(\)){1,1}(;){1,1}', q[-1])
        if result != None:
            if (len(result[0]) == len(q[-1])):
                return 1
    return 0


def sort(arr1, arr2, arr3):
    min = arr1[0]
    index = 0
    sort_second = list()
    sort_client = list()
    sort_time   = list()
    for i in range(0, len(arr1)):
        for j in range(0, len(arr1)):
            if (arr1[j] < min) :
                min = arr1[j]
                index = j
        sort_second.append(min)
        sort_client.append(arr2[index])
        sort_time.append(arr3[index])
        del arr3[index]
        del arr2[index]
        del arr1[index]
        if len(arr1):
            min = arr1[0]
            index = 0
    return  sort_second, sort_client, sort_time


def difference(sort_second):
    k1 = 0
    k2 = 0
    size = len(sort_second)
    for i in range(k1, size-2):
        for j in range(k1+1, len(sort_second)):
           number = sort_second[j] - sort_second[i]
           sort_second[k1+1] = number
           k1 += 1
        
        k2 += 1
        k1 = k2
    return sort_second


def k(dif_second, sort_client, sort_time, sort_second, s):

    for i in range(0, len(dif_second)):
            time.sleep(dif_second[i])

            time1 = str(time.strftime("%H:%M:%S", time.localtime()))
            time2 = str(sort_time[i])
            s.sendto(('\n' + 'Початковий час:         ' + time2).encode("utf-8"), sort_client[i])
            s.sendto(('Таймер, який спрацював: ' + str(sort_second[i]) + 'с.').encode("utf-8"), sort_client[i])
            s.sendto(('Кінцевий час:           ' + time1).encode("utf-8"), sort_client[i])
            
            # при включанні будильника вмикається музика 'шлях_до_музики'
            pygame.init()
            song = pygame.mixer.Sound('шлях_до_музики')
            clock = pygame.time.Clock()
            song.play()
            while True:
                clock.tick(60)
                time.sleep(7)
                pygame.quit()


def server():
    with open('/Users/andrejlasuk/Desktop/С++/КМ1/Варік 11/команди відправлені на сервер.txt', 'w') as file: # перезаписуєм файл(опорожнюєм файл)
        pass

    host = '127.0.0.1'
    port = 1037

    clients = []

    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # перший сокет TCP, другій IP --- > протокол
    s.bind((host, port))

    quit = False
    print("Server Started")

    arr1 = list()
    arr2 = list()
    arr3 = list()
    arr4 = list()

    while not quit:
        try:
            data, addr = s.recvfrom(1024)  # date принімає повідомлення; addr лічний адрес клієнта

            if addr not in clients:
                arr4.append([addr, 0])
                clients.append(addr)

            itsatime = time.strftime("%Y-%m-%d-%H.%M.%S", time.localtime())  # відображаєм час кожної команди на сервері
            print("[" + addr[0] + "]=[" + str(addr[1]) + "]=[" + itsatime + "]/", end="")
            print(data.decode("utf-8"))

            with open('/Users/andrejlasuk/Desktop/С++/КМ1/Варік 11/команди відправлені на сервер.txt', 'a+', encoding='utf-8') as file:
                """
                  запис команд кожного клієнта у файл
                """
                file.write("[" + addr[0] + "]=[" + str(addr[1]) + "]=[" + itsatime + "]/")
                file.write(data.decode("utf-8") + "\n")

            for client in clients:
                if addr == client:

                    second = command_time(data.decode("utf-8"))
                    booll1 = command_who(data.decode("utf-8"))


                    if second:
                        time1 = str(time.strftime("%H:%M:%S", time.localtime()))
                        arr1.append(second)
                        arr2.append(client)
                        arr3.append(time1)

                        sort_second, sort_client, sort_time = sort(arr1, arr2, arr3)
                        dif_second = difference(sort_second)

                        for i in arr4:
                            if i[0] == addr:
                                i[1] += 1
                                if i[1] <= 3:
                                    s.sendto(('\t\t' + 'Час:    ' + time1).encode("utf-8"), client)
                                    s.sendto(('\t\t' + 'Таймер: ' + str(second) + 'c.').encode("utf-8"), client)
                                    rT = Thread(target=k, args=(dif_second, sort_client, sort_time, sort_second, s))
                                    rT.start()
                                else:
                                    str_line = "Нажаль, кількість будильників вичерпано!"
                                    s.sendto(str_line.encode("utf-8"), client)
                    elif booll1:
                        who(client, s)
                    else:
                        for client in clients:
                            if addr != client:
                                s.sendto(data, client)
        except KeyboardInterrupt:
            print("Server Stopped")
            quit = True
    s.close()


server()


