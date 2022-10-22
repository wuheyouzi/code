from time import sleep

import getCollect
import getBilibiliVideo
import download
import os

Path = {
    "listPath": "E:\\video\\list.txt",
    "flvPath": "E:\\video\\flv\\",
    "mp4Path": "E:\\video\\mp4\\"
}

writeMode = "r+b"
journalMode = "a+"

count = 1


def journal():
    with open(Path.get("listPath"), journalMode, encoding="utf-8") as f:
        f.write(f'bv_id: {item["bv_id"]}\n')
        f.write(f'  bv_url: {videoUrl}\n')
        f.write(f'  title: {item["title"]}\n')
        f.write(f'  upper: \n')
        f.write(f'    name: {item["upper"]["name"]}\n')
        f.write(f'    mid: {item["upper"]["mid"]}\n')
        f.write('\n')


def flvToMp4():
    open(mp4FilePath, 'w')
    os.system(f'del {mp4FilePath}')
    os.system(f'ffmpeg -i {flvFilePath} -y -vcodec copy -acodec copy {mp4FilePath}')


if __name__ == '__main__':
    while True:
        collectList = getCollect.main()
        for item in collectList:
            videoUrl = f'https://www.bilibili.com/video/{item["bv_id"]}'
            flvFilePath = f'{Path.get("flvPath")}{item["bv_id"]}.flv'
            mp4FilePath = f'{Path.get("mp4Path")}{item["bv_id"]}.mp4'

            if os.path.exists(flvFilePath):
                if os.path.exists(mp4FilePath):
                    continue
                try:
                    flvToMp4()
                    if os.path.exists(mp4FilePath):
                        continue
                    raise Exception('flv转换mp4失败，flv文件不存在或损坏。将重新获取flv文件')
                except Exception as e:
                    print(e)

            while True:
                try:
                    real_url = getBilibiliVideo.main(videoUrl)
                    download.thread(real_url, videoUrl, item["bv_id"], flvFilePath, mp4FilePath)
                    flvToMp4()
                    if os.path.exists(mp4FilePath):
                        break
                    raise Exception('flv转换mp4失败，flv文件不存在或损坏。将重新获取flv文件')
                except Exception as e:
                    print(e)
                    continue

            journal()
        print("waiting for events...")
        sleep(10)
