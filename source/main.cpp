
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

    // pair<Vector2i, Vector2i>�^��int�^��pair��v�f�Ƃ��Ď���vector
    std::vector<std::pair<std::pair<sf::Vector2i, sf::Vector2i>, int>> moves;

    // animation�p //
    sf::Clock animeClock;
    bool animation = false;

    // �ړ������܂łɂ����鎞�� //
    const float ANIMATION_DURATION = 0.15;

    // timer�p //
    sf::Clock gameClock;

    // space key �������ꂽ��Atimer ���A�X�^�[�g //
    bool gStart = false;

    // �^�C�}�[�́Arun, stop
    bool gTimer = false;
    
    sf::Time timer;
    std::string formattedSeconds;


    bool gameOver = false;
    bool gameClear = false;

    Game() : window(sf::VideoMode(gh::WINDOW_W, gh::WINDOW_H), "2048!") {
 
        // �ŏ��́A�V�����p�l����2���p�� //
        createNewPanel();
        createNewPanel();
    }

    // �ړ����̃p�l����`�� //
    void drawMovePanel() {
        Panel mPanel;

        // ����̃p�l���̍��W
        sf::Vector2i gOffset(gh::OFFSET_X, gh::OFFSET_Y);

        for (int i = 0; i < moves.size(); i++) {
            // �ړ�����������܂ŁA���ǂ̂��炢�Ȃ̂� //
            float movePercent = (animeClock.getElapsedTime().asSeconds() / ANIMATION_DURATION);

            sf::Vector2i f = moves[i].first.first;   // ���݂̃|�W�V���� //
            sf::Vector2i t = moves[i].first.second;  // �ړ���̃|�W�V���� //

            // ���݂̐��l�A�ړ�����������܂ł́A���݂̐��l���\������� //
            int num = moves[i].second;

            // �[���l���Ȃ��B������Ƃ��ړ������ //
            sf::Vector2f curPos = sf::Vector2f(f) + sf::Vector2f(t - f) * movePercent;

            // �|�W�V�����ɁA�p�l���̃T�C�Y�ƈʒu���l�� //
            float x = curPos.x * (mPanel.SIZE + gh::MARGIN) + gh::OFFSET_X;
            float y = curPos.y * (mPanel.SIZE + gh::MARGIN) + gh::OFFSET_Y;

            // panel class �̊֐��ɓn���āA�\�����Ă��炤 //
            mPanel.SetGamePanel(x, y, num);
            mPanel.draw(window);
        }

        // �A�j���[�V�������I�������� //
        if (animeClock.getElapsedTime().asSeconds() >= ANIMATION_DURATION) {
            // animation �I���ŁA�V�������l���i�[ //
            for (int y = 0; y < gh::ROWS; y++) {
                for (int x = 0; x < gh::COLS; x++) {
                    grid[y][x] = tempGrid[y][x];
                }
            }

            animation = false;

            // movePanel() �œ������́A�����ŏ��� //
            moves.clear();

            // �V���Ȃ�p�l�����Z�b�g //
            createNewPanel();
        }
    }

    // �p�l���̕`��
    void drawBoard() {
        Panel panel;
        for (int y = 0; y < gh::ROWS; y++) {
            for (int x = 0; x < gh::COLS; x++) {
                int num = grid[y][x];

                // animation���́A���ׂẴp�l����0�Ƃ��ĕ`�� //
                // 0�̎��́A���l���`�悳��Ȃ��̂ŁA�ړ����̃p�l���̎ז������Ȃ� //
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

    // �V�����p�l�����Z�b�g //
    void createNewPanel() {
        std::vector<sf::Vector2i> availablePoint;

        // �󔒂̃}�X��T�� //
        for (int y = 0; y < gh::ROWS; y++) {
            for (int x = 0; x < gh::COLS; x++) {
                if (!grid[y][x]) {
                    availablePoint.push_back({x, y});
                }
            }
        }

        // �S�Ẵ}�X�����܂��Ă��܂�����A�Q�[���I�[�o�[ //
        if (!availablePoint.size()) {
            gameOver = true;
            gTimer = false;
            return;
        }

        // �󔒂̃}�X���A�����_���ɑI�� //
        sf::Vector2i temp = availablePoint[rand() % availablePoint.size()];

        grid[temp.y][temp.x] = START_NUMBER;
    }

    // �A�j���[�V�����ɕK�v�ȏ����擾����֐� //
    void movePanel(int dx, int dy) {
        // �悸�́A�ړ��O�̃p�l���̐��l���i�[ //
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                tempGrid[y][x] = grid[y][x];
            }
        }

        for (int y = 0; y < 4; y++) {
            std::vector<sf::Vector2i> fromPos;  // ���݂̃|�W�V����
            std::vector<sf::Vector2i> toPos;    // �ړ���̃|�W�V����
            std::vector<int> srcNum;            // ���݂̃p�l���̐��l
            std::vector<int> before;            //
            std::vector<int> after;

            for (int x = 0; x < 4; x++) {
                if (dx == -1 || dx == 1) {  // ���E //
                    if (tempGrid[y][x]) {
                        // 0�ȊO�̐��l������ //
                        before.push_back(tempGrid[y][x]);

                        // ���݂̃|�W�V���������� //
                        fromPos.push_back({x, y});

                        // ���W�̐��l������
                        srcNum.push_back(tempGrid[y][x]);
                    }
                } else {  // �㉺ (x, y) ���t�ɂȂ�̂Œ��� //
                    if (tempGrid[x][y]) {
                        // 0�ȊO�̐��l������ //
                        before.push_back(tempGrid[x][y]);

                        // ���݂̃|�W�V���������� //
                        fromPos.push_back({y, x});

                        // ���W�̐��l������
                        srcNum.push_back(tempGrid[x][y]);
                    }
                }
            }

            // right, down �̎��͔z��𔽓] //
            if (dx == 1 || dy == 1) {
                reverse(before.begin(), before.end());
            }

            // �����ŋ����I��length��5�ɂ��� //
            while (before.size() < 5) {
                // before ����0�����鎞�́A�S��0�̎������B//
                // before ���l�Ƃ̊Ԃ�0�́A�����B//
                // ��: 00000, 84200, 22000 20000 �Ȋ��� //
                before.push_back(0);
            }

            for (int i = 0; i < 4; i++) {
                int current = before[i];
                int next = before[i + 1];

                // 0�̎��́A���������o�^����Ȃ� //
                if (!current) break;

                // �������l�����񂾏ꍇ //
                if (next && current == next) {
                    after.push_back(current + next);

                    // �ړ���̔z��ɁA�����|�W�V������2����
                    if (dx == -1) {
                        toPos.push_back({i, y});
                        toPos.push_back({i, y});
                    } else if (dx == 1) {
                        // 3 �͔z��̗v�f�̈�ԍŌ�,
                        // ����i��0�Ȃ�΁Ax�́A3�ŁA��ԉE�ɂ���
                        toPos.push_back({3 - i, y});
                        toPos.push_back({3 - i, y});
                    } else if (dy == -1) {
                        toPos.push_back({y, i});
                        toPos.push_back({y, i});
                    } else if (dy == 1) {
                        toPos.push_back({y, 3 - i});
                        toPos.push_back({y, 3 - i});
                    }

                    // ���̂����̂� next ���폜 //
                    before.erase(cbegin(before) + i + 1);

                } else {
                    // ���l�����΂Ȃ��������́A���̂܂�
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

            // �����ŋ����I��length��4�ɂ��� //
            while (after.size() < 4) {
                // ��: 0000, 8420, 2200 2000 �Ȋ��� //
                after.push_back(0);
            }

            // right, down �̎��͔��] //
            if (dx == 1 || dy == 1) {
                // ���l�̔z��𔽓] //
                reverse(after.begin(), after.end());

                // �|�W�V�����̔z��𔽓] //
                reverse(toPos.begin(), toPos.end());
            }

            // �V�������l���i�[ //
            for (int i = 0; i < 4; i++) {
                if (dx == -1 || dx == 1) {  // ���E //
                    tempGrid[y][i] = after[i];
                } else {  // �㉺ //
                    tempGrid[i][y] = after[i];
                }
            }

            // animation�p�̏����i�[ //
            for (int i = 0; i < fromPos.size(); i++) {
                // moves {{���݂̃|�W�V����, �ړ���̃|�W�V����}, ���݂̐��l}
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

        // key�̉������ςȂ���s�ɂ��� //
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

            // space key �� timer ���X�^�[�g //
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

    // �o�ߎ��Ԃ��擾���� //
    void gameTimer() {
        timer = gameClock.getElapsedTime();

        int getTime = timer.asSeconds();

        int hours = getTime / 3600;
        int minutes = (getTime % 3600) / 60;
        float seconds = getTime % 60 + timer.asMilliseconds() % 1000 / 1000.0f;

        // �^�C�}�[���A 00:00:00.000 �̌`�ɕϊ�
        std::ostringstream stream;
        stream << std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setfill('0')
               << std::setw(6) << std::fixed << std::setprecision(3) << seconds;

        formattedSeconds = stream.str();
    }

    bool update() {

        if (gTimer) gameTimer();

        // ���̈����́Astring�^�ł� //
        myFrame.update(formattedSeconds);
        return true;
    }

    void draw() {
        window.clear();
        myFrame.draw(window);
        drawBoard();

        // �Q�[�����I��������A�e�L�X�g��`��� //
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