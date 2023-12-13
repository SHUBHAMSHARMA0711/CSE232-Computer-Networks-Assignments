import csv
import matplotlib.pyplot as plt


totalBits = 0
lastTime = 0
firstTime = 0
forkThroughput = []
threadThroughput = []
selectThroughput = []
pollThroughput = []
epollThroughput = []

for i in range(1, 4):
    with open('/home/shubham21099/CN/Assignment/CSVs/server-fork-' + str(i) + '.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)

        firstTime = float(next(reader)[1])

        for row in reader:
            lastTime = float(row[1])
            totalBits += int(row[5])


    forkThroughput.append((totalBits * 8) / (lastTime - firstTime))


print("\nThrougput for Fork at no. of Clients = 500  is: ", forkThroughput[0], "bits per second")
print("Througput for Fork at no. of Clients = 1000 is: ", forkThroughput[1], "bits per second")
print("Througput for Fork at no. of Clients = 3000 is: ", forkThroughput[2], "bits per second\n\n")



for i in range(1, 4):
    with open('/home/shubham21099/CN/Assignment/CSVs/server-thread-' + str(i) + '.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)

        firstTime = float(next(reader)[1])

        for row in reader:
            lastTime = float(row[1])
            totalBits += int(row[5])


    threadThroughput.append((totalBits * 8) / (lastTime - firstTime))


print("Througput for Thread at no. of Clients = 500  is: ", threadThroughput[0], "bits per second")
print("Througput for Thread at no. of Clients = 1000 is: ", threadThroughput[1], "bits per second")
print("Througput for Thread at no. of Clients = 3000 is: ", threadThroughput[2], "bits per second\n\n")


for i in range(1, 3):
    with open('/home/shubham21099/CN/Assignment/CSVs/server-select-' + str(i) + '.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)

        firstTime = float(next(reader)[1])

        for row in reader:
            lastTime = float(row[1])
            totalBits += int(row[5])


    selectThroughput.append((totalBits * 8) / (lastTime - firstTime))


print("Througput for Select at no. of Clients = 500  is: ", selectThroughput[0], "bits per second")
print("Througput for Select at no. of Clients = 1000 is: ", selectThroughput[1], "bits per second\n\n")


for i in range(1, 4):
    with open('/home/shubham21099/CN/Assignment/CSVs/server-epoll-' + str(i) + '.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)

        firstTime = float(next(reader)[1])

        for row in reader:
            lastTime = float(row[1])
            totalBits += int(row[5])


    pollThroughput.append((totalBits * 8) / (lastTime - firstTime))


print("Througput for Poll at no. of Clients = 500  is: ", pollThroughput[0], "bits per second")
print("Througput for Poll at no. of Clients = 1000 is: ", pollThroughput[1], "bits per second")
print("Througput for Poll at no. of Clients = 3000 is: ", pollThroughput[2], "bits per second\n\n")



for i in range(1, 4):
    with open('/home/shubham21099/CN/Assignment/CSVs/server-poll-' + str(i) + '.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)

        firstTime = float(next(reader)[1])

        for row in reader:
            lastTime = float(row[1])
            totalBits += int(row[5])


    epollThroughput.append((totalBits * 8) / (lastTime - firstTime))


print("Througput for Epoll at no. of Clients = 500  is: ", epollThroughput[0], "bits per second")
print("Througput for Epoll at no. of Clients = 1000 is: ", epollThroughput[1], "bits per second")
print("Througput for Epoll at no. of Clients = 3000 is: ", epollThroughput[2], "bits per second\n\n")



clients = [500, 1000, 3000]

plt.figure(figsize=(10, 6))

plt.plot(clients, [forkThroughput[0], forkThroughput[1], forkThroughput[2]], marker='o', label='Fork')
plt.plot(clients, [threadThroughput[0], threadThroughput[1], threadThroughput[2]], marker='o', label='Thread')
plt.plot(clients, [selectThroughput[0], selectThroughput[1], 0], marker='o', label='Select')
plt.plot(clients, [pollThroughput[0], pollThroughput[1], pollThroughput[1]], marker='o', label='EPoll')
plt.plot(clients, [epollThroughput[0], epollThroughput[1], epollThroughput[2]], marker='o', label='poll')

plt.xlabel('Number of Clients')
plt.ylabel('Throughput (bits per second)')
plt.title('Throughput vs Number of Clients')
plt.yticks(pollThroughput)
plt.legend()
plt.grid(True)
plt.show()