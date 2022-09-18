#include <iostream>
#include <string>

class PokerCard
{
public:
    PokerCard(std::string s, int f)
    {
        suit = s;
        face = f;
    }
    friend std::ostream &operator<<(std::ostream &out, const PokerCard &p)
    {
        out<<"["<<p.face<<" of "<<p.suit<<"]";
        return out;
    }

    //Please finish the operator override
    //請完成運算子多載
    //spade > heart > diamond > club
    //1 > 13 > 12 > 11 > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2
    bool operator>(const PokerCard &b)
    {
      int test_face = face, input_face = b.face;
      if(test_face == 1)
        test_face += 13;
      if(input_face == 1)
        input_face += 13;

      if(test_face > input_face)
        return true;
      else if(test_face < input_face)
        return false;
      else
      {
        if(suit > b.suit)
          return true;
        else
          return false;
      }
    }
    bool operator<(const PokerCard &b)
    {
      int test_face = face, input_face = b.face;
      if(test_face == 1)
        test_face += 13;
      if(input_face == 1)
        input_face += 13;

      if(test_face < input_face)
        return true;
      else if(test_face > input_face)
        return false;
      else
      {
        if(suit < b.suit)
          return true;
        else
          return false;
      }
    }
    bool operator==(const PokerCard &b)
    {
      if(b.suit == suit && b.face == face)
        return true;
      else
        return false;
    }

private:
    std::string suit;
    int face;
};

int main()
{
    PokerCard **card = (PokerCard **)malloc(sizeof(PokerCard *) * 52);

    std::string s[] = {"spade", "heart", "diamond", "club"};
    int j, k;
    for(j = 0;j < 4;j ++)
        for(k = 1;k <= 13;k ++)
            card[j * 13 + k - 1] = new PokerCard(s[j], k);
    for(j = 0;j < 52;j ++)
    {
        for(k = 0;k < 52;k ++)
        {
            std::cout<<*(card[j])<<">"<<*(card[k])<<":"<<(*(card[j])>*(card[k]))<<std::endl;
            std::cout<<*(card[j])<<"<"<<*(card[k])<<":"<<(*(card[j])<*(card[k]))<<std::endl;
            std::cout<<*(card[j])<<"=="<<*(card[k])<<":"<<(*(card[j])==*(card[k]))<<std::endl;
        }
    }
}
