import requests
import json


def main():

    count = 1
    collectList = []

    while True:
        url = f'https://api.bilibili.com/x/v3/fav/resource/list?media_id=1731150707&pn={count}&ps=20&keyword=&order=mtime' \
              '&type=0&tid=0&platform=web&jsonp=jsonp'
        resp = requests.get(url)

        medias = ""
        try:
            json_text = json.loads(resp.text)
            medias = json_text['data']['medias']
        except Exception as e:
            print(e)
            exit(1)

        if medias is None:
            return collectList

        collectList += medias

        count += 1
