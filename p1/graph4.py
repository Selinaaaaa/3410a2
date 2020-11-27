import matplotlib.pylab as plt

x_cor = [1, 4, 8]

default = []
static = []
dynamic = []
with open ("q4_default.txt", "r") as f:
    time = (float) ((f.readline().split(" "))[1])
for i in range(3):
    default.append(time)
   
with open ("q4_static.txt", "r") as f:
    for i in range(3):
        static.append((float) ((f.readline().split(" "))[1]))
with open ("q4_dynamic.txt", "r") as f:
    for i in range(3):
        dynamic.append((float) ((f.readline().split(" "))[1]))

plt.xlabel("chunk sizes")
plt.ylabel("Time(seconds)")

plt.plot(x_cor, default, 'g-', label = 'default')
plt.plot(x_cor, static, 'c-', label = 'static')
plt.plot(x_cor, dynamic, 'y-', label = 'dynamic')

plt.legend()
plt.savefig("q4.png")
