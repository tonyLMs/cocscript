#include "phash.h"

// ����ͼ���·��
// ��֪��ϣ�㷨��ʵ��
string p_hash(Mat src) {

    // Step1. ��ͼ����СΪ 8 * 8
    resize(src, src, Size(8, 8), 0, 0, INTER_LINEAR);

    // Step2. ����64�����صĻҶȾ�ֵ
    double avg = mean(src)[0];

    // Step3. ��ƽ��ֵ�Ƚϣ�����01�ַ���
    string str = "";
    for (int i = 0; i < 8; i++) {
        unsigned char* data = src.ptr(i);
        for (int j = 0; j < 8; j++) {
            if (data[j] <= avg) {
                str += "0";
            }
            else {
                str += "1";
            }
        }
    }

    // Step4. �����ϣֵ
    string h = "";
    for (int i = 0; i < 61; i += 4) {
        string s = str.substr(i, 4);
        h += str_to_hex(s);
    }
    return h;
}


// �ַ���ת16����
string str_to_hex(string s) {
    string result = "";
    int num = 0, p = 3;
    for (int i = 0; i < 4; i++) {
        if (s[i] == '1') {
            num += pow(2, p);
        }
        p--;
    }
    if (num == 10) { // ����д�ú�������������
        result += "a";
    }
    else if (num == 11) {
        result += "b";
    }
    else if (num == 12) {
        result += "c";
    }
    else if (num == 13) {
        result += "d";
    }
    else if (num == 14) {
        result += "e";
    }
    else if (num == 15) {
        result += "f";
    }
    else {
        stringstream ss;
        ss << num;
        result += ss.str();
    }
    return result;
}


// ���㺺������
int hamming(string str1, string str2) {
    int count = 0;
    for (int i = 0; i < 16; i++) {
        if (str1[i] != str2[i]) {
            count++;
        }
	}
	return count;
}

int p_hash_hamming(Mat src1, Mat src2, bool is_open)
{
	if (is_open)
	{
		string str1 = p_hash(src1);
		string str2 = p_hash(src2);
		return hamming(str1, str2);
	}
	else
	{
        return 66;
    }
}