import pandas as pd
import matplotlib.pyplot as plt
import os

# パスの設定（スクリプトから見た相対パスではなく、プロジェクトルートからの実行を想定）
csv_path = "results/result.csv"
img_path = "results/mse_comparison.png"

# ファイルがあるか確認
if not os.path.exists(csv_path):
    print(f"Error: {csv_path} not found. Did you run the simulation?")
    exit(1)

# 1. CSVファイルを読み込む
df = pd.read_csv(csv_path)

# 2. グラフの設定
plt.figure(figsize=(10, 6))
plt.title("Comparison of MSE: Mean-based vs Max-based Estimators", fontsize=16)
plt.xlabel("Sample Size (n)", fontsize=14)
plt.ylabel("Mean Squared Error (MSE)", fontsize=14)
plt.grid(True, which="both", linestyle="--", alpha=0.7)

# 3. プロット
plt.plot(df["n"], df["mse_mom"], label="MOM (Mean-based Unbiased)", 
         color="gray", linestyle="--", marker="x")
plt.plot(df["n"], df["mse_umvue"], label="UMVUE (Max-based Unbiased)", 
         color="blue", marker="o", linewidth=2)
plt.plot(df["n"], df["mse_bayes"], label="Bayes (Max-based Min-MSE)", 
         color="red", marker="*", linewidth=2)

# 4. 保存
plt.legend(fontsize=12)
plt.savefig(img_path)
print(f"Graph saved to {img_path}")
# plt.show() # サーバー環境などでエラーになる場合はコメントアウト推奨