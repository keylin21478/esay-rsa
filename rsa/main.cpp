//rsa����������㷨
#include<iostream>
#include<math.h>
#include<cstdlib>
#include<ctime>
using namespace std;

int a[1000];

//��չgcd
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
//��a��ģm�µĳ˷���Ԫ
ll mod_inverse(ll a, ll m) {
	ll x, y;
	if (exgcd(a, m, x, y) == 1)//ax+my=1
		return (x%m + m) % m;
	return -1;//������
}

// �ж��Ƿ�Ϊ����
int prime_number_judge(int k) {
	int i;
	if (k == 2 || k == 1 || k == 0) return 0;

	for (i = 2; i <= sqrt(k); i++)
	{
		if (k % i == 0) return 0;
	}

	return 1;
}
// �õ� n ֵ
int get_n(int p, int q) {
	return q * p;
}
//�õ�  n  ��ŷ������ֵ	
int get_Euler_of_n(int p, int q) {
	return (p - 1)*(q - 1);
}
/* �����������Ʒ�����ŷ������㷨���������Լ�� */
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
//���ѡȡ��Կ���� e
int get_e(int k) {
	//��һ���õ������䣨1�� k������ �� k �������Ϊ 1 ����
	int h = 0;
	for (int i = 2; i <= k; i++) {
		if (gcd(i, k) == 1)
		{
			a[h] = i;//��������������i��
			h++;	 //�����˲��裬a[0]~a[h - 1]���Ƿ��������Ĵ������� e
		}
	}
	cout << "Ŀǰ��ѡ��Ĺ�Կ����e����" << endl;
	int m;
	for (m = 0; m <= h - 1; m++) {
		if (m == h - 1) { cout << a[m] << endl; }
		else { cout << a[m] << " "; }
	}

	cout << "����Ҫָ����Կ����e�𣿣�����1��ʾ�룬0��ʾ���룩" << endl;


	int ok; cin >> ok;
	if (ok) {
		cout << "������ָ���Ĳ���e" << endl;
		int e;
		cin >> e;
		return e;
	}
	else {
		// �ڶ������������� ���ѡȡȷ���� ��Կ���� e
		srand((unsigned)time(NULL));
		int r = rand() % (h);
		cout << "���ѡ���Ĳ���eΪ" << a[r] << endl;
		return a[r];
	}

}
//������ȡģ a ^ b % c
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
	//��һ��������������
	while (i != 2) {
		cout << "������һ��������" << endl;
		int p;
		cin >> p;
		if (prime_number_judge(p)) {
			cout << "�����" << p << "��ȷ" << endl;
			b[i] = p;
			i++;
		}
	}
	//�ڶ����õ� n�� U��n��	
	int n = get_n(b[0], b[1]); cout << "n=" << n << endl;
	int Q = get_Euler_of_n(b[0], b[1]); cout << "Q=" << Q << endl;;
	//������ �õ� e;
	int e = get_e(Q);  /* e = 3;*/ cout << "e=" << e << endl;;
	//�õ� e ��ģ	 Q�µĳ˷���Ԫ
	int d = mod_inverse(e, Q);
	// ��ʱ ��{e,n}Ϊ����Կ,{d,n}Ϊ����Կ
	cout << "��ԿΪ" << "[" << e << "," << n << "]" << endl;
	cout << "˽ԿΪ" << "[" << d << "," << n << "]" << endl;
	cout << "��Ҫ���ܵ���Ϣ" << endl;
	int msg;
	cin >> msg;
	int encryption = PowerMod(msg, e, n);
	cout << "������" << encryption << endl;
	return 0;

}
int main() {

	start();
	system("pause");
	return 0;
}