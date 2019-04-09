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

def drawOutLine(ax, times):
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

def drawpoint(ax, num, times, ch):
    # 生成外围颜色
    drawOutLine(ax, times)
    #取出所有位
    x = []
    for i in range(times):
        temp, addnum = divmod(num * 10 ** i, 10)
        x.append(np.pi / 5 * int(addnum))

    r = 125 * np.ones(times) + list(2 * i for i in range(0, times))
    color = copy.deepcopy(x) #确定颜色
    for i in range(1, len(x) - 1):
        x[i] = x[i] + (x[i - 1] + x[i + 1] - 10) * (np.pi / 100)
    theta = x
    area = (r / (np.pi * 5)) ** 2
    ax.scatter(theta, r, c=color, s=area, cmap='hsv', alpha=0.5)

    plt.text(np.pi * 1.2, 40 + times / 5, ch, size=90, wrap=True)

def main():
    N = 300
    num = np.pi # or np.e
    ch = 'π' # or e

    print("start to draw %lf points!" % np.e)
    plt.style.use('dark_background')
    fig, ax = plt.subplots()
    ax = plt.subplot(111, polar=True)
    drawpoint(ax, num, N, ch)
    fig.set_size_inches(10, 10)
    plt.show()

if __name__ == "__main__":
    main()
