// yapay zeka ödevi.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    double sutun=0, satir=0; //matris boyutunu öğrenmek için kullanıcan alacağım sayılar
    double degerler[100][100]; //matris değerlerini kaydettiğim değişken
    double sutun_index[100][2]; //sütun değerlerinin katsayı ve faydalarını saklayacağım değişken
    string isimler[100]; //kullanıcının verdiği karşılaştıralacak değerlerin isimleri
    string ozellikler[100]; //kullanıcının verdiği özelliklerin isimleri

    cout << "TOPSIS YONTEMI ILE PROBLEM COZME" << endl;
    cout << "Kac secim bulunmakta (satir sayisi): ";
    cin >> satir;
    cout << "Kac ozellik bulunmakta (sutun sayisi): ";
    cin >> sutun;
    cout << "--------------------------------------------" << endl;

    for (int i=0; i < satir; i++) {
        cout << i+1<< ". secimin ismi :";
        cin >> isimler[i];
    }

    cout << "--------------------------------------------" << endl;


    for (int i = 0; i < sutun; i++) {
        cout << i + 1 << ". ozelligin ismi :";
        cin >> ozellikler[i];
        cout << i + 1 << ". ozelligin katsayisi :";
        cin >> sutun_index[i][0];
        cout << i + 1 << ". ozelligin faydasi (faydaliysa 1, degilse 0 giriniz):";
        cin >> sutun_index[i][1];
        while(!(sutun_index[i][1] == 1 || sutun_index[i][1] == 0)) {
            cout << i + 1 << ". ozelligin faydasi (faydaliysa 1, degilse 0 giriniz):";
            cin >> sutun_index[i][1];
        }
        cout << "--------------------------------------------" << endl;

    }

    for (int i = 0; i < satir; i++) {
        for (int j = 0; j < sutun; j++) {
            cout << isimler[i] << " seciminin " << ozellikler[j] << " ozelliginin degeri:";
            cin >> degerler[i][j];
        }
    }

    double bolenler[100];
    double kare=0, toplam=0;
    for (int j = 0; j < sutun; j++) {
        for (int i = 0; i < satir; i++) {
            kare = degerler[i][j]* degerler[i][j];
            toplam = toplam + kare;
        }
 
        bolenler[j] = sqrt(toplam);
        toplam = 0;

    }

    double normalize[100][100];

    for (int i = 0; i < satir; i++) {
        for (int j = 0; j < sutun; j++) {
            
            normalize[i][j] = degerler[i][j] / bolenler[j];
        }
    }


    for (int i = 0; i < satir; i++) {
        for (int j = 0; j < sutun; j++) {

            normalize[i][j] = normalize[i][j]* sutun_index[j][0];
        }
    }


    //nomralizasyon tablosundaki değerleri, sütunların faydalarına göre en büyük ve en küçük değerlerini bulma adımı.

    double performans[100][2];
    double buyuk = 0, kucuk=0;

    for (int j = 0; j < sutun; j++) {
        kucuk = normalize[0][j];
        buyuk = normalize[0][j];

        for (int i = 0; i < satir; i++) {
            if (normalize[i][j] > buyuk) {
                buyuk = normalize[i][j];
            }


            if (normalize[i][j] < kucuk) {
                kucuk = normalize[i][j];
            }


        }
        if (sutun_index[j][1] == 1) {
            performans[j][0] = buyuk;
            performans[j][1] = kucuk;
        }
        else {
            performans[j][0] = kucuk;
            performans[j][1] = buyuk;
        }

    }


    //si+ ve si- değerlerini hesaplama
    double s[100][2];
    double p=0, n=0;

    for (int i = 0; i < satir; i++) {

        for (int j = 0; j < sutun; j++) {
            p = p + ((normalize[i][j] - performans[j][0])* (normalize[i][j] - performans[j][0]));
            n = n + ((normalize[i][j] - performans[j][1])* (normalize[i][j] - performans[j][1]));
        }
        s[i][0] = sqrt(p);
        s[i][1] = sqrt(n);
        p = 0;
        n = 0;

    }

    double sonuc[100];
    for (int i = 0; i < satir; i++) {
        sonuc[i] = s[i][1] / (s[i][0] + s[i][1]);
    }


    //sonucların sıralanması
    double gecici = 0;
    string isim;
    for (int i = 0; i < satir-1; i++) {
        for (int j = 0; j < satir-1; j++) {
            if (sonuc[j] < sonuc[j + 1]) {
                gecici = sonuc[j];
                sonuc[j] = sonuc[j + 1];
                sonuc[j + 1] = gecici;

                isim = isimler[j];
                isimler[j] = isimler[j + 1];
                isimler[j + 1] = isim;
            }
        }
    }












    cout << "----------------------------------------------------" << endl;
    cout << "----------------- GIRILEN DEGERLER -----------------" << endl<<endl;

    for (int i = 0; i < satir; i++) {
        cout << isimler[i] << "  ";
        for (int j = 0; j < sutun; j++) {
            cout <<degerler[i][j] << " - ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "-------------- NORMALIZASYON TABLOSU ---------------" << endl << endl;
    
    for (int i = 0; i < satir; i++) {
        cout << isimler[i] << ": ";
        for (int j = 0; j < sutun; j++) {
            cout << normalize[i][j]<<" - ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "----------------------------------------------------" << endl;
    cout << "------------- V+/V- (MAX/MIN) DEGERLERI -------------" << endl << endl;

    for (int j = 0; j < sutun; j++) {
        cout << isimler[j]<<":  ";
        cout << "V+ :"<<performans[j][0] << " / "<<"V- :"<< performans[j][1]<<endl;
    }

    cout << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "--------------- Si+ ve Si- DEGERLERI ----------------"<<endl<<endl;

    for (int j = 0; j < satir; j++) {
        cout << isimler[j] << ":  ";
        cout << s[j][0] << " - " << s[j][1]<<endl;
    }
    cout << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "------------------ SONUC TABLOSU -------------------" << endl<<endl;



    for (int j = 0; j < satir; j++) {
        cout <<j+1<<". uygun secim "<<isimler[j]<<" degeri: "<< sonuc[j] << endl;
    }
}

// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
