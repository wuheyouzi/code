import getBilibiliVideo
import download
import os

Path = {
    "flvPath": "flv\\",
    "mp4Path": "mp4\\"
}

count = 1


def flvToMp4():
    open(mp4FilePath, 'w')
    os.system(f'del {mp4FilePath}')
    os.system(f'ffmpeg\\bin\\ffmpeg.exe -i {flvFilePath} -y -vcodec copy -acodec copy {mp4FilePath}')


if __name__ == '__main__':
    url = input("url链接：")
    BV = url.split("?")[-2].split("/")[-1]
    print(BV)
    videoUrl = f'https://www.bilibili.com/video/{BV}'
    flvFilePath = f'{Path.get("flvPath")}{BV}.flv'
    mp4FilePath = f'{Path.get("mp4Path")}{BV}.mp4'
    while True:
        try:
            real_url = getBilibiliVideo.main(videoUrl)
            download.thread(real_url, videoUrl, BV, flvFilePath, mp4FilePath)
            flvToMp4()
            if os.path.exists(mp4FilePath):
                break
            raise Exception('flv转换mp4失败，flv文件不存在或损坏。将重新获取flv文件')
        except Exception as e:
            print(e)
            continue