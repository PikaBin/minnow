#include <stdexcept>

#include "byte_stream.hh"
#include <iostream>
using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity )
  , closeFlag( false )
  , pushed_number( 0 )
  , errFlag( false )
  , poped_number( 0 )
  , dataQue()
  , allPushstr()
{}

void Writer::push( string data )
{

  uint64_t cap = available_capacity();
  uint64_t dataLen = data.size();
  uint64_t allowNum = min( dataLen, cap );

  // 每次推入前先判断剩余容量,超出则不入
  if ( cap <= 0 ) {
    // std::cerr<<"avvilable capacity is not enough"<<cap<<endl;
    return;
  }

  for ( uint64_t i = 0; i < allowNum; i++ ) {
    dataQue.push( data[i] );
    allPushstr += data[i];
  }
  pushed_number += allowNum;
}

void Writer::close()
{
  closeFlag = true;
}

void Writer::set_error()
{
  errFlag = true;
  cerr << " error appears in writer" << endl;
}

bool Writer::is_closed() const
{
  return closeFlag;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - pushed_number + poped_number;
  // return {};
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return pushed_number;
}

std::string Reader::peek() const
{
  int count = dataQue.size();
  int beginPos = allPushstr.length() - count;
  // cout<<"all push:"<<allPushstr<<" begin: "<<beginPos<<" count: "<<count<<endl;
  string remainInque = allPushstr.substr( beginPos );
  // std::cout<<"peek: "<<remainInque<<std::endl;
  return remainInque;
  // return string_view(remainInque);
  // std::cout<<"the data queue is empty!";
  // return {};
}

bool Reader::is_finished() const
{
  // Your code here.
  return closeFlag && ( dataQue.size() == 0 );
}

bool Reader::has_error() const
{
  // Your code here.
  return errFlag;
}

void Reader::pop( uint64_t len )
{
  try {
    for ( size_t i = 0; i < len; i++ ) {
      // if len > queue.size()
      dataQue.pop();
    }
    poped_number += len;
  } catch ( const std::exception& e ) {
    std::cerr << e.what() << '\n';
    errFlag = true;
  }
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  // return pushed_number - poped_number;
  // std::cout<< "dataque's size is :"<<dataQue.size()<<endl;
  return dataQue.size();
}

uint64_t Reader::bytes_popped() const
{
  return poped_number;
}
