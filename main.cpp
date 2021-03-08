#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include "sha256.h"
using namespace std;
struct user {
    string nume;
    string parola;
    string status;
};
map<string,user> mp;
void citire()
{
    int m, n, l;
    user x;
    string a, b, c;
    ifstream f("logare.xml");
    string s;
    getline(f,s);
    while(getline(f,s))
    {
        if(s=="</users>")
            break;
        else
        {
            getline(f,a);
            getline(f,b);
            getline(f,c);
            n=s.find_first_of("\"");
            m=s.find_last_of("\"");
            l=m-n-1;
            x.nume=s.substr(n+1,l);
            n=a.find_first_of(">");
            m=a.find_last_of("<");
            l=m-n-1;
            x.parola=a.substr(n+1,l);
            n=b.find_first_of(">");
            m=b.find_last_of("<");
            l=m-n-1;
            x.status=b.substr(n+1,l);
            mp[x.nume]=x;
        }
    }
    f.close();
}
void afisarexml()
{
    ofstream g("logare.xml");
    g<<"<users>"<<'\n';
    for(auto i:mp)
    {
        g<<"    <username=\""<<i.second.nume<<"\">"<<'\n';
        g<<"        <parola>"<<i.second.parola<<"</parola>"<<'\n';
        g<<"        <status>"<<i.second.status<<"</status>"<<'\n';
        g<<"    </username>"<<'\n';
    }
    g<<"</users>"<<'\n';
}
void vizualizare_conturi()
{
    for(auto i:mp)
    {
        cout<<i.second.nume<<" - ";
        cout<<i.second.status<<'\n';
    }
}
struct Materie{
    string numematerie;
    string absente;
    string note;
};
struct Elev{
    string numeelev;
    string cnp;
    map<string,Materie> materie;
};
struct Clasa{
    string numeclasa;
    string invatator;
    string cnpinvatator;
    map<string,Elev> elev;
};
struct Scoala{
    string numescoala;
    map<string,Clasa> clasa;
};
map<string,Scoala> scoala;
void citire_catalog()
{
    int n, m, l;
    string s;
    ifstream f("catalog.xml");
    while(1)
    {
      getline(f,s);
      if(s.substr(0,7)!="<scoala")
        break;
      n=s.find_first_of("\"");
      m=s.find_last_of("\"");
      l=m-n-1;
      scoala[s.substr(n+1,l)].numescoala=s.substr(n+1,l);
      s=s.substr(n+1,l);
      for(int i=1;i<=1;i++)
      {
          string CLASA, CNP;
          getline(f,CLASA);
          n=CLASA.find_first_of("\"");
          m=CLASA.find_last_of("\"");
          l=m-n-1;
          scoala[s].clasa[CLASA.substr(n+1,l)].numeclasa=CLASA.substr(n+1,l);
          CLASA=CLASA.substr(n+1,l);
          string NUME;
          getline(f,NUME);
          n=NUME.find_first_of(">");
          m=NUME.find_last_of("<");
          l=m-n-1;
          scoala[s].clasa[CLASA].invatator=NUME.substr(n+1,l);
          NUME=NUME.substr(n+1,l);
          getline(f,CNP);
          n=CNP.find_first_of(">");
          m=CNP.find_last_of("<");
          l=m-n-1;
          scoala[s].clasa[CLASA].cnpinvatator=CNP.substr(n+1,l);
          getline(f,NUME);
          while(NUME!="  </clasa>")
          {
              string MATERIE;
              n=NUME.find_first_of("\"");
              m=NUME.find_last_of("\"");
              l=m-n-1;
              scoala[s].clasa[CLASA].elev[NUME.substr(n+1,l)].numeelev=NUME.substr(n+1,l);
              NUME=NUME.substr(n+1,l);
              getline(f,CNP);
              n=CNP.find_first_of(">");
              m=CNP.find_last_of("<");
              l=m-n-1;
              scoala[s].clasa[CLASA].elev[NUME].cnp=CNP.substr(n+1,l);
              getline(f,MATERIE);
              while(MATERIE!="    </elev>")
              {
                  string NOTE, ABSENTE, rulment;
                  getline(f,NOTE);
                  getline(f,ABSENTE);
                  getline(f,rulment);
                  n=MATERIE.find_first_of("\"");
                  m=MATERIE.find_last_of("\"");
                  l=m-n-1;
                  scoala[s].clasa[CLASA].elev[NUME].materie[MATERIE.substr(n+1,l)].numematerie=MATERIE.substr(n+1,l);
                  MATERIE=MATERIE.substr(n+1,l);
                  n=ABSENTE.find_first_of(">");
                  m=ABSENTE.find_last_of("<");
                  l=m-n-1;
                  scoala[s].clasa[CLASA].elev[NUME].materie[MATERIE].absente=ABSENTE.substr(n+1,l);
                  n=NOTE.find_first_of(">");
                  m=NOTE.find_last_of("<");
                  l=m-n-1;
                  scoala[s].clasa[CLASA].elev[NUME].materie[MATERIE].note=NOTE.substr(n+1,l);
                  getline(f,MATERIE);
              }
              getline(f,NUME);
          }
      }
    }
}
void afisare_catalog()
{
    ofstream g("catalog.xml");
    for(auto iscoala:scoala)
    {
      g<<"<scoala=\""<<iscoala.second.numescoala<<"\">"<<'\n';
      for(auto iclasa:iscoala.second.clasa)
      {
        g<<"  <clasa=\""<<iclasa.second.numeclasa<<"\">"<<'\n';
        g<<"    <invatator>"<<iclasa.second.invatator<<"</invatator>"<<'\n';
        g<<"    <cnp>"<<iclasa.second.cnpinvatator<<"</cnp>"<<'\n';
        for(auto ielev:iclasa.second.elev)
        {
          g<<"    <elev=\""<<ielev.second.numeelev<<"\">"<<'\n';
          g<<"      <cnp>"<<ielev.second.cnp<<"</cnp>"<<'\n';
          for(auto imaterie:ielev.second.materie)
          {
            g<<"      <materie=\""<<imaterie.second.numematerie<<"\">"<<'\n';
            g<<"        <note>"<<imaterie.second.note<<"</note>"<<'\n';
            g<<"        <absente>"<<imaterie.second.absente<<"</absente>"<<'\n';
            g<<"      </materie>"<<'\n';
          }
          g<<"    </elev>"<<'\n';
        }
        g<<"  </clasa>"<<'\n';
      }
      g<<"</scoala>"<<'\n';
    }
}
void vizualizare_catalog()
{
    for(auto iscoala:scoala)
    {
      cout<<iscoala.second.numescoala<<'\n';
      for(auto iclasa:iscoala.second.clasa)
      {
        cout<<"Clasa "<<iclasa.second.numeclasa<<'\n';
        cout<<"Invatator "<<iclasa.second.invatator<<'\n';
        cout<<"Elevi: \n";
        for(auto ielev:iclasa.second.elev)
        {
          cout<<ielev.second.numeelev<<'\n';
          for(auto imaterie:ielev.second.materie)
          {
            cout<<"  "<<imaterie.second.numematerie<<'\n';
            cout<<"    Note "<<imaterie.second.note<<'\n';
            cout<<"    Numar absente"<<imaterie.second.absente<<'\n';
          }
        }
      }
    }
}
void iesire()
{
  afisarexml();
  afisare_catalog();
  exit(0);
}
void adaugare(string Nume, string Parola, string Status)
{
    user x;
    x.nume=Nume;
    x.parola=sha256(Parola);
    x.status=Status;
    mp[x.nume]=x;
}
void stergere(string Nume)
{
    mp.erase(Nume);
}
user login()
{
    string nume, parola, status;
    while(1)
    {
      cout<<"Introduceti mai jos datele de logare"<<'\n'<<"User: ";
      cin>>nume;
      if(nume=="0")
        iesire();
      cout<<"Parola: ";
      cin>>parola;
      if(parola=="0")
        iesire();
      parola=sha256(parola);
      if (mp.find(nume) == mp.end())
        cout<<"Acest user nu exista in baza de date \n";
      else
      {
          if(mp[nume].parola != parola)
          {
              cout<<"Parola introdusa este gresita \n";
          }
          else
          {
            if(mp[nume].status!="admin")
            {
              for(auto iscoala:scoala)
                for(auto iclasa:iscoala.second.clasa)
                {
                  if(iclasa.second.cnpinvatator==nume)
                    cout<<"Bine ai venit, "<<iclasa.second.invatator<<"! \n";
                  else
                    for(auto ielev:iclasa.second.elev)
                      if(ielev.second.cnp==nume)
                        cout<<"Bine ai venit, "<<ielev.second.numeelev<<"! \n";
                }
              return mp[nume];
            }
            else
            {
              cout<<"Accesul permis doar persoanelor autorizate!!! Accesul fraudulos va fi pedepsit conform legii! \n";
              return mp[nume];
            }
          }
      }
    }
}
void admin_conturi()
{
  while(1)
  {
    int x;
    cout<<"1.Creeaza un cont \n";
    cout<<"2.Sterge un cont \n";
    cout<<"3.Vizualizati conturi \n";
    cout<<"4.Inapoi \n";
    cout<<"5.Iesire \n";
    cin>>x;
    if(x==0)
        iesire();
    if(x==1)
    {
      cout<<"Dati username: ";
      user nou;
      cin>>nou.nume;
      if(nou.nume=="0")
        iesire();
      cout<<"Dati parola: ";
      cin>>nou.parola;
      if(nou.parola=="0")
        iesire();
      cout<<"Dati status: ";
      cin>>nou.status;
      if(nou.status=="0")
        iesire();
      adaugare(nou.nume,nou.parola,nou.status);
      cout<<"Contul a fost adaugat cu succes! \n";
    }
    else
      if(x==2)
      {
        cout<<"Dati username: ";
        string nou;
        cin>>nou;
        if(nou=="0")
            iesire();
        if (mp.find(nou) == mp.end())
            cout<<"Acest user nu exista in baza de date \n";
        else
        {
            stergere(nou);
            cout<<"Contul a fost sters cu succes! \n";
        }
      }
      else
      if(x==3)
        vizualizare_conturi();
      if(x==4)
          return;
      else
      if(x==5)
        iesire();
  }
}
void elev(user cont)
{
    for(auto iscoala:scoala)
    {
      for(auto iclasa:iscoala.second.clasa)
      {
        for(auto ielev:iclasa.second.elev)
        {
          if(ielev.second.cnp==cont.nume)
          {
            cout<<ielev.second.numeelev<<'\n';
            for(auto imaterie:ielev.second.materie)
            {
              cout<<"  "<<imaterie.second.numematerie<<'\n';
              cout<<"    Note "<<imaterie.second.note<<'\n';
              cout<<"    Numar absente "<<imaterie.second.absente<<'\n';
            }
          }
        }
      }
    }
}
void modificare_note(string SCOALA,string CLASA,string ELEV,string MATERIE)
{
  string NOTE;
  cout<<"Dati noile note: ";
  getline(cin,NOTE);
  if(NOTE=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].elev[ELEV].materie[MATERIE].note=NOTE;
  cout<<"Notele au fost modificate cu succes! \n";
}
void modificare_absente(string SCOALA,string CLASA,string ELEV,string MATERIE)
{
  string ABSENTE;
  cout<<"Dati noile absente: ";
  getline(cin,ABSENTE);
  if(ABSENTE=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].elev[ELEV].materie[MATERIE].absente=ABSENTE;
  cout<<"Absentele au fost modificate cu succes! \n";
}
void invatator(user cont)
{
  string SCOALA, CLASA;
  for(auto iscoala:scoala)
  {
    for(auto iclasa:iscoala.second.clasa)
    {
      if(iclasa.second.cnpinvatator==cont.nume)
      {
        SCOALA=iscoala.second.numescoala;
        CLASA=iclasa.second.numeclasa;
        while(1)
        {
          auto iscoala=scoala[SCOALA];
          auto iclasa=scoala[SCOALA].clasa[CLASA];
          int x;
          string NOTE, ABSENTE, NUME;
          cout<<"1.Modificati note \n";
          cout<<"2.Modificati absente \n";
          cout<<"3.Vizualizare catalog\n";
          cout<<"4.Iesire \n";
          cin>>x;
          if(x==0 || x==4)
            iesire();
          else
          if(x==3)
          {
            for(auto ielev:iclasa.elev)
            {
              cout<<ielev.second.numeelev<<'\n';
              for(auto imaterie:ielev.second.materie)
              {
                cout<<"  "<<imaterie.second.numematerie<<'\n';
                cout<<"    Note "<<imaterie.second.note<<'\n';
                cout<<"    Numar absente "<<imaterie.second.absente<<'\n';
              }
            }
          }
          else
          if(x==2)
          {
            string snume, smaterie;
            cout<<"Dati numele elevului caruia doriti sa ii modificati absentele: ";
            getline(cin,snume);
            getline(cin,snume);
            if(snume=="0")
              iesire();
            if (iclasa.elev.find(snume) == iclasa.elev.end())
                cout<<"Acest elev nu exista in baza de date \n";
            else
            {
              cout<<"Dati numele materiei la care doriti sa ii modificati absentele: ";
              getline(cin,smaterie);
              if(smaterie=="0")
                iesire();
              if ((iclasa.elev[snume].materie.find(smaterie) == iclasa.elev[snume].materie.end()))
                cout<<"Aceasta materie nu exista \n";
              else
                modificare_absente(iscoala.numescoala,iclasa.numeclasa,snume,smaterie);
            }
          }
          else
          if(x==1)
          {
            string snume, smaterie;
            cout<<"Dati numele elevului caruia doriti sa ii modificati notele: ";
            getline(cin,snume);
            getline(cin,snume);
            if(snume=="0")
            iesire();
            if (iclasa.elev.find(snume) == iclasa.elev.end())
                cout<<"Acest elev nu exista in baza de date \n";
            else
            {
              cout<<"Dati numele materiei la care doriti sa ii modificati notele: ";
              getline(cin,smaterie);
              if(smaterie=="0")
                iesire();
              if ((iclasa.elev[snume].materie.find(smaterie) == iclasa.elev[snume].materie.end()))
                cout<<"Aceasta materie nu exista \n";
              else
                modificare_note(iscoala.numescoala,iclasa.numeclasa,snume,smaterie);
            }
          }
        }
      }
    }
  }
}


