#include <bits/stdc++.h>
using namespace std;
vector<string> moveLog;
class Cube {
public:
    // Faces: 0=U,1=D,2=L,3=R,4=F,5=B
    char face[6][9];

    bool loadFromFile(const string& filename) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Error: Cannot open file\n";
            return false;
        }

        string s;
        fin >> s;
        fin.close();

        if (s.size() != 54) {
            cerr << "Error: Invalid cube string length\n";
            return false;
        }

        int idx = 0;
        for (int f = 0; f < 6; f++) {
            for (int i = 0; i < 9; i++) {
                face[f][i] = s[idx++];
            }
        }
        return true;
    }

    void printCube() const {
        static const char* name[6] = {"U","D","L","R","F","B"};
        for (int f = 0; f < 6; f++) {
            cout << name[f] << ": ";
            for (int i = 0; i < 9; i++) {
                cout << face[f][i];
            }
            cout << '\n';
        }
    }
};
// ================= MOVE ENGINE =================

void rotateCW(char f[9]) {
    char t[9];
    memcpy(t, f, 9);
    f[0]=t[6]; f[1]=t[3]; f[2]=t[0];
    f[3]=t[7]; f[4]=t[4]; f[5]=t[1];
    f[6]=t[8]; f[7]=t[5]; f[8]=t[2];
}

// U
void moveU(Cube &c) {
    rotateCW(c.face[0]);
    char t0=c.face[4][0], t1=c.face[4][1], t2=c.face[4][2];
    c.face[4][0]=c.face[3][0]; c.face[4][1]=c.face[3][1]; c.face[4][2]=c.face[3][2];
    c.face[3][0]=c.face[5][0]; c.face[3][1]=c.face[5][1]; c.face[3][2]=c.face[5][2];
    c.face[5][0]=c.face[2][0]; c.face[5][1]=c.face[2][1]; c.face[5][2]=c.face[2][2];
    c.face[2][0]=t0; c.face[2][1]=t1; c.face[2][2]=t2;
     moveLog.push_back("UC");  
}

// U'
void moveUi(Cube &c){ 
    moveU(c); moveU(c); moveU(c);
    moveLog.pop_back(); moveLog.pop_back(); moveLog.pop_back(); 
    moveLog.push_back("UCC");}
