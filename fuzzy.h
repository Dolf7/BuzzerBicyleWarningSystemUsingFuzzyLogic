#include "fuzzyValue.h"

class fuzzyData
{
private:
    float valueSpeed[3]; // Fuzzy value for Speed
    float valueDistance[3]; // Fuzzy value for distance
    float rule[3][3]; //rule value for Fuzzy Logic
    int setPoint[3][3] = { //Middle for Each Condition
        // Pelan Sdg Cepat
        {102, 204, 255}, // Dekat
        {51, 153, 204},  // Sedang
        {0, 51, 102}     // Jauh
    };

    float minX(float a, float b) // Menentukan nilai terkecil dari 2 Bilangan a dan b
    {
      if (a < b)
      {
        return a;
      }
      return b;
    }

    void setDataAnd()
    {
      for (int i = 0; i < 3; i++) // Iterasi untuk array Rule
      {
        for (int j = 0; j < 3; j++)
        {
          if (this->valueDistance[i] == 0 || this->valueSpeed[j] == 0) // rule ke i j 0 jika tidak masuk ke logika
          {
            rule[i][j] = 0;
            continue;
          }
          rule[i][j] = minX(this->valueDistance[i], this->valueSpeed[j]); //Set Rule value
          // cout << this->valueSpeed[i] << " " << this->valueDistance[j] <<
        }
      }
    }

    void calculateValue() // Hitung Fuzzy Value;
    {
      this->valueDistance[0] = valueJarakDekat(this->distance);
      this->valueDistance[1] = valueJarakSedang(this->distance);
      this->valueDistance[2] = valueJarakJauh(this->distance);
      this->valueSpeed[0] = valueKecepatanLambat(this->speed);
      this->valueSpeed[1] = valueKecepatanSedang(this->speed);
      this->valueSpeed[2] = valueKecepatanTinggi(this->speed);
      setDataAnd();
    }

    int averageWeight() // defuzzyfication with Average Weight.
    {
      float totalA, totalB;
      for (int i = 0; i < 3; i++)
      {
          for (int j = 0; j < 3; j++)
          {
              if (rule[i][j] == 0)
                  continue;
              totalA += rule[i][j] * setPoint[i][j];
              totalB += rule[i][j];
          }
      }
      return totalA / totalB;
    }

    int middleOfMaxima() // defuzzyfication with Midle Of Maxima or Mean Max Membership
    {
      float length = 0;
      float sumOfValue = 0;
      float max = 0;
      int indx[2];
      //ITERATE in SetPoint Array
      for (int i = 0; i < 3; i++)
      {
          for (int j = 0; j < 3; j++)
          {
              if (rule[i][j] == 0)
                  continue;
              if (rule[i][j] >= max) // Search MAX Value
              {
                  if (rule[i][j] > max) // Jika Nilai paling besar sendiri
                  {
                      max = rule[i][j];
                      sumOfValue = 0;
                      length = 1;
                      sumOfValue += setPoint[i][j];
                  }
                  else if (rule[i][j] == max) // HITUNG jika Ada yang memiliki Tinggi yang Sama
                  {
                      length++;
                      sumOfValue += setPoint[i][j];
                  }
              }
          }
      }

      if (rule[0][2] == max && length == 1) // Jika Dalam OUTPUT Kategori SANGAT KUAT 204 - 255
      {
          ((max * (255 - 204) + 204)+255)/2;
      }
      return sumOfValue / length;
    }

public:
    int speed;
    int distance;
    int output;
    fuzzyData(int speed, int distance)
    {
      this->distance = distance;
      this->speed = speed;
      this->calculateValue();
      // pilih salah satu defuzzyfikasi method
      // this->output = this->averageWeight(); 
      this->output = this->middleOfMaxima();
    }

    // FOR DEBUGGING and Testing 
    // void printAllVariable()
    // {
    //     cout << "Rule : " << endl
    //          << "\tP\tS\tC" << endl;
    //     for (int i = 0; i < 3; i++)
    //     {
    //         i == 0 ? cout << "D\t" : i == 1 ? cout << "S\t"
    //                                         : cout << "J\t";
    //         for (int j = 0; j < 3; j++)
    //         {
    //             cout << this->rule[i][j] << " \t ";
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    //     cout << "Value Speed - Value Distance : " << endl;
    //     for (int i = 0; i < 3; i++)
    //     {
    //         cout << this->valueSpeed[i] << '-' << this->valueDistance[i] << endl;
    //         ;
    //     }
    // }
};
