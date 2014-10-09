#include<iostream>
#include<cstdio>
#include<map>
using namespace std;

/***
 * Psuedo Random Number Generator
 */
class PRNGen
{
public:
	PRNGen(int N, int S, int W)
	:_N(N), _g(S), _W(W)
	{
		_arr = new int[N];
		for(int i = 0 ; i < _N ; i ++)
			_arr[i] = _next();
	}

	int next()
	{
		return _arr[--_N];
	}

	~PRNGen()
	{
		delete _arr;
	}
private:
	int _g, _W, _N;
	int *_arr;

	int _next()
	{
		int ai = (_g/7)%10;
		if(_g%2 == 0) _g /= 2;
		else _g = (_g/2) ^ _W;
		return ai;
	}
};

/***
 * @param	mask	is trail divisible by Q
 */
int calSpecialCase(int N, int mask, PRNGen& prng)
{
	int res = 0, s = 0;
	for(int i = 0 ; i < N ; i ++)
	{
		int d = prng.next();

		if(mask & (1<<d))
			s ++;

		if(d != 0)
			res += s;
	}
	return res;
}

int calNormalCase(int N, int Q, PRNGen& prng)
{
	map<int, int> statis;
	statis[0] = 1;
	int res = 0;
	// prefix sum
	int pre = 0, pow10 = 1;
	for(int i = 0 ; i < N ; i ++, (pow10 *= 10) %= Q)
	{
		int d = prng.next();
		(pre += d*pow10) %= Q;
		if(d != 0)
			res += statis[pre];
		statis[pre] ++;
	}
	return res;
}

int main(int argc, const char *argv[])
{
	int N, S, W, Q;
	while(~scanf("%d %d %d %d", &N, &S, &W, &Q) && (N||S||W||Q))
	{
		PRNGen prng(N, S, W);
		if(Q == 2)
			printf("%d\n", calSpecialCase(N, 0x155, prng));
		else if(Q == 5)
			printf("%d\n", calSpecialCase(N, 0x21, prng));
		else
			printf("%d\n", calNormalCase(N, Q, prng));
	}
	return 0;
}
