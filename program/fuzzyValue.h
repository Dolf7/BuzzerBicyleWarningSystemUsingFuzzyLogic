// Fungsi Keanggotaan Fuzzy

// Fungsi Keanggotaan KECEPATAN
int batasKecepatanLambat = 15;
float puncakKecepatanSedang = 22.5;
int awalKeceptanCepat = 30;

float valueKecepatanLambat(int speed)
{
    if (speed <= batasKecepatanLambat && speed > 0)
        return 1;
    else if (speed > batasKecepatanLambat && speed < puncakKecepatanSedang)
    {
        return ((puncakKecepatanSedang - speed) / (puncakKecepatanSedang - batasKecepatanLambat));
    }
    else
        return 0;
}

float valueKecepatanSedang(int speed)
{
    if (speed <= batasKecepatanLambat || speed >= awalKeceptanCepat)
        return 0;
    else if (speed > batasKecepatanLambat && speed < puncakKecepatanSedang)
    {
        return (speed - batasKecepatanLambat) / (puncakKecepatanSedang - batasKecepatanLambat);
    }
    else if (speed  >= puncakKecepatanSedang && speed < awalKeceptanCepat)
        return ((awalKeceptanCepat - speed) / (awalKeceptanCepat - puncakKecepatanSedang));
    return 0;
}

float valueKecepatanTinggi(int speed)
{
    if (speed <= puncakKecepatanSedang)
        return 0;
    else if (speed > puncakKecepatanSedang && speed < awalKeceptanCepat)
        return (speed - puncakKecepatanSedang) / (awalKeceptanCepat - puncakKecepatanSedang);
    else
        return 1;
    return 0;
}

// Fungsi Keanggotaan JARAK

int batasJarakDekat = 150;
int puncakJarakSedang = 250;
int awalJarakJauh = 350;

float valueJarakDekat(int jarak)
{
    if (jarak <= batasJarakDekat && jarak > 0)
        return 1;
    else if (jarak > batasJarakDekat && jarak < puncakJarakSedang)
    {
        return (float(puncakJarakSedang - jarak) / float(puncakJarakSedang - batasJarakDekat));
    }
    else
        return 0;
    return 10;
}
float valueJarakSedang(int jarak)
{
    if (jarak <= batasJarakDekat || jarak >= awalJarakJauh)
        return 0;
    else if (jarak > batasJarakDekat && jarak < puncakJarakSedang)
    {
        return (float(jarak - batasJarakDekat) / float(puncakJarakSedang - batasJarakDekat));
    }
    else if (jarak >= puncakJarakSedang && jarak < awalJarakJauh)
        return (float(awalJarakJauh - jarak) / float(awalJarakJauh - puncakJarakSedang));
    return 10;
}

float valueJarakJauh(int jarak)
{
    if (jarak <= puncakJarakSedang)
        return 0;
    else if (jarak > puncakJarakSedang && jarak < awalJarakJauh)
        return (float(jarak - puncakJarakSedang) / float(awalJarakJauh - puncakJarakSedang));
    else
        return 1;
    return 10;
}

// Fungsi Keanggotaan OUTPUT BUZZER - Dibutuhkan jika perlu menghitung Manual Saat Defuzzyfikasi -

// int awalPelan = 1;
// int puncakPelan = 51, puncakSedang = 102, puncakAgakKuat = 153, puncakKuat = 204, puncakSangatKuat = 255;

// float buzzerMati(float z)
// {
//     return 0;
// }

// float buzzerPelan(float alpha, int stat)
// {
//     if (alpha == 0) return 0;
//     int z;
//     if (stat == 1)
//         z = alpha * (puncakPelan - awalPelan) + awalPelan;
//     else if (stat == 2)
//         z = puncakSedang - alpha * (puncakSedang - puncakPelan);
//     else
//         return 0;
//     return z;
// }

// float buzzerSedang(float alpha, int stat)
// {
//     if (alpha == 0) return 0;
//     int z;
//     if (stat == 1)
//     {
//         z = alpha * (puncakSedang - puncakPelan) + puncakPelan;
//     }
//     else if (stat == 2)
//     {
//         z = puncakAgakKuat - alpha * (puncakAgakKuat - puncakSedang);
//     }
//     else
//         return 0;
//     return z;
// }

// float buzzerAgakKuat(float alpha, int stat)
// {
//     if (alpha == 0) return 0;
//     int z;
//     if (stat == 1)
//     {
//         z = alpha * (puncakAgakKuat - puncakSedang) + puncakSedang;
//     }
//     else if (stat == 2)
//     {
//         z = puncakKuat - alpha * (puncakKuat - puncakAgakKuat);
//     }
//     else
//         return 0;
//     return z;
// }

// float buzzeKuat(float alpha, int stat)
// {
//     if (alpha == 0) return 0;
//     int z;
//     if (stat == 1)
//     {
//         z = alpha * (puncakKuat - puncakAgakKuat) + puncakAgakKuat;
//     }
//     else if (stat == 2)
//     {
//         z = puncakSangatKuat - alpha * (puncakSangatKuat - puncakKuat);
//     }
//     else
//         return 0;
//     return z;
// }

// float buzzerSangatKuat(float alpha)
// {
//     if (alpha == 0) return 0;
//     int z;
//     if (alpha == 1)
//         return 255;
//     z = alpha * (puncakSangatKuat - puncakKuat) + puncakKuat;
//     return z;
// }