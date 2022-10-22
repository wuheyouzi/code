import requests

url_f = "https://shiqianjiang.cn/home/image/bg"
url_e = ".webp"

headers = {
    'Accept': 'image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8',
    'Accept-Language': 'zh-CN,zh;q=0.9',
    'Connection': 'keep-alive',
    'Referer': 'https://shiqianjiang.cn/home/',
    'Sec-Fetch-Dest': 'image',
    'Sec-Fetch-Mode': 'no-cors',
    'Sec-Fetch-Site': 'same-origin',
    'User-Agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) '
                  'Chrome/103.0.0.0 Mobile Safari/537.36',
    'sec-ch-ua': '".Not/A)Brand";v="99", "Google Chrome";v="103", "Chromium";v="103"',
    'sec-ch-ua-mobile': '?1',
    'sec-ch-ua-platform': 'Android'
}

for i in range(9):
    a = str(i)
    if (i == 0):
        a = ''
    resp = requests.get(url_f + a + url_e, headers=headers, verify=False)
    with open("shiqianjiang/"+str(i)+".webp", mode="wb") as f:
        f.write(resp.content)

url = "https://shiqianjiang.cn/home/image/home.webp"
resp = requests.get(url, headers=headers, verify=False)
with open("shiqianjiang/"+"home.webp", mode="wb") as f:
        f.write(resp.content)

url = "https://shiqianjiang.cn/image/head.png"
resp = requests.get(url, headers=headers, verify=False)
with open("shiqianjiang/"+"head.webp", mode="wb") as f:
        f.write(resp.content)