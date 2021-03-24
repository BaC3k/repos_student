#include <iostream>
#include <vector> 
#include <sstream>
#include <fstream>
#include <ios>
#include <set>

//#define ASIZE 256  
//#define XSIZE 8   

#define MAX(a, b) ((a < b) ? b : a)
#define OUTPUT(j) (std::cout << j<<std::endl)
//int arr[XSIZE][2];
std::vector<std::vector<int> > arr;
//std::vector<int[2]> arr;
//Bad Character 
/*
void preBmBc(char* x, int m, int bmBc[]) {
    int i;

    for (i = 0; i < ASIZE; ++i)
        bmBc[i] = m; // заполняет xsize
    for (i = 0; i < m - 1; ++i)
        bmBc[x[i]] = m - i - 1;
}
*/
void fillarr(std::vector<uint32_t> pat, int m) {
    //int m = strlen(pat);
    for (int i = 0; i < m; i++) {
        int j = pat[i];
        arr[i][0] = j;
        arr[i][1] = i;
    }
}

int bchar(uint32_t c, int m) {
    for (int i = m - 1; i >= 0; i--) {
        if (arr[i][0] == c) {
            return i;
        }
    }

    //return m;// размер паттерна
    //std::cout << std::endl;
    return 0;
}
void suffixes(std::vector<uint32_t> x, int m, std::vector<uint32_t> suff) {
    int f, g, i;

    suff[m - 1] = m;
    g = m - 1;
    for (i = m - 2; i >= 0; --i) {
        if (i > g&& suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 - f];
        else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && x[g] == x[g + m - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}

//Good suffix
void preBmGs(std::vector<uint32_t> x, int m, std::vector<uint32_t>bmGs) {
    int i, j;
    std::vector<uint32_t> suff;
    suff.resize(m);

    suffixes(x, m, suff); // создает массив

    for (i = 0; i < m; ++i)
        bmGs[i] = m;
    j = 0;
    for (i = m - 1; i >= 0; --i) {
        if (suff[i] == i + 1) {
            for (; j < m - 1 - i; ++j)
                if (bmGs[j] == m)
                    bmGs[j] = m - 1 - i;
        }
    }

    for (i = 0; i <= m - 2; ++i)
        bmGs[m - 1 - suff[i]] = m - 1 - i;
}
//так же считаем размер для вектора
std::vector<uint32_t> input() {
    std::set<uint32_t> alphabet;
    uint32_t value;
    std::vector<uint32_t> retval;
    std::stringstream in(std::ios_base::in | std::ios_base::out);
    std::string str;
    std::ifstream file;
    std::getline(std::cin, str);
    in << str;
    while (in >> value) {
        retval.push_back(value);
        alphabet.insert(value);  // для подсчета кол-ва уникальных значений
    }
    retval.push_back(alphabet.size());// добавляем в конец вектора размер алфавита
    return retval;
}

void BM(std::vector<uint32_t> x, int m, std::vector<uint32_t> y, int n) {
    int i, j;
    std::vector<uint32_t>bmGs;//, bmBc[ASIZE];
    bmGs.resize(m);
    arr.resize(m, std::vector<int>(2));
    /* Preprocessing */
    preBmGs(x, m, bmGs);
    fillarr(x, m);
    //preBmBc(x, m, bmBc);

    /* Searching */
    j = 0;
    while (j <= n - m) {
        for (i = m - 1; i >= 0 && x[i] == y[i + j]; i--);
        if (i < 0) {
            OUTPUT(j);
            j += bmGs[0];
        }
        else
            j += MAX(bmGs[i], bchar(y[i + j], m) - m + 1 + i);
    }
}

///DA3
/*
void badCharHeuristic(uint32_t* str, int size, int badchar[ASIZE])
{
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < ASIZE; i++)
        badchar[i] = -1;

    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++) {
        int j = (int)str[i]; //код символа в таблице asci
        badchar[j] = i; // i - номер позиции последнего вхождения символа j
    }
}
*/
//void fillarr(char* pat) {

//int bchar(char c) {

//void search(char* txt, char* pat)
/*void search(uint32_t* txt, int n, uint32_t* pat, int m)
{
    // int m = strlen(pat);
    // int n = strlen(txt);

    int badchar[ASIZE];

    //badCharHeuristic(pat, m, badchar);

    int s = 0; // s is shift of the pattern with respect to text
    while (s <= (n - m))
    {

        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
        {
            printf("\n pattern occurs at shift = %d", s);

            //s += (s + m < n) ? m - badchar[txt[s + m]] : 1; //вычисление сдвига
            s += (s + m < n) ? m - bchar(txt[s + m]) : 1; //вычисление сдвига
        }

        else
            // s += max(1, j - badchar[txt[s + j]]);
            s += MAX(1, j - bchar(txt[s + m]));
    }
}
*/
///DA3
int main()
{

    /*
    uint32_t txt[] = {
        122,
        11,
        111111111,
        134,
        1565,
        18,
        333,
        1212,
        144,
        1,
        178499345,
        238729040,
        134,
        1565,
        18,
        1234241,
        312434354,
        545744,
        1565,
        18,
        238439402,
        242834923,
        239494789,
        16257413,
        12312312
    };
    uint32_t pat[] = { 134,
        1565,
        18,
        1234241,
        312434354,
        545744,
        1565,
        18, };
        */
    std::vector<uint32_t> pat = input();
    int ASIZE = pat[pat.size() - 1];
    pat.pop_back();//удаление последнего эл-та вектора
    std::vector<uint32_t> txt = input();
    txt.pop_back();
    BM(pat, pat.size(), txt, txt.size());
}