void sterge_scoala(string SCOALA)
{
  scoala.erase(SCOALA);
}
void sterge_clasa(string SCOALA, string CLASA)
{
  scoala[SCOALA].clasa.erase(CLASA);
}
void sterge_elev(string SCOALA, string CLASA, string ELEV)
{
  scoala[SCOALA].clasa[CLASA].elev.erase(ELEV);

}
void sterge_materie(string SCOALA, string CLASA, string ELEV, string MATERIE)
{
  scoala[SCOALA].clasa[CLASA].elev[ELEV].materie.erase(MATERIE);
  //cout<<"Materia a fost stearsa cu succes! \n";

}



void adaugare_scoala(string SCOALA)
{
  scoala[SCOALA].numescoala=SCOALA;
  cout<<"Scoala a fost adaugata cu succes! \n";
}
void adaugare_clasa(string SCOALA, string CLASA)
{
  scoala[SCOALA].clasa[CLASA].numeclasa=CLASA;
  cout<<"Clasa a fost adaugata cu succes! \n";
}
void adaugare_invatator(string SCOALA, string CLASA)
{
  string new_invatator;
  cout<<"Dati numele invatatorului: ";
  getline(cin,new_invatator);
  if(new_invatator=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].invatator=new_invatator;
  cout<<"Invatatorul a fost adaugata cu succes! \n";
}
void adaugare_cnpinvatator(string SCOALA, string CLASA)
{
  string new_cnpinvatator;
  cout<<"Dati cnpul invatatorului: ";
  getline(cin,new_cnpinvatator);
  if(new_cnpinvatator=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].cnpinvatator=new_cnpinvatator;
  cout<<"Cnpul invatatorului a fost adaugata cu succes! \n";
}
void adaugare_elev(string SCOALA, string CLASA, string ELEV)
{
  scoala[SCOALA].clasa[CLASA].elev[ELEV].numeelev=ELEV;
  cout<<"Elevul a fost adaugat cu succes! \n";
}
void adaugare_cnpelev(string SCOALA, string CLASA, string ELEV)
{
  string new_cnpelev;
  cout<<"Dati cnpul elevului: ";
  getline(cin,new_cnpelev);
  if(new_cnpelev=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].elev[ELEV].cnp=new_cnpelev;
  cout<<"Cnp elevului a fost adaugat cu succes! \n";
}
void adaugare_materie(string SCOALA, string CLASA, string ELEV, string MATERIE)
{
  scoala[SCOALA].clasa[CLASA].elev[ELEV].materie[MATERIE].numematerie=MATERIE;
  cout<<"Materia a fost adaugata cu succes! \n";
}
void adaugare_absente(string SCOALA, string CLASA, string ELEV, string MATERIE)
{
  string new_absente;
  cout<<"Dati absentele: ";
  getline(cin,new_absente);
  if(new_absente=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].elev[ELEV].materie[MATERIE].absente=new_absente;
  cout<<"Absentele au fost adaugate cu succes! \n";
}
void adaugare_note(string SCOALA, string CLASA, string ELEV, string MATERIE)
{
  string new_note;
  cout<<"Dati notele: ";
  getline(cin,new_note);
  if(new_note=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].elev[ELEV].materie[MATERIE].note=new_note;
  cout<<"Notele au fost adaugate cu succes! \n";
}


