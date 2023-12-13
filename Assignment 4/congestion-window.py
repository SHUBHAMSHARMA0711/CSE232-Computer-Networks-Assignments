import csv
import matplotlib.pyplot as plt

count = 0
window_sum = 0.0
current_time = 0.0
packet_timestamps = []
congestion_windows = []

with open('C:\\Users\\shubh\\Downloads\\CN\\Assignment 4\\h1.csv') as file:
    reader = csv.reader(file)
    next(reader)

    for row in reader:
        if row[7] != "":
            if float(row[1]) >= current_time and float(row[1]) < current_time + 0.1:
                window_sum += float(row[7])
                count += 1

            else:
                if count != 0:
                    congestion_windows.append(window_sum / count)
                    packet_timestamps.append(current_time + 0.05)

                current_time += 0.1
                window_sum = float(row[7])
                count = 1


plt.plot(packet_timestamps, congestion_windows)
plt.title('Average Congestion Window Size vs Time (0.1s intervals)')
plt.xlabel('Time (in seconds)')
plt.ylabel('Average Congestion Window Size (in bytes)')
plt.show()