// D
void moveD(Cube &c) {
    rotateCW(c.face[1]);

    char t0=c.face[4][6], t1=c.face[4][7], t2=c.face[4][8];

    c.face[4][6]=c.face[2][6];
    c.face[4][7]=c.face[2][7];
    c.face[4][8]=c.face[2][8];

    c.face[2][6]=c.face[5][6];
    c.face[2][7]=c.face[5][7];
    c.face[2][8]=c.face[5][8];

    c.face[5][6]=c.face[3][6];
    c.face[5][7]=c.face[3][7];
    c.face[5][8]=c.face[3][8];

    c.face[3][6]=t0;
    c.face[3][7]=t1;
    c.face[3][8]=t2;
    moveLog.push_back("DC");  
}
//D'
void moveDi(Cube &c){ 
    moveD(c); moveD(c); moveD(c);
    moveLog.pop_back(); moveLog.pop_back(); moveLog.pop_back();
    moveLog.push_back("DCC");
}
//B
void moveB(Cube &c) {
    rotateCW(c.face[5]);

    char t0=c.face[0][0], t1=c.face[0][1], t2=c.face[0][2];

    c.face[0][0]=c.face[3][2];
    c.face[0][1]=c.face[3][5];
    c.face[0][2]=c.face[3][8];

    c.face[3][2]=c.face[1][8];
    c.face[3][5]=c.face[1][7];
    c.face[3][8]=c.face[1][6];

    c.face[1][6]=c.face[2][0];
    c.face[1][7]=c.face[2][3];
    c.face[1][8]=c.face[2][6];

    c.face[2][0]=t2;
    c.face[2][3]=t1;
    c.face[2][6]=t0;
     moveLog.push_back("BC");  
}
//B'
void moveBi(Cube &c){ 
    moveB(c); moveB(c); moveB(c); 
    moveLog.pop_back(); moveLog.pop_back(); moveLog.pop_back();
    moveLog.push_back("BCC"); 
}
//R
void moveR(Cube &c) {
    rotateCW(c.face[3]);

    char t0=c.face[0][2], t1=c.face[0][5], t2=c.face[0][8];

    c.face[0][2]=c.face[4][2];
    c.face[0][5]=c.face[4][5];
    c.face[0][8]=c.face[4][8];

    c.face[4][2]=c.face[1][2];
    c.face[4][5]=c.face[1][5];
    c.face[4][8]=c.face[1][8];

    c.face[1][2]=c.face[5][6];
    c.face[1][5]=c.face[5][3];
    c.face[1][8]=c.face[5][0];

    c.face[5][0]=t0;
    c.face[5][3]=t1;
    c.face[5][6]=t2;
     moveLog.push_back("RC");  
}
//R'
void moveRi(Cube &c){
    moveR(c); moveR(c); moveR(c); 
    moveLog.pop_back(); moveLog.pop_back(); moveLog.pop_back(); 
    moveLog.push_back("RCC");
}
//L
void moveL(Cube &c) {
    rotateCW(c.face[2]);

    char t0=c.face[0][0], t1=c.face[0][3], t2=c.face[0][6];

    c.face[0][0]=c.face[5][8];
    c.face[0][3]=c.face[5][5];
    c.face[0][6]=c.face[5][2];

    c.face[5][2]=c.face[1][6];
    c.face[5][5]=c.face[1][3];
    c.face[5][8]=c.face[1][0];

    c.face[1][0]=c.face[4][0];
    c.face[1][3]=c.face[4][3];
    c.face[1][6]=c.face[4][6];

    c.face[4][0]=t0;
    c.face[4][3]=t1;
    c.face[4][6]=t2;
}
//L'
void moveLi(Cube &c){
    moveL(c); moveL(c); moveL(c); 
    moveLog.pop_back(); moveLog.pop_back(); moveLog.pop_back();
    moveLog.push_back("LCC");
}
//F
void moveF(Cube &c) {
    rotateCW(c.face[4]);

    char t0=c.face[0][6], t1=c.face[0][7], t2=c.face[0][8];

    c.face[0][6]=c.face[2][8];
    c.face[0][7]=c.face[2][5];
    c.face[0][8]=c.face[2][2];

    c.face[2][2]=c.face[1][2];
    c.face[2][5]=c.face[1][1];
    c.face[2][8]=c.face[1][0];

    c.face[1][0]=c.face[3][6];
    c.face[1][1]=c.face[3][3];
    c.face[1][2]=c.face[3][0];

    c.face[3][0]=t0;
    c.face[3][3]=t1;
    c.face[3][6]=t2;
     moveLog.push_back("FC");
}
//F'
void moveFi(Cube &c){ 
    moveF(c); moveF(c); moveF(c); 
    moveLog.pop_back(); moveLog.pop_back(); moveLog.pop_back();
    moveLog.push_back("FCC");
}
char center(const Cube& c, int face) {
    return c.face[face][4];
}
bool cubeSolved(const Cube& c) {
    for (int f = 0; f < 6; f++) {
        for (int i = 0; i < 9; i++) {
            if (c.face[f][i] != c.face[f][4]) {
                return false;
            }
        }
    }
    return true;
}
bool whiteCrossSolved(const Cube& c) {
    return c.face[1][1]=='W' &&
           c.face[1][3]=='W' &&
           c.face[1][5]=='W' &&
           c.face[1][7]=='W' &&
           c.face[4][7]==center(c,4) &&
           c.face[3][7]==center(c,3) &&
           c.face[5][7]==center(c,5) &&
           c.face[2][7]==center(c,2);
}
bool f2lSolved(const Cube& c) {
    for (int i = 0; i < 9; i++) {
        if (c.face[1][i] != c.face[1][4]) return false;
    }
    int faces[4] = {4, 3, 5, 2};
    for (int f : faces) {
        if (c.face[f][3] != c.face[f][4]) return false;
        if (c.face[f][4] != c.face[f][4]) return false;
        if (c.face[f][5] != c.face[f][4]) return false;
        if (c.face[f][6] != c.face[f][4]) return false;
        if (c.face[f][7] != c.face[f][4]) return false;
        if (c.face[f][8] != c.face[f][4]) return false;
    }

    return true;
}
bool ollSolved(const Cube& c) {
    return c.face[0][0]=='Y' &&
           c.face[0][1]=='Y' &&
           c.face[0][2]=='Y' &&
           c.face[0][3]=='Y' &&
           c.face[0][4]=='Y' &&
           c.face[0][5]=='Y' &&
           c.face[0][6]=='Y' &&
           c.face[0][7]=='Y' &&
           c.face[0][8]=='Y';
}
struct EdgePos {
    int f1, i1;
    int f2, i2;
};

