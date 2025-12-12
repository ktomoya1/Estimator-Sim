#include <iostream>
#include <vector>
#include <random>
#include <cmath>

int main () {
	// 入力
	// 引数１：真のパラメータθ（例1.0）
	// 引数２：思考回数K（例：100,000回以上推奨）
	// 引数３：サンプルサイズnの範囲（n=1からn=20までループ）

	double theta;
	int K, N;
	std::cin >> theta >> K >> N;

	// パソコンのハードウェア情報を使って、毎回違う種を作る
	std::random_device seed_gen;
	// 乱数を作るエンジン（メルセンヌ・ツイスタ）
	// さっき作った種を渡して、エンジンを初期化する
	std::mt19937 engine(seed_gen());
	// 分布を決める（0.0からthetaまで）
	std::uniform_real_distribution<double> dist(0.0, theta);

	std::cout << "n,mse_mom,mse_bayes,mse_umvue" << std::endl;
	for (int n = 1; n <= N; n++) {
		double sse_mom = 0;
		double sse_bayes = 0;
		double sse_umvue = 0;
		for (int k = 0; k < K; k++) {
			// サンプルサイズn個分だけ乱数を作る (X1...Xn)
			double x_sum = 0;
			double x_max = 0;
			for (int i = 0; i < n; i++) {
				double x = dist(engine);
				x_sum += x;
				x_max = fmax(x_max, x);
			}
			// その乱数群から「たった一つの推定量(θ_hat)」を計算する
			double theta_mom = 2.0 / static_cast<double>(n) * x_sum;
			double theta_bayes = (n + 2.0) / (n + 1.0) * x_max;
			double theta_umvue = (n + 1.0) / static_cast<double>(n) * x_max;
	
			// 誤差計算（ループしない）　「今回の推定量(θ_hat) - 真の正解(θ)を引く
			// 2乗して合計変数に足す
			sse_mom += std::pow(theta_mom - theta, 2);
			sse_bayes += std::pow(theta_bayes - theta, 2);
			sse_umvue += std::pow(theta_umvue - theta, 2);
		}
		// 誤差の平均をとる
		double mse_mom = sse_mom / K;
		double mse_bayes = sse_bayes / K;
		double mse_umvue = sse_umvue / K;
		std::cout << n << "," << mse_mom << "," << mse_bayes << "," << mse_umvue << std::endl;
	}

	return 0;
}