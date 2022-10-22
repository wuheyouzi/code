import requests
import threading
import datetime
import time


def thread(url, Referer, BV, flvFilePath, mp4FilePath):

    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                      'Chrome/83.0.4103.61 Safari/537.36',
        'Referer': Referer
    }

    r = requests.get(url, headers=headers, stream=True, timeout=30)
    all_thread = 1
    # 获取视频大小
    file_size = int(r.headers['content-length'])
    # 如果获取到文件大小，创建一个和需要下载文件一样大小的文件
    if file_size:
        print('视频大小：' + str(int(file_size / 1024 / 1024)) + "MB")
    # 每个线程每次下载大小
    size = 5242880
    # 当前文件大小需大于5M
    if file_size > size:
        # 获取总线程数
        all_thread = int(file_size / size)
    part = file_size // all_thread
    threads = []
    startTime = datetime.datetime.now().replace(microsecond=0)
    for i in range(all_thread):
        # 获取每个线程开始时的文件位置
        start = part * i
        # 获取每个文件结束位置
        if i == all_thread - 1:
            end = file_size
        else:
            end = start + part
        if i > 0:
            start += 1
        headers = headers.copy()
        headers['Range'] = "bytes=%s-%s" % (start, end)
        t = threading.Thread(target=Handler, name='线程-' + str(i),
                             kwargs={'start': start, 'end': end, 'url': url, 'filePath': flvFilePath, 'headers': headers})
        t.setDaemon(True)
        threads.append(t)
    open(flvFilePath, 'w')
    # 线程开始
    for t in threads:
        t.start()
    # 等待所有线程结束
    print('正在下载……')
    for t in threads:
        t.join()
    endTime = datetime.datetime.now().replace(microsecond=0)

    print('下载完成！用时：%s' % (endTime - startTime))


def Handler(start, end, url, filePath, headers=None):
    if headers is None:
        headers = {}
    tt_name = threading.current_thread().getName()
    print(tt_name + ' 已启动')
    r = requests.get(url, headers=headers, stream=True)
    total_size = end - start
    downsize = 0
    startTime = time.time()
    with open(filePath, 'r+b') as fp:
        fp.seek(start)
        fp.tell()
        for chunk in r.iter_content(204800):
            if chunk:
                fp.write(chunk)
                downsize += len(chunk)
                line = tt_name + '-downloading %d KB/s - %.2f MB， 共 %.2f MB'
                line = line % (
                    downsize / 1024 / (time.time() - startTime), downsize / 1024 / 1024,
                    total_size / 1024 / 1024)
                print(line, end='\r')
