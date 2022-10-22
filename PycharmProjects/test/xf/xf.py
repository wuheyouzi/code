import requests

# url = "https://www.bs666.cn/style/img/logo.png"
# url = "https://www.bs666.cn/style/img/qq.jpg"
# url = "https://www.bs666.cn/style/img/bs.jpg"
url = "https://www.bs666.cn/style/img/1.png"

headers = {
    'referer': 'https://www.bs666.cn/'
}

resp = requests.get(url, headers=headers)
with open("1.png", "wb") as f:
    f.write(resp.content)
