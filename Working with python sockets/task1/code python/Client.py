import socket, time, threading

"""
    Тобто тут ми відправляєм від одного користувача повідомлення на сервер
    а далі від сервера вони розприділяються по клієнтам
"""


def receving(name, sock):
    while not shutdownd:
        try:
            data, addr = sock.recvfrom(1024)  # повідомлення і адреса клієнта
            print(data.decode("utf-8"))  # виводим розшифроване повідомлення
        except:
            pass


shutdownd = False
join = False

host = '127.0.0.1'      # відмінний від сервера
port = 0                # будь-який бо сервер сам створює по суті йому порт

server = ('127.0.0.1', 1037)

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)    # підтримка технології TCP IP
s.bind((host, port))
s.setblocking(0)    # допоміжна функція щоб виникало лишніх помилок оскільки сервер  у нас це многопоточність

print("Команда закінчується крапкою з комою")
alias = input("Name: ")

rT = threading.Thread(target=receving, args=("RecvThread", s))     # робимо многопоточність, тобто відображення повідомлень у кожного клієнта
rT.start()

while (shutdownd == False):   # поки клієнт не вийшов
    if (join == False):
        s.sendto(("[" + alias + "] --> клієнт приєднався").encode("utf-8"), server)
        join = True
    else:
        try:
            message = input()
            if message != "":
                s.sendto(("[" + alias + "] :: " + message).encode("utf-8"), server)
            time.sleep(0.2)
        except:
            s.sendto(("[" + alias + "] --> клієнт віддєднався").encode("utf-8"), server)
            shutdownd = True

rT.join()  # потрібне щоб переглядало нашу прграму, для того щоб користувачі нормально контактували в часі, не булорозривів у часі
s.close()
