# ==========================================
# 変数定義
# ==========================================
NAME        = estimator
CXX         = c++
# C++11以上を指定(必須)。-O3で計算速度を爆速にする
CXXFLAGS    = -Wall -Wextra -Werror -std=c++11 -O3
SRCS        = src/estimator.cpp
OBJS        = $(SRCS:.cpp=.o)

# ==========================================
# ルール定義
# ==========================================
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

# .cpp から .o を作るルール
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	# CSVファイルが出力されていたら消す場合（お好みでコメントアウト外して）
	# rm -f result.csv

re: fclean all

.PHONY: all clean fclean re