import requests
import re
import os
from concurrent.futures import ThreadPoolExecutor

url = "https://inis.cn/"

if url.endswith("/"):
    files_path = url.split("/")[-2]
else:
    files_path = url.split("/")[-1]


def download_pic(pic_url):
    global files_path

    files_path_pic = files_path + "/pictures"

    if not os.path.exists(files_path_pic):
        os.makedirs(files_path_pic)

    if os.path.exists(f'{files_path_pic}/{pic_url.split("/")[-1]}'):
        return

    resp_pic = ""
    for i in range(5):
        try:
            resp_pic = requests.get(pic_url)
            break
        except Exception as e:
            print(f'Error getting pic {pic_url} - trying e: {e}')
            resp_pic = ""
            continue
    if resp_pic == "":
        return
    with open(f'{files_path_pic}/{pic_url.split("/")[-1]}', "wb") as f:
        f.write(resp_pic.content)

    print("Downloading {} over!".format(pic_url))


if __name__ == '__main__':
    resp = requests.get(url)

    re = re.compile(f'".*?(?P<picture>.*?)"', re.S)
    res = re.finditer(resp.text)

    pic = set()
    for item in res:
        p_url = item.group("picture")

        if not p_url.endswith(".jpg") and not p_url.endswith(".png") and not p_url.endswith(".webp"):
            continue
        if p_url.startswith("/"):
            p_url = p_url[1:]
            p_url = url + p_url
        if p_url.startswith("./"):
            p_url = url + p_url[2:]
        print(p_url)
        pic.add(p_url)

    with ThreadPoolExecutor(1000) as thread_pool:
        for item in pic:
            thread_pool.submit(download_pic(item))