const EdgePos EDGE_POS[12] = {
    {0,5,3,1}, {0,7,4,1}, {0,3,2,1}, {0,1,5,1},
    {1,5,3,7}, {1,7,4,7}, {1,3,2,7}, {1,1,5,7},
    {4,5,3,3}, {4,3,2,5}, {5,3,2,3}, {5,5,3,5}
};
void bringWhiteEdgeToTop(Cube& c, const EdgePos& e) {
    if (e.f1 == 0 || e.f2 == 0) return;

    if (e.f1 == 1 || e.f2 == 1) {
        if (e.f1 == 4 || e.f2 == 4) {
            moveF(c); moveF(c);
        } else if (e.f1 == 3 || e.f2 == 3) {
            moveR(c); moveR(c);
        } else if (e.f1 == 5 || e.f2 == 5) {
            moveB(c); moveB(c);
        } else if (e.f1 == 2 || e.f2 == 2) {
            moveL(c); moveL(c);
        }
        return;
    }

    if (e.f1 == 4 || e.f2 == 4) {
        moveF(c);
    } else if (e.f1 == 3 || e.f2 == 3) {
        moveR(c);
    } else if (e.f1 == 5 || e.f2 == 5) {
        moveB(c);
    } else if (e.f1 == 2 || e.f2 == 2) {
        moveL(c);
    }
}

