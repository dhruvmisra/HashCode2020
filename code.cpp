#include<bits/stdc++.h>
#define ll long long
using namespace std;

//Logging DS
typedef int DEBUG_LEVEL;
int d_level = 0;
template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const std::pair<const Key, Value>& p)
{
    os << p.first << " => " << p.second;
    return os;
}
template<typename Container>
void log(DEBUG_LEVEL level, const Container& c) {
    if (level >= d_level) {
        for(typename Container::const_iterator it = c.begin();
            it != c.end(); ++it)
        std::cout << *it << '\n';
    }
}

class Library{
  public:
    ll noBooks;
    ll signupDays;
    ll  booksperDay;
    vector<ll> books;
    ll score;
    ll index;
    float efficiencyIndex;
    float commonIndex;
    ll booksIncluded;
    Library() {
      commonIndex = 0;
      score = 0;
    }
    void print() {
      cout<<noBooks<<" "<<signupDays<<" "<<booksperDay<<" "<<score<<" "<<commonIndex<<" "<<efficiencyIndex<<endl;
    }
    void calculateEI(){
      efficiencyIndex=((float)booksperDay*(float)score)/((float)signupDays*(float)noBooks*commonIndex);
    }
    void clear() {
      commonIndex = 0;
      score = 0;
      books.clear();
    } 
};

//Variables
Library l;
ll B, L, D, id, i, j, currDays;
vector<Library> libIncluded;
vector<Library> lib;
unordered_map<ll, ll> freq;
vector<ll> scores(100000);

//Compare functions 
bool sortLib(Library L1, Library L2){
  return L1.efficiencyIndex>L2.efficiencyIndex;
}
bool sortBooks(ll a, ll b ){
  return scores[a]>scores[b];
}

void solve() {
  scores.clear();
  lib.clear();
  libIncluded.clear();

  cin>>B>>L>>D;
  for(i=0; i<B; i++)
    cin>>scores[i];
    

  for(i=0; i<L; i++){
    cin>>l.noBooks>>l.signupDays>>l.booksperDay;

    for(j=0; j<l.noBooks; j++){
      cin>>id;
      l.score += scores[id];
      l.books.push_back(id);
      freq[id]++;
    }
    l.index = i;

    if(l.signupDays < D) {
      lib.push_back(l);
    }

    l.clear();
  }

  for(i=0; i<L; i++){
    for(j=0; j<lib[i].noBooks; j++) {
      lib[i].commonIndex += freq[lib[i].books[j]];
    }
    lib[i].commonIndex /= lib[i].noBooks;
    lib[i].calculateEI();
    // if(lib[i].index == 387)
    //   lib[i].print();
  }

  sort(lib.begin(), lib.end(), sortLib);

  currDays = 0, i = 0;
  while(currDays < D && i < lib.size()){
    if(currDays+lib[i].signupDays >= D) {
      i++;
      continue;
    }
    currDays += lib[i].signupDays;
    // lib[i].booksIncluded = max((lib[i].noBooks)*(D-currDays)/(lib[i].booksperDay), 1ll);
    lib[i].booksIncluded = min((D-currDays)*(lib[i].booksperDay), lib[i].noBooks);
    sort(lib[i].books.begin(), lib[i].books.end(), sortBooks);

    libIncluded.push_back(lib[i]);
    // cout<<currDays<<" "<<lib[i].booksIncluded<<endl;
    i++;
  }

  //Printing output
  cout<<libIncluded.size()<<endl;
  for(i=0; i<libIncluded.size(); i++) {
    cout<<libIncluded[i].index<<" "<<libIncluded[i].booksIncluded<<endl;
    for(j=0; j<libIncluded[i].booksIncluded; j++){
      cout<<libIncluded[i].books[j]<<" ";
    }
    cout<<endl;
  }
}

int main() {
  string inputs[6] = { "a_example.txt", "b_read_on.txt", "c_incunabula.txt", "d_tough_choices.txt", "e_so_many_books.txt", "f_libraries_of_the_world.txt" };

  for(int input=0; input<6; input++) {
    string input_path = "input/" + inputs[input];
    string output_path = "output/output";
    output_path += (char)65+input;
    output_path +=  ".out";
    
    freopen(input_path.c_str(), "r", stdin);

    fstream file; 
    file.open(output_path.c_str(), ios::out); 
    streambuf* stream_buffer_cout = cout.rdbuf(); 
    streambuf* stream_buffer_file = file.rdbuf(); 
    cout.rdbuf(stream_buffer_file); 

    solve();
  }
  return 0;  
}
