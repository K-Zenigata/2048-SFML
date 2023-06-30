
#include "../include/GameFrame.hpp"
#include "../include/KeyHandler.hpp"
#include "../include/Panel.hpp"

class Game {
   public:
    sf::RenderWindow window;

    KeyHandler myKey;
    bool keyState = false;

    GameFrame myFrame;
    int grid[4][4] = {0};
    int tempGrid[4][4] = {0};

    const int START_NUMBER = 2;

    // pair<Vector2i, Vector2i>型とint型のpairを要素として持つvector
    std::vector<std::pair<std::pair<sf::Vector2i, sf::Vector2i>, int>> moves;

    // animation用 //
    sf::Clock animeClock;
    bool animation = false;

    // 移動完了までにかかる時間 //
    const float ANIMATION_DURATION = 0.15;

    // timer用 //
    sf::Clock gameClock;

    // space key が押されたら、timer を、スタート //
    bool gStart = false;

    // タイマーの、run, stop
    bool gTimer = false;
    
    sf::Time timer;
    std::string formattedSeconds;


    bool gameOver = false;
    bool gameClear = false;

    Game() : window(sf::VideoMode(gh::WINDOW_W, gh::WINDOW_H), "2048!") {
 
        // 最初は、新しいパネルを2枚用意 //
        createNewPanel();
        createNewPanel();
    }

    // 移動中のパネルを描画 //
    void drawMovePanel() {
        Panel mPanel;

        // 左上のパネルの座標
        sf::Vector2i gOffset(gh::OFFSET_X, gh::OFFSET_Y);

        for (int i = 0; i < moves.size(); i++) {
            // 移動が完了するまで、今どのくらいなのか //
            float movePercent = (animeClock.getElapsedTime().asSeconds() / ANIMATION_DURATION);

            sf::Vector2i f = moves[i].first.first;   // 現在のポジション //
            sf::Vector2i t = moves[i].first.second;  // 移動先のポジション //

            // 現在の数値、移動が完了するまでは、現在の数値が表示される //
            int num = moves[i].second;

            // 深く考えない。ちょっとずつ移動する為 //
            sf::Vector2f curPos = sf::Vector2f(f) + sf::Vector2f(t - f) * movePercent;

            // ポジションに、パネルのサイズと位置を考慮 //
            float x = curPos.x * (mPanel.SIZE + gh::MARGIN) + gh::OFFSET_X;
            float y = curPos.y * (mPanel.SIZE + gh::MARGIN) + gh::OFFSET_Y;

            // panel class の関数に渡して、表示してもらう //
            mPanel.SetGamePanel(x, y, num);
            mPanel.draw(window);
        }

        // アニメーションが終了したら //
        if (animeClock.getElapsedTime().asSeconds() >= ANIMATION_DURATION) {
            // animation 終了で、新しい数値を格納 //
            for (int y = 0; y < gh::ROWS; y++) {
                for (int x = 0; x < gh::COLS; x++) {
                    grid[y][x] = tempGrid[y][x];
                }
            }

            animation = false;

            // movePanel() で得た情報は、ここで消去 //
            moves.clear();

            // 新たなるパネルをセット //
            createNewPanel();
        }
    }

    // パネルの描画
    void drawBoard() {
        Panel panel;
        for (int y = 0; y < gh::ROWS; y++) {
            for (int x = 0; x < gh::COLS; x++) {
                int num = grid[y][x];

                // animation時は、すべてのパネルを0として描画 //
                // 0の時は、数値が描画されないので、移動中のパネルの邪魔をしない //
                if (animation) num = 0;

                panel.SetGamePanel(x * (panel.SIZE + gh::MARGIN) + gh::OFFSET_X, y * (panel.SIZE + gh::MARGIN) + gh::OFFSET_Y, num);

                panel.draw(window);

                // game clear //
                if (grid[y][x] == 2048) {
                    gameClear = true;
                    gTimer = false;
                }
            }
        }

        if (moves.size()) drawMovePanel();
    }

    // 新しいパネルをセット //
    void createNewPanel() {
        std::vector<sf::Vector2i> availablePoint;

        // 空白のマスを探す //
        for (int y = 0; y < gh::ROWS; y++) {
            for (int x = 0; x < gh::COLS; x++) {
                if (!grid[y][x]) {
                    availablePoint.push_back({x, y});
                }
            }
        }

        // 全てのマスが埋まってしまったら、ゲームオーバー //
        if (!availablePoint.size()) {
            gameOver = true;
            gTimer = false;
            return;
        }

        // 空白のマスを、ランダムに選ぶ //
        sf::Vector2i temp = availablePoint[rand() % availablePoint.size()];

        grid[temp.y][temp.x] = START_NUMBER;
    }

