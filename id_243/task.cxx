Not good



#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

bool build_primes(vector<long> &primes);//, size_t max_number_count);
void deassemble(vector<long> &out_primes, vector<long> &out_count,
                long todo, vector<long> const &primes);
bool there_common_primes(vector<long> const &primes1,
                         vector<long> const &primes2);
bool compare_less(long resilence_nom, long resilence_den,
                  vector<long> const &nom_primes, vector<long> const &nom_cnt,
                  vector<long> const &den_primes, vector<long> const &den_cnt,
                  vector<long> const &all_primes);
void add_prime(vector<long> &primes, vector<long> &primes_cnt,
               long prime, long prime_cnt);

int main(int argc, char *argv[])
{
    vector<long> all_primes;
    build_primes(all_primes);//, 10001);
    //cout << primes.size() << /*" : " << primes[primes.size()-1] <<*/ endl;
    long biggest_prime = all_primes[all_primes.size()-1];

    vector<long> den_primes;
    vector<long> den_primes_cnt;
    vector<long> nom_primes;
    vector<long> nom_primes_cnt;
    deassemble(den_primes, den_primes_cnt, 94744, all_primes);
    deassemble(nom_primes, nom_primes_cnt, 15499, all_primes);

    cout << "Nom: ";
    size_t sz;
    if (nom_primes.size() > 0) {
        cout << "(" << nom_primes[0] << " ^ " << nom_primes_cnt[0] << ")";
        for (sz= 1; sz < nom_primes.size(); ++sz) {
            cout << " * (" << nom_primes[sz] << " ^ "
                 << nom_primes_cnt[sz] << ")";
        }
    } else {
        cout << "NO???";
    }
    cout << endl;

    cout << "Denom: ";
    if (den_primes.size() > 0) {
        cout << "(" << den_primes[0] << " ^ " << den_primes_cnt[0] << ")";
        for (sz= 1; sz < den_primes.size(); ++sz) {
            cout << " * (" << den_primes[sz] << " ^ "
                 << den_primes_cnt[sz] << ")";
        }
    } else {
        cout << "NO???";
    }
    cout << endl;

    vector<vector<long> > allsets;
    allsets.push_back(vector<long>(1, -1));

    vector<long> atmp;
    vector<long> atmp_cnt;

    size_t index = 1;
    while(1) {
        cout << "index ->" << index << endl;
        deassemble(atmp, atmp_cnt, (long)index, all_primes);
        long resilient = 0;
        for (size_t sz = 0; sz < index; ++sz) {
            if (!there_common_primes(allsets[sz], atmp)) {
                ++resilient;
            }
        }
        allsets.push_back(atmp);
        if (compare_less(resilient, (long)index, nom_primes, nom_primes_cnt,
                         den_primes, den_primes_cnt,
                         all_primes)) {
            cout << "answer is <" << index << ">" << endl;
            return 0;
        }
        if ((long)index >= biggest_prime) {
            cout << "index is <" <<
                index << "> more or equal to biggest prime" << endl;
            return 0;
        }
        ++index;
    }
    return 0;
}

void deassemble(vector<long> &out_primes, vector<long> &out_count,
                long todo, vector<long> const &primes)
{
    out_primes.clear();
    out_count.clear();
    if (1 == todo) {
        out_primes.push_back(1);
        out_count.push_back(1);
        return;
    }
    //long new_prime_max = (long)sqrt((double)todo);
    size_t sz = 0;
    bool bFirst = true;
    while(primes[sz] <= todo) {
        if (todo / primes[sz] * primes[sz] == todo) {
            todo /= primes[sz];
            if (bFirst) {
                out_primes.push_back(primes[sz]);
                out_count.push_back(1);
                bFirst = false;
            } else {
                ++out_count[out_count.size() - 1];
            }
        } else {
            bFirst = true;
            ++sz;
        }
    }
}

bool build_primes(vector<long> &primes)//, size_t max_number_count)
{
    primes.clear();
    
    ifstream ifs;
    ifs.open("/home/user/yshenderov/euler/primes_1mil.txt");
    if (ifs.good()) {
        long prime;
        while (!ifs.eof()) {
            ifs >> prime;
            primes.push_back(prime);
        }
        cout << "last " << prime << endl;
        return true;
    }
    return false;
}

