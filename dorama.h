#ifndef DORAMA_H
#define DORAMA_H
#include <QString>

class Dorama
{

private:

    QString m_name;
    QString m_url;
    int m_lastViewedSeries;
    int m_newSeries;

public:

    Dorama(QString _name,QString _url,int _newSeries)
        :m_name(_name),m_url(_url),m_newSeries(_newSeries)
    {
        m_lastViewedSeries=0;
    }
    ~Dorama(){}

    QString getName()const{return m_name;}
    QString getURL()const{return m_url;}
    int getLastSeries()const{return m_lastViewedSeries;}
    int getNewSeries()const{return m_newSeries;}
    void setLastWatchedSeries(int _lastViewedSeries){
      if (_lastViewedSeries>0&&_lastViewedSeries<=getNewSeries())
        m_lastViewedSeries=_lastViewedSeries;
    }

};

#endif // DORAMA_H
