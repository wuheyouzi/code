# 线程池: 一次性开辟一些线程. 我们用户直接给线程池子提交任务. 线程任务的调度交给线程池来完成
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor

import requests

url = "https://baidu.com"


def func():
    for item in range(100):
        resp = requests.get(url)
        print("over!")
        resp.close()


if __name__ == '__main__':
    # 创建线程池
    with ThreadPoolExecutor(61) as t:
        for i in range(1000):
            t.submit(func)
