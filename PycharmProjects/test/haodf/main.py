import requests
import re

url = "https://www.haodf.com/bingcheng/list.html"

headers = {
     'user-agent': 'Mozilla/5.0 (iPhone; CPU iPhone OS 13_2_3 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.3 Mobile/15E148 Safari/604.1'
}

resp = requests.get(url, headers=headers)
rest = re.compile('.*?<a href="(?P<question_url>.*?)".*?<a class="fl" href="(?P<doctor_url>.*?)".*?', re.S)
reply = rest.finditer(resp.text)

for item in reply:
    print(item.group("question_url"), item.group("doctor_url"))
