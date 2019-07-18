#coding:utf-8
'''
> File Name : piShow.py
> Author    : Doni Daniel
> Mail      : sigboom@163.com
> Creat Time: 二 4/9 20:39:23 2019
'''
'''
note: 
    该程序希望能展现数学之美，无限不循环小数 π
    每一位值(与相邻两位有所修正)为theta, 
    每一位所在位数为半径r做半径为(r/(np.pi * 50)) ** 3 的点 
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
    out_width = 1500
    color = np.ones(M)
    line_r = (times * 2 + 210 + out_width) * np.ones(M)
    split_r = (times * 2 + 210 + out_width * 15 / 16) * np.ones(11)
    box_line = (times * 2 + 210 + out_width * 10 / 13) * np.ones(M)
    line_theta = [i * 2 * np.pi / M for i in range(M)]
    split_theta = np.linspace(0, 2 * np.pi, 11) - M / 20
    for i in range(1, 11):
        color[int(i * (M / 10) - M / 20) : int((i + 1) * (M / 10) - M / 20)] = (i + 1) * np.pi / 5
    ax.scatter(line_theta, line_r, c=color, s=out_width, cmap='hsv')
    ax.scatter(line_theta, box_line, c='k', s=out_width / 4, alpha= 1)
    ax.scatter(split_theta, split_r, c='k', s=out_width, alpha=1)

    ax.spines['polar'].set_color('k') #删去连接轴
    plt.tick_params(labelsize=25)
    plt.xticks(list((2 * np.pi * i) / 10 for i in range(0, 10)), list(range(11)))
    plt.yticks([])
    plt.ylim((0, (times * 2 + 210) + out_width))
    plt.grid(False)

def draw_point(ax, pi, times):
    # 生成外围颜色
    draw_out_line(ax, times)
    #取出所有位
    x = []
    for i in range(times):
        temp, addnum = divmod(pi(i), 10)
        x.append(np.pi / 5 * int(addnum))

    r = times / 2 * np.ones(times) + list(2 * i for i in range(0, times))
    for i in range(1, len(x) - 1):
        x[i] = x[i] + (x[i - 1] + x[i + 1] - 10) * (np.pi / 100)
    theta = x
    area = (r / (np.pi * 50)) ** 3
    color = copy.deepcopy(x)  # 确定颜色
    print(color)
    ax.scatter(theta, r, c=color, s=area, cmap='hsv', alpha=0.3)


def main():
    N = 1000
    ch = 'π'
    print("start to draw %lf points!" % np.pi)
    plt.style.use('dark_background')
    fig, ax = plt.subplots()
    ax = plt.subplot(111, polar=True)
    draw_point(ax, pi, N)
    plt.text(np.pi * 1.2, 120 + N / 2, ch, size=100, wrap=True)
    fig.set_size_inches(10, 10)
    plt.show()

if __name__ == "__main__":
    main()
