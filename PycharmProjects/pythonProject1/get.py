import os
import pprint
import re
import json
import requests
from lxml import etree

if __name__ == "__main__":

    folder_list = os.listdir('./')
    for folder in folder_list:
        if folder.startswith('bili'):
            for json_name in os.listdir(folder):
                json_path = os.path.join('./', folder, json_name)
                if not os.path.exists(json_path):
                    print(json_path)
                with open(json_path, 'r', encoding='utf-8') as f:
                    dic = json.load(f)
                for i, (part_url, title) in enumerate(dic.items()):
                    # url_ = "https://www.bilibili.com/video/BV1BA411J7FP"
                    url_ = 'https://' + part_url
                    # #手动构造请求头的参数
                    headers = {
                        'User-Agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.41 Safari/537.36",
                        'Cookie': "_uuid=5153E88A-59D5-781D-382E-8722D512D26609183infoc; buvid4=3079BA34-505B-A455-7138-105AFF9641D796730-022020421-5tvc85fCeqioMaiBYlCXsw==; buvid3=A5F6E3E0-4F12-0EAB-FA6A-BA1FDD2E5BAC10673infoc; b_nut=1647424609; i-wanna-go-back=-1; nostalgia_conf=-1; CURRENT_BLACKGAP=0; rpdid=|(umkmJ~|uJ)0J'uYR~Rk)uRk; fingerprint=630aac0ea364ba115c3f563f8232e885; buvid_fp_plain=undefined; buvid_fp=630aac0ea364ba115c3f563f8232e885; DedeUserID=357527535; DedeUserID__ckMd5=c4c968312dfb7fc0; SESSDATA=6cb1c121,1667119652,5e3e4*51; bili_jct=237a9a39b192e826bde83bceae51fa8f; b_ut=5; blackside_state=0; CURRENT_QUALITY=64; sid=iq4xiym2; bp_video_offset_357527535=656217762427830300; bsource=search_baidu; innersign=1; PVID=4; CURRENT_FNVAL=4048; b_lsid=92764539_1808E9D6599",
                        'Referer': url_
                    }
                # # 对视频主页发送请求，获取响应
                response_ = requests.get(url_, headers=headers)
                html_ = response_.text
                # print(html_)
                tree = etree.HTML(html_)

                play_info = re.findall('<script>window.__playinfo__=(.*?)</script>', html_)[0]
                import json

                play_info_dic = json.loads(play_info)

                # pprint.pprint(play_info_dic)
                audio_url = play_info_dic['data']['dash']['audio'][0]['base_url']
                video_url = play_info_dic['data']['dash']['video'][0]['base_url']
                # print(audio_url)

                audio_content = requests.get(url=audio_url, headers=headers).content
                video_content = requests.get(url=video_url, headers=headers).content
                with open(folder + '/' + '{}.mp3'.format(part_url.replace('/', '_')), mode='wb') as f:
                    f.write(audio_content)
                with open(folder + '/' + '{}.mp4'.format(part_url.replace('/', '_')), mode='wb') as f:
                    f.write(video_content)
                print(
                    '{} is successfully downloaded!'.format(folder + '/' + '{}.mp4'.format(part_url.replace('/', '_'))))
