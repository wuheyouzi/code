import os

clear_temp_dir = ["C:\\Users\\鹅\\AppData\\Local\\Temp"]

img_dirList = ["E:\\img\\"]


def clear_temp():
    print("clearing temporary:")
    for path in clear_temp_dir:
        if os.path.exists(path):
            os.remove(path)
    print("--------------------------------")


def check_img():
    print("check_img:")
    for path in img_dirList:
        if os.path.exists(path):
            print(f' img_path: {path}')
            for file_name in os.listdir(path):
                if file_name.find(".") == -1:
                    os.remove(path + file_name)
                    print(f'clear: {path}')
    print("--------------------------------")


if __name__ == '__main__':
    check_img()
    clear_temp()
