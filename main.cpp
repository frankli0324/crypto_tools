#include"encoding.h"
#include<iostream>
using namespace std;
int test() {
	//urlencode test
	//string a = UrlEncode::encode("https://blog.csdn.net/gemo/article/details/8468311");
	//cout << a << endl;
	cout << UrlEncode::decode("%59%69%70%70%65%68%21%20%59%6F%75%72%20%55%52%4C%20%69%73%20%63%68%61%6C%6C%65%6E%67%65%2F%74%72%61%69%6E%69%6E%67%2F%65%6E%63%6F%64%69%6E%67%73%2F%75%72%6C%2F%73%61%77%5F%6C%6F%74%69%6F%6E%2E%70%68%70%3F%70%3D%72%65%6F%67%6F%6F%72%63%61%6E%65%64%26%63%69%64%3D%35%32%23%70%61%73%73%77%6F%72%64%3D%66%69%62%72%65%5F%6F%70%74%69%63%73%20%56%65%72%79%20%77%65%6C%6C%20%64%6F%6E%65%21") << endl;
	
	//base64 test    最好拿python
	string a = Base64::encode("oaijd");
	cout << a << endl;
	cout << Base64::decode(a) << endl;

	//fence test
	//注意：fence中的第二个参数表示<加密后>每个单元的字符数
	cout << Fence::encode("Thequickbrownfoxjumpsoverthelazydog", 17, true) << endl;
	cout << Fence::decode("Teucbonojmsvrhlzdghqikrwfxupoeteayo", 17, true) << endl;
	vector<string>aaa = Fence::auto_decode("tn c0afsiwal kes,hwit1r  g,npt  ttessfu}ua u  hmqik e {m,  n huiouosarwCniibecesnren.");
	for (int i = 0; i < aaa.size(); i++)cout << "possible solution" << i << ":  " << aaa[i] << endl;

	//rot series
	//rot5 将每个数位向前旋转5位，即每一位i=(i+5)%10
	//rot13 对每个字母进行类似操作
	//rot18 对每个数字和字母进行类似操作
	//rot47 对每个ascii码在33-126间的字符进行类似操作

	vector<string>aa = Caesar::decode_listall("PDA MQEYG XNKSJ BKT FQILO KRAN PDA HWVU ZKC KB YWAOWN WJZ UKQN QJEMQA OKHQPEKJ EO YLLODLXHJEYY");
	for (int i = 0; i < aa.size(); i++)cout << i << ":::" << aa[i] << endl;

	cout << ASCII::decode("84, 104, 101, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 105, 115, 58, 32, 103, 103, 104, 98, 98, 103, 109, 115, 109, 101, 108, 98");
}

int main() {

}