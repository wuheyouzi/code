#include <string>
#include <iostream>

std::string curlToObject(std::string s) {
    // ɾ����һ��
    for (int i = 1; i <= 2; i++) {
        int pos = s.find("\'");
        s.erase(0, pos + 1);
    }

    // ��Ҫɾ���Ĳ���
    std::string cut[] = { "curl", "\\", "-H", "--compressed", "\n" };
    for (int i = 0; i < cut->length(); i++) {
        int pos = s.find(cut[i]);
        while (pos != std::string::npos) {
            s.erase(pos, cut[i].size());
            pos = s.find(cut[i]);
        }
    }

    // ���ݴ�����������ַ����ĸ�ʽ
//    std::replace(s.begin(), s.end(), '\'', '\"');
    int pos = s.find('\'');
    while (pos != -1) {
        s[pos] = '\"';
        pos = s.find('\'');
    }

    // ɾβ���ո�
    while (/*!s.ends_with('\"')*/ s[s.size() - 1] != '\"') {
        s.erase(s.size() - 1, 1);
    }

    // :���߼�""����β�Ӷ���
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ':') {
            if (s[i + 1] != ' ') continue;
            s.insert(i, "\"");
            s.insert(i + 3, "\"");
            int start = i + 4;
            while (start < s.size() - 1) {
                if (s[start] == '\"') {
                    s.insert(start + 1, ",");
                    break;
                }
                start++;
            }
            i++;
        }
    }


    // �����Ÿ�ʽ��
    s.insert(0, "{");
    s.append("\n");
    s.append("}");

    return s;
}

std::string readCurl() {
    std::string s = "", t;
    while (true) {
        getline(std::cin, t);
        t += '\n';
        s += t;
        if (t.find("--compressed") != std::string::npos) {
            break;
        }
    }
    return s;
}

int main() {
    std::string s = readCurl();
    std::cout << std::endl;
    std::cout << curlToObject(s) << std::endl;
    std::cin.get();
}

