//rsa加密与解密算法
#include<iostream>
#include<math.h>
#include<cstdlib>
#include<ctime>
using namespace std;

int a[1000];
//扩展gcd
typedef long long ll;
ll exgcd(ll l, ll r, ll &x, ll &y)
{
	if (r == 0) { x = 1; y = 0; return l; }
	else
	{
		ll d = exgcd(r, l%r, y, x);
		y -= l / r * x;
		return d;
	}
}
//求a在模m下的乘法逆元
ll mod_inverse(ll a, ll m) {
	ll x, y;
	if (exgcd(a, m, x, y) == 1)//ax+my=1
		return (x%m + m) % m;
	return -1;//不存在
}

// 判断是否为质数
int prime_number_judge(int k) {
	int i;
	if (k == 2 || k == 1 || k == 0) return 0;

	for (i = 2; i <= sqrt(k); i++)
	{
		if (k % i == 0) return 0;
	}

	return 1;
}
// 得到 n 值
int get_n(int p, int q) {
	return q * p;
}
//得到  n  的欧拉函数值	
int get_Euler_of_n(int p, int q) {
	return (p - 1)*(q - 1);
}
/* 迭代法（递推法）：欧几里得算法，计算最大公约数 */
int gcd(int m, int n)
{
	while (m>0)
	{
		int c = n % m;
		n = m;
		m = c;
	}
	return n;
}
//随机选取公钥参数 e
int get_e(int k) {
	//第一步得到开区间（1， k）所有 与 k 最大公因数为 1 的数
	int h = 0;
	for (int i = 2; i <= k; i++) {
		if (gcd(i, k) == 1)
		{
			a[h] = i;//保留符合条件的i；
			h++;	 //经过此步骤，a[0]~a[h - 1]才是符合条件的待定参数 e
		}
	}
	cout << "目前可选择的公钥参数e如下" << endl;
	int m;
	for (m = 0; m <= h - 1; m++) {
		if (m == h - 1) { cout << a[m] << endl; }
		else { cout << a[m] << " "; }
	}

	cout << "你想要指定公钥参数e吗？（输入 0 or 1）" << endl;
	int ok; cin >> ok;
	if (ok) {
		int e;
		cin >> e;
		return e;
	}
	else {
		// 第二步，从数组中 随机选取确定的 公钥参数 e
		srand((unsigned)time(NULL));
		int r = rand() % (h);
		return a[r];
	}

}
//快速幂取模 a ^ b % c
int PowerMod(int a, int b, int c)
{
	int ans = 1;
	a = a % c;
	while (b>0) {
		if (b % 2 == 1)
			ans = (ans * a) % c;
		b = b / 2;
		a = (a * a) % c;
	}
	return ans;
}
int start() {
	int i = 0;
	int b[10];
	//第一步输入两个素数
	while (i != 2) {
		cout << "请输入一个大素数" << endl;
		int p;
		cin >> p;
		if (prime_number_judge(p)) {
			cout << "输入的" << p << "正确" << endl;
			b[i] = p;
			i++;
		}
	}
	//第二步得到 n和 U（n）	
	int n = get_n(b[0], b[1]); cout << "n=" << n << endl;
	int Q = get_Euler_of_n(b[0], b[1]); cout << "Q=" << Q << endl;;
	//第三步 得到 e;
	int e = get_e(Q);  /* e = 3;*/ cout << "e=" << e << endl;;
	//得到 e 在模	 Q下的乘法逆元
	int d = mod_inverse(e, Q);
	// 此时 以{e,n}为公开钥,{d,n}为秘密钥
	cout << "公钥为" << "[" << e << "," << n << "]" << endl;
	cout << "私钥为" << "[" << d << "," << n << "]" << endl;
	cout << "想要加密的信息" << endl;
	int msg;
	cin >> msg;
	int encryption = PowerMod(msg, e, n);
	cout << "密文是" << encryption << endl;
	return 0;


}
int main() {

	start();
	system("pause");
	return 0;
}