void modificare_scoala(string SCOALA)
{
  string new_scoala;
  cout<<"Dati noua scoala: ";
  getline(cin,new_scoala);
  if(new_scoala=="0")
    iesire();
  scoala[new_scoala]=scoala[SCOALA];
  scoala[new_scoala].numescoala=new_scoala;
  sterge_scoala(SCOALA);
  cout<<"Scoala a fost modificata cu succes! \n";
}
void modificare_clasa(string SCOALA, string CLASA)
{
  string new_clasa;
  cout<<"Dati noua clasa: ";
  getline(cin,new_clasa);
  if(new_clasa=="0")
    iesire();
  scoala[SCOALA].clasa[new_clasa]=scoala[SCOALA].clasa[CLASA];
  scoala[SCOALA].clasa[new_clasa].numeclasa=new_clasa;
  cout<<"Clasa a fost modificata cu succes! \n";
  sterge_clasa(SCOALA,CLASA);
}
void modificare_invatator(string SCOALA, string CLASA)
{
  string new_invatator;
  cout<<"Dati noul invatator: ";
  getline(cin,new_invatator);
  if(new_invatator=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].invatator=new_invatator;
  cout<<"Invatatorul a fost modificat cu succes! \n";
}
void modificare_cnpinvatator(string SCOALA, string CLASA)
{
  string new_cnpinvatator;
  cout<<"Dati noul cnp al invatatorului: ";
  getline(cin,new_cnpinvatator);
  if(new_cnpinvatator=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].cnpinvatator=new_cnpinvatator;
  cout<<"Cnpul invatatorului a fost modificat cu succes! \n";
}
void modificare_elev(string SCOALA, string CLASA, string ELEV)
{
  string new_elev;
  cout<<"Dati noul elev: ";
  getline(cin,new_elev);
  if(new_elev=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].elev[new_elev]=scoala[SCOALA].clasa[CLASA].elev[ELEV];
  scoala[SCOALA].clasa[CLASA].elev[new_elev].numeelev=new_elev;
  sterge_elev(SCOALA,CLASA,ELEV);
  cout<<"Elevul a fost modificat cu succes! \n";
}
void modificare_cnpelev(string SCOALA, string CLASA, string ELEV)
{
  string new_cnpelev;
  cout<<"Dati noul cnp al elevului: ";
  getline(cin,new_cnpelev);
  if(new_cnpelev=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].elev[ELEV].cnp=new_cnpelev;
  cout<<"Cnpul elevului a fost modificat cu succes! \n";
}
void modificare_materie(string SCOALA, string CLASA, string ELEV, string MATERIE)
{
  string new_materie;
  cout<<"Dati noua materie: ";
  getline(cin,new_materie);
  if(new_materie=="0")
    iesire();
  scoala[SCOALA].clasa[CLASA].elev[ELEV].materie[new_materie]=scoala[SCOALA].clasa[CLASA].elev[ELEV].materie[MATERIE];
  scoala[SCOALA].clasa[CLASA].elev[ELEV].materie[new_materie].numematerie=new_materie;
  sterge_materie(SCOALA,CLASA,ELEV,MATERIE);
  cout<<"Materia a fost modificata cu succes! \n";
}



