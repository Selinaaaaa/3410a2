import matplotlib.pylab as plt

x_cor = [1, 2, 4, 8]

s2d = []
s3d = []
with open ("2ds.txt", "r") as f:
    time = (float) ((f.readline().split(" "))[1])
for i in range(4):
    s2d.append(time)
 
with open ("3ds.txt", "r") as f:
    time = (float) ((f.readline().split(" "))[1])
for i in range(4):
    s3d.append(time)
    
p2d = []
p3d = []
with open ("2dp.txt", "r") as f:
    for i in range(4):
        p2d.append((float) ((f.readline().split(" "))[1]))
with open ("3dp.txt", "r") as f:
    for i in range(4):
        p3d.append((float) ((f.readline().split(" "))[1]))

plt.xlabel("No. Threads")
plt.ylabel("Time(seconds)")

plt.plot(x_cor, s2d, 'b-', label = '2dSequential')
plt.plot(x_cor, s3d, 'g-', label = '3dSequential')
plt.plot(x_cor, p2d, 'c-', label = '2dparallel')
plt.plot(x_cor, p3d, 'y-', label = '3dparallel')

plt.legend()
plt.savefig("q3.png")
