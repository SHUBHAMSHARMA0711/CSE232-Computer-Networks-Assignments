import csv
import matplotlib.pyplot as plt
from decimal import Decimal

nextTime = 0
previousTime = 0
forkLatency = []
threadLatency = []
selectLatency = []
pollLatency = []
epollLatency = []


for i in range(1, 4):
    latency = []
    with open('/home/shubham21099/CN/Assignment/CSVs/server-fork-' + str(i) + '.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)

        previousTime = float(next(reader)[1])

        for row in reader:
            nextTime = float(row[1])
            latency.append(nextTime - previousTime)
            previousTime = nextTime

    forkLatency.append(sum(latency) / len(latency))

print("\nAverage Latency for Fork at no. of Clients = 500  is: ", forkLatency[0] * 1000, "milliseconds")
print("Average Latency for Fork at no. of Clients = 1000 is: ", forkLatency[1] * 1000, "milliseconds")
print("Average Latency for Fork at no. of Clients = 3000 is: ", forkLatency[2] * 1000, "milliseconds\n\n")


for i in range(1, 4):
    latency = []
    with open('/home/shubham21099/CN/Assignment/CSVs/server-thread-' + str(i) + '.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)

        previousTime = float(next(reader)[1])

        for row in reader:
            nextTime = float(row[1])
            latency.append(nextTime - previousTime)
            previousTime = nextTime

    threadLatency.append(sum(latency) / len(latency))

print("Average Latency for Thread at no. of Clients = 500  is: ", threadLatency[0] * 1000, "milliseconds")
print("Average Latency for Thread at no. of Clients = 1000 is: ", threadLatency[1] * 1000, "milliseconds")
print("Average Latency for Thread at no. of Clients = 3000 is: ", threadLatency[2] * 1000, "milliseconds\n\n")


for i in range(1, 3):
    latency = []
    with open('/home/shubham21099/CN/Assignment/CSVs/server-select-' + str(i) + '.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)


        for row in reader:
            latency.append(Decimal(row[7]))
                

    selectLatency.append(sum(latency) / len(latency))


print("Average Latency for Select at no. of Clients = 500  is: ", selectLatency[0] * 1000, "milliseconds")
print("Average Latency for Select at no. of Clients = 1000 is: ", selectLatency[1] * 1000, "milliseconds\n\n")



for i in range(1, 4):
    latency = []
    with open('/home/shubham21099/CN/Assignment/CSVs/server-poll-' + str(i) + '.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)


        for row in reader:
            latency.append(Decimal(row[7]))
                

    pollLatency.append(sum(latency) / len(latency))


print("Average Latency for Poll at no. of Clients = 500  is: ", pollLatency[0] * 1000, "milliseconds")
print("Average Latency for Poll at no. of Clients = 1000 is: ", pollLatency[1] * 1000, "milliseconds")
print("Average Latency for Poll at no. of Clients = 3000 is: ", pollLatency[2] * 1000, "milliseconds\n\n")


for i in range(1, 4):
    latency = []
    with open('/home/shubham21099/CN/Assignment/CSVs/server-epoll-' + str(i) + '.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)

        previousTime = float(next(reader)[1])

        for row in reader:
            nextTime = float(row[1])
            latency.append(nextTime - previousTime)
            previousTime = nextTime

    epollLatency.append(sum(latency) / len(latency))

print("Average Latency for Epoll at no. of Clients = 500  is: ", epollLatency[0] * 1000, "milliseconds")
print("Average Latency for Epoll at no. of Clients = 1000 is: ", epollLatency[1] * 1000, "milliseconds")
print("Average Latency for Epoll at no. of Clients = 3000 is: ", epollLatency[2] * 1000, "milliseconds\n\n")



clients = [500, 1000, 3000]

plt.figure(figsize=(10, 6))

plt.plot(clients, [forkLatency[0], forkLatency[1], forkLatency[2]], marker='o', label='Fork')
plt.plot(clients, [threadLatency[0], threadLatency[1], threadLatency[2]], marker='o', label='Thread')
plt.plot(clients, [selectLatency[0], selectLatency[1], 0], marker='o', label='Select')
plt.plot(clients, [pollLatency[0], pollLatency[1], pollLatency[2]], marker='o', label='Poll')
plt.plot(clients, [epollLatency[0], epollLatency[1], epollLatency[2]], marker='o', label='Epoll')

plt.xlabel('Number of Clients')
plt.ylabel('Latency (millisecond)')
plt.title('Latency vs Number of Clients')
plt.yticks(threadLatency)
plt.legend()
plt.grid(True)
plt.show()