    // アニメーションに必要な情報を取得する関数 //
    void movePanel(int dx, int dy) {
        // 先ずは、移動前のパネルの数値を格納 //
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                tempGrid[y][x] = grid[y][x];
            }
        }

        for (int y = 0; y < 4; y++) {
            std::vector<sf::Vector2i> fromPos;  // 現在のポジション
            std::vector<sf::Vector2i> toPos;    // 移動先のポジション
            std::vector<int> srcNum;            // 現在のパネルの数値
            std::vector<int> before;            //
            std::vector<int> after;

            for (int x = 0; x < 4; x++) {
                if (dx == -1 || dx == 1) {  // 左右 //
                    if (tempGrid[y][x]) {
                        // 0以外の数値が入る //
                        before.push_back(tempGrid[y][x]);

                        // 現在のポジションを入れる //
                        fromPos.push_back({x, y});

                        // 座標の数値を入れる
                        srcNum.push_back(tempGrid[y][x]);
                    }
                } else {  // 上下 (x, y) が逆になるので注意 //
                    if (tempGrid[x][y]) {
                        // 0以外の数値が入る //
                        before.push_back(tempGrid[x][y]);

                        // 現在のポジションを入れる //
                        fromPos.push_back({y, x});

                        // 座標の数値を入れる
                        srcNum.push_back(tempGrid[x][y]);
                    }
                }
            }

            // right, down の時は配列を反転 //
            if (dx == 1 || dy == 1) {
                reverse(before.begin(), before.end());
            }

            // ここで強制的にlengthを5にする //
            while (before.size() < 5) {
                // before 頭に0がある時は、全部0の時だけ。//
                // before 数値との間に0は、無い。//
                // 例: 00000, 84200, 22000 20000 な感じ //
                before.push_back(0);
            }

            for (int i = 0; i < 4; i++) {
                int current = before[i];
                int next = before[i + 1];

                // 0の時は、いっさい登録されない //
                if (!current) break;

                // 同じ数値が並んだ場合 //
                if (next && current == next) {
                    after.push_back(current + next);

                    // 移動先の配列に、同じポジションが2つ入る
                    if (dx == -1) {
                        toPos.push_back({i, y});
                        toPos.push_back({i, y});
                    } else if (dx == 1) {
                        // 3 は配列の要素の一番最後,
                        // 仮にiが0ならば、xは、3で、一番右にくる
                        toPos.push_back({3 - i, y});
                        toPos.push_back({3 - i, y});
                    } else if (dy == -1) {
                        toPos.push_back({y, i});
                        toPos.push_back({y, i});
                    } else if (dy == 1) {
                        toPos.push_back({y, 3 - i});
                        toPos.push_back({y, 3 - i});
                    }

                    // 合体したので next を削除 //
                    before.erase(cbegin(before) + i + 1);

                } else {
                    // 数値が並ばなかった時は、そのまま
                    after.push_back(current);

                    if (dx == -1) {
                        toPos.push_back({i, y});
                    } else if (dx == 1) {
                        toPos.push_back({3 - i, y});
                    } else if (dy == -1) {
                        toPos.push_back({y, i});
                    } else if (dy == 1) {
                        toPos.push_back({y, 3 - i});
                    }
                }
            }

            // ここで強制的にlengthを4にする //
            while (after.size() < 4) {
                // 例: 0000, 8420, 2200 2000 な感じ //
                after.push_back(0);
            }

            // right, down の時は反転 //
            if (dx == 1 || dy == 1) {
                // 数値の配列を反転 //
                reverse(after.begin(), after.end());

                // ポジションの配列を反転 //
                reverse(toPos.begin(), toPos.end());
            }

            // 新しい数値を格納 //
            for (int i = 0; i < 4; i++) {
                if (dx == -1 || dx == 1) {  // 左右 //
                    tempGrid[y][i] = after[i];
                } else {  // 上下 //
                    tempGrid[i][y] = after[i];
                }
            }

            // animation用の情報を格納 //
            for (int i = 0; i < fromPos.size(); i++) {
                // moves {{現在のポジション, 移動先のポジション}, 現在の数値}
                moves.push_back(std::make_pair(std::make_pair(fromPos[i], toPos[i]), srcNum[i]));
            }
        }

        animation = true;
        animeClock.restart();
    }

    void processInput() {
        if (gameClear || gameOver || animation) return;

        if (!keyState && gTimer) {
            if (myKey.left) {
                movePanel(-1, 0);
            } else if (myKey.right) {
                movePanel(1, 0);
            } else if (myKey.up) {
                movePanel(0, -1);
            } else if (myKey.down) {
                movePanel(0, 1);
            }
        }

        // keyの押しっぱなしを不可にする //
        if (!myKey.left && !myKey.right && !myKey.up && !myKey.down) keyState = false;
    }

    void input() {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                default:
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;
            }

            // space key で timer がスタート //
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !gStart) {
                gameClock.restart();
                gTimer = true;
                gStart = true;
            }

            myKey.KeyDownHandler(event);
            myKey.KeyUpHandler(event);
            processInput();
        }
    }

    // 経過時間を取得する //
    void gameTimer() {
        timer = gameClock.getElapsedTime();

        int getTime = timer.asSeconds();

        int hours = getTime / 3600;
        int minutes = (getTime % 3600) / 60;
        float seconds = getTime % 60 + timer.asMilliseconds() % 1000 / 1000.0f;

        // タイマーを、 00:00:00.000 の形に変換
        std::ostringstream stream;
        stream << std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0')
               << std::setw(6) << std::fixed << std::setprecision(3) << seconds;

        formattedSeconds = stream.str();
    }

    bool update() {

        if (gTimer) gameTimer();

        // この引数は、string型です //
        myFrame.update(formattedSeconds);
        return true;
    }

    void draw() {
        window.clear();
        myFrame.draw(window);
        drawBoard();

        // ゲームが終了したら、テキストを描画へ //
        if (gameClear || gameOver) {
            myFrame.GameEnd(window, gameClear, gameOver);
        }

        window.display();
    }

    void run() {
        while (window.isOpen()) {
            input();
            update();
            draw();
        }
    }
};

int main() {
    std::srand(time(NULL));
    Game game;
    game.run();
    return 0;
}