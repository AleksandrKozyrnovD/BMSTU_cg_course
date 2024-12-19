from matplotlib import pyplot as plt

    # 12 & 0.4 & 0.34 \\ \hline
    # 24 & 1.25 & 0.41 \\ \hline
    # 36 & 1.45 & 0.42 \\ \hline
    # 48 & 1.7 & 0.46 \\ \hline
    # 60 & 1.76 & 0.48 \\ \hline
    # 72 & 1.91 & 0.49 \\ \hline
    # 84 & 2.13 & 0.5 \\ \hline
    # 96 & 2.34 & 0.54 \\ \hline
    # 108 & 2.41 & 0.57 \\ \hline
    # 120 & 2.55 & 0.59 \\ \hline


with_light = [
    [12, 0.4],
    [24 * 2, 1.25],
    [36 * 3, 1.45],
    [48*4, 1.7],
    [60*5, 1.76],
    [72*6, 1.91],
    [84*7, 2.13],
    [96*8, 2.34],
    [108*9, 2.41],
    [120*10, 2.55]
]


without_light = [
    [12,0.34],
    [24*2,0.41],
    [36*3,0.42],
    [48*4,0.46],
    [60*5,0.48],
    [72*6,0.487],
    [84*7,0.5],
    [96*8,0.54],
    [108*9,0.57],
    [120*10,0.59]
]

x1 = [i[0] for i in with_light]
y1 = [i[1] for i in with_light]


x2 = [i[0] for i in without_light]
y2 = [i[1] for i in without_light]


plt.grid()
plt.scatter(x1, y1, color='red', label='Со светом', marker='o')
plt.plot(x1, y1, color='red')

plt.scatter(x2, y2, color='blue', label='Без света', marker='*')
plt.plot(x2, y2, color='blue')


plt.xlabel('Количество видимых граней')
plt.ylabel('Время отрисовки, сек.')

plt.xticks([x[0] for x in with_light])

plt.legend()

plt.show()