void alignAndInsertWhiteEdge(Cube& c) {
    for (int i = 0; i < 4; i++) {
        if (c.face[4][1] == center(c,4)) {
            moveF(c); moveF(c);
            return;
        }
        if (c.face[3][1] == center(c,3)) {
            moveR(c); moveR(c);
            return;
        }
        if (c.face[5][1] == center(c,5)) {
            moveB(c); moveB(c);
            return;
        }
        if (c.face[2][1] == center(c,2)) {
            moveL(c); moveL(c);
            return;
        }
        moveU(c);
    }
}
void solveWhiteCross(Cube& c) {
    int guard = 0;
    while (!whiteCrossSolved(c) && guard < 50) {
        guard++;
        for (int i = 0; i < 12; i++) {
            const EdgePos& e = EDGE_POS[i];
            char a = c.face[e.f1][e.i1];
            char b = c.face[e.f2][e.i2];
            if (a == 'W' || b == 'W') {
                bringWhiteEdgeToTop(c, e);
                alignAndInsertWhiteEdge(c);
                break;
            }
        }
    }
}
bool isWhite(char a, char b, char c) {
    return (a=='W' || b=='W' || c=='W');
}
bool whiteCornerFRSolved(const Cube& c) {
    return c.face[1][2]=='W' &&
           c.face[4][8]==center(c,4) &&
           c.face[3][6]==center(c,3);
}
void insertWhiteCornerFR(Cube& c) {
    moveU(c);
    moveR(c);
    moveUi(c);
    moveRi(c);
}
void removeWrongWhiteCornerFR(Cube& c) {
    moveR(c);
    moveU(c);
    moveRi(c);
}
void bringWhiteCornerToTop(Cube& c) {
    if (isWhite(c.face[0][8], c.face[4][2], c.face[3][2])) return;

    for (int i = 0; i < 4; i++) {
        if (isWhite(c.face[0][8], c.face[4][2], c.face[3][2]))
            return;
        moveU(c);
    }

    removeWrongWhiteCornerFR(c);
}
void solveWhiteCorners(Cube& c) {
    int guard = 0;

    while (guard++ < 40) {
        if (whiteCornerFRSolved(c)) {
            moveU(c);
            continue;
        }

        bringWhiteCornerToTop(c);

        if (isWhite(c.face[0][8], c.face[4][2], c.face[3][2])) {
            insertWhiteCornerFR(c);
        }

        if (whiteCornerFRSolved(c)) {
            moveU(c);
        }

        bool done = true;
        for (int i = 0; i < 4; i++) {
            if (!whiteCornerFRSolved(c)) done = false;
            moveU(c);
        }
        if (done) break;
    }
}
bool secondLayerSolved(const Cube& c) {
    int faces[4] = {4, 3, 5, 2};
    for (int f : faces) {
        if (c.face[f][3] != center(c,f)) return false;
        if (c.face[f][5] != center(c,f)) return false;
    }
    return true;
}
void insertSecondLayerLeft(Cube& c) {
    moveUi(c);
    moveLi(c);
    moveU(c);
    moveL(c);
    moveU(c);
    moveF(c);
    moveUi(c);
    moveFi(c);
}
void insertSecondLayerRight(Cube& c) {
    moveU(c);
    moveR(c);
    moveUi(c);
    moveRi(c);
    moveUi(c);
    moveFi(c);
    moveU(c);
    moveF(c);
}
void removeWrongSecondLayerEdge(Cube& c) {
    insertSecondLayerRight(c);
}
bool alignSecondLayerEdge(Cube& c) {
    char f = center(c,4);
    char r = center(c,3);

    for (int i = 0; i < 4; i++) {
        if (c.face[0][7] == f && c.face[4][1] != 'Y') {
            if (c.face[4][1] == r) {
                insertSecondLayerRight(c);
            } else {
                insertSecondLayerLeft(c);
            }
            return true;
        }
        moveU(c);
    }
    return false;
}
void solveSecondLayer(Cube& c) {
    int guard = 0;

    while (!secondLayerSolved(c) && guard++ < 40) {

        if (alignSecondLayerEdge(c))
            continue;

        bool fixed = false;
        for (int i = 0; i < 4; i++) {
            if (c.face[4][5] != center(c,4) &&
                c.face[3][3] != center(c,3)) {
                removeWrongSecondLayerEdge(c);
                fixed = true;
                break;
            }
            moveU(c);
        }

        if (!fixed)
            moveU(c);
    }
}
bool yellowCrossSolved(const Cube& c) {
    return c.face[0][1] == 'Y' &&
           c.face[0][3] == 'Y' &&
           c.face[0][5] == 'Y' &&
           c.face[0][7] == 'Y';
}
int yellowCrossPattern(const Cube& c) {
    bool up    = c.face[0][1] == 'Y';
    bool left  = c.face[0][3] == 'Y';
    bool right = c.face[0][5] == 'Y';
    bool down  = c.face[0][7] == 'Y';

    if (up && left && right && down) return 3; // cross
    if (left && right) return 2;               // line
    if (up && right) return 1;                 // L-shape
    if (up) return 0;                           // dot
    return 0;
}
void algYellowCross(Cube& c) {
    moveF(c);
    moveR(c);
    moveU(c);
    moveRi(c);
    moveUi(c);
    moveFi(c);
}
void solveYellowCross(Cube& c) {
    int guard = 0;

    while (!yellowCrossSolved(c) && guard++ < 6) {
        int pattern = yellowCrossPattern(c);

        if (pattern == 0) {
            algYellowCross(c);
        }
        else if (pattern == 1) {
            algYellowCross(c);
        }
        else if (pattern == 2) {
            algYellowCross(c);
        }
        else if (pattern == 3) {
            return;
        }

        moveU(c);
    }
}
int countAlignedYellowEdges(const Cube& c) {
    int cnt = 0;
    if (c.face[4][1] == center(c,4)) cnt++; // F
    if (c.face[3][1] == center(c,3)) cnt++; // R
    if (c.face[5][1] == center(c,5)) cnt++; // B
    if (c.face[2][1] == center(c,2)) cnt++; // L
    return cnt;
}
bool yellowEdgesAligned(const Cube& c) {
    return countAlignedYellowEdges(c) == 4;
}
void algPLL_EdgeCycle(Cube& c) {
    moveR(c);
    moveU(c);
    moveRi(c);
    moveU(c);
    moveR(c);
    moveU(c);
    moveU(c);
    moveRi(c);
    moveU(c);
}
void alignTwoEdges(Cube& c) {
    for (int i = 0; i < 4; i++) {
        if (countAlignedYellowEdges(c) >= 2)
            return;
        moveU(c);
    }
}
void alignYellowCrossEdges(Cube& c) {
    int guard = 0;

    while (!yellowEdgesAligned(c) && guard++ < 10) {

        alignTwoEdges(c);

        int aligned = countAlignedYellowEdges(c);

        if (aligned == 4) return;

        if (aligned == 2) {
            algPLL_EdgeCycle(c);
        } else {
            algPLL_EdgeCycle(c);
        }
    }
}
bool yellowCornersPositioned(const Cube& c) {
    char f = center(c,4);
    char r = center(c,3);
    char b = center(c,5);
    char l = center(c,2);

    int correct = 0;

    auto ok = [&](char a, char b, char c, char x, char y, char z) {
        set<char> s1 = {a,b,c};
        set<char> s2 = {x,y,z};
        return s1 == s2;
    };

    if (ok(c.face[0][8], c.face[4][2], c.face[3][2], 'Y', f, r)) correct++;
    if (ok(c.face[0][2], c.face[3][2], c.face[5][2], 'Y', r, b)) correct++;
    if (ok(c.face[0][0], c.face[5][2], c.face[2][2], 'Y', b, l)) correct++;
    if (ok(c.face[0][6], c.face[2][2], c.face[4][2], 'Y', l, f)) correct++;

    return correct == 4;
}
bool rotateUntilOneCornerMatches(Cube& c) {
    char f = center(c,4);
    char r = center(c,3);

    for (int i = 0; i < 4; i++) {
        set<char> s = {c.face[0][8], c.face[4][2], c.face[3][2]};
        if (s == set<char>{'Y',f,r}) return true;
        moveU(c);
    }
    return false;
}
void solveYellowCornerPositions(Cube& c) {
    int guard = 0;

    while (!yellowCornersPositioned(c) && guard++ < 10) {

        if (!rotateUntilOneCornerMatches(c)) {
            algPLL_CornerCycle(c);
            continue;
        }

        algPLL_CornerCycle(c);
    }
}
bool yellowCornersOriented(const Cube& c) {
    return c.face[0][0]=='Y' &&
           c.face[0][2]=='Y' &&
           c.face[0][6]=='Y' &&
           c.face[0][8]=='Y';
}
void algTwistCorner(Cube& c) {
    moveR(c);
    moveU(c);
    moveRi(c);
    moveUi(c);
}
void orientYellowCorners(Cube& c) {
    int guard = 0;

    while (!yellowCornersOriented(c) && guard++ < 30) {

        if (c.face[0][8] != 'Y') {
            algTwistCorner(c);
            algTwistCorner(c);
        }
        moveU(c);
    }
}
int main() {
    Cube cube;

    if (!cube.loadFromFile("cube_state.txt")) {
        return 1;
    }

    solveWhiteCross(cube);
    solveWhiteCorners(cube);
    solveSecondLayer(cube);
    solveYellowCross(cube);
    alignYellowCrossEdges(cube);
    solveYellowCornerPositions(cube);
    orientYellowCorners(cube);

    ofstream fout("solution.txt");
    if (!fout.is_open()) {
        return 1;
    }

    for (const string& move : moveLog) {
        fout << move << " ";
    }
    fout << "\n";
    fout.close();

    return 0;
}

