import requests
import re

url = 'https://image.baidu.com/search/index?ct=201326592&z=&tn=baiduimage&ipn=r&word=%E7%B1%B3%E7%94%BB%E5%B8%88%E4' \
      '%BD%9C%E5%93%81&pn=&spn=&istype=2&ie=utf-8&oe=utf-8&cl=2&lm=-1&st=-1&fr=&fmq=1651566210785_R&ic=&se=&sme' \
      '=&width=&height=&face=0&hd=&latest=&copyright=&cs=&os=&objurl=&di=&gsm=3a2&dyTabStr=MCwzLDIsNiwxLDQsNSw4LDcsOQ' \
      '%3D%3D '

headers = {
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,'
              'application/signed-exchange;v=b3;q=0.9',
    'Accept-Encoding': 'gzip, deflate, br',
    'Accept-Language': 'zh-CN,zh;q=0.9',
    'Cache-Control': 'max-age=0',
    'Connection': 'keep-alive',
    'Cookie': 'BDqhfp=%E7%B1%B3%E7%94%BB%E5%B8%88%E4%BD%9C%E5%93%81%26%26-10-1undefined%26%260%26%261; '
              'winWH=%5E6_1536x731; BDIMGISLOGIN=0; BIDUPSID=7DAD0ECC5B301F7858C6BFD5E8F8E670; PSTM=1643120555; '
              '__yjs_duid=1_365f63a1c12962bcdd552741ae1621741644545731188; '
              'BAIDUID=8DE9135E201E5637F797FD3EFBD15E12:FG=1; BDORZ=B490B5EBF6F3CD402E515D22BCDA1598; '
              'BA_HECTOR=a424ah8g808l84alm21h71hrt0r; '
              'H_PS_PSSID'
              '=36309_31660_34813_35909_36165_34584_35979_36074_36279_36281_35864_36236_26350_36303_22158_36061; '
              'delPer=0; PSINO=5; BDRCVFR[dG2JNJb_ajR]=mk3SLVN4HKm; BDRCVFR[-pGxjrCMryR]=mk3SLVN4HKm; '
              'indexPageSugList=%5B%22%E7%B1%B3%E7%94%BB%E5%B8%88%E4%BD%9C%E5%93%81%22%2C%22%E5%9B%9B%E5%8D%83%E5%9B'
              '%9B%E4%B8%87%E5%8E%86%E5%8F%B2%E5%9C%BA%E9%A6%86%E5%86%85%E9%83%A8%22%2C%22%E9%A3%8E%E6%99%AF%E5%9B%BE'
              '%E7%89%87%22%2C%22cake%22%2C%22java%22%5D; cleanHistoryStatus=0; BDRCVFR[tox4WRQ4-Km]=mk3SLVN4HKm; '
              'BDRCVFR[CLK3Lyfkr9D]=mk3SLVN4HKm; '
              'ab_sr=1.0'
              '.1_Y2M1ZTBjNmE4MGFmMTU4MTc0ZGM1MzAyNWE4NWMzOTNlMGFiYmVkMmNjMzgzZjY0NzFiMDA2YThhOTAxYTIwMzM4MTUwYTA1ZDViOWMzMTFhMjZkYzhlOTdhZmVhNDlkZjBhN2RkNTZhZmY5MDRhMTJiOTdlYzg5NjE4YWIwNDE4NWE2ODEyZWZiMDNmM2YxYmYyYTI0ZWFlMzEzNDI1Mg==; BAIDUID_BFESS=8DE9135E201E5637F797FD3EFBD15E12:FG=1',
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                  'Chrome/101.0.4951.54 Safari/537.36 '
}


def func(s):
    if s.split('/')[2] == "ns-strategy.cdn.bcebos.com":
        return 1
    else:
        return 0


if __name__ == '__main__':
    resp = requests.get(url, headers=headers)
    resp.encoding = "utf-8"

    rest = re.compile('.*?"thumbURL":"(?P<picture>.*?)"', re.S)
    reply = rest.finditer(resp.text)

    for item in reply:
        r_url = item.group("picture")
        r_url = r_url.replace('\\', '')
        res = requests.get(r_url, headers=headers)

        if func(r_url) == 1:
            # name = r_url.split('/')[-1]
            # name = name.replace('.jpg', '')
            continue
        else:
            name = r_url.split('/')[4]
            name = name.split(',')[0]
            name = name.replace('u=', '')
        with open("baiduimg/" + name + ".jpg", mode="wb") as f:
            f.write(res.content)
            print(f'{name} over!')
        res.close()

    resp.close()