void administrare_catalog()
{
  string SCOALA, ELEV, CLASA, MATERIE, INVATAOR, NOTE, ABSENTE, CNPELEV, CNPINVATATOR;
  while(1)
  {
    int x;
    cout<<"Ce operatie doriti sa efectuati? \n";
    cout<<"1.Stergeti un element \n";
    cout<<"2.Adaugati un element \n";
    cout<<"3.Modificati un element \n";;
    cout<<"4.Inapoi \n";
    cout<<"5.Iesire \n";
    cin>>x;
    if(x==5 || x==0)
      iesire();
    else
    if(x==4)
      return;
    else
    if(x==1)
    {
      int y;
      cout<<"Ce element doriti sa stergeti? \n";
      cout<<"1.Scoala \n";
      cout<<"2.Clasa \n";
      cout<<"3.Elev \n";
      cout<<"4.Materie \n";
      cout<<"5.Inapoi \n";
      cout<<"6.Iesire \n";
      cin>>y;
      if(y==0 || y==6)
        iesire();
      else
      if(y==5)
        return;
      else
      {
        if(y>=1)
        {
          cout<<"Dati scoala: ";
          getline(cin,SCOALA);
          getline(cin,SCOALA);
          if (scoala.find(SCOALA) == scoala.end())
          {
            cout<<"Scoala nu exista in baza de date \n";
            y=0;
          }
          if(SCOALA=="0")
            iesire();
          if(y==1)
          {
            sterge_scoala(SCOALA);
            cout<<"Scoala a fost stearsa cu succes! \n";
          }
        }
        if(y>=2)
        {
          cout<<"Dati clasa: ";
          getline(cin,CLASA);
          if (scoala[SCOALA].clasa.find(CLASA) == scoala[SCOALA].clasa.end())
          {
            cout<<"Clasa nu exista in baza de date \n";
            y=0;
          }
          if(CLASA=="0")
            iesire();
          if(y==2)
          {
            sterge_clasa(SCOALA,CLASA);
            cout<<"Clasa fost stearsa cu succes! \n";
          }
        }
        if(y>=3)
        {
          cout<<"Dati elevul: ";
          getline(cin,ELEV);
          if (scoala[SCOALA].clasa[CLASA].elev.find(ELEV) == scoala[SCOALA].clasa[CLASA].elev.end())
          {
            cout<<"Elevul nu exista in baza de date \n";
            y=0;
          }
          if(ELEV=="0")
            iesire();
          if(y==3)
          {
            sterge_elev(SCOALA,CLASA,ELEV);
            cout<<"Elevul a fost sters cu succes! \n";
          }
        }
        if(y>=4)
        {
          cout<<"Dati materia: ";
          getline(cin,MATERIE);
          if (scoala[SCOALA].clasa[CLASA].elev[ELEV].materie.find(ELEV) == scoala[SCOALA].clasa[CLASA].elev[ELEV].materie.end())
          {
            cout<<"Materia nu exista in baza de date \n";
            y=0;
          }
          if(MATERIE=="0")
            iesire();
          if(y==4)
          {
            sterge_materie(SCOALA,CLASA,ELEV,MATERIE);
            cout<<"Materia a fost stearsa cu succes! \n";
          }
        }
      }
    }
    if(x==2)
    {
      int y;
      cout<<"Ce element doriti sa adaugati? \n";
      cout<<"1.Scoala \n";
      cout<<"2.Clasa \n";
      cout<<"3.Invatator \n";
      cout<<"4.Cnp invatator \n";
      cout<<"5.Elev \n";
      cout<<"6.Cnp elev \n";
      cout<<"7.Materie \n";
      cout<<"8.Note \n";
      cout<<"9.Absente \n";
      cout<<"10.Inapoi \n";
      cout<<"11.Iesire \n";
      cin>>y;
      if(y==0 || y==11)
        iesire();
      else
      if(y==10)
        return;
      else
      {
        if(y>=1)
        {
          cout<<"Dati scoala: ";
          getline(cin,SCOALA);
          getline(cin,SCOALA);
          if(SCOALA=="0")
            iesire();
          if(y==1)
            adaugare_scoala(SCOALA);
          else
            if (scoala.find(SCOALA) == scoala.end())
            {
              cout<<"Scoala nu exista in baza de date \n";
              y=0;
            }
        }
        if(y>=2)
        {
          cout<<"Dati clasa: ";
          getline(cin,CLASA);
          if(CLASA=="0")
            iesire();
          if(y==2)
            adaugare_clasa(SCOALA,CLASA);
          else
          {
            if (scoala[SCOALA].clasa.find(CLASA) == scoala[SCOALA].clasa.end())
            {
              cout<<"Clasa nu exista in baza de date \n";
              y=0;
            }
            else
            {
              if(y==3)
                adaugare_invatator(SCOALA,CLASA);
              if(y==4)
                adaugare_cnpinvatator(SCOALA,CLASA);
            }
          }
        }
        if(y>=5)
        {
          cout<<"Dati elevul: ";
          getline(cin,ELEV);
          if(ELEV=="0")
            iesire();
          if(y==5)
            adaugare_elev(SCOALA,CLASA,ELEV);
          else
          {
            if (scoala[SCOALA].clasa[CLASA].elev.find(ELEV) == scoala[SCOALA].clasa[CLASA].elev.end())
            {
              cout<<"Elevul nu exista in baza de date \n";
              y=0;
            }
            else
            {
              if(y==6)
                adaugare_cnpelev(SCOALA,CLASA,ELEV);
            }
          }
        }
        if(y>=7)
        {
          cout<<"Dati materia: ";
          getline(cin,MATERIE);
          if(MATERIE=="0")
            iesire();
          if(y==7)
            adaugare_materie(SCOALA,CLASA,ELEV,MATERIE);
          else
          {
            if (scoala[SCOALA].clasa[CLASA].elev[ELEV].materie.find(MATERIE) == scoala[SCOALA].clasa[CLASA].elev[ELEV].materie.end())
            {
              cout<<"Materia nu exista in baza de date \n";
              y=0;
            }
            else
            {
              if(y==8)
                modificare_note(SCOALA,CLASA,ELEV,MATERIE);
              if(y==9)
                modificare_absente(SCOALA,CLASA,ELEV,MATERIE);
            }
          }
        }
      }
    }
    if(x==3)
    {
      int y;
      cout<<"Ce element doriti sa modificati? \n";
      cout<<"1.Scoala \n";
      cout<<"2.Clasa \n";
      cout<<"3.Invatator \n";
      cout<<"4.Cnp invatator \n";
      cout<<"5.Elev \n";
      cout<<"6.Cnp elev \n";
      cout<<"7.Materie \n";
      cout<<"8.Note \n";
      cout<<"9.Absente \n";
      cout<<"10.Inapoi \n";
      cout<<"11.Iesire \n";
      cin>>y;
      if(y==0 || y==11)
        iesire();
      else
      if(y==10)
        return;
      else
      {
        if(y>=1)
        {
          cout<<"Dati scoala: ";
          getline(cin,SCOALA);
          getline(cin,SCOALA);
          if (scoala.find(SCOALA) == scoala.end())
          {
            cout<<"Scoala nu exista in baza de date \n";
            y=0;
          }
          if(SCOALA=="0")
            iesire();
          if(y==1)
            modificare_scoala(SCOALA);
        }
        if(y>=2)
        {
          cout<<"Dati clasa: ";
          getline(cin,CLASA);
          if (scoala[SCOALA].clasa.find(CLASA) == scoala[SCOALA].clasa.end())
          {
            cout<<"Clasa nu exista in baza de date \n";
            y=0;
          }
          if(CLASA=="0")
            iesire();
          if(y==2)
            modificare_clasa(SCOALA,CLASA);
          if(y==3)
            modificare_invatator(SCOALA,CLASA);
          if(y==4)
            modificare_cnpinvatator(SCOALA,CLASA);
        }
        if(y>=5)
        {
          cout<<"Dati elevul: ";
          getline(cin,ELEV);
          if (scoala[SCOALA].clasa[CLASA].elev.find(ELEV) == scoala[SCOALA].clasa[CLASA].elev.end())
          {
            cout<<"Elevul nu exista in baza de date \n";
            y=0;
          }
          if(ELEV=="0")
            iesire();
          if(y==5)
           modificare_elev(SCOALA,CLASA,ELEV);
          if(y==6)
            modificare_cnpelev(SCOALA,CLASA,ELEV);
        }
        if(y>=7)
        {
          cout<<"Dati materia: ";
          getline(cin,MATERIE);
          if (scoala[SCOALA].clasa[CLASA].elev[ELEV].materie.find(MATERIE) == scoala[SCOALA].clasa[CLASA].elev[ELEV].materie.end())
          {
            cout<<"Materia nu exista in baza de date \n";
            y=0;
          }
          if(MATERIE=="0")
            iesire();
          if(y==7)
            modificare_materie(SCOALA,CLASA,ELEV,MATERIE);
          if(y==8)
            modificare_note(SCOALA,CLASA,ELEV,MATERIE);
          if(y==9)
            modificare_absente(SCOALA,CLASA,ELEV,MATERIE);
        }
      }
    }
  }
}
void admin_catalog()
{
  while(1)
  {
    int x;
    cout<<"Ce operatie doriti sa efectuati? \n";
    cout<<"1.Administrare baza de date \n";
    cout<<"2.Vizualizare baza de date \n";
    cout<<"3.Inapoi \n";
    cout<<"4.Iesire \n";
    cin>>x;
    if(x==0 || x==4)
    {
    iesire();
    }
    else
    if(x==3)
    return;
    else
    if(x==2)
    vizualizare_catalog();
    else
    if(x==1)
    administrare_catalog();
  }
}
void admin()
{
  while(1)
  {
    cout<<"Ce operatie doriti sa efectuati? \n";
    cout<<"1.Administrare conturi \n";
    cout<<"2.Administrare baza de date \n";
    cout<<"3.Iesire \n";
    int x;
    cin>>x;
    system("CLS");
    if(x==0)
        iesire();
    if(x==1)
    {
      admin_conturi();
    }
    else
    if(x==2)
      admin_catalog();
    else
    if(x==3)
        return;
  }
}
int main()
{
    citire();
    citire_catalog();
    cout<<"La orice moment, introduceti valoarea 0 pentru a iesi din program \n";
    user cont=login();
    if(cont.status=="admin")
        admin();
    if(cont.status=="elev")
        elev(cont);
    if(cont.status=="invatator")
    {
      invatator(cont);
    }
    afisarexml();
    afisare_catalog();
    return 0;
}
