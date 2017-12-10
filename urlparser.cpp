#include "urlparser.h"
#include "dorama.h"
#include "boost/asio.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/regex.hpp"
#include <fstream>

#include <QString>

using boost::asio::ip::tcp;

void GetHostPageFromURL(QString _url, QString &_host, QString & _page)
{
  if (_url[0] == 'h')
    _url = _url.remove(0,7);
  int position = _url.indexOf("/");
  _host = _url.mid(0,position);
  _page = _url.mid(position,_url.size()-1);
}

int GetPageHTMLCode(QString _url)
{
  try
  {
    QString host = "", page = "";
    GetHostPageFromURL(_url, host, page);

    boost::asio::io_service io_service;

    // Список конечных точкек соответствующие серверу
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(host.toStdString(), "http");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::resolver::iterator end;

    tcp::socket socket(io_service);
    boost::system::error_code error = boost::asio::error::host_not_found;
    while (error && endpoint_iterator != end)
      {
        socket.close();
        socket.connect(*endpoint_iterator++, error);
      }
    if (error)
      throw boost::system::system_error(error);

    boost::asio::streambuf request;
    std::ostream request_stream(&request);

    request_stream << "GET " << page.toStdString() << " HTTP/1.0\r\n";
    request_stream << "Host: " << host.toStdString() << "\r\n";
    request_stream << "Accept: text/html\r\n";
    request_stream << "Cache-Control: no-cache\r\n";
    request_stream << "Connection: close\r\n\r\n";
    request_stream.flush();

    boost::asio::write(socket, request);
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    std::istream response_stream(&response);
    std::string header;
    while (std::getline(response_stream, header) && header != "\r");

    std::ofstream file("web_source.txt");
    if (!file)
      throw std::runtime_error("Cannot create file");

    while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
      {
        file << &response;
      }
    if (error != boost::asio::error::eof)
      throw boost::system::system_error(error);
  }
  // Надо подумать куда кидать

  catch (std::exception& e)
  {
    //std::cout << "Exception: " << e.what();
    //std::getchar();
  }
  return 0;
}

void SearchDoramaData(QString&_name,int &_series)
{
  std::fstream file;
  file.open("web_source.txt");

  std::string line = "", flagTagSeries="read-last", flagTagName="eng-name";
  boost::regex RegExSeries("[0-9]+\"");
  boost::regex RegExName(">+[A-Z,a-z,0-9, ]+<");
  boost::smatch resultNumber;

  while (!_streamfile.eof()) {
          getline(_streamfile, line);
          if (line.find(flagTagSeries) != std::string::npos)
          {
                  std::string::const_iterator ItStart = line.begin();
                  std::string::const_iterator ItEnd = line.end();
                  boost::regex_search(ItStart, ItEnd, resultNumber, RegExSeries);
                  std::string ref = resultNumber[0];
                  series = boost::lexical_cast<int>(ref.c_str(),ref.length()-1);//lenght()-1 cut \"
          }
          else if (line.find(flagTagName) != std::string::npos)
          {
                  std::string::const_iterator ItStart = line.begin();
                  std::string::const_iterator ItEnd = line.end();
                  boost::regex_search(ItStart, ItEnd, resultNumber, RegExName);
                  _name = boost::lexical_cast<std::string>(resultNumber);
                  _name.mid(1,_name.size()-2);
          }

          line = "";
  }
    file.close();
}

Dorama CreateDoramaItem(QString _url)
{
  QString name="";
  int series=0;

  if(GetPageHTMLCode(_url)==0)
    SearchDoramaData(name,series);

  return new Dorama(name,_url,series);
}
