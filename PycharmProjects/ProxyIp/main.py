import requests
import re
import telnetlib
from concurrent.futures import ProcessPoolExecutor
import pymysql

url = "https://www.kuaidaili.com/free/inha/{}/"

headers = {
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,'
              'application/signed-exchange;v=b3;q=0.9',
    'Accept-Language': 'zh-CN,zh;q=0.9',
    'Cache-Control': 'max-age=0',
    'Connection': 'keep-alive',
    'Cookie': 'channelid=0; _ga=GA1.2.1364292381.1665829640; _gid=GA1.2.551373342.1665829640; '
              'Hm_lvt_7ed65b1cc4b810e9fd37959c9bb51b31=1665829640; _gcl_au=1.1.1526546522.1665829641; '
              'sid=1665829828450213; Hm_lpvt_7ed65b1cc4b810e9fd37959c9bb51b31=1665830197',
    'Referer': 'https://www.kuaidaili.com/free/inha/3/',
    'User-Agent': 'Mozilla/5.0 (iPhone; CPU iPhone OS 13_2_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) '
                  'Version/13.0.3 Mobile/15E148 Safari/604.1 '
}

db = pymysql.connect(host='localhost', user='root', password='aa303030', database='proxyip', charset='utf8')

count = 1
ip_now = requests.get("http://httpbin.org/get").json()['origin']
rest = re.compile('.*?<td data-title="IP">(?P<ip>.*?)</td>.*?<td data-title="PORT">(?P<port>.*?)</td>.*?>', re.S)


def check(proxy_ip, proxy_port):
    try:
        telnetlib.Telnet(ip, port, timeout=5)
        resp_proxy_ip = requests.get("http://httpbin.org/get", proxies={"http": f'{proxy_ip}:{proxy_port}'})
        resp_proxy_ip.close()
        json_pict = resp_proxy_ip.json()
        pict_ip = json_pict['origin']
        if pict_ip == ip_now:
            EOFError('Proxy error')
        return True
    except Exception as e:
        print(e)
        return False


def get_proxy_ip(p_ip, p_port):
    print(f'ip: {p_ip}:{p_port}')
    if check(p_ip, p_port):
        print("check success")
        cursor = db.cursor()
        data = f'{p_ip}:{p_port}'
        try:
            cursor.execute(f'insert into ip(ip) values(\'{data}\');')
            db.commit()
            print("commit success")
        except Exception as e:
            print(e)
    else:
        print("failed")


if __name__ == '__main__':
    with ProcessPoolExecutor(max_workers=30) as t:
        while True:
            try:
                resp = requests.get(url.format(count), headers=headers)
                resp.close()

                reply = rest.finditer(resp.text)
                for item in reply:
                    ip = item.group('ip')
                    port = item.group('port')
                    t.submit(get_proxy_ip(ip, port))

                count += 1

            except Exception as e:
                print(f'page {count}: error:{e}')
