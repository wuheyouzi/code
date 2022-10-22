import time
import requests
from lxml import etree
import datetime

url = 'https://s.weibo.com/top/summary?cate=realtimehot'

header = {
    'authority': 's.weibo.com',
    'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,'
              'application/signed-exchange;v=b3;q=0.9',
    'accept-language': 'zh-CN,zh;q=0.9',
    'cache-control': 'max-age=0',
    'cookie': 'SUBP=0033WrSXqPxfM725Ws9jqgMF55529P9D9WW-fHGvKn_NC7ARe98PLJea5JpX5KMhUgL.FoMXSonf1KnpS022dJLoI0YLxK-LB'
              '.BL1KeLxKBLB.BLBK5LxK.L1h2L1hMLxKnLBKML1h2LxKnL1KqL1hBLxKnL12BLBoMLxKqL1KMLBoqt; '
              'SINAGLOBAL=6374478611580.168.1659164111117; ALF=1691130319; SSOLoginState=1659594320; '
              'SCF=AsibDHZDqunaY9oyGs633EcmAhxMr-wIZ3d1hpIoRsT9k0NqU1hE7yGjfObYB4tmWasrv5XMByay9R0TPInP7IU.; '
              'SUB=_2A25P7xYADeRhGeFK7VoU-SbNzD2IHXVsnQDIrDV8PUNbmtANLVD_kW9NQzDJp1BEYNRrC1ROn9tTmVDLQanyJ6GZ; '
              '_s_tentry=login.sina.com.cn; UOR=login.sina.com.cn,weibo.com,login.sina.com.cn; '
              'Apache=1565674917000.2283.1659594315585; '
              'ULV=1659594315591:5:4:4:1565674917000.2283.1659594315585:1659484452576',
    'sec-ch-ua': '.Not/A)Brand";v="99", "Google Chrome";v="103", "Chromium";v="103',
    'sec-ch-ua-mobile': '?1',
    'sec-ch-ua-platform': 'Android',
    'sec-fetch-dest': 'document',
    'sec-fetch-mode': 'navigate',
    'sec-fetch-site': 'none',
    'sec-fetch-user': '?1',
    'upgrade-insecure-requests': '1',
    'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) '
                  'Chrome/103.0.0.0 Mobile Safari/537.36 '
}

params = {
    'cate': 'realtimehot'
}


def get_now_time():
    return datetime.datetime.now()


def get_now_time_str():
    return datetime.datetime.strftime(get_now_time(), '%Y-%m-%d %H时%M分')


if __name__ == '__main__':

    now_time = get_now_time_str()

    while True:
        while now_time == get_now_time_str():
            time.sleep(0.5)

        now_time = get_now_time_str()
        print("Time: ", get_now_time(), end=' ')

        resp = requests.get(url, headers=header, params=params)

        doc = etree.HTML(resp.text)
        tr = doc.xpath('/html/body/div/section/ul/li/a/span')

        with open('./微博热搜/' + get_now_time_str() + '.txt', 'w') as p:
            for i in tr:
                p.write(i.text + '\n')

        print('get over!')
        time.sleep(0.5)