bool there_common_primes(vector<long> const &primes1,
                         vector<long> const &primes2)
{
    size_t sz1 = 0;
    size_t sz2 = 0;

    //cout << "In there_common_primes" << endl;
    while ((sz1 < primes1.size()) && (sz2 < primes2.size())) {
        if (primes1[sz1] == primes2[sz2]) {
            //cout << "Out true there_common_primes" << endl;
            return true;
        }
        if (primes1[sz1] < primes2[sz2]) {
            ++sz1;
        } else {
            ++sz2;
        }
    }
    //cout << "Out false there_common_primes" << endl;
    return false;
}

bool compare_less(long resilence_nom, long resilence_den,
                  vector<long> const &nom_primes, vector<long> const &nom_cnt,
                  vector<long> const &den_primes, vector<long> const &den_cnt,
                  vector<long> const &all_primes)
{
    cout << resilence_nom << ":" << resilence_den << endl;
    if (0 == resilence_nom) return false;
    vector<long>  r_nom_primes;
    vector<long>  r_nom_cnt;
    vector<long>  r_den_primes;
    vector<long>  r_den_cnt;

    deassemble(r_nom_primes, r_nom_cnt, resilence_nom, all_primes);
    deassemble(r_den_primes, r_den_cnt, resilence_den, all_primes);
    cout <<  "sz " << r_den_primes.size() << endl;

    vector<long>  o_nom_primes = nom_primes;
    vector<long>  o_nom_cnt = nom_cnt;
    vector<long>  o_den_primes = den_primes;
    vector<long>  o_den_cnt = den_cnt;

    size_t sz_o_nom = o_nom_primes.size();
    size_t sz_r_nom = r_nom_primes.size();

    size_t szr = 0, szo = 0;

    while ((szr < r_den_primes.size()) &&(szo < o_den_primes.size())) {
        if (r_den_primes[szr] < o_den_primes[szo]) {
            add_prime(o_nom_primes, o_nom_cnt,
                      r_den_primes[szr], r_den_cnt[szr]);
            ++szr;
        } else if (r_den_primes[szr] > o_den_primes[szo]) {
            add_prime(r_nom_primes, r_nom_cnt,
                      o_den_primes[szo], o_den_cnt[szo]);
            ++szo;
        } else {
            if (r_den_cnt[szr] < o_den_cnt[szo]) {
                add_prime(r_nom_primes, r_nom_cnt,
                          r_den_primes[szr], o_den_cnt[szr] - r_den_cnt[szo]);
            } else if (r_den_cnt[szr] > o_den_cnt[szo]) {
                add_prime(o_nom_primes, o_nom_cnt,
                          r_den_primes[szr], r_den_cnt[szr] - o_den_cnt[szo]);
            }
            ++szr;
            ++szo;
        }
    }

    size_t sz;

    if (szr < r_den_primes.size()) {
        for (; szr < r_den_primes.size(); ++szr) {
            add_prime(o_nom_primes, o_nom_cnt,
                      r_den_primes[szr], r_den_cnt[szr]);
        }
    } else if (szo < o_den_primes.size()) {
        for (; szo < o_den_primes.size(); ++szo) {
            add_prime(r_nom_primes, r_nom_cnt,
                      o_den_primes[szo], o_den_cnt[szo]);
        }
    }

    long r_out = 1;
    for(sz = 0; sz < r_nom_primes.size(); ++sz) {
        while (r_nom_cnt[sz]--) {
            r_out *= r_nom_primes[sz];
        }
    }
    long o_out = 1;
    for(sz = 0; sz < o_nom_primes.size(); ++sz) {
        while (o_nom_cnt[sz]--) {
            o_out *= o_nom_primes[sz];
        }
    }
    cout << r_out << ":" << o_out << endl;
    return (r_out < o_out);
}

void add_prime(vector<long> &primes, vector<long> &primes_cnt,
               long prime, long prime_cnt)
{
    size_t sz = 0;
    while((sz < primes.size()) && (prime > primes[sz])) ++sz;
    if (sz >= primes.size()) {
        primes.push_back(prime);
        primes_cnt.push_back(prime_cnt);
    } else if (prime == primes[sz]) {
        primes_cnt[sz] += prime_cnt;
    } else {
        //May be we need move rest of array here and
        //insert new prime though for this task it seems would be enough
        //just to add to end
        primes.push_back(prime);
        primes_cnt.push_back(prime_cnt);
    }
}
