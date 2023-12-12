#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{

  Address DestAdress( host, "http" );
  TCPSocket clientSocket;
  clientSocket.connect( DestAdress );
  /**
   * 使用socket与http服务器沟通的语法是这样的：
   * GET /hello HTTP/1.1        //注意这里换行符号为\r\n
   * Host: cs144.keithw.org
   * Connection:  close
   * 注意最后要发送一个\r\n
   */

  const string sendData = "GET " + path + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";
  // cout<<sendData;
  clientSocket.write( sendData );
  string buffer = "";
  while ( !clientSocket.eof() ) {
    clientSocket.read( buffer );
    cout << buffer;
  }

  clientSocket.close();
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
