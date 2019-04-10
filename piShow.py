#coding:utf-8
'''
> File Name : piShow.py
> Author    : Doni Daniel
> Mail      : sigboom@163.com
> Creat Time: 二 4/9 20:39:23 2019
'''
'''
note: 
    该程序希望能展现数学之美，无限不循环小数 π 或 e
    每一位值(与相邻两位有所修正)为theta, 
    每一位所在位数为半径r做半径为(r/(np.pi * 5)) ** 2 的点 
'''
import numpy as np
import matplotlib.pyplot as plt
import copy

#马青公式
def pi(n):
    p = 10 ** (n + 10)
    a = p * 16 // 5
    b = p * 4 // -239
    f = a + b
    p = f
    j = 3
    while abs(f):
        a //= -25
        b //= -57121
        f = (a + b) // j
        p += f
        j += 2
    return p // 10**10  # 去掉 k 位，k=10

def draw_out_line(ax, times):
    M = 1000
    color = np.zeros(M)
    line_r = (times * 2 + 210) * np.ones(M)
    line_theta = [i * 2 * np.pi / M for i in range(M)]
    for i in range(1, 11):
        color[int(i * (M / 10) - M / 20): int((i + 1) * (M / 10) - M / 20)] = (i + 1) * np.pi / 5;
    ax.scatter(line_theta, line_r, c=color, s=1000, cmap = 'hsv')

    plt.xticks(list((2 * np.pi * i) / 10 for i in range(0, 10)), list(range(11)))
    plt.yticks([])
    plt.ylim((0, (times * 2 + 210)))
    plt.grid(False)

def draw_point(ax, pi, times):
    # 生成外围颜色
    draw_out_line(ax, times)
    #取出所有位
    x = []
    for i in range(times):
        temp, addnum = divmod(pi(i), 10)
        x.append(np.pi / 5 * int(addnum))

    r = times / 2.5 * np.ones(times) + list(2 * i for i in range(0, times))
    color = copy.deepcopy(x) #确定颜色
    for i in range(1, len(x) - 1):
        x[i] = x[i] + (x[i - 1] + x[i + 1] - 10) * (np.pi / 100)
    theta = x
    area = (r / (np.pi * 2)) ** 2
    ax.scatter(theta, r, c=color, s=area, cmap='hsv', alpha=0.5)

def main():
    N = 1000
    ch = 'π'
    print("start to draw %lf points!" % np.pi)
    plt.style.use('dark_background')
    fig, ax = plt.subplots()
    ax = plt.subplot(111, polar=True)
    draw_point(ax, pi, N)
    plt.text(np.pi * 1.2, 80 + N / 4, ch, size=90, wrap=True)
    fig.set_size_inches(10, 10)
    plt.show()

if __name__ == "__main__":
    main()
