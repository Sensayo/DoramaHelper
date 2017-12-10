#ifndef URLPARSER_H
#define URLPARSER_H
#include <iostream>
#include <QString>
#include "dorama.h"

void GetHostPageFromURL(QString _url, QString &_host, QString & _page);

int GetPageHTMLCode(QString _url);

void SearchDoramaData(QString&_name,int &_series);

Dorama CreateDoramaItem(QString _url);

#endif // URLPARSER_H
