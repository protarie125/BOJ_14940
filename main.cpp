#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

constexpr auto Inf = int{ 987'654'321 };

int n, m;
vvi field;
pii start;
vvi dist;

const auto dx = vi{ -1,1,0,0 };
const auto dy = vi{ 0,0,-1,1 };

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m;
	field = vvi(n, vi(m));
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			cin >> field[i][j];
			if (2 == field[i][j]) {
				start = { i, j };
			}
		}
	}

	dist = vvi(n, vi(m, Inf));
	dist[start.first][start.second] = 0;

	using Node = pair<int, pii>;
	auto q = priority_queue <Node, vector<Node>, greater<Node>>{};
	q.push({ 0, start });

	while (!q.empty()) {
		const auto [wd, pos] = q.top();
		q.pop();

		const auto& [y, x] = pos;

		for (auto d = 0; d < 4; ++d) {
			const auto& nx = x + dx[d];
			const auto& ny = y + dy[d];

			if (nx < 0 || m <= nx ||
				ny < 0 || n <= ny) {
				continue;
			}

			if (0 == field[ny][nx]) {
				continue;
			}

			const auto& ndist = wd + 1;
			if (ndist < dist[ny][nx]) {
				dist[ny][nx] = ndist;

				q.push({ ndist, { ny, nx } });
			}
		}
	}

	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < m; ++j) {
			if (0 == field[i][j]) {
				dist[i][j] = 0;
			}

			cout << (Inf != dist[i][j] ? dist[i][j] : -1) << ' ';
		}
		cout << '\n';
	}

	return 0;
}